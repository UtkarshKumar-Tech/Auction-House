#include <iostream>

#include "User.h"

using namespace std;


// ==============================
// MAIN FUNCTION
// ==============================

int main()
{
    UserManager manager;

    int choice;

    do
    {
        cout << "\n============================================\n";
        cout << "              AUCTION HOUSE\n";
        cout << "============================================\n";

        cout << "              LEVEL 1\n";
        cout << "           USER MANAGEMENT\n";

        cout << "============================================\n";

        cout << "1. Register\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";

        cout << "\nChoose an option: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                manager.registerUser();
                break;

            case 2:
                manager.userLogin();
                break;

            case 3:
                cout << "\n============================================\n";
                cout << "     Thank you for using Auction House!\n";
                cout << "============================================\n";

                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}