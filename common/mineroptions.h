#ifndef MINEROPTIONS_H
#define MINEROPTIONS_H

#include <MkCore/MSettings>

class MUuidPtr;

class MinerOptions : public MSettings
{
  public:
    struct Property
    {
      static Q_DECL_CONSTEXPR QString Name;
      static Q_DECL_CONSTEXPR QString Parameters_Coin;
      static Q_DECL_CONSTEXPR QString Parameters_HwComponent;
    };

             MinerOptions(const MUuidPtr &id);
    virtual ~MinerOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    QString name   () const;
    void    setName(const QString &name);
};

#endif