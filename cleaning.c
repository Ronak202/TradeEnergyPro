#include "energy_trading.h"
// cleaning up the memeory
void cleanUpMemory(transaction_node** transHead, seller_node** sellerHead, buyer_node** buyerHead, pair_node** pairHead) {
    printf("Cleaning up memory...\n");

    // Free transaction list
    transaction_node* tempTrans;
    while (*transHead != NULL) {
        tempTrans = *transHead;
        *transHead = (*transHead)->next;
        free(tempTrans);
    }
    *transHead = NULL;

    // Free seller list, including regular buyers
    seller_node* tempSeller;
    while (*sellerHead != NULL) {
        tempSeller = *sellerHead;

        // Free regular buyers linked list
        regularBuyer* tempBuyer;
        while (tempSeller->regularBuyers != NULL) {
            tempBuyer = tempSeller->regularBuyers;
            tempSeller->regularBuyers = tempSeller->regularBuyers->next;
            free(tempBuyer);
        }

        *sellerHead = (*sellerHead)->next;
        free(tempSeller);
    }
    *sellerHead = NULL;

    // Free buyer list
    buyer_node* tempBuyerNode;
    while (*buyerHead != NULL) {
        tempBuyerNode = *buyerHead;
        *buyerHead = (*buyerHead)->next;
        free(tempBuyerNode);
    }
    *buyerHead = NULL;

    // Free pairs list
    pair_node* tempPair;
    while (*pairHead != NULL) {
        tempPair = *pairHead;
        *pairHead = (*pairHead)->next;
        free(tempPair);
    }
    *pairHead = NULL;

    printf("Memory cleanup complete.\n");
}