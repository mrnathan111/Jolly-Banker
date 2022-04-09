//Nathan Koplitz
#include "Account.h"
#include <sstream>

Account::Account(int actNumber, string fN, string lN)
{
    for (int i = 0; i < 10; i++)
    {
        balanceFunds[i] = 0;
    }
    accountID = actNumber;
    firstName = fN;
    lastName = lN;
    fundNames[0] = "Money Market";
    fundNames[1] = "Prime Money Market";
    fundNames[2] = "Long-Term Bond";
    fundNames[3] = "Short-Term Bond";
    fundNames[4] = "500 Index Fund";
    fundNames[5] = "Capital Value Fund";
    fundNames[6] = "Growth Equity Fund";
    fundNames[7] = "Growth Index Fund";
    fundNames[8] = "Value Fund";
    fundNames[9] = "Value Stock Index";
}

void Account::printAccount() const
{
    cout << "Transaction History for " << firstName << " " << lastName << " by fund." << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << fundNames[i] << ": $" << balanceFunds[i] << endl;
        for (int j = 0; j < history[i].size(); j++)
        {
            cout << "  " << history[i][j] << endl;
        }
    }
    cout << endl;
}

void Account::printActFund(const int fundN) const
{
    cout << "Transaction History for " << firstName << " " << lastName << " " << fundNames[fundN] << ": $" << balanceFunds[fundN] << endl;
    for (int i = 0; i < history[fundN].size(); i++)
    {
        cout << "  " << history[fundN][i] << endl;
    }
    cout << endl;
}

void Account::recordTrans(string trans, int fundN)
{
    history[fundN].push_back(trans); //keeps adding transaction history to array of vectors (history)
    return;
}

void Account::printActBalance() const
{
    cout << firstName << " " << lastName << " Account ID: " << accountID << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "      "<< fundNames[i] << ": $" << balanceFunds[i] << endl;
    }
    cout << endl;
}

bool Account::Withdrawal(const int fundNum, const int amount)
{
    char trans = 'W';
    if (balanceFunds[fundNum] < amount) //if fund DOESN'T have enough money
    {
        if (fundNum == 0 && balanceFunds[1] >= (amount - balanceFunds[0])) //if special account, and there is enough to cover in the similar account
        {
            int amt = amount - balanceFunds[0];
            int emptiedAmt = balanceFunds[0];
            balanceFunds[1] -= (amount - balanceFunds[0]);
            balanceFunds[0] = 0;
            stringstream ss;
            ss << trans;
            ss << " ";
            ss << accountID;
            ss << fundNum;
            ss << " ";
            ss << emptiedAmt;
            string line1 = ss.str();
            recordTrans(line1, fundNum); //stores the withdrawal from the insufficient account

            ss.str("");
            ss << trans;
            ss << " ";
            ss << accountID;
            ss << 1;
            ss << " ";
            ss << amt;
            string line = ss.str();
            recordTrans(line, 1); //stores the withdrawal from the account that compensated for the similar account
            return true;
        }
        else if (fundNum == 1 && balanceFunds[0] >= (amount - balanceFunds[1]))
        {
            int emptiedAmt = balanceFunds[0];
            int amt = amount - balanceFunds[1];
            balanceFunds[0] -= (amount - balanceFunds[1]);
            balanceFunds[1] = 0;
            stringstream ss;
            ss << trans;
            ss << " ";
            ss << accountID;
            ss << fundNum; 
            ss << " ";
            ss << emptiedAmt;
            string line1 = ss.str();
            recordTrans(line1, fundNum); //stores the withdrawal from the insufficient account

            ss.str("");
            ss << trans;
            ss << " ";
            ss << accountID;
            ss << 0;
            ss << " ";
            ss << amt;
            string line = ss.str();
            recordTrans(line, 0);//stores the withdrawal from the account that compensated for the similar account
            return true;
        }
        else if (fundNum == 2 && balanceFunds[3] >= (amount - balanceFunds[2]))
        {
            int emptiedAmt = balanceFunds[0];
            int amt = amount - balanceFunds[2];
            balanceFunds[3] -= (amount - balanceFunds[2]);
            balanceFunds[2] = 0;
            stringstream ss;
            ss << trans;
            ss << " ";
            ss << accountID;
            ss << fundNum; 
            ss << " ";
            ss << emptiedAmt;
            string line1 = ss.str();
            recordTrans(line1, fundNum); //stores the withdrawal from the insufficient account

            ss.str("");
            ss << trans;
            ss << " ";
            ss << accountID;
            ss << 3;
            ss << " ";
            ss << amt;
            string line = ss.str();
            recordTrans(line, 3);//stores the withdrawal from the account that compensated for the similar account
            return true;
        }
        else if (fundNum == 3 && balanceFunds[2] >= (amount - balanceFunds[3]))
        {
            int emptiedAmt = balanceFunds[0];
            int amt = amount - balanceFunds[3];
            balanceFunds[2] -= (amount - balanceFunds[3]);
            balanceFunds[3] = 0;
            stringstream ss;
            ss << trans;
            ss << " ";
            ss << accountID;
            ss << fundNum; 
            ss << " ";
            ss << emptiedAmt;
            string line1 = ss.str();
            recordTrans(line1, fundNum);//stores the withdrawal from the insufficient account

            ss.str("");
            ss << trans;
            ss << " ";
            ss << accountID;
            ss << 2;
            ss << " ";
            ss << amt;
            string line = ss.str();
            recordTrans(line, 2);//stores the withdrawal from the account that compensated for the similar account
            return true;
        }
        else
        {
            cout << "ERROR: Not enough funds to withdraw $" << amount << " from " << firstName << " " << lastName << " " << fundNames[fundNum] << endl;
            return false;
        }
    }
    else
    {
        balanceFunds[fundNum] -= amount;
        stringstream ss;
        ss << trans;
        ss << " ";
        ss << accountID;
        ss << fundNum;
        ss << " ";
        ss << amount;
        string line = ss.str();
        recordTrans(line, fundNum); //Stores withdrawal from the account
        return true;
    }
    return true;
}

void Account::Deposit(const int amount, const int fundNum)
{
    balanceFunds[fundNum] += amount;
}

bool Account::Transfer(const int sFund, Account* rAct, const int rFund, const int amt)
{
    bool success = this->WithdDuringTransf(sFund, amt); //Uses this withdraw method so it doesn't store a W and T transaction in it's history. Only T
    if (success == true) // If you could withdraw, then deposit
    {
        rAct->Deposit(amt, rFund);
        return true;
    }
    else
        return false;

}

bool Account::WithdDuringTransf(const int fundNum, const int amount) //Doesn't store history. Only withdraws then returns T/F
{
    if (balanceFunds[fundNum] < amount)
    {
        if (fundNum == 0 && balanceFunds[1] >= (amount - balanceFunds[0])) //if special account, and there is enough to cover in the similar account
        {
            balanceFunds[1] -= (amount - balanceFunds[0]);
            balanceFunds[0] = 0;
            return true;
        }
        else if (fundNum == 1 && balanceFunds[0] >= (amount - balanceFunds[1]))
        {
            balanceFunds[0] -= (amount - balanceFunds[1]);
            balanceFunds[1] = 0;
            return true;
        }
        else if (fundNum == 2 && balanceFunds[3] >= (amount - balanceFunds[2]))
        {
            balanceFunds[3] -= (amount - balanceFunds[2]);
            balanceFunds[2] = 0;
            return true;
        }
        else if (fundNum == 3 && balanceFunds[2] >= (amount - balanceFunds[3]))
        {
            return true;
        }
        else
        {
            cout << "ERROR: Not enough funds to withdraw $" << amount << " from " << firstName << " " << lastName << " " << fundNames[fundNum] << endl;
            return false;
        }
    }
    else
    {
        balanceFunds[fundNum] -= amount;
        return true;
    }
    return true;
}

string Account::getFirstName()
{
    return firstName;
}
string Account::getLastName()
{
    return lastName;
}

void Account::setFirstName(string fN)
{

    firstName = fN;
}
void Account::setLastName(string lN)
{
    lastName = lN;
}

int Account::getID()
{
    return accountID;
}
void Account::setID(int iD)
{
    accountID = iD;
}