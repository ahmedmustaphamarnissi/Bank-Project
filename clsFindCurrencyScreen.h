#pragma once
#include <iostream>
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsCurrecy.h"
#include<vector>

using namespace std;

class clsFindCurrencyScreen :protected clsScreen
{
private :
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
	static void ShowFindCurrencyScreen() {
		

		_DrawScreenHeader("\t  Find Currency Screen");
		cout << "\nFind By [1] Code , or [2] Country ? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 2, "Enter just [1] or [2]  : ");

		if (Choice == 1) {
			string CurrencyCode;
			cout << "\nPlease enter currency code : ";
			CurrencyCode = clsInputValidate::ReadString();
			
			clsCurrency Record = clsCurrency::FindByCode(CurrencyCode);

			if (Record.IsCurrencyExist(CurrencyCode)) {
				cout << "\nCurrency found :-)" << endl;
				_PrintCurrency(Record);
			}
			else {
				
				cout << "\nCurrency not found :-(" << endl;
			}
		}
		else {
			string Name;
			cout << "\nPlease enter Country Name code : ";
			Name = clsInputValidate::ReadString();

			clsCurrency Record = clsCurrency::FindByCountry(Name);

			if (Record.IsEmpty()) {
				cout << "\nCurrency not found :-(" << endl;
			}
			else {
				cout << "\nCurrency found :-)" << endl;
				_PrintCurrency(Record);
			}
		}
	}
};

