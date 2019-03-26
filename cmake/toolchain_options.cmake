##
#
# Copyright © 2019 Ruben Van Boxem
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.o

# Compiler options
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-pedantic-errors -Wextra -Wconversion -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Werror ${CMAKE_CXX_FLAGS}")
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
elseif(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  string(REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  if(NOT ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
      add_compile_options(/wd4503)
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "-pedantic-errors -Wextra -Wconversion -Winit-self -Wmissing-include-dirs -Wstrict-aliasing -Werror ${CMAKE_CXX_FLAGS}")
  if(MINGW)
    link_libraries(-lpthread)
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
  else()
    add_compile_options(-Wno-error=unused-command-line-argument)
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
  endif()
endif()

OPTION(GC_SECTIONS "Enable function and data sections generation for the compiler, and also remove unused sections on link" ON)
OPTION(SPLIT_DEBUG "Split debug info from the rest of the binaries. This should improve link time")

if(GC_SECTIONS)
  if(MINGW OR UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections")
  endif()
endif()

if(SPLIT_DEBUG)
  if(NOT MINGW AND UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -gsplit-dwarf")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -gsplit-dwarf")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--gdb-index")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=gold -Wl,--gdb-index")
  endif()
endif()
