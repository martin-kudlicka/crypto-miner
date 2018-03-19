#include "hardwarestrings.h"

HardwareStrings::HardwareStrings()
{
  insert(Hardware::Type::Cpu, "CPU");
  insert(Hardware::Type::Gpu, "GPU");
}