FIND_PACKAGE(Qt4 REQUIRED)

include(${QT_USE_FILE})


#宏定义
add_definitions(-DTIMESEQ_LIB)


#头文件路径
include_directories(
    .
    ${SRC_DIR}/hal
    ${SRC_DIR}/common
)


#创建一系列的变量
set(moc_files 
    timeseq.h
    asynctimeseq.h
)

set(source_files 
    timeseq.cpp
    asynctimeseq.cpp
)


#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${MOC_OUTPUTS})


#最终目标文件
link_directories(${3RDPARTY_LIB_DIR})

add_library(timeseq SHARED ${moc_files} ${source_files} ${MOC_OUTPUTS})
target_link_libraries(timeseq ${QT_LIBRARIES} hal common)