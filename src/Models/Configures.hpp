/////////////////////////////////////////////////////////////
// (c)  2016   white  Configures.hpp
/////////////////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_MODEL_CONFIGURES_HPP
#define JUBEON_MODEL_CONFIGURES_HPP

#include "WindowConfig.hpp"
#include "PanelConfig.hpp"

#include <memory>

namespace jubeon {
	namespace models {
		class Configures {
		public:

			///////////////////////////////////////////////
			// Configures
			///////////////////////////////////////////////
			std::shared_ptr<WindowConfig> window_config;
			std::shared_ptr<PanelConfig> panel_config;



			~Configures() {}	//Do not override huh

			static Configures * getInstance(void);

		private:
			Configures() {}

			static std::unique_ptr<Configures> conf;
			
		};
	};
};

#endif
