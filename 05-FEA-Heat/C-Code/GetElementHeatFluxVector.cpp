#include <MainFile.h>
using namespace std;


void GetElementHeatFluxVector(const int i_elem,  const int nnode_ele, const int dof_node,
		const int Ng, const int ShapeOrder, const int ndim, const arma::mat& coords, const arma::imat& elem_node,
		const arma::mat& elem_stiff,const int location, const arma::mat& Uur,
		arma::mat& flux, arma::mat& gradT)

		/* You need to complete this function. Note that in order to evaluate the flux, you need
		to calculate flux(r) = -[k]*[Bhat(r)]*{T}. Note that this follows the same format used to determine the conductivity matrix. [Bhat(r)]'*[k]*[Bhat(r)].
		
		When location is 1, evaluate the flux at the gauss points (and hence flux will be a 2x4 matrix)
		When location is 0, evaluate the flux at the centroid (r = [0,0], and hence the flux is a 2x1 matrix) */
				
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
  arma::mat DNhat;
  arma::mat J;
  arma::mat Bhat;
  rvec = arma::zeros<arma::colvec>(Ng);
  k = arma::zeros<arma::mat>(ndim*ndim,ndim*ndim);
  J = arma::zeros<arma::mat>(ndim, ndim);

  for (int i=0;i<nnode_ele;i++ ) {
	  uel(i) = Uur(elem_node(i,i_elem-1)-1,0);
	  for (int j=0;j<ndim;j++) {
		  xel(j,i) = coords(elem_node(i,i_elem-1)-1,j);
	  }
  }

  if (location == 1) {
	// Evaluating flux at guass points (same used to obtain field approximation    
	 //flux = -kmat*Bhat*uel; for each gauss point
	 //gradT = Bhat*uel; for each gauss point
	k << elem_stiff(i_elem-1, 0) << 0 << arma::endr
      << 0 << elem_stiff(i_elem-1, 1) << arma::endr;
	for(int i=0; i<Ng; i++){
    GaussQuadrature(Ng, r1, w1);
    	for(int j=0; j<Ng; j++){
    	GaussQuadrature(Ng, r2, w2);
    	rvec(0) = r1(i);
    	rvec(1) = r2(j);
    	Quad2DShapeFunctions(ShapeOrder, rvec, Nhat, DNhat);
    	J = xel * DNhat.t(); 
    	Bhat = arma::inv(J.t()) * DNhat;
    	flux.col(2*i+j) = -k * Bhat * uel;
    	}
  	}
  }

  if (location == 0) {
	  // Evaluating flux at the center of isoparametric element
	  //flux = -kmat*Bhat*uel; for the centroid
	  //gradT = Bhat*uel;  for the centroid
	k << elem_stiff(i_elem-1, 0) << 0 << arma::endr
      << 0 << elem_stiff(i_elem-1, 1) << arma::endr;
    	rvec(0) = 0;
    	rvec(1) = 0;
    	Quad2DShapeFunctions(ShapeOrder, rvec, Nhat, DNhat);
    	J = xel * DNhat.t(); 
    	Bhat = arma::inv(J.t()) * DNhat;
    	flux.col(0) = -k * Bhat * uel;
    	gradT.col(0) = Bhat * uel;
  }
}
