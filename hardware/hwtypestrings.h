#ifndef HWTYPESTRINGS_H
#define HWTYPESTRINGS_H

#include "hardware_global.h"
#include <MkCore/MStringizer>
#include "hwcomponent.h"

class HARDWARE_EXPORT HwTypeStrings : public MStringizer<HwComponent::Type>
{
  public:
             HwTypeStrings();
    virtual ~HwTypeStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif