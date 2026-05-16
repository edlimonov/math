//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STRUVE_H1_HPP
#define BOOST_MATH_STRUVE_H1_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/tools/assert.hpp>
#include <boost/math/special_functions/bessel.hpp>

#if defined(__GNUC__) && defined(BOOST_MATH_USE_FLOAT128)
//
// This is the only way we can avoid
// warning: non-standard suffix on floating constant [-Wpedantic]
// when building with -Wall -pedantic.  Neither __extension__
// nor #pragma diagnostic ignored work :(
//
#pragma GCC system_header
#endif

namespace boost { namespace math { namespace detail{

template <typename T>
BOOST_MATH_GPU_ENABLED T struve_h1(T x)
{

     BOOST_MATH_STATIC const T P1[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0222222222222222222222222118062)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.000416241507253677060631828322354)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00000488041736317376726314427958885)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0000000294402083864859334652764158964)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.01800506821444558260016330191e-10)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.87843499656820508549732062363e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.48207818794936784891724605153e-16))
     };
     BOOST_MATH_STATIC const T Q1[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00984056074501310370012914383751)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000472629205427404035699512170137)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000143677402739490194157062876109)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.96181556185183612945022853931e-10)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.0022859657436399905464210672e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.8393903960346502732335745573e-16))
     };
     BOOST_MATH_STATIC const T P2[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0222222222222019521735597464924)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.000407152117627130807224563730837)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00000472398625054902966348913733802)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0000000276967557946033645003705556936)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 9.26387255666205353828873871846e-11)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.62527158537972767608532916082e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.19928543759787850825575526152e-16))
     };
     BOOST_MATH_STATIC const T Q2[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0102495832778267217809058749333)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000519098786272607100457055926622)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000169405244805377222254388434576)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.85233870512986394360695675183e-10)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.00441077254611557159376033412e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.35339718517133299578178099385e-16))
     };

    T value;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    // XXX: correct?
    BOOST_MATH_ASSERT(x > 0); // reflection handled elsewhere.

    if (x <= 4)                       // x in (0, 4]
    {
        T y = x * x;
        BOOST_MATH_ASSERT(sizeof(P1) == sizeof(Q1));
        T r = evaluate_rational(P1, Q1, y);
        value = two_div_pi<T>() * y * (static_cast<T>(1) / 3 - y * r);
    }
    else if (x <= 8)                  // x in (4, 8]
    {
        T y = x * x;
        BOOST_MATH_ASSERT(sizeof(P2) == sizeof(Q2));
        T r = evaluate_rational(P2, Q2, y);
        value = two_div_pi<T>() * y * (static_cast<T>(1) / 3 - y * r);
    }
    else                                // x in (8, \infty)
    {
        T y = 2 / pi<T>();
        //
        // What follows is really just:
        //
        // value = 2 / pi + Y_1(x)
        //
        // This is the test realization
        //
        value = y + boost::math::cyl_neumann(1, x);
    }

    return value;
}

}}} // namespaces

#endif // BOOST_MATH_STRUVE_H1_HPP
