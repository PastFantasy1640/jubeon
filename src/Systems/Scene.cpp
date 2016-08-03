#include "Scene.hpp"

bool jubeon::systems::Scene::is_running = false;
std::unique_ptr<jubeon::systems::Scene> jubeon::systems::Scene::next_scene;

//���L���̈ړ�
void jubeon::systems::Scene::setNextScene(std::unique_ptr<Scene> next_scene)
{
	Scene::next_scene = std::move(next_scene);
}

int jubeon::systems::Scene::process(std::unique_ptr<Scene> first_scene)
{
	//����̃V�[�����
	Scene::setNextScene(std::move(first_scene));

	int ret = 0;
	while (ret == 0 && Scene::next_scene) {
		std::unique_ptr<Scene> current;			//���݂̃V�[��
		current = std::move(Scene::next_scene);	//���L���̈ړ�

		//���s
		ret = current->process();

		//������current�̓f�X�g���N�g
	}

	//�Ԃ�
	return ret;
}
