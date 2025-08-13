INCLUDE(CMakePackageConfigHelpers)

SET(name "charwidth")
SET(target "${name}")
SET(src_dir "${work_dir}/src")

PROJECT("${name}" VERSION "${version}" LANGUAGES C CXX)

################################################################

SET(versions
	"7.0.0" "8.0.0" "9.0.0" "10.0.0"
	"11.0.0" "12.0.0" "13.0.0" "14.0.0"
	"15.0.0" "15.1.0" "16.0.0" "17.0.0")

SET(headers)
FOREACH(version IN LISTS versions)
	LIST(APPEND headers
		"${version}/c90.h"
		"${version}/c99.h"
		"${version}/cpp98.h"
		"${version}/cpp11.h"
		"${version}/cpp17.h")
ENDFOREACH()

LIST(APPEND headers
	"def.h"
	"type_c90.h"
	"type_c99.h"
	"charwidth_c90.h"
	"charwidth_c99.h"
	"charwidth_cpp98.h"
	"charwidth_cpp11.h"
	"charwidth_cpp17.h")

DP_Message(INFO "headers:")
FOREACH(header ${headers})
	DP_Message(INFO "    ${header}")
ENDFOREACH()

########

ADD_LIBRARY("${target}" INTERFACE)

########

INSTALL(TARGETS "${target}"
	EXPORT "${name}-targets"
	INCLUDES DESTINATION "include")

DP_InstallFiles("${src_dir}" "include/${name}" "${headers}")

INSTALL(EXPORT "${name}-targets"
	FILE "${name}-targets.cmake"
	NAMESPACE "${name}::"
	DESTINATION "lib/cmake/${name}")

WRITE_BASIC_PACKAGE_VERSION_FILE("${name}-config-version.cmake" COMPATIBILITY AnyNewerVersion)

INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/${name}-config-version.cmake" DESTINATION "lib/cmake/${name}")
INSTALL(FILES "${work_dir}/cmake/lib/${name}-config.cmake" DESTINATION "lib/cmake/${name}")
