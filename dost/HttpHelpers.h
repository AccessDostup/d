/*
	This file is a part of madfish-webtoolkit project.
	http://code.google.com/p/madfish-webtoolkit/

	(c) 2009 Alexander "Mad Fish" Chehovsky
	See License.txt for licensing information.
*/

#pragma once
#ifndef _HTTPHELPERS_H
#define	_HTTPHELPERS_H

#include "Http.h"
#include "FileUtils.h"
#include "Util.h"

#include <string>
#include <map>


namespace WebToolkit
{

struct Mapping
{
	HttpMethod allowedMethod;
	HttpHandler* handler;
	bool handlerAutoDelete;
	HttpHandler* errorHandler;
	bool errorHandlerAutoDelete;
	FileUploadHandler* fileHandler;
	bool fileHandlerAutoDelete;
};

class Dispatcher:public HttpHandler
{
protected:
	std::map<std::string,Mapping> dispatchMap;
	std::string defaultHandler;
public:
	Dispatcher();
	~Dispatcher();
	void AddMapping(const std::string& st,HttpMethod allowedMethod,HttpHandler* handler,bool handlerAutoDelete=false,HttpHandler* errorHandler=NULL,bool errorHandlerAutoDelete=false,FileUploadHandler* fileHandler=NULL,bool fileHandlerAutoDelete=false);
	void SetDefaultHandler(std::string defaultHandler);
	void Invoke(const std::string& what,HttpServerContext* context);
	virtual void Handle(HttpServerContext* context)=0;
};

class HostDispatcher:public Dispatcher
{
public:
	void Handle(HttpServerContext* context);
};

class URIDispatcher:public Dispatcher
{
public:
	void Handle(HttpServerContext* context);
};

class Redirector:public HttpHandler
{
protected:
	std::string redirectURI;
public:
	Redirector(const std::string& uri);
	void Handle(HttpServerContext* context);
};

template<class T>
class HttpHandlerConnector:public HttpHandler
{
public:
	typedef void (T::*HandlerFunction)(HttpServerContext* context);
	T* obj;
	HandlerFunction fn;
	HttpHandlerConnector(T* o,HandlerFunction f):obj(o),fn(f)
	{
	}
	void Handle(HttpServerContext* context)
	{
		context->HtmlBody = CoreToolkit::FileUtils::ReadFile("template/header.html");
		(obj->*fn)(context);
		context->HtmlBody.append(CoreToolkit::FileUtils::ReadFile("template/footer.html"));
		CoreToolkit::Util::Substitute(context->HtmlBody, "<%basepath%>", "http://" + context->requestHeader.host, true);
		context->responseBody << context->HtmlBody;
		context->HtmlBody.clear();
	}
};

template<class T>
class HttpFileHandlerConnector:public FileUploadHandler
{
public:
	typedef void (T::*HandlerFunction)(HttpServerContext* context,const std::string& name,const std::string& filename,CoreToolkit::InputStream* stream);
	T* obj;
	HandlerFunction fn;
	HttpFileHandlerConnector(T* o,HandlerFunction f):obj(o),fn(f)
	{
	}
	void HandleFileUpload(HttpServerContext* context,const std::string& name,const std::string& filename,CoreToolkit::InputStream* stream)
	{
		(obj->*fn)(context,name,filename,stream);
	}
};

}

#endif

