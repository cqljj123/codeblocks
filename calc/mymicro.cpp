// mymicro.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <cctype>
#include "mymicro.h"
//#include <regex>
/*数字判断*/
double calcrnd()
{
	static long seed=GetTickCount();
	srand(seed);
	seed =rand();
	double a =(double)(seed)/RAND_MAX;
	return a;
}
bool ifanumber(char v)
{
    return (v>='0' && v<='9');
}
bool ifsuboralpha(char v)
{
    return (isalpha(v)||(v=='_'));
}
bool is_num_valid(const std::string& email)
{
    int doc = 0;
    char tpc = 0;
    for(int i = 0; i<email.length(); ++i)
    {
        tpc = email[i];
        if(tpc == '.')
        {
            ++doc;
            if(doc>1) return false;
            continue;
        }
        if(!ifanumber(tpc)) return false;

    }
    return true;
    //const std::regex pattern("\\d*(\\.)?\\d+");
    //return std::regex_match(email, pattern);
}
/*id判断*/

bool is_id_valid(const std::string& email)
{
    //cout<<email.c_str();
    bool ret = true;
    char tpc = 0;
    tpc = email[0];
    if(!ifsuboralpha(tpc)) return false;
    for(int i = 1; i<email.length(); ++i)
    {
        tpc = email[i];
        if( !(ifanumber(tpc) ||ifsuboralpha(tpc))) return false;

    }
    return true;
    //const std::regex pattern("^[a-zA-Z_](\\d*\\w*)+");
    //return std::regex_match(email, pattern);
}
/*执行*/
/*词法分析*/
void MYMICRO::parsetoken(std::vector<TOKEN> & tokens)
{
	tokens.clear();
	std::string tokenv ;
	char ch = 0;
	int flag = 0;
	int paras  =0;
	while(input->good())
	{
		*input>>ch;
		if(ch!='\n'&& isspace(ch)) continue; /*跳过空格*/
		input->putback(ch);
		flag = 0;
		while(input->good())
		{
			*input>>ch;
			switch (ch)
			{
			case TOKEN::ASSI:
				{
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::VAID;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::ASSI;
					temp.tokenval= '=';
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::MMULT:
				{
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::IDNM;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::MMULT;
					temp.tokenval= TOKEN::MMULT;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::DIV:
				{
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::IDNM;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::DIV;
					temp.tokenval= TOKEN::DIV;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::LINE:
				{
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::IDNM;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::SEMI;
					temp.tokenval= TOKEN::SEMI;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::COMM:
				{
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::IDNM;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::COMM;
					temp.tokenval= TOKEN::COMM;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::LPAR:
				{
					//std::cout<<paras<<"\n";
					if(paras<0) throw(PAERROR);
					++paras;
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::FUNC;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::LPAR;
					temp.tokenval= TOKEN::LPAR;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::RPAR:
				{
					//std::cout<<paras<<"\n";
					if(paras<1) throw(PAERROR);
					--paras;

					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::IDNM;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::RPAR;
					temp.tokenval= TOKEN::RPAR;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::MINU:
				{
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::IDNM;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::MINU;
					temp.tokenval= TOKEN::MINU;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::PLUS:
				{
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::IDNM;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::PLUS;
					temp.tokenval= TOKEN::PLUS;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::MULT:
				{
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::IDNM;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::MULT;
					temp.tokenval= TOKEN::MULT;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			case TOKEN::SEMI:
				{
					if(tokenv.size()>0)
					{
						TOKEN temp;
						temp.tokentype= TOKEN::IDNM;
						temp.tokenval= tokenv;
						tokens.push_back(temp);
						tokenv.clear();/*清空tokenval*/
					}
					TOKEN temp;
					temp.tokentype= TOKEN::SEMI;
					temp.tokenval= TOKEN::SEMI;
					tokens.push_back(temp);
					flag = 1;
					break;
				}
			default:
				tokenv.push_back(ch);
				break;
			}

			if(flag = 1)
			{
				break;
			}

		}

	}
	if(paras>0) throw(PAERROR);
	if(tokenv.size()>0)
	{
		TOKEN temp;
		temp.tokentype= TOKEN::IDNM;
		temp.tokenval= tokenv;
		tokens.push_back(temp);
		tokenv.clear();
	}
	/*判断token正确性*/
	for(auto item = tokens.begin();item != tokens.end();++item)
	{
		if(item->tokentype == TOKEN::FUNC)
		{
			if( ! is_id_valid(item->tokenval))
			{
				throw(IDERROR);
			}
		}
		if(item->tokentype == TOKEN::VAID)
		{
			if( ! is_id_valid(item->tokenval))
			{
				throw(IDERROR);
			}
		}
		if(item->tokentype == TOKEN::IDNM)
		{
			if(is_id_valid(item->tokenval))
			{
				item->tokentype = TOKEN::VAID;
			}
			else if(is_num_valid(item->tokenval))
			{
				item->tokentype = TOKEN::CONSTNUM;
			}
			else throw(NUERROR);
		}
		if(item != tokens.begin())
		{
			auto titem = item-1;
			if(item->tokentype == TOKEN::IDNM || item->tokentype == TOKEN::VAID)
			{
				if(titem->tokentype == TOKEN::IDNM || titem->tokentype == TOKEN::VAID)
				{
					throw(NUERROR);
				}
			}
		}
	}

}
/*计算解析组函数,以 , ; 为分割*/
double MYMICRO::parseexpr(std::vector<TOKEN> & tokens,std::vector<TOKEN>::iterator & tokeniter)
{
	TOKEN::token_type _type;/*栈中符号*/
	stack<char>  operstack;
	stack<double> valstack; /*符号栈和数值栈*/
	operstack.push('(');
	double ret;
	while(true)
	{
		/*如果为分号*/
		if(tokeniter==tokens.end() ||tokeniter->tokentype == TOKEN::SEMI || tokeniter->tokentype == TOKEN::COMM )
		{
			if(operstack.size()==1)
			{
				ret = valstack.top();
				break;
			}
			else
			{
				double num1 ,num2;
				if(valstack.size()<2) throw(PLERROR);
				num2 = valstack.top();
				valstack.pop();
				num1 = valstack.top();
				valstack.pop();
				switch (operstack.top())
				{
				case '+':
					ret = num2+num1;
					break;
				case '-':
					ret = num1-num2;
					break;
				case '*':
					ret = num2*num1;
					break;
				case '/':
					if(num2==0.0) ret =0.0;
					else
						ret = num1/num2;
					break;
				case '^':
					if(num1==0.0) ret = 0.0;
					else
						ret = pow(num1,num2);
					break;

				default:
					ret = 0.0;
				}
				valstack.push(ret);
				operstack.pop();
				continue;
			}
		}

		else if(tokeniter->tokentype == TOKEN::CONSTNUM) /*如果为常量或者变量*/
		{
			valstack.push(/*stod(tokeniter->tokenval)*/strtod((tokeniter->tokenval).c_str(),NULL));
		}
		else if(tokeniter->tokentype == TOKEN::VAID)
		{
			valstack.push(var_table[tokeniter->tokenval]);
		}
		else if(tokeniter->tokentype == TOKEN::FUNC)/*如果为函数*/
		{
			valstack.push(parsefunction(tokens,tokeniter));
			if(tokeniter != tokens.end()) --tokeniter;
		}
		else if(ifoperator(*tokeniter))
		{
			/*没有前面的操作符*/
			if(operstack.top()==TOKEN::LPAR && valstack.size()<1)
			{
				valstack.push(0);
				operstack.push(tokeniter->tokentype);
			}
			else
			{
				/*后面的操作符优先级交低*/
				if(operstack.size()<2)
				{
					operstack.push(tokeniter->tokentype);
				}
				else  if(open_lev(tokeniter->tokentype)<=open_lev(operstack.top()) )
				{
					double num1 ,num2;
					if(valstack.size()<2) throw(PLERROR);
					num2 = valstack.top();
					valstack.pop();
					num1 = valstack.top();
					valstack.pop();
					switch (operstack.top())
					{
					case '+':
						ret = num2+num1;
						break;
					case '-':
						ret = num1-num2;
						break;
					case '*':
						ret = num2*num1;
						break;
					case '/':
						if(num2==0.0) ret =0.0;
						else
							ret = num1/num2;
						break;
					case '^':
						if(num1==0.0) ret = 0.0;
						else
							ret = pow(num1,num2);
						break;

					default:
						ret = 0.0;
					}
					valstack.push(ret);
					operstack.pop();
					operstack.push(tokeniter->tokentype);
					/*计算值保存到*/
				}
				else
				{
					operstack.push(tokeniter->tokentype);
				}
			}

		}
		else if(tokeniter->tokentype == TOKEN::LPAR) /*左括号*/
		{
			operstack.push(tokeniter->tokentype);
		}
		else if(tokeniter->tokentype == TOKEN::RPAR)/*右括号*/
		{
			if(operstack.top()=='(')
			{
				operstack.pop();
				//++tokeniter;
				if(operstack.size()==0)
				{
					if(valstack.size()>0) ret = valstack.top();
					else ret =0;
					//--tokeniter;
					return ret;
				}
				++tokeniter;
				continue;
			}
			if(open_lev(operstack.top())>-1)
			{
				double num1 ,num2;
				if(valstack.size()<2) throw(PLERROR);
				num2 = valstack.top();
				valstack.pop();
				num1 = valstack.top();
				valstack.pop();
				switch (operstack.top())
				{
				case '+':
					ret = num2+num1;
					break;
				case '-':
					ret = num1-num2;
					break;
				case '*':
					ret = num2*num1;
					break;
				case '/':
					if(num2==0.0) ret =0.0;
					else
						ret = num1/num2;
					break;
				case '^':
					if(num1==0.0) ret = 0.0;
					else
						ret = pow(num1,num2);
					break;

				default:
					ret = 0.0;
				}
				valstack.push(ret);
				operstack.pop();
				operstack.push(tokeniter->tokentype);

			}
			else
			{
				operstack.pop();
			}
			--tokeniter;
		}
		if(tokeniter != tokens.end()) ++tokeniter;/*向下移动*/
	}
	return ret;

}
/*函数参数解析及其计算,添加函数到其中就可以退添加函数*/
double MYMICRO::parsefunction(std::vector<TOKEN> & tokens,std::vector<TOKEN>::iterator & tokeniter)
{
	/*参数栈*/
	//stack<double> params;
	vector<double> params;
	//double param=0;
	double ret=0;
	//int leftp=1;/*记录括号数*/
	auto func = *tokeniter;
	++tokeniter;/*读掉当前函数名*/
	++tokeniter;/*读掉一个括号*/
	while(true)
	{
		params.push_back(parseexpr(tokens,tokeniter));
		//params.push();
		if(tokeniter != tokens.end() && tokeniter->tokentype == TOKEN::COMM)
		{
			++tokeniter;
			continue;
		}
		else
		{
				if(tokeniter != tokens.end()) ++tokeniter;
				break;
		}
	}
	if(func.tokenval =="sin")
	{
		if(params.size()==1)
		{
			ret = sin(params[0]);
		}
		else throw(FPERROR3);
	}
	else if(func.tokenval =="cos")
	{
		if(params.size()==1)
		{
			ret = cos(params[0]);
		}
		else throw(FPERROR3);
	}
	else if(func.tokenval =="log")
	{
		if(params.size()==1)
		{
			ret = log(params[0]);
		}
		else if(params.size()==2)
		{
			ret = log(params[1])/log(params[0]);
		}
		else throw(FPERROR3);
	}
	else if(func.tokenval =="global")
	{
		for(auto it:this->var_table)
		{
			cout<<it.first<<":\t"<<it.second<<"\n";
		}
	}
	else if(func.tokenval =="help")
	{
		cout<<"help funciton\n sorry now it very simpleness\n later it will be detailedness! \n";
		cout<<"functions:\nhelp(),global()\nabs(),max(),min(),\nexp(),log(base,index),rand(),sum(),\npi(),sin(),cos()\n";
	}
	else if(func.tokenval =="max")
	{
		double tp = 0.0;
		if(params.size()<1)
		{
			throw(FPERROR3);
		}
		else
		{
			tp = params[0];
		}
		for(int i = 1; i<params.size();++i)
		{
			if(tp<params[i])
			{
				tp = params[i];
			}
		}
		ret = tp;
	}
	else if(func.tokenval =="min")
	{
		double tp = 0.0;
		if(params.size()<1)
		{
			throw(FPERROR3);
		}
		else
		{
			tp = params[0];
		}
		for(int i = 1; i<params.size();++i)
		{
			if(tp>params[i])
			{
				tp = params[i];
			}
		}
		ret = tp;
	}
	else if(func.tokenval =="rand")
	{
		//double tp = 0.0;
		if(params.size()>1)
		{
			throw(FPERROR3);
		}
		ret = calcrnd();
	}
	else if(func.tokenval =="sum")
	{
		double tp = 0.0;
		if(params.size()<1)
		{
			throw(FPERROR3);
		}
		for(int i = 0; i<params.size();++i)
		{
			tp+=params[i];
		}
		ret = tp;
	}
	else if(func.tokenval =="exp")
	{
		if(params.size()==1)
		{
			ret = exp(params[0]);
		}
		else throw(FPERROR3);
	}
	else if(func.tokenval =="abs")
	{
		if(params.size()==1)
		{
			ret = abs(params[0]);
		}
		else throw(FPERROR3);
	}
	else if(func.tokenval =="pi")
	{
		ret = 3.14159265358979;
	}
	else
	{
		throw(FPERROR2);
	}
	return ret;
}
	double MYMICRO::eval(int &err)
	{
		err = -1;
		double ret=0,tp;
		double *val;
		try
		{
			auto tokeniter = cur_tokens.begin();
			while(tokeniter != cur_tokens.end())
			{
				auto titer2= tokeniter+1;
				if(titer2 != cur_tokens.end() &&titer2->tokentype == TOKEN::ASSI && tokeniter->tokentype == TOKEN::VAID)
				{
					val = &this->var_table[tokeniter->tokenval];
					tokeniter = titer2+1;
				}
				else
				{
					val = &this->var_table["ans"];
				}
				if(tokeniter == cur_tokens.end()) return 0.0;
				double t = parseexpr(cur_tokens,tokeniter);
				*val = t;
				ret = *val;
				if(tokeniter != cur_tokens.end()) ++tokeniter;
			}
		}
		catch(MYMICRO::ERRORTYPE e)
		{
			err= e;
		}
		catch(...)
		{
			err = 100;
		}
		return ret;

	}
/*主函数:为eval,计算字符串,err错误信息,参考mymicro 中错误enum*/
double MYMICRO::eval(string evalstr,int &err)
{
	err = -1;
	getstr(evalstr);/*获得字符串*/
	//std::vector<TOKEN> tokens;
	try
	{
		parsetoken();
	}
	catch(MYMICRO::ERRORTYPE e)
	{
		err= e;
		return 0.0;
	}
	catch(...)
	{
		err = 100;
		return 0.0;
	}
	return this->eval(err);
}

