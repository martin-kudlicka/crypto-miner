#include "hwtypestrings.h"

HwTypeStrings::HwTypeStrings()
{
  insert(Hardware::Type::Cpu, "CPU");
  insert(Hardware::Type::Gpu, "GPU");
}