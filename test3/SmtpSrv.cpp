#include "SmtpSrv.h"

SmtpSrv::SmtpSrv(const std::string & smtpServer, int port, const std::string & username, const std::string & password)
{
    _username = username;
    _password = password;
    _smtpServer = smtpServer;
    _port = port;

}


int SmtpSrv::sendMail(const std::string& from, const std::string& to, const std::string& subject, const std::string& content)
{

    try {
        SecureSMTPClientSession secure(_smtpServer, _port);
        secure.open();
        Poco::Net::initializeSSL();

        SharedPtr<InvalidCertificateHandler> pCert = new AcceptCertificateHandler(false);
        Context::Ptr pContext = new Poco::Net::Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        SSLManager::instance().initializeClient(0, pCert, pContext);

        secure.login();
        bool tlsStarted = secure.startTLS(pContext);
        if (!tlsStarted) {
            return -1;
        }

        MailMessage message;
        message.setSender(from);
        message.addRecipient(MailRecipient(MailRecipient::PRIMARY_RECIPIENT, to));
        message.setSubject(subject);
        message.setContentType("text/plain; charset=UTF-8");
        message.setContent(content, MailMessage::ENCODING_8BIT);
        secure.login(SMTPClientSession::AUTH_LOGIN, _username, _password);
        secure.sendMessage(message);
        secure.close();

    }catch (Poco::Net::SMTPException& e) {
        return e.code();
    }catch (Poco::Net::NetException& e) {
        return e.code();
    }catch (Poco::Exception& e) {
        return e.code();
    }
	return 0;
}
