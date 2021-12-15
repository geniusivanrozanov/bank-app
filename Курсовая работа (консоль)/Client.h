#pragma once
#include "Account.h"
class Client : public Account
{
public:
	Client(int id, Status status, const String& login, const String& password);
};

