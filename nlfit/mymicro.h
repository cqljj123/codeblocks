#ifndef __MYMICRO_H__
#define __MYMICRO_H__
#include <string>
#include <vector>
#include <map>
#include <set>
//#include <deque>
#include <stack>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;
class TOKEN{
public:
	typedef enum TOKENTYPE
	{
		STOP ,
		VAID=1, /*变量*/
		FUNC=2, /*函数*/
		IDNM=3,/*函数或者变量*/
		CONSTNUM=4,
		FUNCTION, /*自定义函数*/
		PLUS = '+', /*加*/
		MINU = '-',
		MULT = '*',
		MMULT='^', /*乘方*/
		DIV ='/',
		MOD = '%', /*取余*/
		LPAR = '(',
		RPAR = ')',
		COLO = ':',
		ASSI = '=',
		SEMI = ';',
		LINE = '\n',
		COMM = ','
	} token_type;
	std::string tokenval; /*tokenstring*/
	token_type tokentype; /*token_type*/
	//	int tokenpos; /*token position*/
};
class MYMICRO
{
public:
	void clear()
	{
		var_table.clear();/*清空数据表*/	
	}
	MYMICRO()
	{
		//var_table["pi"] = 3.14159265358979;
		//var_table["e"] = 2.71828182845905;
		input = nullptr;
	}
	std::map<std::string,double> var_table; /*变量表*/
	std::set<std::string> fun_table; /*函数表*/
	typedef enum ERRORTYPE{
		IDERROR=1, /*变量错误*/
		FUERROR, /*函数错误*/
		NUERROR ,/*数字错误*/
		PAERROR,/*括号不等*/
		PLERROR,
		FPERROR2, /*函数不存在*/
		FPERROR3, /*函数参数个数错误*/
		FPERROR4/*函数运行错误*/

	} errortype;
	string errstr(int err)
	{

		switch (err)
		{
		case IDERROR:
			return string("variable name error");
		case FUERROR: /*函数错误*/
			return string("function name error");
		case NUERROR :/*数字错误*/
			return string("number error");
		case PAERROR:/*括号不等*/
			return string("parenthesis error");
		case PLERROR:
			return string("parenthesis error");
		case FPERROR2: /*函数不存在*/
			return string("function exist error");
		case FPERROR3: /*函数参数个数错误*/
			return string("function params error");
		case FPERROR4:/*函数运行错误*/
			return string("function running error");
		default:
			return string("");
			break;
		}
	}
	/*运算符优先级*/
	int open_lev(char op1)
	{
		//按数学上等级划分
		switch(op1)
		{
		case '<':
		case '>':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 3;
		default:
			return -1;
		}
	}
	/*计算表达式*/
	bool ifoperator(TOKEN tokeniter)
	{
		switch (tokeniter.tokentype)
		{
		case TOKEN::DIV:
		case TOKEN::MULT:
		case TOKEN::MINU:
		case TOKEN::MMULT:
		case TOKEN::PLUS:
		case TOKEN::MOD:
			return true;
		default:
			return false;
		}
		return false;
	}
	double parseexpr(std::vector<TOKEN> & tokens,std::vector<TOKEN>::iterator & tokeniter);
	/*计算函数*/
	double parsefunction(std::vector<TOKEN> & tokens,std::vector<TOKEN>::iterator & tokeniter);
	void getstr(std::string & st)
	{
		cur_string = st;
		getstr();
		//input = new std::istringstream(st);
	}
	void getstr()
	{
		if(input ==nullptr) delete input;
		input = new std::istringstream(cur_string);	
	}
	/*解析*/
	double eval(int &err);
	double eval(string evalstr,int &err);
	void parsetoken(std::vector<TOKEN> & tokens);
	void parsetoken()
	{
		parsetoken(cur_tokens);
	}
	std::istream * input;
	std::vector<TOKEN>  cur_tokens;
	std::string cur_string;


};

#endif