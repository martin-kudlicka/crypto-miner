#include "hwcomponentstrings.h"

#include "companystrings.h"
#include "hardwarestrings.h"

namespace HwComponentStrings
{

QString toString(const Hardware::HwComponent &hwComponent)
{
  QString value;

  static CompanyStrings companyStrings;
  static HardwareStrings hardwareStrings;

  if (hwComponent.company != Hardware::Company::Any)
  {
    value.append(companyStrings.toString(hwComponent.company));
    value.append(' ');
  }
  value.append(hardwareStrings.toString(hwComponent.hardware));

  return value;
}

}