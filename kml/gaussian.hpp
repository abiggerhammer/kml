/***************************************************************************
 *  The Kernel-Machine Library                                             *
 *  Copyright (C) 2004--2006 by Rutger W. ter Borg                         *
 *                                                                         *
 *  This library is free software; you can redistribute it and/or          *
 *  modify it under the terms of the GNU Lesser General Public             *
 *  License as published by the Free Software Foundation; either           *
 *  version 2.1 of the License, or (at your option) any later version.     *
 *                                                                         *
 *  This library is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *  Lesser General Public License for more details.                        *
 *                                                                         *
 *  You should have received a copy of the GNU Lesser General Public       *
 *  License along with this library; if not, write to the Free Software    *
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  *
 ***************************************************************************/

#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include <boost/call_traits.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/type_traits.hpp>
#include <kml/input_value.hpp>
#include <kml/distance.hpp>
#include <cassert>

namespace kml {

/*!
 
\brief Gaussian kernel of the form \f$ f(x)=e^{-\gamma\|x - \mu\|} \f$ where
	\f$ \gamma = \frac{1}{\sigma^2} \f$
\param T defines the underlying input data type
	(distance_square<T, T> must be defined, which is done for
	scalar and vector types in distance.hpp)
 
This is a template class that creates a functor for the Gaussian kernel.
 
Complexity: O(d+c), i.e., a little more time than needed for computing the dot product
 
\ingroup kernels
 
*/

template<typename T>
class gaussian: public std::binary_function<T, T, typename input_value<T>::type> {
public:
    /*! Refinement of AdaptableBinaryFunction */
    typedef T first_argument_type;
    typedef T second_argument_type;
    typedef typename input_value<T>::type result_type;

    /*! Refinement of Kernel */
    typedef gaussian<T> type;

    // scalar type ... 
    typedef typename input_value<T>::type scalar_type;
    friend class boost::serialization::access;

    /*! Refinement of DefaultConstructible */
    gaussian() {
        set_width(1.0);
    }

    /*! Refinement of CopyConstructible */
    gaussian( type const &other ) {
        copy( other );
    }

    /*! Refinement of Assignable */
    type &operator=( type const &other ) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    /*! Construct a Gaussian kernel by providing a value for sigma
        \param sigma  the width of the gaussian kernel */
    gaussian( typename boost::call_traits<scalar_type>::param_type sigma ) {
        set_width(sigma);
    }

    /*! Kernel constructor by providing TokenIterators */
    template<typename TokenIterator>
    gaussian( TokenIterator const begin, TokenIterator const end ) {
        if (begin == end ) {
            // default value
            set_width( 1.0 );
        } else {
            set_width( boost::lexical_cast<double>( *begin ) );
        }
    }

    /*! Returns the result of the evaluation of the Gaussian kernel for its arguments
    	\param u input pattern u
        \param v input pattern v
    	\return \f$ e^{-\gamma\|u - v\|} \f$
    */
    scalar_type operator()( T const &u, T const &v ) const {
        return std::exp( exp_factor * distance_square( u, v ) );
    }

    /*! Sets \f$ \sigma \f$. */
    void set_width( typename boost::call_traits<scalar_type>::param_type sigma ) {
        assert( sigma > 0.0 );
        width = sigma;
        exp_factor = -1.0 / (2.0*sigma*sigma);
    }

    /*! Returns \f$ \sigma \f$. */
    scalar_type const get_width() const {
        return width;
    }

    /*! Sets \f$ \gamma \f$. */
    void set_gamma( typename boost::call_traits<scalar_type>::param_type gamma ) {
        set_scale_factor( gamma );
    }

    /*! Sets \f$ \gamma \f$. */
    void set_scale_factor( typename boost::call_traits<scalar_type>::param_type gamma ) {
        assert( gamma > 0.0 );
        width = std::sqrt(0.5 / gamma);
        exp_factor = -gamma;
    }

    /*! Returns \f$ \gamma \f$. */
    scalar_type const get_gamma() const {
        return -exp_factor;
    }

    /*! Returns \f$ \gamma \f$. */
    scalar_type const get_scale_factor() const {
        return -exp_factor;
    }

    /*! The dimension of the feature space */
    scalar_type const dimension() const {
        return std::numeric_limits<scalar_type>::infinity();
    }

    /*! loading and saving capabilities */
    template<class Archive>
    void serialize( Archive &archive, unsigned int const version ) {
        archive & width;
        archive & exp_factor;
    }

    // for debugging purposes
    friend std::ostream& operator<<(std::ostream &os, type const &k) {
        os << "Gaussian kernel (exp(-||u-v||^2/(2*" << k.width << "^2))" << std::endl;
        return os;
    }

private:
    void copy( type const &other ) {
        width = other.width;
        exp_factor = other.exp_factor;
    }

    scalar_type width;
    scalar_type exp_factor;

};

} // namespace kml





namespace boost {
namespace serialization {

template<typename T>
struct tracking_level< kml::gaussian<T> > {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    BOOST_STATIC_CONSTANT(
        int,
        value = tracking_level::type::value
    );
};

}
}

#endif
