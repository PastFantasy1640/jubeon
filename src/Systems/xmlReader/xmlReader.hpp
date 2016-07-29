#pragma once

#ifndef JUBEON_SYSTEM_XMLREADER_HPP
#define JUBEON_SYSTEM_XMLREADER_HPP

#include <string>
#include <fstream>

namespace jubeat_online {
	namespace system {
		class xmlReader {
		private:
			const std::string filename;

			xmlReader();
		public:
			xmlReader(const std::string filename);
			virtual ~xmlReader();
		};
	}
}

#endif