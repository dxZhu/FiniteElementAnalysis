#include "MainFile.h"
#include <iostream>

using namespace std;

void AssembleModule( const int n_node, int& n_dof, int& total_dof, int& n_pre_disp, int& n_load, int& nnode_ele, int& n_elem, 
		       const arma::colvec& elem_stiff, arma::colvec& elem_load, const arma::imat& elem_node, arma::icolvec& disp_node, arma::colvec& disp_val, 
		  arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::colvec& Uur, arma::colvec& Pur, arma::colvec& coords, arma::colvec& h, arma::icolvec& force_node, arma::colvec& force_val)
{ 

//Assemble Module:
  //Set Up
  int row = 0;
  int fixeddofs = total_dof-n_dof; //1
  Up = arma::zeros<arma::colvec>(fixeddofs);
  for(int i=0; i<n_pre_disp; i++){
  	int node = 0;
  	double u = disp_val(i);
  	node = disp_node(i);
  	row = -eq_num(node-1);
  	Up(row-1) = u;
  }
  
  //Set Pel, Pf and Pp
  double p1;
  double p2;
  arma::colvec Pel;
  Pel = arma::zeros<arma::colvec>(2);
  Pf = arma::zeros<arma::colvec>(n_dof);
  Pp = arma::zeros<arma::colvec>(fixeddofs);
  for(int iel=0; iel<n_elem; iel++){
  	p1 = elem_load(iel)/h(iel) * (coords(iel+1) * h(iel) - 0.5 * (coords(iel+1) * coords(iel+1)) + 0.5 * (coords(iel) * coords(iel)));
  	p2 = elem_load(iel)/h(iel) * (0.5 * (coords(iel+1) * coords(iel+1)) - (0.5 * coords(iel) * coords(iel)) - coords(iel) * h(iel));
  	Pel << p1 << arma::endr
  		<< p2 << arma::endr;
  	for (int i=0; i<2; i++){
  		int i_node = elem_node(i,iel);
  		row = eq_num(i_node - 1);
  		if(row>0){
  			Pf(row-1) = Pf(row-1) + Pel(i);
  		}else{
  			Pp(-row -1) = Pp(-row-1) + Pel(i);
  		}
  			}
  	}
  	for(int i=0; i<n_load; i++){
  		int node = force_node(i);
  		int p = force_val(i);
  		row = eq_num(node-1);
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
  Kel = arma::ones<arma::mat>(2,2);
  
  for(int iel=0; iel<n_elem; iel++){
  	double k;
  	k = elem_stiff(iel) / h(iel);	//ith elem stiffness 
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
  
  }