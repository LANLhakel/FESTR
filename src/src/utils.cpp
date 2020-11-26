/**
 * @file utils.cpp
 * @brief Collection of stand-alone utility functions
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 20 November 2014\n
 * Last modified on 26 November 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <utils.h>

#include <constants.h>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <stdexcept>

//-----------------------------------------------------------------------------

double utils::radians(const double x)
{
    return x * (cnst::PI / 180.0);
}

//-----------------------------------------------------------------------------

double utils::degrees(const double x)
{
    return x * (180.0 / cnst::PI);
}

//-----------------------------------------------------------------------------

int utils::nint(const double x)
{
    return static_cast<int>(floor(x + 0.5));
}

//-----------------------------------------------------------------------------

std::string utils::trim_char(std::string str, const char c)
{
    std::string::size_type pos = str.find_last_not_of(c);

    if (pos != std::string::npos)
    {
        str.erase(pos + 1);
        pos = str.find_first_not_of(c);
        if (pos != std::string::npos) str.erase(0, pos);
    }
    else
        str.erase(str.begin(), str.end());

    return str;
}

//-----------------------------------------------------------------------------

std::string utils::trim(std::string str)
{
    return trim_char(str, ' ');
}

//-----------------------------------------------------------------------------

std::string utils::trim_line_breaks(std::string str)
{
    return trim_char(str, '\n');
}

//-----------------------------------------------------------------------------

std::string utils::double_to_string(const double x)
{
    const size_t N = 15;
    std::ostringstream b;
    b << std::scientific << std::setw(N) << std::setprecision(6) << x;
    std::string rv(b.str());
    size_t iexp = rv.find('e');
    size_t nexp = N - 2 - iexp;
    if (nexp > 2  &&  rv[iexp+2] == '0') // drop leading 0 in 3-digit exponent
        rv = " " + rv.substr(0, iexp+2) + rv.substr(iexp+3, nexp-1);

    return rv;
}

//-----------------------------------------------------------------------------

// Scott Meyers: "Effective STL" p. 127
std::string utils::file_to_string(const std::string &fname)
{
    std::ifstream infile(fname.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << fname << " is not open in "
                  << "utils::file_to_string" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string s((std::istreambuf_iterator<char>(infile)),
                   std::istreambuf_iterator<char>());
    if (*(s.end()-1) == '\n') s.erase(s.end()-1, s.end());
    infile.close();
    infile.clear();
    return s;
}

//-----------------------------------------------------------------------------

int utils::sign_int(const int x)
{
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    else // x == 0
        return 0;
}

//-----------------------------------------------------------------------------

utils::RetQuad utils::solve_quadratic(const double a, const double b,
                                      const double c, const double EQT)
{   // Numerical Recipes in FORTRAN, Second Edition
    const double BIG = -1.0e100;
    const double TOL = fabs(EQT);
    RetQuad rv;

    if (fabs(a) <= TOL) // a == 0 (linear equation)
    {
        if (fabs(b) <= TOL) // b == 0 (return no solution)
        {
            rv.nroots = 0;
            rv.x1 = rv.x2 = BIG;
        }
        else // b != 0
        {
            rv.nroots = 1;
            rv.x1 = rv.x2 = -c/b;
        }
    }
    else // a != 0 (quadratic equation)
    {
        double d = b*b - 4.0*a*c;
        if (fabs(d) <= TOL) d = 0.0;

        if (d < 0.0) // no real solution
        {
            rv.nroots = 0;
            rv.x1 = rv.x2 = BIG;
        }
        else // d >= 0.0
        {
            if (fabs(b) <= TOL) // this extra b == 0 branch is needed
            {   // because Numerical Recipes assumes that sgn(b) cannot be 0
                // whereas our sign_eqt(b, TOL) == 0 if b == 0 within TOL
                rv.x1 = sqrt(-c/a);
                rv.x2 = -rv.x1;
            }
            else
            {   // sign_eqt(b, TOL) != 0 in this branch
                double q = -0.5 * (b + sign_eqt(b, TOL) * sqrt(d));
                rv.x1 = q/a;
                rv.x2 = c/q;
            }

            if (rv.x1 < rv.x2) std::swap(rv.x1, rv.x2); // ensure x1 >= x2

            if (d <= TOL)
                rv.nroots = 1;
            else
                rv.nroots = 2;

        } // d < 0.0

    } // fabs(a) <= TOL

    return rv;
}

//-----------------------------------------------------------------------------

void utils::find_line(std::ifstream &istr, const std::string &str)
{
    std::string s;
    while (true)
    {
        getline(istr, s);
        if (trim(s) == str) break;
        if (istr.eof())
        {
            std::cerr << "Error: " << str << " not found\n" <<
              "Program stopped in function find_line()" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

//-----------------------------------------------------------------------------

void utils::find_word(std::ifstream &istr, const std::string &str)
{
    std::string s;
    while (true)
    {
        istr >> s;
        if (trim(s) == str) break;
        if (istr.eof())
        {
            std::cerr << "Error: " << str << " not found\n" <<
              "Program stopped in function find_word()" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

//-----------------------------------------------------------------------------

std::string utils::fname_root(const std::string &material,
                              const std::string &te_str,
                              const std::string &tr_str,
                              const std::string &ne_str)
{
    return material+"_te"+te_str+"ev_tr"+tr_str+"ev_ne"+ne_str+"pcc_";
}

//-----------------------------------------------------------------------------

void utils::load_eos(const std::string &fname, const size_t n,
                     std::vector<double> &v, double &zbar)
{
    size_t ilow, ihigh, i, j;
    std::ifstream infile(fname.c_str());
    if (!infile.is_open())
    {
        std::cerr << "Error: file " << fname << " is not open in "
                  << "utils::load_eos" << std::endl;
        exit(EXIT_FAILURE);
    }

    find_word(infile, "zbar");
    infile >> zbar;

    find_word(infile, "range");
    infile >> ilow >> ihigh;

    find_line(infile, "charge  fract_popul");
    v.assign(n, 0.0);
    for (i = ilow; i <= ihigh; ++i) infile >> j >> v.at(i);
    infile.close();
    infile.clear();
}

//-----------------------------------------------------------------------------

double utils::ne_charge_neut(const double np, const unsigned short int nmat,
                             const std::vector<double> &fp,
                             const std::vector<double> &zb)
{
    double s(0.0);
    for (unsigned short int i = 0; i < nmat; ++i) s += fp.at(i) * zb.at(i);
    return s * np;
}

//-----------------------------------------------------------------------------

int utils::ndigits(const size_t i)
{
    size_t k = 10;
    for (int j = 1; j <= cnst::INT_WIDTH; ++j)
    {
        if (i < k) return j;
        k *= 10;
    }
    return 0;
}

//-----------------------------------------------------------------------------

double utils::fitlin(const double x,
                     const double x1, const double y1,
                     const double x2, const double y2)
{
    return y1  +  (x - x1) * (y2 - y1) / (x2 - x1);
}

//-----------------------------------------------------------------------------

double utils::fitpoint(const double x,
                       const double x1, const double y1,
                       const double x2, const double y2,
                       const std::string &xmode, const std::string &ymode)
{
    if (xmode == "lin"  &&  ymode == "lin")
        return fitlin(x, x1, y1, x2, y2);

    if (xmode == "log"  &&  ymode == "lin")
        return fitlin(log(x), log(x1), y1, log(x2), y2);

    if (xmode == "lin"  &&  ymode == "log")
        return exp( fitlin(x, x1, log(y1), x2, log(y2)) );

    if (xmode == "log"  &&  ymode == "log")
        return exp( fitlin(log(x), log(x1), log(y1), log(x2), log(y2)) );

    return 0.0; // unknown xmode, ymode options
}

//-----------------------------------------------------------------------------

std::vector<double> utils::get_grid(const double xlow, const double xhigh,
                                    const size_t n, const std::string &mode,
                                    const bool add_zero)
{
    std::vector<double> rv;
    double x, dx;
    double nm1 = static_cast<double>(n-1);

    if (mode == "lin")
    {
        x = xlow;
        dx = nm1 > 0  ?  (xhigh - xlow) / nm1  :  0.0;
    }
    else if (mode == "log")
    {
        x = log(xlow);
        dx = nm1 > 0  ?  log(xhigh/xlow) / nm1  :  0.0;
    }
    else
    {
        std::cerr << "Error in get_grid (utils.cpp), "
                  << "unknown mode: " << mode << std::endl;
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n; ++i)
    {
        if (mode == "lin")
            rv.emplace_back(x);
        else // mode == "log"
            rv.emplace_back(exp(x));

        x += dx;
    }

    if (add_zero)
    {
        if (rv.at(0) > 0.0) rv.insert(rv.begin(), 0.0);
        if ( *(rv.end()-1) < 0.0) rv.emplace_back(0.0);
    }

    return rv;
}

//-----------------------------------------------------------------------------

void utils::first_difference(const std::string &s1, const std::string &s2)
{
    size_t n1 = s1.size();
    size_t n2 = s2.size();
    std::cout << "string sizes: " << n1 << "  " << n2 << std::endl;
    size_t n = std::min(n1, n2);
    for (size_t i = 0; i < n; ++i)
        if (s1[i] == s2[i])
            std::cout << s1[i];
        else
        {
            std::cout << "\ndifference at position: " << i
                      << "\ns1: " << s1[i]
                      << "\ns2: " << s2[i] << std::endl;
            break;
        }
}

//-----------------------------------------------------------------------------

double utils::planckian(const double hv, const double tev) // both inputs in eV
{
    const double F = 5040.367;
    if (tev <= 0.0) return 0.0;
    return F * pow(hv, 3) / (exp(hv/tev) - 1.0); // W/cm2/sr/eV
}

//-----------------------------------------------------------------------------

std::string utils::bool_to_string(const bool b)
{
    return b ? "true" : "false";
}

//-----------------------------------------------------------------------------

bool utils::string_to_bool(std::string b)
{
    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
    if (b == "true" || b == "on" || b == "1" || b == "yes") return true;
    if (b == "false" || b == "off" || b == "0" || b == "no") return false;
    std::cerr << "Error in string_to_bool (utils), unknown argument: "
              << b << std::endl;
    exit(EXIT_FAILURE);
}

//-----------------------------------------------------------------------------

size_t utils::many_to_one(const std::vector<size_t> &dim,
                          const std::vector<size_t> &indx)
{
    size_t ndim = dim.size();
    size_t n = indx.size();
    if (n != ndim)
    {
        std::string message = "Error: many_to_one ranges do not conform:\n";
        message += "dimensions = " + int_to_string(ndim, ' ', 10) + "\n";
        message += "indices = " + int_to_string(n, ' ', 10);
        throw std::range_error(message);
    }

    size_t j = indx[0];
    for (size_t i = 1; i < n; ++i)
    {
        if (indx[i] >= dim[i])
            throw std::out_of_range("out of range exception");

        j = j * dim[i]  +  indx[i];
    }
    return j;
}

//-----------------------------------------------------------------------------

std::vector<size_t> utils::one_to_many(const std::vector<size_t> &dim, size_t j)
{
    if (dim.empty()) throw std::out_of_range("out of range exception");
    std::vector<size_t> indx;
    const size_t ONE(1);
    size_t n =
    std::accumulate(dim.begin(), dim.end(), ONE, std::multiplies<size_t>() );
    if (j >= n) throw std::out_of_range("out of range exception");

    size_t remainder;
    size_t ndim = dim.size();
    size_t i = ndim;
    indx.resize(ndim);
    for (size_t k = 0; k < ndim; ++k)
    {
        --i;
        remainder = j % dim[i];
        indx.at(i) = remainder;
        j = (j - remainder) / dim[i];
    }
    return indx;
}

//-----------------------------------------------------------------------------

size_t utils::two_to_one(const std::vector<size_t> &dim,
                         const std::pair<size_t, size_t> p)
{
    size_t ndim = dim.size();
    if (p.first >= ndim)
    {
        std::string message = "Error: two_to_one range error:\n";
        message += "maximum = " + int_to_string(ndim-1, ' ', 10) + "\n";
        message += "requested = " + int_to_string(p.first, ' ', 10);
        throw std::range_error(message);
    }

    if (p.second >= dim[p.first])
        throw std::out_of_range("out of range exception");

    size_t rv = p.second;
    for (size_t j = 0; j < p.first; ++j) rv += dim[j];
    return rv;
}

//-----------------------------------------------------------------------------

std::pair<size_t, size_t>
utils::one_to_two(const std::vector<size_t> &dim, size_t j)
{
    if (dim.empty()) throw std::out_of_range("out of range exception");
    size_t ndim = dim.size();
    size_t i = 0;
    while (j >= dim[i])
    {
        j -= dim[i];
        ++i;
        if (i >= ndim) throw std::out_of_range("out of range exception");
    }
    std::pair<size_t, size_t> rv(i, j);
    return rv;
}

//-----------------------------------------------------------------------------

double utils::gaussian(const double x, const double mu, const double sigma)
{
    double y = (x - mu) / sigma;
    return exp(-y*y/2.0) / sigma / sqrt(cnst::TWO_PI);
}

//-----------------------------------------------------------------------------

bool utils::is_contained_in(const double x,
                            const std::vector< std::pair<double, double> > &r)
{
    size_t n = r.size();
    for (size_t i = 0; i < n; ++i)
        if (x >= r.at(i).first  &&  x <= r.at(i).second) return true;
    return false;
}

//-----------------------------------------------------------------------------

void utils::replace_in_string(std::string &s, const std::string &old,
                                              const std::string &rep)
{
    size_t found = s.find(old);
    if (found == std::string::npos)
    {
        std::string msg("replace_in_string: old substring not found");
        throw std::invalid_argument(msg);
    }
    std::string beginning(s.substr(0, found));
    std::string ending(s.substr(found+old.size()));
    s = beginning + rep + ending;
}

//-----------------------------------------------------------------------------

std::vector<double> utils::normalize(const std::vector<double> &f,
                                     const double n)
{
    double s = n / std::accumulate(f.begin(), f.end(), 0.0);
    std::vector<double> fn{f};
    std::for_each(fn.begin(), fn.end(), [s](double &x){x *= s;});

    return fn;
}

//-----------------------------------------------------------------------------

//  end utils.cpp
