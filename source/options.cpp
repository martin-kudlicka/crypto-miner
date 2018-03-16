#include "options.h"

Q_DECL_CONSTEXPR QString Options::Property::Startup_MineOnStartup = "startup/mineOnStartup";

MLazySingleton<Options> gOptions;

Options::Options()
{
  beginGroup("options");
}

bool Options::mineOnStartup() const
{
  return value(Property::Startup_MineOnStartup).toBool();
}