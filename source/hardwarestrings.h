#ifndef HARDWARESTRINGS_H
#define HARDWARESTRINGS_H

#include <MkCore/MStringizer>
#include "../miners/specification.h"

class HardwareStrings : public MStringizer<Hardware>
{
  public:
             HardwareStrings();
    virtual ~HardwareStrings() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

#endif