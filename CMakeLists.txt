cmake_minimum_required(VERSION 2.8)
project(bztask)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB glib-2.0 REQUIRED)
pkg_check_modules(XMLRPC xmlrpc_client++ REQUIRED)
pkg_check_modules(YAML yaml-cpp REQUIRED)

add_subdirectory(src)
