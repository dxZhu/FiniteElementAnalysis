#include "MainFile.h"
#include <iostream>

using namespace std;

void AssembleModule( const int edof, const int n_dof, const int total_dof, const int ndim, const int dof_node,
		     const int n_elem,const int n_load, const int n_pre_disp, const int nnode_ele, const arma::mat& coords,
		     const arma::imat& elem_node,const arma::mat& elem_stiff, const arma::mat& elem_load,
		     const arma::mat& elem_area, const arma::imat& force_node,
		     const arma::colvec& force_val, const arma::imat& disp_node,const arma::colvec& disp_val,
		     const int& n_trac, const arma::imat& trac_ele, const arma::mat& trac_val,
		     const int& Ng, const int& ShapeOrder, const int& Model2D,
		     const arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, arma::mat& Kfp,
		     arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   arma::colvec& Up ){ 

  arma::mat kel;
  arma::colvec pel;
  int fixeddofs = total_dof - n_dof; // 18 - 12 = 6
  Pf = arma::zeros<arma::colvec>(n_dof);
  Up = arma::zeros<arma::colvec>(fixeddofs);
  Uf = arma::zeros<arma::colvec>(n_dof);
  Pp = arma::zeros<arma::colvec>(fixeddofs);
  Kff = arma::zeros<arma::mat>(n_dof,n_dof);
  Kfp = arma::zeros<arma::mat>(n_dof,fixeddofs);
  Kpf = arma::zeros<arma::mat>(fixeddofs,n_dof);	
  Kpp = arma::zeros<arma::mat>(fixeddofs,fixeddofs);
//Assemble Module:
  //Boundary Condition:
  AssemblePrescribedDisplacement( n_pre_disp, disp_node, 
				    disp_val, eq_num, Up );

  //Apply concentrated forces:
  AssembleGlobalForceVector( n_load, force_node, 
				force_val, eq_num, Pf ); 
				cout << "for concentrated force " << Pf  << endl;

  //Prescribed Boundary Flux
  AssemblePrescribedTraction( edof, nnode_ele, dof_node, Ng, ShapeOrder, ndim, 
  				coords, elem_node, elem_stiff, elem_load, elem_area,
				n_trac, trac_ele, trac_val,
				eq_num, Kff, Kpp, Kpf, Kfp, Pf, Pp);

  //Global stiffness matrix
  for(int i_elem=0; i_elem<n_elem; i_elem++)
  {
  	int iel = i_elem + 1;
  //Get Element Node Vector and Stiffness Matrix:
  	kel = arma::zeros<arma::mat>(edof,edof);
    pel = arma::zeros<arma::colvec>(edof);
  	ElementAssemble(edof, iel,  nnode_ele, Ng, ShapeOrder, ndim, Model2D,
  				coords, elem_node, elem_stiff, elem_load, elem_area,
				kel, pel);

  //Get Pp,Pf,Kpp,Kpf,Kfp,Kff, related to stiffness matrix:
  	AssembleGlobalStiffness(iel, nnode_ele, dof_node,
				elem_node, kel, pel, eq_num, 
				Kff, Kpp, Kpf, Kfp, Pf, Pp);
  
  }
cout << "Finishi Global Stiffness Matrix" << endl;

}