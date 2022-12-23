cmake_minimum_required(VERSION 3.19)
project(radar C)

set(CMAKE_C_STANDARD 23)
set(BINARY_NAME radar)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Maybe work on MacM1 only
    # TODO Intel Mac
    include_directories(${BINARY_NAME} /opt/homebrew/Cellar/csfml/2.5.1/include)
    link_directories(${BINARY_NAME} /opt/homebrew/Cellar/csfml/2.5.1/lib)
endif()

if (${WIN32})
    set(EXECUTABLE_TYPE WIN32)
endif()

add_executable(${BINARY_NAME} ${EXECUTABLE_TYPE}
    ${PROJECT_SOURCE_DIR}/src/main.c
    ${PROJECT_SOURCE_DIR}/src/radar/parser.c
    ${PROJECT_SOURCE_DIR}/src/engine/engine.c
    ${PROJECT_SOURCE_DIR}/src/engine/scene.c
    ${PROJECT_SOURCE_DIR}/src/engine/events/handler.c
    ${PROJECT_SOURCE_DIR}/src/engine/events/keys.c
    ${PROJECT_SOURCE_DIR}/src/engine/ui/element.c
    ${PROJECT_SOURCE_DIR}/src/engine/ui/events.c
    ${PROJECT_SOURCE_DIR}/src/engine/entity/entity.c
)

set_target_properties(${BINARY_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin
)

set(CSFML_MODULES
    graphics
    system
    window
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    message(STATUS "Build type not specified: defaulting to Debug.")
endif()

if (${WIN32})
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(LINK_EXTENSION "-d")
    endif()

    string(TOLOWER cmake-build-${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LOWER)

    # Build SFML and CSFML
    set(SFML_DIR ${PROJECT_SOURCE_DIR}/lib/sfml)
    set(CSFML_DIR ${PROJECT_SOURCE_DIR}/lib/csfml)

    set(SFML_BUILD_VARIABLES
        -DBUILD_SHARED_LIBS=1
    )

    set(CSFML_BUILD_VARIABLES
        -DSTATIC_STD_LIBS=1
        -DBUILD_SHARED_LIBS=1
        -DCSFML_LINK_SFML_STATICALLY=0
        -DSFML_DIR=${SFML_DIR}/${CMAKE_BUILD_TYPE_LOWER}
    )

    add_custom_command(TARGET ${BINARY_NAME} PRE_BUILD
        COMMAND
            git submodule update --init &&
            ${CMAKE_COMMAND} ${SFML_BUILD_VARIABLES} -B ${SFML_DIR}/${CMAKE_BUILD_TYPE_LOWER} -S ${SFML_DIR} &&
            ${CMAKE_COMMAND} --build ${SFML_DIR}/${CMAKE_BUILD_TYPE_LOWER} --config ${CMAKE_BUILD_TYPE} &&
            ${CMAKE_COMMAND} ${CSFML_BUILD_VARIABLES} -B ${CSFML_DIR}/${CMAKE_BUILD_TYPE_LOWER} -S ${CSFML_DIR} &&
            ${CMAKE_COMMAND} --build ${CSFML_DIR}/${CMAKE_BUILD_TYPE_LOWER} --config ${CMAKE_BUILD_TYPE}
    )

    target_include_directories(${BINARY_NAME} PRIVATE ${CSFML_DIR}/include)
    target_link_directories(
        ${BINARY_NAME}
        PRIVATE
        ${CSFML_DIR}/${CMAKE_BUILD_TYPE_LOWER}/lib/${CMAKE_BUILD_TYPE}
    )
    target_link_libraries(${BINARY_NAME}
        csfml-main${LINK_EXTENSION}
    )

    # Copy needed dll files
    set(CSFML_SHARED_LIBS_DIR ${CSFML_DIR}/${CMAKE_BUILD_TYPE_LOWER}/lib/${CMAKE_BUILD_TYPE})
    foreach(MODULE ${CSFML_MODULES})
        add_custom_command(
            TARGET ${BINARY_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${CSFML_SHARED_LIBS_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}csfml-${MODULE}${LINK_EXTENSION}-2${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_BINARY_DIR}/bin
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
