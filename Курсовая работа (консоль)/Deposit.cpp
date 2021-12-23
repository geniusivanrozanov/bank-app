#include "Deposit.h"

DepLoan::DepLoan(bool type, Date date)
	: deposit_or_loan(type), date_of_end(date)
{
}

int DepLoan::type() const
{
	return deposit_or_loan ? 1 : -1;
}

void DepLoan::print(std::ostream& out) const
{
	BankAccount::print(out);
	out << " " << date_of_end;
}

void DepLoan::read(std::istream& in)
{
	BankAccount::read(in);
	in >> date_of_end;
}

Vector<String> DepLoan::toArray() const
{
	Vector<String> res(BankAccount::toArray());
	res.reserve(7);
	res.push(deposit_or_loan ? "Депозит" : "Займ");
	res.push(date_of_end.toString());
	if (!getStatus())
		res.at(2) = "Погашен";
	return res;
}
