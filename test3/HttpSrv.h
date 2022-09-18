#pragma once
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Util/ServerApplication.h>

#include "SmtpSrv.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
using namespace std;

using namespace Poco::Net;
using namespace Poco::Util;

#define FAIL_RESPONSE       "send failed:"
#define SUCCESS_RESPONSE   "send successfully"

class MyRequestHandler : public HTTPRequestHandler
{
public:
    virtual void handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp);

private:
    bool checkFormat(const string& emailAddress) {
        //ChaoLi: to use regualr expression to do email address format checking here
        return true;
    }

private:
    const string smtpServer = "smtp.gmail.com";
    int port = 587;
    const string username = "username";
    const string password = "password";

};

class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
    virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest&)
    {
        return new MyRequestHandler;
    }
};

class HttpSrv: public ServerApplication
{
protected:
    int main(const vector<string>&);
   
};

