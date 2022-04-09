//Nathan Koplitz
#include "Bank.h"
#include <sstream>

Bank::Bank(string fileName)
{
    string line;
    ifstream inFile(fileName);
    if (inFile.is_open())
    {
        while (getline(inFile, line)) 
        {
            queueOfTrans.push(line); //Push each line of the file to the queue
        }
    }
    else
    {
        cout << "File unable to open" << endl;
        exit(0);
    }
    inFile.close();
}

void Bank::processQ()
{
    processCopyQ(queueOfTrans);
}

void Bank::processCopyQ(queue <string> q)
{
    //Process the queue, parsing each line correctly
    while (!q.empty())
    {
        string line = q.front();
        stringstream ss(line);
        int actNum = 0;
        int fundNum = 0;
        int amountDesired;
        char trans;
        string lN;
        string fN;
        ss >> trans;
        if (trans == 'O') //If opening an Account
        {
            ss >> lN;
            ss >> fN;
            ss >> actNum;
            if (accountTree.Search(actNum, accountTree.root) == true)  //If Account already exists
            {
                cout << "ERROR: Account " << actNum << " is already open. Transaction refused." << endl;
            }
            else //Account does NOT exist 
            {
                Account* act = new Account((int) actNum, (string) fN, (string) lN);
                accountTree.insert(act);
            }
        }
        else if (trans == 'W') //If Withdrawing from an Account
        {
            string actNumAndFund; //below I am parsing the line into my needed variables, converting as needed to correct data type using stringstream
            ss >> actNumAndFund; //ss == actNum&Fund
            ss >> amountDesired;
            char fund = actNumAndFund.at(4); //fund = fundNum
            actNumAndFund.pop_back(); //remove last digit (fundNum) from actNum string
            actNum = stoi(actNumAndFund); //converting
            fundNum = fund - '0'; //converting
            Account* act = accountTree.Retrieve(actNum, accountTree.root);
            if (act == nullptr) //if Account does not exist
                cout << "ERROR: Account " << actNum << " not found. Transaction refused." << endl;
            else
            {
                bool success = act->Withdrawal(fundNum, amountDesired);
                if (success == false) //If unable to withdraw, still store the withdrawal in history with + (Failed) at the end of the line
                {
                    string amt = to_string(amountDesired);
                    string result = line.substr(0,8);
                    result += amt;
                    result += " (Failed)";
                    act->recordTrans(result, fundNum);
                }
            }
        }
        else if (trans == 'D') //If depositing into Account
        {
            string actNumAndFund;
            ss >> actNumAndFund; //ss == actNum&Fund
            ss >> amountDesired;
            char fund = actNumAndFund.at(4); //fund = fundNum
            actNumAndFund.pop_back(); //remove last digit (fundNum) from actNum string
            actNum = stoi(actNumAndFund);
            fundNum = fund - '0';
            Account* act = accountTree.Retrieve(actNum, accountTree.root);
            if (act == nullptr)
                cout << "ERROR: Account " << actNum << " not found. Transaction refused." << endl;
            else
            {
                act->Deposit(amountDesired, fundNum); //Deposit desired money into account
                act->recordTrans(line, fundNum); //Record transactions into history
            }
        }
        else if (trans == 'T') //If transferring between funds or accounts
        {
            int recActNum; //receiving Account Number
            int sendActNum; //Sending Account Number
            int recFund; //Receiving Fund
            int sendFund; //Sending Fund
            string sendActNumAndFund; //Below I am parsing the line for desired variables and converting as needed
            string recActNumAndFund;
            ss >> sendActNumAndFund;
            ss >> amountDesired;

            char tempSFund = sendActNumAndFund.at(4);
            string sendActNandF = sendActNumAndFund;
            sendActNumAndFund.pop_back();
            sendActNum = stoi(sendActNumAndFund);
            sendFund = tempSFund - '0';
            ss >> recActNumAndFund;
            char tempRFund = recActNumAndFund.at(4);
            string recActNandF = recActNumAndFund;
            recActNumAndFund.pop_back();
            recActNum = stoi(recActNumAndFund);
            recFund = tempRFund - '0';
            if (accountTree.Search(sendActNum, accountTree.root) == false) //If sending account does NOT exist
            {
                cout << "ERROR: Account " << sendActNum << " not found. Transferal refused." << endl;
            }
            else if (accountTree.Search(recActNum, accountTree.root) == false)  //Sending account exists, but recieving account does NOT
            {
                Account* sendAct = accountTree.Retrieve(sendActNum, accountTree.root);
                cout << "ERROR: Account " << recActNum << " not found. Transferal refused." << endl;
                string amt = to_string(amountDesired);
                string result;
                result.push_back(trans);
                result += " " + sendActNandF + " " + amt + " " + recActNandF + " (Failed)";
                sendAct->recordTrans(result, fundNum); //Store Failed transfer to sending accounts history
            }
            else 
            {
                Account* recAct = accountTree.Retrieve(recActNum, accountTree.root);
                Account* sendAct = accountTree.Retrieve(sendActNum, accountTree.root);
                sendAct->Transfer(sendFund, recAct, recFund, amountDesired); //transfer funds

                sendAct->recordTrans(line, sendFund); //record transfer to both sending and receiving accounts' history
                recAct->recordTrans(line, recFund);
            }
        }
        else if (trans == 'H') //If Printing history of account or fund
        {
            string actNumAndFund;
            ss >> actNumAndFund;
            if (actNumAndFund.size() == 4) //if printing entire account
            {
                actNum = stoi(actNumAndFund);
                if (accountTree.Search(actNum, accountTree.root) == false)
                    cout << "ERROR: Account " << actNum << " not found. Transaction refused." << endl;
                else
                {
                    Account* act = accountTree.Retrieve(actNum, accountTree.root);
                    act->printAccount();
                }
            }
            else if (actNumAndFund.size() == 5) // if printing 1 fund in the account
            {
                char tempFund = actNumAndFund.at(4);
                actNumAndFund.pop_back();
                actNum = stoi(actNumAndFund);
                fundNum = tempFund - '0';
                if (accountTree.Search(actNum, accountTree.root) == false)
                    cout << "ERROR: Account" << actNum << " not found. Transaction refused" << endl;
                else
                {
                    Account* act = accountTree.Retrieve(actNum, accountTree.root);
                    act->printActFund(fundNum);
                }
            }
        }
        ss.str(""); //Resets stringstream
        q.pop(); //Pops off each line of queue as you go, processing each transaction
    }
    cout << endl;
    cout << "Processing Done. Final Balances" << endl;
    accountTree.recPrintAct(accountTree.root); //Prints off account balances
}