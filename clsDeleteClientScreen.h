#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include"clsInputValidate.h"
#include <iomanip>

class clsDeleteClientScreen : protected clsScreen
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
    static void ShowDeleteClientScreen() {
        if (!CheckAcessRigths(clsUser::enPermissions::pDeleteClient)) {
            return;
        }
        _DrawScreenHeader("\t  Delete Client Screen");

        cout << "please enter Account number : " << endl;
        string AccountNumber = "";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "Account Number is not found try again ... " << endl;
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _Print(Client);
        char Anser = 'n';
        cout << "are you sue do you want to delete this client ? (y/n) ? ";
        cin >> Anser;

        if (Anser == 'y' || Anser == 'Y') {
            if (Client.Delete()) {
                cout << "Client deleted successfully ..." << endl;
                _Print(Client);
            }
            else
                cout << "Error client not deleted ... ";
        }
    }
};

