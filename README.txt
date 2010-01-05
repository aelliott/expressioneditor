Expression Editor README:
-------------------------

[0] CONTENTS
0. Contents
1. Introduction
2. Installation
2.0 Requirements and Hints
2.1 Getting the Source
2.2 Linux
2.3 Windows
2.4 Mac OSX

[1] INTRODUCTION

Expression Editor is a GPLv3 tool for editing regular expressions, it is
currently in a pre-alpha state.

[2] INSTALLATION

[2.0] REQUIREMENTS AND HINTS

At the moment there is no automated build process, so Expression Editor
requires the development libraries of Qt4.6+ or the Qt4.6+ SDK (which
contains the required libraries and QtCreator a C++/Qt IDE), the
development libraries for PCRE (and pcrecpp), and it requires a build
toolchain (compiler, linker, etc).

On windows this should be fine if you install the SDK, on Linux many
distros include the build essentials in the default packages, but there
are also many that do not include them by default and you will have to
fetch them via your distributions package management system.  On OSX
I believe you will need Xcode or Xcode tools to get the build tools for
QtCreator to compile the application.

If the compile fails for some reason, first try "Build > Clean all" in
QtCreator or "make clean" in a terminal and try the build again.  If it
still won't compile then register a bug at the following URL:

http://github.com/aelliott/expressioneditor/issues

And I will look into the problem, hopefully finding the cause for the
failed compile.  The tree should be buildable at all times, so a failed
compile is a definite bug.

[2.1] GETTING THE SOURCE

The source is available through Expression Editor's git repository at:

http://github.com/aelliott/expressioneditor

On Linux and OSX you can fetch this via git in the command line, make
sure you have git (in Linux via your distribution's package management
and in OSX from the downloads page at http://git-scm.com/) you can then
fetch the source in a src/ directory by doing:

$ cd ~
$ mkdir src && cd src
$ git clone git://github.com/aelliott/expressioneditor.git
$ cd expressioneditor

Once you have the source, you can keep it up to date using git like this:

$ cd ~/src/expressioneditor # or if you put it elsewhere use that path
$ git pull

To fetch the source on Windows you can either compile a git client from
source in cygwin or you can use msysgit both of which are linked from
the http://git-scm.com/ download page.

[2.2] LINUX

If you have Qt4.6 installed (you can check with "qmake --version") then
you can just execute:

$ qmake expressioneditor.pro
$ make
$ ./expressioneditor

Or if you are using the Qt4.6+ SDK then you can open expressioneditor.pro
in QtCreator, and then select "Run" (ctrl+r).

After the initial run a settings directory will have been created in
~/.expressioneditor/ to complete installation copy across the files in
the source tree's common/ directory into ~/.expressioneditor/common/

[2.3] WINDOWS

Since there is currently no Windows installer for Expression Editor you
will need to compile it as in Linux, there are several methods for this
but I recommend you fetch the Qt4.6+ SDK and open expressioneditor.pro
in QtCreator, and then select "Run" (ctrl+r).

After the initial run a settings directory will have been created in
C:/Documents and Settings/Username/expressioneditor to complete
installation copy across the files in the source tree's common/ directory
to the common/ directory in the settings directory.

[2.4] MAC OSX

Expression Editor will also compile and run on OSX, since again there is
no binary to distribute you will need to compile it.  As with the other
platforms you can do this with the Qt4.6+ SDK by opening
expressioneditor.pro and then selecting "Run" (ctrl+r).

After the initial run a settings directory will have been created in
$HOME/.expressioneditor/ to complete installation copy across the files in
the source tree's common/ directory into ~/.expressioneditor/common/
