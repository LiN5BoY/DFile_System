# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\JXCqmlTools_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\JXCqmlTools_autogen.dir\\ParseCache.txt"
  "JXCqmlTools_autogen"
  "QXlsx\\CMakeFiles\\QXlsx_autogen.dir\\AutogenUsed.txt"
  "QXlsx\\CMakeFiles\\QXlsx_autogen.dir\\ParseCache.txt"
  "QXlsx\\QXlsx_autogen"
  )
endif()
