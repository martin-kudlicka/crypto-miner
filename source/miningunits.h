#ifndef MININGUNITS_H
#define MININGUNITS_H

#include <QtCore/QSettings>
#include "miningunit.h"

class MiningUnits
{
  public:
    struct Property
    {
      static Q_DECL_CONSTEXPR QString Group;
    };

    MiningUnits(MinerPlugins *minerPlugins);

          quintptr        count  ()                   const;
    const MiningUnitSPtr &get    (const MUuidPtr &id);
          MUuidPtr        id     (quintptr index)     const;
          quintptr        index  (const MUuidPtr &id) const;
          bool            isEmpty()                   const;

  private:
    MinerPlugins                   *_minerPlugins;
    QHash<MUuidPtr, MiningUnitSPtr> _miningUnits;
    QSettings                       _settings;
};

#endif