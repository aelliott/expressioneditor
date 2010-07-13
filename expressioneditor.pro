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
    qtregex.cpp \
    regexfactory.cpp \
    pcrewrapper.cpp \
    capturedstring.cpp \
    commentgraphicsitem.cpp \
    configgraphicsitem.cpp \
    posixregex.cpp \
    expressiontester.cpp \
    blocktester.cpp \
    blockhighlighter.cpp \
    settingsdialog.cpp
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
    qtregex.hpp \
    regexfactory.hpp \
    pcrewrapper.hpp \
    capturedstring.hpp \
    commentgraphicsitem.hpp \
    configgraphicsitem.hpp \
    posixregex.hpp \
    expressiontester.hpp \
    blocktester.hpp \
    blockhighlighter.hpp \
    settingsdialog.hpp
RESOURCES += images.qrc
QT += xml
LIBS += -lpcre \
    -lpcrecpp \
    -L/usr/include
OTHER_FILES += README.txt \
    gpl.txt \
    CREDITS.txt
