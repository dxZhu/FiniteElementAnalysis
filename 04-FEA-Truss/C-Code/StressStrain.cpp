#include "MainFile.h"
#include <iostream>

using namespace std;

void StressStrain( const int n_node, int n_elem, int dof_node, int nnode_ele,
		  arma::mat  elem_stiff, arma::mat elem_load, arma::mat Uur, arma::mat coords, arma::colvec le, arma::imat elem_node,
		  arma::mat& stress, arma::mat& strain)
{

double c;
double s;
arma::mat T;
arma::colvec Uel;	//element displacement
arma::colvec U_diff;
arma::colvec node;

node = arma::zeros<arma::colvec>(nnode_ele);
stress = arma::zeros<arma::mat>(n_elem, 1);
strain = arma::zeros<arma::mat>(n_elem, 1);
T = arma::zeros<arma::mat>(nnode_ele, nnode_ele*dof_node); 
Uel = arma::zeros<arma::colvec>(nnode_ele*dof_node); 
U_diff = arma::zeros<arma::colvec>(nnode_ele); 
for(int iel=0; iel<n_elem; iel++){
	node(0) = elem_node(0, iel);
  	node(1) = elem_node(1, iel);
	c = (coords(node(1)-1,0)-coords(node(0)-1,0))/le(iel);
	s = (coords(node(1)-1,1)-coords(node(0)-1,1))/le(iel);	
	T << c << s << 0 << 0 << arma::endr
		<< 0 << 0 << c << s << arma::endr;
	for(int i=0; i<nnode_ele; i++){
		int nodex = 2 * i;
		int nodey = 2 * i + 1;
		Uel(nodex) = Uur(node(i)-1,0);
		Uel(nodey) = Uur(node(i)-1,1);
	}
	//cout << Uel;
	U_diff = T * Uel;
	//cout << U_diff;
	strain(iel) = (U_diff(1) - U_diff(0))/(le(iel));
	stress(iel,0) = elem_stiff(iel,0) * (strain(iel) - elem_load(iel,1) * elem_stiff(iel,1));
}

}