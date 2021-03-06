cmake_minimum_required (VERSION 3.8)

# Hide "ALL_BUILD" and "ZERO_CHECK" in a folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set project name
project (BasicStarter)

# /////////////////////////////////////////////////////////////////////////////
# ////////////////////////// FUNCTIONS ////////////////////////////////////////
# /////////////////////////////////////////////////////////////////////////////
# Recreate the folder architecture inside the Visual Studio solution (might work for other IDEs as well)
function(VS_RegisterFiles _FILES)
    foreach(_file IN ITEMS ${_FILES})
        get_filename_component(_filepath "${_file}" PATH)
        string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_filepath}")
        string(REPLACE "/" "\\" _group_path "${_group_path}")
        source_group("${_group_path}" FILES "${_file}")
    endforeach()
endfunction()

# Set C++ version
set(CXX_STANDARD 17)

# Set the folder where the executable is created
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# /////////////////////////////////////////////////////////////////////////////
# ////////////////////////// LIBRAIRIES ///////////////////////////////////////
# /////////////////////////////////////////////////////////////////////////////

link_directories(${CMAKE_SOURCE_DIR}/lib)

# find the required packages
if(UNIX)
  find_package(GLM REQUIRED)
  message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
  find_package(GLFW3 REQUIRED)
  message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
  # find_package(GLEW REQUIRED)
  # message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")
endif(UNIX)

add_library(GLAD "thirdparty/glad.c")

if(WIN32)
  set(LIBS glfw3 opengl32 STB_IMAGE GLAD)
elseif(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  find_package(OpenGL REQUIRED)
  add_definitions(${OPENGL_DEFINITIONS})
  find_package(X11 REQUIRED)
  # note that the order is important for setting the libs
  # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
  set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xcursor GL dl pthread ${ASSIMP_LIBRARIES})
  set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
elseif(APPLE)
  INCLUDE_DIRECTORIES(/System/Library/Frameworks)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  FIND_LIBRARY(IOKit_LIBRARY IOKit)
  FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
  MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
  SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
  SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY})
  set(LIBS ${LIBS} ${APPLE_LIBS})
else()
  set(LIBS )
endif(WIN32)

add_library(STB_IMAGE "thirdparty/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

set(LIBS ${LIBS} GLAD)

macro(makeLink src dest target)
  add_custom_command(TARGET ${target} POST_BUILD COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}  DEPENDS  ${dest} COMMENT "mklink ${src} -> ${dest}")
endmacro()

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

# /////////////////////////////////////////////////////////////////////////////
# ////////////////////////// RESSOURCES ///////////////////////////////////////
# /////////////////////////////////////////////////////////////////////////////
# Configure assets header file
configure_file(src/helpers/RootDir.h src/helpers/RootDir.h)

# Set include directories
include_directories(
  ${CMAKE_BINARY_DIR}/src
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include)

# Grab all the source files
file(GLOB_RECURSE MY_SOURCES ${CMAKE_SOURCE_DIR}/src/*)
file(GLOB_RECURSE MY_SHADERS ${CMAKE_SOURCE_DIR}/res/shaders/*)
file(GLOB_RECURSE MY_MODELS ${CMAKE_SOURCE_DIR}/res/models/*)
file(GLOB_RECURSE MY_SCENES ${CMAKE_SOURCE_DIR}/res/scene/*)

# Create target executable
add_executable(${PROJECT_NAME}
  ${MY_SOURCES}
  ${MY_SHADERS} # we include them here only so that they will appear in the solution explorer of Visual Studio
  ${MY_SCENES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD ${CXX_STANDARD})

# define the include dirs
MESSAGE(STATUS " ${LIBS}")
target_link_libraries(${PROJECT_NAME} ${LIBS})

# Recreate the folder architecture inside the Visual Studio solution (might work for other IDEs as well)
VS_RegisterFiles("${MY_SOURCES}")
VS_RegisterFiles("${MY_SHADERS}")
VS_RegisterFiles("${MY_SCENES}")

# copy shader files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/res
  DESTINATION ${CMAKE_BINARY_DIR})

