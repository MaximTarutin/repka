QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

win32:RC_ICONS += repa.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    global.cpp \
    lev_2_window.cpp \
    lev_3_window.cpp \
    lev_4_window.cpp \
    lev_5_window.cpp \
    lev_6_window.cpp \
    lev_7_window.cpp \
    main.cpp \
    mainwindow.cpp \
    mapwindow.cpp \
    static_object.cpp

HEADERS += \
    global.h \
    lev_2_window.h \
    lev_3_window.h \
    lev_4_window.h \
    lev_5_window.h \
    lev_6_window.h \
    lev_7_window.h \
    mainwindow.h \
    mapwindow.h \
    static_object.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res1.qrc \
    res2.qrc \
    res3.qrc \
    res4.qrc \
    res5.qrc \
    res6.qrc \
    res7.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
