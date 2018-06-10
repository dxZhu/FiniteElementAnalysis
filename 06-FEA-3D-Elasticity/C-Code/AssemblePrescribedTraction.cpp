#include "MainFile.h"
#include <iostream>

using namespace std;

void AssemblePrescribedTraction( const int edof, const int nnode_ele, const int dof_node,
		const int Ng, const int ShapeOrder, const int ndim, const arma::mat& coords, const arma::imat& elem_node,
		const arma::mat& elem_stiff, const arma::mat& elem_load, const arma::mat& elem_area,
		const int& n_trac, const arma::imat& trac_ele, const arma::mat& trac_val,
		const arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, arma::mat& Kfp,
		arma::colvec& Pf,  arma::colvec& Pp )
{

  arma::mat kel;
  arma::colvec pel;

//loop over boundaries with contraction
  for(int m=0; m<n_trac; m++)
  {
    int i_elem;
    double mag;
    double x_component;
    double y_component;
    i_elem = trac_ele(m,0);
    mag = trac_val(m,0);
    x_component = trac_val(m,1);
    y_component = trac_val(m,2);
    bool stiffness = true;
    bool lumped = true;
    kel = arma::zeros<arma::mat>(edof,edof);
    pel = arma::zeros<arma::colvec>(edof);
//Set prescrived pel, caused by prescribed contraction
    ElementSurfaceTraction(edof, m, nnode_ele, Ng, ShapeOrder, ndim, 
    	coords, elem_node, trac_ele, mag, x_component, y_component, 
		kel, pel);
		
//Assemble the kel and pel to Kur and Pur
	AssembleGlobalStiffness(i_elem, nnode_ele, dof_node,
				elem_node, kel, pel, eq_num, 
				Kff, Kpp, Kpf, Kfp, Pf, Pp); 	
  }
		     
}