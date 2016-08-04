#pragma once

//インクルードガードをつけましょう
#ifndef JUBEON_GAME_SCENES_TEMPLATESCENE_HPP
#define JUBEON_GAME_SCENES_TEMPLATESCENE_HPP

#include "../../Systems/Scene.hpp"

namespace jubeon {
	namespace game {
		namespace scenes {
			class TemplateScene : public jubeon::systems::Scene {
			public:
				//コンストラクタ
				//適宜引数付きも定義すること
				TemplateScene();

				//デストラクタ
				virtual ~TemplateScene();

				//プロセス関数
				virtual int process(void) override;
			};
		};
	};
}; //end of jubeon

#endif //end of include guard