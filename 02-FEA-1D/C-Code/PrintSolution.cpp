#include <MainFile.h>
using namespace std;

void PrintSolution(arma::colvec& Uf, arma::colvec& Pp,  arma::colvec& Uur,   arma::colvec& Pur)
{

  ofstream fout;

  fout.open ("UF_Vector.dat");
  fout << Uf;
  fout.close();
 
  fout.open ("PP_Vector.dat");
  fout << Pp;
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
