#ifndef MININGUNITS_H
#define MININGUNITS_H

#include <QtCore/QSettings>
#include <MkCore/MUuidPtr>

class MiningUnits
{
  public:
    struct Property
    {
      static Q_DECL_CONSTEXPR QString Group;
    };

    MiningUnits();

    quintptr count  ()               const;
    MUuidPtr id     (quintptr index) const;
    bool     isEmpty()               const;

  private:
    QSettings _settings;
};

#endif