#pragma once

#ifndef JUBEON_NETWORK_NETWORKFILE_HPP
#define JUBEON_NETWORK_NETWORKFILE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

namespace jubeon {
	namespace network {
		class NetworkFile : public sf::InputStream, protected sf::TcpSocket{
		public:
			NetworkFile();
			virtual ~NetworkFile();

			bool open(const std::string & host, const std::string & path, const unsigned short port = 80);

			virtual sf::Int64 read(void * data, sf::Int64 size) override;

			virtual sf::Int64 seek(sf::Int64 position) override;

			virtual sf::Int64 tell(void) override;

			virtual sf::Int64 getSize(void) override;

		private:

		};
	}
}

#endif