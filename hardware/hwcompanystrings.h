#ifndef HWCOMPANYSTRINGS_H
#define HWCOMPANYSTRINGS_H

#include <MkCore/MStringizer>
#include "hardware.h"

class HwCompanyStrings : public MStringizer<Hardware::Company>
{
  public:
             HwCompanyStrings();
    virtual ~HwCompanyStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif