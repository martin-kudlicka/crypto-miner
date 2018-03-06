#include "consolewindow.h"

ConsoleWindow::ConsoleWindow(const QString &text)
{
  _ui.setupUi(this);

  _ui.minerText->setPlainText(text);
}

void ConsoleWindow::on_minerWorker_outputLine(const QString &line) const
{
  _ui.minerText->appendPlainText(line);
}