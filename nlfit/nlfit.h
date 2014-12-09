#ifndef __NLFIT__
#define __NLFIT__
#pragma once
typedef struct{
	double tolx,tolfun,derivstep;
	int maxiter;
} option; //选项设置
typedef struct {
	int iter; //迭代次数
	char flag ;//跳出条件
	double sse;	//残差平方和
}resultinfo;
ostream & operator<<(ostream & s,const resultinfo &a);
extern "C" int mtdiv2(double * A,int m,int n,double *B,int p,double *ret);
char lmfit(double *X,double *y,double *yf,double *yr,int lenx ,fitfunction model,mat & beta,int p, option & options,resultinfo & result);// 买夸特 非线性回归
char nlfit(double *x,double *y,double *yf,double *yr,int lenx,fitfunction model,double * beta,int p,option & NLF_OPTIONS,resultinfo& info);
void  getjacobian(double *beta,int p,double fdiffstep, fitfunction model,double *x ,double *yfit,int len,mat &j) ; //雅阁比矩阵计算
double norm(double * beta,int p);
#endif
