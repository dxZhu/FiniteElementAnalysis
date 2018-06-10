#include "MainFile.h"
#include <iostream>

using namespace std;

void AssembleModule( const int n_node, int n_dof, int total_dof, int n_pre_disp, 
  int n_load, int nnode_ele, int n_elem, int ndim, int dof_node,
  const arma::mat elem_stiff, arma::mat elem_load, const arma::imat elem_node, arma::mat elem_area,
  arma::imat disp_node, arma::colvec disp_val, arma::imat force_node, arma::colvec force_val, 
  arma::imat eq_num, arma::mat coords, arma::colvec le,
  arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, arma::mat& Kfp, 
  arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf, arma::colvec& Up){ 

//Assemble Module:
  //Set Up
  int row = 0;
  int fixeddofs = total_dof-n_dof; //1
  Up = arma::zeros<arma::colvec>(fixeddofs);
  for(int i=0; i<n_pre_disp; i++){
  	int nodei = 0;
  	int dim = 0;
  	nodei = disp_node(i,0);
  	dim = disp_node(i,1);
  	row = eq_num(nodei-1, dim-1);
  	Up(-row-1) = disp_val(i);
  }

  //Set Pel, Pf and Pp
  arma::colvec Pel;
  arma::colvec Pg;
  arma::colvec Pt;
  arma::colvec node;
  double gamma;	//gamma = rou * g
  double alpha;	//coef of temperature
  double c;	//cso(theta)
  double s;	//sin(theta)
  int nodea = 0;
  int nodeb = 0;
  Pel = arma::zeros<arma::colvec>(nnode_ele * dof_node);
  Pg = arma::zeros<arma::colvec>(nnode_ele * dof_node);
  Pt = arma::zeros<arma::colvec>(nnode_ele * dof_node);
  Pf = arma::zeros<arma::colvec>(n_dof);
  Pp = arma::zeros<arma::colvec>(fixeddofs);
  node = arma::zeros<arma::colvec>(nnode_ele);
  for(int iel=0; iel<n_elem; iel++){
  	Pel = arma::zeros<arma::colvec>(nnode_ele * dof_node);	//Initialize Pel every loop
  	node(0) = elem_node(0, iel);
  	node(1) = elem_node(1, iel);
  	c = (coords(node(1)-1,0)-coords(node(0)-1,0))/le(iel);
  	s = (coords(node(1)-1,1)-coords(node(0)-1,1))/le(iel);
  	//Add temperature force
  	Pt << -c << arma::endr
  		<< -s << arma::endr
  		<< c << arma::endr
  		<< s << arma::endr;
  	alpha = elem_stiff(iel,0) * elem_area(iel,0) * elem_stiff(iel,1) * elem_load(iel,1);
  	Pt = alpha * Pt;
  	//Add gravity force
  	Pg << 0 << arma::endr
  		<< 1 << arma::endr
  		<< 0 << arma::endr
  		<< 1 << arma::endr;
  	gamma = -elem_load(iel,0)/2 * elem_area(iel,0) * le(iel);
  	Pg = gamma * Pg;
  	Pel = Pt + Pg;
  	for(int i=0; i<nnode_ele; i++){
  	  for(int j=0; j<dof_node; j++){	
  		row = eq_num(node(i)-1, j);
  		if(row>0){
  			Pf(row-1) = Pf(row-1) + Pel(2*i+j);
  		}else{
  			Pp(-row -1) = Pp(-row-1) + Pel(2*i+j);}
  			}
  		}
  	}

  	//Add external force
  	for(int i=0; i<n_load; i++){
  		int nodei= force_node(i, 0);
  		int dim = force_node(i, 1);
  		int p = force_val(i);
  		row = eq_num(nodei-1, dim-1);
  		if(row>0){
  			Pf(row-1) = Pf(row-1) + p;
  		}else{
  			Pp(-row -1) = Pp(-row-1) + p;
  		}
  	}
 
  //set KEL  
  //Assemble stiffness
  Kff = arma::zeros<arma::mat>(n_dof,n_dof);
  Kfp = arma::zeros<arma::mat>(n_dof,fixeddofs);
  Kpf = arma::zeros<arma::mat>(fixeddofs,n_dof);	//2x5
  Kpp = arma::zeros<arma::mat>(fixeddofs,fixeddofs);
  arma::mat Kel;
  arma::mat T;
  arma::mat T1;
  arma::mat Tel;
  arma::mat Uel;
  Kel = arma::zeros<arma::mat>(nnode_ele * dof_node,nnode_ele * dof_node);
  T = arma::zeros<arma::mat>(nnode_ele * dof_node, nnode_ele);
  T1 = arma::zeros<arma::mat>(nnode_ele * dof_node, nnode_ele);
  Tel = arma::zeros<arma::mat>(nnode_ele * dof_node, nnode_ele * dof_node);
  Uel = arma::zeros<arma::mat>(nnode_ele, nnode_ele);
  Uel << 1 << -1 << arma::endr
  	<< -1 << 1 << arma::endr;
  double stiff;
  for(int iel=0; iel<n_elem; iel++){
	  Kel = arma::zeros<arma::mat>(nnode_ele * dof_node,nnode_ele * dof_node);
	  T = arma::zeros<arma::mat>(nnode_ele * dof_node, nnode_ele);	//Initialize Kel, T
	  node(0) = elem_node(0, iel);
  	  node(1) = elem_node(1, iel);
	  c = (coords(node(1)-1,0)-coords(node(0)-1,0))/le(iel);
	  s = (coords(node(1)-1,1)-coords(node(0)-1,1))/le(iel);
	  T << c << 0 << arma::endr
	  	<< s << 0 << arma::endr
	  	<< 0 << c << arma::endr
	  	<< 0 << s << arma::endr;
	  T1 = T * Uel;
	  Tel = T1 * arma::trans(T);
	  stiff = elem_stiff(iel, 0) * elem_area(iel) / le(iel);
	  Kel = stiff * Tel;
	for(int i=0; i<nnode_ele; i++){	//loop over rows
  	  int row =0;
  	  int inode = elem_node(i,iel);
  	  for(int k=0; k<dof_node; k++){
  		row = eq_num(inode-1, k);
  		for(int j=0; j<nnode_ele; j++){	//loop over columns
  			int col = 0;
  			int jnode = elem_node(j,iel);
  			for(int l=0; l<dof_node; l++){
  			  int col = eq_num(jnode-1, l);
  			  int p = 2 * i + k;
  			  int q = 2 * j + l;
  					if(row>0){//free row
  						if(col>0){//free col
  						Kff(row-1,col-1) = Kff(row-1,col-1) + Kel(p,q);
  						}else{//restricted col
  						Kfp(row-1,-col-1) = Kfp(row-1,-col-1) + Kel(p,q);}
  					}else{//restricted node
  						if(col>0){//free col
  						Kpf(-row-1, col-1) = Kpf(-row-1, col-1) + Kel(p,q);
  						}else{//restricted col
  						Kpp(-row-1, -col-1) = Kpp(-row-1, -col-1) + Kel(p,q);}
  						}
  				}
  			}
  			
  		}
  	}
	
  }

}