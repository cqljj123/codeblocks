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
		VAID=1, /*����*/
		FUNC=2, /*����*/
		IDNM=3,/*�������߱���*/
		CONSTNUM=4,
		FUNCTION, /*�Զ��庯��*/
		PLUS = '+', /*��*/
		MINU = '-',
		MULT = '*',
		MMULT='^', /*�˷�*/
		DIV ='/',
		MOD = '%', /*ȡ��*/
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
		var_table.clear();/*������ݱ�*/	
	}
	MYMICRO()
	{
		//var_table["pi"] = 3.14159265358979;
		//var_table["e"] = 2.71828182845905;
		input = nullptr;
	}
	std::map<std::string,double> var_table; /*������*/
	std::set<std::string> fun_table; /*������*/
	typedef enum ERRORTYPE{
		IDERROR=1, /*��������*/
		FUERROR, /*��������*/
		NUERROR ,/*���ִ���*/
		PAERROR,/*���Ų���*/
		PLERROR,
		FPERROR2, /*����������*/
		FPERROR3, /*����������������*/
		FPERROR4/*�������д���*/

	} errortype;
	string errstr(int err)
	{

		switch (err)
		{
		case IDERROR:
			return string("variable name error");
		case FUERROR: /*��������*/
			return string("function name error");
		case NUERROR :/*���ִ���*/
			return string("number error");
		case PAERROR:/*���Ų���*/
			return string("parenthesis error");
		case PLERROR:
			return string("parenthesis error");
		case FPERROR2: /*����������*/
			return string("function exist error");
		case FPERROR3: /*����������������*/
			return string("function params error");
		case FPERROR4:/*�������д���*/
			return string("function running error");
		default:
			return string("");
			break;
		}
	}
	/*��������ȼ�*/
	int open_lev(char op1)
	{
		//����ѧ�ϵȼ�����
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
	/*������ʽ*/
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
	/*���㺯��*/
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
	/*����*/
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