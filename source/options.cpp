#include "options.h"

Q_DECL_CONSTEXPR QString Options::Property::Startup_MineOnStart = "startup/mineOnStart";

MLazySingleton<Options> gOptions;

Options::Options()
{
  beginGroup("options");
}

bool Options::mineOnStart() const
{
  return value(Property::Startup_MineOnStart).toBool();
}