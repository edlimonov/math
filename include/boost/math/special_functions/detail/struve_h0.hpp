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

     BOOST_MATH_STATIC const T H0_coeff[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.909859164)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.909855001)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.687514637)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.126164557)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.013828813)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.000876918))
     };

    T value, polynom;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    // XXX: correct?
    BOOST_MATH_ASSERT(x > 0); // reflection handled elsewhere.

    if (x <= 3)                       // x in (0, 3]
    {
          T y = x / 3;
          // 
          // Using evaluate_even_polynomial to have powers:
          // 0, 2, 4, 6, 8, 10
          //
          T polynom = evaluate_even_polynomial(H0_coeff, y);
          value = y * polynom;
     }
    else                                // x in (3, \infty)
    {
          T y = 1 / x;
          T y2 = y * constants::one_div_root_pi<T>();
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

