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

    BOOST_MATH_STATIC const T P1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0707355302630645936750591582287)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00207185634168603648672328873045)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0000314267803061135186741922283008)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000240524915142590080089672932483)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.00000000100629922419318636560262041863)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.19727473870844852931259370195e-12)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.00671658115837495154166406484e-15))
    };
    BOOST_MATH_STATIC const T Q1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.010709821019495754756436869509)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000563519497780850996300711774198)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000189131392123180385940303583515)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.34461726487495401100979798332e-10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.61778054381056332955101039727e-13)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.37200932001096714788701957446e-16))
    };
    BOOST_MATH_STATIC const T P2[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0707355302630643207871829899468)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00205866317889296216055287310135)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0000310616746928870978096345286205)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000235280060955466445919212973876)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -9.70593779236440095427094477126e-10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.07630860662005894450785907496e-12)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.84282040708072928521548904116e-15))
    };
    BOOST_MATH_STATIC const T Q2[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0108963349643807231569770672193)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000586509485689252087868312018462)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000202982441298818573421754324052)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.86703348546725372477308884897e-10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.89362585208136399079514131897e-13)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.07596958785990493572381645341e-16))
    };
    BOOST_MATH_STATIC const T P3[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0707355302624461161899572006688)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.00203852409584127337138973985565)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -0.0000305120212958885834445688786211)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000227467610401218116778917967584)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -9.18642512975190989060158994717e-10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.90562352986910869463948025244e-12)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.62213766893678773519215799217e-15))
    };
    BOOST_MATH_STATIC const T Q3[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0111810445398670918107030761353)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0000622687904502169707040593979945)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.000000225725974749920826236395863646)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.77999860152313495211063851528e-10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.03523581226795604737619670593e-12)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.10624344652668178394832713731e-15))
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
        value = x * (two_div_pi<T>() + y * r);
    }
    else if (x <= 5)                  // x in (4, 5]
    {
        T y = x * x;
        BOOST_MATH_ASSERT(sizeof(P2) == sizeof(Q2));
        T r = evaluate_rational(P2, Q2, y);
        value = x * (two_div_pi<T>() + y * r);
    }
    else if (x <= 8)                  // x in (5, 8]
    {
        T y = x * x;
        BOOST_MATH_ASSERT(sizeof(P3) == sizeof(Q3));
        T r = evaluate_rational(P3, Q3, y);
        value = x * (two_div_pi<T>() + y * r);
    }
    else                                // x in (8, \infty)
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
