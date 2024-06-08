#ifndef ROUTER_H
#define ROUTER_H

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/URI.h>
#include <map>
#include <functional>

class Router : public Poco::Net::HTTPRequestHandlerFactory
{
public:
    Router(){};
    ~Router(){};

    using RouteHandler = std::function<void(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse&)>;
    void addRoute(const std::string& uri, RouteHandler handler);

    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request) override;

    void setDefaultHandler(RouteHandler handler);

private:
    class RouteHandlerImpl : public Poco::Net::HTTPRequestHandler
    {
    public:
        RouteHandlerImpl(RouteHandler handler) : handler(handler) {}

        void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override {
            handler(request, response);
        }

    private:
        RouteHandler handler;
    };

    std::map<std::string, RouteHandler> m_routes;
    RouteHandler m_defaultHandler;
};

#endif