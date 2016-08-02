#pragma once

#ifndef JUBEON_GRAPHICS_LAYERMANAGER_HPP
#define JUBEON_GRAPHICS_LAYERMANAGER_HPP

#include <string>
#include <list>
#include <memory>
#include <map>
#include <mutex>
#include <SFML/Graphics.hpp>

#include "LayerBase.hpp"

//windowを生成するのは絶対にメインスレッド
//eventループは持たない
//eventループはメインスレッド

namespace jubeon{
	namespace graphics {

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
				const sf::Vector2i startWindowPosition = sf::Vector2i(0, 0),
				const sf::Uint32 style = sf::Style::Default
				);

			/** デストラクタ
			 */
			virtual ~LayerManager();

			typedef enum : unsigned char {
				SYSTEM = 0,
				FOREGROUND = 1,
				MAIN = 2,
				BACKGROUND = 3
			}LayerType;

			void addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber);

			//スレッドを立てて起動
			//必ずメインスレッドで呼ぶこと。
			void run(void);

			//ウィンドウが開いているか
			bool isWindowOpening(void) const;

			//ウィンドウを終了させる
			void closeWindow(void);


		private:

			void process(void);


			std::mutex layer_list_mtx;							//layer_listに対するロック
			std::map<std::shared_ptr<LayerBase>, LayerType> layer_map;	//レイヤーマップ
			std::vector<std::shared_ptr<LayerBase>> layer_list;	//レイヤーリスト

			LayerManager(const LayerManager & cp);				//コピーコンストラクタの禁止
			LayerManager();										//デフォルトコンストラクタも禁止

			const sf::VideoMode					vmode;			//生成するウィンドウのサイズなど
			const std::string					window_title;	//生成するウィンドウのタイトル
			const sf::Uint32					window_style;	//生成するウィンドウのスタイル
			const bool							isVSync;		//垂直同期をとるか
			const unsigned int					fpsLimit;		//0で制限なし
			const sf::Vector2i					window_position;//ウィンドウを生成するポジション


			std::shared_ptr<sf::RenderWindow>	window;			//生成するウィンドウの実体（継承はしない。外部から触ってほしくないpublicがある）
			std::unique_ptr<sf::RenderTexture>	window_buffer;	//画面調整のためのラストバッファ

			std::shared_ptr<bool>				is_thread_running;
			std::shared_ptr<bool>				is_open_window;

			const static sf::Vector2u			RENDER_TEXTURE_SIZE;

		};	//end of LayerManager
	};//end of graphics
};//end of jubeon

#endif /* --- end of JUBEON_GRAPHICS_LAYERMANAGER_HPP --- */