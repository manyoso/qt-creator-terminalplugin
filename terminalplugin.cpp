/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#include "terminalplugin.h"
#include "terminalwindow.h"

#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icore.h>
#include <coreplugin/imode.h>
#include <coreplugin/modemanager.h>
#include <coreplugin/id.h>
#include <extensionsystem/pluginmanager.h>

#include <QtCore/QDebug>
#include <QtCore/QtPlugin>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QMessageBox>
#include <QtGui/QPushButton>

namespace Terminal {
namespace Internal {


/*! Constructs the Terminal plugin. Normally plugins don't do anything in
    their constructor except for initializing their member variables. The
    actual work is done later, in the initialize() and extensionsInitialized()
    methods.
*/
TerminalPlugin::TerminalPlugin()
    : m_window(0)
{
}

/*! Plugins are responsible for deleting objects they created on the heap, and
    to unregister objects from the plugin manager that they registered there.
*/
TerminalPlugin::~TerminalPlugin()
{
    ExtensionSystem::PluginManager::instance()->removeObject(m_window);
    delete m_window;
    m_window = 0;
}

/*! Initializes the plugin. Returns true on success.
    Plugins want to register objects with the plugin manager here.

    \a errorMessage can be used to pass an error message to the plugin system,
       if there was any.
*/
bool TerminalPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    m_window = new TerminalWindow(this);
    ExtensionSystem::PluginManager::instance()->addObject(m_window);
    return true;
}

/*! Notification that all extensions that this plugin depends on have been
    initialized. The dependencies are defined in the plugins .pluginspec file.

    Normally this method is used for things that rely on other plugins to have
    added objects to the plugin manager, that implement interfaces that we're
    interested in. These objects can now be requested through the
    PluginManagerInterface.

    The TerminalPlugin doesn't need things from other plugins, so it does
    nothing here.
*/
void TerminalPlugin::extensionsInitialized()
{
}

} // namespace Internal
} // namespace Terminal

Q_EXPORT_PLUGIN(Terminal::Internal::TerminalPlugin)
