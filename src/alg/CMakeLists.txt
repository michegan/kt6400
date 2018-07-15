FIND_PACKAGE(Qt4 REQUIRED)

include(${QT_USE_FILE})


#宏定义
add_definitions(-DALG_LIB)


#头文件路径
include_directories(
    .
    ${SRC_DIR}/common
)


#创建一系列的变量
set(moc_files 

)

set(source_files 
    #alg.cpp
    newalg.cpp
    algthread.cpp
)


#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${MOC_OUTPUTS})


#最终目标文件
add_library(alg SHARED ${moc_files} ${source_files} ${MOC_OUTPUTS})
target_link_libraries(alg common ${QT_LIBRARIES})