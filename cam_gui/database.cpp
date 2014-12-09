#include "database.h"
#include <direct.h>
#include <string>
#include <wx/string.h>
#include <wx/wx.h>
int createdatabase()
{
	char  buf[200];
	getcwd(buf,199);
	sqlitedbdef(db);
	wxString path; 
	path.Printf("%s\\data\\database.db",buf);
	int result = sqlite3_open(path.c_str(), &db );
	IFSQLITE_OK_DONE(result,db);/*打开数据库*/
	sqlitstmtdef(stmtC);/*定义执行语句*/
	wxString create("CREATE TABLE IF NOT EXISTS data(time timestamp  primary key,wd CHARACTER(20) ,gq CHARACTER(20) ,yq CHARACTER(20) ,sd CHARACTER(20),ynd CHARACTER(20))");
	sqlitepreparedef(result,db,create.c_str(),&stmtC);	 /*准备结构*/
	result = sqlite3_step(stmtC); /*执行*/
	if(result != SQLITE_DONE) 
	{
		return result;
	}
	//wxMessageBox("create");
	return SQLITE_OK;
}
