# expressioneditor build script
#   (this cmake file written with the help of Marc Bowes' mxitc CMakeLists.txt)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(expressioneditor)
# The version number.
SET(expressioneditor_VERSION_MAJOR 0)
SET(expressioneditor_VERSION_MINOR 1)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR} ${expressioneditor_SOURCE_DIR} ${expressioneditor_BINARY_DIR})

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
    blockhighlighter.cpp
    expressiongraphicsscene.cpp
    capturedstring.cpp
    expressionedit.cpp
    expressionhighlighter.cpp
    graphicsitemsettings.cpp
    main.cpp
    mainwindow.cpp
    regexfactory.cpp
    settingsdialog.cpp
    testblockwidget.cpp
    testinputswidget.cpp
    testsearchreplacewidget.cpp
    GraphicsItems/alternationgraphicsitem.cpp
    GraphicsItems/anchorgraphicsitem.cpp
    GraphicsItems/bracketexpressiongraphicsitem.cpp
    GraphicsItems/characterclassitem.cpp
    GraphicsItems/commentgraphicsitem.cpp
    GraphicsItems/errorgraphicsitem.cpp
    GraphicsItems/expressiongraphicsitem.cpp
    GraphicsItems/groupinggraphicsitem.cpp
    GraphicsItems/literalgraphicsitem.cpp
    GraphicsItems/placeholdergraphicsitem.cpp
    GraphicsItems/regexgraphicsitem.cpp
    GraphicsItems/repeatgraphicsitem.cpp
    GraphicsItems/specialchargraphicsitem.cpp
    RegexModules/cppawkparser.cpp
    RegexModules/cppecmascriptparser.cpp
    RegexModules/cppgrepparser.cpp
    RegexModules/cppposixparser.cpp
    RegexModules/icuparser.cpp
    RegexModules/pcreparser.cpp
    RegexModules/posixparser.cpp
    RegexModules/parser.cpp
    RegexModules/qtparser.cpp
    RegexModules/qtregex.cpp
    RegexModules/regexbase.cpp
    RegexModules/token.cpp
)

# Wrap QOBJECT classes
SET(expressioneditor_HPP_SRCS
    blockhighlighter.hpp
    expressiongraphicsscene.hpp
    expressionedit.hpp
    expressionhighlighter.hpp
    graphicsitemsettings.hpp
    mainwindow.hpp
    settingsdialog.hpp
    testblockwidget.hpp
    testinputswidget.hpp
    testsearchreplacewidget.hpp
    GraphicsItems/alternationgraphicsitem.hpp
    GraphicsItems/anchorgraphicsitem.hpp
    GraphicsItems/bracketexpressiongraphicsitem.hpp
    GraphicsItems/characterclassitem.hpp
    GraphicsItems/commentgraphicsitem.hpp
    GraphicsItems/errorgraphicsitem.hpp
    GraphicsItems/expressiongraphicsitem.hpp
    GraphicsItems/groupinggraphicsitem.hpp
    GraphicsItems/literalgraphicsitem.hpp
    GraphicsItems/regexgraphicsitem.hpp
    GraphicsItems/repeatgraphicsitem.hpp
    GraphicsItems/specialchargraphicsitem.hpp
    RegexModules/cppawkparser.hpp
    RegexModules/cppecmascriptparser.hpp
    RegexModules/cppgrepparser.hpp
    RegexModules/cppposixparser.hpp
    RegexModules/icuparser.hpp
    RegexModules/pcreparser.hpp
    RegexModules/posixparser.hpp
    RegexModules/parser.hpp
    RegexModules/qtparser.hpp
    RegexModules/qtregex.hpp
    RegexModules/regexbase.hpp
)

# Set UI form files
SET(expressioneditor_UI_FILES
    graphicsitemsettings.ui
    mainwindow.ui
    settingsdialog.ui
    testsearchreplacewidget.ui
)

# Set resource files
SET(expressioneditor_QRC_FILES
    images.qrc
    stylesheets.qrc
)

# Set link libraries
SET(expressioneditor_LINK_LIBS ${QT_LIBRARIES})

# Configuring project
CONFIGURE_FILE(cmakeconfig.hpp.in ${expressioneditor_BINARY_DIR}/cmakeconfig.hpp @ONLY)

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
    LIST(APPEND expressioneditor_HPP_SRCS RegexModules/pcreregex.hpp
                                          RegexModules/perlregex.hpp
                                          )
    LIST(APPEND expressioneditor_CPP_SRCS RegexModules/pcreregex.cpp
                                          RegexModules/perlregex.cpp
                                          pcrewrapper.cpp)
    LIST(APPEND expressioneditor_LINK_LIBS ${HAVE_PCRE} ${HAVE_PCRECPP})
else()
    message("## NOT Building PCRE Support   ##")
endif(NOT NO_PCRE)

# Add ICU if available/used
if(NOT NO_ICU)
    message("## -- Building ICU Support     ##")
    LIST(APPEND expressioneditor_HPP_SRCS RegexModules/icuregex.hpp)
    LIST(APPEND expressioneditor_CPP_SRCS RegexModules/icuregex.cpp)
    LIST(APPEND expressioneditor_LINK_LIBS ${HAVE_ICU_I18N} ${HAVE_ICU_UC} ${HAVE_ICU_DATA})
else()
    message("## NOT Building ICU Support    ##")
endif(NOT NO_ICU)

# Disabled for now, if this becomes available the application is ready for it
# but it will require some testing because as of now the implementation for
# GCC is incomplete meaning no code could be tested.
# Add C++11 if requested
if(NOT NO_CPP11)
    message("## -- Building C++11 Support   ##")
    LIST(APPEND expressioneditor_HPP_SRCS RegexModules/cpp11regex.hpp)
    LIST(APPEND expressioneditor_CPP_SRCS RegexModules/cpp11regex.cpp)
    LIST(APPEND CMAKE_CXX_FLAGS "--std=c++0x")
else()
    message("## NOT Building C++11 Support  ##")
endif(NOT NO_CPP11)

message("#################################")

# Add resource files
QT4_ADD_RESOURCES(expressioneditor_CPP_SRCS ${expressioneditor_QRC_FILES})

# Add UI form files
QT4_WRAP_UI(expressioneditor_CPP_SRCS ${expressioneditor_UI_FILES})

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

# CPack Configuration
INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Regular Expression Editor")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/gpl.txt")
SET(CPACK_PACKAGE_FILE_NAME "expressioneditor-${expressioneditor_VERSION_MAJOR}.${expressioneditor_VERSION_MINOR}")
SET(CPACK_PACKAGE_EXECUTABLES expressioneditor "Expression Editor")
SET(CPACK_PACKAGE_NAME ExpressionEditor)
SET(CPACK_PACKAGE_VERSION_MAJOR 0)
SET(CPACK_PACKAGE_VERSION_MINOR 1)
SET(CPACK_PACKAGE_VERSION_PATCH 0)
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Expression Editor ${expressioneditor_VERSION_MAJOR}.${expressioneditor_VERSION_MINOR}")

# Per-platform CPack Configuration
IF(UNIX)
    INSTALL(PROGRAMS ${CMAKE_BINARY_DIR}/expressioneditor DESTINATION bin)
ELSEIF(APPLE)
    INSTALL(PROGRAMS ${CMAKE_BINARY_DIR}/expressioneditor DESTINATION bin)
ELSEIF(WIN32)
    SET(CPACK_GENERATOR NSIS)
    SET(CPACK_NSIS_MUI_ICON ${expressioneditor_SOURCE_DIR}/images/application-icon/expressioneditor.ico)
    #SET(CPACK_PACKAGE_ICON ${expressioneditor_SOURCE_DIR}/images/application-icon/256x256.png)

    INSTALL(PROGRAMS ${QT_BINARY_DIR}/QtCore4.dll
                     ${QT_BINARY_DIR}/QtGui4.dll
                     ${QT_BINARY_DIR}/mingwm10.dll
                     ${QT_BINARY_DIR}/libgcc_s_dw2-1.dll
            DESTINATION bin)

    IF(NOT NO_PCRE)
        INSTALL(PROGRAMS ${PCRE_PATH}/libpcre.dll
                         ${PCRE_PATH}/libpcrecpp.dll
                DESTINATION bin)
    ENDIF(NOT NO_PCRE)
    INSTALL(PROGRAMS ${CMAKE_BINARY_DIR}/expressioneditor.exe DESTINATION bin)
ENDIF()

INCLUDE(CPack)
