#ifndef BOOST_MATH_STRUVE_HN_HPP
#define BOOST_MATH_STRUVE_HN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/assert.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/detail/struve_h0.hpp>
#include <boost/math/special_functions/detail/struve_h1.hpp>
#include <cmath>

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
        factor *= (n & 0x1) ? 1 : -1;  // H_{n}(-z) = (-1)^n H_n(z)
        x = -x;
    }

    if (x == 0)
    {
        return static_cast<T>(0);
    }
    if (n >= 1000)
    {
        T order = static_cast<T>(n);
        value = exp(order * (static_cast<T>(1) + log(x / (2 * order))));
        value *= x / (pi<T>() * order * root_two<T>());
        return factor * value;
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

    T u_n, v_n, u_tmp, v_tmp;
    if (x < n) { // backward reccurence
        
        T u_current(1), u_next(0), v_current(0), v_next(0);
        for (int k = 2 * n; k >= 0; k--) {

            u_tmp = u_current;
            v_tmp = v_current;
            T frac = std::pow(0.5 * x, k + 1) / (root_pi<T>() * boost::math::tgamma(T(k + 1) + T(1.5)));

            u_current = -u_next + 2 * ((k + 1) / x) * u_current;
            v_current = -v_next + 2 * ((k + 1) / x) * v_current + frac;

            if (k == n) {
                u_n = u_current;
                v_n = v_current;
            }

            u_next = u_tmp;
            v_next = v_tmp;
        }
        
        value = (struve_h0(x) - v_current) * u_n / u_current + v_n;

    } else { // forward reccurence
        prev = struve_h0(x);
        current = struve_h1(x);
        T frac(1);

        policies::check_series_iterations<T>("boost::math::struve_h_n<%1%>(%1%,%1%)", static_cast<unsigned>(n), pol);
        for (int k = 1; k < n; k++)
        {
            T numerator = 2 * k * current;
            T t1 = numerator / x;

            frac *= (x / 2);
            T denominator = root_pi<T>() * boost::math::tgamma(T(k) + T(1.5));
            T t2 = frac / denominator;

            value = t1 + t2 - prev;
            prev = current;
            current = value;
        }
    }
    value *= factor;

    return value;
}

}}} // namespaces

#endif // BOOST_MATH_STRUVE_HN_HPP