#include "MainFile.h"
using namespace std;

// This function must not be modified!!! 
// Autograding script will be using this output format 
// when grading your assignments

void PrintOutput(const int& n_dof, const int& total_dof, const arma::imat& eq_num, 
		 arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf,  arma::mat& Kfp, 
		 arma::colvec& Uf, arma::colvec& Up, arma::colvec& Pp,  arma::colvec& Pf, arma::colvec& Uur,   arma::colvec& Pur)
{

  int fixeddofs = total_dof-n_dof;

  ofstream fout;
  fout.open ("EQNUM.dat");
  fout << eq_num;
  fout.close();

  fout.open ("KPP_Matrix.dat");
  for (int i=0;i<fixeddofs;i++){
    for (int j=0;j<fixeddofs;j++){
      if (j<fixeddofs-1) fout << Kpp(i,j) << "\t";
      else fout << Kpp(i,j) << "\n";;
    }
  }
  fout.close();

 fout.open ("KPF_Matrix.dat");
  for (int i=0;i<fixeddofs;i++){
    for (int j=0;j<n_dof;j++){
      if (j<n_dof-1) fout << Kpf(i,j) << "\t";
      else fout << Kpf(i,j) << "\n";;
    }
  }
  fout.close();

 fout.open ("KFP_Matrix.dat");
  for (int i=0;i<n_dof;i++){
    for (int j=0;j<fixeddofs;j++){
      if (j<fixeddofs-1) fout << Kfp(i,j) << "\t";
      else fout << Kfp(i,j) << "\n";;
    }
  }
  fout.close();



 fout.open ("KFF_Matrix.dat");
  for (int i=0;i<n_dof;i++){
    for (int j=0;j<n_dof;j++){
      if (j<n_dof-1) fout << Kff(i,j) << "\t";
      else fout << Kff(i,j) << "\n";;
    }
  }
  fout.close();

  fout.open ("UF_Vector.dat");
  fout << Uf;
  fout.close();
  
  fout.open("UP_Vector,dat");
  fout << Up;
  fout.close();
  
  fout.open ("PP_Vector.dat");
  fout << Pp;
  fout.close();

  fout.open ("PF_Vector.dat");
  fout << Pf;
  fout.close();
  
  fout.open ("UUR_Vector.dat");
  fout << Uur;
  fout.close();

  fout.open ("PUR_Vector.dat");
  fout << Pur;
  fout.close();


  cout<<"NODE DISPLACEMENT\n";
  cout<<Uur<<endl;
  cout<<"NODE FORCE\n";
  cout<<Pur<<endl;

}
