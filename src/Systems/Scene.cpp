#include "Scene.hpp"

bool jubeon::systems::Scene::is_running = false;
bool jubeon::systems::Scene::is_scene_change = false;
std::shared_ptr<jubeon::systems::Scene> jubeon::systems::Scene::next_scene;
std::shared_ptr<jubeon::systems::Scene> jubeon::systems::Scene::current_scene;
jubeon::graphics::LayerManager * jubeon::systems::Scene::main_window;

//���L���̈ړ�
void jubeon::systems::Scene::setNextScene(const std::shared_ptr<Scene> & next_scene)
{
	Scene::next_scene = next_scene;
	Scene::is_scene_change = true;
}

jubeon::graphics::LayerManager * jubeon::systems::Scene::getMainWindow()
{
	return Scene::main_window;
}

int jubeon::systems::Scene::process(jubeon::graphics::LayerManager * main_window, const std::shared_ptr<Scene> & first_scene)
{
	if (!Scene::is_running) {
		Scene::is_running = true;	//�C���N���[�h�K�[�h�I��

									//����̃V�[�����
		Scene::current_scene = first_scene;

		//�E�B���h�E�̃C���X�^���X�ݒ�
		Scene::main_window = main_window;


		int ret = 0;

		while (ret == 0 && Scene::current_scene) {

			ret = Scene::current_scene->process();

			if (Scene::is_scene_change) {
				Scene::current_scene = Scene::next_scene;	//�V�[�����ڂ�
				Scene::is_scene_change = false;
			}

			Scene::getMainWindow()->process();

		}

		//�Ԃ�
		Scene::is_running = false;
		return ret;
	}

	//�ċA�I���s
	return -1;
}
