FIND_PACKAGE(Qt4 REQUIRED)

set(QT_USE_QTDESIGNER TRUE)

include(${QT_USE_FILE})


#宏定义
add_definitions(-DWIDGET_LIB)


#头文件路径
include_directories(
    .
    ./graph
    ./lineedit    
    ${SRC_DIR}/common
)


#通过include导入子文件
include("${CMAKE_CURRENT_SOURCE_DIR}/graph/CMakeLists.rules")
include("${CMAKE_CURRENT_SOURCE_DIR}/lineedit/CMakeLists.rules")
if(WIN32)
  include("${CMAKE_CURRENT_SOURCE_DIR}/interface/CMakeLists.rules")
endif(WIN32)


#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${MOC_OUTPUTS})


#最终目标文件
add_library(widget SHARED ${moc_files} ${source_files} ${MOC_OUTPUTS})
target_link_libraries(widget common ${QT_LIBRARIES})