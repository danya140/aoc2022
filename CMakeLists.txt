cmake_minimum_required(VERSION 3.23)
project(aoc2022)

set(CMAKE_CXX_STANDARD 14)

MACRO(DIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/day_*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

DIRLIST(DIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(subdir ${DIRS})
    add_subdirectory(${subdir})
endforeach()
