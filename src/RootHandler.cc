#include "RootHandler.h"
#include <Poco/Net/HTMLForm.h>
#include <Poco/StreamCopier.h>
#include <iostream>
#include <Poco/Util/Application.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

static void saveLog(Poco::Net::HTTPServerRequest &request) {
    Poco::Logger &logger = Poco::Logger::root();
    // 记录客户端 IP 地址
    std::string clientIP = request.clientAddress().host().toString();
    logger.information("Client IP: " + clientIP);

    // 记录请求方法
    std::string method = request.getMethod();
    logger.information("Method: " + method);

    // 记录请求 URI
    std::string uri = request.getURI();
    logger.information("URI: " + uri);

    // 记录 HTTP 版本
    std::string version = request.getVersion();
    logger.information("Version: " + version);

    // 记录请求头
    const Poco::Net::NameValueCollection &headers = request;
    for (const auto &header : headers) {
        logger.information(header.first + ": " + header.second);
    }
    logger.information("Done\n");
}

static void sendJSONResponse(Poco::Net::HTTPServerResponse &response, const Poco::JSON::Object &jsonobj) {
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    std::ostream &ostr = response.send();
    jsonobj.stringify(ostr);
}

void RootHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response)
{
    saveLog(request);

    // 设置CORS响应头部
    response.set("Access-Control-Allow-Origin", "*");
    response.set("Access-Control-Allow-Methods", "GET, POST");
    response.set("Access-Control-Allow-Headers", "Content-Type");

    // 如果是OPTIONS请求，响应204并返回
    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
        response.setContentLength(0);
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
        response.send();
        return;
    }

    Poco::JSON::Object jsonObj;
    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {

        jsonObj.set("method", "GET");
        Poco::JSON::Array fArr;
        Poco::JSON::Object orange;
        orange.set("name", "orange");
        orange.set("color", "orange");
        
        fArr.add(orange);
        Poco::JSON::Object apple;
        apple.set("name", "apple");
        apple.set("color", "red");
        fArr.add(apple);
        Poco::JSON::Object strawberry;
        strawberry.set("name", "strawberry");
        strawberry.set("color", "red");
        fArr.add(strawberry);
        jsonObj.set("fruits", fArr);

    } else if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
        jsonObj.set("method", "POST");
        Poco::JSON::Array fArr;
        Poco::JSON::Object orange;
        orange.set("name", "orange");
        orange.set("color", "orange");
        
        fArr.add(orange);
        Poco::JSON::Object apple;
        apple.set("name", "apple");
        apple.set("color", "red");
        fArr.add(apple);
        Poco::JSON::Object strawberry;
        strawberry.set("name", "strawberry");
        strawberry.set("color", "red");
        fArr.add(strawberry);
        jsonObj.set("fruits", fArr);

#if 0
        // Read the request body
        std::istream &istr = request.stream();
        std::string body;
        Poco::StreamCopier::copyToString(istr, body);
        std::cout << "Request Body: " << body << std::endl;

#endif
        // DO POST 处理表单数据
        if (request.getContentType().find("application/x-www-form-urlencoded") != std::string::npos ||
            request.getContentType().find("multipart/form-data") != std::string::npos) {
            Poco::Net::HTMLForm form(request, request.stream());
            for (const auto &field : form) {
                std::cout << "Field name: " << field.first << ":" << field.second << std::endl;
            }
        } else if (request.getContentType().find("application/json") != std::string::npos) {
                std::istream& istr = request.stream();
                Poco::JSON::Parser parser;
                Poco::Dynamic::Var result = parser.parse(istr);
                Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();

                std::ostringstream oss;
                json->stringify(oss, 2);  // pretty print with indentation
                std::cout << "Parsed JSON: " << oss.str() << std::endl;
        }

    } else {
        jsonObj.set("error", "Method not allowed");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
    }
    sendJSONResponse(response, jsonObj);
}