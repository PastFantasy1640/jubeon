#include "Scene.hpp"

bool jubeon::systems::Scene::is_running = false;
std::unique_ptr<jubeon::systems::Scene> jubeon::systems::Scene::next_scene;

//所有権の移動
void jubeon::systems::Scene::setNextScene(std::unique_ptr<Scene> next_scene)
{
	Scene::next_scene = std::move(next_scene);
}

int jubeon::systems::Scene::process(std::unique_ptr<Scene> first_scene)
{
	//初回のシーン代入
	Scene::setNextScene(std::move(first_scene));

	int ret = 0;
	while (ret == 0 && Scene::next_scene) {
		std::unique_ptr<Scene> current;			//現在のシーン
		current = std::move(Scene::next_scene);	//所有権の移動

		//実行
		ret = current->process();

		//ここでcurrentはデストラクト
	}

	//返す
	return ret;
}
