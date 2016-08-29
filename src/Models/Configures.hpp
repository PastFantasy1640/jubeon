/////////////////////////////////////////////////////////////
// (c)  2016   white  Configures.hpp
/////////////////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_MODEL_CONFIGURES_HPP
#define JUBEON_MODEL_CONFIGURES_HPP

#include "WindowConfig.hpp"

#include <memory>

namespace jubeon {
	namespace models {
		class Configures {
		public:

			///////////////////////////////////////////////
			// Configures
			///////////////////////////////////////////////
			std::shared_ptr<WindowConfig> window_config;




			~Configures() {}	//Do not override huh

			Configures * getInstance(void);

		private:
			Configures();

			static std::unique_ptr<Configures> conf;
			
		};
	};
};

#endif
