SOURCES += main.cpp \
    mainwindow.cpp \
    welcome.cpp \
    expressioneditor.cpp \
    multilinetester.cpp \
    expressionhighlighter.cpp \
    graphicaleditor.cpp \
    graphicaltoolkit.cpp \
    graphicalworkspace.cpp \
    graphicalexpression.cpp \
    textgraphicsitem.cpp \
    alternativesgraphicsitem.cpp \
    groupinggraphicsitem.cpp \
    charrangegraphicsitem.cpp \
    repeatgraphicsitem.cpp \
    specialchargraphicsitem.cpp \
    repeateditdialog.cpp \
    texteditdialog.cpp \
    specialchareditdialog.cpp \
    regexgraphicsitem.cpp \
    regexbase.cpp \
    pcreregex.cpp \
    pcrewrapper.cpp \
    posixregex.cpp \
    qtregex.cpp \
    regexfactory.cpp \
    capturedstring.cpp \
    commentgraphicsitem.cpp \
    configgraphicsitem.cpp \
    expressiontester.cpp \
    blocktester.cpp \
    blockhighlighter.cpp \
    settingsdialog.cpp \
    icuregex.cpp
HEADERS += mainwindow.hpp \
    welcome.hpp \
    expressioneditor.hpp \
    multilinetester.hpp \
    expressionhighlighter.hpp \
    graphicaleditor.hpp \
    graphicaltoolkit.hpp \
    graphicalworkspace.hpp \
    graphicalexpression.hpp \
    textgraphicsitem.hpp \
    alternativesgraphicsitem.hpp \
    groupinggraphicsitem.hpp \
    charrangegraphicsitem.hpp \
    repeatgraphicsitem.hpp \
    specialchargraphicsitem.hpp \
    repeateditdialog.hpp \
    texteditdialog.hpp \
    specialchareditdialog.hpp \
    regexgraphicsitem.hpp \
    regexbase.hpp \
    pcreregex.hpp \
    pcrewrapper.hpp \
    posixregex.hpp \
    qtregex.hpp \
    regexfactory.hpp \
    capturedstring.hpp \
    commentgraphicsitem.hpp \
    configgraphicsitem.hpp \
    expressiontester.hpp \
    blocktester.hpp \
    blockhighlighter.hpp \
    settingsdialog.hpp \
    icuregex.hpp
win32 {
SOURCES -= pcreregex.cpp \
    pcrewrapper.cpp \
    posixregex.cpp
HEADERS -= pcreregex.hpp \
    pcrewrapper.hpp \
    posixregex.hpp
}
RESOURCES += images.qrc
QT += xml
# Remove this if you want to compile without PCRE
!win32 {
LIBS += -lpcre \
    -lpcrecpp \
    -L/usr/include \
    -L/usr/lib \
    -licui18n \
    -licuuc \
    -licudata
}
OTHER_FILES += README.txt \
    gpl.txt \
    CREDITS.txt \
    CMakeLists.txt
win32 {
DEFINES += NO_PCRE NO_POSIX NO_ICU
}
