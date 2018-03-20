#ifndef HWCOMPONENT_H
#define HWCOMPONENT_H

#include "hardware_global.h"
#include <QtCore/QList>

class HARDWARE_EXPORT HwComponent
{
  public:
    enum class Company
    {
      Any,
      Amd,
      Nvidia
    };
    enum class Type
    {
      Cpu,
      Gpu
    };

    HwComponent(Company company, Type type);

    Company company () const;
    QString toString() const;
    Type    type    () const;

    bool operator==(const HwComponent &other) const;

  private:
    Company _company;
    Type    _type;
};

using HwComponentList = QList<HwComponent>;

uint HARDWARE_EXPORT qHash(const HwComponent &key, uint seed = 0);

#endif