#include <MainFile.h>
using namespace std;

void PrintPostProcessingResults(arma::mat& StrainAtIntegrationPoints, arma::mat& StressAtIntegrationPoints,
        arma::mat& TpAtIntegrationPoints, arma::mat& VMAtIntegrationPoints,
        arma::mat& StrainAtCentroid, arma::mat& StressAtCentroid, arma::mat& TpAtCentroid,
        arma::mat& StrainAtNodes, arma::mat& StressAtNodes, arma::mat& TpAtNodes, arma::mat&  VMAtNodes)
{
  ofstream fout;
  
    cout<<"STRESS AT INTEGRATION POINTS\n";
  cout << StressAtIntegrationPoints;
  fout.open ("StressAtIntegrationPoints.dat");
  fout << StressAtIntegrationPoints;
  fout.close();
  
  cout<<"STRAIN AT INTEGRATION POINTS\n";
  cout << StrainAtIntegrationPoints;
  fout.open ("StrainAtIntegrationPoints.dat");
  fout << StrainAtIntegrationPoints;
  fout.close();
  
  cout<<"PRINCIPAL STRESSES AT INTEGRATION POINTS\n";
  cout << TpAtIntegrationPoints;
  fout.open ("PrincipalStressesAtIntegrationPoints.dat");
  fout << TpAtIntegrationPoints;
  fout.close();
  
  cout<<"VOM MISES STRESSES AT INTEGRATION POINTS\n";
  cout << VMAtIntegrationPoints;
  fout.open ("VonMisesAtIntegrationPoints.dat");
  fout << VMAtIntegrationPoints;
  fout.close();

  cout<<"STRESS AT CENTROID\n";
  cout << StressAtCentroid;
  fout.open ("StressAtCentroid.dat");
  fout << StressAtCentroid;
  fout.close();
  
  cout<<"STRAIN AT CENTROID\n";
  cout << StrainAtCentroid;
  fout.open ("StrainAtCentroid.dat");
  fout << StrainAtCentroid;
  fout.close();
  
  cout<<"PRINCIPAL STRESSES AT CENTROID\n";
  cout << TpAtCentroid;
  fout.open ("PrincipalStressesAtCentroid.dat");
  fout << TpAtCentroid;
  fout.close();
  

  cout<<"STRESSES AT NODES\n";
  cout << StressAtNodes;
  fout.open ("StressAtNodes.dat");
  fout << StressAtNodes;
  fout.close();
  
  cout<<"STRAIN AT NODES\n";
  cout << StrainAtNodes;
  fout.open ("StrainAtNodes.dat");
  fout << StrainAtNodes;
  fout.close();
 
  cout<<"PRINCIPAL STRESSES AT NODES\n";
  cout << TpAtNodes;
  fout.open ("PrincipalStressesAtNodes.dat");
  fout << TpAtNodes;
  fout.close();
  
  cout<<"VOM MISES STRESSES AT NODES\n";
  cout << VMAtNodes;
  fout.open ("VonMisesStressesAtNodes.dat");
  fout << VMAtNodes;
  fout.close();
}