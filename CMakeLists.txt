cmake_minimum_required(VERSION 3.18)

project(ujer_eats)
set(MUZZLE_ROOT "../muzzle_legacy")
set(MUZZLE_LIB_FOLDER ${MUZZLE_ROOT}/../Muzzle/deps)

set(raudio_source_dir ./include/external/raudio/src)

INCLUDE_DIRECTORIES(${MUZZLE_ROOT}/include)
LINK_DIRECTORIES(${MUZZLE_LIB_FOLDER}/glfw/lib)
set(mz_source_dir ${MUZZLE_ROOT}/src)

#could use aux_source_directory() but its better to list each file to ensure new files are compiled
#https://stackoverflow.com/a/25077976/10415312

set(mz_source
        ${mz_source_dir}/Applet.c
        ${mz_source_dir}/callback.c
        ${mz_source_dir}/Drawing.c
        ${mz_source_dir}/Error.c
        ${mz_source_dir}/Loop.c
        ${mz_source_dir}/Muzzle.c
        ${mz_source_dir}/Rectangle.c
        ${mz_source_dir}/tint.c
        ${mz_source_dir}/Circle.c
        ${mz_source_dir}/Input.c
        ${mz_source_dir}/Sprite.c
        ${mz_source_dir}/Text.c
        ${mz_source_dir}/Time.c
        )

set(raudio_source
        ${raudio_source_dir}/raudio.c
        )

add_compile_definitions(RAUDIO_STANDALONE)
add_compile_definitions(SUPPORT_FILEFORMAT_MP3)

set(source main.c include/application.c include/application.h include/loop.c include/input.c include/input.h include/game_state.c include/game_state.h include/collision.h include/customers.c)

add_executable(main ${source} ${mz_source} ${raudio_source})

message(STATUS "Checking OS")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Checking OS - found (Darwin/MacOS)")
    message(FATAL_ERROR "Darwin/MacOS are not yet supported in this CMakeLists.txt, if you know how to compile this project with CMake on Darwin/MacOS. Submit a Github Issue")

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Checking OS - found (WIN32)")
    TARGET_LINK_LIBRARIES(main glfw3 opengl32 gdi32 dsound)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Checking OS - found (Linux)")
    TARGET_LINK_LIBRARIES(main glfw GL m)

else ()
    # Default to Unix
    message(STATUS "Checking OS - not found (Unix)")
    TARGET_LINK_LIBRARIES(main glfw GL m)
endif ()