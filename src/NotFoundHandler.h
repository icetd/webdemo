#ifndef NOT_FOUND_HANDLER_H
#define NOT_FOUND_HANDLER_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

class NotFoundHandler : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        response.setContentType("application/json");
        std::ostream &ostr = response.send();
        ostr << "{ \"error\": \"Not Found\" }";
    }
};

#endif