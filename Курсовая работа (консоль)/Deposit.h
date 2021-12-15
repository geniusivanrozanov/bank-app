#pragma once
#include "BankAccount.h"
#include "Date.h"
#include <iostream>

class DepLoan : public BankAccount
{
private:
	Date date_of_end;
	int deposit_or_loan;
public:
	DepLoan(int);
	virtual int type() const override;
	virtual void print(std::ostream&) const override;
	virtual void read(std::istream&) override;
};

