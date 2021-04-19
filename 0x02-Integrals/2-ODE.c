#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void plot_ODE(double u0, double du0, double dx)
{
	int i = 0;
	double u = u0, du = du0, ddu = -sin(u), error = dx / 2;
	double up, dup, ddup;
	double e = du0 * du0 / 2 + 1 - cos(u0);
	double duest;
	FILE *fp=NULL, *fpg=NULL;
	char name[20];
	double PI = 3.1415926536;

	sprintf(name, "graph_%.2f_%.2f.txt", u0, du0);
	fp=fopen(name,"w");
/*	fpg=fopen("test_graph", "w");*/
	while ((i == 0 || (fabs(u - u0) + fabs(du - du0)) > error) && i < 100000 && u >= -5 *PI && u <= 5 *PI)
	{
		fprintf(fp, "%i\t %lf\t %lf\t %lf\t %lf\n", i, u, du, ddu, du * du / 2 + 1 - cos(u));
/*		fprintf(fpg, "%i\t %lf\t %lf\t %lf\t %lf\n", i, u, du, ddu, du * du / 2 + 1 - cos(u));*/
		ddup = -sin(u);
		dup = du + (ddup + ddu) / 2.0 * dx;
		up = u + (dup + du) / 2.0 * dx;
		duest = sqrt(2*(e - 1 + cos(up)));
		if (dup > 0)
			dup = duest;
		else
			dup = -duest;
		ddu = ddup;
		du = dup;
		u = up;
		i++;
	}
	fclose(fp);
}





int main()
{
	int i, j;
	double u0;
	double du0;
	double dx = 1.0 / 1000;
	double PI = 3.1415926536;

	double tableu0[] = {-4 * PI, -2 *PI, 0 , 2 * PI, 4 * PI};
	double tabledu0[] = { -3, -2.5, -2.1, -2.05, 0.5, 1, 1.5, 1.9, 1.95, 1.99, 2.05, 2.1, 2.5, 3 };

	for (i = 0 ; i < 5; i++)
	{
		u0 = tableu0[i];
		for (j = 0 ; j < 14; j++)
		{
			du0 = tabledu0[j];
			plot_ODE(u0, du0, dx);
		}

	}
}
