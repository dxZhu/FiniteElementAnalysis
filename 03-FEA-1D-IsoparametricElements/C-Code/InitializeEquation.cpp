#include "MainFile.h"
#include <iostream>

using namespace std;

void InitializeEquation( const int n_node, int& dof_node, int& n_dof, int& total_dof, int& n_pre_disp, int& n_load, int& nnode_ele, int& n_elem, 
		       const arma::colvec& elem_stiff, arma::colvec& elem_load, const arma::imat& elem_node, arma::icolvec& disp_node, arma::colvec& disp_val, 
		  arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::colvec& Uur,  arma::colvec& Pur, arma::mat coords, arma::colvec& h, arma::icolvec& force_node, arma::colvec& force_val)
{ 
  total_dof = n_node * dof_node; //6
  n_dof = total_dof - n_pre_disp; //5
  int fixeddofs = total_dof-n_dof; //1
  eq_num = arma::zeros<arma::imat>(n_node, 1);
  Pf = arma::zeros<arma::colvec>(n_dof);
  Uf = arma::ones<arma::colvec>(n_dof);
  Pp = arma::zeros<arma::colvec>(fixeddofs);
  Up = arma::zeros<arma::colvec>(fixeddofs);
  Kff = arma::ones<arma::mat>(n_dof,n_dof);
  Kfp = arma::ones<arma::mat>(n_dof,fixeddofs);
  Kpf = arma::zeros<arma::mat>(fixeddofs,n_dof);	//2x5
  Kpp = arma::zeros<arma::mat>(fixeddofs,fixeddofs);
  h = arma::zeros<arma::colvec>(n_elem);
  
  //Initialize Equation
   for(int i=0; i<n_pre_disp; i++){
  	int node=0;
  	node = disp_node(i);
  	eq_num(node-1, 0) = -(i+1);
  }
 
  int row = 0;
  for(int i=0; i < n_node; i++){
  	if(eq_num(i,0)==0){
  	row++;
  	eq_num(i,0) = row;
  	}
  }
  
  for(int i=0; i < n_elem; i++){
  	h(i) = coords(i+1,0) - coords(i,0);
  }

 
  }