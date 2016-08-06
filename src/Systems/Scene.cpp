#include "Scene.hpp"

bool jubeon::systems::Scene::is_running = false;
std::unique_ptr<jubeon::systems::Scene> jubeon::systems::Scene::next_scene;
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

									//初回のシーン代入
		Scene::setNextScene(std::move(first_scene));

		//ウィンドウのインスタンス設定
		Scene::main_window = main_window;

		int ret = 0;

		ret = main_window->run(std::move(first_scene));
		
		//返す
		Scene::is_running = false;
		return ret;
	}

	//再帰的実行
	return -1;
}
