#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#define alloc(t) (t*) malloc(sizeof(t))

// define a linked list sCell
typedef struct sCell
{
	double n;
	struct sCell *next;
} tCell;

// Add element to the beginning of the list
tCell *InitCell(double elt, tCell *succ)
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
		printf("%.9f ", first->n);
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


// Heron Function
tCell *Heron(double p, double u0)
{
	double un;
	double un1;
	tCell *ret = NULL;

	if (u0 == 0)
		return (NULL);

	ret = InitCell(u0, ret);
	un = u0;
	un1 = 1 / 2.0 * (un + p / un);
	while (fabs(un1-un) > (1 / pow(10, 7)))
	{
		un = un1;
		un1 = 1 / 2.0 * (un + p / un);
		ret = InitCell(un, ret);
	}
	return (ret);
}

// Heron Function simple
void HeronSimple(double p, double u0)
{
	double un;
	double un1;

	if (u0 == 0)
	{
		printf("u0 can't be equal to 0\n");
		return;
	}

	printf("%.9f", u0);
	un = u0;
	un1 = 1 / 2.0 * (un + p / un);
	while (fabs(un1-un) > (1 / pow(10, 7)))
	{
		un = un1;
		un1 = 1 / 2.0 * (un + p / un);
		printf(" %.9f", un);
	}
}



int main()
{
	double p, u0;
	tCell *first=NULL;

	printf("U0 = ");
	scanf("%lf", &u0);
	printf("p = ");
	scanf("%lf", &p);

	// COMPLEX METHOD USING LINKED LIST
	printf("the Heron sequence until having convergence with an error equal to 10^(-7) is: \n ");
	first = Heron(p,u0);
	PrintList(first);
	printf("\n");
	printf("Convergence value is %.9f\n", u0 / fabs(u0) * sqrt(p));
	freeCell(first);

	// SIMPLE METHOD WITH DIRECT DISPLAY
	printf("the Heron sequence until having convergence with an error equal to 10^(-7) is: \n ");
	HeronSimple(p,u0);
	printf("\n");
	printf("Convergence value is %.9f\n", u0 / fabs(u0) * sqrt(p));

	return 0;
}
