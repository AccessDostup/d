#ifndef _MYSQL_LIB_H
#define	_MYSQL_LIB_H

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#ifdef WIN32
#include <windows.h>
#else
#include <stdio.h>
#endif

using namespace std;

namespace CoreToolkit
{

struct ResQuery
{
	sql::ResultSet *res;
	bool err;
};

struct InsertQuery
{
	string *NameTable;

	sql::ResultSet *res;
	bool err;
};

class Mysql_lib
{
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *pstmt;

public:
	static bool Connect();
	static bool Queryupdateinsert(const string& query);
	static ResQuery Queryselect(const string& query);
};

}

#endif

