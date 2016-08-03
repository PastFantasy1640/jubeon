#pragma once

#ifndef JUBEON_SYSTEMS_SCENE_HPP
#define JUBEON_SYSTEMS_SCENE_HPP

#include <memory>

namespace jubeon {
	namespace systems {

		//Sceneクラス
		class Scene {
		private:
			//次のシーン
			static std::unique_ptr<Scene> next_scene;

			//すでにstatic processメソッドは動いて居るか
			//スレッドアンセーフ
			static bool is_running;

		protected:
			//次のシーンを設定する
			//設定した後のnext_sceneには所有権が無いため注意
			static void setNextScene(std::unique_ptr<Scene> next_scene);

		public:
			//コンストラクタ
			Scene() {};

			//デストラクタ
			virtual ~Scene() {};

			//process仮想関数。それぞれのシーンで処理を記述する
			//プロセスから抜けるとすぐにNextSceneへ行くので、ループは自前で整備する。
			//戻り値が0以外だとプログラムを終了する。
			virtual int process(void) = 0;

			//メインスレッドで実行されるprocess関数。
			//再帰してはならないし、できない設計にしてある
			//メインスレッドで実行する。戻り値は終了ステータス
			static int process(std::unique_ptr<Scene> first_scene);

		};	
	};
};

#endif

