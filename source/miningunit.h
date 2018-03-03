#ifndef MININGUNIT_H
#define MININGUNIT_H

#include <QtCore/QSharedPointer>
#include "miningunitoptions.h"
#include "../miners/common/minerworkerinterface.h"

class MinerInterface;
class MinerPlugins;

class MiningUnit
{
  public:
    MiningUnit(const MUuidPtr &id, MinerPlugins *minerPlugins);

    const MiningUnitOptions &options() const;
          void               start  ();
          void               stop   ();

  private:
    const MinerInterface          *_minerPlugin;
          MiningUnitOptions        _options;
          MinerWorkerInterfaceSPtr _worker;
};

using MiningUnitSPtr = QSharedPointer<MiningUnit>;

#endif