#pragma once
#include "Account.h"
class Admin : public Account
{
public:
    Admin() : Account(ADMIN, Identifier<Account>::getFreeId()) {}
    Admin(const Admin& src) : Account(src) {}
    Admin(const Account& src) : Account(src) {}
    void menu() override;

    void accountsMenu();
    void showAllAccounts();
    void sortAccountsMenu();
    void searchAccountsMenu();
    void filterMenu();
    void additionMenu();
    void deletionMenu();
    void modificationMenu();
    void blockAccountMenu();
    void acceptAccountMenu();
    void saveAccountsChanges();

    void bankAccountsMenu();
    void showBankAccounts();
    void showDepLoans();
    void sortBankAccountsMenu();
};

