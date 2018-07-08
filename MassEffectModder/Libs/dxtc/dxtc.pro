TEMPLATE = lib
CONFIG += staticlib warn_off

QT -= gui core

SOURCES += \
    Codec_DXTC_Alpha.cpp \
    Codec_DXTC_RGBA.cpp \
    CompressonatorXCodec.cpp

HEADERS += \
    Common.h \
    CompressonatorXCodec.h

DEFINES += USE_SSE USE_SSE2

QMAKE_CXXFLAGS +=

macx {
    # macOS clang doesn't have OpenMP enabled
    # we need provide version with enabled
    # brew version setup:
    QMAKE_CC  = /usr/local/opt/llvm/bin/clang
    QMAKE_CXX = /usr/local/opt/llvm/bin/clang++
    QMAKE_LIBDIR += /usr/local/opt/llvm/lib
}