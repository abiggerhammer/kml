//
// Copyright (c) 2002--2010
// Toon Knapen, Karl Meerbergen, Kresimir Fresl,
// Thomas Klimpel and Rutger ter Borg
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// THIS FILE IS AUTOMATICALLY GENERATED
// PLEASE DO NOT EDIT!
//

#ifndef BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GEJSV_HPP
#define BOOST_NUMERIC_BINDINGS_LAPACK_DRIVER_GEJSV_HPP

#include <boost/assert.hpp>
#include <boost/numeric/bindings/begin.hpp>
#include <boost/numeric/bindings/detail/array.hpp>
#include <boost/numeric/bindings/is_column_major.hpp>
#include <boost/numeric/bindings/is_mutable.hpp>
#include <boost/numeric/bindings/lapack/workspace.hpp>
#include <boost/numeric/bindings/remove_imaginary.hpp>
#include <boost/numeric/bindings/size.hpp>
#include <boost/numeric/bindings/stride.hpp>
#include <boost/numeric/bindings/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

//
// The LAPACK-backend for gejsv is the netlib-compatible backend.
//
#include <boost/numeric/bindings/lapack/detail/lapack.h>
#include <boost/numeric/bindings/lapack/detail/lapack_option.hpp>

namespace boost {
namespace numeric {
namespace bindings {
namespace lapack {

//
// The detail namespace contains value-type-overloaded functions that
// dispatch to the appropriate back-end LAPACK-routine.
//
namespace detail {

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * float value-type.
//
inline std::ptrdiff_t gejsv( const char joba, const char jobu, const char jobv,
        const char jobr, const char jobt, const char jobp,
        const fortran_int_t m, const fortran_int_t n, float* a,
        const fortran_int_t lda, float* sva, float* u,
        const fortran_int_t ldu, float* v, const fortran_int_t ldv,
        float* work, const fortran_int_t lwork, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_SGEJSV( &joba, &jobu, &jobv, &jobr, &jobt, &jobp, &m, &n, a, &lda,
            sva, u, &ldu, v, &ldv, work, &lwork, iwork, &info );
    return info;
}

//
// Overloaded function for dispatching to
// * netlib-compatible LAPACK backend (the default), and
// * double value-type.
//
inline std::ptrdiff_t gejsv( const char joba, const char jobu, const char jobv,
        const char jobr, const char jobt, const char jobp,
        const fortran_int_t m, const fortran_int_t n, double* a,
        const fortran_int_t lda, double* sva, double* u,
        const fortran_int_t ldu, double* v, const fortran_int_t ldv,
        double* work, const fortran_int_t lwork, fortran_int_t* iwork ) {
    fortran_int_t info(0);
    LAPACK_DGEJSV( &joba, &jobu, &jobv, &jobr, &jobt, &jobp, &m, &n, a, &lda,
            sva, u, &ldu, v, &ldv, work, &lwork, iwork, &info );
    return info;
}

} // namespace detail

//
// Value-type based template class. Use this class if you need a type
// for dispatching to gejsv.
//
template< typename Value >
struct gejsv_impl {

    typedef Value value_type;
    typedef typename remove_imaginary< Value >::type real_type;

    //
    // Static member function for user-defined workspaces, that
    // * Deduces the required arguments for dispatching to LAPACK, and
    // * Asserts that most arguments make sense.
    //
    template< typename MatrixA, typename VectorSVA, typename MatrixU,
            typename MatrixV, typename WORK, typename IWORK >
    static std::ptrdiff_t invoke( const char joba, const char jobu,
            const char jobv, const char jobr, const char jobt,
            const char jobp, MatrixA& a, VectorSVA& sva, MatrixU& u,
            MatrixV& v, detail::workspace2< WORK, IWORK > work ) {
        namespace bindings = ::boost::numeric::bindings;
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixU >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_column_major< MatrixV >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                VectorSVA >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixU >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (boost::is_same< typename remove_const<
                typename bindings::value_type< MatrixA >::type >::type,
                typename remove_const< typename bindings::value_type<
                MatrixV >::type >::type >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< VectorSVA >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixU >::value) );
        BOOST_STATIC_ASSERT( (bindings::is_mutable< MatrixV >::value) );
        BOOST_ASSERT( bindings::size(work.select(fortran_int_t())) >=
                min_size_iwork( bindings::size_row(a),
                bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size(work.select(real_type())) >=
                min_size_work( joba, jobu, jobv, bindings::size_row(a),
                bindings::size_column(a) ));
        BOOST_ASSERT( bindings::size_minor(a) == 1 ||
                bindings::stride_minor(a) == 1 );
        BOOST_ASSERT( bindings::size_minor(u) == 1 ||
                bindings::stride_minor(u) == 1 );
        BOOST_ASSERT( bindings::size_minor(v) == 1 ||
                bindings::stride_minor(v) == 1 );
        BOOST_ASSERT( bindings::size_row(a) >= 0 );
        BOOST_ASSERT( bindings::stride_major(a) >= std::max< std::ptrdiff_t >(1,
                bindings::size_row(a)) );
        return detail::gejsv( joba, jobu, jobv, jobr, jobt, jobp,
                bindings::size_row(a), bindings::size_column(a),
                bindings::begin_value(a), bindings::stride_major(a),
                bindings::begin_value(sva), bindings::begin_value(u),
                bindings::stride_major(u), bindings::begin_value(v),
                bindings::stride_major(v),
                bindings::begin_value(work.select(real_type())),
                bindings::size(work.select(real_type())),
                bindings::begin_value(work.select(fortran_int_t())) );
    }

    //
    // Static member function that
    // * Figures out the minimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member function
    // * Enables the unblocked algorithm (BLAS level 2)
    //
    template< typename MatrixA, typename VectorSVA, typename MatrixU,
            typename MatrixV >
    static std::ptrdiff_t invoke( const char joba, const char jobu,
            const char jobv, const char jobr, const char jobt,
            const char jobp, MatrixA& a, VectorSVA& sva, MatrixU& u,
            MatrixV& v, minimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        bindings::detail::array< real_type > tmp_work( min_size_work( joba,
                jobu, jobv, bindings::size_row(a),
                bindings::size_column(a) ) );
        bindings::detail::array< fortran_int_t > tmp_iwork(
                min_size_iwork( bindings::size_row(a),
                bindings::size_column(a) ) );
        return invoke( joba, jobu, jobv, jobr, jobt, jobp, a, sva, u, v,
                workspace( tmp_work, tmp_iwork ) );
    }

    //
    // Static member function that
    // * Figures out the optimal workspace requirements, and passes
    //   the results to the user-defined workspace overload of the 
    //   invoke static member
    // * Enables the blocked algorithm (BLAS level 3)
    //
    template< typename MatrixA, typename VectorSVA, typename MatrixU,
            typename MatrixV >
    static std::ptrdiff_t invoke( const char joba, const char jobu,
            const char jobv, const char jobr, const char jobt,
            const char jobp, MatrixA& a, VectorSVA& sva, MatrixU& u,
            MatrixV& v, optimal_workspace ) {
        namespace bindings = ::boost::numeric::bindings;
        return invoke( joba, jobu, jobv, jobr, jobt, jobp, a, sva, u, v,
                minimal_workspace() );
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array work.
    //
    static std::ptrdiff_t min_size_work( const char joba, const char jobu,
            const char jobv, const std::ptrdiff_t m, const std::ptrdiff_t n ) {
        if ( jobu == 'N' && jobv == 'N' ) {
            if ( joba != 'E' && joba != 'G' )
                return std::max< std::ptrdiff_t >( std::max<
                        std::ptrdiff_t >( 2*m+n, 4*n+1), 7 );
            else
                return std::max< std::ptrdiff_t >( std::max<
                        std::ptrdiff_t >( 2*m+n, n*n+4*n), 7 );
        } else if ( jobu == 'N' || jobu == 'W' || jobv == 'N' ||
                jobv == 'W' ) {
                return std::max< std::ptrdiff_t >( 2*n+m, 7);
        } else {
            if ( jobv != 'J' )
                return 6*n+2*n*n;
            else
                return std::max< std::ptrdiff_t >( m+3*n+n*n, 7);
        }
    }

    //
    // Static member function that returns the minimum size of
    // workspace-array iwork.
    //
    static std::ptrdiff_t min_size_iwork( const std::ptrdiff_t m,
            const std::ptrdiff_t n ) {
        return m+3*n;
    }
};


//
// Functions for direct use. These functions are overloaded for temporaries,
// so that wrapped types can still be passed and used for write-access. In
// addition, if applicable, they are overloaded for user-defined workspaces.
// Calls to these functions are passed to the gejsv_impl classes. In the 
// documentation, most overloads are collapsed to avoid a large number of
// prototypes which are very similar.
//

//
// Overloaded function for gejsv. Its overload differs for
// * User-defined workspace
//
template< typename MatrixA, typename VectorSVA, typename MatrixU,
        typename MatrixV, typename Workspace >
inline typename boost::enable_if< detail::is_workspace< Workspace >,
        std::ptrdiff_t >::type
gejsv( const char joba, const char jobu, const char jobv,
        const char jobr, const char jobt, const char jobp, MatrixA& a,
        VectorSVA& sva, MatrixU& u, MatrixV& v, Workspace work ) {
    return gejsv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( joba, jobu, jobv, jobr, jobt, jobp, a,
            sva, u, v, work );
}

//
// Overloaded function for gejsv. Its overload differs for
// * Default workspace-type (optimal)
//
template< typename MatrixA, typename VectorSVA, typename MatrixU,
        typename MatrixV >
inline typename boost::disable_if< detail::is_workspace< MatrixV >,
        std::ptrdiff_t >::type
gejsv( const char joba, const char jobu, const char jobv,
        const char jobr, const char jobt, const char jobp, MatrixA& a,
        VectorSVA& sva, MatrixU& u, MatrixV& v ) {
    return gejsv_impl< typename bindings::value_type<
            MatrixA >::type >::invoke( joba, jobu, jobv, jobr, jobt, jobp, a,
            sva, u, v, optimal_workspace() );
}

} // namespace lapack
} // namespace bindings
} // namespace numeric
} // namespace boost

#endif