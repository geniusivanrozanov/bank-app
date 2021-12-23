#pragma once
#include "String.h"
#include "Menu.h"
#include "Account.h"
#include "DataBase.h"

class Form
{
protected:
	COORD pos;
	int width;
	int height;
	void printField(const String&, const String&);
public:
	Form(int width, int height) : width(width), height(height) 
	{
		pos = getCenterdCoords(width, height);
	}
	virtual void show() = 0;
	virtual Account* init() = 0;
};

class MainForm : public Form
{
public:
	MainForm() 
		: Form(20, 12)
	{}
	virtual void show() override;
	virtual Account* init() override;
};

class AuthForm : public Form
{
private:
	String button;
public:
	AuthForm(int width)
		: Form(width, 9)
	{
		int indent = width - 5;
		button = String(indent / 2, ' ') + "Войти" + String(indent / 2 + indent % 2, ' ');
	}
	virtual void show() override;
	virtual Account* init() override;
};

class RegForm : public Form
{
private:
	String button;
public:
	RegForm(int width)
		: Form(width, 21)
	{
		int indent = width - 18;
		button = String(indent / 2, ' ') + "Зарегистрироваться" + String(indent / 2 + indent % 2, ' ');
	}
	virtual void show() override;
	virtual Account* init() override;
};