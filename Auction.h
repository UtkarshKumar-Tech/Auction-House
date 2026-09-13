#ifndef AUCTION_H
#define AUCTION_H

#include <string>

using namespace std;

// ==============================
// AUCTION NODE STRUCTURE
// ==============================

struct Auction
{
    int auctionID;
    string itemName;
    string category;
    double startingPrice;
    string auctionType; // Regular / VIP
    string status;      // Open / Closed

    Auction *next;

    // Constructor
    Auction(
        int id,
        string item,
        string cat,
        double price,
        string type);
};

// ==============================
// AUCTION MANAGEMENT CLASS
// ==============================

class AuctionManager
{
private:
    Auction *head;
    Auction *tail;
    int nextAuctionID;

public:
    // Constructor
    AuctionManager();

    // Destructor
    ~AuctionManager();

    // Auction functions
    void createAuction();
    void displayAuctions();

    // Search auction
    Auction *findByID(int id);

    // Search and display auction
    void searchAuction();

    // Update auction
    void updateAuction();

    // Delete auction
    void deleteAuction();

    // Filter auctions
    void filterAuctions();
};

#endif