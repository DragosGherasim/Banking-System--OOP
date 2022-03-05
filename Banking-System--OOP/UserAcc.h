#pragma once
#include "BankAcc.h"
#include "SilverBankAcc.h"
#include "GoldBankAcc.h"
#include "DiamondBankAcc.h"
#include <string>
#include <memory>
#include <iostream>
#include <vector>

/*
		--- Details about the UserAcc class ---

		== Members ==

	-> _name is used to give a name for UserAcc, _user and _pass to login process, to check if the UserAcc is registered in bank
	database, etc;

	-> _code : user code (eg. SBA73852) contains a head_code (SBA), which determines the type of bank account for the user (Silver Bank Account)
	, polymorphism, and with the tail_code (73852) is used for Transfer Money Process;

	-> _bank_acc is a shared_ptr to a BankAcc class that is an abstract class;

	-> _num_dep_us, _num_with_us are used to count the number of deposits and withdrawals, because each type of bank accounts has a limit of
	deposits and withdrawals;
*/

class UserAcc
{
private:
	std::string _name, _user, _pass;
	std::string _code;
	std::shared_ptr <BankAcc> _bank_acc; // COMPOSITION	
	unsigned int _num_dep_us, _num_with_us;

public:
	UserAcc(std::string = " ", std::string = " ", std::string = " ", std::string = " ", std::shared_ptr <BankAcc> = nullptr, unsigned int = 0, unsigned int = 0);
	void setUser(std::string user) { _user = user; }
	void setPass(std::string pass) { _pass = pass; }
	void setName(std::string name) { _name = name; }
	void setUsCode(std::string code) { _code = code; setBankAcc(); } // set the _code but also initialize _bank_acc;
	void setAccBal(double balance) { if (!_bank_acc) setBankAcc();  _bank_acc->setBal(balance); }
	void setNumUsDep(unsigned int val) { _num_dep_us = val; }
	void setNumUsWith(unsigned int val) { _num_with_us = val; }
	std::string getUser() const { return _user; }
	std::string getPass() const { return _pass; }
	std::string getName() const { return _name; }
	std::string getUsCode() const { return _code; }
	double getAccBal() const { return _bank_acc->getBal(); }
	unsigned int getMaxNumAccDep() const { return _bank_acc->getMaxNumDep(); }
	unsigned int getMaxNumAccWith() const { return _bank_acc->getMaxNumWith(); }
	unsigned int getNumUsDep() const { return _num_dep_us; }
	unsigned int getNumUsWith() const { return _num_with_us; }
	unsigned int getMaxAccAmountReceived() { return _bank_acc->getMaxAmountReceived(); }
	unsigned int getMaxBalUs() { return _bank_acc->getMaxBal(); }
	void setBankAcc();
	bool deposit(unsigned int);
	bool withdraw(unsigned int);
	bool transferAmount(unsigned int);
	bool posTransfer();
};

/* Default Constructor With Defaul Values */
UserAcc::UserAcc(std::string name, std::string user, std::string pass, std::string code, std::shared_ptr <BankAcc> bank_acc, unsigned int num_dep_us, unsigned int _num_with_us)
	: _name{ name }, _user{ user }, _pass{ pass }, _code{ code }, _bank_acc{ bank_acc }, _num_dep_us{ num_dep_us }, _num_with_us{ _num_with_us }
{

}

/* is used to initialize the _bank_acc of an UserAcc with the chosen type of bank account (Polymorphism) */
void UserAcc::setBankAcc()
{
	std::string head_code;
	for (std::size_t it{ 0 }; it < 3; ++it)
		head_code += _code[it];

	if (head_code == "SBA")
		_bank_acc = std::make_shared<SilverBankAcc>();
	else if (head_code == "GBA")
		_bank_acc = std::make_shared<GoldBankAcc>();
	else
		_bank_acc = std::make_shared<DiamondBankAcc>();
}

/* returns true if the UserAcc succesfully deposits the given amount, after the _bank_acc->deposit method checks if it is possible with
this amount to deposit it for UserAcc's bank account type, else returns false */
bool UserAcc::deposit(unsigned int amount)
{
	if (_bank_acc->deposit(amount))
	{
		++_num_dep_us;
		return true;
	}

	return false;
}

/* returns true if the UserAcc succesfully withdraws the given amount, after the _bank_acc->withdraw method checks if it is possible with
this amount to withdraw for UserAcc's bank account typ, else returns false */
bool UserAcc::withdraw(unsigned int amount)
{
	if (_bank_acc->withdraw(amount))
	{
		++_num_with_us;
		return true;
	}

	return false;
}
/* returns true if the UserAcc succesfully transfers the given amount, after the _bank_acc->transfer method checks if it is possible with
this amount to transfer for UserAcc's bank account typ, else returns false */
bool UserAcc::transferAmount(unsigned int amount)
{
	if (_bank_acc->transfer(amount))
		return true;
	return false;
}

/* returns true if the UserAcc's bank account has the acces to Transfer Process, else returns false */
bool UserAcc::posTransfer()
{
	if (_bank_acc->getPosTransf())
		return true;

	return false;
}
