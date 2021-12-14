#include "BankAccount.h"

BankAccount::BankAccount(int id, int client_id, unsigned int cash, bool status)
	: id(id), client_id(client_id), cash(cash), status(status)
{
}

int BankAccount::getClientId() const
{
	return client_id;
}

int BankAccount::getId() const
{
	return id;
}

unsigned int BankAccount::getCash() const
{
	return cash;
}

bool BankAccount::getStatus() const
{
	return status;
}

int BankAccount::compareId(BankAccount* const& src1, BankAccount* const& src2)
{
	return src1->id - src2->id;
}

int BankAccount::compareClientId(BankAccount* const& src1, BankAccount* const& src2)
{
	return src1->client_id - src2->client_id;
}

int BankAccount::compareCash(BankAccount* const& src1, BankAccount* const& src2)
{
	return static_cast<int>(src1->cash) - src2->cash;
}

std::ostream& operator<<(std::ostream & out, const BankAccount & src)
{
	out << src.id << " " << src.client_id << " " << src.cash << " " << src.status;
	return out;
}
