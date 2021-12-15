#include "Deposit.h"

DepLoan::DepLoan(int type)
	: deposit_or_loan(type)
{
}

int DepLoan::type() const
{
	return deposit_or_loan;
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
