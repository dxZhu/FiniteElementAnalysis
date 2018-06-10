#include "MainFile.h"
#include <iostream>

using namespace std;


void AssembleGlobalStiffness(int& elem_num, 
arma::mat& Kel, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kfp, arma::mat& Kpf, const arma::imat& elem_node, arma::imat& eq_num)
{

  	  	for(int i=0; i<2; i++){	//loop over rows
  		int i_node = elem_node(i,elem_num);	//element1 with nodei
  		int row =0;
  		row = eq_num(i_node-1);
  		for(int j=0; j<2; j++){	//loop over columns
  			int j_node = elem_node(j,elem_num);	//element1 with nodej
  			int col = eq_num(j_node-1);
  			if(row>0){//free row
  				if(col>0){//free col
  				Kff(row-1,col-1) = Kff(row-1,col-1) + Kel(i,j);
  				}else{//restricted col
  				Kfp(row-1,-col-1) = Kfp(row-1,-col-1) + Kel(i,j);
  				}
  			}
  			else{//restricted node
  				if(col>0){//free col
  				Kpf(-row-1, col-1) = Kpf(-row-1, col-1) + Kel(i,j);
  				}else{//restricted col
  				Kpp(-row-1, -col-1) = Kpp(-row-1, -col-1) + Kel(i,j);
  				}
  			}
  			
  		}
  	}	
  }
