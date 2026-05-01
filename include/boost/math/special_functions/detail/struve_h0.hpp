//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STRUVE_H0_HPP
#define BOOST_MATH_STRUVE_H0_HPP

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
BOOST_MATH_GPU_ENABLED T struve_h0(T x)
{

    BOOST_MATH_STATIC const T P[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0707355302630645936750594539914)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00792106043964393838700433537069)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.000459347160858328152666975152103)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000127570704598573950427855592976)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.000000177610756112727457308380231305)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00000000100365914526111521466630492207))
    };
    BOOST_MATH_STATIC const T Q[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0480186462137823940239219913993)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00111562640140860204136655251856)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000159678117968420435240449310321)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000144009832908415329312877296644)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.73639642330268552035075149213e-10))
    };

    T value;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    // XXX: correct?
    BOOST_MATH_ASSERT(x > 0); // reflection handled elsewhere.

    if (x <= 2)                       // x in (0, 2]
    {
        T y = x * x;
        T z = y / 4;
        BOOST_MATH_ASSERT(sizeof(P) == sizeof(Q));
        T r = evaluate_rational(P, Q, z);
        value = x * (two_div_pi<T>() + y * r);
    }
    else                                // x in (2, \infty)
    {
          T y = 2 / x;
          T y2 = y * (1 / pi<T>());
          //
          // What follows is really just:
          //
          // value = 2 / (x * pi) + Y_0(x)
          //
          // This is the test realization
          //
          value = y2 + boost::math::cyl_neumann(0, x);
    }

    return value;
}

}}} // namespaces

#endif // BOOST_MATH_STRUVE_H0_HPP
