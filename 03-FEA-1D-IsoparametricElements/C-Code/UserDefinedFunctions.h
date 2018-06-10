#include <iostream>

using namespace std;

double UMAT(double x);
double DLODA(double x);
double UAREA(double x);

//Define E function
double UMAT(double x){
	double eval;
	if(x<=3.0){
		eval = 20 * x;
	}else if(x<=6.0){
		eval = 10 * x + 20;
	}else{cout << "x is out of range" << endl;}
	return(eval);
}

double DLOAD(double x){
	double bval;
	if(x<=2.0){
		bval = x * x;
	}else if(x<=4.0){
		bval = x;
	}else if(x<=6.0){
		bval = 10;
	}else{cout << "x is out of range!" << endl;}
	return(bval);
}