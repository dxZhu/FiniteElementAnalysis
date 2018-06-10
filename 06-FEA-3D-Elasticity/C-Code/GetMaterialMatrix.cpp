#include "MainFile.h"
#include <iostream>

using namespace std;

void GetMaterialMatrix(const int& Model2D, const int& i_elem, const arma::mat& elem_stiff, arma::mat& k)
{

double ElasticityModulus = elem_stiff(i_elem-1, 0);
double PoissonRatio = elem_stiff(i_elem-1, 1);
double E = ElasticityModulus;
double v = PoissonRatio;
double miu = E/(2 * (1+v));
double lamda = E*v/((1+v)*(1-2*v));

switch(Model2D){
  	case 1:	//Plane Stress
  	k << E/(1-v*v) << 0 << 0 << E*v/(1-v*v) << arma::endr
  		<< 0 << miu << miu << 0 << arma::endr
  		<< 0 << miu << miu << 0 << arma::endr
  		<< E*v/(1-v*v) << 0 << 0 << E/(1-v*v) << arma::endr;
  	break;
  	case 2:	//Plane Strain
  	k << lamda+2*miu << 0 << 0 << lamda << arma::endr
  		<< 0 << miu << miu << 0 << arma::endr
  		<< 0 << miu << miu << 0 << arma::endr
  		<< lamda << 0 << 0 << lamda+2*miu << arma::endr;
  	break;
  	}
}