// testnls.cpp : Defines the entry point for the console application.
//
//#define USEMKL Sequential
#include "stdafx.h"
#include "objfunc.h"
#include "nlfit.h"
extern MYMICRO objectexe; /*公式解析器*/
extern vector<pair<string,double>> GLOAB_BETA; /*全局系数*/
option NLF_OPTIONS={1.0e-8,1.0e-8,6.055454452393343e-006,500};//全局选项

int yzpfit(double *x,double *y,double *yfit,double * yr,int lenx,double * beta)
{
	fitfunction model = objection;
	int lenp=3;
	lenp = GLOAB_BETA.size();
	resultinfo info;

	nlfit(x,y,yfit,yr,lenx, model,beta, lenp,NLF_OPTIONS,info);
	cout<<info;
	//结果处理;
	return 0;
}

void calc()
{
	MYMICRO MICRO;
	std::vector<TOKEN> tokens;
	char buf[1000];
	std::cout<<"welcome:\n";
	int err;
	while(true)
	{
		cout<<">>";
		std::cin.getline(buf,1000);
		std::cout<<"\t"<<MICRO.eval(buf,err)<<"\n";
		std::cout<<MICRO.errstr(err)<<"\n";
	}
	//return err;
}

int main(int argc, char* argv[])
{
	//calc();
	unsigned a1 =GetTickCount();
	mat beta(4);
	beta.M[0]=0.1;
	beta.M[1]=0.1;
	beta.M[2]=5;
	beta.M[3]=1;
	double x[]={1799.94,1698.71,1599.5,1400.93,1299.92,1200.23,999.1,799.76,600.69,399.46,198.69,99.97,50.21,0.92};
	double y[]={10.84,11.38,11.74,11.75,11.47,11.77,11.9,11.25,10.98,9.74,7.18,4.17,2.17,-0.38};
	mat yf(14);
	mat yr(14);
	mat ty(y,14);
	string sting1 = "a=0.1;b=0.1;c=5;";
	string strig2 = "y=b*x/(x+a)-c;";
	objectfuncint(sting1,strig2);
	yzpfit(x,y,yf.M,yr.M,14,beta.M);
	yf.pluscol(yr);
	ty.pluscol(yf);
	cout<<ty;
	cout <<beta<<endl;
	cout<<GetTickCount()-a1;
	system("pause");
}

