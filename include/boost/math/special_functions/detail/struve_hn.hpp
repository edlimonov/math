#ifndef BOOST_MATH_STRUVE_HN_HPP
#define BOOST_MATH_STRUVE_HN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/assert.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/detail/struve_h0.hpp>
#include <boost/math/special_functions/detail/struve_h1.hpp>

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
BOOST_MATH_GPU_ENABLED T struve_hn(int n, T x, const Policy& pol)
{
    T value(0), factor, current, prev;

    BOOST_MATH_STD_USING
    using namespace boost::math::constants;

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
    if (n == 1)
    {
        return factor * struve_h1(x);
    }

    BOOST_MATH_ASSERT(n > 1);

    // large order only
    value = (x * constants::e<T>()) / (2 * static_cast<T>(n));
    T value_powered_n = value;

    for (int i = 0; i < n - 1; ++i) {
        value_powered_n *= value;
    }

    value = value_powered_n;
    value *= x;
    value /= (constants::pi<T>() * static_cast<T>(n) * constants::root_two<T>());

    // if (x <= 1) { // x in (0, 1]

    // } else {
    //     prev = struve_h0(x);
    //     current = struve_h1(x);
    //     T frac(1);

    //     policies::check_series_iterations<T>("boost::math::struve_h_n<%1%>(%1%,%1%)", static_cast<unsigned>(n), pol);
    //     for (int k = 1; k < n; k++)
    //     {
    //         T numerator = 2 * k * current;
    //         T t1 = numerator / x;

    //         frac *= (x / 2);
    //         T denominator = root_pi<T>() * gamma(T(k) + T(1.5));
    //         T t2 = frac / denominator;

    //         value = t1 + t2 - prev;
    //         prev = current;
    //         current = value;
    //     }
    // }

    // prev = struve_h0(x);
    // current = struve_h1(x);
    // T frac(1);

    // policies::check_series_iterations<T>("boost::math::struve_h_n<%1%>(%1%,%1%)", static_cast<unsigned>(n), pol);
    // for (int k = 1; k < n; k++)
    // {
    //     T numerator = 2 * k * current;
    //     T t1 = numerator / x;

    //     frac *= (x / 2);
    //     T denominator = root_pi<T>() * boost::math::tgamma(T(k) + T(1.5));
    //     T t2 = frac / denominator;

    //     value = t1 + t2 - prev;
    //     prev = current;
    //     current = value;
    // }
    value *= factor;

    return value;
}

}}} // namespaces

#endif // BOOST_MATH_STRUVE_HN_HPP