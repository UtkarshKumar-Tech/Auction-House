#include "Auction.h"

#include <iostream>
#include <limits>

using namespace std;

// ==============================
// AUCTION CONSTRUCTOR
// ==============================

Auction::Auction(
    int id,
    string item,
    string cat,
    double price,
    string type)
{
    auctionID = id;
    itemName = item;
    category = cat;
    startingPrice = price;
    auctionType = type;
    status = "Open";
    next = nullptr;
}

// ==============================
// AUCTION MANAGER CONSTRUCTOR
// ==============================

AuctionManager::AuctionManager()
{
    head = nullptr;
    tail = nullptr;
    nextAuctionID = 1;
}

// ==============================
// AUCTION MANAGER DESTRUCTOR
// ==============================

AuctionManager::~AuctionManager()
{
    Auction *current = head;

    while (current != nullptr)
    {
        Auction *toDelete = current;
        current = current->next;

        delete toDelete;
    }
}

// ==============================
// FIND AUCTION BY ID
// ==============================

Auction *AuctionManager::findByID(int id)
{
    Auction *current = head;

    while (current != nullptr)
    {
        if (current->auctionID == id)
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}

// ==============================
// CREATE AUCTION
// ==============================

void AuctionManager::createAuction()
{
    string itemName;
    string category;
    string auctionType;
    double startingPrice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n====================================\n";
    cout << "          CREATE AUCTION\n";
    cout << "====================================\n";

    cout << "Enter item name: ";
    getline(cin, itemName);

    cout << "Enter category: ";
    getline(cin, category);

    cout << "Enter starting price: ";
    cin >> startingPrice;

    if (startingPrice <= 0)
    {
        cout << "\nInvalid starting price.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter auction type (Regular/VIP): ";
    getline(cin, auctionType);

    // Create new auction node
    int newID = nextAuctionID++;

    Auction *newAuction = new Auction(
        newID,
        itemName,
        category,
        startingPrice,
        auctionType);

    // Add to linked list
    if (head == nullptr)
    {
        head = newAuction;
        tail = newAuction;
    }
    else
    {
        tail->next = newAuction;
        tail = newAuction;
    }

    cout << "\nAuction created successfully!\n";
    cout << "Auction ID: " << newID << "\n";
}

// ==============================
// DISPLAY ALL AUCTIONS
// ==============================

void AuctionManager::displayAuctions()
{
    if (head == nullptr)
    {
        cout << "\nNo auctions available.\n";
        return;
    }

    cout << "\n============================================\n";
    cout << "              UPPERWORLD AUCTIONS\n";
    cout << "============================================\n";

    Auction *current = head;

    while (current != nullptr)
    {
        cout << "\n--------------------------------------------\n";

        cout << "Auction ID      : " << current->auctionID << "\n";
        cout << "Item Name       : " << current->itemName << "\n";
        cout << "Category        : " << current->category << "\n";
        cout << "Starting Price  : Rs. " << current->startingPrice << "\n";
        cout << "Auction Type    : " << current->auctionType << "\n";
        cout << "Status          : " << current->status << "\n";

        cout << "--------------------------------------------\n";

        current = current->next;
    }
}
// ==============================
// SEARCH AUCTION
// ==============================

void AuctionManager::searchAuction()
{
    int id;

    cout << "\n====================================\n";
    cout << "          SEARCH AUCTION\n";
    cout << "====================================\n";

    cout << "Enter Auction ID: ";
    cin >> id;

    Auction *found = findByID(id);

    if (found == nullptr)
    {
        cout << "\nAuction not found.\n";
        return;
    }

    cout << "\nAuction found successfully!\n";

    cout << "\n--------------------------------------------\n";
    cout << "Auction ID      : " << found->auctionID << "\n";
    cout << "Item Name       : " << found->itemName << "\n";
    cout << "Category        : " << found->category << "\n";
    cout << "Starting Price  : Rs. " << found->startingPrice << "\n";
    cout << "Auction Type    : " << found->auctionType << "\n";
    cout << "Status          : " << found->status << "\n";
    cout << "--------------------------------------------\n";
}
// ==============================
// UPDATE AUCTION
// ==============================

void AuctionManager::updateAuction()
{
    int id;

    cout << "\n====================================\n";
    cout << "          UPDATE AUCTION\n";
    cout << "====================================\n";

    cout << "Enter Auction ID: ";
    cin >> id;

    Auction *found = findByID(id);

    if (found == nullptr)
    {
        cout << "\nAuction not found.\n";
        return;
    }

    cout << "\nAuction found!\n";

    cout << "\nCurrent Auction Details:\n";
    cout << "--------------------------------------------\n";
    cout << "Auction ID      : " << found->auctionID << "\n";
    cout << "Item Name       : " << found->itemName << "\n";
    cout << "Category        : " << found->category << "\n";
    cout << "Starting Price  : Rs. " << found->startingPrice << "\n";
    cout << "Auction Type    : " << found->auctionType << "\n";
    cout << "Status          : " << found->status << "\n";
    cout << "--------------------------------------------\n";

    string newItemName;
    string newCategory;
    string newAuctionType;
    double newStartingPrice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter new item name: ";
    getline(cin, newItemName);

    cout << "Enter new category: ";
    getline(cin, newCategory);

    cout << "Enter new starting price: ";
    cin >> newStartingPrice;

    if (newStartingPrice <= 0)
    {
        cout << "\nInvalid starting price.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter new auction type (Regular/VIP): ";
    getline(cin, newAuctionType);

    // Update auction details
    found->itemName = newItemName;
    found->category = newCategory;
    found->startingPrice = newStartingPrice;
    found->auctionType = newAuctionType;

    cout << "\nAuction updated successfully!\n";
}
// ==============================
// DELETE AUCTION
// ==============================

void AuctionManager::deleteAuction()
{
    int id;

    cout << "\n====================================\n";
    cout << "          DELETE AUCTION\n";
    cout << "====================================\n";

    cout << "Enter Auction ID: ";
    cin >> id;

    // Check if list is empty
    if (head == nullptr)
    {
        cout << "\nNo auctions available.\n";
        return;
    }

    // Case 1: Delete first node
    if (head->auctionID == id)
    {
        Auction *toDelete = head;

        head = head->next;

        // If deleted node was the only node
        if (head == nullptr)
        {
            tail = nullptr;
        }

        delete toDelete;

        cout << "\nAuction deleted successfully.\n";
        return;
    }

    // Search for the node
    Auction *current = head;

    while (current->next != nullptr &&
           current->next->auctionID != id)
    {
        current = current->next;
    }

    // Auction not found
    if (current->next == nullptr)
    {
        cout << "\nAuction not found.\n";
        return;
    }

    // Node to delete
    Auction *toDelete = current->next;

    // Remove node from linked list
    current->next = toDelete->next;

    // If deleting the last node
    if (toDelete == tail)
    {
        tail = current;
    }

    delete toDelete;

    cout << "\nAuction deleted successfully.\n";
}
// ==============================
// FILTER AUCTIONS
// ==============================

void AuctionManager::filterAuctions()
{
    int choice;

    cout << "\n====================================\n";
    cout << "          FILTER AUCTIONS\n";
    cout << "====================================\n";

    cout << "1. Filter by Auction Type\n";
    cout << "2. Filter by Category\n";
    cout << "3. Back\n";

    cout << "\nChoose an option: ";
    cin >> choice;

    if (choice == 1)
    {
        string type;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter auction type (Regular/VIP): ";
        getline(cin, type);

        Auction *current = head;
        bool found = false;

        while (current != nullptr)
        {
            if (current->auctionType == type)
            {
                if (!found)
                {
                    cout << "\n============================================\n";
                    cout << "          FILTERED AUCTIONS\n";
                    cout << "============================================\n";
                }

                cout << "\n--------------------------------------------\n";
                cout << "Auction ID      : " << current->auctionID << "\n";
                cout << "Item Name       : " << current->itemName << "\n";
                cout << "Category        : " << current->category << "\n";
                cout << "Starting Price  : Rs. " << current->startingPrice << "\n";
                cout << "Auction Type    : " << current->auctionType << "\n";
                cout << "Status          : " << current->status << "\n";
                cout << "--------------------------------------------\n";

                found = true;
            }

            current = current->next;
        }

        if (!found)
        {
            cout << "\nNo auctions found for type: " << type << "\n";
        }
    }
    else if (choice == 2)
    {
        string category;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter category: ";
        getline(cin, category);

        Auction *current = head;
        bool found = false;

        while (current != nullptr)
        {
            if (current->category == category)
            {
                if (!found)
                {
                    cout << "\n============================================\n";
                    cout << "          FILTERED AUCTIONS\n";
                    cout << "============================================\n";
                }

                cout << "\n--------------------------------------------\n";
                cout << "Auction ID      : " << current->auctionID << "\n";
                cout << "Item Name       : " << current->itemName << "\n";
                cout << "Category        : " << current->category << "\n";
                cout << "Starting Price  : Rs. " << current->startingPrice << "\n";
                cout << "Auction Type    : " << current->auctionType << "\n";
                cout << "Status          : " << current->status << "\n";
                cout << "--------------------------------------------\n";

                found = true;
            }

            current = current->next;
        }

        if (!found)
        {
            cout << "\nNo auctions found in category: " << category << "\n";
        }
    }
    else if (choice == 3)
    {
        cout << "\nReturning...\n";
    }
    else
    {
        cout << "\nInvalid choice.\n";
    }
}