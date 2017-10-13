cmake_minimum_required (VERSION 3.0)

message ("CMAKE_CURRENT_SOURCE_DIR:" ${CMAKE_CURRENT_SOURCE_DIR})
message ("CMAKE_CURRENT_BINARY_DIR:" ${CMAKE_CURRENT_BINARY_DIR})
message ("PROJECT_BINARY_DIR:" ${PROJECT_BINARY_DIR})
message ("CMAKE_CONFIGURATION_TYPES:" ${CMAKE_CONFIGURATION_TYPES})

# Glob TRC2PMBUSTool Header Files
file(GLOB TRC2PMBUSTool_HEADER *.h)
message("TRC2PMBUSTool_HEADER: " ${TRC2PMBUSTool_HEADER})

# Glob TRC2PMBUSTool Source Files
file(GLOB TRC2PMBUSTool_SOURCE *.cpp *.rc)
message("TRC2PMBUSTool_SOURCE: " ${TRC2PMBUSTool_SOURCE})

file(GLOB TOTALPHASE_SOURCE Aardvark/*.c)
message("TOTALPHASE_SOURCE: " ${TOTALPHASE_SOURCE})


# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
#source_group("" FILES ${MATH_SOURCES})
#source_group("hidapi" FILES ${HIDAPI_SOURCE})
#source_group("include" FILES ${HIDAPI_HEADER})

# Properties->C/C++->General->Additional Include Directories
include_directories (.)
include_directories (${CMAKE_SOURCE_DIR}/TaskSystem)
include_directories (${CMAKE_SOURCE_DIR}/hidapi-0.7.0/hidapi)

# Set Properties->General->Configuration Type to Application(.exe)
# Creates hidtest.exe with the listed sources (hidtest.cpp)
# Adds sources to the Solution Explorer
add_executable (TRC2PMBUSTool ${TRC2PMBUSTool_SOURCE} ${TOTALPHASE_SOURCE} ${TRC2PMBUSTool_HEADER})

# Creates a folder "executables" and adds target 
# project (hidapi.vcproj) under it
set_property(TARGET TRC2PMBUSTool PROPERTY FOLDER "executables")

# Add Preprocessor
if(WIN32)
target_compile_options(TRC2PMBUSTool PRIVATE "/EHsc")
target_compile_options(TRC2PMBUSTool PRIVATE "/openmp")
target_compile_options(TRC2PMBUSTool PRIVATE "/D__WXMSW__")
target_compile_options(TRC2PMBUSTool PRIVATE "/D_CRT_SECURE_NO_DEPRECATE")
target_compile_options(TRC2PMBUSTool PRIVATE "/D_UNICODE")
target_compile_options(TRC2PMBUSTool PRIVATE "/DUNICODE")
target_compile_options(TRC2PMBUSTool PRIVATE "/DMDd")
elseif(UNIX)
target_compile_options(TRC2PMBUSTool PRIVATE "-D_FILE_OFFSET_BITS=64") 
target_compile_options(TRC2PMBUSTool PRIVATE "-DWXUSINGDLL") 
target_compile_options(TRC2PMBUSTool PRIVATE "-D__WXGTK__")
#target_compile_options(TRC2PMBUSTool PRIVATE "-D_DEBUG")
endif()

if(UNIX)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -D_DEBUG")
endif()

#set_target_properties(TRC2PMBUSTool PROPERTIES
                      #COMPILE_DEFINITIONS "_CRT_SECURE_NO_DEPRECATE")

#set_target_properties(TRC2PMBUSTool PROPERTIES
					  #COMPILE_DEFINITIONS "__WXMSW__")
					  
# Properties->General->Output Directory
if(WIN32)	
set_target_properties(TRC2PMBUSTool PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()
			
if(WIN32)		  
set_target_properties(TRC2PMBUSTool PROPERTIES
		      LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

# Link Libraries
target_link_libraries(TRC2PMBUSTool hidapi)				  
target_link_libraries(TRC2PMBUSTool TaskSystem)
		
if(wxWidgets_FOUND)
message ("WXWIDGETS Found")
message ("WXWIDGETS Include DIR:" ${wxWidgets_INCLUDE_DIRS})
message ("WXWIDGETS Libraries:" ${wxWidgets_LIBRARIES})
message ("WXWIDGETS Libraries DIR:" ${wxWidgets_LIBRARIES_DIRS})

include_directories (${wxWidgets_INCLUDE_DIRS})
target_link_libraries(TRC2PMBUSTool ${wxWidgets_LIBRARIES})

if(WIN32)
#target_link_libraries(TRC2PMBUSTool "$ENV{WXWIDGETS_HOME}\\lib\\vc_lib\\wxmsw31ud_adv.lib")
target_link_libraries(TRC2PMBUSTool debug "$ENV{WXWIDGETS_HOME}/lib/vc_lib/wxmsw31ud_adv.lib"
                                    optimized "$ENV{WXWIDGETS_HOME}/lib/vc_lib/wxmsw31u_adv.lib")
									
target_link_libraries(TRC2PMBUSTool debug "$ENV{WXWIDGETS_HOME}/lib/vc_lib/wxpngd.lib"
				    optimized "$ENV{WXWIDGETS_HOME}/lib/vc_lib/wxpng.lib")
elseif(UNIX)
target_link_libraries(TRC2PMBUSTool "-lwx_gtk2u_adv-3.0")
target_link_libraries(TRC2PMBUSTool "-ldl -lusb-1.0 -fPIC")
endif()
									

#link_directories("$ENV{WXWIDGETS_HOME}\\lib\\vc_lib")
else()
message ("WXWIDGETS Not Found")
endif()

#message("$<CONFIG:Debug>:" $<CONFIG:Debug>)
#if($<$<CONFIG:Debug:1>>)
if(MSVC)

add_custom_command(
        TARGET TRC2PMBUSTool POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/Aardvark/aardvark.dll
                ${PROJECT_BINARY_DIR}/$<$<CONFIG:Debug>:Debug>/aardvark.dll)
				
add_custom_command(
        TARGET TRC2PMBUSTool POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/Aardvark/aardvark.dll
                ${PROJECT_BINARY_DIR}/$<$<CONFIG:Release>:Release>/aardvark.dll)

#set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
foreach(CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
	#set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CONFIGURATION_TYPE} )
	#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Aardvark/aardvark.dll DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE}})
	
					
#add_custom_command(
#		TARGET TRC2PMBUSTool POST_BUILD
#		COMMAND ${CMAKE_COMMAND} -E copy
#				${CMAKE_CURRENT_SOURCE_DIR}/Aardvark/aardvark.dll
#				${PROJECT_BINARY_DIR}/${CONFIGURATION_TYPE}/aardvark.dll)
						
endforeach(CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
endif()
