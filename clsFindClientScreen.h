#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include"clsInputValidate.h"
#include <iomanip>

class clsFindClientScreen :protected clsScreen
{
private :
    static void _Print(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n__________________________________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n__________________________________________\n";

    }
public :
    static void ShowFindClientScreen() {
        if (!CheckAcessRigths(clsUser::enPermissions::pFindClient)) {
            return;
        }
        _DrawScreenHeader("\t  Find Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        if (!Client1.IsEmpty()) {
            cout << "\n Client is Found : " << endl;
            _Print(Client1);
        }
        else
            cout << "\n Client is not Found ... " << endl;
    }
};

