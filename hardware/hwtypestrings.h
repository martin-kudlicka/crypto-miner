#ifndef HWTYPESTRINGS_H
#define HWTYPESTRINGS_H

#include <MkCore/MStringizer>
#include "hardware.h"

class HwTypeStrings : public MStringizer<Hardware::Type>
{
  public:
             HwTypeStrings();
    virtual ~HwTypeStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif