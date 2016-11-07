TARGET = ImageTest
SOURCES += $$PWD/src/main.cpp \
           $$PWD/src/Image.cpp

HEADERS += $$PWD/include/Image.h

OTHER_FILES += $$PWD/README.md

INCLUDEPATH += $$PWD/include

QMAKE_CXXFLAGS += $$system(Magick++-config --cppflags)

LIBS += $$system(Magick++-config --libs)
