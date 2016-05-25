/*
 * Copyright (C) 2012 Adam Treat. All rights reserved.
 */

#ifndef TERMINALPLUGIN_H
#define TERMINALPLUGIN_H

#include "terminalwindow.h"

#include <extensionsystem/iplugin.h>

namespace Terminal {
namespace Internal {

class TerminalWindow;

class TerminalPlugin
  : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "TerminalPlugin.json")

public:
    TerminalPlugin();
    ~TerminalPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();

private:
    TerminalWindow *m_window;
};

} // namespace Internal
} // namespace Terminal

#endif // TERMINALPLUGIN_H
