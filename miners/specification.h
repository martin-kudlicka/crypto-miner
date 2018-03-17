#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <QtCore/QList>

enum class Company
{
  Any,
  Amd,
  Nvidia
};

enum class Hardware
{
  Cpu,
  Gpu
};

struct HwComponent
{
  Company  company;
  Hardware hardware;

  HwComponent(Company company, Hardware hardware) : company(company), hardware(hardware)
  {
  }
  bool operator==(const HwComponent &other) const
  {
    return other.company == company && other.hardware == hardware;
  }
};

static uint qHash(const HwComponent &key, uint seed = 0)
{
  return qHash(static_cast<uchar>(key.company), seed) ^ qHash(static_cast<uchar>(key.hardware), seed);
}

using HwComponentList = QList<HwComponent>;

#endif