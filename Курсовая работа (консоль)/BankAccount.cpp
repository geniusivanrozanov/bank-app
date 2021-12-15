#include "BankAccount.h"

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

void BankAccount::setClientId(int id)
{
	client_id = id;
}

void BankAccount::setId(int id)
{
	this->id = id;
}

void BankAccount::setCash(unsigned int cash)
{
	this->cash = cash;
}

void BankAccount::setStatus(bool st)
{
	status = st;
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

int BankAccount::type() const
{
	return 0;
}

void BankAccount::print(std::ostream& out) const
{
	out << type() << " " << id << " " << client_id << " " << cash << " " << status;
}

void BankAccount::read(std::istream& in)
{
	in >> id >> client_id >> cash >> status;
}

std::ostream& operator<<(std::ostream & out, const BankAccount & src)
{
	src.print(out);
	return out;
}

std::istream& operator>>(std::istream& in, BankAccount& src)
{
	src.read(in);
	return in;
}
