#include <MainFile.h>
using namespace std;


void GetElementFluxVector(const int i_elem,  const int nnode_ele, const int dof_node,
		const int Ng, const int ShapeOrder, const int Model2D, const int ndim, const arma::mat& coords, const arma::imat& elem_node,
		const arma::mat& elem_stiff,const int location, const arma::mat& Uur,
		arma::mat& stress, arma::mat& strain)

{
  arma::mat 	xel(ndim, nnode_ele);
  arma::colvec 	uel(nnode_ele*dof_node);
  arma::colvec r1;
  arma::colvec w1;
  arma::colvec r2;
  arma::colvec w2;
  arma::mat k;
  arma::colvec rvec;
  arma::rowvec Nhat;
  arma::mat Noi;
  arma::mat DNhat;
  arma::mat J;
  arma::mat Bhat;
  arma::mat Boi;
  arma::mat I;
  rvec = arma::zeros<arma::colvec>(Ng);
  k = arma::zeros<arma::mat>(ndim*ndim,ndim*ndim);
  J = arma::zeros<arma::mat>(ndim, ndim);
  I = arma::eye<arma::mat>(ndim,ndim);

  for (int i=0;i<nnode_ele;i++ ) {
  	  int node = elem_node(i,i_elem-1);
	  for (int j=0;j<ndim;j++) {
	  	uel(2*i+j) = Uur(node-1,j);
		xel(j,i) = coords(node-1,j);
	  }
  }
 
  if (location == 1) {
  	 // Evaluating flux at guass points (same used to obtain field approximation    
	 //stress = kmat*Bhat*uel; for each gauss point
	 //gradU = Bhat*uel; for each gauss point
  	GetMaterialMatrix(Model2D, i_elem, elem_stiff, k);
	for(int i=0; i<Ng; i++){
    GaussQuadrature(Ng, r1, w1);
    	for(int j=0; j<Ng; j++){
    	GaussQuadrature(Ng, r2, w2);
    	rvec(0) = r1(i);
    	rvec(1) = r2(j);
    	Quad2DShapeFunctions(ShapeOrder, rvec, Nhat, DNhat);
    	J = xel * DNhat.t(); 
    	Bhat = arma::inv(J.t()) * DNhat;
    	Boi = arma::kron(Bhat, I);
    	stress.col(2*i+j) = k * (Boi * uel);
    	strain.col(2*i+j) = Boi * uel;
    	}
  	}
	 
  }

  if (location == 0) {
  	// Evaluating flux at the center of isoparametric element
	//flux = -kmat*Bhat*uel; for the centroid
	//gradT = Bhat*uel;  for the centroid
	GetMaterialMatrix(Model2D, i_elem, elem_stiff, k);
	rvec(0) = 0;
    rvec(1) = 0;
	Quad2DShapeFunctions(ShapeOrder, rvec, Nhat, DNhat);
  	J = xel * DNhat.t(); 
    Bhat = arma::inv(J.t()) * DNhat;
    Boi = arma::kron(Bhat, I);
    stress.col(0) = k * (Boi * uel);
    strain.col(0) = Boi * uel;
  
  }
}
