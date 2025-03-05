#include "energy_trading.h"
transaction_node* createTransactionNode(char* transactionID, char* buyerID, char* sellerID, int amt_energy, float price, const char* date_time) {
    transaction_node* newtransaction = (transaction_node*)malloc(sizeof(transaction_node));
    if (!newtransaction) {
        return NULL;
    }
    strcpy(newtransaction->transaction_id, transactionID);
    strcpy(newtransaction->buyer_id, buyerID);
    strcpy(newtransaction->seller_id, sellerID);
    newtransaction->amount_energy = amt_energy;
    newtransaction->price_kwh = price;
    strcpy(newtransaction->timestamp, date_time);
    newtransaction->next = NULL;
    return newtransaction;
}

void add_transaction(transaction_node** transptr, seller_node** sellerptr, buyer_node** buyerptr, pair_node** pairptr,
                      char* transactionID, char* sellerID, char* buyerID, int amt_energy, char* date_time) {
    
    seller_node* seller = findorcreate_seller(sellerptr, sellerID);
    buyer_node* buyer = findorcreate_buyer(buyerptr, buyerID, amt_energy);
    pair_node* pair = findOrCreate_pair(pairptr, buyerID, sellerID);

    float price = (amt_energy > 300) ? seller->price_kwh_gt_300 : seller->price_kwh_lt_300;
    transaction_node* newtransaction = createTransactionNode(transactionID, buyerID, sellerID, amt_energy, price, date_time);
    
    newtransaction->next = *transptr;
    *transptr = newtransaction;

    pair->number_transactions++;

    if (pair->number_transactions > 5) {
        regularBuyer* regBuyer = seller->regularBuyers;
        int isRegular = 0;

        while (regBuyer != NULL && !isRegular) {
            if (strcmp(regBuyer->buyer_id, buyerID) == 0) {
                isRegular = 1;  
            } else {
                regBuyer = regBuyer->next; 
            }
        }

        if (!isRegular) {
            regularBuyer* newRegular = (regularBuyer*)malloc(sizeof(regularBuyer));
            if (newRegular!=NULL)
            {
            strcpy(newRegular->buyer_id, buyerID);
            newRegular->next = seller->regularBuyers;
            seller->regularBuyers = newRegular;
            }
        }
    }
}
// Function to update transaction details by transaction ID
void update_transaction(transaction_node* transptr, seller_node* sellerptr, char* transactionID) {
    transaction_node* temp = transptr;

    while (temp != NULL) {
        if (strcmp(temp->transaction_id, transactionID) == 0) {
            int new_amount;
            float new_price;
            char choice;
            printTableHeader();
            printTableRow(temp);

            // Ask user if they want to update the energy amount
            printf("\nDo you want to update the amount of energy? (y/n): ");
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                printf("Enter new amount of energy: ");
                scanf("%d", &new_amount);
                temp->amount_energy = new_amount;

            
                seller_node* seller = sellerptr;
                while (seller != NULL && strcmp(seller->seller_id, temp->seller_id) != 0)
               {
                seller = seller->next;  
               }

              if (seller != NULL) {
             temp->price_kwh = (temp->amount_energy > 300) ? seller->price_kwh_gt_300 : seller->price_kwh_lt_300;
             }
            }

            printf("\nDo you want to update the price per kWh manually? (y/n): ");
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                printf("Enter new price per kWh: ");
                scanf("%f", &new_price);
                temp->price_kwh = new_price;
            }

            printf("\nTransaction %s updated successfully!\n", transactionID);
            printf("Updated Amount: %d kWh\n", temp->amount_energy);
            printf("Updated Price per kWh: %.2f\n", temp->price_kwh);
            printf("\nUpdated Transaction::\n");
            printTableHeader();
            printTableRow(temp);
            return;
        }
        temp = temp->next;
    }
    printf("Transaction ID %s not found!\n", transactionID);
    printf("---------------------------------------------------\n");
}
   // sort transaction acc to amount of energy!!
   transaction_node* trans_merge(transaction_node* list1,transaction_node* list2){
    transaction_node* result,*ptr1,*ptr2,*tail;
    ptr1 = list1;
    ptr2 = list2;
    if(list1->amount_energy < list2->amount_energy){
    result = tail = list1;
    ptr1 = ptr1->next;
    }
    else{
    result = tail = list2;
    ptr2 = ptr2->next;
    }
    while((ptr1!=NULL)&&(ptr2!=NULL)){
    if(ptr1->amount_energy < ptr2->amount_energy){
    tail->next = ptr1;
    tail=ptr1;
    ptr1 = ptr1->next;
    }
    else{
    tail->next = ptr2;
    tail=ptr2;
    ptr2 = ptr2->next;
    }
    }
    if(ptr1!=NULL){
    tail->next = ptr1;
    }
    else{
    tail->next = ptr2;
    }
    return result;
    }
    
    transaction_node* trans_divide(transaction_node* list_ptr){
    transaction_node* nptr,*fast,*slow;
    fast = slow = list_ptr;
    fast = fast->next->next;
    while(fast!=NULL){
    slow=slow->next;
    fast=fast->next;
    if(fast!=NULL){
    fast=fast->next;
    }
    }
    nptr=slow->next;
    slow->next = NULL;
    return nptr;
    }
    
    transaction_node* trans_sort(transaction_node** transptr){
    transaction_node* nptr;transaction_node* list_ptr;
    transaction_node* lptr;
    lptr =*transptr;
    list_ptr = *transptr;
    if(transptr!=NULL && lptr->next!=NULL){
    nptr = trans_divide(list_ptr);
    list_ptr = trans_sort(&list_ptr);
    nptr = trans_sort(&nptr);
    lptr = trans_merge(list_ptr,nptr);
    }
    return lptr;
    }
    // display highest amount transaction
    void display_highest_energy(transaction_node* ptr) {
        if (ptr == NULL) {
            printf("No transactions available.\n");
            return;
        }
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
    
        int max_energy = ptr->amount_energy;  
        transaction_node* temp = ptr;      
    
        printTableHeader();
        while (temp != NULL) {
            if (temp->amount_energy == max_energy) {
                printTableRow(temp);
            }
            temp = temp->next;
        }  
    }
    
