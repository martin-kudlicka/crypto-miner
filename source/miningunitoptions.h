#ifndef MININGUNITOPTIONS_H
#define MININGUNITOPTIONS_H

#include <MkCore/MSettings>
#include <MkCore/MUuidPtr>

class MiningUnitOptions : public MSettings
{
  public:
    struct Property
    {
      static Q_DECL_CONSTEXPR QString Miner;
      static Q_DECL_CONSTEXPR QString Pool_Address;
      static Q_DECL_CONSTEXPR QString Pool_Password;
      static Q_DECL_CONSTEXPR QString Pool_Username;
      static Q_DECL_CONSTEXPR QString Statistics_AcceptedResults;
      static Q_DECL_CONSTEXPR QString Statistics_MiningTime;
    };

             MiningUnitOptions(const MUuidPtr &id);
    virtual ~MiningUnitOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

          quintptr  acceptedResults   () const;
    const MUuidPtr &id                () const;
          QString   miner             () const;
          quintptr  miningTime        () const;
          QString   poolAddress       () const;
          QString   poolPassword      () const;
          QString   poolUsername      () const;
          void      setAcceptedResults(quintptr count);
          void      setMiner          (const QString &name);
          void      setMiningTime     (quintptr seconds);

  private:
    MUuidPtr _id;
};

#endif