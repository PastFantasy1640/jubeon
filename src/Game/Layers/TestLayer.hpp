#pragma once

#include "../../Graphics/Layer/LayerBase.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			class TestLayer : public jubeon::graphics::LayerBase{
			public:
				void			Init();						//初期化関数
				void			Update();					//処理関数
				void			Draw();						//描写関数
				void			Exit();						//終了関数
			};
		}
	}

}