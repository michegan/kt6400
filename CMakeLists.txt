#工程名
PROJECT(6400)


#CMake版本
cmake_minimum_required(VERSION 2.8)


#平台相关（宏定义）
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif(WIN32)


#定义一些变量
SET(CMAKE_BUILD_TYPE          "Debug")

if(WIN32)
    set(PLATFORM              win32)
else(WIN32)
    set(PLATFORM              arm)

    SET(CMAKE_C_COMPILER    arm-linux-gcc)
    SET(CMAKE_CXX_COMPILER    arm-linux-g++)
    SET(CMAKE_CXX_FLAGS       "-O2 -pipe -fPIC -Wall -fmessage-length=0")
endif(WIN32)


#各种目录变量
set(SRC_DIR                                 ${PROJECT_SOURCE_DIR}/src)
set(BUILD_DIR                               ${PROJECT_SOURCE_DIR}/build/src)
set(INSTALL_DIR                             ${PROJECT_SOURCE_DIR}/install)
set(RELEASE_DIR                             ${PROJECT_SOURCE_DIR}/release)
set(INSTALL_LIB_DIR                         ${INSTALL_DIR}/lib)

set(3RDPARTY_LIB_DIR                        ${PROJECT_SOURCE_DIR}/3rdparty/${PLATFORM})
set(3RDPARTY_INCLUDE_DIR                    ${PROJECT_SOURCE_DIR}/3rdparty/include)


#子目录
add_subdirectory(src)


#安装
install(FILES ${RELEASE_DIR}/run.sh                          DESTINATION ${INSTALL_DIR})
install(FILES ${RELEASE_DIR}/tscalibrate.sh                  DESTINATION ${INSTALL_DIR})

install(DIRECTORY ${RELEASE_DIR}/ko                          DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/sql                         DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/data                        DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/help                        DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/icon                        DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/image                       DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/config                      DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/machine                     DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/timeseq                     DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/language                    DESTINATION ${INSTALL_DIR})
install(DIRECTORY ${RELEASE_DIR}/template                    DESTINATION ${INSTALL_DIR})

if(WIN32)
    install(FILES ${BUILD_DIR}/ui/Debug/app.exe                        DESTINATION ${INSTALL_DIR})

    install(FILES ${BUILD_DIR}/alg/Debug/alg.dll                       DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/hal/Debug/hal.dll                       DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/log/Debug/log.dll                       DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/xml/Debug/xml.dll                       DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/count/Debug/count.dll                   DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/print/Debug/print.dll                   DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/common/Debug/common.dll                 DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/config/Debug/config.dll                 DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/widget/Debug/widget.dll                 DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/timeseq/Debug/timeseq.dll               DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/database/Debug/database.dll             DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/keyboard/Debug/keyboard.dll             DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/language/Debug/language.dll             DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/transmit/Debug/transmit.dll             DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/datatable/Debug/datatable.dll           DESTINATION ${INSTALL_DIR})
    install(FILES ${BUILD_DIR}/qextserialport/Debug/qextserialport.dll DESTINATION ${INSTALL_DIR})

else(WIN32)
    install(FILES ${BUILD_DIR}/ui/app                                  DESTINATION ${INSTALL_DIR})

    install(FILES ${BUILD_DIR}/alg/libalg.so                           DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/hal/libhal.so                           DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/log/liblog.so                           DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/xml/libxml.so                           DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/count/libcount.so                       DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/print/libprint.so                       DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/common/libcommon.so                     DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/config/libconfig.so                     DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/widget/libwidget.so                     DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/timeseq/libtimeseq.so                   DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/database/libdatabase.so                 DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/keyboard/libkeyboard.so                 DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/language/liblanguage.so                 DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/transmit/libtransmit.so                 DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/datatable/libdatatable.so               DESTINATION ${INSTALL_LIB_DIR})
    install(FILES ${BUILD_DIR}/qextserialport/libqextserialport.so     DESTINATION ${INSTALL_LIB_DIR})

    install(FILES ${3RDPARTY_LIB_DIR}/libinter.so                      DESTINATION ${INSTALL_LIB_DIR})

endif(WIN32)