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

//Defining structs for program
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

// Reading in SHOP data from CSV
struct Shop createAndStockShop()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("stock.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

        read = getline(&line, &len, fp);
    		char *d = strtok(line, ",");
    		double cash = atof(d);

    		struct Shop shop = { cash };

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

// Reading in CUSTOMER data from CSV
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

    struct Product p = {productName, 0}; //NAME PRICE
    struct ProductStock shoppingListItem = {p, quantity};
		customer.shoppingList[customer.index++] = shoppingListItem;
    }
return customer;
}



int findProduct(struct Shop s, char* name){
  int x = 0;
  for (int i=0;i<s.index;i++){
    if(strcmp(name,s.stock[i].product.name) == 0){
      return x = 1;
    }
}
return x;
}




int startup()
{
	printf("THE C SHOP \n");
	printf("-------------\n");

	char* choice = (char*) malloc(10 * sizeof(char));

  printf("Start LIVE mode, Y/N?  ");
	scanf("%s", choice);
  printf("\n");
	if (strcmp(choice, "y")==0 || strcmp(choice, "Y")==0){

char* productName = (char*) malloc(20 * sizeof(char));
char* temp = (char*) malloc(20 * sizeof(char)); //declared to handle whitespace
printf("What product would you like?\n");
scanf("%c", &temp);
scanf("%[^\n]s", productName);


struct Shop s = createAndStockShop();

int x = findProduct(s,productName);

while(x != 1){

int x = findProduct(s,productName);
  char* productName = (char*) malloc(20 * sizeof(char));
  char* temp = (char*) malloc(20 * sizeof(char)); //declared to handle whitespace

    printf("What product would you like?\n");
    scanf("%c", &temp);
    scanf("%[^\n]s", productName);
    x = 0;
  }


// loop over to to check if it exists - TODO


    int quantity;
    printf("What quantity of %s is required?\n", productName);
    scanf("%d", &quantity);

    float budget;
    printf("What is your budget?\n");
    scanf("%f", &budget);
    printf("Budget is %.2f and you require %d of product %s.\n",budget, quantity, productName);

//
//
// SEE SHOP C for creating customer struct with input from terminal

struct Customer l = {"Mary",budget};
struct ProductStock itemList = {productName, quantity};



    return 1;

	} else if (strcmp(choice, "n")==0 || strcmp(choice, "N")==0 ){
		printf("Reading in Shop and Customer CSVs\n");
    printf("---------------------------------\n");
		return 2;

	}else {
    printf("Enter Y or N, %s is invalid\n", choice);
  }

}

void printProduct(struct Product p)
{
	printf("PRODUCT NAME: %s \nPRODUCT PRICE: %.2f\n", p.name, p.price);

}

void printShop(struct Shop shop)
{
	printf("Shop has %.2f in cash\n", shop.cash);
	for (int i = 0; i < shop.index; i++)
	{
		printProduct(shop.stock[i].product);
		printf("SHOP Product Quantity: %d\n", shop.stock[i].quantity);
    printf("-------------\n");
	}
}




void printCust(struct Customer c)
{
//	printf("Customer %s has budget %.2f in cash\n", customer.name, customer.budget);
  for (int i = 0; i < c.index; i++)
	{

  //  printProduct(customer.shoppingList[i].product);

    printf("The customer ordered %d of %s\n", c.shoppingList[i].quantity, c.shoppingList[i].product.name);
    // double cost = customer.shoppingList[i].quantity*customer.shoppingList[i].product.price;

    //double cost = customer.shoppingList[i].quantity * customer.shoppingList[i].product.price;
		//printf("The cost to %s will be %.2f\n", customer.name, cost);

	}
}


double findPrice(struct Shop s, char* name){
  for (int i=0;i<s.index;i++){
    if(strcmp(name,s.stock[i].product.name) == 0){
      return s.stock[i].product.price;
    }
  }
  return -1;
}


int findQuantity(struct Shop s, char* name){
  for (int i=0;i<s.index;i++){
    if(strcmp(name,s.stock[i].product.name) == 0){
      return s.stock[i].quantity;
    }
  }
  return -1;


}


void customerCost(struct Shop s, struct Customer* c){
//function for assessing cost of customer order
double customerCost = 0;

for (int i=0; i<c->index; i++){
  struct Product p = c->shoppingList[i].product;


  int quantity = findQuantity(s,p.name);
//  printf("The quantity of %s in the shop is %d \n",p.name,quantity);

  if(quantity < c->shoppingList[i].quantity){
    printf("\n");
    printf("ALERT: Shop has %d stock of %s.\n",quantity, p.name);
    printf("       As Customer requires %d items of %s,\n",c->shoppingList[i].quantity,p.name);
    printf("       these items were removed before processing remainder of order!\n");
    printf("\n");

    c->shoppingList[i].quantity = 0;
    //break;
  }



  double price = findPrice(s,p.name);

  //printf("The price of %s in the shop is %.2f\n", p.name,price);
  double itemCost = c->shoppingList[i].quantity * price;
  customerCost += itemCost;




}

if(customerCost>c->budget){
  printf("Customer %s has inadequate budget to satisfy order\n",c->name);
}else{
  c->budget = c->budget - customerCost;}

//printf("Customer %s has budget %.2f \n",c->name, c->budget);
printf("\n");
printf("Total customer cost for order is %.2f \n", customerCost);

}


int main(){
struct Shop s = createAndStockShop();
startup();



struct Customer c = customerOrder();


printf("Customer %s has budget %.2f \n",c.name, c.budget);
printf("\n");
printCust(c);

//Creating pass pointers to maintain values of variables in Customer.
struct Customer* d = &c;

//Define customer budget prior to ordering
double x = c.budget;

//Execute customer order from CSV
customerCost(s,d);

//Define customer budget post ordering
double y = c.budget;

printf("Shop CASH prior to Order is %.2f\n", s.cash);
s.cash = s.cash + (x-y);
printf("Shop CASH following Order is %.2f\n", s.cash);





	return 0;
}


//write a method which loops through the Customers shopping list and for each item looks
// for the price from the shop, from there you could set the price for the customer to
//  match the shop or you could do all the math to figure out if the customer can buy
