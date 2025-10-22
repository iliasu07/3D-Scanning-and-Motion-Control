# Install script for directory: /home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "PATH")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/AdolcForward"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/AlignedVector3"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/ArpackSupport"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/AutoDiff"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/BVH"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/EulerAngles"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/FFT"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/IterativeSolvers"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/KroneckerProduct"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/LevenbergMarquardt"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/MatrixFunctions"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/MPRealSupport"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/NNLS"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/NonLinearOptimization"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/NumericalDiff"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/OpenGLSupport"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/Polynomials"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/SparseExtra"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/SpecialFunctions"
    "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/Splines"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/build/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/iliasu07/Documents/GitHub/3D-SMC/lib/eigen-5.0.0/build/unsupported/Eigen/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
