#ifndef BOOST_MATH_STRUVE_HN_HPP
#define BOOST_MATH_STRUVE_HN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/assert.hpp>
#include </Users/nailzaripov/boost/boost/math/special_functions/detail/struve_h0.hpp>
#include </Users/nailzaripov/boost/boost/math/special_functions/detail/struve_h1.hpp>

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
BOOST_MATH_GPU_ENABLED T struve_hn(int n, T x, const Policy& pol)
{
    T value(0), factor;

    BOOST_MATH_STD_USING

    //
    // Reflection has to come first:
    //
    if (n < 0)
    {
        factor = static_cast<T>((n & 0x1) ? -1 : 1);  // H_{-n}(z) = (-1)^n H_n(z)
        n = -n;
    }
    else
    {
        factor = 1;
    }
    if(x < 0)
    {
        factor *= (n & 0x1) ? -1 : 1;  // H_{n}(-z) = (-1)^n H_n(z)
        x = -x;
    }

    // TODO: large asymptotic realization

    if (x == 0)
    {
        return static_cast<T>(0);
    }
    if (n == 0)
    {
        return factor * struve_h0(x);
    }
    // if (n == 1)
    // {
    //     return factor * struve_h1(x);
    // }

    BOOST_MATH_ASSERT(n > 1);
    return value;
}

}}} // namespaces

#endif // BOOST_MATH_STRUVE_HN_HPP