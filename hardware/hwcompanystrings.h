#ifndef HWCOMPANYSTRINGS_H
#define HWCOMPANYSTRINGS_H

#include <MkCore/MStringizer>
#include "hwcomponent.h"

class HwCompanyStrings : public MStringizer<HwComponent::Company>
{
  public:
             HwCompanyStrings();
    virtual ~HwCompanyStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif