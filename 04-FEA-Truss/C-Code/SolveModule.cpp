#include "MainFile.h"
#include <iostream>

using namespace std;

void SolveModule( const int n_node, int n_pre_disp, int dof_node,
		  arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::mat& Uur,   arma::mat& Pur, arma::colvec& R)
{
  int row = 0;
  int col = 0;
//Define the reaction force
  R = arma::zeros<arma::colvec>(n_pre_disp);
//Solve Uf
  Uf = arma::solve(Kff, (Pf - Kfp * Up));

  //Solve R
  R = -Pp + Kpp * Up + Kpf * Uf; 
  //Solve Uur, Pur  
  Uur = arma::zeros<arma::mat>(n_node, dof_node);
  Pur = arma::zeros<arma::mat>(n_node, dof_node);
  for(int i=0; i< n_node; i++){
    for(int j=0; j<dof_node; j++){
    row = eq_num(i,j);
    if(row>0){//free node
    Uur(i, j) = Uf(row-1);
    Pur(i, j) = Pf(row-1);}else{//prescribed node
    Uur(i, j) = Up(-row-1);
    Pur(i, j)=R(-row-1);}
    }
  }
  
}