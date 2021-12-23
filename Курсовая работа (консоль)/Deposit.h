#pragma once
#include "BankAccount.h"
#include "Date.h"
#include <iostream>

class DepLoan : public BankAccount
{
private:
	Date date_of_end;
	bool deposit_or_loan;
public:
	DepLoan(bool, Date = Date());
	virtual int type() const override;
	virtual void print(std::ostream&) const override;
	virtual void read(std::istream&) override;
	virtual Vector<String> toArray() const override;
};

