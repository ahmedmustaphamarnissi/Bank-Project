#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 ,eAddNewClient=2};
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete=false;

    void _AddNew() {
        string Line = clsBankClient::_ConverClientObjectToLine(*this);
        clsBankClient::_AddDataLineToFile(Line);
    }

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C.MarkForDelete() == false) {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }
    
    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    

    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
        string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }
    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    struct stTransferLog;
    static stTransferLog _ConvertLineToRecordTranferLog(string Line) {
        vector <string> vRecord = clsString::Split(Line, "#//#");
        stTransferLog Record;
        Record.DateTime = vRecord[0];
        Record.AccountNumberFrom = vRecord[1];
        Record.AccountNumberto = vRecord[2];
        Record.Ammount= stof(vRecord[3]);
        Record.AccountBalanceFrom = stof(vRecord[4]);
        Record.AccountBalanceto = stof(vRecord[5]);
        Record.UserName = vRecord[6];
        return Record;
    }
    
public:
    struct stTransferLog {
        string DateTime;
        string AccountNumberFrom;
        string AccountNumberto;
        float Ammount;
        float AccountBalanceFrom;
        float AccountBalanceto;
        string UserName;
    };
     
    static vector <stTransferLog> GetTransferLogList() {
        vector <stTransferLog> vRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);

        if (MyFile.is_open()) {
            string Line;
            stTransferLog Record;
            while (getline(MyFile, Line)) {
                Record = _ConvertLineToRecordTranferLog(Line);
                vRecord.push_back(Record);
            }
            MyFile.close();
            
        }
        return vRecord;
    }
    
    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }
    bool MarkForDelete() {
        return _MarkForDelete;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    string FullName() {
        return FirstName + " " + LastName;
    }
    

    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }
    bool Deposit(double Ammount) {
        if (Ammount < 0)
            return false;

        _AccountBalance += Ammount;
        Save();

    }

    bool Withdraw(double Ammount) {
        if (Ammount > _AccountBalance)
            return false;

        _AccountBalance -= Ammount;
        Save();

    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 ,svFaildAccountNumberExists};

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }
        case enMode::eAddNewClient :
            if (clsBankClient::IsClientExist(_AccountNumber)) {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else {


                _Mode=enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }


        }



    }
    static clsBankClient AddNewClient(string AccountNumber) {
        return clsBankClient(enMode::eAddNewClient, "", "", "", "", AccountNumber, "", 0);
    }
    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete() {
        vector <clsBankClient> vClients;
       vClients= clsBankClient::_LoadClientsDataFromFile();
       for (clsBankClient& C : vClients) {
           if (C.AccountNumber() == _AccountNumber) {
               _MarkForDelete = true;
               break;
           }
       }
       clsBankClient::_SaveCleintsDataToFile(vClients);
       *this = clsBankClient::_GetEmptyClientObject();

       return true;


    }

    bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);

        return true;
    }
    

    static vector<clsBankClient> GetClientsList() {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances() {
        vector <clsBankClient> vClients;
        vClients = clsBankClient::_LoadClientsDataFromFile();

        double Total=0;
        for (clsBankClient& C : vClients) {
            Total += C.AccountBalance;
        }
        return Total;
     }
};