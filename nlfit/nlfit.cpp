#include "stdafx.h"
#include "nlfit.h"
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

ostream & operator<<(ostream & s,const resultinfo &a)
{
	s<<endl;
	s<<"iter:"<< a.iter<<endl;
	s<<"flag:"<< a.flag<<endl;
	s<<"sse:"<< a.sse<<endl;
	return s;
}
double norm(double * beta,int p) //平方和开方
{
	double ret = 0.0;
	for(int i=0;i<p;i++)
	{
		ret	+= (beta[i]*beta[i]);
	}
	//return ret;
	return sqrt(ret);
}
void getjacobian(double *beta,int p,double fdiffstep, fitfunction model,double *x ,double *yfit,int len,mat &j)  //雅阁比矩阵计算
{
	//jacob矩阵计算
	mat delta(p);
	mat yplus(len);
	double delata1,nb,y1;
	for(int k = 0 ; k< p;k++)
	{
		memcpy(delta.M,beta,sizeof(double)*p);
		if (beta[k] == 0 )
		{
			nb = sqrt(norm(beta,p));  //异常点处理
			delata1 =fdiffstep * (nb + (nb==0));
			delta.M[k] += delata1;
		}
		else
		{
			delata1 = fdiffstep*beta[k];
			delta.M[k] +=delata1;
		}
		for(int i = 0 ;i< len;i++)
		{
			yplus.M[i] = model(delta.M,&x[i]);
			y1=model(delta.M,&x[i]);
			j.M[i*p+k]= (y1-yfit[i])/(delata1);
		}
	}
}
void mtdiv3(mat &a,mat &b,mat &ret)
{
	//左除
	mat ta(a),tb(b);
	mtdiv2(ta.M,ta.ROW,a.COL,b.M,b.COL,ret.M);
}
char nlfit(double *x,double *y,double *yf,double *yr,int lenx,fitfunction model,double * beta,int p,option& NLF_OPTIONS,resultinfo& info)
{
	mat tbeta(beta,p);
	//resultinfo info;
	char ch =lmfit(x,y,yf,yr,lenx ,model, tbeta,p, NLF_OPTIONS,info);
	//cout<<info;
	memcpy(beta,tbeta.M,p*sizeof(double));
	return ch;
}
char lmfit(double *X,double *y,double *yf,double *yr,int lenx ,fitfunction model,mat & beta,int p, option &options,resultinfo &result) // 买夸特 非线性回归
{
	double eps =  2.220446049250313e-016,sse,sseold,diagJtJm,dtmp;
	double betatol = options.tolx,maxiter =options.maxiter,rtol = options.tolfun,fdiffstep = options.derivstep ;
	double lambda = 0.01; // 初始lambda.
	double sqrteps = sqrt(eps);
	int iter =0,i=0,j=0;
	char cause;
	bool breakOut = false;
	mat steps(p),yfit(lenx),r(lenx),betaold,JCB(lenx,p),Jplus(lenx+p,p),rplus(lenx+p);//临时数组变量
	for(i = 0 ;i< lenx ;i++)
	{
		dtmp = model(beta.M,&X[i]);
		r.M[i] = y[i]-dtmp;
		yfit.M[i] = dtmp;
	}
	sse = norm(r.M,lenx);
	iter = 0;
	cause = 'a';
	do
	{
		iter++;
		betaold = beta;
		sseold = sse;
		getjacobian(beta.M,p,fdiffstep,model,X,yfit.M,lenx,JCB);

		Jplus.zeros();
		memcpy(Jplus.M,JCB.M,lenx*p*sizeof(double));
		memcpy(rplus.M,r.M,lenx*sizeof(double));
itersatart:
		for(i=0;i<p;i++)
		{
			diagJtJm = 0.0;
			for(j=0;j<lenx;j++)
			{
				dtmp = 1.0;
				dtmp *=JCB.M[j*p+i];
				dtmp *=JCB.M[j*p+i];
				diagJtJm +=dtmp;
			}
			Jplus.M[(lenx+i)*p+i] = sqrt(lambda*diagJtJm);
			rplus.M[lenx+i]= 0.0;
		}
		mtdiv3(Jplus,rplus,steps);
		beta =  beta + steps;
		for(i = 0 ;i< lenx;i++)
		{
			dtmp= model(beta.M,&X[i]);
			r.M[i] = y[i]-dtmp;
			yfit.M[i]  =dtmp;
		}
		sse = norm(r.M,lenx);
		if(sse < sseold)
			lambda = max(0.1*lambda,eps);
		else
		{
			lambda *=10;
			if(lambda > 1e16)
			{
				breakOut = true;
				break;
			}
			beta = betaold;
			goto itersatart;
		}
		if(norm(steps.M,p) < betatol*(sqrteps+norm(beta.M,p)))
		{
			cause = 'x';
			break;
		}
		else
		{
			if (fabs(sse-sseold) <= rtol*sse )
			{
				cause = 'f';
				break ;
			}
			else
			{
				if (breakOut)
				{
					cause = 's';
					break ;
				}
			}
		}
	}while(iter < maxiter);
	memcpy(yr,r.M,lenx*sizeof(double));
	memcpy(yf,yfit.M,lenx*sizeof(double));
	if (iter >= maxiter)  cause = 'm';
	result.flag = cause;
	result.iter=iter;
	result.sse=sse;
	return cause;
}
