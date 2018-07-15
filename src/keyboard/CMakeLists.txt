FIND_PACKAGE(Qt4 REQUIRED)

include(${QT_USE_FILE})


#宏定义
add_definitions(-DKEYBOARD_LIB)


#头文件路径
include_directories(
    .
    ${SRC_DIR}/common
)


#创建一系列的变量
set(moc_files 
    imebar.h
    pinyin.h
    keyboard.h
    keybutton.h
    inputcontext.h
    digitkeyboard.h
    frenchkeyboard.h
    russiakeyboard.h
    chinesekeyboard.h
    englishkeyboard.h
    spanishkeyboard.h
)

set(source_files 
    imebar.cpp
    pinyin.cpp
    keyboard.cpp
    keybutton.cpp
    proxystyle.cpp
    inputcontext.cpp
    digitkeyboard.cpp
    frenchkeyboard.cpp
    russiakeyboard.cpp
    chinesekeyboard.cpp
    englishkeyboard.cpp
    spanishkeyboard.cpp
    punctionconvert.cpp
)


#moc
QT4_WRAP_CPP(MOC_OUTPUTS ${moc_files})
SOURCE_GROUP("moc_cxx" FILES ${MOC_OUTPUTS})


#最终目标文件
add_library(keyboard SHARED ${moc_files} ${source_files} ${MOC_OUTPUTS})
target_link_libraries(keyboard common ${QT_LIBRARIES})
