#include <MainFile.h>
using namespace std;

void PrintPostProcessingResults(arma::mat& FluxAtIntegrationPoints, arma::mat& FluxAtCentroid,
     arma::mat& NodalFlux, arma::colvec& MagnitudeNodalFlux)
{
  ofstream fout;
  cout<<"FLUX AT INTEGRATION POINTS\n";
  cout << FluxAtIntegrationPoints;
  fout.open ("FluxAtIntegrationPoints.dat");
  fout << FluxAtIntegrationPoints;
  fout.close();

  cout<<"FLUX AT CENTROID\n";
  cout << FluxAtCentroid;
  fout.open ("FluxAtCentroid.dat");
  fout << FluxAtCentroid;
  fout.close();

  cout<<"FLUX AT NODES\n";
  cout << NodalFlux;
  fout.open ("FluxAtNodes.dat");
  fout << NodalFlux;
  fout.close();


  cout<<"FLUX MAGNITUDE AT NODES\n";
  cout << MagnitudeNodalFlux;
  fout.open ("FluxMagnitudeAtNodes.dat");
  fout << MagnitudeNodalFlux;
  fout.close();
}