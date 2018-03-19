#ifndef HWCOMPANYSTRINGS_H
#define HWCOMPANYSTRINGS_H

#include <MkCore/MStringizer>
#include "hardware.h"

class CompanyStrings : public MStringizer<Hardware::Company>
{
  public:
             CompanyStrings();
    virtual ~CompanyStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif