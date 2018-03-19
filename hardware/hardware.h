#ifndef HARDWARE_H
#define HARDWARE_H

#include "hardware_global.h"
#include <QtCore/QList>

class HARDWARE_EXPORT Hardware
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

    struct Component
    {
      Company company;
      Type    hardware;

      Component(Company company, Type hardware) : company(company), hardware(hardware)
      {
      }
      bool operator==(const Component &other) const
      {
        return other.company == company && other.hardware == hardware;
      }
    };

    using HwComponentList = QList<Component>;

    Hardware();
};

static uint qHash(const Hardware::Component &key, uint seed = 0)
{
  return qHash(static_cast<uchar>(key.company), seed) ^ qHash(static_cast<uchar>(key.hardware), seed);
}

#endif