FIND_PACKAGE(Qt4 REQUIRED)

set(QT_USE_QTSQL TRUE)

include(${QT_USE_FILE})


#宏定义
add_definitions(-DCOUNT_LIB)


#头文件路径
include_directories(
    .
    ${SRC_DIR}/alg
    ${SRC_DIR}/hal
    ${SRC_DIR}/log
    ${SRC_DIR}/xml
    ${SRC_DIR}/common
    ${SRC_DIR}/config
    ${SRC_DIR}/timeseq
    ${SRC_DIR}/database
    ${SRC_DIR}/datatable
    ${SRC_DIR}/qextserialport
)


#创建一系列的变量
set(moc_files 
    count.h
)

set(source_files 
    count.cpp
    refrange.cpp
)


#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${MOC_OUTPUTS})


#最终目标文件
link_directories(${3RDPARTY_LIB_DIR})

add_library(count SHARED ${moc_files} ${source_files} ${MOC_OUTPUTS})
target_link_libraries(count alg hal log xml common config timeseq database datatable qextserialport ${QT_LIBRARIES})