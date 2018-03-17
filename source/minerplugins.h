#ifndef MINERPLUGINS_H
#define MINERPLUGINS_H

#include <MkCore/MPluginContainer>
#include "../miners/minerinterface.h"

class MinerPlugins : public MPluginContainer<MinerInterface>
{
  public:
             MinerPlugins();
    virtual ~MinerPlugins() Q_DECL_EQ_DEFAULT;
};

#endif