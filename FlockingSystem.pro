QT -= core
QT -=opengl
QT -=xml
# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
cache()
DEFINES +=QT5BUILD
}
TARGET=SimpleBlit
CONFIG-=app_bundle
CONFIG+=c++11
QT +=opengl
DESTDIR=./
OBJECTS_DIR=obj
DEPENDPATH+=$$PWD/include

SOURCES=$$PWD/src/main.cpp \
        $$PWD/../common/Image.cpp \
        $$PWD/../common/Framebuffer.cpp \
        $$PWD/src/Flock.cpp \
        $$PWD/src/Boid.cpp \
        $$PWD/src/PVector.cpp \
        $$PWD/src/Target.cpp \
        $$PWD/src/colorPalette.cpp \
        $$PWD/src/brushStroke.cpp \



HEADERS =$$PWD/../common/Image.h \
         $$PWD/../common/Framebuffer.h \
         $$PWD/include/PVector.h \
         $$PWD/include/Flock.h \
         $$PWD/include/Boid.h \
         $$PWD/include/Target.h \
         $$PWD/include/colorPalette.h \
         $$PWD/include/brushStroke.h \



INCLUDEPATH +=$$PWD/include
INCLUDEPATH +=$$PWD/../common/

QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64
macx:INCLUDEPATH+=/usr/local/boost/
linux-g++:QMAKE_CXXFLAGS +=  -march=native
linux-g++-64:QMAKE_CXXFLAGS +=  -march=native


LIBS+=-L/usr/local/lib -lglfw3

macx:INCLUDEPATH+=/usr/local/include
LIBS += -L/usr/local/lib
macx:LIBS+= -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo
linux:LIBS+= -lGL -lX11 -lXxf86vm -lXrandr -lXi -ldl -lXinerama -lXcursor -lglfw3 -lGLEW -lpthread
macx:QMAKE_MAC_SDK = macosx10.12














