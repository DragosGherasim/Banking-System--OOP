#pragma once

class BankAcc
{
protected:
	double _balance;

public:
	BankAcc(double bal = 0) { _balance = bal; }
	virtual ~BankAcc() {}
	void setBal(double bal) { _balance = bal; }
	double getBal() { return _balance; }
	virtual bool deposit(unsigned int) = 0;
	virtual bool withdraw(unsigned int) = 0;
	virtual bool transfer(unsigned int) = 0;
	virtual unsigned int getMaxNumDep() = 0;
	virtual unsigned int getMaxNumWith() = 0;
	virtual bool getPosTransf() = 0;
	virtual unsigned int getMaxAmountReceived() = 0;
	virtual unsigned int getMaxBal() = 0;
};



