#ifndef BOOST_MATH_STRUVE_HN_HPP
#define BOOST_MATH_STRUVE_HN_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
BOOST_MATH_GPU_ENABLED T struve_hn(int n, T x, const Policy& pol)
{
    T value(0), factor, current, prev, next;

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
    //
    // Special cases:
    //
    if(asymptotic_bessel_large_x_limit(T(n), x))
       return factor * asymptotic_bessel_j_large_x_2<T>(T(n), x, pol);
    if (n == 0)
    {
        return factor * bessel_j0(x);
    }
    if (n == 1)
    {
        return factor * bessel_j1(x);
    }

    if (x == 0)                             // n >= 2
    {
        return static_cast<T>(0);
    }
}

}}} // namespaces

#endif // BOOST_MATH_STRUVE_HN_HPP