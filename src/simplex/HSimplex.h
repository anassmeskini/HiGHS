/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file lp_data/HSimplex.h
 * @brief
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef SIMPLEX_HSIMPLEX_H_
#define SIMPLEX_HSIMPLEX_H_

#include "HConfig.h"
#include "lp_data/HighsModelObject.h"
#include "lp_data/HighsOptions.h"

// Methods not requiring HighsModelObject 

void add_cols_to_lp_vectors(
			    HighsLp &lp,
			    int XnumNewCol,
			    const double *XcolCost,
			    const double *colLower,
			    const double *XcolUpper
			    );

void add_cols_to_lp_matrix(
			   HighsLp &lp,
			   int XnumNewCol,
			   int XnumNewNZ,
			   const int *XAstart,
			   const int *XAindex,
			   const double *XAvalue
			   );

void add_rows_to_lp_vectors(HighsLp &lp,
			    int XnumNewRow,
			    const double *XrowLower,
			    const double *XrowUpper
			    );

void add_rows_to_lp_matrix(HighsLp &lp,
			   int XnumNewRow,
			   int XnumNewNZ,
			   const int *XARstart,
			   const int *XARindex,
			   const double *XARvalue
			   );

void extend_basis_with_nonbasic_cols(
				     HighsLp &lp,
				     HighsBasis &basis,
				     int XnumNewCol
				     );

void extend_basis_with_basic_rows(
				  HighsLp &lp,
				  HighsBasis &basis,
				  int XnumNewRow
				  );

void del_cols_from_lp_vectors(
			    HighsLp &lp,
			    int XfromCol,
			    int XtoCol
			    );

void del_cols_from_lp_matrix(
			     HighsLp &lp,
			     int XfromCol,
			     int XtoCol
			   );

void del_rows_from_lp_vectors(
			    HighsLp &lp,
			    int XfromRow,
			    int XtoRow
			    );

void del_rows_from_lp_matrix(
			     HighsLp &lp,
			     int XfromRow,
			     int XtoRow
			   );

bool nonbasic_flag_basic_index_ok(
				  HighsLp &lp,
				  HighsBasis &basis
				  );
#ifdef HiGHSDEV
void report_basis(
		  HighsLp &lp,
		  HighsBasis &basis
		  );
#endif

/*
// Increment iteration count (here!) and (possibly) store the pivots for
// debugging NLA
void record_pivots(int columnIn, int columnOut, double alpha) {
  // NB This is where the iteration count is updated!
  if (columnIn >= 0) simplex_info_.iteration_count++;
#ifdef HiGHSDEV
  historyColumnIn.push_back(columnIn);
  historyColumnOut.push_back(columnOut);
  historyAlpha.push_back(alpha);
#endif
}
#ifdef HiGHSDEV
// Store and write out the pivots for debugging NLA
void writePivots(const char* suffix) {
  string filename = "z-" + simplex_lp_->model_name_ + "-" + suffix;
  ofstream output(filename.c_str());
  int count = historyColumnIn.size();
  double current_run_highs_time = timer_->readRunHighsClock();
  output << simplex_lp_->model_name_ << " " << count << "\t" <<
current_run_highs_time << endl; output << setprecision(12); for (int i = 0; i <
count; i++) { output << historyColumnIn[i] << "\t"; output <<
historyColumnOut[i] << "\t"; output << historyAlpha[i] << endl;
  }
  output.close();
}
#endif
*/
void options(
	     HighsModelObject &highs_model_object, //!< Model object in which simplex options are to be set
	     const HighsOptions &opt               //!< HiGHS options to be used to set simplex options
	     );

void invalidate_simplex_lp_data(
				HighsSimplexLpStatus &simplex_lp_status// !< Status of simplex LP whose data are to be invalidated
				);

void invalidate_simplex_lp(
			   HighsSimplexLpStatus &simplex_lp_status// !< Status of simplex LP to be invalidated
);

void update_simplex_lp_status(
			      HighsSimplexLpStatus &simplex_lp_status,// !< Status of simplex LP to be updated
			      LpAction action// !< Action prompting update
			      );

void report_simplex_lp_status(
			      HighsSimplexLpStatus &simplex_lp_status// !< Status of simplex LP to be reported
			      );

void compute_dual_objective_value(
				  HighsModelObject &highs_model_object,
                                  int phase = 2);

void initialise_simplex_lp_random_vectors(
					  HighsModelObject &highs_model
					  );

// TRANSPOSE:

void transpose_simplex_lp(
			  HighsModelObject &highs_model
			  );

void scaleHighsModelInit(
			 HighsModelObject &highs_model
			 );

void scaleCosts(
		HighsModelObject &highs_model
		);

void scale_simplex_lp(
		      HighsModelObject &highs_model
		      );

void permute_simplex_lp(
			HighsModelObject &highs_model
			);

// TIGHTEN:

void tighten_simplex_lp(
			HighsModelObject &highs_model
			);

void initialise_basic_index(
			    HighsModelObject &highs_model_object
			    );

void allocate_work_and_base_arrays(
				   HighsModelObject &highs_model_object
				   );

void initialise_from_nonbasic(
			      HighsModelObject &highs_model_object
			      );

void replace_from_nonbasic(
			   HighsModelObject &highs_model_object
			   );

void initialise_with_logical_basis(
				   HighsModelObject &highs_model_object
				   );

void initialise_value_from_nonbasic(
				    HighsModelObject &highs_model_object,
                                    int firstvar,
				    int lastvar
				    );

void initialise_value(
		      HighsModelObject &highs_model_object
		      );

void initialise_phase2_col_bound(
				 HighsModelObject &highs_model_object,
                                 int firstcol,
				 int lastcol
				 );

void initialise_phase2_row_bound(
				 HighsModelObject &highs_model_object,
                                 int firstrow,
				 int lastrow);

void initialise_bound(
		      HighsModelObject &highs_model_object,
		      int phase = 2);

void initialise_phase2_col_cost(
				HighsModelObject &highs_model_object,
                                int firstcol,
				int lastcol);

void initialise_phase2_row_cost(
				HighsModelObject &highs_model_object,
                                int firstrow,
				int lastrow);

void initialise_cost(
		     HighsModelObject &highs_model_object,
		     int perturb = 0);

int get_nonbasicMove(
		     HighsModelObject &highs_model_object,
		     int var);

void populate_work_arrays(
			  HighsModelObject &highs_model_object
			  );

void replace_with_logical_basis(
				HighsModelObject &highs_model_object
				);

void replace_with_new_basis(
			    HighsModelObject &highs_model_object,
                            const int *XbasicIndex
			    );

void setup_num_basic_logicals(
			      HighsModelObject &highs_model_object
			      );

void setup_for_solve(
		     HighsModelObject &highs_model_object
		     );

bool work_arrays_ok(
		    HighsModelObject &highs_model_object,
		    int phase
		    );

bool one_nonbasic_move_vs_work_arrays_ok(
					 HighsModelObject &highs_model_object,
                                         int var
					 );

bool all_nonbasic_move_vs_work_arrays_ok(
					 HighsModelObject &highs_model_object
					 );

bool ok_to_solve(
		 HighsModelObject &highs_model_object,
		 int level,
		 int phase
		 );

void flip_bound(
		HighsModelObject &highs_model_object,
		int iCol
		);

int compute_factor(
		   HighsModelObject &highs_model_object
		   );

void compute_primal(
		    HighsModelObject &highs_model_object
		    );

void compute_dual(
		  HighsModelObject &highs_model_object
		  );

void correct_dual(
		  HighsModelObject &highs_model_object,
                  int *free_infeasibility_count
		  );

void compute_dual_infeasible_in_dual(
				     HighsModelObject &highs_model_object,
                                     int *dual_infeasibility_count
				     );

void compute_dual_infeasible_in_primal(
				       HighsModelObject &highs_model_object,
                                       int *dual_infeasibility_count
				       );

// Compute the primal values (in baseValue) and set the lower and upper bounds
// of basic variables
int set_source_out_from_bound(
			      HighsModelObject &highs_model_object,
                              const int column_out
			      );

double
compute_primal_objective_function_value(
					HighsModelObject &highs_model_object
					);

// Record the shift in the cost of a particular column
void shift_cost(
		  HighsModelObject &highs_model_object,
		  int iCol,
                  double amount
		  );

// Undo the shift in the cost of a particular column
void shift_back(
		  HighsModelObject &highs_model_object,
		  int iCol);

// The major model updates. Factor calls factor.update; Matrix
// calls matrix.update; updatePivots does everything---and is
// called from the likes of HDual::updatePivots
void update_factor(
		   HighsModelObject &highs_model_object,
		   HVector *column,
                   HVector *row_ep,
		   int *iRow,
		   int *hint
		   );

void update_pivots(
		   HighsModelObject &highs_model_object,
		   int columnIn,
                   int rowOut,
		   int sourceOut
		   );

void update_matrix(HighsModelObject &highs_model_object,
		   int columnIn,
                   int columnOut
		   );

#ifdef HiGHSDEV
void util_analyse_lp_solution(
			      HighsModelObject &highs_model_object
			      );
#endif

void report_iteration_count_dual_objective_value(
						 HighsModelObject &highs_model_object,
						 int i_v
						 );

#endif // SIMPLEX_HSIMPLEX_H_
