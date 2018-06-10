using namespace std;
#include <MainFile.h>

// ME 471 / AE 420
// Programming Assignment #5: 2D Heat Transfer
// Prof. Mariana Silva

/* Write your main code here */

int main()
{

  int nnode_ele; //nnode_ele: number of nodes per element
  int dof_node;  //dof_node: number of degree of freedom per node
  int edof;      //edof: number of degree of freedom per element
  int n_dof;
  int total_dof;
  int ndim = 2; // problem dimension (2D truss => ndim = 2)

  int Ng;
  int ShapeOrder;
  int Model2D;

  int n_node;
  int n_elem;
  int n_load;
  int n_pre_disp;
  int n_trac;

  arma::mat coords;
  arma::imat elem_node;
  arma::mat  elem_stiff;
  arma::mat  elem_load;
  arma::mat  elem_area;
  arma::imat force_node;
  arma::colvec force_val;
  arma::imat  disp_node;
  arma::colvec disp_val;
  arma::imat trac_ele;
  arma::mat  trac_val;

  arma::imat eq_num;
  arma::colvec Pf;
  arma::colvec Pp;
  arma::colvec Uf;
  arma::colvec Up;
  arma::mat Uur;
  arma::mat Pur;
  arma::mat Kff;
  arma::mat Kfp;
  arma::mat Kpf;
  arma::mat Kpp;

  arma::mat StressAtIntegrationPoints;
  arma::mat StrainAtIntegrationPoints;

  arma::mat TpAtIntegrationPoints;
  arma::mat VMAtIntegrationPoints;
  arma::mat StrainAtCentroid;
  arma::mat StressAtCentroid;
  arma::mat TpAtCentroid;
  arma::mat StrainAtNodes;
  arma::mat StressAtNodes;
  arma::mat TpAtNodes;
  arma::mat VMAtNodes;

  //string filename = "Patch.dat"; //Example1
  //string filename = "inputTortoTextBook.dat"; //Example2
  //string filename = "PatchPointForce.dat"; //Example3
  string filename = "Patch-1Element.dat"; //Example4

  //%% BEFORE COMMITING YOUR CODE: comment all lines above and keep the line below uncommented!
  //%% We will modify the line below to read our test input file
  //string filename = "input.dat";
  //%% IMPORTANT INFORMATION
  
  /*=========================================================;
  %                 Read data from input files               ;
  %=========================================================*/

  ReadInput(filename, ndim,  n_node, n_elem, n_load, n_pre_disp, nnode_ele,dof_node,edof,
	    coords, elem_node, elem_stiff, elem_load, elem_area,  force_node, force_val, 
	    disp_node, disp_val, n_trac, trac_ele, trac_val,
	    Ng, ShapeOrder, Model2D);

/*=========================================================;
  %                 Complete your FEA code                   ;
  %=========================================================*/
 /*==========================================================;
 %                 Creating Global Id matrix                 ;
 %===========================================================*/
 //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//

  InitializeEquation( n_node,  n_pre_disp, dof_node,
  					 disp_node, eq_num,
  					 n_dof, total_dof );




  //*=========================================================;
  // Write EQNUM output
  // DO NOT MODIFY THE LINE BELOW!!
  PrintEQNUM(eq_num);
  //=========================================================*/

 /*==========================================================;
 %                 Assemble Module                            ;
 %===========================================================*/
 //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//

  AssembleModule( edof, n_dof, total_dof, ndim, dof_node, n_elem, n_load, n_pre_disp, nnode_ele, 
				coords, elem_node, elem_stiff, elem_load, elem_area,
				force_node, force_val, disp_node, disp_val, n_trac, trac_ele, trac_val,
		     	Ng, ShapeOrder, Model2D,
		     	eq_num, Kff, Kpp, Kpf, Kfp, Pf, Pp, Uf, Up );


  //*=========================================================;
  // Write Matrices output
  // DO NOT MODIFY THE LINE BELOW!!
  PrintMatrices(n_dof, total_dof, Kff, Kpp, Kpf, Kfp);
  // =========================================================*


 /*==========================================================;
 %                 Solve (Analysis)                          ;
 %===========================================================*/
 //~~~~~~~~~~~~~~~~~ Your Code Here ~~~~~~~~~~~~~~~~~~~~~~~~//

  SolveModule( n_node, n_dof, total_dof, dof_node,
				eq_num, Kff,  Kpp, Kpf, Kfp, Pf, Pp,
				Uf, Up, Uur, Pur );

  //*=========================================================;
  // Write Solution Output Files
  // DO NOT MODIFY THE LINE BELOW!!
  PrintSolution(Uf, Pp, Uur, Pur);
  // =========================================================*
 /*=========================================================;
  %                 Post-Processing                         ;
  %=========================================================*/
  EvaluateFieldGradient( nnode_ele, n_node, n_elem, dof_node, Ng, ShapeOrder, Model2D, ndim,
		  coords, elem_node, elem_stiff, Uur, StrainAtIntegrationPoints, StressAtIntegrationPoints,
		  TpAtIntegrationPoints, VMAtIntegrationPoints, StrainAtCentroid, StressAtCentroid, TpAtCentroid,
		  StrainAtNodes, StressAtNodes, TpAtNodes, VMAtNodes);

  //*=========================================================;
  // Write Solution Output Files
  // DO NOT MODIFY THE LINE BELOW!!
  PrintPostProcessingResults(StrainAtIntegrationPoints, StressAtIntegrationPoints, TpAtIntegrationPoints,
    VMAtIntegrationPoints, StrainAtCentroid, StressAtCentroid, TpAtCentroid, StrainAtNodes,
    StressAtNodes, TpAtNodes, VMAtNodes);
  // =========================================================*

  return(0);
}



