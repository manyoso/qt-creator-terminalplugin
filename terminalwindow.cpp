/*
 * Copyright (C) 2012 Adam Treat. All rights reserved.
 */

#include "terminalwindow.h"

#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/icontext.h>
#include <coreplugin/ifile.h>
#include <extensionsystem/pluginmanager.h>
#include <texteditor/fontsettings.h>
#include <texteditor/texteditorsettings.h>
#include <utils/environment.h>

#include <qtermwidget.h>
#include <QtGui/QIcon>

namespace Terminal {
namespace Internal {

class TerminalContainer : public QWidget
{
public:
    TerminalContainer(QWidget *parent);

    QTermWidget *termWidget() const { return m_termWidget; }

private:
    QVBoxLayout *m_layout;
    QTermWidget *m_termWidget;
};

TerminalContainer::TerminalContainer(QWidget *parent)
{
    m_termWidget = new QTermWidget(0, parent);
    m_termWidget->setWindowTitle(tr("Terminal"));
    m_termWidget->setWindowIcon(QIcon());
    m_termWidget->setScrollBarPosition(QTermWidget::ScrollBarRight);
#if defined(Q_OS_LINUX)
    m_termWidget->setColorScheme("Linux");
    m_termWidget->setKeyBindings("linux");
#elif defined(Q_OS_MACX)
    m_termWidget->setColorScheme("WhiteOnBlack");
    m_termWidget->setKeyBindings("macbook");
#else
    m_termWidget->setColorScheme("BlackOnLightYellow");
    m_termWidget->setKeyBindings("default");
#endif
    QFont font = TextEditor::TextEditorSettings::instance()->fontSettings().font();
    m_termWidget->setTerminalFont(font);
    m_termWidget->setTerminalOpacity(1.0);
    setFocusProxy(m_termWidget);

    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_termWidget);
    setLayout(m_layout);
}

TerminalWindow::TerminalWindow(QObject *parent)
   : IOutputPane(parent)
   , m_terminalContainer(0)
{
    Core::Context context("Terminal.Window");
}

QWidget *TerminalWindow::outputWidget(QWidget *parent)
{
    if (!m_terminalContainer)
        m_terminalContainer = new TerminalContainer(parent);
    return m_terminalContainer;
}

QList<QWidget *> TerminalWindow::toolBarWidgets() const
{
    return QList<QWidget *>();
}

QString TerminalWindow::displayName() const
{
    return tr("Terminal");
}

int TerminalWindow::priorityInStatusBar() const
{
    return 50;
}

void TerminalWindow::clearContents()
{
    if (!m_terminalContainer || !m_terminalContainer->termWidget())
        return;
    QString cmd = "clear\n";
    m_terminalContainer->termWidget()->sendText(cmd);
}

void TerminalWindow::visibilityChanged(bool visible)
{
    static bool initialized = false;
    if (!m_terminalContainer || !m_terminalContainer->termWidget() || initialized || !visible)
        return;

    m_terminalContainer->termWidget()->setWorkingDirectory(QDir::homePath());
    if (Core::IEditor *editor = Core::EditorManager::instance()->currentEditor()) {
        const QDir dir = QFileInfo(editor->file()->fileName()).absoluteDir();
        if (dir.exists())
            m_terminalContainer->termWidget()->setWorkingDirectory(dir.canonicalPath());
    }

    Utils::Environment env = Utils::Environment::systemEnvironment();
    env.set("QTCREATOR_PID", QString("%1").arg(getpid()).toLatin1());
    m_terminalContainer->termWidget()->setEnvironment(env.toStringList());
    m_terminalContainer->termWidget()->startShellProgram();
    initialized = true;
}

void TerminalWindow::setFocus()
{
    if (!m_terminalContainer || !m_terminalContainer->termWidget())
        return;
    m_terminalContainer->setFocus(Qt::OtherFocusReason);
}

bool TerminalWindow::hasFocus() const
{
    if (!m_terminalContainer || !m_terminalContainer->termWidget())
        return false;
    return m_terminalContainer->hasFocus();
}

bool TerminalWindow::canFocus() const
{
    return true;
}

bool TerminalWindow::canNavigate() const
{
    return false;
}

bool TerminalWindow::canNext() const
{
    return false;
}

bool TerminalWindow::canPrevious() const
{
    return false;
}

void TerminalWindow::goToNext()
{
    // no-op
}

void TerminalWindow::goToPrev()
{
    // no-op
}

} // namespace Internal
} // namespace Terminal
