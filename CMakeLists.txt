cmake_minimum_required (VERSION 3.0)
 
message ("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message ("CMAKE_CURRENT_BINARY_DIR:" ${CMAKE_CURRENT_BINARY_DIR}) 
 
# Maps to Visual Studio solution file (Tutorial.sln)
# The solution will have all targets (exe, lib, dll) 
# as Visual Studio projects (.vcproj)
project (TRC2PMBUSTool)
 
# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
 
# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
 
# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
# Print CMAKE_CXX_FLAGS
message ("cxx Flags:" ${CMAKE_CXX_FLAGS})

# Find wxWidgets library
find_package(wxWidgets COMPONENTS core base REQUIRED)

if(wxWidgets_FOUND)
message ("WXWIDGETS Found")
message ("WXWIDGETS Include DIR:" ${wxWidgets_INCLUDE_DIRS})
message ("WXWIDGETS Libraries:" ${wxWidgets_LIBRARIES})
message ("WXWIDGETS Libraries DIR:" ${wxWidgets_LIBRARY_DIRS})
else()
message ("WXWIDGETS Not Found")
endif()

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(hidapi-0.7.0)
add_subdirectory(hidapi-0.7.0/hidtest)
add_subdirectory(TaskSystem)
add_subdirectory(libGIS)
add_subdirectory(TRC2PMBUSTool)
 
# Turn on CMake testing capabilities
#enable_testing()
 
# Add test cases
#add_test(AppTest1 ${PROJECT_BINARY_DIR}/bin/app 100)
#add_test(AppTest2 ${PROJECT_BINARY_DIR}/bin/app 200)
#add_test(AppTest3 ${PROJECT_BINARY_DIR}/bin/app 300)
