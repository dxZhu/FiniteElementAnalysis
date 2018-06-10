#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// INCLUDE ARMADILLO LIBRARY DEFINITIONS
#include <armadillo>
#include <iostream>
#include <iomanip>


void ReadInput(const std::string& filename, const int ndim, int& n_node, int& n_elem, int& n_load, int& n_pre_disp,
	       int& nnode_ele, int& dof_node, int& edof, 
	       arma::mat& coords, arma::imat& elem_node, arma::mat& elem_stiff, 
	       arma::mat& elem_load, arma::mat& elem_area, arma::imat& force_node, arma::colvec& force_val, 
	       arma::imat& disp_node, arma::colvec& disp_val);

void InitializeEquation( const int n_node, int dof_node, int& n_dof, int& total_dof, int n_pre_disp, int n_load, int nnode_ele, int n_elem, int ndim, 
		        const arma::imat& elem_node, arma::imat disp_node,
		  arma::imat& eq_num, arma::mat coords, arma::colvec& le);
		  
void AssembleModule( const int n_node, int n_dof, int total_dof, int n_pre_disp, 
  int n_load, int nnode_ele, int n_elem, int ndim, int dof_node,
  const arma::mat elem_stiff, arma::mat elem_load, const arma::imat elem_node, arma::mat elem_area,
  arma::imat disp_node, arma::colvec disp_val, arma::imat force_node, arma::colvec force_val, 
  arma::imat eq_num, arma::mat coords, arma::colvec le,
  arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, arma::mat& Kfp, 
  arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf, arma::colvec& Up);
  
void SolveModule( const int n_node, int n_pre_disp, int dof_node,
		  arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::mat& Uur,   arma::mat& Pur, arma::colvec& R);

void StressStrain( const int n_node, int n_elem, int dof_node, int nnode_ele,
		  arma::mat  elem_stiff, arma::mat elem_load, arma::mat Uur, arma::mat coords, arma::colvec le, arma::imat elem_node,
		  arma::mat& stress, arma::mat& strain);
		  
		  

void PrintEQNUM(const arma::imat& eq_num);

void PrintMatrices(const int& n_dof, const int& total_dof, arma::mat& Kff,
    arma::mat& Kpp, arma::mat& Kpf,  arma::mat& Kfp);

void PrintSolution(arma::colvec& Uf, arma::colvec& Pp,  arma::mat& Uur,   arma::mat& Pur);

void PrintStressStrain(arma::mat& strain, arma::mat& stress);