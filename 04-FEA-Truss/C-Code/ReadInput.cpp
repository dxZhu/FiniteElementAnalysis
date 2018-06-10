#include <MainFile.h>
using namespace std;

void ReadInput(const std::string& filename, const int ndim, int& n_node, int& n_elem, int& n_load, int& n_pre_disp,
	       int& nnode_ele, int& dof_node, int& edof, 
	       arma::mat& coords, arma::imat& elem_node, arma::mat& elem_stiff, 
	       arma::mat& elem_load, arma::mat& elem_area, arma::imat& force_node, arma::colvec& force_val, 
	       arma::imat& disp_node, arma::colvec& disp_val)
{


  ifstream fout(filename.c_str());
int      count = 0;

if (fout.is_open() ) {

  fout >> n_node >> n_elem >> n_load >> n_pre_disp;
  //cout<<n_node<<n_elem<<n_load<<n_pre_disp<<"\n";

  nnode_ele  = 2;
  dof_node = 2; //Number of degrees of freedom per node
  edof = nnode_ele*dof_node; //number of degrees of freedom per element

  elem_node = arma::zeros<arma::imat>(nnode_ele,n_elem);
  elem_stiff = arma::zeros<arma::mat>(n_elem,2);
  elem_load = arma::zeros<arma::mat>(n_elem,2);
  elem_area = arma::zeros<arma::mat>(n_elem,1);
  force_node  = arma::zeros<arma::imat>(n_load,ndim);
  force_val  = arma::zeros<arma::colvec>(n_load);
  disp_node  = arma::zeros<arma::imat>(n_pre_disp,ndim);
  disp_val  = arma::zeros<arma::colvec>(n_pre_disp);
  coords = arma::zeros<arma::mat>(n_node,ndim);


  for (int i=0;i<n_node;i++ ) {

    for (int j=0;j<ndim;j++) {

      fout >> coords(i,j);
 
    }
  }  
  
  //cout<<coords<<"\n";

  for (int i=0;i<n_elem;i++ ) {

    fout >> elem_node(0,i) >> elem_node(1,i) >> elem_stiff(i,0) >>  elem_load(i,0) >> elem_area(i,0) >> elem_stiff(i,1) >> elem_load(i,1) ;

   }  
  /*cout<<elem_node;
  cout<<elem_stiff;
  cout<<elem_load;
  cout<<elem_area;*/
  
  for (int i=0;i<n_load;i++ ) {
    for (int j=0;j<ndim;j++) {
      fout >> force_node(i,j);
    }
    fout >> force_val(i);
  }

  for (int i=0;i<n_pre_disp;i++ ) {
    for (int j=0;j<ndim;j++) {
      fout >> disp_node(i,j);
    }
    fout >> disp_val(i);
  }
  /*cout<<force_node;
  cout<<force_val;
  cout<<disp_node;
  cout<<disp_val;*/

}

fout.close();

}
