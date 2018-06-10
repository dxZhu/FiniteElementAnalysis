#include "MainFile.h"
#include <iostream>

using namespace std;

void Quad2DShapeFunctions(const int& ShapeOrder, const arma::colvec& rvec, arma::rowvec& Nhat, arma::mat& DNhat)
{

	double r1 = rvec(0);
	double r2 = rvec(1);
	if(ShapeOrder ==1 ){
	Nhat = arma::zeros<arma::rowvec>(4);
	DNhat = arma::zeros<arma::mat>(2,4);
	Nhat(0) = 0.25 * (1 - r1) * (1 - r2);
	Nhat(1) = 0.25 * (1 + r1) * (1 - r2);
	Nhat(2) = 0.25 * (1 + r1) * (1 + r2);
	Nhat(3) = 0.25 * (1 - r1) * (1 + r2);
	DNhat(0,0) = -0.25 * (1 - r2);
	DNhat(0,1) = 0.25 * (1 - r2);
	DNhat(0,2) = 0.25 * (1 + r2);
	DNhat(0,3) = -0.25 * (1 + r2);
	DNhat(1,0) = -0.25 * (1 - r1);
	DNhat(1,1) = -0.25 * (1 + r1);
	DNhat(1,2) = 0.25 * (1 + r1);
	DNhat(1,3) = 0.25 * (1 - r1);
	}
	else if(ShapeOrder ==2 ){
	Nhat = arma::zeros<arma::rowvec>(8);
	DNhat = arma::zeros<arma::mat>(2,8);
	Nhat(0) = -0.25 * (1 - r1) * (1 - r2) * (1 + r1 + r2);
	Nhat(1) = -0.25 * (1 + r1) * (1 + r2) * (1 - r1 + r2);
	Nhat(2) = -0.25 * (1 + r1) * (1 + r2) * (1 - r1 - r2);
	Nhat(0) = -0.25 * (1 - r1) * (1 + r2) * (1 + r1 - r2);
	Nhat(0) = 0.5 * (1 - r1 * r1) * (1 - r2);
	Nhat(0) = 0.5 * (1 - r2 * r2) * (1 + r1);
	Nhat(0) = 0.5 * (1 - r1 * r1) * (1 + r2);
	Nhat(0) = 0.5 * (1 - r2 * r2) * (1 - r1);
	DNhat(0,0) = -0.25 * (r2 - 1) * (2 * r1 + r2);
	DNhat(0,1) = -0.25 * (r2 - 1) * (2 * r1 - r2);
	DNhat(0,2) = 0.25 * (r2 + 1) * (2 * r1 + r2);
	DNhat(0,3) = 0.25 * (r2 + 1) * (2 * r1 - r2); 
	DNhat(0,4) = r1 * (r2 - 1);
	DNhat(0,5) = 0.5 * (1 - r2 * r2);
	DNhat(0,6) = -r1 * (r2 + 1);
	DNhat(0,7) = 0.5 * (r2 * r2 - 1);
	DNhat(1,0) = -0.25 * (r1 - 1) * (r1 + 2 * r2);
	DNhat(1,1) = -0.25 * (r1 + 1) * (r1 - 2 * r2);
	DNhat(1,2) = 0.25 * (r1 + 1) * (r1 + 2 * r2);
	DNhat(1,3) = 0.25 * (r1 - 1) * (r1 - 2 * r2); 
	DNhat(1,4) = 0.5 * (r1 * r1 - 1);
	DNhat(1,5) = -(1 + r1) * r2;
	DNhat(1,6) = 0.5 * (1 - r1 * r1);
	DNhat(1,7) = -(r1 - 1) * r2;
	}
	else if(ShapeOrder ==3 ){
	Nhat = arma::zeros<arma::rowvec>(8);
	DNhat = arma::zeros<arma::mat>(2,8);
	Nhat(0) = -0.25 * (1 - r1) * (1 - r2) * (1 + r1 + r2);
	Nhat(1) = -0.25 * (1 + r1) * (1 + r2) * (1 - r1 + r2);
	Nhat(2) = -0.25 * (1 + r1) * (1 + r2) * (1 - r1 - r2);
	Nhat(0) = -0.25 * (1 - r1) * (1 + r2) * (1 + r1 - r2);
	Nhat(0) = 0.5 * (1 - r1 * r1) * (1 - r2);
	Nhat(0) = 0.5 * (1 - r2 * r2) * (1 + r1);
	Nhat(0) = 0.5 * (1 - r1 * r1) * (1 + r2);
	Nhat(0) = 0.5 * (1 - r2 * r2) * (1 - r1);
	DNhat(0,0) = -0.25 * (r2 - 1) * (2 * r1 + r2);
	DNhat(0,1) = -0.25 * (r2 - 1) * (2 * r1 - r2);
	DNhat(0,2) = 0.25 * (r2 + 1) * (2 * r1 + r2);
	DNhat(0,3) = 0.25 * (r2 + 1) * (2 * r1 - r2); 
	DNhat(0,4) = r1 * (r2 - 1);
	DNhat(0,5) = 0.5 * (1 - r2 * r2);
	DNhat(0,6) = -r1 * (r2 + 1);
	DNhat(0,7) = 0.5 * (r2 * r2 - 1);
	DNhat(1,0) = -0.25 * (r1 - 1) * (r1 + 2 * r2);
	DNhat(1,1) = -0.25 * (r1 + 1) * (r1 - 2 * r2);
	DNhat(1,2) = 0.25 * (r1 + 1) * (r1 + 2 * r2);
	DNhat(1,3) = 0.25 * (r1 - 1) * (r1 - 2 * r2); 
	DNhat(1,4) = 0.5 * (r1 * r1 - 1);
	DNhat(1,5) = -(1 + r1) * r2;
	DNhat(1,6) = 0.5 * (1 - r1 * r1);
	DNhat(1,7) = -(r1 - 1) * r2;
	}

}