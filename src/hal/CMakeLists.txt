FIND_PACKAGE(Qt4 REQUIRED)

include(${QT_USE_FILE})


#宏定义
add_definitions(-DHAL_LIB)


#头文件路径
include_directories(
    .
    ${SRC_DIR}/common
    ${SRC_DIR}/qextserialport
)


#创建一系列的变量
set(moc_files 
    liscomm.h
    mcucomm.h
)

set(source_files 
    haldma.cpp
    halfpga.cpp
    liscomm.cpp
    mcucomm.cpp
    halsigno.cpp
    halkernel.cpp
    halnetlink.cpp
    halreagent.cpp
)


#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${MOC_OUTPUTS})


#最终目标文件
link_directories(${3RDPARTY_LIB_DIR})

add_library(hal SHARED ${moc_files} ${source_files} ${MOC_OUTPUTS})
if(WIN32)
    target_link_libraries(hal common qextserialport ${QT_LIBRARIES})
else(WIN32)
    target_link_libraries(hal inter common qextserialport ${QT_LIBRARIES})
endif(WIN32)