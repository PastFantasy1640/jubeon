/*
 *	Sceneクラスについて			-作成者:white-
 *		【クラス概要】
 *		Sceneクラスは場面を管理します。ある任意の時間tにおいて、存在するインスタンスは必ず1つだけです。
 *		新しく場面を作成する場合は、このSceneクラスを継承したクラスに実装します。命名規則はxxxSceneクラスにしてください。
 *		それぞれのサブクラスのprocess関数が処理ループを実装する関数です。一度関数を抜けたらそのSceneインスタンスは消滅するので、処理ループは自前で実装してください。
 *		process関数の戻り値は終了ステータスです。0以外、もしくは次に実行するSceneがnullptrの場合システムを終了します。
 *
 *		【マルチスレッド対策】
 *		Sceneの基底クラスのstaticメソッドは、スレッドアンセーフです。よって、全メソッドはメインスレッド以外から呼ばないでください。
 *		それぞれのサブクラスに関しては、描写スレッドやIOスレッドからのアクセスがあるかと思いますので、スレッドセーフ対策をしてください。
 *
 *		【シーン管理メソッド】		
 *		staticなprocess関数は決してメインスレッド以外で呼ばないでください。また、出来る限りmain関数の中でコールしてください。
 *
 *		【process関数内での動作のルール】
 *		メインウィンドウ（LayerManager）のインスタンスへのポインタがgetMainWindow()で取得できます。
 *		イベントの管理はgetMainWindow()->getWindowEvent(e)で取得し各自で行ってください。
 *		詳しくはLayerManagerを参照してください。
 *		メインウィンドウを生成（サブウィンドウは生成されていない場合もある）した後にstaticなprocess関数はコールされます。
 *		そのため、メインウィンドウのインスタンスは、process関数実行中では確保してあることを前提とした動作を定義して良いです。
 *		新しいレイヤーを生成する場合は、レイヤーのインスタンス管理に注意してください。
 *		詳しくはLayerManagerを参照してください。新しく生成されたインスタンスはshared_ptrで共有されるため、シーンを移っただけでは削除されません。
 *		addLayerする場合は、Init関数に注意してください。ロードに時間がかかる場合、処理スレッドをブロッキングします。
 *		ブロッキングしたくない時は、スレッドを新しく立てて、addLayerを別スレッドで実行してください。
 *
 *		【次のシーンへのインスタンスの受け渡し】
 *		次のシーンへのインスタンスの受け渡しが必要な場合は、新しく作るシーンのコンストラクタで渡すか、メソッドを実装して渡してください。
 *		process関数には引数が無いため、そこでの受け渡しは不可能です。
 **/


#pragma once

#ifndef JUBEON_SYSTEMS_SCENE_HPP
#define JUBEON_SYSTEMS_SCENE_HPP

#include <memory>

#include <thread>

#include "Graphics/Layer/LayerManager.hpp"

#include <atomic>

namespace jubeon {

	namespace systems {

		//Sceneクラス
		//staticメソッドはオーバーライドできないし、Sceneクラスのstaticメソッドはオーバーライドしてはならないものである。
		//Sceneクラスを継承したクラスを作成し、それぞれのシーンとする。
		class Scene {
		private:
			//次のシーン
			static std::shared_ptr<Scene> next_scene;

			//現在のシーン
			static std::shared_ptr<Scene> current_scene;

			//すでにstatic processメソッドは動いて居るか
			//スレッドアンセーフ
			static std::atomic<bool> is_running;

			static std::atomic<bool> is_loop;

			static bool is_scene_change;

            static jubeon::graphics::LayerManager * main_window;
            
			static void process2(const std::shared_ptr<Scene> & first_scene);
            
		protected:
			//次のシーンを設定する
			static void setNextScene(const std::shared_ptr<Scene> & next_scene);
			
            
		public:
			//コンストラクタ
			Scene();

			//デストラクタ
			virtual ~Scene() {};

			//process仮想関数。それぞれのシーンで処理を記述する
			//プロセスから抜けるとすぐにNextSceneへ行くので、ループは自前で整備する。
			//戻り値が0以外だとプログラムを終了する。
			virtual int process(void) = 0;

			virtual void init(void) = 0;

			//メインスレッドで実行されるprocess関数。
			//再帰してはならないし、できない設計にしてある
			//メインスレッドで実行する。戻り値は終了ステータス
			template<class T,class... Args>
			static int process(jubeon::graphics::LayerManager * main_window, Args... args){
		        Scene::main_window = main_window;
			    std::shared_ptr<T> first_scene(new T(args...));
			    std::thread th(&Scene::process2,first_scene);
			    th.detach();
			    return 0;//process2(first_scene);
			}

			static void ExitGame() {
				is_loop.store(false);

				while (is_running.load()) std::this_thread::sleep_for(std::chrono::microseconds(1));	//  1マイクロ秒
			}

		};	
	};
};

#endif

