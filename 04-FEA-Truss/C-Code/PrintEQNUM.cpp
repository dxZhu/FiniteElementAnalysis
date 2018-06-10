#include <MainFile.h>
using namespace std;

void PrintEQNUM(const arma::imat& eq_num)
{
  ofstream fout;
  fout.open ("EQNUM.dat");
  fout << eq_num;
  fout.close();

}
