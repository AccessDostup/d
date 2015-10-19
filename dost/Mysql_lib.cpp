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
   	  con = driver->connect("TCP://127.0.0.1:3306", "root", "root");
    } catch (sql::SQLException &e) {
	  cout<<"ERR: NO CONNECT MySQL";
	  return false;
	}

   	try
	{
   	  con->setSchema("test");
   	  return true;
    } catch (sql::SQLException &e) {
	  cout<<"ERR: NO BD IN MySQL";
	  return false;
	}
}

bool Mysql_lib::Queryupdateinsert(const string& query)
{
	  pstmt = con->prepareStatement("INSERT INTO test(id) VALUES (?)");
	  for (int i = 1; i <= 10; i++) {
	    pstmt->setInt(1, i);
	    pstmt->executeUpdate();
	  }
	  delete pstmt;
    if(mysql_query(&conn, query)) return true;
	return false;
}

ResQuery Mysql_lib::Queryselect(const string& query)
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
