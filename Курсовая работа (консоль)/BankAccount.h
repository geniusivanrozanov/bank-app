#pragma once
#include <iostream>

class BankAccount
{
private:
	const int id;
	const int client_id;
	unsigned int cash;
	bool status;
public:
	BankAccount(int, int, unsigned int, bool);

	int getClientId() const;
	int getId() const;
	unsigned int getCash() const;
	bool getStatus() const;

	static int compareId(BankAccount* const& src1, BankAccount* const& src2);
	static int compareClientId(BankAccount* const& src1, BankAccount* const& src2);
	static int compareCash(BankAccount* const& src1, BankAccount* const& src2);

	friend std::ostream& operator<<(std::ostream&, const BankAccount&);
};

