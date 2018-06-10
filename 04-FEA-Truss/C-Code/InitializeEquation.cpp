#include "MainFile.h"
#include <iostream>

using namespace std;

void InitializeEquation( const int n_node, int dof_node, int& n_dof, int& total_dof, int n_pre_disp, int n_load, int nnode_ele, int n_elem, int ndim, 
		        const arma::imat& elem_node, arma::imat disp_node,
		  arma::imat& eq_num, arma::mat coords, arma::colvec& le)
{ 
  
  total_dof = n_node * dof_node; 
  n_dof = total_dof - n_pre_disp; 
  eq_num = arma::zeros<arma::imat>(n_node, ndim);
  /*Pf = arma::zeros<arma::colvec>(n_dof);
  Uf = arma::ones<arma::colvec>(n_dof);
  Pp = arma::zeros<arma::colvec>(fixeddofs);
  Up = arma::zeros<arma::colvec>(fixeddofs);
  Kff = arma::ones<arma::mat>(n_dof,n_dof);
  Kfp = arma::ones<arma::mat>(n_dof,fixeddofs);
  Kpf = arma::zeros<arma::mat>(fixeddofs,n_dof);	//2x5
  Kpp = arma::zeros<arma::mat>(fixeddofs,fixeddofs);*/
  le = arma::zeros<arma::colvec>(n_elem);
  
  //Initialize Equation
   for(int i=0; i<n_pre_disp; i++){
  	int node = 0;
  	int dim = 0;
  	node = disp_node(i,0);
  	dim = disp_node(i,1);
  	eq_num(node-1, dim-1) = -(i+1);
  }
 
  int row = 0;
  for(int i=0; i < n_node; i++){
  	for(int j=0; j<dof_node; j++){
  	  if(eq_num(i,j)==0){
  	  row++;
  	  eq_num(i,j) = row;
  	}
  	}
  }
  
  //length of each element
  for(int i=0; i < n_elem; i++){
  	int nodea = 0;
  	int nodeb = 0;
  	nodea = elem_node(0, i);
  	nodeb = elem_node(1, i);
  	le(i) = sqrt((coords(nodea-1,0)-coords(nodeb-1,0)) * (coords(nodea-1,0)-coords(nodeb-1,0)) + (coords(nodea-1,1)-coords(nodeb-1,1)) * (coords(nodea-1,1)-coords(nodeb-1,1)));
  }

 
  }