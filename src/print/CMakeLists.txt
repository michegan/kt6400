FIND_PACKAGE(Qt4 REQUIRED)

include(${QT_USE_FILE})


#宏定义
add_definitions(-DPRINT_LIB)


#头文件路径
include_directories(
    .
    ${SRC_DIR}/xml
    ${SRC_DIR}/common
    ${SRC_DIR}/config
    ${SRC_DIR}/language
    ${SRC_DIR}/qextserialport
)


#创建一系列的变量
set(moc_files 
    print.h
    printer.h
    thermalprinter.h
    abstractprinter.h
)

set(source_files 
    print.cpp
    printer.cpp
    deskjetprinter.cpp
    thermalprinter.cpp
    abstractprinter.cpp
)


#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${HEADER_MOCS})


#最终目标文件
link_directories(${3RDPARTY_LIB_DIR})

set(LIBRARY_OUTPUT_PATH ${LIB_OUTPUT_DIR})

add_library(print SHARED ${moc_files} ${source_files} ${MOC_OUTPUTS})
target_link_libraries(print ${QT_LIBRARIES} xml common config language qextserialport)
