#include <MainFile.h>
using namespace std;


void EvaluateFieldGradient( const int nnode_ele, const int n_node, const int n_elem, const int dof_node,
		const int Ng, const int ShapeOrder, const int Model2D, const int ndim, const arma::mat& coords, 
		const arma::imat& elem_node, const arma::mat& elem_stiff, const arma::mat& Uur,
		arma::mat& StrainAtIntegrationPoints, arma::mat& StressAtIntegrationPoints,
		arma::mat& TpAtIntegrationPoints, arma::mat& VMAtIntegrationPoints,
		arma::mat& StrainAtCentroid, arma::mat& StressAtCentroid, arma::mat& TpAtCentroid,
		arma::mat& StrainAtNodes, arma::mat& StressAtNodes, arma::mat& TpAtNodes, arma::mat&  VMAtNodes)

{

	  StrainAtIntegrationPoints = arma::zeros<arma::mat>(n_elem*Ng*Ng,ndim*ndim);
	  StressAtIntegrationPoints = arma::zeros<arma::mat>(n_elem*Ng*Ng,ndim*ndim);
	  TpAtIntegrationPoints = arma::zeros<arma::mat>(n_elem*Ng*Ng,3);
	  VMAtIntegrationPoints = arma::zeros<arma::mat>(n_elem*Ng*Ng,1);
	  StrainAtCentroid = arma::zeros<arma::mat>(n_elem,ndim*ndim);
	  StressAtCentroid = arma::zeros<arma::mat>(n_elem,ndim*ndim);	
	  TpAtCentroid = arma::zeros<arma::mat>(n_elem,3);	
	  StrainAtNodes = arma::zeros<arma::mat>(n_node,ndim*ndim);
	  StressAtNodes = arma::zeros<arma::mat>(n_node,ndim*ndim);
	  TpAtNodes = arma::zeros<arma::mat>(n_node,3);
	  VMAtNodes = arma::zeros<arma::mat>(n_node,1);

	  // ------------------------------------------------------------
	  // ------- Get the Flux at the integration points -------------
	  // ------------------------------------------------------------
	  int location = 1; // evaluate at the gauss points used for the solution
	  arma::mat stress = arma::zeros<arma::mat>(ndim*ndim,Ng*Ng);
	  arma::mat strain = arma::zeros<arma::mat>(ndim*ndim,Ng*Ng);

	  for (int i=0;i<n_elem;i++) {
		  //cout<<"Element = "<<i<<"\n";
		  
		  double e = elem_stiff(i,0);
		  double nu = elem_stiff(i,1);
		  double lambda = e*nu/((1+nu)*(1-2.*nu));
		
		  int i_elem = i+1;
		  GetElementFluxVector(i_elem,nnode_ele, dof_node, Ng, ShapeOrder, Model2D, ndim, coords, elem_node,
					elem_stiff, location , Uur, stress, strain);
		  for (int j=0;j<Ng*Ng;j++){
			  int pos = (i)*Ng*Ng + j;
			  //cout<<"pos = "<<pos<<"\n";
			  StressAtIntegrationPoints.row(pos) = arma::trans(stress.col(j));
			  StrainAtIntegrationPoints.row(pos) = arma::trans(strain.col(j));
			  
			  double sigmaave = (stress(0,j) + stress(3,j))/2;
			  double radius = sqrt ( pow((stress(0,j) - stress(3,j))/2,2) + pow(stress(1,j),2)   );
			  
			  TpAtIntegrationPoints(pos,0) = sigmaave + radius;
			  TpAtIntegrationPoints(pos,1) = sigmaave - radius;
			  if (Model2D == 1) {
				  TpAtIntegrationPoints(pos,2) = 0;
			  }
			  else if(Model2D == 2) {
				  TpAtIntegrationPoints(pos,2) = lambda*(strain(0,j)+strain(3,j));
			  }
			  
			  VMAtIntegrationPoints(pos,0) = sqrt( 0.5* (
					  pow( TpAtIntegrationPoints(pos,0) - TpAtIntegrationPoints(pos,1),2) + 
					  pow( TpAtIntegrationPoints(pos,0) - TpAtIntegrationPoints(pos,2),2) + 
					  pow( TpAtIntegrationPoints(pos,1) - TpAtIntegrationPoints(pos,2),2) 
			  ));
			  
		  }
	  }
	  //cout<<StressAtIntegrationPoints<<"\n";
	  //cout<<StrainAtIntegrationPoints<<"\n";

	  // ------------------------------------------------------------
	  // ------- Get the Flux at the centroid -----------------------
	  // ------------------------------------------------------------
	  location = 0; // evaluate at the gauss points used for the solution
	  arma::mat stressC = arma::zeros<arma::mat>(ndim*ndim,1);
	  arma::mat strainC = arma::zeros<arma::mat>(ndim*ndim,1);

	  for (int i=0;i<n_elem;i++) {
		  //cout<<"Element = "<<i<<"\n";		  
		  double e = elem_stiff(i,0);
		  double nu = elem_stiff(i,1);
		  double lambda = e*nu/((1+nu)*(1-2.*nu));
		  int i_elem = i+1;
		  GetElementFluxVector(i_elem,nnode_ele, dof_node, Ng, ShapeOrder, Model2D, ndim, coords, elem_node,
					elem_stiff, location , Uur, stressC, strainC);
		  StressAtCentroid.row(i) = arma::trans(stressC);
		  StrainAtCentroid.row(i) = arma::trans(strainC);
		  
		  double sigmaave = (stressC(0) + stressC(3))/2;
		  double radius = sqrt ( pow((stressC(0) - stressC(3))/2,2) + pow(stressC(1),2)   );
		  
		  TpAtCentroid(i,0) = sigmaave + radius;
		  TpAtCentroid(i,1) = sigmaave - radius;
		  if (Model2D == 1) {
			  TpAtCentroid(i,2) = 0;
		  }
		  else if(Model2D == 2) {
			  TpAtCentroid(i,2) = lambda*(strainC(0)+strainC(3));
		  }
		  
		  
	  }


	  // ------------------------------------------------------------
	  // ------- Extrapolate flux to nodes    -----------------------
	  // ------------------------------------------------------------
	  arma::colvec scale = arma::zeros<arma::mat>(n_node);
	  int node;
	  for (int i=0;i<n_elem;i++) {
		  for (int j=0;j<nnode_ele;j++) {
			  node = elem_node(j,i)-1;
			  scale(node) = scale(node) + 1;
			  StressAtNodes.row(node) = StressAtNodes.row(node) + StressAtCentroid.row(i);
			  StrainAtNodes.row(node) = StrainAtNodes.row(node) + StrainAtCentroid.row(i);
			  TpAtNodes.row(node) = TpAtNodes.row(node) + TpAtCentroid.row(i);
		  }
	  }
	  for (int i=0;i<n_node;i++) {
	  		  for (int j=0;j<ndim*ndim;j++) {
	  			StressAtNodes(i,j) = StressAtNodes(i,j)/scale(i);
	  			StrainAtNodes(i,j) = StrainAtNodes(i,j)/scale(i);		  		
	  		  }
	  		  TpAtNodes.row(i) = TpAtNodes.row(i)/scale(i);
			  VMAtNodes(i) = sqrt( 0.5* (
					  pow( TpAtNodes(i,0) - TpAtNodes(i,1),2) + 
					  pow( TpAtNodes(i,0) - TpAtNodes(i,2),2) + 
					  pow( TpAtNodes(i,1) - TpAtNodes(i,2),2) 
			  ));
	  }



}
