cmake_minimum_required(VERSION 3.24)
project(radar C)

set(CMAKE_C_STANDARD 23)

set(VCPKG_DIR C:/vcpkg)

set(BINARY_NAME radar)

add_executable(${BINARY_NAME}
    ${PROJECT_SOURCE_DIR}/src/main.c
)

set_target_properties(${BINARY_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set(CSFML_MODULES
    graphics
    system
    window
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(LINK_EXTENSION "-d")
    endif()

    string(TOLOWER cmake-build-${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LOWER)

    # Build SFML and CSFML
    set(SFML_DIR ${PROJECT_SOURCE_DIR}/lib/sfml)
    set(CSFML_DIR ${PROJECT_SOURCE_DIR}/lib/csfml)
    add_custom_command(TARGET ${BINARY_NAME} PRE_LINK
        COMMAND
            ${CMAKE_COMMAND} -B ${SFML_DIR}/${CMAKE_BUILD_TYPE_LOWER} -S ${SFML_DIR} -DSFML_USE_SYSTEM_DEPS=1 -DBUILD_SHARED_LIBS=0 -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake &&
            ${CMAKE_COMMAND} --build ${SFML_DIR}/${CMAKE_BUILD_TYPE_LOWER} --config ${CMAKE_BUILD_TYPE} &&
            ${CMAKE_COMMAND} -DSFML_DIR=${SFML_DIR}/${CMAKE_BUILD_TYPE_LOWER} -B ${CSFML_DIR}/${CMAKE_BUILD_TYPE_LOWER} -S ${CSFML_DIR} -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake &&
            ${CMAKE_COMMAND} --build ${CSFML_DIR}/${CMAKE_BUILD_TYPE_LOWER} --config ${CMAKE_BUILD_TYPE}
    )

    target_include_directories(${BINARY_NAME} PRIVATE ${CSFML_DIR}/include)
    target_link_directories(
        ${BINARY_NAME}
        PRIVATE
        ${CSFML_DIR}/${CMAKE_BUILD_TYPE_LOWER}/lib/${CMAKE_BUILD_TYPE}
    )

    # Copy needed dll files
    set(CSFML_SHARED_LIBS_DIR ${CSFML_DIR}/${CMAKE_BUILD_TYPE_LOWER}/lib/${CMAKE_BUILD_TYPE})
    foreach(MODULE ${CSFML_MODULES})
        add_custom_command(
            TARGET ${BINARY_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${CSFML_SHARED_LIBS_DIR}/csfml-${MODULE}${LINK_EXTENSION}-2.dll ${CMAKE_BINARY_DIR}/bin
        )
    endforeach(MODULE)
endif()

target_include_directories(${BINARY_NAME} PRIVATE include)

# Link modules to the target
foreach(MODULE ${CSFML_MODULES})
    target_link_libraries(${BINARY_NAME}
        csfml-${MODULE}${LINK_EXTENSION}
    )
endforeach(MODULE)
