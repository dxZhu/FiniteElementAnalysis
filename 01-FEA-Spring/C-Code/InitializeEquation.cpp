#include "MainFile.h"
#include <iostream>

using namespace std;

void InitializeEquation( const int n_node, int& n_dof, int& total_dof, int& n_pre_disp, int& n_load, int& nnode_ele, int& n_elem, 
		       const arma::colvec& elem_stiff, const arma::imat& elem_node, arma::icolvec& disp_node, arma::colvec& disp_val, 
		  arma::imat& eq_num, arma::icolvec& force_node, arma::colvec& force_val, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::colvec& Uur,   arma::colvec& Pur )
{ 
  n_dof = 5;
  total_dof = 7;
  int fixeddofs = total_dof-n_dof;
  eq_num = arma::zeros<arma::imat>(n_node,1);
  Pf = arma::zeros<arma::colvec>(n_dof);
  Uf = arma::ones<arma::colvec>(n_dof);
  Pp = arma::zeros<arma::colvec>(fixeddofs);
  Up = arma::zeros<arma::colvec>(fixeddofs);
  Kff = arma::ones<arma::mat>(n_dof,n_dof);
  Kfp = arma::ones<arma::mat>(n_dof,fixeddofs);
  Kpf = arma::zeros<arma::mat>(fixeddofs,n_dof);	//2x5
  Kpp = arma::zeros<arma::mat>(fixeddofs,fixeddofs);
  //Initialize Equation
  eq_num = arma::zeros<arma::imat>(n_node,1);
  for(int i=0; i < n_pre_disp; i++){
  	int node=0;
  	node = disp_node(i);
  	eq_num(node-1) = -(i+1);
  }
  
  int row = 0;
  for(int i=0; i < n_node; i++){
  	if(eq_num(i)==0){
  	row++;
  	eq_num(i) = row;
  	}
  }

  n_dof = n_node-n_pre_disp;
  total_dof = 7;
  }