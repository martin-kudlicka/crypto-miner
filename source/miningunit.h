#ifndef MININGUNIT_H
#define MININGUNIT_H

#include <QtCore/QSharedPointer>
#include "miningunitoptions.h"

class MiningUnit
{
  public:
    MiningUnit(const MUuidPtr &id);

    const MiningUnitOptions &options() const;

  private:
    MiningUnitOptions _options;
};

using MiningUnitSPtr = QSharedPointer<MiningUnit>;

#endif