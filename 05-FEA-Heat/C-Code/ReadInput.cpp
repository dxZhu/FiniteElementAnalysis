#include <MainFile.h>
using namespace std;

void ReadInput(const std::string& filename, const int ndim, int& n_node, int& n_elem, int& n_load, int& n_pre_disp,
	       int& nnode_ele, int& dof_node, int& edof, 
	       arma::mat& coords, arma::imat& elem_node, arma::mat& elem_stiff, 
	       arma::mat& elem_load, arma::mat& elem_area, arma::imat& force_node, arma::colvec& force_val, 
	       arma::imat& disp_node, arma::colvec& disp_val,
	       int& n_trac_q, arma::imat& trac_q_ele, arma::mat& trac_q_val,
	       int& n_trac_c, arma::imat& trac_c_ele, arma::mat& trac_c_val, int& Ng, int& ShapeOrder )
{
/*
	% INPUT:
	% filen: name of the file with input values
	% ndim: problem dimension (ndim=2 -> 2D problem)

	% OUTPUT:
	% N_NODE, the (integer) number of nodes
	% N_ELEM, the (integer) number of elements
	% N_LOAD, the (integer) number of nonzero prescribed concentrated loads
	% N_PRE_DISP, the (integer) number prescribed field (essential) BCs
	% N_MAT, the (integer) number of material sets
	% N_BLOAD, the (integer) number of body load sets
	% N_TRAC, the (integer) number of prescribed flux/traction BCs
	% ELEM_NODE(nnode_ele, N_ELEM), matrix that contains node numbers (integers) for each element
	% ELEM_STIFF(N_ELEM,2), vector that contains stiffness value (real) and thermal expansion coefficient for each element
	% ELEM_LOAD(N_ELEM,2), vector that contains specific weight (real) and change in temperature for each element
	% FORCE_NODE(N_LOAD), vector that contains the node numbers (integer) where forces are applied
	% FORCE_VAL(N_LOAD), vector that contains the value of the forces (real) corresponding to the numbers in FORCE_NODE
	% DISP_NODE(N_PRE_DISP), vector that contains the node numbers (integer) where boundary conditions are imposed
	% DISP_VAL(N_PRE_DISP),  vector that contains the value of the forces (real) corresponding to the numbers in DISP_NODE*/

	cout<<"Reading file:"<< filename<<"\n";


  ifstream fout(filename.c_str());
  int      count = 0;
  int n_mat, n_bload;

  int mat_index, load_index;

  Ng = 2;
  ShapeOrder = 1; // At this point, only linear shape function is implemented

  if (fout.is_open() ) {

	  fout >> n_node >> n_elem >> n_load >> n_pre_disp >> n_trac_q >> n_trac_c >> n_mat >> n_bload;
	  //cout<<n_node<<"\t"<<n_elem<<"\t"<<n_load<<"\t"<<n_pre_disp<<"\t"<<n_trac_q<<"\t" << n_trac_c <<"\t"<< n_mat <<"\t"<< n_bload<<"\n";

	  nnode_ele  = 4;
	  dof_node = 1; //Number of degrees of freedom per node
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
  trac_q_ele  = arma::zeros<arma::imat>(n_trac_q,2);//% first entry is the element, second entry is the local edge number (index)
  trac_q_val  = arma::zeros<arma::mat>(n_trac_q,1);// qp
  trac_c_ele  = arma::zeros<arma::imat>(n_trac_c,2);//% first entry is the element, second entry is the local edge number (index)
  trac_c_val  = arma::zeros<arma::mat>(n_trac_c,2);//(h, Tinf)

  arma::mat material = arma::zeros<arma::mat>(n_mat,3); //(kx, ky, t)
  arma::mat bodyload = arma::zeros<arma::mat>(n_bload,1);

  int temp;
  for (int i=0;i<n_mat;i++ ) {
	  fout>>temp;
	  for (int j=0;j<3;j++) {
		  fout >> material(i,j);
     }
   }
  //cout<<material;
  for (int i=0;i<n_bload;i++ ) {
	  fout>>temp>> bodyload(i,0);
   }
  //cout<<bodyload;

   for (int i=0;i<n_node;i++ ) {

	   fout >> temp;

	   for (int j=0;j<ndim;j++) {

		   fout >> coords(i,j);
 
	   }
  }  
  //cout<<coords<<"\n";

  for (int i=0;i<n_elem;i++ ) {
	  fout >> temp;
	  //cout<<temp<<"\n";
	  for (int j=0;j<nnode_ele;j++) {
		  fout >> elem_node(j,i);
	  }
	  //cout << elem_node.col(i);
	  fout >> mat_index >> load_index;
	  //cout<< mat_index<<"\t"<<load_index<<"\n";
	  elem_stiff(i,0) = material(mat_index-1,0);
	  elem_stiff(i,1) = material(mat_index-1,1);
	  elem_load(i,0) = bodyload(load_index-1,0);
	  elem_area(i,0) = material(mat_index-1,2);
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

  for (int i=0;i<n_trac_q;i++ ) {
    fout >> trac_q_ele(i,0) >> trac_q_ele(i,1) >> trac_q_val(i,0);
  }

  for (int i=0;i<n_trac_c;i++ ) {
    fout >> trac_c_ele(i,0) >> trac_c_ele(i,1) >> trac_c_val(i,0) >> trac_c_val(i,1);
  }

  /*cout<<force_node;
  cout<<force_val;
  cout<<disp_node;
  cout<<disp_val;
  cout<<trac_q_ele;
  cout<<trac_q_val;
  cout<<trac_c_ele;
  cout<<trac_c_val;*/

}

fout.close();

}
