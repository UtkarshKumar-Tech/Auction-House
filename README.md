# Auction House

A console-based Auction House Management System developed in C++ using basic data structures.

## Project Objective

The project simulates an Auction House with different divisions and services.

The system will gradually include:

- User Management
- Upperworld Auctions
- Regular and VIP Membership
- VIP Card Management
- Bidding System
- Underworld Information Services
- Commission Requests
- Admin / Owner Management
- Transaction Records
- Reports

## Project Progress

### Level 1 - User Management

- User registration
- User login
- User profile
- Unique user ID
- Email validation
- Singly linked list for user management

### Level 2 - Upperworld Auction System

- Auction creation
- Auction display
- Auction search by ID
- Auction update
- Auction deletion
- Auction filtering by type
- Auction filtering by category
- Singly linked list for auction management

### Level 3 - Membership & VIP Card Management

#### Membership System

- Regular membership
- VIP membership
- Total spending tracking
- VIP eligibility based on spending
- VIP upgrade system
- VIP membership display

#### VIP Card System

- VIP card creation
- Unique VIP card ID
- Issue date
- Expiry date
- Active card status
- VIP card display
- Prevention of duplicate active cards

#### VIP Benefits

- Access to VIP auctions
- Early access to selected auctions
- Priority registration
- Access to VIP-only items
- Exclusive VIP events

#### VIP Card Management

- VIP card status checking
- Card access validation
- Card blocking
- Card unblocking
- Card renewal
- Card deactivation

## Data Structures Used

### Singly Linked List

The project currently uses singly linked lists for dynamic management of users, auctions, and VIP cards.

#### User Management

Each user is stored as a node in a linked list.

```text
User 1 -> User 2 -> User 3 -> NULL

## Project Structure

Auction-House/
│
├── main.cpp
├── User.h
├── User.cpp
├── Auction.h
├── Auction.cpp
└── README.md

## Technologies

- C++
- Standard C++ Library
- Console Interface
- Basic Data Structures

## Future Levels

1. User Management
2. Upperworld & Auctions
3. Regular/VIP Membership
4. Bidding System
5. Bid History
6. Auction Winner
7. Auction Transactions
8. Underworld
9. Outer Information Marketplace
10. Information Transactions
11. Inner Commission System
12. Commission Pricing
13. Queue System
14. Priority Queue
15. Information Transactions
16. Commission Transactions
17. Admin / Owner
18. Protected Data Storage
19. Reports
20. Admin Dashboard