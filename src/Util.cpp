#include "Util.h"

double square(double a)
{
	return a * a;
}

double cubic(double a)
{
	return a * a * a;
}

double Bernstein01(double u)
{
	return 1. - u;
}

double Bernstein11(double u)
{
	return u;
}

double Bernstein02(double u)
{
	return square(1. - u);
}

double Bernstein12(double u)
{
	return 2. * u * (1. - u);
}

double Bernstein22(double u)
{
	return square(u);
}

double Bernstein03(double u)
{
	return cubic(1. - u);
}

double Bernstein13(double u)
{
	return 3. * u * square(1. - u);
}

double Bernstein23(double u)
{
	return 3. * square(u) * (1. - u);
}

double Bernstein33(double u)
{
	return cubic(u);
}
