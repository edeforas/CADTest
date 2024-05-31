#ifndef _Util_
#define _Util_

#define swap(a,b) { auto tmp=a; a=b; b=tmp; }  
#define rotate(a,b,c) { auto tmp=a; a=b; b=c; c=a; }  

double square(double a);
double cubic(double a);

double Bernstein01(double u);
double Bernstein11(double u);

double Bernstein02(double u);
double Bernstein12(double u);
double Bernstein22(double u);

double Bernstein03(double u);
double Bernstein13(double u);
double Bernstein23(double u);
double Bernstein33(double u);

#endif
