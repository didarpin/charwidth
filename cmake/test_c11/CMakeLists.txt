SET(target "test_c11")
SET(test_dir "${work_dir}/test")

PROJECT("test" VERSION "${version}" LANGUAGES C)

################################################################

DP_TryUseCcache()
DP_TrySetCStandard(11)

################################################################

SET(files "${test_dir}/test_c11.c")
DP_Message(INFO "files:")
FOREACH(file ${files})
	DP_Message(INFO "    ${file}")
ENDFOREACH()

########

ADD_EXECUTABLE("${target}" "${files}")

SET(precompile_headers)
SET(compile_opts "-Wall")
SET(defs)
SET(include_dirs "${work_dir}")
SET(link_opts)
SET(link_dirs)
SET(link_libs)

TARGET_PRECOMPILE_HEADERS("${target}" PRIVATE ${precompile_headers})
TARGET_COMPILE_OPTIONS("${target}" PRIVATE ${compile_opts})
TARGET_COMPILE_DEFINITIONS("${target}" PRIVATE ${defs})
TARGET_INCLUDE_DIRECTORIES("${target}" PRIVATE ${include_dirs})
TARGET_LINK_OPTIONS("${target}" PRIVATE ${link_opts})
TARGET_LINK_DIRECTORIES("${target}" PRIVATE ${link_dirs})
TARGET_LINK_LIBRARIES("${target}" PRIVATE ${link_libs})

SET_TARGET_PROPERTIES("${target}" PROPERTIES OUTPUT_NAME "test_c11")

########

INSTALL(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/test_c11" DESTINATION ".")

########

ADD_TEST(NAME test_c11 COMMAND test_c11)
