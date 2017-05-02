cmake_minimum_required(VERSION 2.8)
PROJECT(3DCurator)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
if (ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
else()
  find_package(ItkVtkGlue REQUIRED)
  include(${ItkVtkGlue_USE_FILE})
  set(Glue ItkVtkGlue)
endif()

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED QUIET)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${Boost_INCLUDE_DIRS})

file(GLOB UI_FILES *.ui)
file(GLOB QT_WRAP *.h)
file(GLOB CPP_FILES *.cpp)

set(RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/assets/resources.qrc)
qt5_add_resources(RESOURCE_ADDED ${RESOURCE})

qt5_wrap_ui(UISrcs ${UI_FILES})
set_source_files_properties(${RESOURCE_ADDED} PROPERTIES GENERATED ON)
add_executable(3DCurator ${CPP_FILES} ${UISrcs} ${QT_WRAP} ${RESOURCE_ADDED})
qt5_use_modules(3DCurator Core Gui)
target_link_libraries(3DCurator ${Glue} ${VTK_LIBRARIES} ${ITK_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBS})
