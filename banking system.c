#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[100];
    float balance;
};

void createAccount() {
    struct Account acc;
    FILE *fp;

    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);
    printf("Enter Name: ");
    getchar(); 
    fgets(acc.name, 100, stdin);
    acc.name[strcspn(acc.name, "\n")] = 0; 
    printf("Enter Initial Deposit Amount: ");
    scanf("%f", &acc.balance);

    fp = fopen("accounts.dat", "rb");
    if (fp != NULL) {
        struct Account temp;
        while (fread(&temp, sizeof(struct Account), 1, fp)) {
            if (temp.accountNumber == acc.accountNumber) {
                printf("Account with this number already exists!\n");
                fclose(fp);
                return;
            }
        }
        fclose(fp);
    }

    fp = fopen("accounts.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&acc, sizeof(struct Account), 1, fp);
    fclose(fp);

    printf("Account created successfully!\n");
}

int main() {
    createAccount();
    return 0;
}
