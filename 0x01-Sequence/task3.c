#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265

// Task1
typedef struct
{
	double re;
	double im;
} complex;


// Task3
double Modulus(complex c)
{
	double res;

	res = sqrt(c.re * c.re + c.im * c.im);
	return (res);
}

// Task5
complex Addition(complex c1, complex c2)
{
	complex c3;

	c3.re = c1.re + c2.re;
	c3.im = c1.im + c2.im;
	return (c3);
}


// Task7
complex Multiplication(complex c1, complex c2)
{
	complex c3;

	c3.re = c1.re * c2.re - c1.im * c2.im;
	c3.im = c1.re * c2.im + c1.im * c2.re;
	return (c3);
}


// Task10
void ComplexNumber(complex c)
{
	printf("%.2f%+.2fi\n", c.re, c.im);
}


int NumberRec(complex z, complex c, int maxiter)
{
	int nb = 0;
	complex zn;

	zn.re = z.re;
	zn.im = z.im;

	while (nb < maxiter)
	{
		if (Modulus(zn) > 2)
			return (nb);
		zn = Multiplication(zn, zn);
		zn = Addition(zn, c);
		nb++;
	}
	return (nb);
}


/**
 * alloc_grid - returns a pointer to a 2 dimensional array of integers
 *
 * @width : grid width
 * @height : grid height
 *
 * Return: created array
 */

int **alloc_grid(int width, int height)
{
	int i, j;
	int **s;

	if (width <= 0 || height <= 0)
		return (NULL);

	s = malloc(height * sizeof(int *));

	if (s == NULL)
		return (NULL);


	for (i = 0; i < height; i++)
	{
		s[i] = malloc(width * sizeof(int));
		if (s[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}
		for (j = 0; j < width; j++)
			s[i][j] = 0;
	}
	return (s);
}


/**
 * free_grid - frees a 2 dimensional grid
 *
 * @grid : grid to be freed
 * @height : grid height
 *
 * Return: None
 */

void free_grid(int **grid, int height)
{
	int i;

	for (i = 0; i < height; i++)
		free(grid[i]);
	free(grid);
}


void generateMan()
{
	double minre = -2.25;
	double maxre = 1;
	double minim = -1.25;
	double maxim = 1.25;
	double inc = 0.001;
	unsigned long nbcol, nbline, i, j;
	int **grid;
	complex z, c;

	nbcol = (maxre - minre) / inc + 1;
	nbline = (maxim - minim) / inc + 1;
	grid = alloc_grid(nbcol, nbline);

	z.re = 0;
	z.im = 0;

	for (i = 0; i < nbline; i++)
	{
		c.im = minim + i * inc;
		for (j = 0; j < nbcol; j++)
		{
			c.re = minre + j * inc;
			grid[i][j] = NumberRec(z, c, 100);
		}
	}

	FILE* pgmimg;
	pgmimg = fopen("mandelbrot.pgm", "wb"); //write the file in binary mode
	fprintf(pgmimg, "P2\n"); // Writing Magic Number to the File
	fprintf(pgmimg, "%lu %lu\n", nbcol, nbline); // Writing Width and Height into the file
	fprintf(pgmimg, "255\n"); // Writing the maximum gray value
	for (i = 0; i < nbline; i++)
	{
		for (j = 0; j < nbcol; j++)
			fprintf(pgmimg, "%d ", 255 - 255 * grid[i][j] / 100);
		fprintf(pgmimg, "\n");
	}
	fclose(pgmimg);
	free_grid(grid, nbline);
}



void generateJulia(complex c)
{
	double minre = -2;
	double maxre = +2;
	double minim = -1;
	double maxim = 1;
	double inc = 0.001;
	unsigned long nbcol, nbline, i, j;
	int **grid;
	complex z;

	nbcol = (maxre - minre) / inc + 1;
	nbline = (maxim - minim) / inc + 1;
	grid = alloc_grid(nbcol, nbline);

	for (i = 0; i < nbline; i++)
	{
		z.im = minim + i * inc;
		for (j = 0; j < nbcol; j++)
		{
			z.re = minre + j * inc;
			grid[i][j] = NumberRec(z, c, 255);
		}
	}

	FILE* pgmimg;
	pgmimg = fopen("julia.pgm", "wb"); //write the file in binary mode
	fprintf(pgmimg, "P2\n"); // Writing Magic Number to the File
	fprintf(pgmimg, "%lu %lu\n", nbcol, nbline); // Writing Width and Height into the file
	fprintf(pgmimg, "255\n"); // Writing the maximum gray value
	for (i = 0; i < nbline; i++)
	{
		for (j = 0; j < nbcol; j++)
			fprintf(pgmimg, "%d ", grid[i][j]);
		fprintf(pgmimg, "\n");
	}
	fclose(pgmimg);
	free_grid(grid, nbline);
}

int main()
{
	complex c;

	generateMan();
	c.re = -0.80004309;
	c.im = 0.164138006;
	generateJulia(c);
}
