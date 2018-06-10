#include "MainFile.h"
#include <iostream>

using namespace std;

void GaussQuadrature(const int& Ng, arma::colvec& rg, arma::colvec& wg)
{

if(Ng == 1){
  		rg = arma::zeros<arma::colvec>(Ng);
  		wg = arma::zeros<arma::colvec>(Ng);
		rg(0) = 0.0;
		wg(0) = 2.0;	
	}else if(Ng == 2){
	  	rg = arma::zeros<arma::colvec>(Ng);
  		wg = arma::zeros<arma::colvec>(Ng);
		rg(0) = -1/sqrt(3.0);
		rg(1) = 1/sqrt(3.0);
		wg(0) = 1.0;
		wg(1) = 1.0;	
	}else if(Ng == 3){
	  	rg = arma::zeros<arma::colvec>(Ng);
  		wg = arma::zeros<arma::colvec>(Ng);
		rg(0) = -sqrt(0.6);
		rg(1) = 0;
		rg(2) = sqrt(0.6);
		wg(0) = 5.0 / 9;
		wg(1) = 8.0 / 9;
		wg(2) = 5.0 / 9;
	}else if(Ng == 4){
	    rg = arma::zeros<arma::colvec>(Ng);
  		wg = arma::zeros<arma::colvec>(Ng);
		rg(0) = -sqrt(1/35.0 * (15.0 + sqrt(30.0) * 2.0));
		rg(1) = -sqrt(1/35.0 * (15.0 - sqrt(30.0) * 2.0));
		rg(2) = sqrt(1/35.0 * (15.0 - sqrt(30.0) * 2.0));
		rg(3) = sqrt(1/35.0 * (15.0 + sqrt(30.0) * 2.0));
		wg(0) = 49.0 /6/(18.0 + sqrt(30.0));
		wg(1) = 49.0 /6/(18.0 - sqrt(30.0));
		wg(2) = 49.0 /6/(18.0 - sqrt(30.0));
		wg(3) = 49.0 /6/(18.0 + sqrt(30.0));
	}else{cout << "Ng should not be larger than 4!";}
	
}