#include "ServerApp.h"

void ServerApp::initialize(Application &self)
{
    loadConfiguration(); // load default configuration files, if present
    ServerApplication::initialize(self);
    initializeLogger();
}

void ServerApp::initializeLogger()
{
    Poco::AutoPtr<Poco::FileChannel> pFileChannel(new Poco::FileChannel);
    // 设置日志文件路径
    pFileChannel->setProperty("path", "sample.log");

    // 设置日志文件旋转大小为 10 MB
    pFileChannel->setProperty("rotation", "10 M");

    // 设置日志文件备份策略为基于时间戳的备份
    pFileChannel->setProperty("archive", "timestamp");

    // 设置是否压缩备份文件
    pFileChannel->setProperty("compress", "false");

    // 设置保留的备份文件数量为 2
    pFileChannel->setProperty("purgeCount", "1");

    // 设置日志时间戳的时区为本地时间
    pFileChannel->setProperty("times", "local");

    // 设置是否在每次写入日志消息后立即刷新文件缓冲区
    pFileChannel->setProperty("flush", "false");

    // 设置是否在打开日志文件时进行旋转
    pFileChannel->setProperty("rotateOnOpen", "true");

    // 格式化输出通道（支持的格式化语句参见Poco::PatternFormatter类说明
    Poco::AutoPtr<Poco::PatternFormatter> pPatternFmt(new Poco::PatternFormatter("%L%Y-%m-%d %H:%M:%S [%q]: %t"));
    Poco::AutoPtr<Poco::FormattingChannel> pFmtChannel(new Poco::FormattingChannel(pPatternFmt, pFileChannel));

    Poco::Logger::root().setChannel(pFmtChannel);
}

void ServerApp::uninitialize()
{
    ServerApplication::uninitialize();
}

int ServerApp::main(const std::vector<std::string> &args)
{
    Poco::UInt16 port = 1234;
    Poco::Net::HTTPServerParams *pParams = new Poco::Net::HTTPServerParams;
    pParams->setMaxQueued(10);
    pParams->setMaxThreads(16);
    Poco::Net::ServerSocket svs(port); // set-up a server socket

    Poco::Net::HTTPServer server(new MyRequestHandlerFactory(), svs, pParams);
    server.start();

    Poco::Logger &logger = Poco::Logger::root();
    poco_information(logger, "================ App Start ================");
    waitForTerminationRequest();
    server.stop();
    return Application::EXIT_OK;
}