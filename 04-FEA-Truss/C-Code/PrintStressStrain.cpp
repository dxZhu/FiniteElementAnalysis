#include <MainFile.h>
using namespace std;

void PrintStressStrain(arma::mat& strain, arma::mat& stress)
{

	ofstream fout;

  fout.open ("Stress_Vector.dat");
  fout << stress;
  fout.close();
  
  fout.open ("Strain_Vector.dat");
  fout << strain;
  fout.close();
  

}
