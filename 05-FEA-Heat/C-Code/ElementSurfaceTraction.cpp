#include "MainFile.h"
#include <iostream>

using namespace std;

void ElementSurfaceTraction( const int edof, const int i,  const int nnode_ele,
		const int Ng, const int ShapeOrder, const int ndim, const arma::mat& coords, const arma::imat& elem_node,
		const arma::imat& trac_ele, double betaP, double betaK, bool stiffness, bool lumped,
		arma::mat& kel, arma::colvec& pel)
{
  int m = i;
  int ielem = trac_ele(m,0);
  int face = trac_ele(m,1);
  arma::colvec rg;
  arma::colvec wg;
  arma::colvec nh;
  arma::colvec rvec;
  arma::mat Xe;
  arma::mat J;
  arma::mat k;
  arma::rowvec Nhat;
  arma::mat DNhat;
  arma::mat Nl;
  arma::mat Nc;
  arma::colvec temp;	//used in lumped

  Nl = arma::zeros<arma::mat>(nnode_ele,nnode_ele);
  kel = arma::zeros<arma::mat>(nnode_ele,nnode_ele);
  pel = arma::zeros<arma::colvec>(nnode_ele);
        	
  GaussQuadrature(Ng, rg, wg);
  
  for(int i=0; i<Ng; i++){
  	switch(face){
  		case 1:
  		nh << 0 << arma::endr
  		   << -1 << arma::endr;	//normal vector
  		rvec << rg(i) << arma::endr 
  			<< -1 << arma::endr;
  		break;
  		case 2:
  		nh << 1 << arma::endr
  		   << 0 << arma::endr;	//normal vector
  		rvec << 1 << arma::endr
  			<< rg(i) << arma::endr;
  		break;
  		case 3:
  		nh << 0 << arma::endr
  		   << 1 << arma::endr;	//normal vector
  		rvec << rg(i) << arma::endr
  			<< 1 << arma::endr;
  		break;
  		case 4:
  		nh << -1 << arma::endr
  		   << 0 << arma::endr;	//normal vector
  		rvec << -1 << arma::endr
  			<< rg(i) << arma::endr;
  		break;
  		}
  	Quad2DShapeFunctions(ShapeOrder, rvec, Nhat, DNhat);
 //	cout << rvec << endl << Nhat << endl << DNhat << endl;
  	
//Set Xe
  Xe = arma::zeros<arma::mat>(ndim, nnode_ele);
  for(int i=0; i<nnode_ele; i++){
    int node = elem_node(i,ielem-1);
    for(int j=0; j<ndim; j++){
  		Xe(j,i) = coords(node-1,j);}
  	}
    J = Xe * DNhat.t(); 
    pel = pel + Nhat.t() * betaP * arma::det(J) * arma::norm(arma::inv(J.t()) * nh) * wg(i);
//    cout << pel << endl << Nhat.t() << endl << J << endl;

    if(stiffness){
      Nc = Nhat.t() * Nhat;
      if(lumped){
        temp = arma::sum(Nc,1);
        for(int k=0; k<nnode_ele; k++){
        	Nl(k,k) = temp(k);}
        kel = kel+ betaK * Nl * arma::det(J) * arma::norm(arma::inv(J.t()) * nh) * wg(i);}	
      else{
        kel = kel+ betaK * Nc * arma::det(J) * arma::norm(arma::inv(J.t()) * nh) * wg(i);}
    }
    }
  }