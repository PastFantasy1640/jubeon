#pragma once

#ifndef JUBEON_NETWORK_NETWORKFILE_HPP
#define JUBEON_NETWORK_NETWORKFILE_HPP

#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace network {
		class NetworkFile : sf::InputStream {
		public:
			NetworkFile();
			virtual ~NetworkFile();

			bool open(const std::string & network_pass);

			virtual sf::Int64 read(void * data, sf::Int64 size) override;

			virtual sf::Int64 seek(sf::Int64 position) override;

			virtual sf::Int64 tell(void) override;

			virtual sf::Int64 getSize(void) override;

		private:

		};
	}
}

#endif