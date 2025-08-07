SET(target "test_cpp11")
SET(test_dir "${work_dir}/test")

PROJECT("test" VERSION "${version}" LANGUAGES CXX)

################################################################

DP_TryUseCcache()
DP_TrySetCxxStandard(11)

################################################################

SET(files "${test_dir}/test_cpp11.cpp")
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

SET_TARGET_PROPERTIES("${target}" PROPERTIES OUTPUT_NAME "test_cpp11")

########

INSTALL(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/test_cpp11" DESTINATION ".")

########

ADD_TEST(NAME test_cpp11 COMMAND $<TARGET_FILE:${target}>)
