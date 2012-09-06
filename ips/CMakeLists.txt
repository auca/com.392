#
# CMakeLists.txt
#
# Created by Dmitrii Toksaitov on Sat Aug 11 12:13:58 KGT 2012
#

# Names, Sources

set(IPS_EXECUTABLE ips)
set(IPS_SOURCES ips.c)

# Libraries

# PNG
find_package(PNG REQUIRED)

# Includes

include_directories(${PNG_INCLUDE_DIRS})

# Targets

add_executable(${IPS_EXECUTABLE} ${IPS_SOURCES})
target_link_libraries(${IPS_EXECUTABLE} ${PNG_LIBRARIES})

