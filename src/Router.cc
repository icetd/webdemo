#include "Router.h"

void Router::addRoute(const std::string &uri, RouteHandler handler)
{
    m_routes[uri] = handler;
}

Poco::Net::HTTPRequestHandler *Router::createRequestHandler(const Poco::Net::HTTPServerRequest &request)
{
    Poco::URI uri(request.getURI());
    auto it = m_routes.find(uri.getPath());
    if (it != m_routes.end()) {
        return new RouteHandlerImpl(it->second);
    } else {
        return new RouteHandlerImpl(m_defaultHandler);
    }
}

void Router::setDefaultHandler(RouteHandler handler)
{
    m_defaultHandler = handler;
}