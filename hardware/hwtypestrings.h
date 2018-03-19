#ifndef HWTYPESTRINGS_H
#define HWTYPESTRINGS_H

#include <MkCore/MStringizer>
#include "hardware.h"

class HardwareStrings : public MStringizer<Hardware::Type>
{
  public:
             HardwareStrings();
    virtual ~HardwareStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif