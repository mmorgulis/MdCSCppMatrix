cmake_minimum_required(VERSION 3.16)

project(MdCSCppMatrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MdCSCppMatrix main.cpp
    matrix.hpp
)

include(GNUInstallDirs)
install(TARGETS MdCSCppMatrix
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
