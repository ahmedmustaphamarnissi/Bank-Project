#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private :
    static void PrintTransferLogRecordLine(clsBankClient::stTransferLog LoginRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(8) << left << LoginRegisterRecord.AccountNumberFrom;
        cout << "| " << setw(8) << left << LoginRegisterRecord.AccountNumberto;
        cout << "| " << setw(8) << left << LoginRegisterRecord.Ammount;
        cout << "| " << setw(10) << left << LoginRegisterRecord.AccountBalanceFrom;
        cout << "| " << setw(10) << left << LoginRegisterRecord.AccountBalanceto;
        cout << "| " << setw(8) << left << LoginRegisterRecord.UserName;
    }
public :
    static void ShowLoginRegisterScreen()
    {
        
        vector <clsBankClient::stTransferLog> vTransferLogRecord = clsBankClient::GetTransferLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t\t(" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Ammount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsBankClient::stTransferLog Record : vTransferLogRecord)
            {

                PrintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        
    }
};

