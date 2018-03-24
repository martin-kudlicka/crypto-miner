#ifndef HWCOMPANYSTRINGS_H
#define HWCOMPANYSTRINGS_H

#include "hardware_global.h"
#include <MkCore/MStringizer>
#include "hwcomponent.h"

class HARDWARE_EXPORT HwCompanyStrings : public MStringizer<HwComponent::Company>
{
  public:
             HwCompanyStrings();
    virtual ~HwCompanyStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif