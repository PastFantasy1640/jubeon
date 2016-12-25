#include "Scene.hpp"

//for Logger
#include "Logger.hpp"

bool jubeon::systems::Scene::is_running = false;
bool jubeon::systems::Scene::is_scene_change = false;
std::shared_ptr<jubeon::systems::Scene> jubeon::systems::Scene::next_scene;
std::shared_ptr<jubeon::systems::Scene> jubeon::systems::Scene::current_scene;
jubeon::graphics::LayerManager * jubeon::systems::Scene::main_window;

//Constructor
jubeon::systems::Scene::Scene()
{
}

//���L���̈ړ�
void jubeon::systems::Scene::setNextScene(const std::shared_ptr<Scene> & next_scene)
{
	Scene::next_scene = next_scene;
	Scene::is_scene_change = true;
}

void jubeon::systems::Scene::process2(const std::shared_ptr<Scene> & first_scene)
{
	if (!Scene::is_running) {
		Scene::is_running = true;	//�C���N���[�h�K�[�h�I��

        Logger::information("Start to scene process.");

		//����̃V�[�����
		Scene::current_scene = first_scene;
		

        Logger::information("Initializing the first scene.");
		Scene::current_scene->init();
        Logger::information("Finished initializing the first scene.");

		int ret = 0;

		while (ret == 0 && Scene::current_scene) {

			ret = Scene::current_scene->process();

			if (Scene::is_scene_change) {
				Scene::current_scene = Scene::next_scene;	//�V�[�����ڂ�
                Logger::information("Initializing the next scene.");
				Scene::current_scene->init();
				Scene::is_scene_change = false;
			}

            jubeon::graphics::LayerManager::processAll();

		}

        Logger::information("Closing the scene process.");
        
		//�Ԃ�
		Scene::is_running = false;
		//return ret;
	}

	//�ċA�I���s
	//return -1;
}
