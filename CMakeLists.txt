CMAKE_MINIMUM_REQUIRED(VERSION 3.26)
SET(work_dir ${CMAKE_SOURCE_DIR})
INCLUDE("${work_dir}/cmake/base/share.cmake")

DP_ReadString("${work_dir}/version" version)
PROJECT("charwidth" VERSION "${version}" LANGUAGES C CXX)

################################################################

OPTION(charwidth_project "ON: enable all project, OFF: disable all project" ON)
OPTION(charwidth_project_lib "Enable library project" "${charwidth_project}")
OPTION(charwidth_project_test_c90 "Enable test_c90 project" "${charwidth_project}")
OPTION(charwidth_project_test_c99 "Enable test_c99 project" "${charwidth_project}")
OPTION(charwidth_project_test_cpp11 "Enable test_cpp11 project" "${charwidth_project}")
OPTION(charwidth_project_test_cpp17 "Enable test_cpp17 project" "${charwidth_project}")

SET(test_options
	"charwidth_project_test_c90"
	"charwidth_project_test_c99"
	"charwidth_project_test_cpp11"
	"charwidth_project_test_cpp17")

FOREACH(opt IN LISTS test_options)
	IF(${opt})
		ENABLE_TESTING()
		BREAK()
	ENDIF()
ENDFOREACH()

DP_SetSourceCodeUtf8()

IF(charwidth_project_lib)
	ADD_SUBDIRECTORY("cmake/lib")
ENDIF()

IF(charwidth_project_test_c90)
	ADD_SUBDIRECTORY("cmake/test_c90")
ENDIF()

IF(charwidth_project_test_c99)
	ADD_SUBDIRECTORY("cmake/test_c99")
ENDIF()

IF(charwidth_project_test_cpp11)
	ADD_SUBDIRECTORY("cmake/test_cpp11")
ENDIF()

IF(charwidth_project_test_cpp17)
	ADD_SUBDIRECTORY("cmake/test_cpp17")
ENDIF()
