#pragma once

#ifndef WG_SYSTEMS_LayerBase_HPP_
#define WG_SYSTEMS_LayerBase_HPP_

#include <SFML/Graphics.hpp>

namespace jubeat_online {
	namespace graphics {
		namespace layer {

			class LayerBase : public sf::RenderTexture{
			private:

				//コピーコンストラクタは禁止
				LayerBase(const LayerBase & copy);

				//終了コード
				int						exit_code;


			protected:
				//コンストラクタ、デストラクタ
				LayerBase();
				inline void clearBuffer(void) {
					this->clear(sf::Color(0, 0, 0, 0));
				}

			public:

				virtual void			Init() = 0;						//初期化関数
				virtual void			Draw() = 0;						//描写関数
				virtual void			Exit() = 0;						//終了関数

				virtual ~LayerBase();

				/** レイヤーを終了します。0以外のコードを設定することでレイヤーの終了判定を有効にします。
				 * @param code 終了コード
				 */
				void setExitCode(const int code);

				/** 終了コードを取得します。ただし取得できるのはインスタンスが存在する間のみです。
				 * @returns 終了コード
				 */
				unsigned int getExitCode(void) const;

			};
		}
	}
}


#endif