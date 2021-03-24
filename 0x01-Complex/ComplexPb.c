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



// Task2
complex Conjugate(complex c)
{
	complex res;

	res.re = c.re;
	res.im = -c.im;
	return (res);
}


// Task3
double Modulus(complex c)
{
	double res;

	res = sqrt(c.re * c.re + c.im * c.im);
	return (res);
}


// Task4
double Argument(complex c)
{
	double res;
	if (c.re == 0 && c.im == 0)
		return (0);
	if (c.re == 0 && c.im > 0)
		return (PI/2);
	if (c.re == 0 && c.im < 0)
		return (-PI/2);
	if (c.re >= 0)
		return (atan(c.im / c.re));
	if (c.im > 0)
		return (PI + atan(c.im / c.re));
	return (-PI + atan(c.im / c.re));

}

// Task5
void Addition(complex c1, complex c2, complex *c3)
{
	c3->re = c1.re + c2.re;
	c3->im = c1.im + c2.im;
}

// Task6
void Subtraction(complex c1, complex c2, complex *c3)
{
	c3->re = c1.re - c2.re;
	c3->im = c1.im - c2.im;
}


// Task7
void Multiplication(complex c1, complex c2, complex *c3)
{
	c3->re = c1.re * c2.re - c1.im * c2.im;
	c3->im = c1.re * c2.im + c1.im * c2.re;
}


// Task8
void Division(complex c1, complex c2, complex *c3)
{
	if (c2.re == 0 && c2.im == 0)
	{
		c3->re = 0;
		c3->im = 0;
	}
	else
	{
		c3->re = (c1.re * c2.re + c1.im * c2.im) / (c2.re * c2.re + c2.im * c2.im);
		c3->im = (c2.re * c1.im - c2.im * c1.re) / (c2.re * c2.re + c2.im * c2.im);
	}
}


// Task9
void ComplexFromModArg (double m, double arg, complex *c3)
{
	c3->re = m * cos(arg);
	c3->im = m * sin(arg);
}

// Task10
void ComplexNumber(complex c)
{
	printf("%.2f%+.2fi\n", c.re, c.im);
}

//the main
int main()
{
	complex c1;
	complex c2;
	complex c3;
	double m;
	double arg;
	c1.re = 1;
	c1.im = 1;
	c2.re = 3;
	c2.im = 4;
	ComplexNumber(c1);
	ComplexNumber(Conjugate(c1));
	printf("Modulus of c1 = %.2f\n", Modulus(c1));
	printf("Modulus of c2 = %.2f\n", Modulus(c2));
	c1.re = -0.0001;
	c1.im = -1;
	c2.re = 0;
	c2.im = -1;
	printf("Argument of c1 = %.2f\n", Argument(c1));
	printf("Argument of c2 = %.2f\n", Argument(c2));
	c1.re = 1;
	c1.im = 1;
	c2.re = 3;
	c2.im = 4;
	Addition(c1,c2,&c3);
	ComplexNumber(c3);
	Subtraction(c1,c2,&c3);
	ComplexNumber(c3);
	Multiplication(c1,c2,&c3);
	ComplexNumber(c3);
	Division(c1,c2,&c3);
	ComplexNumber(c3);
	m = 1;
	arg = -3 * PI / 4;
	ComplexFromModArg(m, arg, &c3);
	ComplexNumber(c3);
	m = 10;
	arg = - PI / 6;
	ComplexFromModArg(m, arg, &c3);
	ComplexNumber(c3);
	return 0;
}
