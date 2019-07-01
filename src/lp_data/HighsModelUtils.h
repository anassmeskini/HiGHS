/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file lp_data/HighsModelUtils.h
 * @brief Class-independent utilities for HiGHS
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef LP_DATA_HIGHSMODELUTILS_H_
#define LP_DATA_HIGHSMODELUTILS_H_

#include "HConfig.h"
#include "lp_data/HighsStatus.h"

#ifdef HiGHSDEV
// Analyse lower and upper bounds of a model
void analyseModelBounds(const char* message, int numBd,
                        const std::vector<double>& lower,
                        const std::vector<double>& upper);
#endif
void reportModelBoundSol(const bool columns, const int dim,
                         const std::vector<double>& lower,
                         const std::vector<double>& upper,
                         const std::vector<std::string>& names,
                         const std::vector<double>& primal,
                         const std::vector<double>& dual,
                         const std::vector<HighsBasisStatus>& status);
int maxNameLength(const int num_name, const std::vector<std::string>& names);

#endif
