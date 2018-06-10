#include "MainFile.h"
#include <iostream>

using namespace std;

void InitializeEquation(const int& n_node, const int& n_pre_disp, 
			const int dof_node, const arma::imat& disp_node, 
			arma::imat& eq_num, int& n_dof, int& total_dof )
{ 
  
  total_dof = n_node * dof_node; //18
  n_dof = total_dof - n_pre_disp; //18 - 6 = 12
  eq_num = arma::zeros<arma::imat>(n_node, dof_node);
  
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
 
  }