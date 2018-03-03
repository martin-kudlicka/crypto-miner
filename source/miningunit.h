#ifndef MININGUNIT_H
#define MININGUNIT_H

#include <QtCore/QSharedPointer>
#include "miningunitoptions.h"
#include "../miners/common/minerworkerinterface.h"

class MinerInterface;
class MinerPlugins;

class MiningUnit : public QObject
{
  Q_OBJECT

  public:
    struct Statistics
    {
      quintptr results;

      Statistics();
    };

             MiningUnit(const MUuidPtr &id, MinerPlugins *minerPlugins);
    virtual ~MiningUnit() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    const MiningUnitOptions &options          () const;
    const Statistics        &sessionStatistics() const;
          void               start            ();
          void               stop             ();

  private:
    const MinerInterface          *_minerPlugin;
          MiningUnitOptions        _options;
          MinerWorkerInterfaceSPtr _worker;
          Statistics               _sessionStatistics;

  private Q_SLOTS:
    void on_worker_resultAccepted();
};

using MiningUnitSPtr = QSharedPointer<MiningUnit>;

#endif