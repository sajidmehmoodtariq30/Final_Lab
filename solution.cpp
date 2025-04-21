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
class checkingAccount : public account
{
public:
    checkingAccount(float b = 0.0, float r = 0) : account(b, r) {}

    void withdrawlDetails(float amount) override
    {
        if (balance - amount < 0)
        {
            charge += 15; 
            
            balance -= 15;
            return;
        }

        account::withdrawlDetails(amount);
    }

    void monthlyProc() override
    {
        charge += 5 + (0.10 * ndrawls);
        account::monthlyProc();
    }
};

int main()
{
    float savingsBalance, checkingBalance, interestRate;

    cout << "Enter initial savings balance: Rs:";
    cin >> savingsBalance;
    cout << "Enter initial checking balance: Rs:";
    cin >> checkingBalance;
    cout << "Enter annual interest rate (decimal): ";
    cin >> interestRate;

    savingAccount savings;
    savings.depositsDetails(savingsBalance);

    checkingAccount checking(checkingBalance, interestRate);

    int choice;
    float amount;
    float totalSavingsDeposits = 0, totalSavingsWithdrawals = 0;
    float totalCheckingDeposits = 0, totalCheckingWithdrawals = 0;

    do
    {
        cout << "\n1. Deposit to Savings\n2. Withdraw from Savings\n";
        cout << "3. Deposit to Checking\n4. Withdraw from Checking\n";
        cout << "5. End Month\n6. Exit\nChoice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Amount: Rs:";
            cin >> amount;
            savings.depositsDetails(amount);
            totalSavingsDeposits += amount;
            break;
        case 2:
            cout << "Amount: Rs:";
            cin >> amount;
            savings.withdrawlDetails(amount);
            totalSavingsWithdrawals += amount;
            break;
        case 3:
            cout << "Amount: Rs:";
            cin >> amount;
            checking.depositsDetails(amount);
            totalCheckingDeposits += amount;
            break;
        case 4:
            cout << "Amount: Rs:";
            cin >> amount;
            checking.withdrawlDetails(amount);
            totalCheckingWithdrawals += amount;
            break;
        case 5:
            float savingsServiceCharge = savings.getCharge();
            float checkingServiceCharge = checking.getCharge();

            savings.monthlyProc();
            checking.monthlyProc();

            cout << "\n--- Monthly Statement ---\n";
            cout << "\nSavings Account:\n";
            cout << "Beginning balance: Rs:" << savingsBalance << endl;
            cout << "Total deposits: Rs:" << totalSavingsDeposits << endl;
            cout << "Total withdrawals: Rs:" << totalSavingsWithdrawals << endl;
            cout << "Service charges: Rs:" << savingsServiceCharge << endl;
            cout << "Ending balance: Rs:" << savings.getBalance() << endl;

            cout << "\nChecking Account:\n";
            cout << "Beginning balance: Rs:" << checkingBalance << endl;
            cout << "Total deposits: Rs:" << totalCheckingDeposits << endl;
            cout << "Total withdrawals: Rs:" << totalCheckingWithdrawals << endl;
            cout << "Service charges: Rs:" << checkingServiceCharge << endl;
            cout << "Ending balance: Rs:" << checking.getBalance() << endl;

            totalSavingsDeposits = totalSavingsWithdrawals = 0;
            totalCheckingDeposits = totalCheckingWithdrawals = 0;
            savingsBalance = savings.getBalance();
            checkingBalance = checking.getBalance();
            break;
        }
    } while (choice != 6);

    return 0;
}