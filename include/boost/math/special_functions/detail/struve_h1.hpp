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
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0222222222222222375490478630529)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.000431238897786980354017004905167)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00000518449304501303905173943082267)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0000000331395927973048980349804059204)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.26222129977683184987348585615e-10)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.81049012623587558552337247532e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.44471730334291552228895903695e-16)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.80992062662045450379351658005e-19))
     };
     BOOST_MATH_STATIC const T Q2[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00916567817101478592576884840922)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000416639669683400537283894717224)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000123304196693759612152593428639)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.60662940430738897336712287738e-10)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.01783395289156978368972807018e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.30336470752717840183185584752e-16)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.58804113242891615033035260615e-19))
     };
     BOOST_MATH_STATIC const T P3[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0222222222222388033367470463424)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.000428150178579328607033936499942)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00000512836366039782167435079993456)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0000000324907078190709864888911278559)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.22457551966245954680391025337e-10)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.68601960824794604847771418338e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.23020170728417424528513321896e-16)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.655082993558791425561661665e-19))
     };
     BOOST_MATH_STATIC const T Q3[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00930467053556493647418484715711)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000431093550497694878425922752778)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000130765739214127220510953668506)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.85656980866486316472616809132e-10)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.60788465567808390776914522226e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.27749795480362647662021356161e-16)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.56409168076507969865035124728e-19))
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
    else if (x <= 7)                  // x in (4, 7]
    {
        T y = x * x;
        BOOST_MATH_ASSERT(sizeof(P2) == sizeof(Q2));
        T r = evaluate_rational(P2, Q2, y);
        value = two_div_pi<T>() * y * (static_cast<T>(1) / 3 - y * r);
    }
    else if (x <= 8)                  // x in (7, 8]
    {
        T y = x * x;
        BOOST_MATH_ASSERT(sizeof(P3) == sizeof(Q3));
        T r = evaluate_rational(P3, Q3, y);
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
