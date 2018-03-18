#include "hwcomponentstrings.h"

#include "companystrings.h"
#include "hardwarestrings.h"

namespace HwComponentStrings
{

QString toString(const HwComponent &hwComponent)
{
  QString value;

  static CompanyStrings companyStrings;
  static HardwareStrings hardwareStrings;

  if (hwComponent.company != Company::Any)
  {
    value.append(companyStrings.toString(hwComponent.company));
    value.append(' ');
  }
  value.append(hardwareStrings.toString(hwComponent.hardware));

  return value;
}

}