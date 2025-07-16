#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsCurrecy.h"
#include<vector>
#include <iomanip>

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private : 

    static void _PrintCurrencyRecordLine(clsCurrency Record)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << Record.Country();
        cout << "| " << setw(8) << left << Record.CurrencyCode();
        cout << "| " << setw(40) << left << Record.CurrencyName();
        cout << "| " << setw(10) << left << Record.Rate();
        
    }

public :
	static void ShowCurrenciesListScreen() {
		
		vector <clsCurrency> vRecord = clsCurrency::GetCurrenciesList();

        string Title = "\t\tCurrencies List";
        string SubTitle = "\t    (" + to_string(vRecord.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(40) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vRecord.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        for (clsCurrency C : vRecord) {
            _PrintCurrencyRecordLine(C);
            cout << endl;
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
	}
};

