#include <MainFile.h>
using namespace std;


void EvaluateFieldGradient( const int nnode_ele, const int n_node, const int n_elem, const int dof_node,
		const int Ng, const int ShapeOrder, const int ndim, const arma::mat& coords, const arma::imat& elem_node,
		const arma::mat& elem_stiff, const arma::mat& Uur,
		arma::mat& FluxAtIntegrationPoints, arma::mat& ElementFlux, arma::mat& NodalFlux,
		arma::colvec& MagnitudeNodalFlux, arma::mat& NodalGradT, arma::colvec& MagnitudeGradT)
		
{

	  FluxAtIntegrationPoints = arma::zeros<arma::mat>(n_elem*ndim*Ng,ndim);
	  ElementFlux = arma::zeros<arma::mat>(n_elem,ndim);
	  NodalFlux = arma::zeros<arma::mat>(n_node,ndim);
	  MagnitudeNodalFlux = arma::zeros<arma::colvec>(n_node);
	  NodalGradT = arma::zeros<arma::mat>(n_node,ndim);
	  MagnitudeGradT = arma::zeros<arma::colvec>(n_node);

	  // ------------------------------------------------------------
	  // ------- Get the Flux at the integration points -------------
	  // ------------------------------------------------------------
	  int location = 1; // evaluate at the gauss points used for the solution
	  arma::mat flux = arma::zeros<arma::mat>(ndim,Ng*ndim);
	  arma::mat gradT = arma::zeros<arma::mat>(ndim,Ng*ndim);

	  for (int i=0;i<n_elem;i++) {
	  	int iel = i + 1;
		GetElementHeatFluxVector(iel,nnode_ele, dof_node, Ng, ShapeOrder, ndim, coords, elem_node,
					elem_stiff, location , Uur, flux, gradT);
		for (int j=0;j<ndim*Ng;j++){
			int pos = (i)*ndim*Ng + j;
			FluxAtIntegrationPoints.row(pos) = arma::trans(flux.col(j));
		  }
	  }
		cout << "Finish flux at integration points" << endl;
	  // ------------------------------------------------------------
	  // ------- Get the Flux at the centroid -----------------------
	  // ------------------------------------------------------------
	  location = 0; // evaluate at the gauss points used for the solution
	  arma::mat fluxC = arma::zeros<arma::mat>(ndim,1);
	  arma::mat gradTC = arma::zeros<arma::mat>(ndim,1);
	  arma::mat ElementGradT = arma::zeros<arma::mat>(n_elem,ndim);

	  for (int i=0;i<n_elem;i++) {
	  	  int iel = i + 1;
		  GetElementHeatFluxVector(iel,nnode_ele, dof_node, Ng, ShapeOrder, ndim, coords, elem_node,
					elem_stiff, location , Uur, fluxC, gradTC);
		  ElementFlux.row(i) = arma::trans(fluxC);
		  ElementGradT.row(i) = arma::trans(gradTC);
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
			  NodalFlux.row(node) = NodalFlux.row(node) + ElementFlux.row(i);
			  NodalGradT.row(node) = NodalGradT.row(node) + ElementGradT.row(i);
		  }
	  }
	  for (int i=0;i<n_node;i++) {
	  		  for (int j=0;j<ndim;j++) {
	  			  NodalFlux(i,j) = NodalFlux(i,j)/scale(i);
	  			  NodalGradT(i,j) = NodalGradT(i,j)/scale(i);
	  		  }
	  		  MagnitudeNodalFlux(i) = arma::norm( NodalFlux.row(i) , 2 );
	  		  MagnitudeGradT(i) = arma::norm( NodalGradT.row(i) , 2 );
	  }

  
}
