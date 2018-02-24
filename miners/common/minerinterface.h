#ifndef MINERINTERFACE_H
#define MINERINTERFACE_H

#include <QtCore/QObject>

#define IID_MINERINTERFACE "cz.martink.CryptoMiner.MinerInterface"

class MinerInterface : public QObject
{
  Q_OBJECT

  public:
    virtual QString name() const = 0;

  protected:
    virtual ~MinerInterface() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;
};

Q_DECLARE_INTERFACE(MinerInterface, IID_MINERINTERFACE);

#endif