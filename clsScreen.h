#pragma once
#include <iostream>
#include"clsUser.h"
#include"Global.h"
#include"clsDate.h"

using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "Date : " << clsDate::DateToString(clsDate());
        cout << "\t\t\t______________________________________";
        cout << "\n\nUser : " << CurrentUser.UserName ;
        cout << "  \t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

    }
public :
    
    static bool CheckAcessRigths(clsUser::enPermissions Permission) {
        if (!CurrentUser.CheckAccessPermission(Permission)) {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\tAcess Denied , Contatct your Admin";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
            return true;
    }

};

