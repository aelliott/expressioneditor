CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(ExpressionEditor)
# The version number.
SET(ExpressionEditor_VERSION_MAJOR 0)
SET(ExpressionEditor_VERSION_MINOR 1)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} ${ExpressionEditor_SOURCE_DIR})

INCLUDE(CheckIncludeFiles)
#INCLUDE(CheckLibraryExists)

# Check for regex.h
CHECK_INCLUDE_FILES(regex.h HAVE_REGEX_H)
#if(NOT HAVE_REGEX_H)
#    set(NO_POSIX "Not building POSIX support" ON)
#endif(NOT HAVE_REGEX_H)

# Check for ICU files
CHECK_INCLUDE_FILES(unicode/regex.h HAVE_UNICODE_REGEX_H)
CHECK_INCLUDE_FILES(unicode/conv.h HAVE_UNICODE_CONV_H)
#if(NOT HAVE_UNICODE_CONV_H OR NOT HAVE_UNICODE_REGEX_H)
#    set(NO_ICU "Not building ICU support" ON)
#endif(NOT HAVE_UNICODE_CONV_H OR NOT HAVE_UNICODE_REGEX_H)

# Check for PCRE
CHECK_INCLUDE_FILES(pcre.h HAVE_PCRE_H)
CHECK_INCLUDE_FILES(pcrecpp.h HAVE_PCRECPP_H)
#if(NOT HAVE_PCRE_H OR NOT HAVE_PCRECPP_H)
#    set(NO_PCRE "Not building PCRE support" ON)
#endif(NOT HAVE_PCRE_H OR NOT HAVE_PCRECPP_H)

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
SET(ExpressionEditor_CPP_SRCS
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
SET(ExpressionEditor_HPP_SRCS
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
SET(ExpressionEditor_LINK_LIBS ${QT_LIBRARIES})



# Add POSIX if available/used
if(NOT NO_POSIX)
    LIST(APPEND ExpressionEditor_HPP_SRCS posixregex.hpp)
    LIST(APPEND ExpressionEditor_CPP_SRCS posixregex.cpp)
endif(NOT NO_POSIX)

# Add PCRE if available/used
if(NOT NO_PCRE)
    LIST(APPEND ExpressionEditor_HPP_SRCS pcreregex.hpp)
    LIST(APPEND ExpressionEditor_CPP_SRCS pcreregex.cpp pcrewrapper.cpp)
    LIST(APPEND ExpressionEditor_LINK_LIBS pcre pcrecpp)
endif(NOT NO_PCRE)

# Add ICU if available/used
if(NOT NO_ICU)
    LIST(APPEND ExpressionEditor_HPP_SRCS icuregex.hpp)
    LIST(APPEND ExpressionEditor_CPP_SRCS icuregex.cpp)
    LIST(APPEND ExpressionEditor_LINK_LIBS icui18n icuuc icudata)
endif(NOT NO_ICU)

QT4_WRAP_CPP(ExpressionEditor_CPP_SRCS ${ExpressionEditor_HPP_SRCS})

ADD_EXECUTABLE(ExpressionEditor ${ExpressionEditor_CPP_SRCS})

# Link to Qt
TARGET_LINK_LIBRARIES(ExpressionEditor ${ExpressionEditor_LINK_LIBS})
