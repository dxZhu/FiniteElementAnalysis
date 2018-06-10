#include "MainFile.h"
#include <iostream>

using namespace std;

void AssemblePrescribedDisplacement( const int& n_pre_disp, const arma::imat& disp_node, 
				     const arma::colvec& disp_val,  const arma::imat& eq_num, arma::colvec& Up )
{

  int row = 0;

  for(int i=0; i<n_pre_disp; i++){
  	int node = 0;
  	int dim = 0;
  	node = disp_node(i,0);
  	dim = disp_node(i,1);
  	row = eq_num(node-1, dim-1);
  	Up(-row-1) = disp_val(i);
  }				     

}