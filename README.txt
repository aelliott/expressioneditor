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

Expression Editor requires Qt4.6.0+, a C++ compiler and CMake to build.
However there are also several other optional dependencies which will be
included by default if they are found on the system.  These are:

 - POSIX regular expressions via regex.h
 - PCRE (Perl-Compatible Regular Expressions)
 - ICU (International Components for Unicode)

Each of these add their respective regular expression engines as options
within Expression Editor.

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

$ cd ~/src/expressioneditor # or if you put it elsewhere use that path
$ mkdir build && cd build/
$ cmake ../
$ make
$ sudo make install # or su -c

After the initial run a settings directory will have been created in
~/.expressioneditor/ to complete installation copy across the files in
the source tree's common/ directory into ~/.expressioneditor/common/

[2.3] WINDOWS

Since there is currently no Windows installer for Expression Editor you
will need to compile it as in Linux, you should be able to use cmake-gui
for this, but I have no further guidance at this time.

After the initial run a settings directory will have been created in
C:/Documents and Settings/Username/expressioneditor to complete
installation copy across the files in the source tree's common/ directory
to the common/ directory in the settings directory.

[2.4] MAC OSX

Expression Editor will also compile and run on OSX, since again there is
no binary to distribute you will need to compile it.  The process for this
is basically the same as for Linux:

$ cd ~/src/expressioneditor # or if you put it elsewhere use that path
$ mkdir build && cd build/
$ cmake ../
$ make
$ ./expressioneditor

You may encounter an error regarding Qt being built for a different
architecture to the one which you are targetting expressioneditor to.  To
resolve this add -DCMAKE_OSX_ARCHITECTURES=i386 to the cmake command.

After the initial run a settings directory will have been created in
~/.expressioneditor/ to complete installation copy across the files in
the source tree's common/ directory into ~/.expressioneditor/common/
