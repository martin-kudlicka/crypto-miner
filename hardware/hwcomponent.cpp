#include "hwcomponent.h"

#include "hwcompanystrings.h"
#include "hwtypestrings.h"

HwComponent::HwComponent(Company company, Type type) : _company(company), _type(type)
{
}

HwComponent::Company HwComponent::company() const
{
  return _company;
}

QString HwComponent::toString() const
{
  QString value;

  static HwCompanyStrings companyStrings;
  static HwTypeStrings hardwareStrings;

  if (_company != HwComponent::Company::Any)
  {
    value.append(companyStrings.toString(_company));
    value.append(' ');
  }
  value.append(hardwareStrings.toString(_type));

  return value;
}

HwComponent::Type HwComponent::type() const
{
  return _type;
}

bool HwComponent::operator==(const HwComponent &other) const
{
  return other._company == _company && other._type == _type;
}

HwComponent HwComponent::fromString(const QString &text)
{
  auto partsStr = text.split(' ');

  auto company = Company::Any;
  if (partsStr.count() > 1)
  {
    static HwCompanyStrings companyStrings;

    company = companyStrings.fromString(partsStr.takeFirst());
  }

  static HwTypeStrings hardwareStrings;

  auto type = hardwareStrings.fromString(partsStr.takeFirst());

  return HwComponent(company, type);

}

uint qHash(const HwComponent &key, uint seed /* 0 */)
{
  return qHash(static_cast<uchar>(key.company()), seed) ^ qHash(static_cast<uchar>(key.type()), seed);
}