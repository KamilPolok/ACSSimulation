# ----------------------------------------DEFINING INSTALLATION BEHAVIOR----------------------------------------

include(GNUInstallDirs) # Holds needed definitions of CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_INCLUDEDIR and others

# Check if instalation path was defined. If not (if it is default), overwrite the default one (to system libraries) to install folder in the source tree
if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS
        "CMAKE_INSTALL_PREFIX is not set. Default value: ${CMAKE_INSTALL_PREFIX}\n"
        "Will set to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX
        "${CMAKE_SOURCE_DIR}/install"
        CACHE PATH "Where the library will be installed to" FORCE
    )
else()
    message(STATUS
        "CMAKE_INSTALL_PREFIX was already set. Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

# Install public headers:

# The variant with PUBLIC_HEADER property unfortunately does not preserve the folder structure:
#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")
# So instead iterate through public headers and install them "manually":

foreach(header ${public_headers})
    get_filename_component(header_absolute "${header}" ABSOLUTE) # Get absolute path to the header
    file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}" "${header_absolute}") # Get relative path of each header file with respect to the source directory and project name.
    get_filename_component(header_directory_path "${header_file_path}" DIRECTORY) # Extract the directory path from header_file_path, omitting the filename.
    install(
        FILES ${header}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}"
    )
endforeach()

# Install the target and create export-set:
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    # These get default values from GNUInstallDirs, no need to set them
    #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    # except for public headers, as we want them to be inside a library folder
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} # include/SomeLibrary
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
)

# ---------------------------------MAKING THE LIBRARY USABLE WITH find_package()---------------------------------

include(CMakePackageConfigHelpers)

# Create the version information file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Generate the package config file from a template
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake
)

# Install CMake targets
install(EXPORT ${PROJECT_NAME}Targets
    FILE "${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${namespace}::
    DESTINATION cmake
)

# Install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION cmake
)
