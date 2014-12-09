#ifndef __DATABASE_H__
#define __DATABASE_H__
#pragma once
#pragma warning(disable:4996)
#include "sqlite3.h"
#include <stdlib.h>
#include <tchar.h>

class sqliteauto_finalize{
public:
	sqlite3_stmt *& stmt;
	sqliteauto_finalize(sqlite3_stmt *& stmt1):stmt(stmt1){
	}
	~sqliteauto_finalize(){
		if(stmt != NULL)
		{
			sqlite3_finalize(stmt);
			stmt = NULL;
		}
	}
};
class sqliteauto_close{
public:
	sqlite3 *& db;
	sqliteauto_close(sqlite3 *& stmt1):db(stmt1){
	}
	~sqliteauto_close(){
		if(db != NULL)
		{
			sqlite3_close(db);
			db = NULL;
		}
	}
};

/*���ݿ�����Զ�����*/
#define sqlitstmtdef(stmt) \
	sqlite3_stmt * stmt=NULL;\
	sqliteauto_finalize stmt##auto_d(stmt)

/*���ݿ��Զ�����*/
#define sqlitedbdef(db) \
	sqlite3 * db=NULL;\
	sqliteauto_close db##auto_d(db)

/*�ж�sqliteִ�н���Ƿ����*/
#define IFSQLITE_OK_DONE(result,db) \
	if((result) != SQLITE_OK && (result) != SQLITE_DONE)   \
   { \
	} 
	//return result;\
	//wcout<<L"SQLITE ERROR:"<<sqlite3_errmsg16(db)<<L"\n"; \
	//cout<<"error:"<<result;\

#define sqlitepreparedef(result,DB,sql,stmtc)  \
			result = sqlite3_prepare(DB,sql,-1,stmtc,NULL) ;\
			IFSQLITE_OK_DONE(result,DB); 

int createdatabase();

#endif