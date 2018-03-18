#ifndef HWCOMPONENTSTRINGS_H
#define HWCOMPONENTSTRINGS_H

#include <QtCore/QString>

struct HwComponent;

namespace HwComponentStrings
{
  QString toString(const HwComponent &hwComponent);
};

#endif