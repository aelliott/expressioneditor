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
    message(STATUS "icuuc found at " ${HAVE_ICU_UC})
    message(STATUS "icui18n found at " ${HAVE_ICU_I18N})
    message(STATUS "icudata found at " ${HAVE_ICU_DATA})
    message(STATUS "[Optional] Building ICU support")
endif(NOT HAVE_ICU_UC OR NOT HAVE_ICU_I18N OR NOT HAVE_ICU_DATA)

# Check for PCRE
FIND_LIBRARY(HAVE_PCRE pcre)
FIND_LIBRARY(HAVE_PCRECPP pcrecpp)
if(NOT HAVE_PCRE OR NOT HAVE_PCRECPP)
    message(STATUS "[Optional] Not building PCRE support")
    set(NO_PCRE true)
else()
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
    alternativesgraphicsitem.cpp
    blockhighlighter.cpp
    blocktester.cpp
    capturedstring.cpp
    charrangegraphicsitem.cpp
    commentgraphicsitem.cpp
    configgraphicsitem.cpp
    expressioneditor.cpp
    expressionhighlighter.cpp
    expressiontester.cpp
    graphicaleditor.cpp
    graphicalexpression.cpp
    graphicaltoolkit.cpp
    graphicalworkspace.cpp
    groupinggraphicsitem.cpp
    mainwindow.cpp
    multilinetester.cpp
    qtregex.cpp
    regexbase.cpp
    regexfactory.cpp
    regexgraphicsitem.cpp
    repeatgraphicsitem.cpp
    repeateditdialog.cpp
    settingsdialog.cpp
    specialchareditdialog.cpp
    specialchargraphicsitem.cpp
    texteditdialog.cpp
    textgraphicsitem.cpp
    welcome.cpp
)

# Wrap QOBJECT classes
SET(expressioneditor_HPP_SRCS
    alternativesgraphicsitem.hpp
    blockhighlighter.hpp
    blocktester.hpp
    charrangegraphicsitem.hpp
    commentgraphicsitem.hpp
    configgraphicsitem.hpp
    expressioneditor.hpp
    expressionhighlighter.hpp
    expressiontester.hpp
    graphicaleditor.hpp
    graphicalexpression.hpp
    graphicaltoolkit.hpp
    graphicalworkspace.hpp
    groupinggraphicsitem.hpp
    mainwindow.hpp
    multilinetester.hpp
    qtregex.hpp
    regexbase.hpp
    regexgraphicsitem.hpp
    repeatgraphicsitem.hpp
    repeateditdialog.hpp
    settingsdialog.hpp
    specialchareditdialog.hpp
    specialchargraphicsitem.hpp
    texteditdialog.hpp
    textgraphicsitem.hpp
    welcome.hpp
)

# Set link libraries
SET(expressioneditor_LINK_LIBS ${QT_LIBRARIES})

# Configuring project
CONFIGURE_FILE(cmakeconfig.hpp.in cmakeconfig.hpp @ONLY)

# Output all optional details:
message("#################################")
message("##                             ##")
message("##     Optional Components     ##")
message("##                             ##")
message("#################################")

# Add POSIX if available/used
if(NOT NO_POSIX)
    message("## -- Building POSIX Support   ##")
    LIST(APPEND expressioneditor_HPP_SRCS posixregex.hpp)
    LIST(APPEND expressioneditor_CPP_SRCS posixregex.cpp)
else()
    message("## NOT Building POSIX Support  ##")
endif(NOT NO_POSIX)

# Add PCRE if available/used
if(NOT NO_PCRE)
    message("## -- Building PCRE Support    ##")
    LIST(APPEND expressioneditor_HPP_SRCS pcreregex.hpp)
    LIST(APPEND expressioneditor_CPP_SRCS pcreregex.cpp pcrewrapper.cpp)
    LIST(APPEND expressioneditor_LINK_LIBS pcre pcrecpp)
else()
    message("## NOT Building PCRE Support   ##")
endif(NOT NO_PCRE)

# Add ICU if available/used
if(NOT NO_ICU)
    message("## -- Building ICU Support     ##")
    LIST(APPEND expressioneditor_HPP_SRCS icuregex.hpp)
    LIST(APPEND expressioneditor_CPP_SRCS icuregex.cpp)
    LIST(APPEND expressioneditor_LINK_LIBS icui18n icuuc icudata)
else()
    message("## NOT Building ICU Support    ##")
endif(NOT NO_ICU)

message("#################################")

QT4_WRAP_CPP(expressioneditor_CPP_SRCS ${expressioneditor_HPP_SRCS})

ADD_EXECUTABLE(expressioneditor ${expressioneditor_CPP_SRCS})

# Link to Qt
TARGET_LINK_LIBRARIES(expressioneditor ${expressioneditor_LINK_LIBS})
