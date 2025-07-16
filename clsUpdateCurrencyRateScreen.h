#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsCurrecy.h"
#include<vector>

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency record) {
		cout << "\nCurrency Card \n";
		cout << "_________________________________" << endl;
		cout << "Country  : " << record.Country() << endl;
		cout << "Code     : " << record.CurrencyCode() << endl;
		cout << "Name     : " << record.CurrencyName() << endl;
		cout << "Rate(1$) : " << record.Rate() << endl;
		cout << "_________________________________" << endl;
	}

public :
	static void ShowUpdateCarrencyRateScreen() {
		_DrawScreenHeader("\t Update Currency Screen");

		cout << "Please enter Currency code : ";
		string Code;
		Code = clsInputValidate::ReadString();

		
		while (!clsCurrency::IsCurrencyExist(Code)) {
			cout << "\nCurrency not found ,try again ..." << endl;
			Code = clsInputValidate::ReadString();
		}
		clsCurrency Record = clsCurrency::FindByCode(Code);
		_PrintCurrency(Record);

			char Anser='n';
			cout << "\n Are you sure do you want update this currency ? (y/n) ?";
			cin >> Anser;

			if (Anser == 'y' || Anser == 'Y') {
				cout << "\nUpdate Currency Rate";
				cout << "\n_______________________" << endl;

				cout << "\nEnter New Rate : ";
				double Rate = clsInputValidate::ReadDblNumber();
				Record.UpdateRate(Rate);
				cout << "\nCurrency Rate Updated Sucessfully :-)" << endl;
				_PrintCurrency(Record);
			}
		}
		
		
	
};

