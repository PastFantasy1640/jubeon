#pragma once

#include "../../Graphics/Layer/LayerBase.hpp"

namespace jubeat_online {
	namespace game {
		namespace layers {
			class TestLayer : public jubeat_online::graphics::layer::LayerBase{
			public:
				void			Init();						//�������֐�
				void			Update();					//�����֐�
				void			Draw();						//�`�ʊ֐�
				void			Exit();						//�I���֐�
			};
		}
	}

}