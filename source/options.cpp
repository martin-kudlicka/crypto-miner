#include "options.h"

Q_DECL_CONSTEXPR QString Options::Property::Console_OutputLinesInMemory = "console/outputLinesInMemory";

Q_DECL_CONSTEXPR QString Options::Property::Startup_MineOnStartup = "startup/mineOnStartup";

MLazySingleton<Options> gOptions;

Options::Options()
{
  beginGroup("options");

  addProperty(Property::Console_OutputLinesInMemory, 64);
}

qintptr Options::consoleOutputLinesInMemory() const
{
  return value(Property::Console_OutputLinesInMemory).toInt();
}

bool Options::mineOnStartup() const
{
  return value(Property::Startup_MineOnStartup).toBool();
}