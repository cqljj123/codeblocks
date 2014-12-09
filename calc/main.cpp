#include "mymicro.h"
using namespace std;
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

int main()
{
    calc();
    cout << "Hello world!" << endl;
    return 0;
}
