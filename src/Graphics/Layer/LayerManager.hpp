#pragma once

#ifndef JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP
#define JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP

#include <string>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>


namespace jubeat_online {
	namespace graphics {
		namespace layer {

			class LayerBase;

			/** レイヤーの管理クラス。ひとつのウィンドウにつきひとつのインスタンスが生成される。
			 */
			class LayerManager {
			public:


				/** 引数付きコンストラクタ。
				 * @param window_title ウィンドウのタイトル
				 * @param width ウィンドウの幅(px)
				 * @param height ウィンドウの高さ(px)
				 */
				LayerManager(
					const std::string & window_title,
					const sf::VideoMode & vmode,
					const bool isVSync,
					const unsigned int fpsLimit = 0,
					const sf::Vector2i startWindowPosition = sf::Vector2i(0,0),
					const sf::Uint32 style = sf::Style::Default
					);

				/** デクスストラクタ
				 */
				virtual ~LayerManager();

				/** ウィンドウを生成します。
				 */
				void createWindow(void);

				typedef enum : unsigned char{
					FOREGROUND = 0,
					MAIN = 1,
					BACKGROUND = 2
				}LayerType;

				void addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber);

				void run(void);

				bool isThreadRunning(void) const;

			private:
				void process(void);
				typedef struct {
					std::shared_ptr<LayerBase> lb;
					LayerType lt;
				} LayerDetail;

				LayerManager(const LayerManager & cp);		//コピーコンストラクタの禁止
				LayerManager();								//デフォルトコンストラクタも禁止
				
				std::shared_ptr< std::list<LayerDetail>>	layer_list;		//レイヤーのリスト

				sf::VideoMode				vmode;			//生成するウィンドウのサイズなど
				std::string					window_title;	//生成するウィンドウのタイトル
				sf::Uint32					window_style;	//生成するウィンドウのスタイル
				bool						isVSync;		//垂直同期をとるか
				unsigned int				fpsLimit;		//0で制限なし
				sf::Vector2i				window_position;//ウィンドウを生成するポジション


				sf::RenderWindow			window;			//生成するウィンドウの実体（継承はしない。外部から触ってほしくないpublicがある）
				sf::RenderTexture			window_buffer;	//画面調整のためのラストバッファ

				std::shared_ptr<bool>		is_thread_running;

				const static sf::Vector2u RENDER_TEXTURE_SIZE;

			};
		};
	};
};

#endif /* --- end of LayerManager --- */