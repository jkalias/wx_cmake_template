find_package(matplot++ CONFIG QUIET)

if(matplot++_FOUND)
    message(STATUS "Found preinstalled matplot++ libraries at ${Matplot++_LIBRARIES}")
    add_library(matplotplusplus_external INTERFACE)
else()
    message(STATUS "Preinstalled matplot++ not found.")
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

    set(matplotplusplus_ROOT_DIR ${STAGED_INSTALL_PREFIX})
    file(TO_NATIVE_PATH "${matplotplusplus_ROOT_DIR}" matplotplusplus_ROOT_DIR)
    set(matplotplusplus_ROOT_DIR ${matplotplusplus_ROOT_DIR} CACHE INTERNAL "Matplot++ installation dir")

    #set(ENV_WX_CONFIG ${STAGED_INSTALL_PREFIX}/bin/wx-config)
    #file(TO_NATIVE_PATH "${ENV_WX_CONFIG}" ENV_WX_CONFIG)
    #set(ENV_WX_CONFIG ${ENV_WX_CONFIG} CACHE INTERNAL "wx-config dir")
endif()


# # # check if matplotplusplus is already installed in the system
# FetchContent_Declare(matplotplusplus
        # GIT_REPOSITORY
		# https://github.com/jkalias/matplotplusplus
		# GIT_TAG
		# origin/master)

# FetchContent_GetProperties(matplotplusplus)
# if(NOT matplotplusplus_POPULATED)
	# message(STATUS "Matplot++ NOT populated")	
	
    # # FetchContent_Populate(matplotplusplus)
	# # message("matplotplusplus_SOURCE_DIR: ${matplotplusplus_SOURCE_DIR}")
	# # message("matplotplusplus_BINARY_DIR: ${matplotplusplus_BINARY_DIR}")
    # # add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
	
	# message(STATUS "Preinstalled matplotplusplus not found.")
    # message(STATUS "Will download and install matplotplusplus in ${STAGED_INSTALL_PREFIX}")
	
    # include(ExternalProject)
    # ExternalProject_Add(matplotplusplus_external
      # GIT_REPOSITORY
	  # https://github.com/jkalias/matplotplusplus
      # GIT_TAG
	  # origin/master
      # UPDATE_COMMAND
      # ""
      # CMAKE_ARGS
      # -DCMAKE_INSTALL_PREFIX=${STAGED_INSTALL_PREFIX}
      # -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}	
      # -DMATPLOTPP_BUILD_EXAMPLES=OFF
	  # -DMATPLOTPP_BUILD_SHARED_LIBS=OFF
	  # -DMATPLOTPP_BUILD_TESTS=OFF
	  # -DCMAKE_BUILD_TYPE=Release
	  # TEST_AFTER_INSTALL
        # 0
        # DOWNLOAD_NO_PROGRESS
        # 1
        # LOG_CONFIGURE
        # 1
        # LOG_BUILD
        # 1
        # LOG_INSTALL
        # 1
    # )
	
    # set(matplotplusplus_ROOT_DIR ${STAGED_INSTALL_PREFIX})
    # file(TO_NATIVE_PATH "${matplotplusplus_ROOT_DIR}" matplotplusplus_ROOT_DIR)
    # set(matplotplusplus_ROOT_DIR ${matplotplusplus_ROOT_DIR} CACHE INTERNAL "matplotplusplus installation dir")
		
# else()
	# message(STATUS "Matplot++ populated")
	# add_library(matplotplusplus_external INTERFACE)
# endif()

# # if(matplotplusplus_FOUND)
    # # message(STATUS "Found preinstalled matplotplusplus libraries at ${matplotplusplus_LIBRARIES}")
    # # add_library(matplotplusplus_external INTERFACE)
# # else()
    
# # endif()