# expressioneditor build script
#   (this cmake file written with the help of Marc Bowes' mxitc CMakeLists.txt)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(expressioneditor)
# The version number.
SET(expressioneditor_VERSION_MAJOR 0)
SET(expressioneditor_VERSION_MINOR 1)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} ${expressioneditor_SOURCE_DIR})

INCLUDE(CheckIncludeFiles)
#INCLUDE(CheckLibraryExists)

# Check for regex.h
FIND_FILE(HAVE_REGEX_H regex.h)
if(NOT HAVE_REGEX_H)
    message(STATUS "[Optional] Not building POSIX support")
    set(NO_POSIX true)
else()
    message(STATUS "[Optional] Building POSIX support")
endif(NOT HAVE_REGEX_H)

# Check for ICU files
FIND_LIBRARY(HAVE_ICU_UC icuuc)
FIND_LIBRARY(HAVE_ICU_I18N icui18n)
FIND_LIBRARY(HAVE_ICU_DATA icudata)
if(NOT HAVE_ICU_UC OR NOT HAVE_ICU_I18N OR NOT HAVE_ICU_DATA)
    message(STATUS "[Optional] Not building ICU support")
    set(NO_ICU true)
else()
    FIND_PATH(ICU_PATH "unicode/regex.h")
    if(ICU_PATH)
        INCLUDE_DIRECTORIES(${ICU_PATH})
        message(STATUS "icuuc found at " ${HAVE_ICU_UC})
        message(STATUS "icui18n found at " ${HAVE_ICU_I18N})
        message(STATUS "icudata found at " ${HAVE_ICU_DATA})
        message(STATUS "[Optional] Building ICU support")
    else()
        message(STATUS "[Optional] Not building ICU support")
        set(NO_ICU true)
    endif(ICU_PATH)
endif(NOT HAVE_ICU_UC OR NOT HAVE_ICU_I18N OR NOT HAVE_ICU_DATA)

# Check for PCRE
FIND_LIBRARY(HAVE_PCRE pcre)
FIND_LIBRARY(HAVE_PCRECPP pcrecpp)
if(NOT HAVE_PCRE OR NOT HAVE_PCRECPP)
    message(STATUS "[Optional] Not building PCRE support")
    set(NO_PCRE true)
else()
    FIND_PATH(PCRE_PATH pcre.h)
    INCLUDE_DIRECTORIES(${PCRE_PATH})
    message(STATUS "pcre found at " ${HAVE_PCRE})
    message(STATUS "pcrecpp found at " ${HAVE_PCRECPP})
    message(STATUS "[Optional] Building PCRE support")
endif(NOT HAVE_PCRE OR NOT HAVE_PCRECPP)

SET(QT_MIN_VERSION "4.6.0")
#INCLUDE(FindQt4)

# Find Qt
FIND_PACKAGE(Qt4 REQUIRED)

# Qt options
SET(QT_USE_QTMAIN true)
SET(QT_USE_QTXML true)

# Bring in Qt
INCLUDE(${QT_USE_FILE})

# Add .cpp files
SET(expressioneditor_CPP_SRCS
    main.cpp
    mainwindow.cpp
    welcome.cpp
    expressioneditor.cpp
    multilinetester.cpp
    expressionhighlighter.cpp
    graphicaleditor.cpp
    graphicaltoolkit.cpp
    graphicalworkspace.cpp
    graphicalexpression.cpp
    repeateditdialog.cpp
    texteditdialog.cpp
    specialchareditdialog.cpp
    regexfactory.cpp
    capturedstring.cpp
    expressiontester.cpp
    blocktester.cpp
    blockhighlighter.cpp
    settingsdialog.cpp
    searchreplacetester.cpp
    GraphicsItems/textgraphicsitem.cpp
    GraphicsItems/specialchargraphicsitem.cpp
    GraphicsItems/repeatgraphicsitem.cpp
    GraphicsItems/regexgraphicsitem.cpp
    GraphicsItems/groupinggraphicsitem.cpp
    GraphicsItems/configgraphicsitem.cpp
    GraphicsItems/commentgraphicsitem.cpp
    GraphicsItems/charrangegraphicsitem.cpp
    GraphicsItems/alternativesgraphicsitem.cpp
    RegexModules/regexbase.cpp
    RegexModules/qtregex.cpp
)

# Wrap QOBJECT classes
SET(expressioneditor_HPP_SRCS
    mainwindow.hpp
    welcome.hpp
    expressioneditor.hpp
    multilinetester.hpp
    expressionhighlighter.hpp
    graphicaleditor.hpp
    graphicaltoolkit.hpp
    graphicalworkspace.hpp
    graphicalexpression.hpp
    repeateditdialog.hpp
    texteditdialog.hpp
    specialchareditdialog.hpp
    expressiontester.hpp
    blocktester.hpp
    blockhighlighter.hpp
    settingsdialog.hpp
    searchreplacetester.hpp
    GraphicsItems/textgraphicsitem.hpp
    GraphicsItems/specialchargraphicsitem.hpp
    GraphicsItems/repeatgraphicsitem.hpp
    GraphicsItems/regexgraphicsitem.hpp
    GraphicsItems/groupinggraphicsitem.hpp
    GraphicsItems/configgraphicsitem.hpp
    GraphicsItems/commentgraphicsitem.hpp
    GraphicsItems/charrangegraphicsitem.hpp
    GraphicsItems/alternativesgraphicsitem.hpp
    RegexModules/regexbase.hpp
    RegexModules/qtregex.hpp
)

# Set resource files
SET(expressioneditor_QRC_FILES
    images.qrc
)

# Set link libraries
SET(expressioneditor_LINK_LIBS ${QT_LIBRARIES})

# Configuring project
CONFIGURE_FILE(cmakeconfig.hpp.in ${CMAKE_SOURCE_DIR}/cmakeconfig.hpp @ONLY)

# Output all optional details:
message("#################################")
message("##                             ##")
message("##     Optional Components     ##")
message("##                             ##")
message("#################################")

# Add POSIX if available/used
if(NOT NO_POSIX)
    message("## -- Building POSIX Support   ##")
    LIST(APPEND expressioneditor_HPP_SRCS RegexModules/posixregex.hpp)
    LIST(APPEND expressioneditor_CPP_SRCS RegexModules/posixregex.cpp)
else()
    message("## NOT Building POSIX Support  ##")
endif(NOT NO_POSIX)

# Add PCRE if available/used
if(NOT NO_PCRE)
    message("## -- Building PCRE Support    ##")
    LIST(APPEND expressioneditor_HPP_SRCS RegexModules/pcreregex.hpp RegexModules/perlregex.hpp)
    LIST(APPEND expressioneditor_CPP_SRCS RegexModules/pcreregex.cpp RegexModules/perlregex.cpp pcrewrapper.cpp)
    LIST(APPEND expressioneditor_LINK_LIBS pcre pcrecpp)
else()
    message("## NOT Building PCRE Support   ##")
endif(NOT NO_PCRE)

# Add ICU if available/used
if(NOT NO_ICU)
    message("## -- Building ICU Support     ##")
    LIST(APPEND expressioneditor_HPP_SRCS RegexModules/icuregex.hpp)
    LIST(APPEND expressioneditor_CPP_SRCS RegexModules/icuregex.cpp)
    LIST(APPEND expressioneditor_LINK_LIBS icui18n icuuc icudata)
else()
    message("## NOT Building ICU Support    ##")
endif(NOT NO_ICU)

# Disabled for now, if this becomes available the application is ready for it
# but it will require some testing because as of now the implementation for
# GCC is incomplete meaning no code could be tested.
# Add C++0x if requested
#if(WITH_CPP0X)
#    message("## -- Building C++0x Support   ##")
#    LIST(APPEND expressioneditor_HPP_SRCS RegexModules/cpp0xregex.hpp)
#    LIST(APPEND expressioneditor_CPP_SRCS RegexModules/cpp0xregex.cpp)
#    LIST(APPEND CMAKE_CXX_FLAGS "--std=c++0x")
#else()
#    message("## NOT Building C++0x Support  ##")
#endif(WITH_CPP0X)

message("#################################")

# Add resource files
QT4_ADD_RESOURCES(expressioneditor_CPP_SRCS ${expressioneditor_QRC_FILES})

# Generate MOC files
QT4_WRAP_CPP(expressioneditor_CPP_SRCS ${expressioneditor_HPP_SRCS})

# Build Executable
IF(UNIX)
    ADD_EXECUTABLE(expressioneditor ${expressioneditor_CPP_SRCS})
ELSEIF(APPLE)
    SET(CMAKE_OSX_ARCHITECTURES i386)
    ADD_EXECUTABLE(expressioneditor MACOSX_BUNDLE ${expressioneditor_CPP_SRCS})
ELSEIF(WIN32)
    ADD_EXECUTABLE(expressioneditor WIN32 ${expressioneditor_CPP_SRCS})
ENDIF()

# Link to Qt and any optional libs
TARGET_LINK_LIBRARIES(expressioneditor ${expressioneditor_LINK_LIBS})

INSTALL(PROGRAMS ${CMAKE_BINARY_DIR}/expressioneditor DESTINATION bin)
