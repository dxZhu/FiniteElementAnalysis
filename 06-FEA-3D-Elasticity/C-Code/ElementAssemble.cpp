#include "MainFile.h"
#include <iostream>

using namespace std;

void ElementAssemble( const int edof, const int i_elem,  const int nnode_ele,
		const int Ng, const int ShapeOrder, const int ndim, const int& Model2D, 
		const arma::mat& coords, const arma::imat& elem_node,
		const arma::mat& elem_stiff, const arma::mat& elem_load, const arma::mat& elem_area,
		arma::mat& kel, arma::colvec& pel)
{
  
  //Get Gauss point and Gauss function:
  arma::colvec r1;
  arma::colvec w1;
  arma::colvec r2;
  arma::colvec w2;
  arma::rowvec Nhat;
  arma::mat DNhat;
  arma::colvec rvec;
  arma::mat Xe;
  arma::mat J;
  arma::mat k;
  arma::mat Bhat;
  arma::mat I;
  arma::colvec b;
  arma::mat Noi;
  arma::mat Boi;
  r1 = arma::zeros<arma::colvec>(Ng);
  r2 = arma::zeros<arma::colvec>(Ng);
  w1 = arma::zeros<arma::colvec>(Ng);
  w2 = arma::zeros<arma::colvec>(Ng);
  rvec = arma::zeros<arma::colvec>(ndim);
  Xe = arma::zeros<arma::mat>(ndim, nnode_ele);
  J = arma::zeros<arma::mat>(ndim, ndim);
  k = arma::zeros<arma::mat>(ndim,ndim);
  Bhat = arma::zeros<arma::mat>(ndim, nnode_ele);
  k = arma::zeros<arma::mat>(ndim*ndim, ndim*ndim);
  b = arma::zeros<arma::colvec>(ndim);
  I = arma::eye<arma::mat>(ndim,ndim); // 2x2 identity matrix

  //get Xe
  Xe = arma::zeros<arma::mat>(ndim, nnode_ele);
  for(int i=0; i<nnode_ele; i++){
    int node = elem_node(i, i_elem-1);
    for(int j=0; j<ndim; j++){
  		Xe(j,i) = coords(node-1,j);}
  	}

  //Get Material Stiffness Matrix:
  GetMaterialMatrix(Model2D, i_elem, elem_stiff, k);
  
  //Get body load:
  b << elem_load(i_elem-1,0) << arma::endr
  	<< elem_load(i_elem-1,1) << arma::endr;
  
  //Get kel and pel:
  for(int i=0; i<Ng; i++){
    GaussQuadrature(Ng, r1, w1);
    for(int j=0; j<Ng; j++){
    GaussQuadrature(Ng, r2, w2);
    rvec(0) = r1(i);
    rvec(1) = r2(j);
    Quad2DShapeFunctions(ShapeOrder, rvec, Nhat, DNhat);
    J = Xe * DNhat.t(); 
    Noi = arma::kron(Nhat, I);
    Bhat = arma::inv(J.t()) * DNhat;
    Boi = arma::kron(Bhat,I);
    kel = kel + Boi.t() * k * Boi * arma::det(J) * w1(i) * w2(j);
    pel = pel + Noi.t() * b * arma::det(J) * w1(i) * w2(j); 
    }
  }
}