#ifndef MINERWORKERINTERFACE_H
#define MINERWORKERINTERFACE_H

#include <QtCore/QObject>

class MinerWorkerInterface : public QObject
{
  Q_OBJECT
};

using MinerWorkerInterfaceSPtr = QSharedPointer<MinerWorkerInterface>;

#endif