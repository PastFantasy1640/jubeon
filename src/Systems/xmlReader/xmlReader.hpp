#pragma once

#ifndef JUBEON_SYSTEM_XMLREADER_HPP
#define JUBEON_SYSTEM_XMLREADER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <memory>

namespace jubeat_online {
	namespace system {
		class xmlReader {
		private:
			const std::string filename;

			//leaf��0�Ԗڂ͂��̗v�f�A
			//leaf��1�Ԗڈȍ~�͑���
			//leaf�̗v�f��0�Ȃ�Avalue��0
			struct Element{
				typedef std::unique_ptr<Element> UPElement;

				std::string value;
				std::vector<UPElement> leafs;
			};


			xmlReader();
		public:
			xmlReader(const std::string filename);
			virtual ~xmlReader();

			bool update(void);

			std::string get(const std::string key);
		};
	}
}

#endif