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
//				LayerBase(const LayerBase & copy);

				int						exit_code;
				//unsigned int			layer_no;						//0が一番手前

			protected:
				//コンストラクタ、デストラクタ
				LayerBase();
				//sf::RenderTexture *		screen_buffer;

			public:

				/** LayerManagerがInit関数よりも先に呼び出します。screen_bufferの初期化を一度だけ行います。二度目以降呼び出しても何も動作をしません。
				 * @param width スクリーンの幅(px)
				 * @param height スクリーンの縦(px)
				 */
				//virtual void			createScreenBuffer(const unsigned int width, const unsigned int height) final;
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

				/** RenderTextureのスプライトを取得します。LayerManagerによって実行されます。
				 * @returns スクリーンバッファのSprite
				 */
				//const sf::Texture * getScreenBufferTexture(void) const;


//				void _setScreenBuffer(sf::RenderTexture * rt);
//				void _setWindowTarget(sf::RenderWindow * wd);

//				unsigned int getLayerNumber(void) const;
//				void setLayerNumber(const unsigned int layer_no);
			};
		}
	}
}


#endif