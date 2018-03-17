#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <QtCore/QSet>

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
};

using HwComponentList = QList<HwComponent>;

#endif