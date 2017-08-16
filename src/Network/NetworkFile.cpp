#include "NetworkFile.hpp"

#include <iostream>

#include "Systems/Logger.hpp"


jubeon::network::NetworkFile::NetworkFile()
	: sf::TcpSocket(), sf::InputStream()
{
}

jubeon::network::NetworkFile::~NetworkFile()
{
}

bool jubeon::network::NetworkFile::open(const std::string & host, const std::string & path, const unsigned short port)
{
	this->setBlocking(true);
	sf::Socket::Status st = this->connect(sf::IpAddress(host), port);	//いずれタイムアウト設定
	if (st != sf::Socket::Status::Done) {
		systems::Logger::warning("[NetworkFile]" + host + path + "への接続に失敗しました。");
		return false;
	}

	std::string query("");
	query += "GET /" + path + " HTTP/1.1\r\n";
	query += "Host: " + host + "\r\n";
	query += "Connection: close\r\n";
	query += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n";
	query += "\n\n";

	st = this->send(query.c_str(), query.size() + 1);

	// Receive an answer from the server
	char buffer[1024];
	std::size_t received = 0;
	this->receive(buffer, sizeof(buffer)-1, received);
	buffer[received] = '\0';
	std::cout << "The server said: " << buffer << std::endl;

	this->close();

	return true;
}

sf::Int64 jubeon::network::NetworkFile::read(void * data, sf::Int64 size)
{
	return sf::Int64();
}

sf::Int64 jubeon::network::NetworkFile::seek(sf::Int64 position)
{
	return sf::Int64();
}

sf::Int64 jubeon::network::NetworkFile::tell(void)
{
	return sf::Int64();
}

sf::Int64 jubeon::network::NetworkFile::getSize(void)
{
	return sf::Int64();
}
