#ifndef MININGUNITS_H
#define MININGUNITS_H

#include <QtCore/QSettings>
#include "miningunit.h"

class MiningUnits
{
  public:
     MiningUnits(MinerPlugins *minerPlugins, MiningModel *miningModel);
    ~MiningUnits();

    quintptr       count      ()                   const;
    MiningUnitSPtr get        (const MUuidPtr &id);
    MUuidPtr       id         (quintptr index)     const;
    quintptr       index      (const MUuidPtr &id) const;
    bool           isEmpty    ()                   const;
    void           removeIndex(quintptr index);

  private:
    MinerPlugins                   *_minerPlugins;
    MiningModel                    *_miningModel;
    QSettings                       _settings;
    QHash<MUuidPtr, MiningUnitSPtr> _miningUnits;
};

#endif