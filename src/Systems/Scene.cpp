#include "Scene.hpp"

bool jubeon::systems::Scene::is_running = false;
std::unique_ptr<jubeon::systems::Scene> jubeon::systems::Scene::next_scene;
jubeon::graphics::LayerManager * jubeon::systems::Scene::main_window;

//���L���̈ړ�
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
		Scene::is_running = true;	//�C���N���[�h�K�[�h�I��

									//����̃V�[�����
		Scene::setNextScene(std::move(first_scene));

		//�E�B���h�E�̃C���X�^���X�ݒ�
		Scene::main_window = main_window;

		int ret = 0;

		ret = main_window->run(std::move(first_scene));
		
		//�Ԃ�
		Scene::is_running = false;
		return ret;
	}

	//�ċA�I���s
	return -1;
}
