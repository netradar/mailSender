#pragma once
#include "Poco/Net/MailMessage.h"
#include "Poco/Net/MailRecipient.h"
#include "Poco/Net/SMTPClientSession.h"
#include "Poco/Net/NetException.h"

#include "Poco/Net/SecureSMTPClientSession.h"
#include "Poco/Net/InvalidCertificateHandler.h"
#include "Poco/Net/AcceptCertificateHandler.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/SecureStreamSocket.h"
#include "Poco/Net/MailRecipient.h"

using Poco::Net::InvalidCertificateHandler;
using Poco::Net::AcceptCertificateHandler;
using Poco::Net::Context;
using Poco::Net::SSLManager;
using Poco::Net::SecureStreamSocket;

using Poco::Net::SocketAddress;
using Poco::Net::SecureSMTPClientSession;
using Poco::Net::SMTPClientSession;
using Poco::SharedPtr;
using Poco::Net::MailMessage;
using Poco::Net::MailRecipient;

using namespace Poco::Net;

class SmtpSrv
{
public:
	SmtpSrv(const std::string & smtpServer, int port, const std::string & username, const std::string & password);
	
	int sendMail(const std::string & from, const std::string & to, const std::string & subject, const std::string & content);
private:

	std::string	_username;
	std::string _password;
	std::string	_smtpServer;
	int _port;
};

