#pragma once
#ifndef _MYSQL_LIB_H
#define	_MYSQL_LIB_H

#include <mysql.h>

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
	MYSQL_RES *res;
	bool err;
};

class Mysql_lib
{
  MYSQL conn;
  MYSQL_ROW row;
public:
	static bool Connect();
	static bool Queryupdateinsert(const std::string& query);
	static ResQuery Queryselect(const std::string& query);
};

}

#endif

