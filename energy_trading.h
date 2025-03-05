#ifndef ENERGY_TRADING_H
#define ENERGY_TRADING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ID_SIZE 6
#define DATE_SIZE 25

// Struct Definitions
typedef struct regularBuyer {
    char buyer_id[ID_SIZE];
    struct regularBuyer* next;
} regularBuyer;

typedef struct seller_id_tag {
    char seller_id[ID_SIZE];
    float price_kwh_gt_300;
    float price_kwh_lt_300;
    struct seller_id_tag *next;
    regularBuyer* regularBuyers;
} seller_node;

typedef struct buyer_id_tag {
    char buyer_id[ID_SIZE];
    int total_amt;
    struct buyer_id_tag *next;
} buyer_node;

typedef struct pairs_tag {
    char seller_id[ID_SIZE];
    char buyer_id[ID_SIZE];
    int number_transactions;
    struct pairs_tag* next;
} pair_node;

typedef struct transaction_id_tag {
    char transaction_id[ID_SIZE];
    char seller_id[ID_SIZE];
    char buyer_id[ID_SIZE];
    int amount_energy;
    float price_kwh;
    char timestamp[DATE_SIZE];
    struct transaction_id_tag *next;
} transaction_node;

// Function Declarations
int validT(char* s);
int validS(char* s);
int validB(char* s);
float get_valid_price(const char* prompt);
int isUniqueTransactionID(char *transactionID, transaction_node* transptr);
void getCurrentTimestamp(char* buffer);
int is_valid_timestamp(const char *timestamp);
transaction_node* createTransactionNode(char* transactionID, char* buyerID, char* sellerID, int amt_energy, float price, const char* date_time);
seller_node* findorcreate_seller(seller_node** sellerptr, char* sellerID);
buyer_node* findorcreate_buyer(buyer_node** buyerptr, char* buyerID, int amnt);
pair_node* findOrCreate_pair(pair_node** pairptr, char* buyerID, char* sellerID);
void add_transaction(transaction_node** transptr, seller_node** sellerptr, buyer_node** buyerptr, pair_node** pairptr, char* transactionID, char* sellerID, char* buyerID, int amt_energy, char* date_time);
void printTableHeader();
void printTableRow(transaction_node* temp);
void displayAllTransactions(transaction_node* transptr);
void displayRegularBuyers(seller_node* sellerptr);
void update_transaction(transaction_node* transptr, seller_node* sellerptr, char* transactionID);
void between_transaction(char* start, char* end, transaction_node* transptr);
float total_revenue_seller(transaction_node *transptr, char *sellerID);
void display_particular_detail(transaction_node *ptr, char* person);
void list_of_seller(transaction_node *transptr, seller_node* sellerptr);
void list_of_buyer(transaction_node *transptr, buyer_node* buyerptr);
transaction_node* trans_merge(transaction_node* list1, transaction_node* list2);
transaction_node* trans_divide(transaction_node* list_ptr);
transaction_node* trans_sort(transaction_node** transptr);
void display_highest_energy(transaction_node* ptr);
buyer_node* merge(buyer_node* list1, buyer_node* list2);
buyer_node* divide(buyer_node* list_ptr);
buyer_node* buyer_sort(buyer_node** buyerptr);
pair_node* pair_merge(pair_node* list1, pair_node* list2);
pair_node* pair_divide(pair_node* list_ptr);
pair_node* pair_sort(pair_node** pairptr);
void display_pair(pair_node* lptr);
void readSellersFromFile(seller_node** sellerptr, const char* filename);
void readTransactionsFromFile(transaction_node** transptr, seller_node** sellerptr, buyer_node** buyerptr, pair_node** pairptr, const char* filename);
void cleanUpMemory(transaction_node** transHead, seller_node** sellerHead, buyer_node** buyerHead, pair_node** pairHead);
void writeSellersToFile(seller_node* sellerptr, const char* filename);
void writeTransactionsToFile(transaction_node* transptr, const char* filename);
void displayMenu();

#endif // ENERGY_TRADING_H