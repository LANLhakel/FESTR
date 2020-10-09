/*=============================================================================

Test.cpp
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

#include <Test.h>

//-----------------------------------------------------------------------------

Test::Test() : group_(""), name_(""), speed_(""), enabled_(false) {}

//-----------------------------------------------------------------------------

Test::Test(const std::string& gr, const std::string& nm,
           const std::string& sp)
           : group_(gr), name_(nm), speed_(sp),
             enabled_(requested_ == "all" || requested_ == "only" ||
                      requested_ == gr    || requested_ == sp) {}

//-----------------------------------------------------------------------------

Test::Test(const std::string& gr, const std::string& nm,
           const std::string& sp, const bool e)
           : group_(gr), name_(nm), speed_(sp), enabled_(e) {}

//-----------------------------------------------------------------------------

Test::~Test()
{
    group_ = "";
    name_ = "";
    speed_ = "";
    enabled_ = false;
}

//-----------------------------------------------------------------------------

int Test::get_run_test_count() {return run_test_count_;}

//-----------------------------------------------------------------------------

void Test::groups_insert(const std::string& st) {groups_.insert(st);}

//-----------------------------------------------------------------------------

bool Test::tests_were_run()
{
    return groups_.find(requested_) != groups_.end();
}

//-----------------------------------------------------------------------------

void Test::set_requested(const std::string& rq) {requested_ = rq;}

//-----------------------------------------------------------------------------

std::string Test::get_requested() {return requested_;}

//-----------------------------------------------------------------------------

void Test::set_verbose(const bool vb) {verbose_ = vb;}

//-----------------------------------------------------------------------------

bool Test::get_verbose() {return verbose_;}

//-----------------------------------------------------------------------------

void Test::set_disabled_speed(const std::string& ds)
{
    disabled_speed_ = ds;
}

//-----------------------------------------------------------------------------

std::string Test::get_disabled_speed() {return disabled_speed_;}

//-----------------------------------------------------------------------------

void Test::set_only_test(const std::string& ts)
{
    only_test_ = ts;
}

//-----------------------------------------------------------------------------

std::string Test::get_only_test() {return only_test_;}

//-----------------------------------------------------------------------------

void Test::disabled_tests_insert(const std::string& str)
{
    disabled_tests_.insert(str);
}

//-----------------------------------------------------------------------------

void Test::set_group(const std::string& gr) {group_ = gr;}

//-----------------------------------------------------------------------------

std::string Test::get_group() const {return group_;}

//-----------------------------------------------------------------------------

void Test::set_name(const std::string& nm) {name_ = nm;}

//-----------------------------------------------------------------------------

std::string Test::get_name() const {return name_;}

//-----------------------------------------------------------------------------

std::string Test::get_id() const {return group_ + "-" + name_;}

//-----------------------------------------------------------------------------

void Test::set_speed(const std::string& sp)
{
    if (sp == "slow")
        speed_ = sp;
    else
        speed_ = "fast";
}

//-----------------------------------------------------------------------------

std::string Test::get_speed() const {return speed_;}

//-----------------------------------------------------------------------------

void Test::enable() {enabled_ = true;}

//-----------------------------------------------------------------------------

void Test::disable() {enabled_ = false;}

//-----------------------------------------------------------------------------

bool Test::is_enabled() const {return enabled_;}

//-----------------------------------------------------------------------------

int Test::check_to_disable()
{
    if (is_enabled() && (
        (disabled_tests_.find(get_id()) != disabled_tests_.end() ) ||
        (speed_ == disabled_speed_)) )
    {
        disable();
        return 1;
    }
    else
    {
        groups_.insert("all");
        groups_.insert("only");
        groups_.insert(group_);
        groups_.insert(speed_);
        return 0;
    };
}

//-----------------------------------------------------------------------------

void Test::check_to_disable_test(int& disabled_test_count)
{
    if (Test::get_requested() == "only")
    {
        disable();
        if (Test::get_only_test() == get_id()) enable();
    }
    disabled_test_count += check_to_disable();
}

//-----------------------------------------------------------------------------

std::string Test::to_string() const
{
    return get_id() + " " + get_speed() + " "
                    + (enabled_ ? "enabled" : "disabled");
}

//-----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& ost, const Test& t)
{
    ost << t.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

bool operator==(const Test& x, const Test& y)
{
    return (x.get_group() == y.get_group() &&
            x.get_name() == y.get_name() &&
            x.get_speed() == y.get_speed() &&
            x.is_enabled() == y.is_enabled());
}

//-----------------------------------------------------------------------------

bool operator!=(const Test& x, const Test& y)
{
    return !(x == y);
}

//-----------------------------------------------------------------------------

int Test::run_test_count_ = 0;
std::string Test::requested_ = "all";
bool Test::verbose_ = false;
Set_of_Strings Test::groups_;
std::string Test::disabled_speed_ = "";
std::string Test::only_test_ = "";
Set_of_Strings Test::disabled_tests_ = Set_of_Strings();

//-----------------------------------------------------------------------------

//  end Test.cpp
