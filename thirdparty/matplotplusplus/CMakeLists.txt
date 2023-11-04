find_package(Matplot++ CONFIG QUIET)

if(Matplot++_FOUND)
    message(STATUS "Found preinstalled Matplot++ libraries at ${Matplot++_LIBRARIES}")
    add_library(matplotplusplus_external INTERFACE)
else()
    message(STATUS "Preinstalled Matplot++ not found.")
    message(STATUS "Will download and install Matplot++ in ${STAGED_INSTALL_PREFIX}")

    include(ExternalProject)
    ExternalProject_Add(matplotplusplus_external
        GIT_REPOSITORY
        https://github.com/jkalias/matplotplusplus
        GIT_TAG
        origin/master
        UPDATE_COMMAND
        ""
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${STAGED_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}	
        -DMATPLOTPP_BUILD_EXAMPLES=OFF
	    -DMATPLOTPP_BUILD_SHARED_LIBS=OFF
	    -DMATPLOTPP_BUILD_TESTS=OFF
	    -DCMAKE_BUILD_TYPE=Release
		-DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON
        TEST_AFTER_INSTALL
        0
        DOWNLOAD_NO_PROGRESS
        1
        LOG_CONFIGURE
        1
        LOG_BUILD
        1
        LOG_INSTALL
        1
    )
endif()