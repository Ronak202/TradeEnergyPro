#include "energy_trading.h"
// Find or create a buyer-seller pair
pair_node* findOrCreate_pair(pair_node** pairptr, char* buyerID, char* sellerID) {
    pair_node* temp = *pairptr;
    while (temp != NULL) {
        if (strcmp(temp->buyer_id, buyerID) == 0 && strcmp(temp->seller_id, sellerID) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    pair_node* newpair = (pair_node*)malloc(sizeof(pair_node));
    if (!newpair) return NULL;

    strcpy(newpair->buyer_id, buyerID);
    strcpy(newpair->seller_id, sellerID);
    newpair->number_transactions = 0;
    newpair->next = *pairptr;
    *pairptr = newpair;
    return newpair;
}
// Sort Seller/buyer pairs in decreasing order of the number of transactions
pair_node* pair_merge(pair_node* list1,pair_node* list2){
    pair_node* result,*ptr1,*ptr2,*tail;
    ptr1 = list1;
    ptr2 = list2;
    if(list1->number_transactions > list2->number_transactions){
    result = tail = list1;
    ptr1 = ptr1->next;
    }
    else{
    result = tail = list2;
    ptr2 = ptr2->next;
    }
    while((ptr1!=NULL)&&(ptr2!=NULL)){
    if(ptr1->number_transactions > ptr2->number_transactions){
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
    pair_node* pair_divide(pair_node* list_ptr){
    pair_node* nptr,*fast,*slow;
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
    
    pair_node* pair_sort(pair_node** pairptr){
    pair_node* nptr;pair_node* list_ptr;
    pair_node* lptr;
    lptr =*pairptr;
    list_ptr = *pairptr;
    if(pairptr!=NULL && lptr->next!=NULL){
    nptr = pair_divide(list_ptr);
    list_ptr = pair_sort(&list_ptr);
    nptr = pair_sort(&nptr);
    lptr = pair_merge(list_ptr,nptr);
    }
    return lptr;
    }
    void display_pair(pair_node* lptr){
        pair_node* temp = lptr;
        while(temp!=NULL){
            printf("Buyer ID: %s\n", temp->buyer_id);
            printf("Seller ID: %s\n", temp->seller_id);
            printf("Number of Transactions: %d \n", temp->number_transactions);
            printf("---------------------------\n");
            temp = temp->next;
        }
    }