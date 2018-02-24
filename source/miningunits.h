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

    MiningUnits();

          quintptr        count  ()               const;
    const MiningUnitSPtr &get    (const MUuidPtr &id);
          MUuidPtr        id     (quintptr index) const;
          bool            isEmpty()               const;

  private:
    QHash<MUuidPtr, MiningUnitSPtr> _miningUnits;
    QSettings                       _settings;
};

#endif