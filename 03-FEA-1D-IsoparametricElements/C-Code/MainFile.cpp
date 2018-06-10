#include "MainFile.h"

using namespace std;

// ME 471 / AE 420
// Programming Assignment #3: 1D elastostatic FE code
// includes:
// - isoparametric linear and quadratic elements
// - numerical integration using Ng = 1,2,3,4 gauss points
// - DLOAD function for user-defined body load b(x)
// - UMAT function for user-defined elasticity modulus E(x)

/* Write your main code here */

int main()
{

  int nnode_ele; //nnode_ele: number of nodes per element
  int dof_node;  //dof_node: number of degree of freedom per node
  int edof;      //edof: number of degree of freedom per element
  int n_dof;     //number of free degrees of freedom
  int total_dof; //total number of degrees of freedom
  int mdim = 1;  // problem dimension (1D rod => mdim = 1)
  int Ng;        //number of integration (Gauss) points (Ng = 1,2,3,4)
  int ShapeOrder; //element order (1:linear, 2:quadratic or 3:cubic)
  double r;

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
  arma::mat coords;
  arma::colvec elem_load;
  arma::colvec h;
  arma::colvec R; 
    
  arma::ivec UMATid;
  arma::ivec DLOADid;
  arma::mat Nr;
  arma::mat DNr;
  arma::rowvec Br;
  arma::vec Jr;
  arma::colvec Rr;	//Integration point for different Ng
  arma::mat X;	//coords at different integration point
  arma::fcolvec w;	//Weight Factor
  
  // =========================================================
  // DO NOT MODIFY THE LINE BELOW!!
  //Autograding script will search for this variable definition
  string filename = "input_3.1.dat";

  ReadInput(filename, mdim, n_node, n_elem, n_load, n_pre_disp,
	       nnode_ele, dof_node, edof, Ng, ShapeOrder, coords, elem_node,
	       elem_stiff, elem_load, UMATid, DLOADid,
	       force_node, force_val, disp_node, disp_val);
	       
	     
  // =========================================================

  /*=========================================================;
  %                 Complete your FEA code                   ;
  %=========================================================*/
 /*==========================================================;
 %                 Creating Global Id matrix                 ;
 %===========================================================*/
 //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//


InitializeEquation(n_node, dof_node, n_dof, total_dof, n_pre_disp, n_load, nnode_ele, n_elem, 
		       elem_stiff, elem_load, elem_node, disp_node, disp_val, eq_num, Kff, Kpp, Kpf, 
		       Kfp, Pf, Pp, Uf, Up,  Uur, Pur, coords, h, force_node, force_val);

GlobalIdMatrix(n_node, n_elem, n_load, n_pre_disp,
  nnode_ele, Ng, ShapeOrder, r, 
  UMATid, DLOADid, Nr, DNr, elem_node, coords, Br, Jr, Rr, X, w);

  
  //*=========================================================;
  // Write EQNUM output
  // DO NOT MODIFY THE LINE BELOW!!
  PrintEQNUM(eq_num);
  //=========================================================*/

 /*==========================================================;
 %                 Assemble Module                            ;
 %===========================================================*/
 //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//
  AssembleModule(n_node, n_dof, total_dof, n_pre_disp, n_load, nnode_ele, n_elem, Ng, ShapeOrder, r, 
  elem_stiff, elem_load, elem_node, disp_node, disp_val, eq_num, Kff, Kpp, Kpf, 
  Kfp, Pf, Pp, Uf, Up, Uur, Pur, coords, h, force_node, force_val, UMATid, DLOADid, Nr, DNr, 
  Br, Jr, Rr, X, w);







  //*=========================================================;
  // Write Matrices output
  // DO NOT MODIFY THE LINE BELOW!!
  PrintMatrices(n_dof, total_dof, Kff, Kpp, Kpf, Kfp);
  // =========================================================*


 /*==========================================================;
 %                 Solve (Analysis)                          ;
 %===========================================================*/
 //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//

SolveModule(n_node, n_pre_disp,
		  eq_num, Kff, Kpp, Kpf, Kfp, Pf, Pp, Uf, Up, Uur, Pur, R, force_node, force_val);





  //*=========================================================;
  // Write Solution Output Files
  // DO NOT MODIFY THE LINE BELOW!!
  PrintSolution(Uf, Pp, Uur, Pur);
  // =========================================================*


  return(0);
}
