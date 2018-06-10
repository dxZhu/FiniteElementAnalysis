#include "MainFile.h"

using namespace std;

void GlobalIdMatrix(int n_node, int n_elem, int n_load, int n_pre_disp, 
  int nnode_ele, int Ng, int ShapeOrder, double& r, 
  arma::ivec& UMATid, arma::ivec& DLOADid, arma::mat& Nr, arma::mat& DNr, 
  arma::imat elem_node,  arma::mat coords,
  arma::rowvec& Br, arma::vec& Jr,arma::colvec& Rr, arma::mat& X, arma::fcolvec& w){
	Nr = arma::zeros<arma::mat>(Ng,nnode_ele);	//Change to mat
	DNr = arma::zeros<arma::mat>(Ng,nnode_ele);	//Change to mat
	Jr = arma::zeros<arma::vec>(Ng);
	Br = arma::zeros<arma::rowvec>(nnode_ele);	
	Rr = arma::zeros<arma::colvec>(Ng);
	w = arma::zeros<arma::fcolvec>(Ng);
	X = arma::zeros<arma::mat>(nnode_ele,n_elem);
	
//Initialize X	
	for(int i=0; i<n_elem; i++){
		for(int j=0; j<nnode_ele; j++){
			int node = elem_node(j,i);
			X(j,i) = coords(node-1,0);
		}
	}	
	
	
//Initialize r and w for different Ng;
	if(Ng == 1){
		Rr(0) = 0.0;
		w(0) = 2.0;	
	}else if(Ng == 2){
		Rr(0) = -1/sqrt(3.0);
		Rr(1) = 1/sqrt(3.0);
		w(0) = 1.0;
		w(1) = 1.0;	
	}else if(Ng == 3){
		Rr(0) = -sqrt(0.6);
		Rr(1) = 0;
		Rr(2) = sqrt(0.6);
		w(0) = 5.0 / 9;
		w(1) = 8.0 / 9;
		w(2) = 5.0 / 9;
	}else if(Ng == 4){
		Rr(0) = -sqrt(1/35.0 * (15.0 + sqrt(30.0) * 2.0));
		Rr(1) = -sqrt(1/35.0 * (15.0 - sqrt(30.0) * 2.0));
		Rr(2) = sqrt(1/35.0 * (15.0 - sqrt(30.0) * 2.0));
		Rr(3) = sqrt(1/35.0 * (15.0 + sqrt(30.0) * 2.0));
		w(0) = 49.0 /6/(18.0 + sqrt(30.0));
		w(1) = 49.0 /6/(18.0 - sqrt(30.0));
		w(2) = 49.0 /6/(18.0 - sqrt(30.0));
		w(3) = 49.0 /6/(18.0 + sqrt(30.0));
	}else{cout << "Ng should not be larger than 4!";}
	
	//Initialize Shape Function
	r = 0;
	if(ShapeOrder ==1 ){
	for(int i=0; i<Ng; i++){
	r = Rr(i);
	Nr(i,0) = (1 - r) * 0.5;
	Nr(i,1) = (1 + r) * 0.5;
	DNr(i,0) = -0.5;
	DNr(i,1) = 0.5;}
	}
	else if(ShapeOrder ==2 ){
	for(int i=0; i<Ng; i++){
	r = Rr(i);
	Nr(i,0) = 0.5 * r * (r - 1);
	Nr(i,1) = -(r + 1) * (r - 1);
	Nr(i,2) = 0.5 * r * (r + 1);
	DNr(i,0) = r - 0.5;
	DNr(i,1) = -2 * r;
	DNr(i,2) = r + 0.5;}
	}
	else if(ShapeOrder ==3 ){
	for(int i=0; i<Ng; i++){
	r = Rr(i);
	Nr(i,0) = -9/16 * (r - 1) * (r - 1/3) * (r + 1/3);
	Nr(i,1) = 27/16 * (r - 1) * (r - 1/3) * (r + 1);
	Nr(i,2) = -27/16 * (r - 1) * (r + 1/3) * (r + 1);
	Nr(i,3) = 9/16 * (r - 1/3) * (r + 1/3) * (r + 1);
	DNr(i,0) = 1/16 * (-27 * r * r + 18 * r + 1);
	DNr(i,1) = 9/16 * (9 * r * r - 2 * r - 3);
	DNr(i,2) = -9/16 * (9 * r * r + 2 * r - 3);
	DNr(i,3) = 1/16 * (27 * r * r + 18 * r - 1);}
	}
/*cout << "The w is " << w;
cout << "Rr is " << Rr;
cout << "The Nr is " << Nr;
cout << "The DNr is " << DNr;*/
	
}	//Function end