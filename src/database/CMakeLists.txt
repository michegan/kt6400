FIND_PACKAGE(Qt4 REQUIRED)

set(QT_USE_QTSQL TRUE)

include(${QT_USE_FILE})


#宏定义
add_definitions(-DDATABASE_LIB)


#头文件路径
include_directories(
    .

)


#创建一系列的变量
set(moc_files 
    datatable.h
)

set(source_files 
    database.cpp
    datatable.cpp
)


#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${MOC_OUTPUTS})


#最终目标文件
add_library(database SHARED ${moc_files} ${source_files} ${MOC_OUTPUTS})
target_link_libraries(database ${QT_LIBRARIES})