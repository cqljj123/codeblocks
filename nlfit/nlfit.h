#ifndef __NLFIT__
#define __NLFIT__
#pragma once
typedef struct{
	double tolx,tolfun,derivstep;
	int maxiter;
} option; //ѡ������
typedef struct {
	int iter; //��������
	char flag ;//��������
	double sse;	//�в�ƽ����
}resultinfo;
ostream & operator<<(ostream & s,const resultinfo &a);
extern "C" int mtdiv2(double * A,int m,int n,double *B,int p,double *ret);
char lmfit(double *X,double *y,double *yf,double *yr,int lenx ,fitfunction model,mat & beta,int p, option & options,resultinfo & result);// ����� �����Իع�
char nlfit(double *x,double *y,double *yf,double *yr,int lenx,fitfunction model,double * beta,int p,option & NLF_OPTIONS,resultinfo& info);
void  getjacobian(double *beta,int p,double fdiffstep, fitfunction model,double *x ,double *yfit,int len,mat &j) ; //�Ÿ�Ⱦ������
double norm(double * beta,int p);
#endif
