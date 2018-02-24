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
      static Q_DECL_CONSTEXPR QString Pool_Wallet;
    };

             MiningUnitOptions(const MUuidPtr &id);
    virtual ~MiningUnitOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    void setMiner(const QString &name);

  private:
    MUuidPtr _id;
};

#endif