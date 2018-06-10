#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// INCLUDE ARMADILLO LIBRARY DEFINITIONS
#include <armadillo>
#include <iostream>
#include <iomanip>

void ReadInput(const std::string& filename, int& n_node, int& n_elem, int& n_load, int& n_pre_disp,
	       const int nnode_ele, arma::imat& elem_node, arma::colvec& elem_stiff,
	       arma::icolvec& disp_node, arma::colvec& disp_val, arma::colvec& coords, arma::colvec& elem_load, arma::icolvec& force_node, arma::colvec& force_val);

void InitializeEquation( const int n_node, int& dof_node, int& n_dof, int& total_dof, int& n_pre_disp, int& n_load, int& nnode_ele, int& n_elem, 
		       const arma::colvec& elem_stiff, arma::colvec& elem_load, const arma::imat& elem_node, arma::icolvec& disp_node, arma::colvec& disp_val, 
		  arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::colvec& Uur,  arma::colvec& Pur, arma::colvec& coords, arma::colvec& h, arma::icolvec& force_node, arma::colvec& force_val);
		  
void AssembleModule( const int n_node, int& n_dof, int& total_dof, int& n_pre_disp, int& n_load, int& nnode_ele, int& n_elem, 
		       const arma::colvec& elem_stiff, arma::colvec& elem_load, const arma::imat& elem_node, arma::icolvec& disp_node, arma::colvec& disp_val, 
		  arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::colvec& Uur, arma::colvec& Pur, arma::colvec& coords, arma::colvec& h, arma::icolvec& force_node, arma::colvec& force_val);

void PrintEQNUM(const arma::imat& eq_num);

void PrintMatrices(const int& n_dof, const int& total_dof, arma::mat& Kff,
    		arma::mat& Kpp, arma::mat& Kpf,  arma::mat& Kfp);

void SolveModule( const int n_node, 
		  arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::colvec& Uur,   arma::colvec& Pur, arma::icolvec& force_node, arma::colvec& force_val);
		  
void PrintSolution(arma::colvec& Uf, arma::colvec& Pp,  arma::colvec& Uur,   arma::colvec& Pur);
