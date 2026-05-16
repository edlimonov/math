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
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0222222222222222222222187208981)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.000414943204245693801488803489504)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00000485769245921173652248653435853)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0000000291852412990471021442150402378)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.00429654493172667611292344395e-10)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.83960144966698339723279761287e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.43691989316889108311299034829e-16))
     };
     BOOST_MATH_STATIC const T Q1[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00989898438037235035940839589073)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000479095465889989296945759651195)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000147129971812573583247311234044)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.07519748465865441810496136172e-10)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.23721501017396033589599490095e-13)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.09391511442343894670811568123e-16))
     };
     BOOST_MATH_STATIC const T H1_coeff[] = {
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.909859286)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.145914713)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.294656958)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.042070508)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.003785727)),
          static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.000207183))
     };

    T value;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    // XXX: correct?
    BOOST_MATH_ASSERT(x > 0); // reflection handled elsewhere.

    if (x <= 5)                     // x in (0, 0.5]
    {
        T y = x * x;
        BOOST_MATH_ASSERT(sizeof(P1) == sizeof(Q1));
        T r = evaluate_rational(P1, Q1, y);
        value = two_div_pi<T>() * y * (static_cast<T>(1) / 3 - y * r);
    }
//     else if (x <= 3)                  // x in (0.5, 3]
//     {
//         T y = x / 3;
//         T y2 = y * y;
//         // 
//         // Using evaluate_even_polynomial to have powers:
//         // 0, 2, 4, 6, 8, 10
//         //
//         T polynom = evaluate_even_polynomial(H1_coeff, y);
//         value = y2 * polynom;
//      }
    else                                // x in (3, \infty)
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
