#include <iostream>

#include "User.h"
#include "Auction.h"

using namespace std;

// ==============================
// MAIN FUNCTION
// ==============================

int main()
{
    UserManager userManager;
    AuctionManager auctionManager;

    int choice;

    do
    {
        cout << "\n============================================\n";
        cout << "              AUCTION HOUSE\n";
        cout << "============================================\n";

        cout << "1. Register\n";
        cout << "2. User Login\n";
        cout << "3. Upperworld\n";
        cout << "4. Exit\n";

        cout << "\nChoose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            userManager.registerUser();
            break;

        case 2:
            userManager.userLogin();
            break;

        case 3:
        {
            int upperChoice;

            do
            {
                cout << "\n============================================\n";
                cout << "                 UPPERWORLD\n";
                cout << "============================================\n";

                cout << "1. Create Auction\n";
                cout << "2. View Auctions\n";
                cout << "3. Search Auction\n";
                cout << "4. Update Auction\n";
                cout << "5. Delete Auction\n";
                cout << "6. Filter Auctions\n";
                cout << "7. Back\n";

                cout << "\nChoose an option: ";
                cin >> upperChoice;

                switch (upperChoice)
                {
                case 1:
                    auctionManager.createAuction();
                    break;

                case 2:
                    auctionManager.displayAuctions();
                    break;

                case 3:
                    auctionManager.searchAuction();
                    break;

                case 4:
                    auctionManager.updateAuction();
                    break;

                case 5:
                    auctionManager.deleteAuction();
                    break;

                case 6:
                    auctionManager.filterAuctions();
                    break;

                case 7:
                    cout << "\nReturning to main menu...\n";
                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
                }

            } while (upperChoice != 7);

            break;
        }

        case 4:
            cout << "\n============================================\n";
            cout << "        Thank you for using Auction House!\n";
            cout << "============================================\n";

            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}