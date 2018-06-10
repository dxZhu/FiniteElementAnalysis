#include "MainFile.h"

// ME 471 / AE 420
// Programming Assignment #0: Learning to submit programming assignments
// Prof. Mariana Silva
using namespace std;

/* Write your main code here */

int main()
{

  int nnode_ele = 2; //nnode_ele: number of nodes per element
  int dof_node = 1; //dof_node: number of degree of freedom per node
  int edof = nnode_ele*dof_node; //edof: number of degree of freedom per element
  int n_dof;
  int total_dof;

  int n_node;
  int n_elem;
  int n_load;
  int n_pre_disp;

  arma::imat elem_node;
  arma::colvec elem_stiff;
  arma::icolvec force_node;
  arma::colvec force_val;
  arma::icolvec disp_node;
  arma::colvec disp_val;

  arma::imat eq_num;
  arma::colvec Pf;
  arma::colvec Pp;
  arma::colvec Uf;
  arma::colvec Up;
  arma::colvec Uur;
  arma::colvec Pur;
  arma::mat Kff;
  arma::mat Kfp;
  arma::mat Kpf;
  arma::mat Kpp;

  // =========================================================
  // DO NOT MODIFY THE LINE BELOW!!
  //Autograding script will search for this variable definition
  string filename = "input.dat";
  // =========================================================

  /*=========================================================;
  %                 Read data from input files               ;
  %=========================================================*/
  ReadInput(filename, n_node, n_elem, n_load, n_pre_disp, nnode_ele,
	    elem_node, elem_stiff, force_node, force_val,
	    disp_node, disp_val);



 /*==========================================================;
 %            "Random" calculations used as an example       ;
 %===========================================================*/
  ExampleFunctions(n_node, n_dof, total_dof, n_pre_disp, n_load, nnode_ele, n_elem,
  elem_stiff, elem_node, disp_node, disp_val, eq_num, 
  force_node, force_val, Kff,  Kpp,  Kpf,  Kfp, Pf, Pp , Uf ,Up, Uur, Pur);

 /*=========================================================;
  %                 Write Output Files                      ;
  %=========================================================*/
  PrintOutput( n_dof, total_dof,  eq_num, Kff,  Kpp,  Kpf,  Kfp, Uf , Up, Pp, Pf, Uur, Pur);

  return(0);
}
