#include "MainFile.h"
#include <iostream>

using namespace std;

void AssembleGlobalStiffness(const int& i_elem, const int& nnode_ele, const int& dof_node,
				const arma::imat& elem_node, const arma::mat& kel, const arma::colvec& pel, 
				const arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
				arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp)
{
	int iel = i_elem;
	//Set for Pur
	for(int i=0; i<nnode_ele; i++){
	int row =0;
  	int inode = elem_node(i,iel-1);
  	  for(int j=0; j<dof_node; j++){	
  		row = eq_num(inode-1, j);
  		if(row>0){
  			Pf(row-1) = Pf(row-1) + pel(2*i+j);
  		}else{
  			Pp(-row -1) = Pp(-row-1) + pel(2*i+j);}
  			}
  		}
	
	
	//Set for Kur
	for(int i=0; i<nnode_ele; i++){	//loop over rows
  	  int row =0;
  	  int inode = elem_node(i,iel-1);
  	  for(int k=0; k<dof_node; k++){
  		row = eq_num(inode-1, k);
  		for(int j=0; j<nnode_ele; j++){	//loop over columns
  			int col = 0;
  			int jnode = elem_node(j,iel-1);
  			for(int l=0; l<dof_node; l++){
  			  int col = eq_num(jnode-1, l);
  			  int p = dof_node * i + k;	//k = l =0;
  			  int q = dof_node * j + l;
  					if(row>0){//free row
  						if(col>0){//free col
  						Kff(row-1,col-1) = Kff(row-1,col-1) + kel(p,q);
  						}else{//restricted col
  						Kfp(row-1,-col-1) = Kfp(row-1,-col-1) + kel(p,q);}
  					}else{//restricted node
  						if(col>0){//free col
  						Kpf(-row-1, col-1) = Kpf(-row-1, col-1) + kel(p,q);
  						}else{//restricted col
  						Kpp(-row-1, -col-1) = Kpp(-row-1, -col-1) + kel(p,q);}
  						}
  				}
  			}
  		}
  	}


}