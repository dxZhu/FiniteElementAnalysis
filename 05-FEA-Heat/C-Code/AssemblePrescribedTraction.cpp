#include "MainFile.h"
#include <iostream>

using namespace std;

void AssemblePrescribedTraction( const int edof, const int nnode_ele, const int dof_node,
		const int Ng, const int ShapeOrder, const int ndim, const arma::mat& coords, const arma::imat& elem_node,
		const arma::mat& elem_stiff, const arma::mat& elem_load, const arma::mat& elem_area,
		const int& n_trac_q, const arma::imat& trac_q_ele, const arma::mat& trac_q_val,
		const int& n_trac_c, const arma::imat& trac_c_ele, const arma::mat& trac_c_val,
		const arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, arma::mat& Kfp,
				     arma::colvec& Pf,  arma::colvec& Pp )
{

  arma::imat trac_ele;	//temp trac matrix, replacement of c_trac and q_trac
  arma::mat kel;
  arma::colvec pel;

//loop over boundaries with convective heat flux
  for(int m=0; m<n_trac_c; m++)
  {
    int i_elem;
    double betaP;
    double betaK;
    i_elem = trac_c_ele(m,0);
    betaP = trac_c_val(m,0) * trac_c_val(m,1);	// = h * T_inf
    betaK = trac_c_val(m,0);	// = h
    trac_ele = trac_c_ele;
    bool stiffness = true;
    bool lumped = true;
    kel = arma::zeros<arma::mat>(edof,edof);
    pel = arma::zeros<arma::colvec>(edof);
//Set kel and pel, caused by prescribed convective heat flux:
    ElementSurfaceTraction(edof, m, nnode_ele, Ng, ShapeOrder, ndim, 
    	coords, elem_node, trac_ele, betaP, betaK, stiffness, lumped,
		kel, pel);
  cout << kel << pel;
//Assemble the kel and pel to Kur and Pur
	AssembleGlobalStiffness(i_elem, nnode_ele, dof_node,
				elem_node, kel, pel, eq_num, 
				Kff, Kpp, Kpf, Kfp, Pf, Pp); 
  cout << Pf << endl;		
  }

  
//loop over boundaries with prescribed heat flux
  for(int m=0; m<n_trac_q; m++)
  {
  	int i_elem;
  	double betaP;
  	double betaK = 0;
  	i_elem = trac_q_ele(m,0);
  	betaP = -trac_q_val(m,0);
  	trac_ele = trac_q_ele;
  	bool stiffness = false;
    bool lumped = false;
    
//Set kel and pel, caused by prescribed heat flux:
    ElementSurfaceTraction(edof, m, nnode_ele, Ng, ShapeOrder, ndim, 
    		coords, elem_node, trac_ele, 
    		betaP, betaK, stiffness, lumped,
			kel, pel);
cout << kel << pel;
//Assemble above kel and pel to global Kur and Pur
	AssembleGlobalStiffness(i_elem, nnode_ele, dof_node,
				elem_node, kel, pel, 
				eq_num, Kff, Kpp, Kpf, Kfp, Pf, Pp);  
  	
  }
 //cout << Kff << endl << Kfp << endl << Kpf << endl << Kpp << endl;		     
}