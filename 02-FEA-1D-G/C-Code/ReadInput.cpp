#include <MainFile.h>
using namespace std;

void ReadInput(const std::string& filename, int& n_node, int& n_elem, int& n_load, int& n_pre_disp,
	       const int nnode_ele, arma::imat& elem_node, arma::colvec& elem_stiff,
	       arma::icolvec& disp_node, arma::colvec& disp_val, arma::colvec& coords, 
	       arma::colvec& elem_load, arma::colvec& elem_area, arma::icolvec& force_node, arma::colvec& force_val)
{


  ifstream fout(filename.c_str());
int      count = 0;

if (fout.is_open() ) {

  fout >> n_node >> n_elem >> n_load >> n_pre_disp;

  elem_node = arma::zeros<arma::imat>(nnode_ele,n_elem);
  elem_stiff = arma::zeros<arma::colvec>(n_elem);
  disp_node  = arma::zeros<arma::icolvec>(n_pre_disp);
  disp_val  = arma::zeros<arma::colvec>(n_pre_disp);
  coords = arma::zeros<arma::colvec>(n_node);
  elem_load = arma::zeros<arma::colvec>(n_elem);
  elem_area = arma::zeros<arma::colvec>(n_elem);
  force_node  = arma::zeros<arma::icolvec>(n_load);
  force_val  = arma::zeros<arma::colvec>(n_load);
  for (int i=0; i<n_node; i++){
  	fout >> coords(i);
  } 
  
  for (int i=0; i<n_elem; i++) {

    fout >> elem_node(0,i) >> elem_node(1,i) >> elem_stiff(i) >> elem_load(i) >> elem_area(i);

   }

for (int i=0;i<n_load;i++ ) {

    fout >> force_node(i) >> force_val(i);

   }

 for (int i=0;i<n_pre_disp;i++ ) {

    fout >> disp_node(i) >> disp_val(i);

   }
}

 fout.close();

}