#
#  The Kernel-Machine Library
#  Copyright (C) 2013 by Rutger ter Borg
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
#
 
add_executable( gaussian gaussian.cpp )
target_link_libraries( gaussian ${Boost_LIBRARIES} ${BLAS_LIBRARIES} )

add_executable( incomplete_cholesky incomplete_cholesky.cpp )
target_link_libraries( incomplete_cholesky ${Boost_LIBRARIES} ${BLAS_LIBRARIES} )

add_executable( svm_classification svm_classification.cpp )


add_executable( svm_regression svm_regression.cpp )
target_link_libraries( svm_regression ${Boost_LIBRARIES} ${BLAS_LIBRARIES} )



