#include "miningunitoptions.h"

Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Pool_Address  = "pool/address";
Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Pool_Password = "pool/password";
Q_DECL_CONSTEXPR QString MiningUnitOptions::Property::Pool_Wallet   = "pool/wallet";

MiningUnitOptions::MiningUnitOptions(const MUuidPtr &id) : _id(id)
{
}