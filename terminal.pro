TEMPLATE = lib
TARGET = Terminal

include(../../qtcreatorplugin.pri)
include(../../plugins/coreplugin/coreplugin.pri)
include(../../plugins/texteditor/texteditor.pri)

DEPENDPATH += . qtermwidget/lib
INCLUDEPATH += . qtermwidget/lib
DEFINES += HAVE_POSIX_OPENPT HAVE_SYS_TIME_H BUNDLE_COLORSCHEMES BUNDLE_KEYBOARDLAYOUTS

macx {
DEFINES += HAVE_UTMPX _UTMPX_COMPAT
}

HEADERS += terminalplugin.h \
           terminalwindow.h \
           qtermwidget/lib/BlockArray.h \
           qtermwidget/lib/Character.h \
           qtermwidget/lib/CharacterColor.h \
           qtermwidget/lib/ColorScheme.h \
           qtermwidget/lib/ColorTables.h \
           qtermwidget/lib/DefaultTranslatorText.h \
           qtermwidget/lib/Emulation.h \
           qtermwidget/lib/ExtendedDefaultTranslator.h \
           qtermwidget/lib/Filter.h \
           qtermwidget/lib/History.h \
           qtermwidget/lib/KeyboardTranslator.h \
           qtermwidget/lib/konsole_wcwidth.h \
           qtermwidget/lib/kprocess.h \
           qtermwidget/lib/kpty.h \
           qtermwidget/lib/kpty_p.h \
           qtermwidget/lib/kptydevice.h \
           qtermwidget/lib/kptyprocess.h \
           qtermwidget/lib/LineFont.h \
           qtermwidget/lib/Pty.h \
           qtermwidget/lib/qtermwidget.h \
           qtermwidget/lib/Screen.h \
           qtermwidget/lib/ScreenWindow.h \
           qtermwidget/lib/Session.h \
           qtermwidget/lib/ShellCommand.h \
           qtermwidget/lib/TerminalCharacterDecoder.h \
           qtermwidget/lib/TerminalDisplay.h \
           qtermwidget/lib/tools.h \
           qtermwidget/lib/Vt102Emulation.h

SOURCES += terminalplugin.cpp \
           terminalwindow.cpp \
           qtermwidget/lib/BlockArray.cpp \
           qtermwidget/lib/ColorScheme.cpp \
           qtermwidget/lib/Emulation.cpp \
           qtermwidget/lib/Filter.cpp \
           qtermwidget/lib/History.cpp \
           qtermwidget/lib/KeyboardTranslator.cpp \
           qtermwidget/lib/konsole_wcwidth.cpp \
           qtermwidget/lib/kprocess.cpp \
           qtermwidget/lib/kpty.cpp \
           qtermwidget/lib/kptydevice.cpp \
           qtermwidget/lib/kptyprocess.cpp \
           qtermwidget/lib/Pty.cpp \
           qtermwidget/lib/qtermwidget.cpp \
           qtermwidget/lib/Screen.cpp \
           qtermwidget/lib/ScreenWindow.cpp \
           qtermwidget/lib/Session.cpp \
           qtermwidget/lib/ShellCommand.cpp \
           qtermwidget/lib/TerminalCharacterDecoder.cpp \
           qtermwidget/lib/TerminalDisplay.cpp \
           qtermwidget/lib/tools.cpp \
           qtermwidget/lib/Vt102Emulation.cpp

RESOURCES += qtermwidget/lib/color-schemes/color-schemes.qrc \
             qtermwidget/lib/kb-layouts/kb-layouts.qrc
