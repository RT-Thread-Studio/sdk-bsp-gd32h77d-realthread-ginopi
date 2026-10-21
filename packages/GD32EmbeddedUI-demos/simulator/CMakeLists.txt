cmake_minimum_required(VERSION 3.10)
project(GD32Embeddedui_simulator)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LV_USE_FREETYPE "Use freetype lib" OFF)
option(LV_USE_FFMPEG   "Use ffmpeg lib"   ON)

# ── 路径配置 ────────────────────────────────────────────────────────────────
set(UI_PATH generated)
set(SIMULATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_ROOT  ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories(${PROJECT_ROOT})
include_directories(${PROJECT_ROOT}/${UI_PATH})
include_directories(${PROJECT_ROOT}/custom)
include_directories(${PROJECT_ROOT}/${UI_PATH}/lang)
include_directories(${PROJECT_ROOT}/${UI_PATH}/screens)
include_directories(${PROJECT_ROOT}/${UI_PATH}/theme)
include_directories(${PROJECT_ROOT}/${UI_PATH}/config)
include_directories(${SIMULATOR_DIR})

# ── 第三方库路径（从 simulator/third_party/ 或全局缓存引用）─────────────────
# 优先使用工程内 simulator/third_party/lvgl，缺失时回退到 GD32EmbeddedUI 内置 LVGL 源码
set(GD32EMBEDDEDUI_LVGL_DIR "" CACHE PATH "GD32EmbeddedUI bundled LVGL source path")
if(EXISTS "${SIMULATOR_DIR}/third_party/lvgl/lvgl.h")
  set(LVGL_DIR "${SIMULATOR_DIR}/third_party/lvgl")
elseif(GD32EMBEDDEDUI_LVGL_DIR AND EXISTS "${GD32EMBEDDEDUI_LVGL_DIR}/lvgl.h")
  set(LVGL_DIR "${GD32EMBEDDEDUI_LVGL_DIR}")
else()
  message(FATAL_ERROR "LVGL source not found. Add LVGL to simulator/third_party/lvgl or set GD32EMBEDDEDUI_LVGL_DIR.")
endif()

include_directories(${LVGL_DIR})
include_directories(${LVGL_DIR}/src)

if(LV_USE_FREETYPE)
    add_definitions(-DFT2_BUILD_LIBRARY -DHAVE_UNISTD_H -DHAVE_FCNTL_H)
    if(EXISTS ${SIMULATOR_DIR}/third_party/freetype)
        set(FREETYPE_DIR ${SIMULATOR_DIR}/third_party/freetype)
        include_directories(${FREETYPE_DIR}/include)
    endif()
endif()

# ── 源文件收集 ────────────────────────────────────────────────────────────
file(GLOB_RECURSE UI_SOURCES
    "${PROJECT_ROOT}/${UI_PATH}/*.c"
    "${PROJECT_ROOT}/custom/*.c"
)

# ── 可执行目标（优先链接预编 LVGL 静态库，缺失时回退源码编译）───────────────
set(GD32EMBEDDEDUI_LVGL_LIB "" CACHE FILEPATH "Prebuilt LVGL static library")
if(GD32EMBEDDEDUI_LVGL_LIB AND EXISTS "${GD32EMBEDDEDUI_LVGL_LIB}")
    add_library(lvgl STATIC IMPORTED)
    set_target_properties(lvgl PROPERTIES IMPORTED_LOCATION "${GD32EMBEDDEDUI_LVGL_LIB}")
    add_executable(simulator
        ${UI_SOURCES}
        main.c
    )
else()
    file(GLOB_RECURSE LVGL_SOURCES
        "${LVGL_DIR}/src/*.c"
    )
    add_library(lvgl STATIC ${LVGL_SOURCES})
    add_executable(simulator
        ${UI_SOURCES}
        main.c
    )
endif()

add_definitions(-DLV_CONF_PATH=lv_conf_custom.h -DLVGL_VERSION_MAJOR=8 -DLV_COLOR_DEPTH=16)
add_definitions(-DLVGL_DIR="${PROJECT_ROOT}/")

target_link_libraries(simulator PRIVATE lvgl user32 gdi32)

SET(EXECUTABLE_OUTPUT_PATH ${SIMULATOR_DIR}/build)
