/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2019 at the University of Edinburgh    */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**@file util/HighsSort.h
 * @brief Sorting routines for HiGHS
 * @author Julian Hall, Ivet Galabova, Qi Huangfu and Michael Feldmeier
 */
#ifndef UTIL_HIGHSSORT_H_
#define UTIL_HIGHSSORT_H_

/**
 * @brief Sort values[1..n] of an array by increasing value
 */
void maxheapsort(int* heap_v,  //!< Int values to be sorted
                 int n         //!< Number of values to be sorted
);
/**
 * @brief Sort values[1..n] of an array by increasing value with corresponding
 * indices
 */
void maxheapsort(double* heap_v,  //!< Values to be sorted
                 int* heap_i,     //!< Indices corrresponding to (sorted) values
                 int n            //!< Number of values to be sorted
);
/**
 * @brief Build a value heap for sorting values[1..n] of an array by increasing
 * value
 */
void build_maxheap(int* heap_v,  //!< Int values to be sorted
                   int n         //!< Number of values to be sorted
);
/**
 * @brief Build a value-index heap for sorting values[1..n] of an array by
 * increasing value
 */
void build_maxheap(double* heap_v,  //!< Values to be sorted
                   int* heap_i,  //!< Indices corrresponding to (sorted) values
                   int n         //!< Number of values to be sorted
);
/**
 * @brief Sort by increasing value a heap built with build_maxheap
 */
void max_heapsort(int* heap_v,  //!< Int values to be sorted
                  int n         //!< Number of values to be sorted
);
/**
 * @brief Sort by increasing value a heap built with build_maxheap
 */
void max_heapsort(double* heap_v,  //!< Values to be sorted
                  int* heap_i,  //!< Indices corrresponding to (sorted) values
                  int n         //!< Number of values to be sorted
);
/**
 * @brief Heapify function for sorting by increasing value
 */
void max_heapify(int* heap_v, int i, int n);

/**
 * @brief Heapify function for sorting by increasing value
 */
void max_heapify(double* heap_v, int* heap_i, int i, int n);

/**
 * @brief Check that a set of integers is in increasing order and in bounds
 */
bool increasing_set_ok(const int* set, const int set_num_entries,
                       const int set_entry_lower, const int set_entry_upper);

/**
 * @brief Check that a set of doubles is in increasing order and in bounds
 */
bool increasing_set_ok(const double* set, const int set_num_entries,
                       const double set_entry_lower,
                       const double set_entry_upper);

#endif /* UTIL_HIGHSSORT_H_ */
