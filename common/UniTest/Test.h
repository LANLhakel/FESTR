#ifndef LANL_ASC_PEM_TEST_H_
#define LANL_ASC_PEM_TEST_H_

/*=============================================================================

Test.h
Testing framework

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 29 October 2018
Last modified on 14 July 2020

Copyright (c) 2018, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

=============================================================================*/

#include <cmath>
#include <iostream>
#include <set>
#include <string>

//-----------------------------------------------------------------------------

// Equality test for discrete data types

template<typename ObjectType>
bool are_equal(const ObjectType& x, const ObjectType& y)
{
    return x == y;
}

//-----------------------------------------------------------------------------

// Equality test with tolerance eqt for float, double, etc.

template<typename RealType>
bool are_equal_real_num(const RealType& x, const RealType& y,
                        const RealType& eqt)
{
    return fabs(x-y) < eqt;
}

//-----------------------------------------------------------------------------

// Equality test with tolerance eqt for objects containing float, double, etc.
// data members. ObjectType must define member function x.abs_diff(y)
// to quantify the "absolute difference" between object instances x and y.

template<typename ObjectType, typename RealType>
bool are_equal_real_obj(const ObjectType& x, const ObjectType& y,
                        const RealType& eqt)
{
    return x.abs_diff(y) < eqt;
}

//-----------------------------------------------------------------------------

typedef std::set<std::string> Set_of_Strings;
const std::string UNCAUGHT_EXCEPTION("should reflect caught exception");

//-----------------------------------------------------------------------------

class Test
{
    friend std::ostream& operator<<(std::ostream& ost, const Test& t);
    friend bool operator==(const Test& x, const Test& y);
    friend bool operator!=(const Test& x, const Test& y);

  public:
    Test();

    Test(const std::string& gr, const std::string& nm,
         const std::string& sp);

    Test(const std::string& gr, const std::string& nm,
         const std::string& sp, const bool e);

    ~Test();

    static int get_run_test_count();

    static void groups_insert(const std::string& st);

    static bool tests_were_run();

    static void set_requested(const std::string& rq);

    static std::string get_requested();

    static void set_verbose(const bool vb);

    static bool get_verbose();

    static void set_disabled_speed(const std::string& ds);

    static std::string get_disabled_speed();

    static void set_only_test(const std::string& ts);

    static std::string get_only_test();

    static void disabled_tests_insert(const std::string& str);

    void set_group(const std::string& gr);

    std::string get_group() const;

    void set_name(const std::string& nm);

    std::string get_name() const;

    std::string get_id() const;

    void set_speed(const std::string& sp);

    std::string get_speed() const;

    void enable();

    void disable();

    bool is_enabled() const;

    // return value to increment disabled tests counter
    int check_to_disable();

    void check_to_disable_test(int& disabled_test_count);

    // equality test for discrete types, both built-in and user-defined
    template<typename ObjectType>
    int check_equal(const ObjectType& expected,
                    const ObjectType& actual)
    {
        return pass_or_fail(are_equal(expected, actual),
                            expected, actual);
    }

    // floating-point equality test for built-in types
    template<typename RealType>
    int check_equal_real_num(const RealType& expected,
                             const RealType& actual,
                             const RealType& eqt)
    {
        return pass_or_fail(are_equal_real_num(expected, actual, eqt),
                            expected, actual);
    }

    // floating-point equality test for user-defined types
    template<typename ObjectType, typename RealType>
    int check_equal_real_obj(const ObjectType& expected,
                             const ObjectType& actual,
                             const RealType& eqt)
    {
        return pass_or_fail(are_equal_real_obj(expected, actual, eqt),
                            expected, actual);
    }

    std::string to_string() const;

  private:
    static int run_test_count_;
    static std::string requested_; // from command-line argument
    static bool verbose_; // true, if passing tests are also to be printed
    static Set_of_Strings groups_;
    static std::string disabled_speed_;
    static std::string only_test_;
    static Set_of_Strings disabled_tests_;

    std::string group_;
    std::string name_;
    std::string speed_; // "slow", "fast"
    bool enabled_;

    // return value to increment failed tests counter
    template<typename ObjectType> // ObjectType must support operator <<
    int pass_or_fail(const bool test_passes,
                     const ObjectType& expected,
                     const ObjectType& actual)
    {
        ++run_test_count_;
        if (test_passes)
        {
            if (verbose_) std::cout << get_id() << ": PASS" << std::endl;
            return 0;
        }
        else
        {
            std::cout << get_id() << ": FAIL\n"
                      << "expected\n" << expected << "\n"
                      << "actual\n" << actual << std::endl;
            return 1;
        }
    }
};

//-----------------------------------------------------------------------------

#endif //  LANL_ASC_PEM_TEST_H_
