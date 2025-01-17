/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file io/HighsIO.h
 * @brief IO methods for HiGHS - currently just print/log messages
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef HIGHS_IO_H
#define HIGHS_IO_H

#include "lp_data/HighsLp.h"

struct HighsOptions;

/**
 * @brief IO methods for HiGHS - currently just print/log messages
 */
enum class HighsMessageType { INFO, WARNING, ERROR };
const char* const HighsMessageTypeTag[] = {"INFO", "WARNING", "ERROR"};

/**
 * @brief Used to direct printed output to FILE* output, according
 * to whether the level bit is set in messageLevel
 */
void HighsPrintMessage(
    unsigned int level,  //!< The message level: Use | operator to display at
                         //!< level NONE, VERBOSE, DETAILED, MINIMAL
    const char* format,  //!< Printing format: must contain exactly one "\n" at
                         //!< end of format
    ...);

/**
 * @brief Used to direct _single-line_ logging output to FILE* logfile,
 * with timestamp and message type notification
 */
void HighsLogMessage(HighsMessageType type,  //!< The message type
                     const char* format,  //!< Printing format: must not contain
                                          //!< "\n", even at the end of format
                     ...);

/*
 * @brief sets the file used for HighsLogMessage
 */
void HighsSetLogfile(FILE* logfile  //!< The output file: default stdout
);

/*
 * @brief sets the file used for HighsPrintMessage
 */
void HighsSetOutput(FILE* output  //!< The output file: default stdout
);

/*
 * @brief sets the level used for HighsPrintMessage
 */
void HighsSetMessagelevel(
    unsigned int
        level  //!< The message level: Use | operator to display at level NONE,
               //!< VERBOSE, DETAILED, MINIMAL. default NONE
);

/*
 * @brief sets the callbacks used to print output and and log
 *
 * Set to NULL to reset to default, which is to print to logfile and output file
 */
void HighsSetMessageCallback(
    void (*printmsgcb_)(unsigned int level, const char* msg, void* msgcb_data),
    void (*logmsgcb_)(HighsMessageType type, const char* msg, void* msgcb_data),
    void* msgcb_data_);

/*
 * @brief sets output options
 */
void HighsSetIO(HighsOptions& options  //!< the options
);

#endif
