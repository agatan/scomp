cmake_minimum_required(VERSION 3.2)

project(scomp CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

include_directories(include)

find_package(Boost 1.59.0 REQUIRED COMPONENTS system)
if (!${Boost_FOUND})
  message(FATAL_ERROR "Boost library not found.")
endif()
include_directories(${Boost_INCLUDE_DIRS})

# LLVM settings {{{
execute_process(
  COMMAND
  llvm-config --version
  OUTPUT_VARIABLE
  LLVM_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
execute_process(
  COMMAND
  llvm-config --includedir
  OUTPUT_VARIABLE
  LLVM_INCLUDE_DIRS
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
execute_process(
  COMMAND
  llvm-config --libdir
  OUTPUT_VARIABLE
  LLVM_LIBRARY_DIRS
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
execute_process(
  COMMAND
  llvm-config --libnames
  OUTPUT_VARIABLE
  LLVM_LIBRARY_NAMES_STRING
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
string(REGEX REPLACE " +" "; " LLVM_LIBRARY_NAMES ${LLVM_LIBRARY_NAMES_STRING})
string(REGEX REPLACE "lib([^.]*)\\.a" "\\1" LLVM_LIBRARY_NAMES ${LLVM_LIBRARY_NAMES})

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

execute_process(
  COMMAND
  llvm-config --system-libs
  OUTPUT_VARIABLE
  LLVM_SYS_LIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
string(REGEX MATCHALL "-l([^ ]+)" LLVM_SYS_LIBS ${LLVM_SYS_LIBS})
set(LLVM_SYS_LIBRARIES)
foreach(l ${LLVM_SYS_LIBS})
  string(REGEX REPLACE "-l([^ ]+)" "\\1" libname ${l})
  list(APPEND LLVM_SYS_LIBRARIES ${libname})
endforeach(l)

execute_process(
  COMMAND
  llvm-config --libs core support native asmparser asmprinter
  OUTPUT_VARIABLE
  LLVM_LIBS_STRING
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )
string(REGEX MATCHALL "-l([^ ]+)" LLVM_LIBS ${LLVM_LIBS_STRING})

set(LLVM_LIBRARIES)
foreach (l ${LLVM_LIBS})
  string(REGEX REPLACE "-l([^ ]+)" "\\1" libname ${l})
  list(APPEND LLVM_LIBRARIES ${libname})
endforeach()
# }}}

add_subdirectory(src)
