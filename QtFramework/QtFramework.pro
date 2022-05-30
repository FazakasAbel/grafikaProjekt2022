QT += core gui #widgets opengl

# We assume that the compiler is compatible with the C++ 11 standard.
greaterThan(QT_MAJOR_VERSION, 4){
    CONFIG         += c++11
    QT             += widgets
} else {
    QMAKE_CXXFLAGS += -std=c++0x
}

greaterThan(QT_MAJOR_VERSION, 5){
    QT             += openglwidgets
}

win32 {
    message("Windows platform...")

    INCLUDEPATH += $$PWD/Dependencies/Include
    DEPENDPATH += $$PWD/Dependencies/Include

    LIBS += -lopengl32 -lglu32

    CONFIG(release, debug|release): {
        contains(QT_ARCH, i386) {
            message("x86 (i.e., 32-bit) release build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x86/" -lglew32
        } else {
            message("x64 (i.e., 64-bit) release build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x64/" -lglew32
        }
    } else: CONFIG(debug, debug|release): {
        contains(QT_ARCH, i386) {
            message("x86 (i.e., 32-bit) debug build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x86/" -lglew32
        } else {
            message("x64 (i.e., 64-bit) debug build")
            LIBS += -L"$$PWD/Dependencies/Lib/GL/x64/" -lglew32
        }
    }

    msvc {
      QMAKE_CXXFLAGS += -openmp -arch:AVX #-D "_CRT_SECURE_NO_WARNINGS"
      QMAKE_CXXFLAGS_RELEASE *= -O2
    }
}

unix: !mac {
    message("Unix/Linux platform...")

    # for GLEW installed into /usr/lib/libGLEW.so or /usr/lib/glew.lib
    LIBS += -lGLEW -lGLU
}

mac {
    message("Macintosh platform...")

    # IMPORTANT: change the letters x, y, z in the next two lines
    # to the corresponding version numbers of the GLEW library
    # which was installed by using the command 'brew install glew'
    INCLUDEPATH += "/opt/homebrew/Cellar/glew/2.2.0_1/include"
    LIBS += -L"/opt/homebrew/Cellar/glew/2.2.0_1/lib" -lGLEW

    # the OpenGL library has to added as a framework
    LIBS += -framework OpenGL
}


FORMS += \
    GUI/MainWindow.ui \
    GUI/SideWidget.ui

HEADERS += \
    Core/BasicFunctions.h \
    Core/Colors4.h \
    Core/Constants.h \
    Core/CyclicCurves3.h \
    Core/DCoordinates3.h \
    Core/FOAHCompositeArc.h \
    Core/FOAHCompositePatch.h \
    Core/FirstOrderAlgebraic-HyperbolicArc3.h \
    Core/FirstOrderAlgebraic-HyperbolicPatch3.h \
    Core/GenericCurves3.h \
    Core/Lights.h \
    Core/LinearCombination3.h \
    Core/Materials.h \
    Core/Matrices.h \
    Core/RealSquareMatrices.h \
    Core/ShaderPrograms.h \
    Core/TCoordinates4.h \
    Core/TensorProductSurfaces3.h \
    Core/TriangularFaces.h \
    Core/TriangulatedMeshes3.h \
    GUI/GLWidget.h \
    GUI/MainWindow.h \
    GUI/SideWidget.h \
    Core/Exceptions.h \
    Parametric/ParametricCurves3.h \
    Parametric/ParametricSurfaces3.h \
    Test/TestFunctions.h

SOURCES += \
    Core/BasicFunctions.cpp \
    Core/CyclicCurves3.cpp \
    Core/FOAHCompositeArc.cpp \
    Core/FOAHCompositePatch.cpp \
    Core/FirstOrderAlgebraic-HyperbolicPatch3.cpp \
    Core/FirstOrderAlgebraicHyperbolicArc3.cpp \
    Core/GenericCurves3.cpp \
    Core/Lights.cpp \
    Core/LinearCombination3.cpp \
    Core/Materials.cpp \
    Core/RealSquareMatrices.cpp \
    Core/ShaderPrograms.cpp \
    Core/TensorProductSurfaces3.cpp \
    Core/TriangulatedMeshes3.cpp \
    Core/stringHelp.cpp \
    GUI/GLWidget.cpp \
    GUI/MainWindow.cpp \
    GUI/SideWidget.cpp \
    Parametric/ParametricCurves3.cpp \
    Parametric/ParametricSurfaces3.cpp \
    Test/TestFunctions.cpp \
    main.cpp
