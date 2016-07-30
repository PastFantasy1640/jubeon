#pragma once

#ifndef JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP
#define JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP

#include <string>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>


#define LAYERMANAGER_DEFAULT_WINDOW_WIDTH 960
#define LAYERMANAGER_DEFAULT_WINDOW_HEIGHT 540


namespace jubeat_online {
	namespace graphics {
		namespace layer {

			class LayerBase;

			/** レイヤーの管理クラス。ひとつのウィンドウにつきひとつのインスタンスが生成される。
			 */
			class LayerManager {
			public:
				/** デフォルトコンストラクタ。
				 */
				LayerManager();


				/** 引数付きコンストラクタ。
				 * @param window_title ウィンドウのタイトル
				 * @param width ウィンドウの幅(px)
				 * @param height ウィンドウの高さ(px)
				 */
				LayerManager(
					const std::string & window_title,
					const sf::VideoMode & vmode,
					const sf::Uint32 style = sf::Style::Default
					);

				/** デクスストラクタ
				 */
				virtual ~LayerManager();

				void createWindow(void);
				void setScale(const double rate);

				typedef enum : unsigned char{
					FOREGROUND = 0,
					MAIN = 1,
					BACKGROUND = 2
				}LayerType;

				void addLayer(LayerBase * layer, const LayerType type, const unsigned char layernumber);

				void process(void);

			private:
				typedef struct {
					LayerBase * lb;
					LayerType lt;
				} LayerDetail;

				LayerManager(const LayerManager & cp);		//コピーコンストラクタの禁止
				
				std::unique_ptr< std::list<LayerDetail>>	layer_list;		//レイヤーのリスト

				sf::VideoMode				vmode;			//生成するウィンドウのサイズなど
				std::string					window_title;	//生成するウィンドウのタイトル
				sf::Uint32					window_style;	//生成するウィンドウのスタイル
				
				sf::RenderWindow			window;			//生成するウィンドウの実体（継承はしない。外部から触ってほしくないpublicがある）

				double scale;


			};
		};
	};
};

#endif /* --- end of LayerManager --- */