#include <iostream>

using namespace std;

class account
{
protected:
    float balance;
    int ndrawls;
    float charge;

private:
    int ndeposits;
    float rate;

public:
    account(float b = 0.0, float r = 0) : balance(b), rate(r), ndeposits(0), charge(0.0), ndrawls(0) {}
    float getBalance() const { return balance; }
    float getCharge() const { return charge; }
    virtual void depositsDetails(float deposit)
    {
        balance += deposit;
        ndeposits++;
    }
    virtual void withdrawlDetails(float deposit)
    {
        balance -= deposit;
        ndrawls++;
    }
    virtual void calcInt()
    {
        float monthlyIntrestRate = rate / 12;
        float monthlyIntrest = balance * monthlyIntrestRate;
        balance += monthlyIntrest;
    }
    virtual void monthlyProc()
    {
        balance -= charge;
        calcInt();
        ndrawls = 0;
        ndeposits = 0;
        charge = 0;
    }
};

class savingAccount : public account
{
private:
    bool status;

public:
    savingAccount() : status(true)
    {
        if (balance > 25){
            status = false;
            cout << "Account is deactivated";
        }
    };

    void withdrawlDetails(float deposit) override
    {
        if (status)
            account::withdrawlDetails(deposit);
        else
            return;
    }
    void depositsDetails(float deposit) override
    {
        if (!status && balance + deposit > 25)
        {
            cout << "Account is Activated";
            status = true;
        }
        account::depositsDetails(deposit);
    }
    void monthlyProc() override
    {
        if (ndrawls > 4)
            charge++;
        account::monthlyProc();
        if (balance > 25){
            cout << "Account is deactivated";
            status = false;
        }
    }
};