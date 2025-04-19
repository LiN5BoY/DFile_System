# Install script for directory: D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/JXCqmlTools")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/build/Desktop_Qt_6_6_3_MSVC2019_64bit-Release/QXlsx/QXlsxQt6.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QXlsxQt6" TYPE FILE FILES
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxabstractooxmlfile.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxabstractsheet.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxabstractsheet_p.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxcellformula.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxcell.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxcelllocation.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxcellrange.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxcellreference.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxchart.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxchartsheet.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxconditionalformatting.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxdatavalidation.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxdatetype.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxdocument.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxformat.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxglobal.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxrichstring.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxworkbook.h"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/QXlsx/header/xlsxworksheet.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/build/Desktop_Qt_6_6_3_MSVC2019_64bit-Release/QXlsx/CMakeFiles/QXlsx.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake"
         "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/build/Desktop_Qt_6_6_3_MSVC2019_64bit-Release/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/build/Desktop_Qt_6_6_3_MSVC2019_64bit-Release/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/build/Desktop_Qt_6_6_3_MSVC2019_64bit-Release/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/build/Desktop_Qt_6_6_3_MSVC2019_64bit-Release/QXlsx/QXlsxQt6Config.cmake"
    "D:/Projects/QT_PROJECT/JXC/JXCqmlTools/JXCqmlTools/build/Desktop_Qt_6_6_3_MSVC2019_64bit-Release/QXlsx/QXlsxQt6ConfigVersion.cmake"
    )
endif()

