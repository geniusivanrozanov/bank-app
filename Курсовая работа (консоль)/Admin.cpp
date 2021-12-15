#include "Admin.h"

Admin::Admin(int id, Status status, const String& login, const String& password)
	: Account(id, status, login, password)
{
}
