#pragma once
#pragma once
#include "BankAcc.h"
#include <iostream>

/*
	*** DiamondBankAcc ***

-> max_balance : 50000 RON;
-> max_deposit : 10000 RON;
-> _max_withdrawal : 7000 RON;
-> tax_withdraw : 3% of the withdrawn amount;
-> tax_deposit : 3% of the deposit amount;
-> max_deposits : 2 ("per24h");
-> max_withdrawals : 1 ("per24h").

	-- Avantaje --
-> bonus_tax_depositt : 1% if the amount deposited is greater than or equal to 9500 RON;
-> tax_withdraw_reduce: 1% if the amount deposited is greater than or equal to 6700 RON;
-> the possibility to receive an amount less than or equal to 8500 RON from a user of our bank with a Gold or Diamond bank account;
-> possibility to send an amount less than or equal to 5000 RON to a user of our bank with a Silver, Gold or Diamond bank account.

*/

class DiamondBankAcc : public BankAcc
{
private:
	static constexpr unsigned int _max_balance = 50000;
	static constexpr unsigned int _max_deposit = 10000;
	static constexpr unsigned int _max_withdrawal = 7000;
	static constexpr double _tax_withdraw = 0.03;
	static constexpr double _tax_deposit = 0.03;
	static constexpr double _bonus_tax_depositt = 0.01;
	static constexpr double _tax_withdraw_reduce = 0.01;
	static constexpr unsigned int _max_amount_received = 8500;
	static constexpr unsigned int _max_transfer = 5000;
	static constexpr bool _pos_transfer = true;
	static constexpr unsigned int _max_deposits = 2;
	static constexpr unsigned int _max_withdrawals = 1;

public:
	virtual ~DiamondBankAcc() {}
	virtual bool deposit(unsigned int) override;
	virtual bool withdraw(unsigned int) override;
	virtual bool transfer(unsigned int) override;
	virtual unsigned int getMaxNumDep() override { return _max_deposits; }
	virtual unsigned int getMaxNumWith() override { return _max_withdrawals; }
	virtual unsigned int getMaxAmountReceived() override { return _max_amount_received; }
	virtual bool getPosTransf() override { return _pos_transfer; }
	virtual unsigned int getMaxBal() override { return _max_balance; }
};

bool DiamondBankAcc::deposit(unsigned int amount)
{
	if (amount > _max_deposit)
	{
		std::cout << "\n\tThe deposit amount allowed for your account must not be more than " << _max_deposit << " RON !";
		return false;
	}

	if (amount + _balance > _max_balance)
	{
		std::cout << "\n\tThe balance of your account should not exceed the amount of " << _max_balance << " RON !";
		return false;
	}

	if (amount >= 9500)
		_balance += (amount - amount * _bonus_tax_depositt);
	else
		_balance += (amount - amount * _tax_deposit);

	return true;
}

bool DiamondBankAcc::withdraw(unsigned int amount)
{
	if (amount > _max_withdrawals)
	{
		std::cout << "\n\tThe amount of withdrawal allowed for your account must not be more than " << _max_withdrawals << " RON !\n";
		return false;
	}

	if (_balance - amount < 0)
	{
		std::cout << "\n\tThe balance of your account should not be less than 0 RON !n";
		return false;
	}

	if (amount > 6700)
		_balance -= (amount + amount * _tax_withdraw_reduce);
	else
		_balance -= (amount + amount * _tax_withdraw);

	return true;

}

bool DiamondBankAcc::transfer(unsigned int amount)
{
	if (_balance > amount)
	{
		if (amount <= _max_transfer)
			return true;
		else
		{
			std::cout << "\n\tThe transfer amount is higher than the maximum accepted for your account ( " << _max_transfer << " RON ) !\n";
			return false;
		}
	}

	std::cout << "\n\tThe transfer amount is higher than your balance ( " << _balance << " RON ) !\n";
	return false;
}