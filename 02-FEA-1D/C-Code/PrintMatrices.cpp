#include <MainFile.h>
using namespace std;

void PrintMatrices(const int& n_dof, const int& total_dof, arma::mat& Kff,
    arma::mat& Kpp, arma::mat& Kpf,  arma::mat& Kfp)
{
  int fixeddofs = total_dof-n_dof;

  ofstream fout;

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
}
