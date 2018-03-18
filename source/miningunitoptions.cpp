#include "miningunitoptions.h"

Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Pool_Address  = "pool/address";
Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Pool_Password = "pool/password";
Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Pool_Username = "pool/username";

Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Statistics_AcceptedResults = "statistics/acceptedResults";
Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Statistics_MiningTime      = "statistics/miningTime";

MiningUnitOptions::MiningUnitOptions(const MUuidPtr &id) : _id(id), _minerOptions(id)
{
  beginGroup("miningUnits");
  beginGroup(id.toString());
}

quintptr MiningUnitOptions::acceptedResults() const
{
  return value(Property::Statistics_AcceptedResults).toUInt();
}

const MUuidPtr &MiningUnitOptions::id() const
{
  return _id;
}

MinerOptions &MiningUnitOptions::miner()
{
  return _minerOptions;
}

const MinerOptions &MiningUnitOptions::miner() const
{
  return _minerOptions;
}

quintptr MiningUnitOptions::miningTime() const
{
  return value(Property::Statistics_MiningTime).toUInt();
}

QString MiningUnitOptions::poolAddress() const
{
  return value(Property::Pool_Address).toString();
}

QString MiningUnitOptions::poolPassword() const
{
  return value(Property::Pool_Password).toString();
}

QString MiningUnitOptions::poolUsername() const
{
  return value(Property::Pool_Username).toString();
}

void MiningUnitOptions::setAcceptedResults(quintptr count)
{
  setValue(Property::Statistics_AcceptedResults, count);
}

void MiningUnitOptions::setMiningTime(quintptr seconds)
{
  setValue(Property::Statistics_MiningTime, seconds);
}