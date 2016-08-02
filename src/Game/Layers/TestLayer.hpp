#pragma once

#include "../../Graphics/Layer/LayerBase.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class TestLayer : public jubeon::graphics::LayerBase{
			public:
				void			Init();						//‰Šú‰»ŠÖ”
				void			Update();					//ˆ—ŠÖ”
				void			Draw();						//•`ÊŠÖ”
				void			Exit();						//I—¹ŠÖ”
			};
		}
	}

}