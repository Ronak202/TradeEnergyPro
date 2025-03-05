#include "energy_trading.h"
// find or create seller
seller_node* findorcreate_seller(seller_node** sellerptr, char* sellerID) {
    int flag = 0;
    seller_node* ptr = *sellerptr;
    while (ptr != NULL && !flag) {
        if (strcmp(ptr->seller_id, sellerID) == 0) {
            flag=1;
        }
        if(flag==0)
        {
            ptr = ptr->next;
        }
    }
    seller_node* newSeller = (seller_node*)malloc(sizeof(seller_node));
    if(!flag){
    strcpy(newSeller->seller_id, sellerID);
    newSeller->price_kwh_lt_300 = get_valid_price(
        "Enter rate for seller below 300 kWh: ");
    newSeller->price_kwh_gt_300 = get_valid_price(
        "Enter rate for seller above 300 kWh: ");
    newSeller->regularBuyers = NULL;
    newSeller->next = *sellerptr;
    *sellerptr = newSeller;
    ptr = newSeller;
    }
    return ptr;
}
// display regylar buyer
void displayRegularBuyers(seller_node* sellerptr) {
    printf("\nRegular Buyers:\n");
    printf("---------------------------------------------------\n");
    printf("| %-10s | %-30s |\n", "Seller ID", "Regular Buyers");
    printf("---------------------------------------------------\n");
    while (sellerptr != NULL) {
        regularBuyer* temp = sellerptr->regularBuyers;
        printf("| %-10s | ", sellerptr->seller_id);
        while (temp != NULL) {
            printf("%-10s ", temp->buyer_id);
            temp = temp->next;
        }
        printf("\n");
        sellerptr = sellerptr->next;
    }
    printf("---------------------------------------------------\n");
}
// total revenue by particular seller
float total_revenue_seller(transaction_node *transptr,char *sellerID)
{
    transaction_node* ptr=transptr;
    float total_revenue=0;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->seller_id,sellerID)==0)
        {
            total_revenue=total_revenue+(ptr->amount_energy)*(ptr->price_kwh);
        }
        ptr=ptr->next;
    }
    return total_revenue;
}
// list of seller
void list_of_seller(transaction_node *transptr,seller_node* sellerptr)
{
     printf("\nTransactions Grouped by Seller:\n");
    transaction_node* t_ptr=NULL;
    seller_node* s_ptr=sellerptr;
    while(s_ptr!=NULL)
    {
        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("Seller ID: %s\n", s_ptr->seller_id);
        printf("| Transaction ID | Buyer ID    | Energy Amount (kWh) | Price/kWh | Timestamp  |\n");
        printf("-------------------------------------------------------------------------------------------------------\n");
        t_ptr=transptr;
          while(t_ptr!=NULL)
          {
            if(strcmp(s_ptr->seller_id,t_ptr->seller_id)==0)
            {
                display_particular_detail(t_ptr,t_ptr->buyer_id);
            }
            t_ptr=t_ptr->next;
          }
           printf("---------------------------\n");
           s_ptr=s_ptr->next;
    }
     printf("---------------------------------------------------\n");
}
