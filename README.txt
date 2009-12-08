Expression Editor README:
-------------------------

[0] CONTENTS
0. Contents
1. Introduction
2. Installation
2.1 Linux
2.2 Windows
2.3 Mac OSX

[1] INTRODUCTION

Expression Editor is a GPLv3 tool for editing regular expressions, it is
currently in a pre-alpha state.

[2] INSTALLATION

At the moment there is no real build process, Expression Editor requires
Qt4.6+ or the Qt4.6+ SDK.

[2.1] LINUX

If you have Qt4.6 installed (you can check with "qmake --version") then
you can just execute:

$ qmake expressioneditor.pro
$ make
$ ./expressioneditor

Or if you are using the Qt4.6+ SDK then you can open expressioneditor.pro
in QtCreator, and then select build.

After the initial run a settings directory will have been created in
~/.expressioneditor/ to complete installation copy across the files in
the source tree's common/ directory into ~/.expressioneditor/common/

[2.2] WINDOWS

Since there is currently no Windows installer for Expression Editor you
will need to compile it as in Linux, there are several methods for this
but I recommend you fetch the Qt4.6+ SDK and open expressioneditor.pro
in QtCreator, and then select build.

After the initial run a settings directory will have been created in
C:/Documents and Settings/Username/expressioneditor to complete
installation copy across the files in the source tree's common/ directory
to the common/ directory in the settings directory.

[2.3] MAC OSX

As yet there have been no tests of Expression Editor running on OSX, but
following the instructions for the Qt SDK should give a good chance of it
working.
