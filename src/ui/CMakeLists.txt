FIND_PACKAGE(Qt4 REQUIRED)

set(QT_USE_QTSQL TRUE)

include(${QT_USE_FILE})


#创建一系列的变量
set(moc_files 

)

set(uic_files 

)

set(source_files 
    main.cpp
)


#通过include导入子文件
include("${CMAKE_CURRENT_SOURCE_DIR}/qc/CMakeLists.rules")
include("${CMAKE_CURRENT_SOURCE_DIR}/count/CMakeLists.rules")
include("${CMAKE_CURRENT_SOURCE_DIR}/frame/CMakeLists.rules")
include("${CMAKE_CURRENT_SOURCE_DIR}/setup/CMakeLists.rules")
include("${CMAKE_CURRENT_SOURCE_DIR}/review/CMakeLists.rules")
include("${CMAKE_CURRENT_SOURCE_DIR}/maintain/CMakeLists.rules")
include("${CMAKE_CURRENT_SOURCE_DIR}/selftest/CMakeLists.rules")
include("${CMAKE_CURRENT_SOURCE_DIR}/calibrate/CMakeLists.rules")


#头文件路径
include_directories(
    .
    ${CMAKE_CURRENT_BINARY_DIR}
    ${SRC_DIR}/alg
    ${SRC_DIR}/hal
    ${SRC_DIR}/log
    ${SRC_DIR}/xml
    ${SRC_DIR}/count
    ${SRC_DIR}/print
    ${SRC_DIR}/widget
    ${SRC_DIR}/common
    ${SRC_DIR}/config
    ${SRC_DIR}/timeseq
    ${SRC_DIR}/database
    ${SRC_DIR}/keyboard
    ${SRC_DIR}/language
    ${SRC_DIR}/transmit
    ${SRC_DIR}/datatable
    ${SRC_DIR}/widget/graph
    ${SRC_DIR}/qextserialport
    ${SRC_DIR}/widget/lineedit
    ${SRC_DIR}/ui/qc
    ${SRC_DIR}/ui/count
    ${SRC_DIR}/ui/frame
    ${SRC_DIR}/ui/setup
    ${SRC_DIR}/ui/review
    ${SRC_DIR}/ui/maintain
    ${SRC_DIR}/ui/selftest
    ${SRC_DIR}/ui/calibrate
)

#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${MOC_OUTPUTS})

#uic
QT4_WRAP_UI(UIC_OUTPUTS ${uic_files})
SOURCE_GROUP("uic_cxx" FILES ${UIC_OUTPUTS})

#最终目标文件
set(APP_LIBRARIES alg hal log xml count print widget common config timeseq database keyboard language transmit datatable qextserialport)

link_directories(${3RDPARTY_LIB_DIR})

add_executable(app ${moc_files} ${source_files} ${MOC_OUTPUTS} ${UIC_OUTPUTS})
target_link_libraries(app ${QT_LIBRARIES} ${APP_LIBRARIES})