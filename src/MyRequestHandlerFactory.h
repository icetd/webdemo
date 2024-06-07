#ifndef MY_REQUEST_HANDLER_FACTORY
#define MY_REQUEST_HANDLER_FACTORY

#include "RootHandler.h"
#include <Poco/Net/HTTPServer.h>

class MyRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    MyRequestHandlerFactory(){};
    ~MyRequestHandlerFactory(){};

public:
    virtual Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
        return new RootHandler;
    };
};

#endif