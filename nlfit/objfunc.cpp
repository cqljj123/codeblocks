#include "stdafx.h"
#include "objfunc.h"
MYMICRO objectexe;
vector<pair<string,double>> GLOAB_BETA;
unsigned long rndnum = GetTickCount() ;//初始随机种子
double obj(double * beta,double * x)
{
	double ret = beta[0]*(1-beta[1]* (*x))*(*x)/(1+beta[2]*(*x))-beta[3] ;
	return ret;
}
double square1(double a)
{
	return a*a;
}
double rnd()
{
	srand(rndnum);
	rndnum =rand();
	//cout<<rndnum<<endl;
	double a =(double)(rndnum)/RAND_MAX;
	return a;
	//return 1.0;
}
double ph_1(double *beta,double *X)// a*x*b/(a*x+b)-c;
{
	if(beta[0]<0)  beta[0]= 0.001*rnd();
	if( abs(beta[1]) < 10) beta[1] = 10 ;
	if(beta[2]<0)  beta[2]= 0.001*rnd();
	if(beta[1]<0)  beta[1]= 0.001*rnd();
	return beta[0] * (*X) * beta[1]/ (beta[0] *(* X) + beta[1]) - beta[2];
}
double ph_2(double *beta,double *x)
{
	double X = *x;
	if (beta[2] < 0 || beta[2] > 1)  beta[2] = 0.001 * rnd();
	if (beta[3] < 0 ) beta[3] = 0.001 * rnd();
	if (beta[1] < 0 ) beta[1] = 0.001 * rnd();
	if (beta[0] < 0 ) beta[0] = 0.001 * rnd();
	return  (beta[0] * X + beta[1] - sqrt(abs(square1(beta[0] * X + beta[1]) - 4 * beta[2] * beta[0] * X * beta[1]))) / 2 / beta[2] - beta[3];
}
double ph_3(double *beta,double *x)
{
	double X = *x;
	double ttp = -beta[0] * X / beta[1];
	if (ttp > 100) return 1.0e12;
	return  beta[1] * (1 - beta[2] * exp(ttp));
	return 0.0;
}
double ph_4(double *beta,double *x)
{
	double X = *x;
	if (beta[3] < 0) beta[3] = 0.001 * rnd();
	if (beta[2] < 0)  beta[2] = 0.001 * rnd();
	if (beta[1] < 0 ) beta[1] = 0.001 * rnd();
	if (beta[0] < 0)  beta[0] = 0.001 * rnd();
	return   beta[0] * (1 - beta[1] * X) * X / (1 + beta[2]* X) - beta[3];
}
double co_1(double *beta,double *x)
{
	double X = *x;
	return beta[0] * (beta[1]) * X / (beta[1] + beta[0] * X) - beta[2];
}
double co_2(double *beta,double *x)
{
	//static int iter;
	double X = *x;
	if (abs(beta[1]) < 10)  beta[1] = 10;
	//cout<<++iter<<endl;
	return  beta[0] * beta[1] * X / (beta[0] * X + beta[1]) - beta[2];
}
double co_3(double *beta,double *x)
{
	double X = *x;
	return  beta[1] * X / (X + beta[0]) - beta[2];
}
double co_4(double *beta,double *x)
{
	double X = *x;
	if (beta[3] < 0)  beta[3] = 0.001 * rnd();
	if (beta[2] < 0 ) beta[2] = 0.001 * rnd();
	if (beta[1] < 0 ) beta[1] = 0.001 * rnd();
	if (beta[0]< 0 )  beta[0] = 0.001 * rnd();
	return beta[0] * (1 - beta[1] * X) * X / (1 + beta[2] * X) - beta[3];
}
double fp_1(double *beta,double *x)
{
	double X = *x;
	if (abs(beta[1]) < 10 ) beta[1] = 10;
	return  beta[0] * X * beta[1] / (beta[0] * X + beta[1]);
}
double fp_2(double *beta,double *x)
{
	double X = *x;
	if( beta[2] < 0 || beta[2] > 1)beta[2] = 0.001 * rnd();
	return  (beta[0] * X + beta[1] - sqrt(abs(square1(beta[0] * X + beta[1])  - 4 * beta[2] * beta[0] * X * beta[1]))) / 2 / beta[2];
	return 0.00;
}
double fp_3(double *beta,double *x)
{
	double X = *x;
	double     ttp = -beta[0] * X / beta[1];
	if(ttp > 100 ) return 100000000000.0;
	return  beta[1] * (1 - exp(ttp));
}
double fp_4(double *beta,double *x)
{
	double X = *x;
	if (beta[0] < -100)  beta[0] = -100;
	if (beta[2] < 0 ) beta[2] = 0.001 * rnd();
	if (beta[1] < -100 ) beta[1] = -100;
	double ttp = -beta[0] * X / beta[2];
	if (ttp > 100) return 100000000000.0;

	double ttp2 = -beta[1] * X / beta[2];
	if (ttp2 > 100) return    100000000000.0;
	return  beta[2] * (1 - exp(ttp)) * exp(ttp2);
}
double fp_5(double *beta,double *x)
{
	double X = *x;
	if(beta[2] < 0)  beta[2] = 0.001 * rnd();
	if(beta[1] < 0)  beta[1] = 0.001 * rnd();
	if(beta[0] < 0)  beta[0] = 0.001 * rnd();
	return beta[0] * (1 - beta[1] * X) * X / (1 + beta[2] * X);
}
/*目标函数*/
double objection(double *beta,double *x)
{
	//static int iter;
	for(int i = 0; i < GLOAB_BETA.size();++i)
	{
		objectexe.var_table[GLOAB_BETA[i].first] = beta[i];	/*设置到全局*/
	}
	objectexe.var_table["x"]= *x;

	int err=-1;
	objectexe.eval(err);
	for(int i = 0; i < GLOAB_BETA.size();++i)
	{
		beta[i] = objectexe.var_table[GLOAB_BETA[i].first] ;	/*设置到全局*/
	}
	//cout<<++iter<<endl;
	return objectexe.var_table["y"];

}
/*初始目标函数*/
int objectfuncint(string & str1,string &str2)
{
	int err=-1;
	objectexe.clear();
	objectexe.eval(str1,err);
	int t;
	if(err != -1 || objectexe.var_table.size()<1)
	{
		MessageBoxA(NULL,"参数错误","err",MB_OKCANCEL);
		return err;
	}
	GLOAB_BETA.clear();/*情况变了*/
	for(auto it:objectexe.var_table)
	{
		if(it.first == "x") continue;
		if(it.first == "y") continue;
		if(it.first == "ans") continue;
		GLOAB_BETA.push_back(it);
	}
	objectexe.eval(str2,err);
	if(err != -1 || objectexe.var_table.size()<1) MessageBoxA(NULL,"参数错误","err",MB_OKCANCEL);
	return err;
}
