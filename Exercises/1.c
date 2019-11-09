


//if ((strcmp(name,"Alice")==0) || (strcmp(name,"Bob")==0))
//{
	printf("Hello %s\n", n);
//} else
//{
	printf("Hello lowly peasant!\n");
//}


//int n;
//int sum = 0;


createCustomer();
printf("Hello\n");


printf("Current Shop Cash is XXX \n To change manually enter  M \n To read from file enter  F :  ");


int n;
int sum = 0;
float cash = 0;//input from file future
int Y = 0;
int n = 0;

printf("Read in Shop Cash from CSV? Y  /  N  : ");
scanf("%s", &n);

if (((n)==Y) || ((n)==y))
	{
		printf("nelly");
	}

	printf("The sum of 1 to %d, was %d\n", n, sum);





	else if (strcmp(choice, "n")==0)
	{
		printf("Enter y or n please \n");

	}








	// imported
	double cost = 0;
	// We will loop over the array to find out how much it will cost the customer to buy all these items
	for(int i=0; i < 2; i++)
	{
		cost += cp[i].price * quantity;
	}
	// in this simple example the customer either can afford it all or nothing, you will want to be able to let them buy what they can afford
	if (cost <= budget)
	{
		// we reduce the customers cash
		budget -= cost;
		// the shop gets the money
		shopCash += cost;
		printf("\nThe customer can buy everything they wanted and now the shop has %.2f and the customer has %.2f remaining\n", shopCash, budget);
	}
