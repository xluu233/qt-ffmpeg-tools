cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME "appqt-ffmpeg-tools")

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# check arch
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BUILD_CPU_ARCH x64)
else()
    set(BUILD_CPU_ARCH x86)
endif()
message(STATUS "[${PROJECT_NAME}] BUILD_CPU_ARCH:${BUILD_CPU_ARCH}")


find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(${PROJECT_NAME}
    main.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI qt-ffmpeg-tools
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


#
# plantform deps
#

# windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # ffmpeg
    # include
    set(FFMPEG_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/ffmpeg-6.1-msvc-build-share/${BUILD_CPU_ARCH}/include")
    target_include_directories(${PROJECT_NAME} PRIVATE ${FFMPEG_INCLUDE_PATH})

    # link
    set(FFMPEG_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/ffmpeg-6.1-msvc-build-share/${BUILD_CPU_ARCH}/bin")
    target_link_directories(${PROJECT_NAME} PUBLIC ${FFMPEG_LIB_PATH})

    message("ffmpeg path: " ${FFMPEG_LIB_PATH})

    target_link_libraries(${PROJECT_NAME} PRIVATE
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
    )

    # copy
#    set(THIRD_PARTY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party")
#    set(FFMPEG_BIN_PATH "${THIRD_PARTY_PATH}/ffmpeg-6.1-msvc-build-share/${BUILD_CPU_ARCH}/bin")
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FFMPEG_BIN_PATH}/avcodec-60.dll" "${QSC_DEPLOY_PATH}"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FFMPEG_BIN_PATH}/avdevice-60.dll" "${QSC_DEPLOY_PATH}"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FFMPEG_BIN_PATH}/avfilter-9.dll" "${QSC_DEPLOY_PATH}"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FFMPEG_BIN_PATH}/avformat-60.dll" "${QSC_DEPLOY_PATH}"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FFMPEG_BIN_PATH}/avutil-58.dll" "${QSC_DEPLOY_PATH}"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FFMPEG_BIN_PATH}/postproc-57.dll" "${QSC_DEPLOY_PATH}"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FFMPEG_BIN_PATH}/swresample-4.dll" "${QSC_DEPLOY_PATH}"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${FFMPEG_BIN_PATH}/swscale-7.dll" "${QSC_DEPLOY_PATH}"

#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${THIRD_PARTY_PATH}/adb/win/adb.exe" "${QSC_DEPLOY_PATH}"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${THIRD_PARTY_PATH}/adb/win/AdbWinApi.dll" "${QSC_DEPLOY_PATH}"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${THIRD_PARTY_PATH}/adb/win/AdbWinUsbApi.dll" "${QSC_DEPLOY_PATH}"

#        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${THIRD_PARTY_PATH}/scrcpy-server" "${QSC_DEPLOY_PATH}"
#    )
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Quick)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
