cmake_minimum_required(VERSION 3.1.0)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

set(CMAKE_CONFIGURATION_TYPES Release)
set(CMAKE_AUTOMOC ON)

PROJECT(3DCurator)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
if(ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
else()
  find_package(ItkVtkGlue REQUIRED)
  include(${ItkVtkGlue_USE_FILE})
  set(GLUE ItkVtkGlue)
endif()

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
find_package(Qt5Core REQUIRED QUIET)
find_package(Qt5Gui REQUIRED QUIET)
find_package(Qt5LinguistTools REQUIRED QUIET)
find_package(Qt5Widgets REQUIRED QUIET)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE CPP_FILES *.cpp)
file(GLOB_RECURSE UI_FILES *.ui)
file(GLOB_RECURSE QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../assets/*.qrc)

qt5_wrap_ui(UI_SOURCES ${UI_FILES})
qt5_add_resources(QRC_SOURCES ${QRC_FILES})

set_source_files_properties(${QRC_SOURCES} PROPERTIES GENERATED ON)
add_executable(3DCurator ${UI_SOURCES} ${QRC_SOURCES} ${HEADER_FILES} ${CPP_FILES})
target_link_libraries(3DCurator Qt5::Core Qt5::Gui Qt5::Widgets ${GLUE} ${VTK_LIBRARIES} ${ITK_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBS})
