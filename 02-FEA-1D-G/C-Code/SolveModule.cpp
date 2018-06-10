#include "MainFile.h"
#include <iostream>

using namespace std;

void SolveModule( const int n_node, 
		  arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::colvec& Uur,   arma::colvec& Pur, arma::icolvec& force_node, arma::colvec& force_val)
{
  int row = 0;
//Solve Uf
  Uf = arma::solve(Kff, (Pf - Kfp * Up));

  //Solve Pp
  Pp = -Pp + Kpp * Up + Kpf * Uf;
  
  //Solve Uur, Pur  
  Uur = arma::ones<arma::colvec>(n_node);
  Pur = arma::zeros<arma::colvec>(n_node);
  for(int i=0; i< n_node; i++){
    row = eq_num(i);
    if(row>0){//free node
    Uur(i) = Uf(row-1);
    Pur(i) = Pf(row-1);}else{//prescribed node
  Uur(i) = Up(-row-1);
  Pur(i)=Pp(-row-1);}
	}

  
}