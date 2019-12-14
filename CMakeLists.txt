##
#
# The MIT License (MIT)
#
# Copyright © 2019 Ruben Van Boxem
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

cmake_minimum_required(VERSION 3.13)
project(petl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(toolchain_options)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Boilerplate
function(exclude_from_build)
  set_source_files_properties(${ARGV} PROPERTIES HEADER_FILE_ONLY TRUE)
endfunction()

# petl itself
set(petl_sources
    petl/expression/basic/double.h++
    petl/expression/basic/int.h++
    petl/expression/basic/literal.h++
    petl/expression/sequence.h++
    petl/no_attribute.h++
    petl/petl.h++
    petl/traits/attribute_of.h++
    petl/traits/class_type.h++
    petl/traits/first_type.h++
    petl/traits/is_tuple.h++
    petl/traits/pointee_type.h++
    petl/utility/as_tuple.h++
    petl/utility/flatten_tuple.h++
    petl/utility/overload.h++
    petl/utility/tuple_rank.h++
    petl/view/sequence.h++
   )
add_library(petl INTERFACE)
target_sources(petl INTERFACE ${petl_sources} ${miscellaneous})
target_include_directories(petl INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
                                          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_features(petl INTERFACE cxx_std_17)

#until CMake and IDEs get along and show INTERFACE targets with their target_sources
add_custom_target(petl_sources SOURCES
    ${petl_sources}
    README.md
    LICENSE.md
    .gitignore
    appveyor.yml
    .travis.yml
    ci/setup_cmake.sh
    ci/setup_libcxx.sh
    ci/setup_ninja.sh
    cmake/toolchain_options.cmake
    )

# tests
enable_testing()
add_subdirectory(tests)
