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

    // Level 3 - Membership
    string membershipStatus;
    double totalSpending;

    User *next;

    User(int id, string n, string e, string p);
};

// ==============================
// VIP CARD
// ==============================

struct VIPCard
{
    int cardID;
    int userID;
    string issueDate;
    string expiryDate;
    string status;

    VIPCard *next;

    VIPCard(
        int id,
        int uid,
        string issue,
        string expiry);
};

// ==============================
// USER MANAGEMENT CLASS
// ==============================

class UserManager
{
private:
    User *head;
    User *tail;
    int nextUserID;

    // Level 3 - VIP Cards
    VIPCard *vipHead;
    VIPCard *vipTail;
    int nextCardID;

public:
    // Constructor
    UserManager();

    // Destructor
    ~UserManager();

    // Search functions
    User *findByEmail(const string &email);
    User *findByID(int id);

    // User functions
    void registerUser();
    void userLogin();
    void userMenu(int userID);
    void displayProfile(User *user);

    // Level 3 - Spending
    void addSpending(int userID);

    // Level 3 - VIP Eligibility
    bool isVIPEligible(User *user);
    void upgradeToVIP(int userID);

    // VIP Card
    void createVIPCard(int userID);
    void displayVIPCard(int userID);
    void displayVIPBenefits(int userID);
    void checkVIPCardStatus(int userID);
    void blockVIPCard(int userID);
    void unblockVIPCard(int userID);
    void renewVIPCard(int userID);
    void deactivateVIPCard(int userID);
};

#endif