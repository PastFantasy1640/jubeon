#pragma once

//auther white
//動作確認済み2016/08/04

//!!!!注意!!!!!
//ファイルを複製しましたか？まずはcpp、hpp共に複製して、名前を変えてから変更してください。

//1.まず最初に、cppファイルとhppファイルを複製して名前を変えましょう。
//命名規則はHogehogeLayer.[c/h]ppです

//インクルードガードを設定してください
#ifndef JUBEON_GAME_LAYERS_TEMPLATELAYER_HPP
#define JUBEON_GAME_LAYERS_TEMPLATELAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			//クラス名を変更してください。
			class TemplateLayer : public jubeon::graphics::LayerBase{
			public:
				//コンストラクタです。必要に応じて引数付きコンストラクタも定義してください。
				TemplateLayer();
				virtual ~TemplateLayer();

				virtual void Init() override;						//初期化関数
				virtual void Draw() override;						//描写関数
				virtual void Exit() override;						//終了関数
			};


		};	//end of layers
	};	//end of game

};	//end of jubeon

#endif	//end of include gurd