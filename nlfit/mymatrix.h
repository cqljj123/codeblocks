#ifndef _MYMATRIX_
#define _MYMATRIX_
#if  !defined(_my_api)
#define _my_api(rtype,name,arg)   EXTERN_C rtype __cdecl   name    arg;
#endif
//#include "stdafx.h"
//#include <iostream>
//using std::ostream;
//using std::cout;
using std::endl;
//#include <memory.h>
//#include <wchar.h>
namespace matrix
{
	class wrong{
	public:
		int p;
		int num;
		wchar_t descrip[100];
		wrong(int n):p(n){ }
		wrong(){}
		~wrong(){}
		void setDescrip(const wchar_t* a){wcscpy(descrip, a);}
	};

	template<typename T>
	class MTX{
	public:
		T *M;
		int ROW,COL;
		MTX(int m=1,int n =1)
		{
			ROW = m;
			COL =n;
			M = NULL;//初始指针
			int mn = m*n;
			if(mn<1) {printf("参数输入错误");throw wrong(); return; }
			M = new T[m*n];
			if(NULL==M){ printf("malloc memery failed!");throw wrong();}
		}
		~MTX(){
			delete [] M;//删除内存
			M = NULL;
		}
		MTX(T * a,int m ,int n=1)
		{
			M=NULL;
			ROW = m;
			COL =n;
			int mn = m*n;
			if(mn<1) {printf("参数输入错误"); throw wrong();return; }
			M = new T[m*n];
			if(NULL==M) { printf("内存分配错误") ;throw wrong();return; }
			memcpy(M,a,sizeof(T)*mn);
		}
		void resize(int m,int n)
		{
			if(m!=ROW || n!=COL)
			{
				ROW = m;
				COL = n;
				if(M!=NULL)
				{
					delete [] M;
				}
				M = new T[ROW*COL];
				if(NULL==M)  { printf("内存分配错误") ; throw wrong();return; }
			}
		}
		void show(int f=1);//显示
		T operator[](int i);
		MTX(const MTX<T> & a){
			if(this==&a) return ;
			ROW = a.ROW;
			COL = a.COL;
			M = new T[ROW*COL];
			if(NULL==M)  { printf("内存分配错误") ;throw wrong();return; }
			memcpy(M,a.M,sizeof(T)*ROW*COL);
		}
		MTX<T>  & operator=(const MTX<T> &r)
		{
			if(this == &r) return *this;
			COL = r.COL;
			ROW = r.ROW;
			if(NULL == M) return *this;
			delete [] M;
			M = NULL;
			M = new T[COL*ROW];
			if(NULL == M) return *this;
			memcpy(M,r.M,sizeof(T)*ROW*COL);
			return *this;
		}
		MTX<T> & operator-(const MTX<T> a){
			if(a.ROW != ROW || a.COL != COL){
				throw wrong();
			}
			for(int i=0;i<ROW*COL;i++) M[i] -= a.M[i];
			return *this;
		}
		MTX<T> & operator+(const T a){
			for(int i=0;i<ROW*COL;i++) M[i] += a;
			return *this;
		}
		MTX<T> & operator+(const MTX<T> a){
			if(a.ROW != ROW || a.COL != COL){
				throw wrong();
			}
			for(int i=0;i<ROW*COL;i++) M[i] += a.M[i];
			return *this;
		}
		void zeros(void )
		{
			memset(M,0,sizeof(T)*ROW*COL);
		}
		void plusrow(const MTX<T> &a)//并在下方
		{
			if(a.COL != COL || a.ROW<1||ROW<1)  { printf("矩阵大小错误") ;throw wrong();return; }
			T *TM =new T[(ROW+a.ROW)*COL];
			if(NULL == TM)  { printf("内存分配错误") ;throw wrong();return; }
			memcpy(TM,M,sizeof(T)*ROW*COL);
			memcpy(&(TM[ROW*COL]),a.M,sizeof(T)*a.ROW*a.COL);
			ROW +=a.ROW;
			if (NULL!=M) delete [] M;
			M = TM;
			return ;
		}
		void pluscol(const  MTX<T> &a)//并在右侧
		{
			int i,j;
			int rx,rx1,cx,rx2;
			if(a.ROW!= ROW || a.COL<1||COL<1)  { printf("矩阵大小错误") ;throw wrong();return; }
			T *TM =new T[(COL+a.COL)*ROW];
			if(NULL == TM)  { printf("内存分配错误") ;throw wrong();return; }
			for(i=0;i<ROW;i++)
			{
				rx = i*(COL+a.COL);
				rx1 = i*COL;
				for(j=0;j<COL;j++)
				{
					TM[rx+j] =M[rx1+j];
				}
				cx = rx+COL;
				rx2 = a.COL*i;
				for(j=0;j<a.COL;j++)
				{
					TM[cx+j] =a.M[rx2+j];
				}
			}
			COL +=a.COL;
			if (NULL!=M) delete [] M;
			M = TM;
			TM = NULL;
			return ;
		}
	};
	template<typename T>
	T MTX<T>::operator[](int i)
	{
		wrong wr(i);
		if(i>=ROW*COL)
		{
			wr.setDescrip(L"下标越界");
			throw wr;
			return M[ROW*COL];
		}
		else if( i<0)
		{
			wr.setDescrip(L"下标越界");
			throw wr;
			return M[0];
		}
		return M[i];
	}
	template<class T>
	ostream & operator<<(ostream & s,const MTX<T>& c)
	{
		s<<endl;
		int ro;
		for(int i = 0;i<c.ROW;i++)
		{
			ro = i*c.COL;
			for (int j = 0;j<c.COL;j++)
			{
				s<<"["<<i<<","<<j<<"]="<<c.M[ro+j]<<"\t";
			}
			s<<endl;
		}
		return s;
	}
	template<class T>
	MTX<T>  operator+(T a,const MTX<T>& b){
		MTX<T>c(b);
		for(int i=0;i<b.ROW*b.COL;i++) c.M[i] += b.M[i];
		return c;
	}
}
#define malacArry(typ,r,n)  matrix::MTX<typ> r##_Array (n) ;typ *&r=r##_Array.M;
#define malacArryInit(typ,r,n)  malacArry(typ,r,n)  r##_Array.zeros();

#endif
