#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * @file utilities.h
 * @brief Collection of stand-alone utility functions
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 20 November 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm> // std::swap() in C++98
#include <utility>   // std::swap() in C++11
#include "constants.h"

//-----------------------------------------------------------------------------

/// Encapsulates stand-alone utility functions
namespace utils
{

//-----------------------------------------------------------------------------

/// Scott Meyers: "Effective STL" p. 38
// (see p. 39 for exception-safety improvements using boost::shared_ptr)
struct DeleteObject
{
    template<typename T>
    void operator () (const T * ptr) {delete ptr;}
};

//-----------------------------------------------------------------------------

/**
  * @brief Conversion of angle from degrees to radians
  * @param[in] x Angle in degrees
  * @return Angle in radians
  */
double radians(const double x);

//-----------------------------------------------------------------------------

/**
  * @brief Conversion of angle from radians to degrees
  * @param[in] x Angle in radians
  * @return Angle in degrees
  */
double degrees(const double x);

//-----------------------------------------------------------------------------

/**
  * @brief Conversion of a real number to its nearest integer
  * @param[in] x Real number
  * @return Integer nearest to x
  */
int nint(const double x);

//-----------------------------------------------------------------------------

/**
  * @brief Remove the specified leading and trailing character from a string
  * @param[in] str String to be trimmed
  * @param[in] c Character to be removed
  * @return Trimmed str
  */
std::string trim_char(std::string str, const char c);

//-----------------------------------------------------------------------------

/**
  * @brief Remove the leading and trailing spaces from a string
  * @param[in] str String to be trimmed
  * @return Trimmed str
  */
std::string trim(std::string str);

//-----------------------------------------------------------------------------

/**
  * @brief Remove the leading and trailing linebreaks from a string
  * @param[in] str String to be trimmed
  * @return Trimmed str
  */
std::string trim_line_breaks(std::string str);

//-----------------------------------------------------------------------------

/**
  * @brief Conversion of a real number to a formatted string
  * @param[in] x Real number to be converted
  * @return String version of x using scientific notation
  */
std::string double_to_string(const double x);

//-----------------------------------------------------------------------------

/**
  * @brief Conversion of an integer to a formatted string
  * @param[in] i Integer to be converted
  * @param[in] fillchar Character used for (left) padding
  * @param[in] length Number of characters in return value
  * @return String version of i
  */
template<typename T>
std::string int_to_string(const T i, const char fillchar, const int length)
{
    std::ostringstream convert;
    convert.str("");
    convert << std::right << std::setw(length) << std::setfill(fillchar) << i;
    return convert.str();
}

//-----------------------------------------------------------------------------

/**
  * @brief Reads a text file into a string
  * @param[in] fname Name of file to be read
  * @return String version of the file's content
  */
std::string file_to_string(const std::string &fname);

//-----------------------------------------------------------------------------

/**
  * @brief Sign flag
  * @param[in] x Real number
  * @return -1, 0, +1
  */
int sign_int(const int x);

//-----------------------------------------------------------------------------

/**
  * @brief Sign flag with tolerance on zero
  * @param[in] x Real number
  * @param[in] EQT Tolerance for comparison with zero
  * @return -1, 0, +1
  */
template<typename T>
int sign_eqt(const T x, const double EQT)
{
    const double y = static_cast<double>(x);
    const double A = fabs(EQT);
    if (y > A)
        return 1;
    else if (y < -A)
        return -1;
    else // y == 0 within A
        return 0;
}

//-----------------------------------------------------------------------------

/// Encapsulates and returns the (real) solutions of a quadratic equation
struct RetQuad
{
    /// Number of distinct real roots
    int nroots;

    /// First real root
    double x1;

    /// Second real root
    double x2;
};

/**
  * @brief Finds (real) solutions of a quadratic equation: \f$ax^2+bx+c=0\f$
  * @param[in] a Quadratic coefficient
  * @param[in] b Linear coefficient
  * @param[in] c Free term
  * @param[in] EQT Tolerance for \f$a=0\f$ and \f$b=0\f$ detection
  * @return Number of distinct real roots and the roots themselves as RetQuad
  */
RetQuad solve_quadratic(const double a, const double b,
                        const double c, const double EQT);

//-----------------------------------------------------------------------------

/**
  * @brief Searches forward in a text file to locate a given line
  *
  * Finds the first line in istr to match a trimmed str and
  * places the stream pointer immediately after it;
  * prints an error message and exit if str is not found
  *
  * @param[in,out] istr File stream
  * @param[in] str Line to be found
 */
void find_line(std::ifstream &istr, const std::string &str);

//-----------------------------------------------------------------------------

/**
  * @brief Searches forward in a text file to locate a given word
  *
  * Finds the first word in istr to match a trimmed str
  * (parsing by operator <<) and
  * places the stream pointer immediately after it;
  * prints an error message and exit if str is not found
  *
  * @param[in,out] istr File stream
  * @param[in] str Word to be found
 */
void find_word(std::ifstream &istr, const std::string &str);

//-----------------------------------------------------------------------------

/**
  * @brief Locates a value in an ordered table by bisecting bracketing interval
  * @param[in] x Value to be located in table v
  * @param[in] v Monotonically increasing table
  * @param[in] ilow Lower index of v-interval bracketing x
  * @param[in] ihigh Upper index of v-interval bracketing x
  * @return Largest v-index, for which v[index] <= x
  */
template<typename T> // T must support "double operator [](size_t)" method
size_t bisect(const double x, const T &v, size_t ilow, size_t ihigh)
{
    size_t imid;
    while (ihigh - ilow > 1)
    {
        imid = (ihigh + ilow) / 2;
        if (v[imid] <= x)
            ilow = imid;
        else
            ihigh = imid;
    }
    return ilow;
}

//-----------------------------------------------------------------------------

/**
  * @brief Brackets a value in an ordered table
  * @param[in] x Value to be bracketed in table v
  * @param[in] v Monotonically increasing table
  * @param[in] imax Highest v-index (= v.size() - 1)
  * @param[in,out] ilow Initial/updated lower index of v-interval bracketing x
  * @param[in,out] ihigh Initial/updated upper index of v-interval bracketing x
  */
template<typename T> // T must support "double operator [](size_t)" method
void bracket(const double x, const T &v,
             const size_t imax, size_t &ilow, size_t &ihigh)
{
    size_t m = 1;
    if (x < v[ilow])
    {
        while (true)
        {
            ihigh = ilow;
            if (ilow > m)
            {
                ilow -= m;
                if (v[ilow] <= x) return;
            }
            else
            {
                ilow = 0;
                return;
            }
            m *= 2;
        }
    }
    else if (v[ihigh] <= x)
    {
        while (true)
        {
            ilow = ihigh;
            ihigh += m;
            if (ihigh > imax)
            {
                ihigh = imax;
                return;
            }
            if (x < v[ihigh]) return;
            m *= 2;
        }
    }
}

//-----------------------------------------------------------------------------

/**
  * @brief Locates a value in an ordered table, nearest to a given value,
  *        by bisection of a bracketing interval
  * @param[in] x Value to be located in table v
  * @param[in] v Monotonically increasing table
  * @param[in] n number of elements in v
  * @param[in] i Initial guess for the return value
  * @return v-index, for which v[index] is nearest to x; 0 if n=0
  */
template<typename T> // T must support "double operator [](size_t)" method
size_t nearest(const double x, const T &v,
               const size_t n, const size_t i)
{
    if (n <= 1) return 0;
    if (x <= v[0]) return 0;
    size_t imax = n - 1;
    if (x >= v[imax]) return imax;

    size_t ilow, ihigh;
    if (i == 0)
        ilow = 0;
    else
        ilow = i - 1;
    if (i == imax)
        ihigh = imax;
    else
        ihigh = i + 1;

    bracket(x, v, imax, ilow, ihigh);
    size_t j = bisect(x, v, ilow, ihigh);
    size_t jp1 = j + 1; // 0 <= j < imax is guaranteed by bisect()
    if (v[jp1] - x  <  x - v[j])
        return jp1;
    else
        return j;
}

//-----------------------------------------------------------------------------

/**
  * @brief Locates a value in a table, nearest to a given value,
  *        by exhaustive search
  * @param[in] x Value to be located in table v
  * @param[in] v Table of distinct values
  * @param[in] n number of elements in v
  * @return v-index, for which v[index] is nearest to x; 0 if n=0
  */
template<typename T> // T must support "double operator [](size_t)" method
size_t nearest_exh(const double x, const T &v, const size_t n)
{   // exhaustive search an all v values
    if (n <= 1) return 0;
    double diff;
    double dmin = fabs(v[0] - x);
    size_t imin = 0;
    for (size_t i = 1; i < n; ++i)
    {
        diff = fabs(v[i] - x);
        if (diff < dmin)
        {
            dmin = diff;
            imin = i;
        }
    }
    return imin;
}

//-----------------------------------------------------------------------------

/**
  * @brief Builds a string containing given material, and values for Te, Tr, Ne
  * @param[in] material Name of material from Table
  * @param[in] te_str Electron temperature (eV)
  * @param[in] tr_str Radiation temperature (eV)
  * @param[in] ne_str Electron number density (particles per cm3)
  * @return Root of file name used in Database lookups for EOS and optical data
  */
std::string fname_root(const std::string &material,
                       const std::string &te_str,
                       const std::string &tr_str,
                       const std::string &ne_str);

//-----------------------------------------------------------------------------

/**
  * @brief Loads a range of values from a file into an array
  * @param[in] fname Name of file
  * @param[in] n Size of array v
  * @param[in] jmin Lower limit of the loaded range
  * @param[in] jmax Upper limit of the loaded range
  * @param[out] v Loaded array
  */
template<typename T> // T must support "double operator [](size_t)" method
void load_array(const std::string &fname, const size_t n,
                const size_t jmin, const size_t jmax, T &v)
{
    std::ifstream infile(fname.c_str());
    find_word(infile, "data");
    std::string s;
    getline(infile, s);
    double x;
    size_t k = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (i > jmax) break;
        infile >> x;
        if (i >= jmin) {v[k] = x; ++k;}
    }
    infile.close();
    infile.clear();
}

//-----------------------------------------------------------------------------

/**
  * @brief Loads EOS data from a file
  * @param[in] fname Name of file
  * @param[in] n Size of array v
  * @param[out] v Ion stage fractional populations, indexed by ion charge
  * @param[out] zbar Average ionization state
  */
void load_eos(const std::string &fname, const size_t n,
              std::vector<double> &v, double &zbar);

//-----------------------------------------------------------------------------

/**
  * @brief Electron number density from charge neutrality constraint
  * @param[in] np Total particle number density (particles per cm3)
  * @param[in] nmat Number of materials
  * @param[in] fp Fractional populations of materials
  * @param[in] zb Average ionization states of materials
  * @return \f$n_e = n_p \sum_{i=1}^{nmat} f_{pi}\;\bar{z_i}\f$
  */
double ne_charge_neut(const double np, const unsigned short int nmat,
                      const std::vector<double> &fp,
                      const std::vector<double> &zb);

//-----------------------------------------------------------------------------

/**
  * @brief Number of digits needed to display an integer
  * @param[in] i Integer to be displayed
  * @return Number of digits needed to display i
  */
int ndigits(const size_t i);

//-----------------------------------------------------------------------------

/**
  * @brief Linear interpolation and extrapolation around two given points
  * @param[in] x Given abscissa for evaluation
  * @param[in] x1 First given abscissa
  * @param[in] y1 First given ordinate
  * @param[in] x2 Second given abscissa
  * @param[in] y2 Second given ordinate
  * @return Ordinate at x on a line defined by points (x1, y1) and (x2, y2)
  */
double fitlin(const double x,
              const double x1, const double y1,
              const double x2, const double y2);

//-----------------------------------------------------------------------------

/**
  * @brief Interpolation and extrapolation around two given points
  * @param[in] x Given abscissa for evaluation
  * @param[in] x1 First given abscissa
  * @param[in] y1 First given ordinate
  * @param[in] x2 Second given abscissa
  * @param[in] y2 Second given ordinate
  * @param[in] xmode "lin" or "log" scaling on x
  * @param[in] ymode "lin" or "log" scaling on y
  * @return Ordinate at x on a function defined by points (x1, y1) and (x2, y2)
  */
double fitpoint(const double x,
                const double x1, const double y1,
                const double x2, const double y2,
                const std::string &xmode, const std::string &ymode);

//-----------------------------------------------------------------------------

/**
  * @brief Generates a grid of values from a range, and size of grid
  * @param[in] xlow Lower limit of range
  * @param[in] xhigh Upper limit of range
  * @param[in] n Number of values in the returned grid
  * @param[in] mode "lin" or "log"
  * @param[in] add_zero If true, 0 will also be in the returned grid
  * @return n values from [xlow, xhigh] with "mode" spacing, 0 may be added
  */
std::vector<double> get_grid(const double xlow, const double xhigh,
                             const size_t n, const std::string &mode,
                             const bool add_zero);

//-----------------------------------------------------------------------------

/**
  * @brief Synchronizes grids (interpolates one data set onto another)
  * @param[in] xin Original grid (assumed monotonically increasing)
  * @param[in] yin Original data set
  * @param[in] NIN Number of values in the original grid
  * @param[in] xmode "lin" or "log": interpolation mode for x
  * @param[in] ymode "lin" or "log": interpolation mode for y
  * @param[in] xout New grid (assumed monotonically increasing)
  * @param[out] yout New data set = yin overlayed onto xout (default yout = 0)
  * @param[in] NOUT Number of values in the new grid
  */
template<typename Txin, typename Tyin, typename Txout, typename Tyout>
// T's must support "double operator [](size_t)" methods
void syngrids(const Txin &xin, const Tyin &yin, const size_t NIN,
              const std::string &xmode, const std::string &ymode,
              const Txout &xout, Tyout &yout, const size_t NOUT)
{
    if (NOUT == 0) return;
    if (NIN == 0)
    {
        for (size_t i = 0; i < NOUT; ++i) yout[i] = 0.0;
        return;
    }
    const size_t MAXIN = NIN - 1;
    const double XMIN = xin[0];
    const double YMIN = yin[0];
    const double XMAX = xin[MAXIN];
    const double YMAX = yin[MAXIN];
    size_t j;
    size_t ilow = 0;
    size_t ihigh = 1;

    for (size_t i = 0; i < NOUT; ++i)
    {
        double x = xout[i];

        if (x <= XMIN)
        {
            yout[i] = YMIN; // flat extrapolation
            continue;
        }

        if (x >= XMAX)
        {
            yout[i] = YMAX; // flat extrapolation
            continue;
        }

        bracket(x, xin, MAXIN, ilow, ihigh);
        j = bisect(x, xin, ilow, ihigh);
        yout[i] = fitpoint(x, xin[j], yin[j], xin[j+1], yin[j+1],
                           xmode, ymode);
    }
}

//-----------------------------------------------------------------------------

/**
  * @brief Rescales ordinates according to a given set of scale factors
  *        (flat extrapolation off the edges)
  * @param[in] hv Scale-factor grid (assumed monotonically increasing)
  * @param[in] sc Scale factors
  * @param[in] NIN Number of values in the original grid
  * @param[in] xmode "lin" or "log": interpolation mode for x
  * @param[in] ymode "lin" or "log": interpolation mode for y
  * @param[in] xout Data x-grid (assumed monotonically increasing)
  * @param[in,out] yout Data set to be rescaled on output
  * @param[in] NOUT Number of values in the output grid
  */
template<typename Thv, typename Tsc, typename Txout, typename Tyout>
// T's must support "double operator [](size_t)" methods
void scale_y(const Thv &hv, const Tsc &sc, const size_t NIN,
             const std::string &xmode, const std::string &ymode,
             const Txout &xout, Tyout &yout, const size_t NOUT)
{
    if (NOUT == 0  ||  NIN == 0) return;
    std::vector<double> so(NOUT);
    syngrids(hv, sc, NIN, xmode, ymode, xout, so, NOUT);
    for (size_t i = 0; i < NOUT; ++i) yout[i] *= so[i];
}

//-----------------------------------------------------------------------------

/**
  * @brief Moves ordinates according to a given set of new positions
  *        (linear extrapolation off the edges)
  * @param[in] hvold Original positions (assumed monotonically increasing)
  * @param[in] hvnew Shifted positions (assumed monotonically increasing)
  * @param[in] NIN Number of values in the original grid
  * @param[in] xold Original x-grid (assumed monotonically increasing)
  * @param[out] xnew Shifted x-grid (assumed monotonically increasing)
  * @param[in] NOUT Number of values in the output grid
  */
template<typename Thvold, typename Thvnew, typename Txold, typename Txnew>
// T's must support "double operator [](size_t)" methods
void shift_x(const Thvold &hvold, const Thvnew &hvnew, const size_t NIN,
             const Txold &xold, Txnew &xnew, const size_t NOUT)
{
    if (NOUT == 0  ||  NIN == 0) return;
    const std::string xmode("lin");
    const std::string ymode("lin");
    syngrids(hvold, hvnew, NIN, xmode, ymode, xold, xnew, NOUT);

    const double XMIN(hvold[0]);
    const double XMAX(hvold[NIN-1]);
    double v;
    for (size_t i = 0; i < NOUT; ++i)
    { // off the edges override flat extrapolation from syngrids with linear
        v = xold[i];
        if (v < XMIN) xnew[i] = fitlin(v, hvold[0], hvnew[0],
                                          hvold[1], hvnew[1]);
        if (v > XMAX) xnew[i] = fitlin(v, hvold[NIN-2], hvnew[NIN-2],
                                          hvold[NIN-1], hvnew[NIN-1]);
    }
}

//-----------------------------------------------------------------------------

/**
  * @brief Rescales y, shifts x, places this new xy onto the given x grid
  * @param[in] hvold Original positions (assumed monotonically increasing)
  * @param[in] sc Scale factors
  * @param[in] hvnew Shifted positions (assumed monotonically increasing)
  * @param[in] NHV Number of values in the calibration/rescale grid
  * @param[in] xin Input data x-grid (assumed monotonically increasing)
  * @param[in] yin Input data (y-values)
  * @param[in] NIN Number of values in the original grid
  * @param[in] xmode "lin" or "log": interpolation mode for x
  * @param[in] ymode "lin" or "log": interpolation mode for y
  * @param[in] xout Output data x-grid (assumed monotonically increasing)
  * @param[out] yout Rescaled/shifted/synchronized output data (y-values)
  * @param[in] NOUT Number of values in the output grid
  */
template<typename Thvold, typename Tsc, typename Thvnew,
         typename Txin, typename Tyin, typename Txout, typename Tyout>
// T's must support "double operator [](size_t)" methods
void rescale(const Thvold &hvold, const Tsc &sc,
             const Thvnew &hvnew, const size_t NHV,
             const Txin &xin, Tyin yin, const size_t NIN,
             const std::string &xmode, const std::string &ymode,
             const Txout &xout, Tyout &yout, const size_t NOUT)
{
    scale_y(hvold, sc, NHV, xmode, ymode, xin, yin, NIN); // yin now rescaled
    std::vector<double> x(NIN);
    shift_x(hvold, hvnew, NHV, xin, x, NIN); // x is the shifted version of xin
    // interpolating (x,yin) onto (xout,yout)
    syngrids(x, yin, NIN, xmode, ymode, xout, yout, NOUT);
}

//-----------------------------------------------------------------------------

/**
  * @brief Locates and prints the first different character between two strings
  * @param[in] s1 First string
  * @param[in] s2 Second string
  */
void first_difference(const std::string &s1, const std::string &s2);

//-----------------------------------------------------------------------------

/**
  * @brief Planckian source function
  * @param[in] hv Photon energy in eV
  * @param[in] tev Temperature in eV
  * @return Planckian specific intensity in Watts / cm2 / sr / eV,\n
  *         or 0, if \f$ tev \leq 0 \f$
  */
double planckian(const double hv, const double tev);

//-----------------------------------------------------------------------------

/**
  * @brief Converts true/false into a string
  * @param[in] b true or false
  * @return "true" or "false"
  */
std::string bool_to_string(const bool b);

//-----------------------------------------------------------------------------

/**
  * @brief Converts strings used to represent true/false into Boolean
  * @param[in] b "true", "false", "on", "off", "1", "0"
  * @return true or false, or halt program if b is not recognized
  */
bool string_to_bool(std::string b);

//-----------------------------------------------------------------------------

/**
  * @brief Indirect indexing: an array of indices -> a single index
  * @param[in] dim Sizes of individual dimensions
  * @param[in] indx Array of indices
  * @return Single product index, throws an exception for invalid input
  */
size_t many_to_one(const std::vector<size_t> &dim,
                   const std::vector<size_t> &indx);

//-----------------------------------------------------------------------------

/**
  * @brief Indirect indexing: a single index -> an array of indices
  * @param[in] dim Sizes of individual dimensions
  * @param[in] j Single indirect product index
  * @return Array of direct indices, throws an exception for invalid input
  */
std::vector<size_t> one_to_many(const std::vector<size_t> &dim, size_t j);

//-----------------------------------------------------------------------------

/**
  * @brief Indirect indexing: a pair of indices -> a single index
  * @param[in] dim Sizes of individual dimensions
  * @param[in] p first: index of dimension, second: index within dimension
  * @return Single summation index, throws an exception for invalid input
  */
size_t two_to_one(const std::vector<size_t> &dim,
                  const std::pair<size_t, size_t> p);

//-----------------------------------------------------------------------------

/**
  * @brief Indirect indexing: a single index -> a pair of indices
  * @param[in] dim Sizes of individual dimensions
  * @param[in] j Single summation index
  * @return first: index of dimension, second: index within dimension,
            throws an exception for invalid input
  */
std::pair<size_t, size_t> one_to_two(const std::vector<size_t> &dim, size_t j);

//-----------------------------------------------------------------------------

/**
  * @brief Normalized Gaussian distribution function
  * @param[in] x Abscissa
  * @param[in] mu Mean
  * @param[in] sigma Standard deviation
  * @return \f$\frac{1}{\sigma\sqrt{2\pi}}\;e^{-\frac{(x-\mu)^2}{2\sigma^2}}\f$
  */
double gaussian(const double x, const double mu, const double sigma);

//-----------------------------------------------------------------------------

/**
  * @brief Integrate a tabulated function by trapezoidal rule
  * @param[in] a Lower limit of integration
  * @param[in] b Upper limit of integration
  * @param[in] x Domain grid (assumed to be monotonically increasing)
  * @param[in] y Tabulated function \f$y=f(x)\f$
  * @param[in] n Number of points on which \f$y=f(x)\f$ is provided
  * @return Definite integral \f$\int_a^b f(x)\;dx\f$
  */
template<typename Tx, typename Ty>
// T's must support "double operator [](size_t)" method
// x grid is assumed to be monotonically increasing
double integrate_trapezoid(double a, double b,
                           const Tx &x, const Ty &y, const size_t n)
{
    if (sign_eqt(a-b, 1.0e-20) == 0) return 0.0;
    // if (a == b) return 0.0;

    double sign;
    if (a > b)
    {
        sign = -1.0;
        std::swap(a, b);
    }
    else
        sign = 1.0;

    size_t nm1 = n - 1;
    a = std::max(a, x[0]);
    b = std::min(b, x[nm1]);

    size_t ia = bisect(a, x, 0, nm1);
    double ya = fitlin(a, x[ia], y[ia], x[ia+1], y[ia+1]);

    size_t ib = bisect(b, x, ia, nm1);
    double yb = fitlin(b, x[ib], y[ib], x[ib+1], y[ib+1]);

    if (ia == ib) return sign * (b - a) * (yb + ya) / 2.0;

    double s = (x[ia+1] - a) * (y[ia+1] + ya)  +  (b - x[ib]) * (yb + y[ib]);
    for (size_t i = ia + 1; i < ib; ++i)
        s += (x[i+1] - x[i]) * (y[i+1] + y[i]);

    return s * sign / 2.0;
}

//-----------------------------------------------------------------------------

/**
  * @brief Convolve a tabulated function f with a normalized Gaussian g
  * @param[in] fwhm Full width at half maximum of the normalized Gaussian g
  * @param[in] xin Domain grid x (assumed to be monotonically increasing)
  * @param[in] yin Tabulated function \f$y=f(x)\f$ (taken as 0 outside xin)
  * @param[in] xout New grid (assumed to be monotonically increasing)
  * @param[out] yout Convolved yin overlayed onto the xout grid
  *             (yout = yin, if xin cannot resolve fwhm)
  * @return Convolution integral
  *         \f$(f*g)(x)=\int_{-\infty}^\infty\;f(t)\;g(x-t)\;dt\f$,\n
  *         throws an exception for mismatched input array sizes
  */
template<typename Txin, typename Tyin, typename Txout, typename Tyout>
// T's must support "double operator [](size_t)", "size_t size(void)" methods
void convolution(const double fwhm, const Txin &xin, const Tyin &yin,
                 const Txout &xout, Tyout &yout)
{
    const double FWHM_TO_SIGMA = 0.5 / sqrt(2.0 * log(2.0));

    size_t nxin = xin.size();
    size_t nyin = yin.size();
    size_t nxout = xout.size();
    size_t nyout = yout.size();

    if ( (nxin != nyin) || (nxout != nyout))
    {
        std::string message = "Error: convolution ranges do not match:";
        message += "\nsize(xin):" + int_to_string(nxin, ' ', cnst::INT_WIDTH);
        message += "\nsize(yin):" + int_to_string(nyin, ' ', cnst::INT_WIDTH);
        message += "\nsize(xout):" + int_to_string(nxout, ' ', cnst::INT_WIDTH);
        message += "\nsize(yout):" + int_to_string(nyout, ' ', cnst::INT_WIDTH);
        throw std::range_error(message);
    }

    std::string xmode("lin");
    std::string ymode("log"); // switch to "lin", if any(yin) <= 0
    double dx;
    double dxmin = 1.0e99; // find the smallest grid increment in xin
    for (size_t i = 0; i < nxin-1; ++i)
    {
        dx = fabs(xin.at(i+1) - xin.at(i));
        if (dx < dxmin) dxmin = dx;
        if (yin.at(i) <= 0.0) ymode = "lin";
    }
    if (yin.at(nxin-1) <= 0.0) ymode = "lin";
    if (fwhm <= 1.5*dxmin) // assign yout = yin
    {
        syngrids(xin, yin, nxin, xmode, ymode, xout, yout, nxout);
        return;
    }

    double sigma = fwhm * FWHM_TO_SIGMA;

    // extrapolate xin, yin at the edges to preempt artificial drop
    size_t ninc = 100;       // must be even
    size_t nhalf = ninc / 2; // add nhalf points to the grid on each side
    size_t nxext = nxin + ninc;
    std::vector<double> xext(nxext), yext(nxext); // extrapolated xin, yin
    double ds = sigma / 10.0; // auxiliary grid spacing
    for (size_t j = 0; j < nxext; ++j)
    {
        if (j < nhalf) // left of the original grid xin
        {
            dx = ds * static_cast<double>(nhalf - j);
            xext.at(j) = xin.at(0) - dx;
            yext.at(j) = fitpoint(xext.at(j),
                                  xin.at(0), yin.at(0),
                                  xin.at(1), yin.at(1),
                                  xmode, ymode);
        }
        else if (j >= nxext - nhalf) // right of the original grid xin
        {
            xext.at(j) = xext.at(j-1) + ds;
            yext.at(j) = fitpoint(xext.at(j),
                                xin.at(nxin-2), yin.at(nxin-2),
                                xin.at(nxin-1), yin.at(nxin-1),
                                xmode, ymode);
        }
        else // on the original grid xin
        {
            xext.at(j) = xin.at(j - nhalf);
            yext.at(j) = yin.at(j - nhalf);
        }
    }

    std::vector<double> y(nxext); // convolution integrand
    for (size_t i = 0; i < nxout; ++i) // loop over output grid points
    {
        for (size_t j = 0; j < nxext; ++j) // build convolution integrand
            y.at(j) = yext.at(j) * gaussian(xout.at(i), xext.at(j), sigma);

        yout[i] = integrate_trapezoid(xext[0], xext[nxext-1], xext, y, nxext);
    }
}

//-----------------------------------------------------------------------------

/**
  * @brief Detect if a given number is contained within a set of intervals
  * @param[in] x Value to be examined
  * @param[in] r Set of intervals (a,b) - where a < b
  * @return true or false
  */
bool is_contained_in(const double x,
                     const std::vector< std::pair<double, double> > &r);

//-----------------------------------------------------------------------------

/**
 * @brief Replaces a substring,\n
 *        throws an exception if "old" is not present in "s"
 * @param[in,out] s String to be modified
 * @param[in] old Substring to be replaced
 * @param[in] rep Replacement string applied at first location of "old" in "s"
 */
void replace_in_string(std::string &s, const std::string &old,
                                       const std::string &rep);

//-----------------------------------------------------------------------------

} // namespace utils

#endif // UTILITIES_H
