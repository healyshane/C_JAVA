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


struct Customer {
	char* name;
	double budget;
	struct ProductStock shoppingList[50];
	int index;
};





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


int main(void){
	struct Customer customer = customerOrder();
	printf("Customer Name is %s and they have %.2f for budget\n", customer.name, customer.budget);
	return 0;
}
