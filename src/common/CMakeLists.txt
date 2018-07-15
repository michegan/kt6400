FIND_PACKAGE(Qt4 REQUIRED)

include(${QT_USE_FILE})


#宏定义
add_definitions(-DCOMMON_LIB)


#头文件路径
include_directories(
    .
)


#创建一系列的变量
set(moc_files 
    sysstate.h
)

set(source_files 
    age.cpp
    dma.cpp
    para.cpp
    path.cpp
    user.cpp
    cache.cpp
    modes.cpp
    paras.cpp
    udisk.cpp
    doctor.cpp
    project.cpp
    reagent.cpp
    seqfile.cpp
    utility.cpp
    version.cpp
    datetime.cpp
    diskinfo.cpp
    histinfo.cpp
    libinter.cpp
    ljqcinfo.cpp
    paraunit.cpp
    resource.cpp
    sampleid.cpp
    sysstate.cpp
    calfactor.cpp
    department.cpp
    sampleinfo.cpp
)


#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${MOC_OUTPUTS})


#最终目标文件
add_library(common SHARED ${moc_files} ${source_files} ${MOC_OUTPUTS})
target_link_libraries(common ${QT_LIBRARIES})