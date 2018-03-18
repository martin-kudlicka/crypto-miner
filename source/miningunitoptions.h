#ifndef MININGUNITOPTIONS_H
#define MININGUNITOPTIONS_H

#include <MkCore/MSettings>
#include <MkCore/MUuidPtr>
#include "../common/mineroptions.h"

class MiningUnitOptions : public MSettings
{
  public:
    struct Property
    {
      static Q_DECL_CONSTEXPR QString Pool_Address;
      static Q_DECL_CONSTEXPR QString Pool_Password;
      static Q_DECL_CONSTEXPR QString Pool_Username;
      static Q_DECL_CONSTEXPR QString Statistics_AcceptedResults;
      static Q_DECL_CONSTEXPR QString Statistics_MiningTime;
    };

             MiningUnitOptions(const MUuidPtr &id);
    virtual ~MiningUnitOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

          quintptr      acceptedResults   () const;
    const MUuidPtr     &id                () const;
          MinerOptions &miner             ();
    const MinerOptions &miner             () const;
          quintptr      miningTime        () const;
          QString       poolAddress       () const;
          QString       poolPassword      () const;
          QString       poolUsername      () const;
          void          setAcceptedResults(quintptr count);
          void          setMiningTime     (quintptr seconds);

  private:
    MinerOptions _minerOptions;
    MUuidPtr     _id;
};

#endif