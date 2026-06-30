cmake_minimum_required(VERSION 3.15)
project(ChargingTerminal LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(BUILD_DIR ${CMAKE_BINARY_DIR}/build)
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMODBUS REQUIRED IMPORTED_TARGET libmodbus)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

set(LV_CONF_PATH ${CMAKE_SOURCE_DIR}/lv_conf.h CACHE STRING "LVGL configuration header" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/lvgl)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/lv_drivers)

target_include_directories(lvgl SYSTEM PUBLIC ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${SRC_DIR}/*.c")

add_executable(charging_terminal ${SOURCES})
target_include_directories(charging_terminal PRIVATE ${CMAKE_SOURCE_DIR} ${INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/lib/lvgl ${CMAKE_SOURCE_DIR}/lib/lv_drivers)
target_link_libraries(charging_terminal PRIVATE PkgConfig::LIBMODBUS PkgConfig::SDL2 lvgl::lvgl lvgl::drivers m)
set_target_properties(charging_terminal PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)

install(TARGETS charging_terminal
    RUNTIME DESTINATION bin
)

add_custom_target(distclean
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
    COMMENT "Remove all build files"
)
