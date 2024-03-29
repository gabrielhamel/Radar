cmake_minimum_required(VERSION 3.19)
project(radar C)

set(CMAKE_C_STANDARD 23)
set(BINARY_NAME radar)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Maybe work on MacM1 only

    execute_process (
        COMMAND bash -c "brew info --json csfml | grep '\"version\": ' | head -n 1 | cut -f4 -d '\"' | tr -d '\n'"
        OUTPUT_VARIABLE CSFML_BREW_VERSION
    )

	message(oui${CSFML_BREW_VERSION}non)

    include_directories(${BINARY_NAME} /opt/homebrew/Cellar/csfml/${CSFML_BREW_VERSION}/include)
    link_directories(${BINARY_NAME} /opt/homebrew/Cellar/csfml/${CSFML_BREW_VERSION}/lib)
endif()

if (${WIN32})
    set(EXECUTABLE_TYPE WIN32)
endif()

add_executable(${BINARY_NAME} ${EXECUTABLE_TYPE}
    ${PROJECT_SOURCE_DIR}/src/main.c
    ${PROJECT_SOURCE_DIR}/src/radar/parser.c
    ${PROJECT_SOURCE_DIR}/src/radar/simulation.c
    ${PROJECT_SOURCE_DIR}/src/radar/events/simulation.c
    ${PROJECT_SOURCE_DIR}/src/radar/entities/aircraft.c
    ${PROJECT_SOURCE_DIR}/src/radar/entities/tower.c
    ${PROJECT_SOURCE_DIR}/src/radar/entities/storm.c
    ${PROJECT_SOURCE_DIR}/src/radar/entities/hitbox.c
    ${PROJECT_SOURCE_DIR}/src/radar/entities/timer.c
    ${PROJECT_SOURCE_DIR}/src/radar/components/ui_link.c
    ${PROJECT_SOURCE_DIR}/src/radar/components/hitbox.c
    ${PROJECT_SOURCE_DIR}/src/radar/components/ttl.c
    ${PROJECT_SOURCE_DIR}/src/radar/components/music.c
    ${PROJECT_SOURCE_DIR}/src/radar/systems/simulation.c
    ${PROJECT_SOURCE_DIR}/src/radar/systems/timer.c
    ${PROJECT_SOURCE_DIR}/src/radar/systems/hitbox/hitbox.c
    ${PROJECT_SOURCE_DIR}/src/radar/systems/hitbox/rect.c
    ${PROJECT_SOURCE_DIR}/src/radar/systems/hitbox/circle.c
    ${PROJECT_SOURCE_DIR}/src/radar/systems/hitbox/custom.c
    ${PROJECT_SOURCE_DIR}/src/radar/musics/ambiance.c
    ${PROJECT_SOURCE_DIR}/src/radar/tools/sprite.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/engine.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/scene.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/render/component.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/render/destroy.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/render/system.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/physics/component.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/physics/system.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/events/handler.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/events/keys.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/events/mouse.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/events/window.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/ui/element.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/ui/events.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/text/unicode.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/ecs/entity.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/ecs/component.c
    ${PROJECT_SOURCE_DIR}/lib/engine/src/ecs/system.c
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
    audio
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
target_include_directories(${BINARY_NAME} PRIVATE lib/engine/include)

# Link modules to the target
foreach(MODULE ${CSFML_MODULES})
    target_link_libraries(${BINARY_NAME}
        csfml-${MODULE}${LINK_EXTENSION}
    )
endforeach(MODULE)

if (${UNIX})
    target_link_libraries(${BINARY_NAME} m)
endif()
