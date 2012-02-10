#-------------------------------------------------
#
# Project created by QtCreator 2011-08-18T18:34:07
#
#-------------------------------------------------

QT       += core gui

TARGET = expressioneditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    RegexModules/regexbase.cpp \
    RegexModules/qtregex.cpp \
    RegexModules/posixregex.cpp \
    RegexModules/perlregex.cpp \
    RegexModules/pcreregex.cpp \
    RegexModules/icuregex.cpp \
    capturedstring.cpp \
    regexfactory.cpp \
    pcrewrapper.cpp \
    RegexModules/token.cpp \
    RegexModules/parser.cpp \
    RegexModules/qtparser.cpp \
    GraphicsItems/expressiongraphicsitem.cpp \
    GraphicsItems/literalgraphicsitem.cpp \
    GraphicsItems/errorgraphicsitem.cpp \
    GraphicsItems/groupinggraphicsitem.cpp \
    GraphicsItems/repeatgraphicsitem.cpp \
    GraphicsItems/characterclassitem.cpp \
    expressionhighlighter.cpp \
    blockhighlighter.cpp \
    GraphicsItems/alternationgraphicsitem.cpp \
    GraphicsItems/anchorgraphicsitem.cpp \
    expressionedit.cpp \
    settingsdialog.cpp \
    graphicsitemsettings.cpp \
    GraphicsItems/bracketexpressiongraphicsitem.cpp \
    RegexModules/pcreparser.cpp \
    RegexModules/posixparser.cpp \
    RegexModules/icuparser.cpp \
    GraphicsItems/commentgraphicsitem.cpp \
    testinputswidget.cpp \
    testblockwidget.cpp \
    testsearchreplacewidget.cpp \
    RegexModules/cpp11regex.cpp \
    RegexModules/cppecmascriptparser.cpp \
    RegexModules/cppposixparser.cpp \
    RegexModules/cppawkparser.cpp \
    RegexModules/cppgrepparser.cpp

HEADERS  += mainwindow.hpp \
    RegexModules/regexbase.hpp \
    RegexModules/qtregex.hpp \
    RegexModules/posixregex.hpp \
    RegexModules/perlregex.hpp \
    RegexModules/pcreregex.hpp \
    RegexModules/icuregex.hpp \
    capturedstring.hpp \
    regexfactory.hpp \
    pcrewrapper.hpp \
    RegexModules/tokens.hpp \
    RegexModules/token.hpp \
    RegexModules/qtparser.hpp \
    RegexModules/parser.hpp \
    GraphicsItems/expressiongraphicsitem.hpp \
    GraphicsItems/literalgraphicsitem.hpp \
    GraphicsItems/errorgraphicsitem.hpp \
    GraphicsItems/groupinggraphicsitem.hpp \
    GraphicsItems/repeatgraphicsitem.hpp \
    GraphicsItems/characterclassitem.hpp \
    expressionhighlighter.hpp \
    blockhighlighter.hpp \
    GraphicsItems/alternationgraphicsitem.hpp \
    GraphicsItems/anchorgraphicsitem.hpp \
    expressionedit.hpp \
    settingsdialog.hpp \
    graphicsitemsettings.hpp \
    GraphicsItems/bracketexpressiongraphicsitem.hpp \
    RegexModules/pcreparser.hpp \
    RegexModules/posixparser.hpp \
    RegexModules/icuparser.hpp \
    GraphicsItems/commentgraphicsitem.hpp \
    testinputswidget.hpp \
    testblockwidget.hpp \
    testsearchreplacewidget.hpp \
    RegexModules/cpp11regex.hpp \
    RegexModules/cppecmascriptparser.hpp \
    RegexModules/cppposixparser.hpp \
    RegexModules/cppawkparser.hpp \
    RegexModules/cppgrepparser.hpp

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    graphicsitemsettings.ui \
    testsearchreplacewidget.ui

OTHER_FILES += \
    CMakeLists.txt \
    cmakeconfig.hpp.in \
    doxy.conf \
    css/main.css \
    gpl.txt \
    .gitignore \
    CREDITS.txt \
    README.txt

RESOURCES += \
    images.qrc \
    stylesheets.qrc
