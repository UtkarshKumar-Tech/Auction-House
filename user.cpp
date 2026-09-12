#include "User.h"

#include <iostream>
#include <limits>

using namespace std;


// ==============================
// USER CONSTRUCTOR
// ==============================

User::User(int id, string n, string e, string p)
{
    userID = id;
    name = n;
    email = e;
    password = p;
    role = "Customer";
    next = nullptr;
}


// ==============================
// USER MANAGER CONSTRUCTOR
// ==============================

UserManager::UserManager()
{
    head = nullptr;
    tail = nullptr;
    nextUserID = 1;
}


// ==============================
// USER MANAGER DESTRUCTOR
// ==============================

UserManager::~UserManager()
{
    User* current = head;

    while (current != nullptr)
    {
        User* toDelete = current;
        current = current->next;

        delete toDelete;
    }
}


// ==============================
// FIND USER BY EMAIL
// ==============================

User* UserManager::findByEmail(const string& email)
{
    User* current = head;

    while (current != nullptr)
    {
        if (current->email == email)
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}


// ==============================
// FIND USER BY ID
// ==============================

User* UserManager::findByID(int id)
{
    User* current = head;

    while (current != nullptr)
    {
        if (current->userID == id)
        {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}


// ==============================
// REGISTER USER
// ==============================

void UserManager::registerUser()
{
    string name;
    string email;
    string password;

    // Clear leftover newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n====================================\n";
    cout << "          REGISTER USER\n";
    cout << "====================================\n";

    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter email: ";
    getline(cin, email);

    // Check duplicate email
    if (findByEmail(email) != nullptr)
    {
        cout << "\nRegistration failed!\n";
        cout << "Email is already registered.\n";

        return;
    }

    cout << "Enter password: ";
    getline(cin, password);

    // Generate unique User ID
    int newID = nextUserID++;

    // Create new node
    User* newUser = new User(
        newID,
        name,
        email,
        password
    );

    // Insert into linked list
    if (head == nullptr)
    {
        // First user
        head = newUser;
        tail = newUser;
    }
    else
    {
        // Add at the end
        tail->next = newUser;
        tail = newUser;
    }

    cout << "\nRegistration successful!\n";
    cout << "Your User ID is: " << newID << "\n";
}


// ==============================
// USER LOGIN
// ==============================

void UserManager::userLogin()
{
    string email;
    string password;

    // Clear leftover newline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n====================================\n";
    cout << "             USER LOGIN\n";
    cout << "====================================\n";

    cout << "Enter email: ";
    getline(cin, email);

    cout << "Enter password: ";
    getline(cin, password);

    // Search user using email
    User* found = findByEmail(email);

    if (found != nullptr && found->password == password)
    {
        cout << "\nLogin successful!\n";
        cout << "Welcome, " << found->name << "!\n";

        userMenu(found->userID);
    }
    else
    {
        cout << "\nInvalid email or password.\n";
    }
}


// ==============================
// USER MENU
// ==============================

void UserManager::userMenu(int userID)
{
    User* user = findByID(userID);

    if (user == nullptr)
    {
        cout << "\nError: User not found.\n";
        return;
    }

    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "          USER MENU\n";
        cout << "====================================\n";

        cout << "Welcome, " << user->name << "!\n\n";

        cout << "1. View Profile\n";
        cout << "2. Logout\n";

        cout << "\nChoose an option: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayProfile(user);
                break;

            case 2:
                cout << "\nLogging out...\n";
                cout << "Goodbye, " << user->name << "!\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 2);
}


// ==============================
// DISPLAY USER PROFILE
// ==============================

void UserManager::displayProfile(User* user)
{
    cout << "\n====================================\n";
    cout << "           USER PROFILE\n";
    cout << "====================================\n";

    cout << "User ID : " << user->userID << "\n";
    cout << "Name    : " << user->name << "\n";
    cout << "Email   : " << user->email << "\n";
    cout << "Role    : " << user->role << "\n";

    cout << "====================================\n";
}