SET(target "test_c90")
SET(test_dir "${work_dir}/test")

PROJECT("test" VERSION "${version}" LANGUAGES C)

################################################################

DP_TryUseCcache()
DP_TrySetCStandard(90)
SET(CMAKE_C_EXTENSIONS OFF)

################################################################

SET(files "${test_dir}/test_c90.c")
DP_Message(INFO "files:")
FOREACH(file ${files})
	DP_Message(INFO "    ${file}")
ENDFOREACH()

########

ADD_EXECUTABLE("${target}" "${files}")

SET(precompile_headers)
SET(compile_opts)
SET(defs)
SET(include_dirs)
SET(link_opts)
SET(link_dirs)
SET(link_libs)

IF(MSVC)
	LIST(APPEND compile_opts "/W4")
ELSE()
	LIST(APPEND compile_opts "-Wall")
ENDIF()

TARGET_PRECOMPILE_HEADERS("${target}" PRIVATE ${precompile_headers})
TARGET_COMPILE_OPTIONS("${target}" PRIVATE ${compile_opts})
TARGET_COMPILE_DEFINITIONS("${target}" PRIVATE ${defs})
TARGET_INCLUDE_DIRECTORIES("${target}" PRIVATE ${include_dirs})
TARGET_LINK_OPTIONS("${target}" PRIVATE ${link_opts})
TARGET_LINK_DIRECTORIES("${target}" PRIVATE ${link_dirs})
TARGET_LINK_LIBRARIES("${target}" PRIVATE ${link_libs})

SET_TARGET_PROPERTIES("${target}" PROPERTIES OUTPUT_NAME "test_c90")

########

INSTALL(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/test_c90" DESTINATION ".")

########

ADD_TEST(NAME test_c90 COMMAND $<TARGET_FILE:${target}> "${test_dir}/data")
