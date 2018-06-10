using namespace std;
#include <MainFile.h>

// ME 471 / AE 420
// Programming Assignment #2: 1D elastostatic FE code

/* Write your main code here */

int main()
{

  int nnode_ele = 2; //nnode_ele: number of nodes per element
  int dof_node = 1; //dof_node: number of degree of freedom per node
  int edof = nnode_ele * dof_node; //edof: number of degree of freedom per element
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
  arma::colvec coords;
  arma::colvec elem_load;
  arma::colvec h;
  arma::colvec elem_area;
  
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
  %                 Complete your FEA code                   ;
  %=========================================================*/

  /*=========================================================;
  %                 Read data from input files               ;
  %=========================================================*/
  //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//

  ReadInput(filename, n_node, n_elem, n_load, n_pre_disp, nnode_ele, elem_node, elem_stiff,
	        disp_node, disp_val, coords, elem_load, elem_area, force_node, force_val);


 /*==========================================================;
 %                 Creating Global Id matrix                 ;
 %===========================================================*/
 //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//


  InitializeEquation(n_node, dof_node, n_dof, total_dof, n_pre_disp, n_load, nnode_ele, n_elem, 
		       elem_stiff, elem_load, elem_node, disp_node, disp_val, eq_num, Kff, Kpp, Kpf, 
		       Kfp, Pf, Pp, Uf, Up,  Uur, Pur, coords, h, force_node, force_val);

  //*=========================================================;
  // Write EQNUM output                       
  // DO NOT MODIFY THE LINE BELOW!!               
  PrintEQNUM(eq_num);
  //=========================================================*/

 /*==========================================================;
 %                 Assemble Module                            ;
 %===========================================================*/
 //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//

  AssembleModule( n_node, n_dof, total_dof, n_pre_disp, n_load, nnode_ele, n_elem, 
		       elem_stiff, elem_load, elem_node, disp_node, disp_val, eq_num, Kff, Kpp, Kpf, 
		  		Kfp, Pf,  Pp, Uf, Up, Uur, Pur, coords, h, force_node, force_val, elem_area);


  //*=========================================================;
  // Write Matrices output
  // DO NOT MODIFY THE LINE BELOW!!
  PrintMatrices(n_dof, total_dof, Kff, Kpp, Kpf, Kfp);
  // =========================================================*


 /*==========================================================;
 %                 Solve (Analysis)                          ;
 %===========================================================*/
 //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//
  SolveModule( n_node, 
		  eq_num, Kff, Kpp, Kpf, Kfp, Pf,  Pp, Uf, Up, Uur, Pur, force_node, force_val);






  //*=========================================================;
  // Write Solution Output Files
  // DO NOT MODIFY THE LINE BELOW!!
  PrintSolution(Uf, Pp, Uur, Pur);
  // =========================================================* 

  return(0);
}



