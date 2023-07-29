#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct normalUser
{
    int userID;
    char name[30];
    char password[10];
    int account_no;
    float balance;
    char status[20];
} normalUser;

typedef struct jointAccountUser
{
    int userID;
    char name1[30];
    char name2[30];
    char password[10];
    int account_no;
    float balance;
    char status[20];
} jointAccountUser;

typedef struct admin
{
    int userID;
    char name[30];
    char password[10];
} admin;

void NormalUserLogin(int sd);
void JointUserLogin(int sd);
void AdminLogin(int sd);
void showMenu(int sd);
void deposit(int sd);
void withdraw(int sd);
void balanceEnquiry(int sd);
void changePassword(int sd);
void viewDetails(int sd);
void addAccount(int sd);
void deleteAccount(int sd);
void modifyAccount(int sd);
void searchAccount(int sd);

int choice, currId;

void selectChoice(int sd)
{
    while (1)
    {
        printf("How do you want to login ?\n");
        printf("1 : Normal-User Login\n");
        printf("2 : Joint Account-User Login\n");
        printf("3 : Admin Login\n");

        scanf("%d", &choice);

        if (choice == 1)
        {
            NormalUserLogin(sd);
            break;
        }
        else if (choice == 2)
        {
            JointUserLogin(sd);
            break;
        }
        else if (choice == 3)
        {
            AdminLogin(sd);
            break;
        }
        else
            printf("Invalid choice!\n");
    }
    return;
}

void showMenu(int sd)
{
    int select;
    if (choice == 1 || choice == 2)
    {
        printf("What do you want to do ?\n");
        printf("1 : Deposit\n");
        printf("2 : Withdraw\n");
        printf("3 : Balance Enquiry\n");
        printf("4 : Password Change\n");
        printf("5 : View Details\n");
        printf("6 : Exit\n");

        scanf("%d", &select);

        switch (select)
        {
        case 1:
            deposit(sd);
            break;
        case 2:
            withdraw(sd);
            break;
        case 3:
            balanceEnquiry(sd);
            break;
        case 4:
            changePassword(sd);
            break;
        case 5:
            viewDetails(sd);
            break;
        case 6:
            write(sd, &select, sizeof(select));
            exit(0);
        default:
            printf("Invalid choice !\n");
            showMenu(sd);
            break;
        }
    }
    else if (choice == 3)
    {
        printf("What do you want to do ?\n");
        printf("1 : Add Account\n");
        printf("2 : Delete Account\n");
        printf("3 : Modify Account\n");
        printf("4 : Search Account\n");
        printf("5 : Exit\n");

        scanf("%d", &select);

        switch (select)
        {
        case 1:
            addAccount(sd);
            break;
        case 2:
            deleteAccount(sd);
            break;
        case 3:
            modifyAccount(sd);
            break;
        case 4:
            searchAccount(sd);
            break;
        case 5:
            write(sd, &select, sizeof(int));
            exit(0);
        default:
            printf("Invalid choice !\n");
            showMenu(sd);
            break;
        }
    }
}

void NormalUserLogin(int sd)
{
    bool result;
    normalUser currUser;
    printf("Enter User ID : \n");
    scanf("%d", &currUser.userID);
    currId = currUser.userID;
    printf("Enter Password : \n");
    scanf("%s", currUser.password);

    write(sd, &choice, sizeof(int));
    write(sd, &currUser, sizeof(normalUser));

    read(sd, &result, sizeof(result));

    if (!result)
    {
        printf("Invalid login !\n");
        selectChoice(sd);
    }
    else
    {
        printf("Succesfully logged in\n");
    }
    return;
}

void JointUserLogin(int sd)
{
    bool result;
    jointAccountUser currUser;
    printf("Enter User ID : \n");
    scanf("%d", &currUser.userID);
    currId = currUser.userID;
    printf("Enter Password : \n");
    scanf("%s", currUser.password);

    write(sd, &choice, sizeof(int));
    write(sd, &currUser, sizeof(jointAccountUser));

    read(sd, &result, sizeof(result));

    if (!result)
    {
        printf("Invalid login !\n");
        selectChoice(sd);
    }
    else
    {
        printf("Succesfully logged in\n");
    }
    return;
}

void AdminLogin(int sd)
{
    bool result;
    admin currUser;
    printf("Enter User ID : \n");
    scanf("%d", &currUser.userID);
    currId = currUser.userID;
    printf("Enter Password : \n");
    scanf("%s", currUser.password);

    write(sd, &choice, sizeof(int));
    write(sd, &currUser, sizeof(admin));

    read(sd, &result, sizeof(result));

    if (!result)
    {
        printf("Invalid login !\n");
        selectChoice(sd);
    }
    else
    {
        printf("Succesfully logged in\n");
    }
    return;
}

void deposit(int sd)
{
    float amount;
    int select = 1;
    bool result;

    printf("Enter the amount to deposit :\n");
    scanf("%f", &amount);

    while (amount <= 0)
    {
        printf("Enter a valid amount !\n");
        printf("Enter the amount to deposit :\n");
        scanf("%f", &amount);
    }

    write(sd, &select, sizeof(int));
    write(sd, &amount, sizeof(float));

    read(sd, &result, sizeof(result));

    if (!result)
    {
        printf("Error !\n");
    }
    else
    {
        printf("Succesfully deposited !\n");
    }
    showMenu(sd);
    return;
}

void withdraw(int sd)
{
    float amount;
    int select = 2;
    bool result;

    printf("Enter the amount to withdraw :\n");
    scanf("%f", &amount);

    while (amount <= 0)
    {
        printf("Enter a valid amount !\n");
        printf("Enter the amount to withdraw :\n");
        scanf("%f", &amount);
    }

    write(sd, &select, sizeof(int));
    write(sd, &amount, sizeof(float));

    read(sd, &result, sizeof(result));

    if (!result)
    {
        printf("Error !\n");
    }
    else
    {
        printf("Succesfully withdrawed!\n");
    }
    showMenu(sd);
    return;
}

void balanceEnquiry(int sd)
{
    float amount;
    int select = 3;
    int len;

    write(sd, &select, sizeof(int));

    len = read(sd, &amount, sizeof(float));

    printf("Available Balance is Rs.");
    printf("%0.2f\n", amount);

    showMenu(sd);
    return;
}

void changePassword(int sd)
{
    int select = 4;
    char newPassword[10];
    bool result;

    printf("Enter the new password :\n");
    scanf("%s", newPassword);

    write(sd, &select, sizeof(int));
    write(sd, newPassword, sizeof(newPassword));

    read(sd, &result, sizeof(result));

    if (!result)
    {
        printf("Error !\n");
    }
    else
    {
        printf("Succesfully changed password !\n");
    }
    showMenu(sd);
    return;
}

void viewDetails(int sd)
{
    int select = 5;

    write(sd, &select, sizeof(int));

    if (choice == 1)
    {
        normalUser currUser1;
        read(sd, &currUser1, sizeof(normalUser));

        printf("User ID : %d\n", currUser1.userID);
        printf("Name : %s\n", currUser1.name);
        printf("Account Number : %d\n", currUser1.account_no);
        printf("Available Balance : Rs.%0.2f\n", currUser1.balance);
        printf("Status : %s\n\n", currUser1.status);
    }
    else if (choice == 2)
    {
        jointAccountUser currUser2;
        read(sd, &currUser2, sizeof(jointAccountUser));

        printf("User ID : %d\n", currUser2.userID);
        printf("Main Account Holder's Name : %s\n", currUser2.name1);
        printf("Other Account Holder's Name : %s\n", currUser2.name2);
        printf("Account Number : %d\n", currUser2.account_no);
        printf("Available Balance : Rs.%0.2f\n", currUser2.balance);
        printf("Status : %s\n\n", currUser2.status);
    }
    showMenu(sd);
    return;
}

void addAccount(int sd)
{
    int select = 1;
    int type;
    bool result;

    write(sd, &select, sizeof(int));

    printf("Enter the type of account to add (1: Normal Account 2: Joint Account) : \n");
    scanf("%d", &type);

    write(sd, &type, sizeof(int));

    if (type == 1)
    {
        normalUser addUser1;
        printf("Enter name of the account holder : \n");
        scanf(" %[^\n]", addUser1.name);
        printf("Enter Password : \n");
        scanf("%s", addUser1.password);
        printf("Initial Deposit : Rs.\n");
        scanf("%f", &addUser1.balance);
        write(sd, &addUser1, sizeof(normalUser));
    }

    if (type == 2)
    {
        jointAccountUser addUser2;
        printf("Enter name of the primary account holder : \n");
        scanf(" %[^\n]", addUser2.name1);
        printf("Enter name of the other account holder : \n");
        scanf(" %[^\n]", addUser2.name2);
        printf("Enter Password : \n");
        scanf("%s", addUser2.password);
        printf("Initial Deposit : Rs.\n");
        scanf("%f", &addUser2.balance);
        write(sd, &addUser2, sizeof(jointAccountUser));
    }

    read(sd, &result, sizeof(result)); // from the server

    if (!result)
    {
        printf("Error !\n");
    }
    else
    {
        printf("Succesfully added the account !\n");
    }
    showMenu(sd);
    return;
}

void deleteAccount(int sd)
{
    int select = 2;
    int type, userID;
    bool result;

    write(sd, &select, sizeof(int));

    printf("Enter the type of account (1: Normal Account 2: Joint Account) : \n");
    scanf("%d", &type);

    write(sd, &type, sizeof(int));

    printf("User ID : \n");
    scanf("%d", &userID);
    write(sd, &userID, sizeof(int));

    read(sd, &result, sizeof(result));

    if (!result)
    {
        printf("Error !\n");
    }
    else
    {
        printf("Succesfully deleted the account !\n");
    }
    showMenu(sd);
    return;
}

void modifyAccount(int sd)
{
    int select = 3;
    int type;
    bool result;

    write(sd, &select, sizeof(int));

    printf("Enter the type of account (1: Normal Account 2: Joint Account) : \n");
    scanf("%d", &type);

    write(sd, &type, sizeof(int));

    if (type == 1)
    {
        normalUser modUser1;
        printf("User ID : \n");
        scanf("%d", &modUser1.userID);
        printf("Account Number : \n");
        scanf("%d", &modUser1.account_no);
        printf("New Name of the account holder : \n");
        scanf(" %[^\n]", modUser1.name);
        printf("New Password : \n");
        scanf("%s", modUser1.password);
        printf("New Balance : \n");
        scanf("%f", &modUser1.balance);
        write(sd, &modUser1, sizeof(normalUser));
    }

    if (type == 2)
    {
        jointAccountUser modUser2;
        printf("User ID : \n");
        scanf("%d", &modUser2.userID);
        printf("Account Number : \n");
        scanf("%d", &modUser2.account_no);
        printf("New Name of the primary account holder : \n");
        scanf(" %[^\n]", modUser2.name1);
        printf("New Name of the other account holder : \n");
        scanf(" %[^\n]", modUser2.name2);
        printf("New Password(max 10 characters) : \n");
        scanf("%s", modUser2.password);
        printf("New Balance : \n");
        scanf("%f", &modUser2.balance);
        write(sd, &modUser2, sizeof(jointAccountUser));
    }

    read(sd, &result, sizeof(result));

    if (!result)
    {
        printf("Error !\n");
    }
    else
    {
        printf("Succesfully modified the account !\n");
    }
    showMenu(sd);
    return;
}

void searchAccount(int sd)
{
    int select = 4;
    int type, len;
    bool result;

    write(sd, &select, sizeof(int));

    printf("Enter the type of account (1: Normal Account 2: Joint Account) : \n");
    scanf("%d", &type);

    write(sd, &type, sizeof(int));

    if (type == 1)
    {
        normalUser searchUser1;
        int userID;
        printf("User ID : \n");
        scanf("%d", &userID);
        write(sd, &userID, sizeof(int));

        len = read(sd, &searchUser1, sizeof(normalUser));
        if (len == 0)
        {
            printf("Wrong User ID !\n");
        }
        else
        {
            printf("User ID : %d\n", searchUser1.userID);
            printf("Name : %s\n", searchUser1.name);
            printf("Account Number : %d\n", searchUser1.account_no);
            printf("Available Balance : Rs.%0.2f\n", searchUser1.balance);
            printf("Status : %s\n\n", searchUser1.status);
        }
    }

    if (type == 2)
    {
        jointAccountUser searchUser2;
        int userID1;
        printf("User ID : \n");
        scanf("%d", &userID1);
        write(sd, &userID1, sizeof(int));

        len = read(sd, &searchUser2, sizeof(jointAccountUser));
        if (len == 0)
        {
            printf("Wrong User ID !\n");
        }
        else
        {
            printf("User ID : %d\n", searchUser2.userID);
            printf("Main Account Holder's Name : %s\n", searchUser2.name1);
            printf("Other Account Holder's Name : %s\n", searchUser2.name2);
            printf("Account Number : %d\n", searchUser2.account_no);
            printf("Available Balance : Rs.%0.2f\n", searchUser2.balance);
            printf("Status : %s\n\n", searchUser2.status);
        }
    }
    showMenu(sd);
    return;
}

int main()
{
    struct sockaddr_in server;
    int sd, msgLength;
    char buff[100];
    char result;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // same machine
    server.sin_port = htons(5555);
    connect(sd, (struct sockaddr *)&server, sizeof(server));

    selectChoice(sd);
    showMenu(sd);

    close(sd);

    return 0;
}
