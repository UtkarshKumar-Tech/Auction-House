#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

// ==============================
// USER NODE STRUCTURE
// ==============================

struct User
{
    int userID;
    string name;
    string email;
    string password;
    string role;

    User* next;

    // Constructor
    User(int id, string n, string e, string p);
};


// ==============================
// USER MANAGEMENT CLASS
// ==============================

class UserManager
{
private:
    User* head;
    User* tail;
    int nextUserID;

public:

    // Constructor
    UserManager();

    // Destructor
    ~UserManager();

    // Search functions
    User* findByEmail(const string& email);
    User* findByID(int id);

    // User functions
    void registerUser();
    void userLogin();
    void userMenu(int userID);
    void displayProfile(User* user);
};

#endif