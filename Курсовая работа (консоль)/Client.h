#pragma once
#include "Account.h"
#include "Array.h"
#include "BankAccount.h"

class Client : public Account
{
private:
    Vector<BankAccount*> my_bank_accounts;
public:
    Client(Status st = CLIENT) : Account(st, Identifier<Account>::getFreeId()) {}
    Client(const Client& src) : Account(src) {}
    Client(const Account& src) : Account(src) {}

    void menu() override;
    void bankAccountsMenu();
    void showBankAccounts();
    void addBankAccountMenu();
    void operationsMenu();
    void depLoansMenu();
    void showDepLoans();
    void addDepLoanMenu();
};

