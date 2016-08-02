#pragma once

#ifndef JUBEON_GRAPHICS_LAYERBASE_HPP
#define JUBEON_GRAPHICS_LAYERBASE_HPP

#include <SFML/Graphics.hpp>

namespace jubeon {
	namespace graphics {

		class LayerBase : public sf::RenderTexture {
		private:

			//コピーコンストラクタは禁止
			LayerBase(const LayerBase & copy);

			//終了コード
			int						exit_code;


		protected:
			//コンストラクタ、デストラクタ
			LayerBase();

			//透過情報を持たせてバッファをクリア
			inline void clearBuffer(void) {
				this->clear(sf::Color(0, 0, 0, 0));
			}


			/** レイヤーを終了します。0以外のコードを設定することでレイヤーの終了判定を有効にします。
			* @param code 終了コード
			*/
			void setExitCode(const int code);

		public:

			virtual void			Init() = 0;						//初期化関数
			virtual void			Draw() = 0;						//描写関数
			virtual void			Exit() = 0;						//終了関数

			virtual ~LayerBase();


			/** 終了コードを取得します。ただし取得できるのはインスタンスが存在する間のみです。
			 * @returns 終了コード
			 */
			unsigned int getExitCode(void) const;


		};	//end of LayerBase

	};//end of graphics
};//end of jubeon


#endif	// end of 