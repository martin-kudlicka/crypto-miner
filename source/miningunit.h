#ifndef MININGUNIT_H
#define MININGUNIT_H

#include <QtCore/QSharedPointer>
#include "miningunitoptions.h"

class MinerInterface;
class MinerPlugins;

class MiningUnit
{
  public:
    MiningUnit(const MUuidPtr &id, MinerPlugins *minerPlugins);

    const MiningUnitOptions &options() const;

  private:
    const MinerInterface    *_minerPlugin;
          MiningUnitOptions  _options;
};

using MiningUnitSPtr = QSharedPointer<MiningUnit>;

#endif