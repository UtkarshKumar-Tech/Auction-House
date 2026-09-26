#include "User.h"

#include <iostream>
#include <limits>

using namespace std;

// ==============================
// VIP CONFIGURATION
// ==============================

const double VIP_THRESHOLD = 500000.0;

// ==============================
// VIP Card Constructor
// ==============================

VIPCard::VIPCard(
    int id,
    int uid,
    string issue,
    string expiry)
{
    cardID = id;
    userID = uid;
    issueDate = issue;
    expiryDate = expiry;
    status = "Active";
    next = nullptr;
}

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

    // Level 3 - Membership
    membershipStatus = "Regular";
    totalSpending = 0.0;

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

    // Level 3 - VIP Cards
    vipHead = nullptr;
    vipTail = nullptr;
    nextCardID = 1;
}

// ==============================
// USER MANAGER DESTRUCTOR
// ==============================

UserManager::~UserManager()
{
    // Delete all users
    User *current = head;

    while (current != nullptr)
    {
        User *toDelete = current;
        current = current->next;
        delete toDelete;
    }

    // Delete all VIP cards
    VIPCard *cardCurrent = vipHead;

    while (cardCurrent != nullptr)
    {
        VIPCard *cardToDelete = cardCurrent;
        cardCurrent = cardCurrent->next;
        delete cardToDelete;
    }
}

// ==============================
// FIND USER BY EMAIL
// ==============================

User *UserManager::findByEmail(const string &email)
{
    User *current = head;

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

User *UserManager::findByID(int id)
{
    User *current = head;

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
    User *newUser = new User(
        newID,
        name,
        email,
        password);

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
    User *found = findByEmail(email);

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
    User *user = findByID(userID);

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
        cout << "2. Add Spending\n";
        cout << "3. Upgrade to VIP\n";
        cout << "4. Create VIP Card\n";
        cout << "5. View VIP Card\n";
        cout << "6. View VIP Benefits\n";
        cout << "7. Check VIP Card Status\n";
        cout << "8. Logout\n";

        cout << "\nChoose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayProfile(user);
            break;

        case 2:
            addSpending(userID);
            break;

        case 3:
            upgradeToVIP(userID);
            break;

        case 4:
            createVIPCard(userID);
            break;

        case 5:
            displayVIPCard(userID);
            break;

        case 6:
            displayVIPBenefits(userID);
            break;

        case 7:
            checkVIPCardStatus(userID);
            break;

        case 8:
            cout << "\nLogging out...\n";
            cout << "Goodbye, " << user->name << "!\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

// ==============================
// DISPLAY USER PROFILE
// ==============================

void UserManager::displayProfile(User *user)
{
    cout << "\n====================================\n";
    cout << "           USER PROFILE\n";
    cout << "====================================\n";

    cout << "User ID : " << user->userID << "\n";
    cout << "Name    : " << user->name << "\n";
    cout << "Email   : " << user->email << "\n";
    cout << "Role    : " << user->role << "\n";
    cout << "Membership : " << user->membershipStatus << "\n";
    cout << "Total Spending : Rs. " << user->totalSpending << "\n";

    cout << "VIP Threshold   : Rs. " << VIP_THRESHOLD << "\n";

    if (isVIPEligible(user))
    {
        cout << "VIP Eligibility : Eligible\n";
    }
    else
    {
        cout << "VIP Eligibility : Not Eligible\n";
    }

    cout << "====================================\n";
}

// ==============================
// ADD SPENDING
// ==============================

void UserManager::addSpending(int userID)
{
    User *user = findByID(userID);

    if (user == nullptr)
    {
        cout << "\nError: User not found.\n";
        return;
    }

    double amount;

    cout << "\n====================================\n";
    cout << "          ADD SPENDING\n";
    cout << "====================================\n";

    cout << "Current Spending : Rs. "
         << user->totalSpending << "\n";

    cout << "Enter spending amount: ";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "\nInvalid amount.\n";
        return;
    }

    user->totalSpending += amount;

    cout << "\nSpending added successfully!\n";
    cout << "Added Amount     : Rs. " << amount << "\n";
    cout << "Total Spending   : Rs. "
         << user->totalSpending << "\n";
}

// ==============================
// CHECK VIP ELIGIBILITY
// ==============================

bool UserManager::isVIPEligible(User *user)
{
    if (user == nullptr)
    {
        return false;
    }

    if (user->membershipStatus == "VIP")
    {
        return false;
    }

    return user->totalSpending >= VIP_THRESHOLD;
}

// ==============================
// UPGRADE TO VIP
// ==============================

void UserManager::upgradeToVIP(int userID)
{
    User *user = findByID(userID);

    if (user == nullptr)
    {
        cout << "\nError: User not found.\n";
        return;
    }

    if (user->membershipStatus == "VIP")
    {
        cout << "\nUser is already a VIP member.\n";
        return;
    }

    if (!isVIPEligible(user))
    {
        cout << "\nVIP upgrade not available.\n";
        cout << "You need to spend at least Rs. "
             << VIP_THRESHOLD << " to become eligible.\n";

        cout << "Current Spending : Rs. "
             << user->totalSpending << "\n";

        cout << "Remaining Amount : Rs. "
             << VIP_THRESHOLD - user->totalSpending << "\n";

        return;
    }

    user->membershipStatus = "VIP";

    cout << "\n====================================\n";
    cout << "          VIP UPGRADE\n";
    cout << "====================================\n";

    cout << "Congratulations, " << user->name << "!\n";
    cout << "You are now a VIP member.\n";
    cout << "Total Spending : Rs. "
         << user->totalSpending << "\n";
    cout << "Membership     : VIP\n";

    cout << "====================================\n";
}

// ==============================
// createVIPCard()
// ==============================

void UserManager::createVIPCard(int userID)
{
    User *user = findByID(userID);

    if (user == nullptr)
    {
        cout << "\nError: User not found.\n";
        return;
    }

    // Only VIP users can get a VIP card
    if (user->membershipStatus != "VIP")
    {
        cout << "\nVIP card cannot be created.\n";
        cout << "User is not a VIP member.\n";
        return;
    }

    // Check if the user already has an active card
    VIPCard *current = vipHead;

    while (current != nullptr)
    {
        if (current->userID == userID &&
            current->status == "Active")
        {
            cout << "\nUser already has an active VIP card.\n";
            cout << "Card ID: " << current->cardID << "\n";
            return;
        }

        current = current->next;
    }

    string issueDate;
    string expiryDate;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n====================================\n";
    cout << "          CREATE VIP CARD\n";
    cout << "====================================\n";

    cout << "Enter issue date (DD/MM/YYYY): ";
    getline(cin, issueDate);

    cout << "Enter expiry date (DD/MM/YYYY): ";
    getline(cin, expiryDate);

    int newCardID = nextCardID++;

    VIPCard *newCard = new VIPCard(
        newCardID,
        userID,
        issueDate,
        expiryDate);

    // Add card to linked list
    if (vipHead == nullptr)
    {
        vipHead = newCard;
        vipTail = newCard;
    }
    else
    {
        vipTail->next = newCard;
        vipTail = newCard;
    }

    cout << "\nVIP Card created successfully!\n";
    cout << "Card ID: " << newCardID << "\n";
}

// ==============================
// displayVIPCard()
// ==============================

void UserManager::displayVIPCard(int userID)
{
    VIPCard *current = vipHead;

    while (current != nullptr)
    {
        if (current->userID == userID)
        {
            cout << "\n====================================\n";
            cout << "             VIP CARD\n";
            cout << "====================================\n";

            cout << "Card ID      : " << current->cardID << "\n";
            cout << "User ID      : " << current->userID << "\n";
            cout << "Issue Date   : " << current->issueDate << "\n";
            cout << "Expiry Date  : " << current->expiryDate << "\n";
            cout << "Status       : " << current->status << "\n";

            cout << "====================================\n";

            return;
        }

        current = current->next;
    }

    cout << "\nNo VIP card found for this user.\n";
}

// ==============================
// displayVIPBenefits()
// ==============================

void UserManager::displayVIPBenefits(int userID)
{
    User *user = findByID(userID);

    if (user == nullptr)
    {
        cout << "\nError: User not found.\n";
        return;
    }

    if (user->membershipStatus != "VIP")
    {
        cout << "\nVIP benefits are available only to VIP members.\n";
        return;
    }

    cout << "\n====================================\n";
    cout << "           VIP BENEFITS\n";
    cout << "====================================\n";

    cout << "1. Access to VIP Auctions\n";
    cout << "2. Early Access to Selected Auctions\n";
    cout << "3. Priority Registration\n";
    cout << "4. Access to VIP-Only Items\n";
    cout << "5. Exclusive VIP Events\n";

    cout << "====================================\n";
}

// ==============================
// checkVIPCardStatus
// ==============================

void UserManager::checkVIPCardStatus(int userID)
{
    VIPCard *current = vipHead;

    while (current != nullptr)
    {
        if (current->userID == userID)
        {
            cout << "\n====================================\n";
            cout << "        VIP CARD STATUS\n";
            cout << "====================================\n";

            cout << "Card ID      : " << current->cardID << "\n";
            cout << "Status       : " << current->status << "\n";
            cout << "Issue Date   : " << current->issueDate << "\n";
            cout << "Expiry Date  : " << current->expiryDate << "\n";

            if (current->status == "Active")
            {
                cout << "Card Access  : Allowed\n";
            }
            else
            {
                cout << "Card Access  : Not Allowed\n";
            }

            cout << "====================================\n";

            return;
        }

        current = current->next;
    }

    cout << "\nNo VIP card found for this user.\n";
}

// ==============================
// blockVIPCard
// ==============================

void UserManager::blockVIPCard(int userID)
{
    VIPCard* current = vipHead;

    while (current != nullptr)
    {
        if (current->userID == userID)
        {
            if (current->status == "Blocked")
            {
                cout << "\nVIP card is already blocked.\n";
                cout << "Card ID: " << current->cardID << "\n";
                return;
            }

            current->status = "Blocked";

            cout << "\n====================================\n";
            cout << "          VIP CARD BLOCKED\n";
            cout << "====================================\n";
            cout << "Card ID : " << current->cardID << "\n";
            cout << "Status  : Blocked\n";
            cout << "====================================\n";

            return;
        }

        current = current->next;
    }

    cout << "\nNo VIP card found for this user.\n";
}

// ==============================
// unblockVIPCard
// ==============================

void UserManager::unblockVIPCard(int userID)
{
    VIPCard* current = vipHead;

    while (current != nullptr)
    {
        if (current->userID == userID)
        {
            if (current->status == "Active")
            {
                cout << "\nVIP card is already active.\n";
                cout << "Card ID: " << current->cardID << "\n";
                return;
            }

            current->status = "Active";

            cout << "\n====================================\n";
            cout << "         VIP CARD UNBLOCKED\n";
            cout << "====================================\n";
            cout << "Card ID : " << current->cardID << "\n";
            cout << "Status  : Active\n";
            cout << "====================================\n";

            return;
        }

        current = current->next;
    }

    cout << "\nNo VIP card found for this user.\n";
}

// ==============================
// renewVIPCard
// ==============================

void UserManager::renewVIPCard(int userID)
{
    VIPCard* current = vipHead;

    while (current != nullptr)
    {
        if (current->userID == userID)
        {
            string newExpiryDate;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n====================================\n";
            cout << "          RENEW VIP CARD\n";
            cout << "====================================\n";

            cout << "Current Expiry Date : "
                 << current->expiryDate << "\n";

            cout << "Enter new expiry date (DD/MM/YYYY): ";
            getline(cin, newExpiryDate);

            if (newExpiryDate.empty())
            {
                cout << "\nInvalid expiry date.\n";
                return;
            }

            current->expiryDate = newExpiryDate;

            // Renewal activates a blocked card again
            current->status = "Active";

            cout << "\nVIP Card renewed successfully!\n";
            cout << "Card ID          : " << current->cardID << "\n";
            cout << "New Expiry Date  : " << current->expiryDate << "\n";
            cout << "Status            : " << current->status << "\n";

            return;
        }

        current = current->next;
    }

    cout << "\nNo VIP card found for this user.\n";
}

// ==============================
// deactivateVipCard
// ==============================

void UserManager::deactivateVIPCard(int userID)
{
    VIPCard* current = vipHead;

    while (current != nullptr)
    {
        if (current->userID == userID)
        {
            if (current->status == "Deactivated")
            {
                cout << "\nVIP card is already deactivated.\n";
                cout << "Card ID: " << current->cardID << "\n";
                return;
            }

            current->status = "Deactivated";

            cout << "\n====================================\n";
            cout << "       VIP CARD DEACTIVATED\n";
            cout << "====================================\n";

            cout << "Card ID : " << current->cardID << "\n";
            cout << "Status  : Deactivated\n";

            cout << "====================================\n";

            return;
        }

        current = current->next;
    }

    cout << "\nNo VIP card found for this user.\n";
}