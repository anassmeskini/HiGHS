/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file io/FilereaderMps.cpp
 * @brief
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#include "io/FilereaderMps.h"
#include "io/HMPSIO.h"
#include "io/HMpsFF.h"
#include "lp_data/HighsLp.h"
#include "lp_data/HighsLpUtils.h"
#include "lp_data/HighsModelUtils.h"

FilereaderRetcode FilereaderMps::readModelFromFile(const HighsOptions& options,
                                                   HighsLp& model) {
  const char* filename = options.filename.c_str();

  // if free format parser
  // Parse file and return status.
  if (options.mps_parser_type == HighsMpsParserType::free) {
    HMpsFF parser{};
    FreeFormatParserReturnCode result = parser.loadProblem(filename, model);
    switch (result) {
      case FreeFormatParserReturnCode::SUCCESS:
        return FilereaderRetcode::OK;
      case FreeFormatParserReturnCode::PARSERERROR:
        return FilereaderRetcode::PARSERERROR;
      case FreeFormatParserReturnCode::FILENOTFOUND:
        return FilereaderRetcode::FILENOTFOUND;
      case FreeFormatParserReturnCode::FIXED_FORMAT:
	HighsLogMessage(HighsMessageType::WARNING, "Free format reader has detected row/col names with spaces: switching to fixed format parser");
        HighsPrintMessage(ML_DETAILED | ML_VERBOSE, "%s %s\n",
                          "Whitespaces encountered in row / col name.",
                          "Switching to fixed format parser.");
        break;
    }
  }

  // else use fixed format parser
  FilereaderRetcode return_code = readMPS(filename, -1, -1, model.numRow_, model.numCol_, model.numInt_,
					  model.sense_, model.offset_, model.Astart_, model.Aindex_, model.Avalue_,
					  model.colCost_, model.colLower_, model.colUpper_, model.rowLower_,
					  model.rowUpper_, model.integrality_, model.col_names_, model.row_names_,
					  options.keep_n_rows);
  if (namesWithSpaces(model.numCol_, model.col_names_)) {
    HighsLogMessage(HighsMessageType::WARNING, "Model has column names with spaces");
#ifdef HiGHSDEV
    namesWithSpaces(model.numCol_, model.col_names_, true);
#endif
  }
  if (namesWithSpaces(model.numRow_, model.row_names_)) {
    HighsLogMessage(HighsMessageType::WARNING, "Model has row names with spaces");
#ifdef HiGHSDEV
    namesWithSpaces(model.numRow_, model.row_names_, true);
#endif
  }
  return return_code;
}

FilewriterRetcode FilereaderMps::writeModelToFile(const char* filename,
                                                  HighsLp& model) {
  return writeLpAsMPS(filename, model);
}

FilereaderRetcode FilereaderMps::readModelFromFile(const char* filename,
                                                   HighsModelBuilder& model) {
  if (filename) {
  }  // surpress warning.
  if (model.getNumberOfVariables() > 0) {
  }  // surpress warning.
  return FilereaderRetcode::PARSERERROR;
}
