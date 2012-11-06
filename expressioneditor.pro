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
    capturedstring.cpp \
    regexfactory.cpp \
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
    GraphicsItems/commentgraphicsitem.cpp \
    testinputswidget.cpp \
    testblockwidget.cpp \
    testsearchreplacewidget.cpp \
    RegexModules/cpp11regex.cpp \
    RegexModules/cppecmascriptparser.cpp \
    RegexModules/cppposixparser.cpp \
    RegexModules/cppawkparser.cpp \
    RegexModules/cppgrepparser.cpp \
    GraphicsItems/specialchargraphicsitem.cpp \
    expressiongraphicsscene.cpp \
    GraphicsItems/regexgraphicsitem.cpp \
    GraphicsItems/placeholdergraphicsitem.cpp

HEADERS  += mainwindow.hpp \
    RegexModules/regexbase.hpp \
    RegexModules/qtregex.hpp \
    capturedstring.hpp \
    regexfactory.hpp \
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
    GraphicsItems/commentgraphicsitem.hpp \
    testinputswidget.hpp \
    testblockwidget.hpp \
    testsearchreplacewidget.hpp \
    RegexModules/cpp11regex.hpp \
    RegexModules/cppecmascriptparser.hpp \
    RegexModules/cppposixparser.hpp \
    RegexModules/cppawkparser.hpp \
    RegexModules/cppgrepparser.hpp \
    GraphicsItems/specialchargraphicsitem.hpp \
    expressiongraphicsscene.hpp \
    GraphicsItems/regexgraphicsitem.hpp \
    GraphicsItems/placeholdergraphicsitem.hpp

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
    README.txt \
    android/AndroidManifest.xml \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/layout/splash.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/android.toolchain.cmake

RESOURCES += \
    images.qrc \
    stylesheets.qrc

android-g++ {
    CONFIG += dll
}

