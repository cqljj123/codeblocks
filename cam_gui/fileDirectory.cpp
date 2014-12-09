/*�ļ��еĽ���*/
//#include "stdafx.h"
#include "fileDirectory.h"
#include <Windows.h>
#include <io.h>
#include "CharacterUtil.h"
#include "fileDirectory.h"
using namespace std;
int TSCreateDirectorySub(const char *path);
int TSCreateDirectorySubws( wstring upath)
{
	char * path=NULL;
	CharacterUtil::UNICODE_to_ANSI_ptr(upath.c_str(),path);
	string wpath(path);
	if(path != NULL)
	{
		delete path;
	}
	return TSCreateDirectory(wpath.c_str());
}
int TSCreateDirectorySub(const char *path)
{
	if(_access(path,6)==0){//���Ŀ¼�Ķ�д��Ϣ
		//cout<<"����Ŀ¼";
		return 1;
	}
	else
	{
		if(CreateDirectoryA(path,NULL))
		{
			//cout<<"�ɹ�����\n";
			return 0;
		}
		else
		{
			//cout<<"����ʧ��\n";
			return -1;
		}
	}
	return 1;
}
//ѭ��������Ŀ¼
int TSCreateDirectory(const char *path)
{
	string pathstring = path;
	string tpath;/*��ʱ·��*/
	for( unsigned int i = 3 ;i<pathstring.length();i++)
	{
		if (pathstring[i] =='\\')
		{
			tpath.clear(); /*���·��*/
			tpath = pathstring.substr(0,i);
			//cout<<i<<":"<<tpath<<"\n";
			if(TSCreateDirectorySub(tpath.c_str())<0)
			{
				return -1;
			}
		}
	}
	return 1;
	//return TSCreateDirectorySub(pathstring.c_str());
}
