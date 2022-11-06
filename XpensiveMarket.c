/*  Isaac Pellegrini Alencar
    SOFTWARE DEVELOPER
    Project 01 - MARKET
    Class - LP1
    */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX 999

typedef struct {
    int productCode;
    int productQty;
    float buyPrice;
    float sellPrice;
    char productName[32];
}PRODUCT;

PRODUCT registry[MAX]; 

void arrayCleaner ()
{
    for(int i=0;i<999;i++)
    {
        registry[i].productCode = -1;
    }
}

int searchCode (int toSearch) 
{
    for(int i=0;i<999;i++)
    {
        if(toSearch==registry[i].productCode)
        {
            return i;
        }
    }
    return -1;
}

void addMoreProducts (int n, float tempBalance, float *balance) 
{
    int qty;
    printf("\n\nProduct: %s. Stock Amount: %d.", registry[n].productName, registry[n].productQty);
    printf("\nBuying Price: $%.2f.", registry[n].buyPrice);
    do{
        printf("\nInsert amount to buy: ");
        scanf("%d", &qty);
        if(qty<=0)
        {
            printf("\nYou inserted an invalid ammount!\nPlease try again setting a valid quantity.\n");
        }
    }while(qty<=0);
    
    tempBalance = qty * registry[n].buyPrice;

    if(tempBalance < *balance)
    {
        *balance = *balance - (registry[n].productQty * registry[n].buyPrice);
        registry[n].productQty = registry[n].productQty + qty;
        system("cls");
        printf("Added products with SUCCESS!\n\n", registry[n].productName);
    }
    else
    {
        printf("\nYou are spending more than the available balance!\nPlease try again setting a valid quantity.\n\n");
    }
}

void addProducts (int *j, float *balance) 
{
    int productID;
    int n=*j;
    int arrayIndex=-1; 
    float tempBalance = *balance;
    float reinsertBalance = *balance;
    do{
        printf("Insert the Product ID: ");
        scanf("%d", &productID);
        if (productID<=0)
        {
            printf("\nYou inserted a invalid ID! Try again.\n\n");
        }
    }while(productID<=0);

    arrayIndex=searchCode(productID);
    if(arrayIndex>-1)
    {
        n=arrayIndex;
        printf("\nYou inserted an existent ID. Adding amount to stock.");
        addMoreProducts(n, tempBalance, &reinsertBalance);
        *balance = reinsertBalance; 
        return;
    }
    printf("Insert the buying price: ");
    scanf("%f", &registry[n].buyPrice);
    do{
        printf("Insert bought amount: ");
        scanf("%d", &registry[n].productQty);
        if(registry[n].productQty<=0) 
        {
            printf("\nYou inserted an invalid quantity!\n");
        }
    }while(registry[n].productQty<=0);
    tempBalance = registry[n].productQty * registry[n].buyPrice;

    if(tempBalance < *balance)
    {
        *balance = *balance - (registry[n].productQty * registry[n].buyPrice);
    }
    else 
    {
        printf("\nYou are spending more than the available balance!\nPlease try again setting a valid quantity.\n\n");
        return;
    }

    printf("Insert the product name: ");
    fflush(stdin);
    gets(registry[n].productName);

    *j = *j + 1;
    registry[n].productCode=productID;
    registry[n].sellPrice=2*registry[n].buyPrice;

    system("cls");
    printf("Product %s inserted with SUCCESS!\n\n", registry[n].productName);
}

void sellProducts (int j, float *balance, float *profit)
{
    int i, n;
    int productCode;
    int typeQty;
    float total=0, subtotal=0;
    int qty;
    printf("Stock:\n");
    for(i=0;i<j;i++) 
    {
        printf("\nProduct: %s. Product code: %d. Stock Amount: %d.", registry[i].productName, registry[i].productCode, registry[i].productQty);
    }
    printf("\n\nHow many different products are being sold? ");
    scanf("%d",&typeQty);
    for(i=1;i<=typeQty;i++)
    {
        printf("Insert the %d Product ID being sold: ", i);
        scanf("%d",&productCode);
        n=searchCode(productCode); 
        if(n<0)
        {
            printf("\nThis ID is not registered! Please, register ir and try again.\n\n"); 
            break;
        }
        do{
            printf("\nProduct: %s.\nAmount: ", registry[n].productName);
            scanf("%d",&qty);
            if(qty>registry[n].productQty)
            {
                printf("\nYou inserted a higher quantity than existent stock!\nInsert a new value as registered above.\n");
            }
        }while(qty>registry[n].productQty);
        
        registry[n].productQty = registry[n].productQty - qty;
        printf("\nUnity Price: $ %.2f", registry[n].sellPrice); 
        subtotal=registry[n].sellPrice * qty;
        printf("\nSubtotal: %.2f", subtotal);
        total = total + subtotal;
        printf("\nTotal Price: %.2f\n\n", total); 
    }
    *profit = *profit + (total/2); 
    *balance = *balance + total;
}

void stockCheck (int j) 
{
    int i;
    for(i=0;i<j;i++) 
    {
        printf("\nProduct: %s. Product ID: %d. Stock Amount: %d.", registry[i].productName, registry[i].productCode, registry[i].productQty);
        printf("\nBuying Price: $%.2f. Selling Price: $%.2f.\n", registry[i].buyPrice, registry[i].sellPrice);
    }
    printf("\n");
}

int main() 
{
    arrayCleaner();

    int on=1, option=0;
    int arrayReader=0; 
    float balance = 3000;
    float profit = 0;

    printf("$$ Welcome to X-Pensive Market $$\n\n"); 

    while(on)
    {
            printf("Menu: \n\n1 - Insert product in Stock \n2 - Sell \n3 - Stock check \n4 - Balance check \n5 - Profit check \n6 - Shutdown app \n\nEnter >> ");
            scanf("%d", &option);
            while(option<1 || option>6) 
            {
                printf("\nInvalid option!\nInsert correct option: ");
                scanf("%d", &option);
            }
            if (option==1) 
            {
                system("cls");
                addProducts(&arrayReader, &balance);
            }
            else if (option==2) 
            {
                if (arrayReader==0)
                {
                    system("cls");
                    printf("There is no registered product!! Please register on option 1.\n\n"); 
                }
                else
                {
                    system("cls");
                    sellProducts (arrayReader, &balance, &profit);
                }
            }
            else if (option==3)
            {
                if (arrayReader==0)
                {
                    system("cls");
                    printf("There is no registered product!! Please register on option 1.\n\n");
                }
                else
                {
                    system("cls");
                    printf("Updated Stock:\n");
                    stockCheck(arrayReader);
                }
            }
            else if (option==4) 
            {
                system("cls");
                printf("Actual Balance: %.2f\n\n", balance);
            }
            else if (option==5)
            {
                system("cls");
                printf("Actual profit: %.2f\n\n", profit);
            }
            else if (option==6) 
            {
                on=0;
            }
    }
    printf("\nThank you for using this App.\n\nDeveloped by:\nIsaac Alencar\n");
    return 1;
}

