/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file simplex/HDualRHS.h
 * @brief Dual simplex optimality test for HiGHS
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef SIMPLEX_HDUALRHS_H_
#define SIMPLEX_HDUALRHS_H_

#include <vector>

#include "lp_data/HighsModelObject.h"

class HVector;

/**
 * @brief Dual simplex optimality test for HiGHS
 *
 * Performs the optimality test and some update primal/weight tasks
 */
class HDualRHS {
 public:
  HDualRHS(HighsModelObject& hmo) : workHMO(hmo) {}

  /**
   * @brief Defines space for Mark, Index and Array, EdWt and EdWtFull
   *
   * Mark (markers of primal infeasibilities?)
   * Index and Array (for ??)
   * EdWt (for gathered DSE weights)
   * EdWtFull (for scattered SED weights)
   */
  void setup();

  /**
   * @brief Choose the row index of a good variable to leave the basis (CHUZR)
   */
  void choose_normal(
      int* chIndex  //!< Row index of variable chosen to leave the basis
  );

  /**
   * @brief Choose a set of row indices of good variables to leave the basis
   * (Multiple CHUZR)
   */
  void choose_multi_global(int* chIndex,  //!< Set of indices of chosen rows
                           int* chCount,  //!< Number of chosen rows
                           int chLimit    //!< Limit on number of of chosen rows
  );

  /**
   * @brief Choose a set of row indices of good variables to leave the basis
   * (Multiple CHUZR)
   */
  void choose_multi_HGauto(int* chIndex,  //!< Set of indices of chosen rows
                           int* chCount,  //!< Number of chosen rows
                           int chLimit    //!< Limit on number of of chosen rows
  );

  /**
   * @brief Choose a set of row indices of good variables to leave the basis
   * (Multiple CHUZR)
   */
  void choose_multi_HGpart(int* chIndex,  //!< Set of indices of chosen rows
                           int* chCount,  //!< Number of chosen rows
                           int chLimit    //!< Limit on number of of chosen rows
  );

  /**
   * @brief Update the primal values by adding a multiple of a given std::vector
   */
  void update_primal(
      HVector* column,  //!< Column to add into primal values
      double theta      //!< Multiple of column to add into primal values
  );

  /**
   * @brief Update the DSE weights
   */
  void update_weight_DSE(
      HVector* column,         //!< Pivotal column
      double DSE_wt_o_rowOut,  //!< (Edge weight of leaving row)/alpha^2
      double Kai,              //!< -2/alpha
      double* dse              //!< DSE std::vector
  );
  /**
   * @brief Update the Devex weights
   */
  void update_weight_Dvx(
      HVector* column,        //!< Pivotal column
      double dvx_wt_o_rowOut  //!< max(1, (Edge weight of leaving row)/alpha^2)
  );
  /**
   * @brief Update the primal value for the row where the basis change has
   * occurred
   */
  void update_pivots(int iRow,     //!< row where the basis change has occurred
                     double value  //!< New primal value in this row
  );

  /**
   * @brief Update the list of primal infeasibilities using indices of primal
   * values which have changed
   */
  void update_infeasList(HVector* column  //!< Changes in primal values
  );

  /**
   * @brief Create the list of greatest primal infeasibilities for efficient
   * CHUZR
   */
  void create_infeasList(double columnDensity);
  /**
   * @brief Create the std::vector of primal infeasibilities
   *
   * TODO: Change the name of "workArray" to something clearer like
   * workInfeasArray!
   */
  void create_infeasArray();

  HighsModelObject& workHMO;  //!< Local copy of pointer to model

  double workCutoff;  //!< Limit for row to be in list with greatest primal
                      //!< infeasibilities
  int workCount;      //!< Number of rows in list with greatest primal
                      //!< infeasibilities
  std::vector<char> workMark;  //!< Flag set if row is in list of those with
                               //!< greatest primal infeasibilities
  std::vector<int>
      workIndex;  //!< List of rows with greatest primal infeasibilities
  std::vector<double> workArray;     //!< Vector of all primal infeasiblities
  std::vector<double> workEdWt;      //!< DSE or Dvx weight
  std::vector<double> workEdWtFull;  //!< Full-length std::vector where weights
                                     //!< are scattered during INVERT

  int partNum;
  int partNumRow;
  int partNumCol;
  int partNumCut;
  int partSwitch;
  std::vector<int> workPartition;
};

#endif /* SIMPLEX_HDUALRHS_H_ */
