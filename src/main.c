#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	double x,y,d;
}PointPos;

int getCoefficient(PointPos* point0, PointPos* point1, double* a, double* b)
{
	if(point0->y == point1->y)
		return -1;
	double subx = point0->x - point1->x, sumx = point0->x + point1->x;
	double suby = point0->y - point1->y, sumy = point0->y + point1->y;
	double subr = point0->d - point1->d, sumr = point0->d + point1->d;
	*a = -subx/suby;
	*b = (sumx*subx + sumy*suby - sumr*subr) / (suby*2);
	return 0;
}

void calculatePos(double a0, double b0, double a1, double b1, double* x, double* y)
{
	*x=(b1-b0)/(a0-a1);
	*y=a1*(*x)+b1;
}

int isOnLine(PointPos points[3])
{
	double x0 = points[0].x, y0 = points[0].y;
	double x1 = points[1].x, y1 = points[1].y;
	double x2 = points[2].x, y2 = points[2].y;
	return (x2-x0)*(y2-y1) == (y2-y0)*(x2-x1);
}

int location3Points(PointPos points[3], double* x ,double* y)
{
	if(isOnLine(points))
		return -1;
	double coefficient_A[2],coefficient_B[2];
	int ci, pi;
	for(ci = pi = 0; pi < 3 && ci < 2; pi++)
	{
		int i1 = pi, i2 = pi+1;
		if(i2 == 3) i2 = 0;
		if(getCoefficient(&points[i1], &points[i2], &coefficient_A[ci], &coefficient_B[ci]) < 0)
			continue;
		ci++;
	}
	calculatePos(coefficient_A[0], coefficient_B[0], coefficient_A[1], coefficient_B[1], x, y);
	return 0;
}

double main(int argc, char* argv[])
{
	printf("%s: hello world!\n", argv[0]);
	if(argc < 10)
	{
		printf("%s x0 y0 d0 x1 y1 d1 x2 y2 d2\n", argv[0]);
		return -1;
	}
	PointPos points[3];
	int i;
	for(i = 0; i < 3; i++)
	{
		points[i].x = strtod(argv[3*i+1], NULL);
		points[i].y = strtod(argv[3*i+2], NULL);
		points[i].d = strtod(argv[3*i+3], NULL);
		printf("p%d:%lf %lf %lf\n", i, points[i].x, points[i].y, points[i].d);
	}
	double x,y;
	if(location3Points(points, &x, &y) < 0)
	{
		printf("points is a line!\n");
		return -1;
	}
	printf("x %lf y %lf\n", x, y);
	return 0;
}

