#include "energy_trading.h"
//reading from energy trading file
void readTransactionsFromFile(transaction_node** transptr, seller_node** sellerptr, buyer_node** buyerptr, pair_node** pairptr, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open transactions file");
        return;
    }
    char buffer[100];  
    fgets(buffer, sizeof(buffer), file);
    char transactionID[ID_SIZE], sellerID[ID_SIZE], buyerID[ID_SIZE], timestamp[DATE_SIZE];
    int amt_energy;
     // read a string untill comma come
    while (fscanf(file, "%[^,],%[^,],%[^,],%d,%[^\n]\n", transactionID, sellerID, buyerID, &amt_energy, timestamp) == 5) {
        add_transaction(transptr, sellerptr, buyerptr, pairptr, transactionID, sellerID, buyerID, amt_energy, timestamp);
    }

    fclose(file);
}
//writing into energy tradingfile
void writeTransactionsToFile(transaction_node* transptr, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open transactions file for writing");
        return;
    }
    fprintf(file, "TransactionID,SellerID,BuyerID,AmountEnergy,Timestamp\n");
    transaction_node* temp = transptr;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%s,%d,%s\n", temp->transaction_id, temp->seller_id, temp->buyer_id, temp->amount_energy, temp->timestamp);
        temp = temp->next;
    }

    fclose(file);
}
// reading from seller file
void readSellersFromFile(seller_node** sellerptr, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open sellers file");
        return;
    }
    char buffer[100]; 
    fgets(buffer, sizeof(buffer), file);
    char sellerID[ID_SIZE];
    float price_kwh_lt_300, price_kwh_gt_300;

    while (fscanf(file, "%[^,],%f,%f\n", sellerID, &price_kwh_lt_300, &price_kwh_gt_300) == 3) {
        seller_node* newSeller = (seller_node*)malloc(sizeof(seller_node));
        strcpy(newSeller->seller_id, sellerID);
        newSeller->price_kwh_lt_300 = price_kwh_lt_300;
        newSeller->price_kwh_gt_300 = price_kwh_gt_300;
        newSeller->regularBuyers = NULL;
        newSeller->next = *sellerptr;
        *sellerptr = newSeller;
    }

    fclose(file);
}
//write into seller file
void writeSellersToFile(seller_node* sellerptr, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open sellers file for writing");
        return;
    }
    fprintf(file, "SellerID,Price_KWh_LT_300,Price_KWh_GT_300\n");

    seller_node* temp = sellerptr;
    while (temp != NULL) {
        fprintf(file, "%s,%.2f,%.2f\n", temp->seller_id, temp->price_kwh_lt_300, temp->price_kwh_gt_300);
        temp = temp->next;
    }

    fclose(file);
}