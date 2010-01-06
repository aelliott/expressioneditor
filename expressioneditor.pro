SOURCES += main.cpp \
    mainwindow.cpp \
    welcome.cpp \
    expressioneditor.cpp \
    expressiontester.cpp \
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
    commentgraphicsitem.cpp
HEADERS += mainwindow.hpp \
    welcome.hpp \
    expressioneditor.hpp \
    expressiontester.hpp \
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
    commentgraphicsitem.hpp
RESOURCES += images.qrc
QT += xml
LIBS += -lpcre \
    -lpcrecpp \
    -L/usr/include
OTHER_FILES += README.txt \
    gpl.txt
