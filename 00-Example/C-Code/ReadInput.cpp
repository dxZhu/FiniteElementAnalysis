#include "MainFile.h"
using namespace std;

void ReadInput(const std::string& filename, int& n_node, int& n_elem, int& n_load, int& n_pre_disp,
	       const int nnode_ele, arma::imat& elem_node, arma::colvec& elem_stiff,
	       arma::icolvec& force_node, arma::colvec& force_val,
	       arma::icolvec& disp_node, arma::colvec& disp_val)
{


  ifstream fout(filename.c_str());
int      count = 0;

if (fout.is_open() ) {

  fout >> n_node >> n_elem >> n_load >> n_pre_disp;	//7 8 3 2

  elem_node = arma::zeros<arma::imat>(nnode_ele,n_elem);	//2x8
  elem_stiff = arma::zeros<arma::colvec>(n_elem);	//8
  force_node  = arma::zeros<arma::icolvec>(n_load);	//3
  force_val  = arma::zeros<arma::colvec>(n_load);	//3
  disp_node  = arma::zeros<arma::icolvec>(n_pre_disp);	//2
  disp_val  = arma::zeros<arma::colvec>(n_pre_disp);	//2

  //give initial value for elem_node and elem_stiff
  for (int i=0;i<n_elem;i++ ) {

    fout >> elem_node(0,i) >> elem_node(1,i) >> elem_stiff(i);

   }

  //give initial input to force vector:
  for (int i=0;i<n_load;i++ ) {

    fout >> force_node(i) >> force_val(i);

   }

  //give initial value for disp vector:
  for (int i=0;i<n_pre_disp;i++ ) {

    fout >> disp_node(i) >> disp_val(i);

   }
}

 fout.close();

}
