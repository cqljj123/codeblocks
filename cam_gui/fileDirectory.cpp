/*文件夹的建立*/
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
	if(_access(path,6)==0){//获得目录的读写信息
		//cout<<"存在目录";
		return 1;
	}
	else
	{
		if(CreateDirectoryA(path,NULL))
		{
			//cout<<"成功建立\n";
			return 0;
		}
		else
		{
			//cout<<"建立失败\n";
			return -1;
		}
	}
	return 1;
}
//循环建立子目录
int TSCreateDirectory(const char *path)
{
	string pathstring = path;
	string tpath;/*临时路径*/
	for( unsigned int i = 3 ;i<pathstring.length();i++)
	{
		if (pathstring[i] =='\\')
		{
			tpath.clear(); /*清空路径*/
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
