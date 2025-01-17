/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file lp_data/HighsLpUtils.h
 * @brief Class-independent utilities for HiGHS
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef LP_DATA_HIGHSLPUTILS_H_
#define LP_DATA_HIGHSLPUTILS_H_

#include "HConfig.h"
#include "io/Filereader.h"
#include "lp_data/HighsLp.h"
#include "lp_data/HighsOptions.h"
#include "lp_data/HighsStatus.h"

class HighsLp;

// Methods taking HighsLp as an argument
HighsStatus checkLp(const HighsLp& lp);

HighsStatus assessLp(HighsLp& lp, const HighsOptions& options,
                     const bool normalise);

HighsStatus assessLpDimensions(const HighsLp& lp);

HighsStatus assess_costs(const int col_ix_os, const int mask_num_col,
                         const bool interval, const int from_col,
                         const int to_col, const bool set,
                         const int num_set_entries, const int* col_set,
                         const bool mask, const int* col_mask,
                         const double* usr_col_cost,
                         const double infinite_cost);

HighsStatus assessBounds(const char* type, const int ix_os,
                         const int mask_num_ix, const bool interval,
                         const int from_ix, const int to_ix, const bool set,
                         const int num_set_entries, const int* ix_set,
                         const bool mask, const int* ix_mask, double* usr_lower,
                         double* usr_upper, const double infinite_bound,
                         const bool normalise);

HighsStatus assessMatrix(const int vec_dim, const int from_ix, const int to_ix,
                         const int num_vec, int& num_nz, int* Xstart,
                         int* Xindex, double* Xvalue,
                         const double small_matrix_value,
                         const double large_matrix_value, bool normalise);

HighsStatus scaleLpColCosts(HighsLp& lp, vector<double>& colScale,
                            const bool interval, const int from_col,
                            const int to_col, const bool set,
                            const int num_set_entries, const int* col_set,
                            const bool mask, const int* col_mask);

HighsStatus scaleLpColBounds(HighsLp& lp, vector<double>& colScale,
                             const bool interval, const int from_col,
                             const int to_col, const bool set,
                             const int num_set_entries, const int* col_set,
                             const bool mask, const int* col_mask);

HighsStatus scaleLpRowBounds(HighsLp& lp, vector<double>& rowScale,
                             const bool interval, const int from_row,
                             const int to_row, const bool set,
                             const int num_set_entries, const int* row_set,
                             const bool mask, const int* row_mask);

HighsStatus addLpCols(HighsLp& lp, const int num_new_col,
                      const double* XcolCost, const double* XcolLower,
                      const double* XcolUpper, const int num_new_nz,
                      const int* XAstart, const int* XAindex,
                      const double* XAvalue, const HighsOptions& options);

HighsStatus appendLpCols(HighsLp& lp, const int num_new_col,
                         const double* XcolCost, const double* XcolLower,
                         const double* XcolUpper, const int num_new_nz,
                         const int* XAstart, const int* XAindex,
                         const double* XAvalue, const HighsOptions& options,
                         const bool valid_matrix);

HighsStatus appendColsToLpVectors(HighsLp& lp, const int num_new_col,
                                  const double* XcolCost,
                                  const double* colLower,
                                  const double* XcolUpper);

HighsStatus appendColsToLpMatrix(HighsLp& lp, const int num_new_col,
                                 const int num_new_nz, const int* XAstart,
                                 const int* XAindex, const double* XAvalue);

HighsStatus addLpRows(HighsLp& lp, const int num_new_row,
                      const double* XrowLower, const double* XrowUpper,
                      const int num_new_nz, const int* XARstart,
                      const int* XARindex, const double* XARvalue,
                      const HighsOptions& options);

HighsStatus appendLpRows(HighsLp& lp, const int num_new_row,
                         const double* XrowLower, const double* XrowUpper,
                         const int num_new_nz, const int* XARstart,
                         const int* XARindex, const double* XARvalue,
                         const HighsOptions& options, bool valid_matrix);

HighsStatus appendRowsToLpVectors(HighsLp& lp, const int num_new_row,
                                  const double* XrowLower,
                                  const double* XrowUpper);

HighsStatus appendRowsToLpMatrix(HighsLp& lp, const int num_new_row,
                                 const int num_new_nz, const int* XARstart,
                                 const int* XARindex, const double* XARvalue);

HighsStatus deleteLpCols(HighsLp& lp, const bool interval, const int from_col,
                         const int to_col, const bool set,
                         const int num_set_entries, const int* col_set,
                         const bool mask, int* col_mask,
                         const bool valid_matrix);

HighsStatus deleteColsFromLpVectors(HighsLp& lp, int& new_num_col,
                                    const bool interval, const int from_col,
                                    const int to_col, const bool set,
                                    const int num_set_entries,
                                    const int* col_set, const bool mask,
                                    const int* col_mask);

HighsStatus deleteColsFromLpMatrix(HighsLp& lp, const bool interval,
                                   const int from_col, const int to_col,
                                   const bool set, const int num_set_entries,
                                   const int* col_set, const bool mask,
                                   int* col_mask);

HighsStatus deleteLpRows(HighsLp& lp, const bool interval, const int from_row,
                         const int to_row, const bool set,
                         const int num_set_entries, const int* row_set,
                         const bool mask, int* row_mask,
                         const bool valid_matrix);

HighsStatus deleteRowsFromLpVectors(HighsLp& lp, int& new_num_row,
                                    const bool interval, const int from_row,
                                    const int to_row, const bool set,
                                    const int num_set_entries,
                                    const int* row_set, const bool mask,
                                    const int* row_mask);

HighsStatus deleteRowsFromLpMatrix(HighsLp& lp, const bool interval,
                                   const int from_row, const int to_row,
                                   const bool set, const int num_set_entries,
                                   const int* row_set, const bool mask,
                                   int* row_mask);

HighsStatus changeLpMatrixCoefficient(HighsLp& lp, const int row, const int col,
                                      const double new_value);

HighsStatus changeLpCosts(HighsLp& lp, const bool interval, const int from_col,
                          const int to_col, const bool set,
                          const int num_set_entries, const int* col_set,
                          const bool mask, const int* col_mask,
                          const double* usr_col_cost,
                          const double infinite_cost);

HighsStatus changeLpColBounds(HighsLp& lp, const bool interval,
                              const int from_col, const int to_col,
                              const bool set, const int num_set_entries,
                              const int* col_set, const bool mask,
                              const int* col_mask, const double* usr_col_lower,
                              const double* usr_col_upper,
                              const double infinite_bound);

HighsStatus changeLpRowBounds(HighsLp& lp, const bool interval,
                              const int from_row, const int to_row,
                              const bool set, const int num_set_entries,
                              const int* row_set, const bool mask,
                              const int* row_mask, const double* usr_row_lower,
                              const double* usr_row_upper,
                              const double infinite_bound);

HighsStatus changeBounds(const char* type, double* lower, double* upper,
                         const int mask_num_ix, const bool interval,
                         const int from_ix, const int to_ix, const bool set,
                         const int num_set_entries, const int* ix_set,
                         const bool mask, const int* ix_mask,
                         const double* usr_lower, const double* usr_upper,
                         const double infinite_bound);

/**
 * @brief Write out the LP as an MPS file
 */
FilewriterRetcode writeLpAsMPS(const char* filename, const HighsLp& lp, const bool free = true);

/**
 * @brief Report the data of an LP
 */
void reportLp(
    const HighsLp& lp,          //!< LP whose data are to be reported
    const int report_level = 0  //!< 0 => scalar [dimensions]; 1=> vector
                                //!< [costs/bounds]; 2 => vector+matrix
);
/**
 * @brief Report the brief data of an LP
 */
void reportLpBrief(const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
void reportLpDimensions(const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
void reportLpObjSense(const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
void reportLpColVectors(const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
void reportLpRowVectors(const HighsLp& lp  //!< LP whose data are to be reported
);
/**
 * @brief Report the data of an LP
 */
void reportLpColMatrix(const HighsLp& lp  //!< LP whose data are to be reported
);

void reportMatrix(const char* message, const int num_col, const int num_nz,
                  const int* start, const int* index, const double* value);

// Get the costs for a contiguous set of columns
HighsStatus getLpCosts(const HighsLp& lp, const int from_col, const int to_col,
                       double* XcolCost);

// Get the bounds for a contiguous set of columns
HighsStatus getLpColBounds(const HighsLp& lp, const int from_col,
                           const int to_col, double* XcolLower,
                           double* XcolUpper);

// Get the bounds for a contiguous set of rows
HighsStatus getLpRowBounds(const HighsLp& lp, const int from_row,
                           const int to_row, double* XrowLower,
                           double* XrowUpper);

HighsStatus getLpMatrixCoefficient(const HighsLp& lp, const int row,
                                   const int col, double* val);
#ifdef HiGHSDEV
// Analyse the data in an LP problem
void analyseLp(const HighsLp& lp, const char* message);
#endif

HighsBasis getSimplexBasis(const HighsLp& lp, const SimplexBasis& basis);

HighsStatus calculateRowValues(const HighsLp& lp, HighsSolution& solution);
HighsStatus calculateColDuals(const HighsLp& lp, HighsSolution& solution);
double calculateObjective(const HighsLp& lp, HighsSolution& solution);

HighsStatus assessIntervalSetMask(const int max_ix, const bool interval,
                                  const int from_ix, const int to_ix,
                                  const bool set, const int num_set_entries,
                                  const int* ix_set, const bool mask,
                                  const int* ix_mask, int& from_k, int& to_k);

void updateOutInIx(const int ix_dim, const bool interval, const int from_ix,
                   const int to_ix, const bool set, const int num_set_entries,
                   const int* ix_set, const bool mask, const int* ix_mask,
                   int& out_from_ix, int& out_to_ix, int& in_from_ix,
                   int& in_to_ix, int& current_set_entry);

bool isColDataNull(const double* usr_col_cost, const double* usr_col_lower,
                   const double* usr_col_upper);
bool isRowDataNull(const double* usr_row_lower, const double* usr_row_upper);
bool isMatrixDataNull(const int* usr_matrix_start, const int* usr_matrix_index,
                      const double* usr_matrix_value);

HighsLp transformIntoEqualityProblem(const HighsLp& lp);
HighsLp dualizeEqualityProblem(const HighsLp& lp);

void logPresolveReductions(const HighsLp& lp, const HighsLp& presolve_lp);

#endif  // LP_DATA_HIGHSLPUTILS_H_
