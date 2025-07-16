#pragma once
#include<iostream>
#include"clsMainScreen.h"
#include"Global.h"
#include"clsUser.h"
#include "clsScreen.h"

class clsLoginScreen : protected clsScreen
{
private :
	static bool _Login() {
		string UserName, Password;
		bool LoginFail=false;
		short Chances = 3;
		do {
			if (LoginFail) {
				Chances--;
				cout << "\nInvalid UserName/Password  \n";
				cout << "You have " << Chances << " Trial(s) to login ... \n";
			}
			if (Chances == 0) {
				cout << "\nYou use your 3 chances :-( " << endl;
				return false;
			}
			cout << "\nPlease enter User Name : ";
			cin >> UserName;

			cout << "\nPlease enter Password : ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFail = CurrentUser.IsEmpty();

		} while (LoginFail);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
	}

public:
	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t\tLogin Screen");
		return _Login();
	}
};

