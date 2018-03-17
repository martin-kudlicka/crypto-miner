#include "hardwarestrings.h"

HardwareStrings::HardwareStrings()
{
  insert(Hardware::Cpu, "CPU");
  insert(Hardware::Gpu, "GPU");
}