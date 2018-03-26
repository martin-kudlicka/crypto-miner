#include "consolewindow.h"

ConsoleWindow::ConsoleWindow(const QString &description, const QStringList &lines) : QDialog(QApplication::activeWindow())
{
  _ui.setupUi(this);

  setWindowTitle(tr("Console - ") + description);

  _ui.minerText->setPlainText(lines.join('\n'));
  _ui.minerText->moveCursor(QTextCursor::End);
}

void ConsoleWindow::on_minerWorker_outputLine(const QString &line) const
{
  _ui.minerText->appendPlainText(line);
}