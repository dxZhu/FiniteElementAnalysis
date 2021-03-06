#include "MainFile.h"
#include <iostream>

using namespace std;

void ExampleFunctions( const int n_node, int& n_dof, int& total_dof, int& n_pre_disp, int& n_load, int& nnode_ele, int& n_elem, 
		       const arma::colvec& elem_stiff, const arma::imat& elem_node, arma::icolvec& disp_node, arma::colvec& disp_val, 
		  arma::imat& eq_num, arma::icolvec& force_node, arma::colvec& force_val, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::colvec& Uur,   arma::colvec& Pur )
{ 

  //Initialize Equation
  eq_num = arma::zeros<arma::imat>(n_node,1);
  for(int i=0; i < n_pre_disp; i++){
  	int node=0;
  	node=disp_node(i);
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
  int fixeddofs = total_dof-n_dof;
  //Assemble Mudule:
  //Set Up
  Up = arma::zeros<arma::colvec>(fixeddofs);
  for(int i=0; i<n_pre_disp; i++){
  	int node = 0;
  	double u = disp_val(i);
  	node = disp_node(i);
  	row = -eq_num(node-1);
  	Up(row-1) = u;
  }
  
  //Set Pf
  Pf = arma::zeros<arma::colvec>(n_dof);
  for(int i=0; i<n_load; i++){
  	int node = 0;
  	node = force_node(i);	//node_th has the force of f:
  	int f = force_val(i);
  	row = eq_num(node-1);	// check which node's external force is known.
  	if(row>0){
  		Pf(row-1) = Pf(row-1) + f;
  	}
  }
  
  //set KEL
  
    
  Uf = arma::ones<arma::colvec>(n_dof);
  Pp = arma::zeros<arma::colvec>(fixeddofs);
  
  //Assemble stiffness
  Kff = arma::zeros<arma::mat>(n_dof,n_dof);
  Kfp = arma::zeros<arma::mat>(n_dof,fixeddofs);
  Kpf = arma::zeros<arma::mat>(fixeddofs,n_dof);	//2x5
  Kpp = arma::zeros<arma::mat>(fixeddofs,fixeddofs);
  arma::mat Kel;
  Kel = arma::ones<arma::mat>(2,2);
  
  for(int iel=0; iel<n_elem; iel++){
  	int k;
  	k = elem_stiff(iel);	//ith elem stiffness 
  	Kel << k << -k << arma::endr
  		<< -k << k << arma::endr;
	for(int i=0; i<2; i++){	//loop over rows
  		int i_node = elem_node(i,iel);	//element1 with nodei
  		int row =0;
  		row = eq_num(i_node-1);
  		for(int j=0; j<2; j++){	//loop over columns
  			int j_node = elem_node(j,iel);	//element1 with nodej
  			int col = eq_num(j_node-1);
  			if(row>0){//free row
  				if(col>0){//free col
  				Kff(row-1,col-1) = Kff(row-1,col-1) + Kel(i,j);
  				}else{//restricted col
  				Kfp(row-1,-col-1) = Kfp(row-1,-col-1) + Kel(i,j);
  				}
  			}
  			else{//restricted node
  				if(col>0){//free col
  				Kpf(-row-1, col-1) = Kpf(-row-1, col-1) + Kel(i,j);
  				}else{//restricted col
  				Kpp(-row-1, -col-1) = Kpp(-row-1, -col-1) + Kel(i,j);
  				}
  			}
  			
  		}
  	}	
	
  }

  //Solve Uf
  Uf = arma::solve(Kff, (Pf - Kfp * Up));

  //Solve Pp
  Pp = Kpp * Up + Kpf * Uf;
  
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
