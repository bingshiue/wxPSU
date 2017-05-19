message ("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message ("CMAKE_CURRENT_BINARY_DIR:" ${CMAKE_CURRENT_BINARY_DIR})

# Glob TaskSystem Header Files
file(GLOB TASKSYSTEM_HEADER *.h)
message("TASKSYSTEM_HEADER: " ${TASKSYSTEM_HEADER})

# Collect TaskSystem SRC File
file(GLOB TASKSYSTEM_SOURCE *.cpp)
message("TASKSYSTEM_SOURCE: " ${TASKSYSTEM_SOURCE})

# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
#source_group("" FILES ${MATH_SOURCES})
#source_group("hidapi" FILES ${HIDAPI_SOURCE})
#source_group("include" FILES ${HIDAPI_HEADER})

# Properties->C/C++->General->Additional Include Directories
include_directories (".")

add_library(TaskSystem STATIC ${TASKSYSTEM_SOURCE} ${TASKSYSTEM_HEADER})

set_property(TARGET TaskSystem PROPERTY FOLDER "libraries")

# Add Preprocessor
if(WIN32)
target_compile_options(TaskSystem PRIVATE "/D_CRT_SECURE_NO_DEPRECATE")
elseif(UNIX)
target_compile_options(TaskSystem PRIVATE "-D__WXGTK__")
endif()

# Properties->General->Output Directory
set_target_properties(TaskSystem PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Set Include/Link Path For wxWidgets					  
if(wxWidgets_FOUND)
message ("WXWIDGETS Found")
message ("WXWIDGETS Include DIR:" ${wxWidgets_INCLUDE_DIRS})
message ("WXWIDGETS Libraries:" ${wxWidgets_LIBRARIES})
message ("WXWIDGETS Libraries DIR:" ${wxWidgets_LIBRARY_DIRS})

include_directories (${wxWidgets_INCLUDE_DIRS})
#target_link_libraries(TaskSystem ${wxWidgets_LIBRARIES})
else()
message ("WXWIDGETS Not Found")
endif()
					  
# Adds logic to INSTALL.vcproj to copy math.dll to the destination directory
#install (TARGETS math
#         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install
#         LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/_install)



