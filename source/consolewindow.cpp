#include "consolewindow.h"

ConsoleWindow::ConsoleWindow(const QString &text)
{
  _ui.setupUi(this);

  _ui.minerText->setPlainText(text);
}