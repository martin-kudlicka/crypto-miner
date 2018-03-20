#include "hwtypestrings.h"

HwTypeStrings::HwTypeStrings()
{
  insert(HwComponent::Type::Cpu, "CPU");
  insert(HwComponent::Type::Gpu, "GPU");
}