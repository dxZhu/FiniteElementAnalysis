#include "MainFile.h"
#include <iostream>

using namespace std;

void SolveModule( const int n_node, const int n_dof, const int total_dof,const int dof_node,
		  const arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp,  arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::mat& Uur,   arma::mat& Pur )
{
  int row = 0;
  int col = 0;
  int fixeddofs = total_dof - n_dof;
  arma::colvec R;
  
  R = arma::zeros<arma::colvec>(fixeddofs);
  Uf = arma::zeros<arma::colvec>(n_dof);
//Solve Uf
  Uf = arma::solve(Kff, (Pf - Kfp * Up));

  //Solve R
  R = -Pp + Kpp * Up + Kpf * Uf; 
  //Solve Uur, Pur  
  Uur = arma::zeros<arma::mat>(n_node, dof_node);
  Pur = arma::zeros<arma::mat>(n_node, dof_node);
  for(int i=0; i< n_node; i++){
    for(int j=0; j< dof_node; j++){
    row = eq_num(i,j);
    if(row>0){//free node
    Uur(i, j) = Uf(row-1);
    Pur(i, j) = Pf(row-1);}else{//prescribed node
    Uur(i, j) = Up(-row-1);
    Pur(i, j)=R(-row-1);}
    }
  }



}