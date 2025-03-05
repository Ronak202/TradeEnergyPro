#include "energy_trading.h"
int main() {
    transaction_node* transptr = NULL;
    seller_node* sellerptr = NULL;
    buyer_node* buyerptr = NULL;
    pair_node* pairptr = NULL;
    void* temptransptr = NULL;
    void* tempbuyer = NULL;
    void* temppairptr = NULL;

    // Read sellers and transactions from files
    readSellersFromFile(&sellerptr, "sellertable.txt");
    readTransactionsFromFile(&transptr, &sellerptr, &buyerptr, &pairptr, "energytrading.txt");

    int choice;
    char transactionID[ID_SIZE], sellerID[ID_SIZE], buyerID[ID_SIZE], timestamp[DATE_SIZE];
    int amt_energy;
    float revenue;
    char start[DATE_SIZE], end[DATE_SIZE];

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            do {
                printf("Enter Transaction ID (must start with 'TXXXX',0<X<9 and be unique): ");
                scanf("%5s", transactionID);
            } while (!validT(transactionID) || !isUniqueTransactionID(transactionID, transptr));

            do {
                printf("Enter Seller ID (must start with 'SXXXX'): ");
                scanf("%5s", sellerID);
            } while (!validS(sellerID));

            do {
                printf("Enter Buyer ID (must start with 'BXXXX'): ");
                scanf("%5s", buyerID);
            } while (!validB(buyerID));

            int valid_input = 0;  
            char ch;
            printf("Enter Energy Amount: ");
            while (!valid_input) {  // Loop until valid input is entered
                if (scanf("%d", &amt_energy) == 1 && amt_energy != 0) {  
                    valid_input = 1;  // Mark input as valid
                } else {
                    printf("Enter correct amount\n");
                    amt_energy = 0;  // Reset value
                    
                    // Clear the input buffer to prevent infinite loop dicard
                    while ((ch = getchar()) != '\n' && ch != EOF);
                }
            }
            getCurrentTimestamp(timestamp);
            add_transaction(&transptr, &sellerptr, &buyerptr, &pairptr, transactionID, sellerID, buyerID, amt_energy, timestamp);
            break;
            case 2:
                displayAllTransactions(transptr);
                break;

            case 3:
                displayRegularBuyers(sellerptr);
                break;

            case 4:
                printf("Enter Transaction ID to update: ");
                scanf("%s", transactionID);
                update_transaction(transptr, sellerptr, transactionID);
                break;

            case 5:
                printf("Enter Seller ID to calculate revenue: ");
                scanf("%s", sellerID);
                revenue = total_revenue_seller(transptr, sellerID);
                printf("Total Revenue for Seller %s: $%.2f\n", sellerID, revenue);
                printf("---------------------------------------------------\n");
                break;

            case 6:
                do {
                    printf("Enter Start Timestamp (YYYY-MM-DD HH:MM:SS): ");
                    scanf(" %[^\n]", start);
            
                    if (!is_valid_timestamp(start)) {
                        printf("Invalid format! Please enter in YYYY-MM-DD HH:MM:SS format.\n");
                    }
                } while (!is_valid_timestamp(start));
            
                do {
                    printf("Enter End Timestamp (YYYY-MM-DD HH:MM:SS): ");
                    scanf(" %[^\n]", end);
            
                    if (!is_valid_timestamp(end)) {
                        printf("Invalid format! Please enter in YYYY-MM-DD HH:MM:SS format.\n");
                    }
                } while (!is_valid_timestamp(end));
                between_transaction(start, end, transptr);
                break;

            case 7:
                list_of_seller(transptr, sellerptr);
                break;

            case 8:
                list_of_buyer(transptr, buyerptr);
                break;

            case 9:
                transptr = trans_sort(&transptr);
                temptransptr = transptr;
                displayAllTransactions(temptransptr);
                display_highest_energy(temptransptr);
                break;

            case 10:
                buyerptr = buyer_sort(&buyerptr);
                tempbuyer = buyerptr;
                printf("Energy sorted");
                list_of_buyer(transptr, tempbuyer);
                break;

            case 11:
                pairptr = pair_sort(&pairptr);
                temppairptr = pairptr;
                display_pair(temppairptr);
                break;

            case 12:
                printf("Exiting program...\n");
                writeSellersToFile(sellerptr, "sellertable.txt");
                writeTransactionsToFile(transptr, "energytrading.txt");
                cleanUpMemory(&transptr, &sellerptr, &buyerptr, &pairptr);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
//  gcc -o energy_trading main.c utils.c transactions.c sellers.c buyers.c pairs.c display.c cleaning.c fileoperation.c