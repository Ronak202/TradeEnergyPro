#include "energy_trading.h"

int validT(char* s) {
    int ans=1;
    if (strlen(s) != 5 || s[0] != 'T' || s[1] == '0') {
        ans=0;
    }

    for (int i = 1; s[i] != '\0' && ans; i++) {
        if (s[i] < '0' || s[i] > '9') {
            ans=0;
        }
    }
    
    return ans;  // Valid "TXXXX" format
}
int validS(char* s){
    int ans=1;
    if(strlen(s)!=5 || s[0]!='S' || s[1]=='0'){
        ans=0;
    }
    if(ans){
        for(int i=1;s[i]!='\0' && ans;i++){
        if(s[i] < '0' || s[i]>'9'){
            ans=0;
        }
        }
    }
    return ans;
    
}

int validB(char* s){
    int ans=1;
    if(strlen(s)!=5 || s[0]!='B' || s[1]=='0'){
        ans=0;
    }
    if(ans){
        for(int i=1;s[i]!='\0' && ans;i++){
        if(s[i] < '0' || s[i]>'9'){
            ans=0;
        }
        }
    }
    return ans;
    
}
// uniqueness for trans id
int isUniqueTransactionID(char *transactionID, transaction_node* transptr) {
    transaction_node *temp = transptr;
    while (temp != NULL) {
        if (strcmp(temp->transaction_id, transactionID) == 0) {
            printf("Error: Transaction ID already exists. Try again.\n");
            return 0;  // Not unique
        }
        temp = temp->next;
    }
    return 1;  // Unique
}
void getCurrentTimestamp(char* buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, DATE_SIZE, "%Y-%m-%d %H:%M:%S", t);
}
// constraint on price
float get_valid_price(const char* prompt) {
    float price;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &price) == 1 && price > 0) {
            return price;
        }
        printf("Invalid price! Price must be greater than 0.\n");
        
        // Clear input buffer
        while (getchar() != '\n');
    }
}
int is_valid_timestamp(const char *timestamp) {
    int year, month, day, hour, minute, second;
    char extra;

    // Check format using sscanf extract value from string
    if (sscanf(timestamp, "%4d-%2d-%2d %2d:%2d:%2d%c", 
               &year, &month, &day, &hour, &minute, &second, &extra) != 6) {
        return 0; 
    }

    // Basic range checks
    if (year < 1900 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    if (hour < 0 || hour > 23) return 0;
    if (minute < 0 || minute > 59) return 0;
    if (second < 0 || second > 59) return 0;

    return 1; // Valid timestamp
}