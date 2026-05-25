#ifndef BOOST_MATH_STRUVE_HPP
#define BOOST_MATH_STRUVE_HPP

#ifdef _MSC_VER
#  pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/detail/struve_hn.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>

namespace boost{ namespace math{

namespace detail{

template <class T, class Policy>
BOOST_MATH_GPU_ENABLED inline T struve_h_imp(int v, T x, const bessel_int_tag&, const Policy& pol)
{
   return struve_hn(v, x, pol);
}

}; // namespace detail

template <class T1, class T2, class Policy>
BOOST_MATH_GPU_ENABLED inline typename detail::bessel_traits<T1, T2, Policy>::result_type struve_h(T1 v, T2 x, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename detail::bessel_traits<T1, T2, Policy>::optimisation_tag tag_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<result_type, Policy>(detail::struve_h_imp<value_type>(v, static_cast<value_type>(x), tag_type(), forwarding_policy()), "boost::math::struve_h<%1%>(%1%,%1%)");
}

template <class T1, class T2>
BOOST_MATH_GPU_ENABLED inline typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type struve_h(T1 v, T2 x)
{
   return struve_h(v, x, policies::policy<>());
}


} // namespace math
} // namespace boost

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif // BOOST_MATH_STRUVE_HPP