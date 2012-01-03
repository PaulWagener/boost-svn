//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// Copyright (C) 2011 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// <boost/thread/thread.hpp>

// thread::id this_thread::get_id();

#include <boost/thread/thread.hpp>
#include <cstdlib>

#include <boost/detail/lightweight_test.hpp>

int main()
{
  typedef boost::chrono::system_clock Clock;
  typedef Clock::time_point time_point;
  typedef Clock::duration duration;
  boost::chrono::milliseconds ms(500);
  time_point t0 = Clock::now();
  boost::this_thread::sleep_for(ms);
  time_point t1 = Clock::now();
  boost::chrono::nanoseconds ns = (t1 - t0) - ms;
  boost::chrono::nanoseconds err = ms / 100;
  // The time slept is within 1% of 500ms
  BOOST_TEST(std::abs(ns.count()) < err.count());

}
