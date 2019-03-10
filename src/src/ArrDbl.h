#ifndef ARRDBL_H
#define ARRDBL_H

/**
 * @file ArrDbl.h
 * @brief Array of doubles
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 3 December 2014\n
 * Last modified on 6 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <vector>
#include <string>

//-----------------------------------------------------------------------------

/// Array of doubles
class ArrDbl
{
private:

    /// Number of values in v
    size_t n;

    /// Array of values v
    std::vector<double> v;

public:

    /// Default constructor
    ArrDbl(void);

    /**
     * @brief Parametrized constructor:
     * sets array size to nin and fills the array with zeroes
     * @param[in] nin Number of array elements
     */
    explicit ArrDbl(const size_t nin);

    /// Destructor
    ~ArrDbl(void);

    /** @brief Releases all array memory */
    void clear(void);

    /**
     * @brief Getter for number of values (ArrDbl::n)
     * @return Size of the array
     */
    size_t size(void) const;

    /** 
     * @brief Reserves memory for nin array elements
     * @param[in] nin Number of array elements
     */
    void reserve(const size_t nin);

    /**
     * @brief Adds a given number to the end of the array
     * @param[in] x Value to be added to the end of the array
     */
    void push_back(const double x);

    /**
     * @brief Getter for i-th component (ArrDbl::v)
     * @param[in] i v-index
     * @return \f$v_i\f$, throws an exception if i is out of range
     */
    double at(const size_t i) const;

    /**
     * @brief Setter for i-th component (ArrDbl::v)
     * @param[in] i v-index
     * @return \f$v_i\f$, throws an exception if i is out of range
     */
    double & at(const size_t i);

    /**
     * @brief Getter for i-th component (ArrDbl::v)
     * @param[in] i v-index (must be a valid index)
     * @return \f$v_i\f$
     */
    double operator [](const size_t i) const;

    /**
     * @brief Setter for i-th component (ArrDbl::v)
     * @param[in] i v-index (must be a valid index)
     * @return \f$v_i\f$
     */
    double & operator [](const size_t i);

    /**
     * @brief Absolute difference between two arrays
     * @param[in] o ArrDbl
     * @return See Definition
     */
    double abs_diff(const ArrDbl &o) const;

    /**
     * @brief String representation of an ArrDbl object
     * @return String representation of *this
     */
    std::string to_string(void) const;

    /**
     * @brief Writes array data to a file, following a header string
     * @param[in] fname Name of output file
     * @param[in] header String written to fname before array data
     */
    void to_file(const std::string &fname,
                 const std::string &header) const;

    /**
     * @brief Resizes the array and fills it with a constant
     * @param[in] nin New array size
     * @param[in] f Fill value
     */
    void assign(const size_t nin, const double f);

    /**
     * @brief Resizes the array and fills it with a constant
     * @param[in] nin New array size
     * @param[in] f Fill value
     */
    void assign(const size_t nin, const float f);

    /**
     * @brief Resizes the array and fills it with a constant
     * @param[in] nin New array size
     * @param[in] f Fill value
     */
    void assign(const size_t nin, const int f);

    /**
     * @brief Fills the array with a constant
     * @param[in] f Fill value
     */
    void fill(const double f);

    /**
     * @brief Fills the array with a constant
     * @param[in] f Fill value
     */
    void fill(const float f);

    /**
     * @brief Fills the array with a constant
     * @param[in] f Fill value
     */
    void fill(const int f);

    /**
     * @brief Unary plus
     * @return \f$\forall i,\;+t_i\f$
     */
    const ArrDbl operator + (void) const;

    /**
     * @brief Unary minus
     * @return \f$\forall i,\;-t_i\f$
     */
    const ArrDbl operator - (void) const;

    /**
     * @brief Adds to an array
     * @param[in] a ArrDbl
     * @return \f$\forall i,\;t_i \rightarrow t_i + a_i\f$
     */
    ArrDbl & operator += (const ArrDbl &a);

    /**
     * @brief Subtracts from an array
     * @param[in] a ArrDbl
     * @return \f$\forall i,\;t_i \rightarrow t_i - a_i\f$
     */
    ArrDbl & operator -= (const ArrDbl &a);

    /**
     * @brief Multiplies an array element by element
     * @param[in] a ArrDbl
     * @return \f$\forall i,\;t_i \rightarrow t_i\,a_i\f$
     */
    ArrDbl & operator *= (const ArrDbl &a);

    /**
     * @brief Divides an array element by element
     * @param[in] a ArrDbl
     * @return \f$\forall i,\;t_i \rightarrow t_i\;/\;a_i\f$;
     *         \f$t_i \rightarrow \infty\f$ for those i's,
     *         where \f$a_i=0\f$
     */
    ArrDbl & operator /= (const ArrDbl &a);

    /**
     * @brief Elemental array addition
     * @param[in] a ArrDbl
     * @return \f$\forall i,\;t_i \rightarrow t_i\;+\;a_i\f$
     */
    const ArrDbl operator + (const ArrDbl &a) const;

    /**
     * @brief Elemental array subtraction
     * @param[in] a ArrDbl
     * @return \f$\forall i,\;t_i \rightarrow t_i\;-\;a_i\f$
     */
    const ArrDbl operator - (const ArrDbl &a) const;

    /**
     * @brief Elemental array multiplication
     * @param[in] a ArrDbl
     * @return \f$\forall i,\;t_i \rightarrow t_i\;a_i\f$
     */
    const ArrDbl operator * (const ArrDbl &a) const;

    /**
     * @brief Elemental array division
     * @param[in] a ArrDbl
     * @return \f$\forall i,\;t_i \rightarrow t_i\;/\;a_i\f$;
     *         \f$t_i \rightarrow \infty\f$ for those i's,
     *         where \f$a_i=0\f$
     */
    const ArrDbl operator / (const ArrDbl &a) const;

    /**
     * @brief Adds a scalar to an array
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i + f\f$
     */
    ArrDbl & operator += (const double f);

    /**
     * @brief Adds a scalar to an array
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i + f\f$
     */
    ArrDbl & operator += (const float f);

    /**
     * @brief Adds a scalar to an array
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i + f\f$
     */
    ArrDbl & operator += (const int f);

    /**
     * @brief Subtracts a scalar from an array
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i - f\f$
     */
    ArrDbl & operator -= (const double f);

    /**
     * @brief Subtracts a scalar from an array
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i - f\f$
     */
    ArrDbl & operator -= (const float f);

    /**
     * @brief Subtracts a scalar from an array
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i - f\f$
     */
    ArrDbl & operator -= (const int f);

    /**
     * @brief Multiplies an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i\,f\f$
     */
    ArrDbl & operator *= (const double f);

    /**
     * @brief Multiplies an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i\,f\f$
     */
    ArrDbl & operator *= (const float f);

    /**
     * @brief Multiplies an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i\,f\f$
     */
    ArrDbl & operator *= (const int f);

    /**
     * @brief Divides an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i\;/\;f\f$;
     *         \f$t_i \rightarrow \infty\f$, if \f$f=0\f$
     */
    ArrDbl & operator /= (const double f);

    /**
     * @brief Divides an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i\;/\;f\f$;
     *         \f$t_i \rightarrow \infty\f$, if \f$f=0\f$
     */
    ArrDbl & operator /= (const float f);

    /**
     * @brief Divides an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\;t_i \rightarrow t_i\;/\;f\f$;
     *         \f$t_i \rightarrow \infty\f$, if \f$f=0\f$
     */
    ArrDbl & operator /= (const int f);

    /**
     * @brief Adds a scalar to an array
     * @param[in] f Scalar
     * @return \f$\forall i, t_i + f\f$
     */
    const ArrDbl operator + (const double f) const;

    /**
     * @brief Adds a scalar to an array
     * @param[in] f Scalar
     * @return \f$\forall i, t_i + f\f$
     */
    const ArrDbl operator + (const float f) const;

    /**
     * @brief Adds a scalar to an array
     * @param[in] f Scalar
     * @return \f$\forall i, t_i + f\f$
     */
    const ArrDbl operator + (const int f) const;

    /**
     * @brief Subtracts a scalar from an array
     * @param[in] f Scalar
     * @return \f$\forall i,\; t_i - f\f$
     */
    const ArrDbl operator - (const double f) const;

    /**
     * @brief Subtracts a scalar from an array
     * @param[in] f Scalar
     * @return \f$\forall i,\; t_i - f\f$
     */
    const ArrDbl operator - (const float f) const;

    /**
     * @brief Subtracts a scalar from an array
     * @param[in] f Scalar
     * @return \f$\forall i,\; t_i - f\f$
     */
    const ArrDbl operator - (const int f) const;

    /**
     * @brief Multiplies an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\; t_i\,f\f$
     */
    const ArrDbl operator * (const double f) const;

    /**
     * @brief Multiplies an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\; t_i\,f\f$
     */
    const ArrDbl operator * (const float f) const;

    /**
     * @brief Multiplies an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\; t_i\,f\f$
     */
    const ArrDbl operator * (const int f) const;

    /**
     * @brief Divides an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\; t_i\;/\;f\f$;
     *         \f$\infty\f$, if \f$f=0\f$
     */
    const ArrDbl operator / (const double f) const;

    /**
     * @brief Divides an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\; t_i\;/\;f\f$;
     *         \f$\infty\f$, if \f$f=0\f$
     */
    const ArrDbl operator / (const float f) const;

    /**
     * @brief Divides an array by a scalar
     * @param[in] f Scalar
     * @return \f$\forall i,\; t_i\;/\;f\f$;
     *         \f$\infty\f$, if \f$f=0\f$
     */
    const ArrDbl operator / (const int f) const;

    /**
     * @brief Divides a scalar by an array
     * @param[in] f Scalar
     * @param[in] a ArrDbl
     * @return \f$\forall i,\;f\;/\;a_i\f$;
     *         \f$\infty\f$, for those i's where \f$a_i=0\f$
     */
    friend const ArrDbl operator / (const double f, const ArrDbl &a);
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of ArrDbl to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o ArrDbl object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const ArrDbl &o);

/**
 * @brief Adds an array to a scalar
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f + a_i\f$
 */
const ArrDbl operator + (const double f, const ArrDbl &a);

/**
 * @brief Adds an array to a scalar
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f + a_i\f$
 */
const ArrDbl operator + (const float f, const ArrDbl &a);

/**
 * @brief Adds an array to a scalar
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f + a_i\f$
 */
const ArrDbl operator + (const int f, const ArrDbl &a);

/**
 * @brief Subtracts an array from a scalar
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f - a_i\f$
 */
const ArrDbl operator - (const double f, const ArrDbl &a);

/**
 * @brief Subtracts an array from a scalar
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f - a_i\f$
 */
const ArrDbl operator - (const float f, const ArrDbl &a);

/**
 * @brief Subtracts an array from a scalar
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f - a_i\f$
 */
const ArrDbl operator - (const int f, const ArrDbl &a);

/**
 * @brief Multiplies a scalar by an array
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f\,a_i\f$
 */
const ArrDbl operator * (const double f, const ArrDbl &a);

/**
 * @brief Multiplies a scalar by an array
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f\,a_i\f$
 */
const ArrDbl operator * (const float f, const ArrDbl & a);

/**
 * @brief Multiplies a scalar by an array
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f\,a_i\f$
 */
const ArrDbl operator * (const int f, const ArrDbl &a);

/**
 * @brief Divides a scalar by an array
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f\;/\;a_i\f$;
 *         \f$\infty\f$, for those i's where \f$a_i=0\f$
 */
const ArrDbl operator / (const float f, const ArrDbl &a);

/**
 * @brief Divides a scalar by an array
 * @param[in] f Scalar
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;f\;/\;a_i\f$;
 *         \f$\infty\f$, for those i's where \f$a_i=0\f$
 */
const ArrDbl operator / (const int f, const ArrDbl &a);

/**
 * @brief Elemental application of the natural logarithm function
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;\ln (a_i)\f$;
 *         \f$-\infty\f$, for those i's where \f$a_i\leq 0\f$
 */
const ArrDbl log(const ArrDbl &a);

/**
 * @brief Elemental application of the exponential function
 * @param[in] a ArrDbl
 * @return \f$\forall i,\;e^{a_i}\f$
 */
const ArrDbl exp(const ArrDbl &a);

#endif // ARRDBL_H
