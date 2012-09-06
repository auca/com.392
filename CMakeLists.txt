#
# CMakeLists.txt
#
# Created by Dmitrii Toksaitov on Sat Aug 11 12:13:58 KGT 2012
#

cmake_minimum_required(VERSION 2.8)

project(ips C)

# Definitions

set(IPS_MAJOR_VERSION 1)
set(IPS_MINOR_VERSION 0)
set(IPS_PATCH_VERSION 0)

# Dependencies

add_subdirectory(deps/zlib)
add_subdirectory(deps/png)

# Sources

add_subdirectory(ips)

