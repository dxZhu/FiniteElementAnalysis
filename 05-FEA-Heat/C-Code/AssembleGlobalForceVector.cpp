#include "MainFile.h"
#include <iostream>

using namespace std;

void AssembleGlobalForceVector( const int& n_load, const arma::imat& force_node, 
				const arma::colvec& force_val, const arma::imat& eq_num,  arma::colvec& Pf )
{
  
  for(int i=0; i<n_load; i++){
  		int node= force_node(i, 0);
  		int dof_id = force_node(i, 1);
  		int p = force_val(i);
  		int row = eq_num(node-1, dof_id-1);
  		if(row>0){
  			Pf(row-1) = Pf(row-1) + p;}
  	}

}