cmake_minimum_required(VERSION 2.8)

# Project name
project(ELM_Status_Widget C)

find_program(EOLIAN eolian_gen)
if (NOT EOLIAN)
	message(FATAL_ERROR "eolian_gen not found")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(ELEMENTARY REQUIRED elementary eet)
include_directories(${ELEMENTARY_INCLUDE_DIRS})

add_custom_command(OUTPUT eo_h
COMMAND eolian_gen -I /usr/share/eolian/include/eo-1 -I/usr/share/eolian/include/efl-1 -I/usr/share/eolian/include/evas-1 -I/usr/share/eolian/include/edje-1 -I/usr/share/eolian/include/ecore-1 -I/usr/local/share/eolian/include/elementary-1 -I /usr/share/eolian/include/evas-1 --gh -o "${PROJECT_SOURCE_DIR}/elm_status.eo.h" "${PROJECT_SOURCE_DIR}/elm_status.eo"
)

add_custom_command(OUTPUT eo_c
COMMAND eolian_gen -I /usr/share/eolian/include/eo-1 -I/usr/share/eolian/include/efl-1 -I/usr/share/eolian/include/evas-1 -I/usr/share/eolian/include/edje-1 -I/usr/share/eolian/include/ecore-1 -I/usr/local/share/eolian/include/elementary-1 -I /usr/share/eolian/include/evas-1 --gc -o "${PROJECT_SOURCE_DIR}/elm_status.eo.c" "${PROJECT_SOURCE_DIR}/elm_status.eo"
)

add_custom_command(OUTPUT eo_c_file
COMMAND eolian_gen -I /usr/share/eolian/include/eo-1 -I/usr/share/eolian/include/eo-1 -I/usr/share/eolian/include/efl-1 -I/usr/share/eolian/include/evas-1 -I/usr/share/eolian/include/edje-1 -I/usr/share/eolian/include/ecore-1 -I/usr/local/share/eolian/include/elementary-1 -I /usr/share/eolian/include/evas-1 --gi -o "${PROJECT_SOURCE_DIR}/elm_status.c" "${PROJECT_SOURCE_DIR}/elm_status.eo"
)

add_custom_command(OUTPUT edj_file
	COMMAND edje_cc -id "${PROJECT_SOURCE_DIR}/images" "${PROJECT_SOURCE_DIR}/status.edc" "status.edj"
)

add_custom_target(eo_file ALL
   DEPENDS eo_h eo_c eo_c_file edj_file)

add_executable(status
   elm_status.c
   main.c)
target_link_libraries(status ${ELEMENTARY_LIBRARIES})
