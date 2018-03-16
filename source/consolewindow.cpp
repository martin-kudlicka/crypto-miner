#include "consolewindow.h"

ConsoleWindow::ConsoleWindow(const QString &text) : QDialog(QApplication::activeWindow())
{
  _ui.setupUi(this);

  _ui.minerText->setPlainText(text);
  _ui.minerText->moveCursor(QTextCursor::End);
}

void ConsoleWindow::on_minerWorker_outputLine(const QString &line) const
{
  _ui.minerText->appendPlainText(line);
}