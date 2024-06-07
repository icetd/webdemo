#ifndef SERVER_APPLICATION_H
#define SERVER_APPLICATION_H

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/File.h>
#include <Poco/FileChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FormattingChannel.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/Format.h>

#include "MyRequestHandlerFactory.h"

class ServerApp : public Poco::Util::ServerApplication
{
public:
    ServerApp() {}
    ~ServerApp() {}

protected:
    void initialize(Application &self);
    void initializeLogger();
    void uninitialize();
    int main(const std::vector<std::string> &args);
};

#endif
