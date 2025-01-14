cmake_minimum_required(VERSION 3.5)

project(CppDesignPatterns)

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR})


foreach(_dir IN ITEMS ${SUBDIRS})
    file(GLOB _files "${_dir}/*.cpp")
    foreach(_file IN ITEMS ${_files})

        get_filename_component(_file_name_with_extension
                ${_file} NAME
        )

        get_filename_component(_file_name
                ${_file} NAME_WLE
        )

        set(_project_name "${_file_name}")

        add_executable(${_project_name} "${_dir}/${_file_name_with_extension}")
    endforeach()

endforeach()