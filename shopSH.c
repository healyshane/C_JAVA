//SHOP ASSIGNMENT IN C.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Product {
	char* name;
	double price;
};

struct ProductStock {
	struct Product product;
	int quantity;
};

struct Shop {
	double cash;
	struct ProductStock stock[20];
	int index;
};

struct Customer {
	char* name;
	double budget;
	struct ProductStock shoppingList[10];
	int index;
};


struct Customer createCustomer()
{
		struct Customer customer = {"John", 200};
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("customer1.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
		char *name = strtok(line, ",");
		char *qty = strtok(NULL, ",");
		int quantity = atoi(qty);

		printf("Name of Item %s Quantity %d \n", name, quantity);

    }
return customer;
}


int startup()
{
	printf("THE C SHOP ");
	printf("-------------\n");
	char* choice = (char*) malloc(10 * sizeof(char));
	printf("Do you want LIVE mode, y/n?\n");
	scanf("%s", choice);

	if (strcmp(choice, "y")==0)
	{
		printf("product by name, specify a quantity, and pay for it.\n");

		printf("The product of 1 to %d, was %d\n");

		return 1;

	} else if (strcmp(choice, "n")==0)
	{
		createCustomer();
		printf("Enter print of Shop or run program from CSVs\n");
		return 2;
	}

}







int main()
{
int pro = startup();
printf("XXX, :", pro);




	return 0;

}



//write a method which loops through the Customers shopping list and for each item looks
// for the price from the shop, from there you could set the price for the customer to
//  match the shop or you could do all the math to figure out if the customer can buy
