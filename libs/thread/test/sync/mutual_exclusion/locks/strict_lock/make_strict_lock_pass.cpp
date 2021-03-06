// Copyright (C) 2011 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// <boost/thread/strict_lock.hpp>

// template <class Lockable>
// strict_lock<Lockable> make_strict_lock(Lockable &);

#define BOOST_THREAD_VERSION 4
#define BOOST_THREAD_USES_LOG
#define BOOST_THREAD_DONT_PROVIDE_NESTED_LOCKS

#include <boost/thread/detail/log.hpp>
#include <boost/thread/strict_lock.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include <boost/detail/lightweight_test.hpp>

#ifdef BOOST_THREAD_USES_CHRONO
typedef boost::chrono::high_resolution_clock Clock;
typedef Clock::time_point time_point;
typedef Clock::duration duration;
typedef boost::chrono::milliseconds ms;
typedef boost::chrono::nanoseconds ns;
#endif

boost::mutex m;

#if ! defined(BOOST_NO_CXX11_AUTO) && ! defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && ! defined BOOST_NO_CXX11_HDR_INITIALIZER_LIST && defined BOOST_THREAD_USES_CHRONO

void f()
{
  time_point t0 = Clock::now();
  time_point t1;
  {
    const auto&& lg = boost::make_strict_lock(m); (void)lg;
    t1 = Clock::now();
    BOOST_THREAD_TRACE;
  }
  BOOST_THREAD_TRACE;
  ns d = t1 - t0 - ms(250);
  // This test is spurious as it depends on the time the thread system switches the threads
  BOOST_TEST(d < ns(2500000)+ms(1000)); // within 2.5ms
}
#endif

int main()
{

#if ! defined(BOOST_NO_CXX11_AUTO) && ! defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && ! defined BOOST_NO_CXX11_HDR_INITIALIZER_LIST
  {
    m.lock();
    boost::thread t(f);
    boost::this_thread::sleep_for(ms(250));
    m.unlock();
    t.join();
  }
#endif
  return boost::report_errors();
}
