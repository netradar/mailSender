#include "HttpSrv.h"

int HttpSrv::main(const vector<string>&)
{
    HTTPServer s(new MyRequestHandlerFactory, ServerSocket(9090), new HTTPServerParams);

    s.start();
    std::cout << std::endl << "Server started" << std::endl;

    waitForTerminationRequest();

    std::cout << std::endl << "Shutting down..." << std::endl;
    s.stop();

    return Application::EXIT_OK;
}

void MyRequestHandler::handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
{

    resp.setStatus(HTTPResponse::HTTP_OK);
    resp.setContentType("text/html");

    std::ostream& response = resp.send();


    //istream &is = req.stream();

    Poco::Net::HTMLForm form(req, req.stream());
    unordered_map<string, string> emailInfo;
    for (const auto& it : form)
    {
        emailInfo.insert(pair<string, string>(it.first, it.second));
    }
    if (emailInfo.size() != 3) {
        response << FAIL_RESPONSE << "parameters are too much or too less";
        response.flush();
        return;
    }

    if (emailInfo["receiver"] == "" || !checkFormat(emailInfo["receiver"])) {
        response << FAIL_RESPONSE << "email address is not correct";
        response.flush();
        return;
    }

    SmtpSrv smtp(smtpServer, port, username, password);

    int ret = smtp.sendMail(username, emailInfo["receiver"], emailInfo["subject"], emailInfo["content"]);

    if (ret == 0) {
        response << SUCCESS_RESPONSE;
    }
    else {
        response << FAIL_RESPONSE << "code is " << ret;
    }

    response.flush();


}
