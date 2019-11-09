#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//adding below code allows getline function to work
ssize_t getdelim(char **linep, size_t *n, int delim, FILE *fp){
    int ch;
    size_t i = 0;
    if(!linep || !n || !fp){
        errno = EINVAL;
        return -1;
    }
    if(*linep == NULL){
        if(NULL==(*linep = malloc(*n=128))){
            *n = 0;
            errno = ENOMEM;
            return -1;
        }
    }
    while((ch = fgetc(fp)) != EOF){
        if(i + 1 >= *n){
            char *temp = realloc(*linep, *n + 128);
            if(!temp){
                errno = ENOMEM;
                return -1;
            }
            *n += 128;
            *linep = temp;
        }
        (*linep)[i++] = ch;
        if(ch == delim)
            break;
    }
    (*linep)[i] = '\0';
    return !i && ch == EOF ? -1 : i;
}
ssize_t getline(char **linep, size_t *n, FILE *fp){
    return getdelim(linep, n, '\n', fp);
}

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


struct Shop createAndStockShop()
{
	struct Shop shop = { 200 };
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s IS A LINE", line);
		char *n = strtok(line, ",");
		char *p = strtok(NULL, ",");
		char *q = strtok(NULL, ",");
		int quantity = atoi(q);
		double price = atof(p);
		char *name = malloc(sizeof(char) * 50);
		strcpy(name, n);
		struct Product product = { name, price };
		struct ProductStock stockItem = { product, quantity };
		shop.stock[shop.index++] = stockItem;
	  }

	return shop;
}


struct Customer customerOrder()
{
		//struct Customer customer = {"John", 200};
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("customer1.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

		read = getline(&line, &len, fp);
		char *a = strtok(line, ",");
		char *b = strtok(NULL, ",");
		char *custName = malloc(sizeof(char) * 50);
		double custBudget = atof(b);
		strcpy(custName,a);
		struct Customer customer = {custName,custBudget};


    while ((read = getline(&line, &len, fp)) != -1) {
		char *name = strtok(line, ",");
		char *qty = strtok(NULL, ",");

		int quantity = atoi(qty);
		char *productName = malloc(sizeof(char) * 50);
		strcpy(productName, name);
		struct ProductStock shoppingListItem = {productName,quantity};
		customer.shoppingList[customer.index++] = shoppingListItem;
    }
return customer;
}







int startup()
{
	printf("THE C SHOP \n");
	printf("-------------\n");

	char* choice = (char*) malloc(10 * sizeof(char));

  printf("Do you want LIVE mode, Y/N?\n");
	scanf("%s", choice);

	if (strcmp(choice, "y")==0 || strcmp(choice, "Y")==0){
// ref fxn to read in shop data
    char* productName = (char*) malloc(20 * sizeof(char));
    char* temp = (char*) malloc(20 * sizeof(char)); //declared to handle whitespace
    printf("What product would you like?\n");
    scanf("%c", &temp);
    scanf("%[^\n]s", productName);


// loop over to to check if it exists - TODO

    int quantity;
    printf("What quantity of %s is required?\n", productName);
    scanf("%d", &quantity);

    float budget;
    printf("What is your budget?\n");
    scanf("%f", &budget);
    printf("Budget is %.2f and you require %d of product %s.\n",budget, quantity, productName);
		return 1;

	} else if (strcmp(choice, "n")==0 || strcmp(choice, "N")==0 ){
		printf("Reading in Shop and Customer CSVs\n");
		return 2;

	}else {
    printf("Enter Y or N, %s is invalid\n", choice);
  }

}

void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);
	printf("-------------\n");
}


void printShop(struct Shop shop)
{
	printf("Shop has %.2f in cash\n", shop.cash);
	for (int i = 0; i < shop.index; i++)
	{
		printProduct(shop.stock[i].product);
		printf("The shop has %d of the above\n", shop.stock[i].quantity);
	}
}


void printCust(struct Customer customer)
{
	printf("Customer Name is %s and they have %.2f for budget\n", customer.name, customer.budget);
	for (int i = 0; i < customer.index; i++)
	{
		printProduct(customer.shoppingList[i].product);
		printf("The shop has %d of the above\n", customer.shoppingList[i].quantity);
	}
}




int main(){
int pro = startup();

createAndStockShop();
if (pro == 1){
  //customerOrder();
  printf("sdlkjflskdjflsdkjf");
}
struct Shop shop = createAndStockShop();
printShop(shop);


struct Customer customer = customerOrder();
printCust(customer);



//printf(cokeStock.quantity, cokeStock.product.name);

// struct Customer dominic = { "Dominic", 100.0 };
//
// struct Product coke = { "Can Coke", 1.10 };
// struct Product bread = { "Bread", 0.7 };
// // printProduct(coke);
//
// struct ProductStock cokeStock = { coke, 20 };
// struct ProductStock breadStock = { bread, 2 };
//
// dominic.shoppingList[dominic.index++] = cokeStock;
// dominic.shoppingList[dominic.index++] = breadStock;
//
// printCustomer(dominic);
	return 0;

}



//write a method which loops through the Customers shopping list and for each item looks
// for the price from the shop, from there you could set the price for the customer to
//  match the shop or you could do all the math to figure out if the customer can buy
