# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\JXCqmlTools_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\JXCqmlTools_autogen.dir\\ParseCache.txt"
  "JXCqmlTools_autogen"
  )
endif()
