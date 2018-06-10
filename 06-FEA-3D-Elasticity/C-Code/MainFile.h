#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// INCLUDE ARMADILLO LIBRARY DEFINITIONS
#include <armadillo>
#include <iostream>
#include <iomanip>

void ReadInput(const std::string& filename, const int ndim, int& n_node, int& n_elem, int& n_load, int& n_pre_disp,
	       int& nnode_ele, int& dof_node, int& edof, 
	       arma::mat& coords, arma::imat& elem_node, arma::mat& elem_stiff, 
	       arma::mat& elem_load, arma::mat& elem_area, arma::imat& force_node, arma::colvec& force_val, 
	       arma::imat& disp_node, arma::colvec& disp_val,
	       int& n_trac, arma::imat& trac_ele, arma::mat& trac_val, int& Ng, int& ShapeOrder, int& Model2D );


void InitializeEquation(const int& n_node, const int& n_pre_disp, 
			const int dof_node, const arma::imat& disp_node, 
			arma::imat& eq_num, int& n_dof, int& total_dof );


void AssembleModule( const int edof, const int n_dof, const int total_dof, const int ndim, const int dof_node,
		     const int n_elem,const int n_load, const int n_pre_disp, const int nnode_ele, const arma::mat& coords,
		     const arma::imat& elem_node,const arma::mat& elem_stiff, const arma::mat& elem_load,
		     const arma::mat& elem_area, const arma::imat& force_node,
		     const arma::colvec& force_val, const arma::imat& disp_node,const arma::colvec& disp_val,
		     const int& n_trac, const arma::imat& trac_ele, const arma::mat& trac_val,
		     const int& Ng, const int& ShapeOrder, const int& Model2D,
		     const arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, arma::mat& Kfp,
		     arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   arma::colvec& Up );


void ElementAssemble( const int edof, const int i_elem,  const int nnode_ele,
		const int Ng, const int ShapeOrder, const int ndim, const int& Model2D, 
		const arma::mat& coords, const arma::imat& elem_node,
		const arma::mat& elem_stiff, const arma::mat& elem_load, const arma::mat& elem_area,
		arma::mat& kel, arma::colvec& pel);

void GetMaterialMatrix(const int& Model2D, const int& i_elem, const arma::mat& elem_stiff, arma::mat& k);

void AssembleGlobalStiffness(const int& i_elem, const int& nnode_ele, const int& dof_node,
				const arma::imat& elem_node, const arma::mat& kel, const arma::colvec& pel, 
				const arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
				arma::mat& Kfp, arma::colvec& Pf,  arma::colvec& Pp);

void AssembleGlobalForceVector( const int& n_load, const arma::imat& force_node, 
				const arma::colvec& force_val, const arma::imat& eq_num,  arma::colvec& Pf );


void AssemblePrescribedDisplacement( const int& n_pre_disp, const arma::imat& disp_node, 
				     const arma::colvec& disp_val,  const arma::imat& eq_num, arma::colvec& Up );

void GaussQuadrature(const int& Ng, arma::colvec& rg, arma::colvec& wg);


void Quad2DShapeFunctions(const int& ShapeOrder, const arma::colvec& rvec, arma::rowvec& Nhat, arma::mat& DNhat);


void ElementSurfaceTraction( const int edof, const int i,  const int nnode_ele,
		const int Ng, const int ShapeOrder, const int ndim, const arma::mat& coords, const arma::imat& elem_node,
		const arma::imat& trac_ele, double mag, double x_component, double y_component,
		arma::mat& kel, arma::colvec& pel);


void AssemblePrescribedTraction( const int edof, const int nnode_ele, const int dof_node,
		const int Ng, const int ShapeOrder, const int ndim, const arma::mat& coords, const arma::imat& elem_node,
		const arma::mat& elem_stiff, const arma::mat& elem_load, const arma::mat& elem_area,
		const int& n_trac, const arma::imat& trac_ele, const arma::mat& trac_val,
		const arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, arma::mat& Kfp,
		arma::colvec& Pf,  arma::colvec& Pp );

void SolveModule( const int n_node, const int n_dof, const int total_dof,const int dof_node,
		  const arma::imat& eq_num, arma::mat& Kff, arma::mat& Kpp, arma::mat& Kpf, 
		  arma::mat& Kfp,  arma::colvec& Pf,  arma::colvec& Pp, arma::colvec& Uf,   
		  arma::colvec& Up,  arma::mat& Uur,   arma::mat& Pur );

void EvaluateFieldGradient( const int nnode_ele, const int n_node, const int n_elem, const int dof_node,
		const int Ng, const int ShapeOrder, const int Model2D, const int ndim, const arma::mat& coords, 
		const arma::imat& elem_node, const arma::mat& elem_stiff, const arma::mat& Uur,
		arma::mat& StrainAtIntegrationPoints, arma::mat& StressAtIntegrationPoints,
		arma::mat& TpAtIntegrationPoints, arma::mat& VMAtIntegrationPoints,
		arma::mat& StrainAtCentroid, arma::mat& StressAtCentroid, arma::mat& TpAtCentroid,
		arma::mat& StrainAtNodes, arma::mat& StressAtNodes, arma::mat& TpAtNodes, arma::mat&  VMAtNodes);
		
void GetElementFluxVector(const int i_elem,  const int nnode_ele, const int dof_node,
		const int Ng, const int ShapeOrder, const int Model2D, const int ndim, const arma::mat& coords, const arma::imat& elem_node,
		const arma::mat& elem_stiff,const int location, const arma::mat& Uur,
		arma::mat& stress, arma::mat& strain);

void PrintEQNUM(const arma::imat& eq_num);

void PrintMatrices(const int& n_dof, const int& total_dof, arma::mat& Kff,
    arma::mat& Kpp, arma::mat& Kpf,  arma::mat& Kfp);

void PrintSolution(arma::colvec& Uf, arma::colvec& Pp,  arma::mat& Uur,   arma::mat& Pur);

void PrintPostProcessingResults(arma::mat& StrainAtIntegrationPoints, arma::mat& StressAtIntegrationPoints,
        arma::mat& TpAtIntegrationPoints, arma::mat& VMAtIntegrationPoints,
        arma::mat& StrainAtCentroid, arma::mat& StressAtCentroid, arma::mat& TpAtCentroid,
        arma::mat& StrainAtNodes, arma::mat& StressAtNodes, arma::mat& TpAtNodes, arma::mat&  VMAtNodes);
