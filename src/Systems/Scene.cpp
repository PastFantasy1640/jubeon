#include "Scene.hpp"

bool jubeon::systems::Scene::is_running = false;
std::unique_ptr<jubeon::systems::Scene> jubeon::systems::Scene::next_scene;
std::unique_ptr<jubeon::systems::Scene> jubeon::systems::Scene::current_scene;
jubeon::graphics::LayerManager * jubeon::systems::Scene::main_window;

//所有権の移動
void jubeon::systems::Scene::setNextScene(std::unique_ptr<Scene> next_scene)
{
	Scene::next_scene = std::move(next_scene);
}

jubeon::graphics::LayerManager * jubeon::systems::Scene::getMainWindow()
{
	return Scene::main_window;
}

int jubeon::systems::Scene::process(jubeon::graphics::LayerManager * main_window, std::unique_ptr<Scene> first_scene)
{
	if (!Scene::is_running) {
		Scene::is_running = true;	//インクルードガード的な

									//ウィンドウのインスタンス設定
		Scene::main_window = main_window;

									//初回のシーン代入
		Scene::current_scene = std::move(first_scene);
		Scene::current_scene->init();



		int ret = 0;

		while (ret == 0 && Scene::current_scene) {
			if (Scene::next_scene) {
				Scene::current_scene = std::move(Scene::next_scene);	//シーンを移す
				Scene::current_scene->init();
			}

			ret = Scene::current_scene->process();

			Scene::getMainWindow()->process();

		}

		//返す
		Scene::is_running = false;
		return ret;
	}

	//再帰的実行
	return -1;
}
