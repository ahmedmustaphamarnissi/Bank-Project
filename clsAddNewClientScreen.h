#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include"clsInputValidate.h"
#include <iomanip>

class clsAddNewClientScreen :protected clsScreen
{
private :
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }
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
	static void AddNewClient() {
        if (!CheckAcessRigths(clsUser::enPermissions::pAddNewClient)) {
            return;
        }
        _DrawScreenHeader("\t  Add New Client Screen");

        cout << "please enter Account number : " << endl;
        string AccountNumber = "";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber)) {
            cout << "Account Number is accualy used try again ... " << endl;
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient NewClient = clsBankClient::AddNewClient(AccountNumber);
        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;
        SaveResult = NewClient.Save();

        switch (SaveResult) {
        case clsBankClient::enSaveResults::svSucceeded: {
            cout << "client Add successfully :-) " << endl;
            _Print(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists: {
            cout << "Account Number is all ready used ..." << endl;
            break;
        }
        case clsBankClient::svFaildEmptyObject: {
            cout << "Error because Account Number is empty ..." << endl;
            break;
        }
        }
    }
};

