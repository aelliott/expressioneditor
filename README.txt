Expression Editor README:

[0] CONTENTS
0. Contents
1. Introduction
2. Installation

[1] INTRODUCTION

Expression Editor is a GPLv3 tool for editing regular expressions, it is
currently in a pre-alpha state.

[2] INSTALLATION

At the moment there is no real build process, Expression Editor requires
Qt4.6+ or the Qt4.6+ SDK.  If you have Qt4.6 installed then you can just
execute:

$ qmake expressioneditor.pro
$ make
$ ./expressioneditor

Or if you are using the Qt4.6+ SDK then you can open expressioneditor.pro
in QtCreator, and then select build (you may or may not need to tell it to
run qmake from the Build menu)

After the initial run a settings directory will have been created in
~/.expressioneditor/ to complete installation copy across the files in
the source's common/ directory into ~/.expressioneditor/common/
