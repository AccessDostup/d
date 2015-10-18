/*
	This file is a part of madfish-webtoolkit project.
	http://code.google.com/p/madfish-webtoolkit/

	(c) 2009 Alexander "Mad Fish" Chehovsky
	See License.txt for licensing information.
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Mysql_lib.h"
#include <stdlib.h>

using namespace std;

namespace CoreToolkit
{

bool Mysql_lib::Connect()
{
   	try
	{
        mysql_init(&conn);
        mysql_real_connect(&conn, "localhost", "root", "", "shop", 0, NULL, 0);
    }
    catch(exception& e)
	{
		LOG(LogError)<<e.what();
		return false;
	}
        mysql_query(&conn, "SET NAMES 'utf8'");

	return true;
}

bool Mysql_lib::Queryupdateinsert(const std::string& query)
{
    if(mysql_query(&conn, query)) return true;
	return false;
}

ResQuery Mysql_lib::Queryselect(const std::string& query)
{
    ResQuery ressource;

    if(mysql_query(&conn, query))
    {
       ressource.err = true;
       return ressource;
    }

    ressource.res = mysql_store_result(&conn);

    if(ressource.res == NULL)
       ressource.err = true;
    return ressource;
}

}
