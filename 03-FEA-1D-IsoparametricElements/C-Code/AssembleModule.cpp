#include "MainFile.h"
#include "UserDefinedFunctions.h"
#include <iostream>

using namespace std;

void AssembleModule( const int n_node, int& n_dof, int& total_dof, int& n_pre_disp, 
  int& n_load, int& nnode_ele, int& n_elem, int Ng, int ShapeOrder, double& r, 
  const arma::colvec& elem_stiff, arma::colvec& elem_load, const arma::imat& elem_node, 
  arma::icolvec& disp_node, arma::colvec& disp_val, 
  arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
  arma::colvec& Up,  arma::colvec& Uur, arma::colvec& Pur, arma::mat& coords, 
  arma::colvec& h, arma::icolvec& force_node, arma::colvec& force_val, 
  arma::ivec& UMATid, arma::ivec& DLOADid, arma::mat& Nr, arma::mat& DNr, 
  arma::rowvec& Br, arma::vec& Jr,arma::colvec& Rr, arma::mat& X, arma::fcolvec& w){ 

  double x;
  double E;
  double b;
  b = 0;
  x = 0;
  E = 0;
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
  arma::colvec Pel;
  Pel = arma::zeros<arma::colvec>(nnode_ele);
  Pf = arma::zeros<arma::colvec>(n_dof);
  Pp = arma::zeros<arma::colvec>(fixeddofs);
  for(int iel=0; iel<n_elem; iel++){
  	Pel = arma::zeros<arma::colvec>(nnode_ele);	//Initialize Pel every loop
  	for(int j=0; j<Ng; j++){
		//Calculate x, Jr and Br:
			x = arma::dot(Nr.row(j), X.col(iel));
			Jr(j) = arma::dot(DNr.row(j), X.col(iel));
			//Give value of b:
			if(DLOADid(iel) == 1){b = DLOAD(x);}else if(DLOADid(iel) == 0){b = elem_load(iel);}
			Pel += arma::trans(Nr.row(j)) * b * Jr(j) * w(j);
	}
  	for (int i=0; i<nnode_ele; i++){
  		int i_node = elem_node(i,iel);
  		row = eq_num(i_node - 1);
  		if(row>0){
  			Pf(row-1) = Pf(row-1) + Pel(i);
  		}else{
  			Pp(-row -1) = Pp(-row-1) + Pel(i);
  		}
  			}
  	}
  	//Add external force
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
  Kel = arma::zeros<arma::mat>(nnode_ele,nnode_ele);
  
  for(int iel=0; iel<n_elem; iel++){
	Kel = arma::zeros<arma::mat>(nnode_ele,nnode_ele);	//Initialize Kel
	for(int j=0; j<Ng; j++){
		//Calculate x, Jr and Br:
			x = arma::dot(Nr.row(j), X.col(iel));
			Jr(j) = arma::dot(DNr.row(j), X.col(iel));
			Br = DNr.row(j)/Jr(j);
			//Give value of E
			if(UMATid(iel) == 1){E = UMAT(x);}else if(UMATid(iel) == 0){E = elem_stiff(iel);}
			Kel += arma::trans(Br) * Br * E * Jr(j) * w(j);
	} 
	for(int i=0; i<nnode_ele; i++){	//loop over rows
  		int i_node = elem_node(i,iel);	//element1 with nodei
  		int row =0;
  		row = eq_num(i_node-1);
  		for(int j=0; j<nnode_ele; j++){	//loop over columns
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