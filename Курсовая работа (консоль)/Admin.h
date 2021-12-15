#pragma once
#include "Account.h"
class Admin : public Account
{
public:
	Admin(int id, Status status, const String& login, const String& password);
};

