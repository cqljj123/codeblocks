#ifndef __OBJFUNC__
#define __OBJFUNC__
#include "mymicro.h";
extern MYMICRO objectexe;
extern vector<pair<string,double>> GLOAB_BETA;
double square1(double a);
double rnd();
double norm(double * beta,int p);
double ph_1(double *beta,double *X);
double ph_2(double *beta,double *X);
double ph_3(double *beta,double *X);
double ph_4(double *beta,double *X);
double co_1(double *beta,double *X);
double co_2(double *beta,double *X);
double co_3(double *beta,double *X);
double co_4(double *beta,double *X);
double fp_1(double *beta,double *X);
double fp_2(double *beta,double *X);
double fp_3(double *beta,double *X);
double fp_4(double *beta,double *X);
double fp_5(double *beta,double *X);
double objection(double *beta,double *x);
/*初始目标函数*/
int objectfuncint(string & str1,string &str2);
#endif