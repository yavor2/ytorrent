#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <utils/utils.h>

#include <mutex>
#include <list>

#include "outputmessage.h"

namespace asio = boost::asio;

class Connection
{
	typedef std::function<void()> ConnectCallback;


public:
	Connection();
	~Connection();

	void connect(const std::string &host, const std::string &port, const ConnectCallback &cb);
	bool isConnected() const { return m_socket.is_open(); }


protected:
	void handleResolve(const boost::system::error_code &, asio::ip::basic_resolver<asio::ip::tcp>::iterator);
	void handleConnect(const boost::system::error_code &);
private:
	asio::deadline_timer m_delayedWriteTimer;
	asio::ip::tcp::resolver m_resolver;
	asio::ip::tcp::socket m_socket;

	ConnectCallback m_cb;

	std::shared_ptr<asio::streambuf> m_outputStream;
	asio::streambuf m_inputStream;
};
extern asio::io_service g_service;

#endif