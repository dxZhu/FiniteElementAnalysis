#include "MainFile.h"

using namespace std;

void ReadInput(const std::string& filename, const int mdim, int& n_node, int& n_elem, int& n_load, int& n_pre_disp,
	       int& nnode_ele, int& dof_node, int& edof, int& Ng, int& ShapeOrder, arma::mat& coords, arma::imat& elem_node,
	       arma::colvec& elem_stiff, arma::colvec& elem_load, arma::ivec& UMATid, arma::ivec& DLOADid,
	       arma::icolvec& force_node, arma::colvec& force_val, arma::icolvec& disp_node, arma::colvec& disp_val)
{


  ifstream fout(filename.c_str());
  int      count = 0;

if (fout.is_open() ) {

  fout >> n_node >> n_elem >> n_load >> n_pre_disp >> Ng >> ShapeOrder;
  //cout<<n_node<<n_elem<<n_load<<n_pre_disp<<Ng<<ShapeOrder<<"\n";

  if (ShapeOrder == 1) nnode_ele = 2; //Number of nodes per element
  else if (ShapeOrder == 2) nnode_ele  = 3;
  else if (ShapeOrder == 3) nnode_ele  = 4;
  else {
    cout<<"Only linear, quadratic and cubic functions are implemented. Exit\n";
    exit(1);
  }

  if (Ng > 4) {
    cout<< "Input is Ng = "<<Ng<<". Max Ng = 4. Exit\n";
    exit(1);
  }
  dof_node  = 1; //Number of degrees of freedom per node
  edof = nnode_ele*dof_node;


  elem_node = arma::zeros<arma::imat>(nnode_ele,n_elem);
  elem_stiff = arma::zeros<arma::colvec>(n_elem);
  elem_load = arma::zeros<arma::colvec>(n_elem);
  UMATid = arma::zeros<arma::ivec>(n_elem);
  DLOADid = arma::zeros<arma::ivec>(n_elem);
  force_node  = arma::zeros<arma::icolvec>(n_load);
  force_val  = arma::zeros<arma::colvec>(n_load);
  disp_node  = arma::zeros<arma::icolvec>(n_pre_disp);
  disp_val  = arma::zeros<arma::colvec>(n_pre_disp);
  coords = arma::zeros<arma::mat>(n_node,mdim);



  for (int i=0;i<n_node;i++ ) {

    fout >> coords(i,0);

   }

  string e1,b1;
  for (int i=0;i<n_elem;i++ ) {
    for (int j=0;j<nnode_ele;j++) {
      fout >> elem_node(j,i);
    }
    fout >> e1  >> b1;
    if (e1 == "UMAT") {
      UMATid(i) = 1;
    }
    else {
      elem_stiff(i) = atof(e1.c_str());
    }
    if (b1 == "DLOAD") {
      DLOADid(i) = 1;
    }
    else {
      elem_load(i) = atof(b1.c_str());
    }
  }

  /*cout<<coords;
  cout<<elem_node;
  cout<<elem_stiff;
  cout<<UMATid;
  cout<<elem_load;
  cout<<DLOADid;
  cout<<Ng<<'\n';
  cout<<ShapeOrder;*/



  for (int i=0;i<n_load;i++ ) {

     fout >> force_node(i) >> force_val(i);

   }
  for (int i=0;i<n_pre_disp;i++ ) {

    fout >> disp_node(i) >> disp_val(i);

   }

  /*cout<<force_node;
  cout<<force_val;
  cout<<disp_node;
  cout<<disp_val;*/
}

 fout.close();

 cout<<"Completed Reading input.dat file\n";

}