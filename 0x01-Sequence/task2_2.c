#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#define alloc(t) (t*) malloc(sizeof(t))

// define a linked list sCell
typedef struct sCell
{
	unsigned long n;
	struct sCell *next;
} tCell;

// Add element to the beginning of the list
tCell *InitCell(unsigned long elt, tCell *succ)
{
	tCell *new;

	new = alloc(tCell);
	if (new == NULL)
		return (NULL);
	new->n = elt;
	new->next = succ;
	return (new);
}

//Display the linked list
void PrintList(tCell *first)
{
	if (first != NULL)
	{
		PrintList(first->next);
		printf("%lu ", first->n);
	}
}

//Free the linked list
void freeCell(tCell *first)
{
	tCell *curs;

	while (first != NULL)
	{
		curs = first->next;
		free(first);
		first = curs;
	}
}


// Fibo Function
tCell *Fibo(unsigned long u0, unsigned long u1)
{
	unsigned long un;
	unsigned long un1;
	unsigned long un2;
	tCell *ret = NULL;

	ret = InitCell(u0, ret);
	ret = InitCell(u1, ret);
	un = u0;
	un1 = u1;
	un2 = un1 + un;
	while (fabs(un2 / (1.0 * un1) - un1 / (1.0 * un)) > (1 / pow(10, 10)))
	{
		un = un1;
		un1 = un2;
		un2 = un1 + un;
		ret = InitCell(un1, ret);
	}
	return (ret);
}

// Heron Function simple
void FiboSimple(unsigned long u0, unsigned long u1)
{
	unsigned long un;
	unsigned long un1;
	unsigned long un2;

	printf("the Fibo sequence until having convergence with an error equal to 10^(-7) is: \n ");
	printf("%lu %lu", u0, u1);
	un = u0;
	un1 = u1;
	un2 = un1 + un;
	while (fabs(un2 / (1.0 * un1) - un1 / (1.0 * un)) > (1 / pow(10, 10)))
	{
		un = un1;
		un1 = un2;
		un2 = un1 + un;
		printf(" %lu", un1);
	}
	printf("\n");
	printf("The Gold Number is %.9f\n", un1 / (1.0 * un));
}



int main()
{
	unsigned long u0, u1;
	tCell *first=NULL;

	printf("u0 = ");
	scanf("%lu", &u0);
	printf("u1 = ");
	scanf("%lu", &u1);

	if (u0 == 0 && u1 == 0)
	{
		printf("Can't define 2 null first terms\n");
		return (0);
	}

	// COMPLEX METHOD USING LINKED LIST
	printf("the Fibo sequence until having convergence with an error equal to 10^(-7) is: \n ");
	first = Fibo(u0,u1);
	PrintList(first);
	printf("\n");
	printf("The Gold Number is %.9f\n", first->n / (1.0 * first->next->n));
	freeCell(first);

	// SIMPLE METHOD WITH DIRECT DISPLAY
	FiboSimple(u0,u1);

	// CHECKING GOLD NUMBER VALUE
	printf("The Gold Number is indeed %.9f\n", (1 + sqrt(5)) / 2);
	return 0;
}
