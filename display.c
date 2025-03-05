#include "energy_trading.h"
// display menu
void displayMenu() {
    printf("\n========== Energy Trading System ==========");
    printf("\n1. Add Transaction");
    printf("\n2. Display All Transactions");
    printf("\n3. Display Regular Buyers");
    printf("\n4. Update a Transaction");
    printf("\n5. Calculate Total Revenue of a Seller");
    printf("\n6. Display Transactions in a Time Range");
    printf("\n7. List Transactions by Seller");
    printf("\n8. List Transactions by Buyer");
     printf("\n9. Find and Display the Transaction with the Highest Energy Amount and Sort Transactions by amount of energy.");
    printf("\n10. Sort buyer's by energy");
    printf("\n11. Sort Seller/buyer pairs in decreasing order of the number of transactions");
    printf("\n12. Exit");
    printf("\n==========================================\n");
}
// table header
void printTableHeader() {
    printf("------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-10s | %-10s | %-10s | %-20s |\n", "Trans ID", "Seller ID", "Buyer ID", "Energy", "Price/kWh", "Timestamp");
    printf("--------------------------------------------------------------------------------------------------\n");
}
// Display single transactions
void printTableRow(transaction_node* temp) {
    printf("| %-10s | %-10s | %-10s | %-10d | %-10.2f | %-20s |\n", 
           temp->transaction_id, temp->seller_id, temp->buyer_id, temp->amount_energy, temp->price_kwh, temp->timestamp);
}

// display all transaction
void displayAllTransactions(transaction_node* transptr) {
    transaction_node* temp = transptr;
    printf("\nAll Transactions:\n");
    printTableHeader();
    while (temp != NULL) {
        printTableRow(temp);
        temp = temp->next;
    }
    printf("--------------------------------------------------------------\n");
}
// display detail of particular seller or buyer;
void display_particular_detail(transaction_node *ptr,char* person)
{
                printf("| %-12s | %-12s | %-15d | %-10.2f | %-20s |\n",
                ptr->transaction_id, person, ptr->amount_energy, ptr->price_kwh, ptr->timestamp);
}
// display transaction btw time
void between_transaction(char* start,char* end,transaction_node* transptr){
    transaction_node* temp = transptr;
    int flag=0;
    printTableHeader();
    while(temp!=NULL){
        if(strcmp(start,temp->timestamp) <= 0 && strcmp(end,temp->timestamp)>=0){
            flag=1;
         printTableRow(temp);  
        }
        temp=temp->next;
    }
    if(flag==0)
    {
        printf("NO transaction exist btween the entered time period!!!\n");
    }
    printf("---------------------------------------------------\n");
}