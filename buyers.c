#include "energy_trading.h"

buyer_node* findorcreate_buyer(buyer_node** buyerptr, char* buyerID, int amnt) {
    int flag = 0;
    buyer_node* ptr = *buyerptr;
    while (ptr != NULL && !flag) {
        if (strcmp(ptr->buyer_id, buyerID) == 0) {
            ptr->total_amt = ptr->total_amt + amnt;
            flag = 1;
        }
        if(flag == 0){
            ptr = ptr->next;
        }
    }
    buyer_node* newBuyer = (buyer_node*)malloc(sizeof(buyer_node));
    if(!flag){
        strcpy(newBuyer->buyer_id, buyerID);
        newBuyer->total_amt = amnt;
        newBuyer->next = *buyerptr;
        *buyerptr = newBuyer;
        ptr = newBuyer;
    }
    return ptr;
}
// list of buyer
void list_of_buyer(transaction_node *transptr,buyer_node* buyerptr)
{
    printf("\nTransactions Grouped by Buyer:\n");
    transaction_node* t_ptr=NULL;
    buyer_node* b_ptr=buyerptr;
    while(b_ptr!=NULL)
    {    printf("Buyer ID: %s Total_Amount:%d\n", b_ptr->buyer_id,b_ptr->total_amt);
         printf("-------------------------------------------------------------------------------------------------------\n");
         printf("| Transaction ID | Seller ID    | Energy Amount (kWh) | Price/kWh | Timestamp  |\n");
         printf("-------------------------------------------------------------------------------------------------------\n");
          t_ptr=transptr;
          while(t_ptr!=NULL)
          {
            if(strcmp(b_ptr->buyer_id,t_ptr->buyer_id)==0)
            {
                display_particular_detail(t_ptr,t_ptr->seller_id);
            }
            t_ptr=t_ptr->next;
          }
           printf("---------------------------\n");
           b_ptr=b_ptr->next;
    }
     printf("---------------------------------------------------\n");
}
// sort buyer acc to amount
buyer_node* merge(buyer_node* list1,buyer_node* list2){
    buyer_node* result,*ptr1,*ptr2,*tail;
    ptr1 = list1;
    ptr2 = list2;
    if(list1->total_amt < list2->total_amt){
    result = tail = list1;
    ptr1 = ptr1->next;
    }
    else{
    result = tail = list2;
    ptr2 = ptr2->next;
    }
    while((ptr1!=NULL)&&(ptr2!=NULL)){
    if(ptr1->total_amt < ptr2->total_amt){
    tail->next = ptr1;
    tail = ptr1;
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
    buyer_node* divide(buyer_node* list_ptr){
    buyer_node* nptr,*fast,*slow;
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
    buyer_node* buyer_sort(buyer_node** buyerptr){
    buyer_node* nptr;buyer_node* list_ptr;
    buyer_node* lptr;
    lptr =*buyerptr;
    list_ptr = *buyerptr;
    if(buyerptr!=NULL && lptr->next!=NULL){
    nptr = divide(list_ptr);
    list_ptr = buyer_sort(&list_ptr);
    nptr = buyer_sort(&nptr);
    lptr = merge(list_ptr,nptr);
    }
    return lptr;
    }
   