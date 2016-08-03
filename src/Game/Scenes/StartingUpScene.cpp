#include "StartingUpScene.hpp"

//���C���[�Q
#include "../Layers/StartingUpLogoLayer.hpp"
#include "Game/Layers/FrameLayer.hpp"

//���̃V�[��
#include "GameScene.hpp"

using namespace jubeon::game;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;

int jubeon::game::scenes::StartingUpScene::process(void)
{
	//�^�C�}�����Z�b�g
	this->ck.restart();

	//���C���[���N��
	shared_ptr<LayerBase> sull(new layers::StartingUpLogoLayer(this));
	this->getMainWindow()->addLayer(shared_ptr<LayerBase>(new layers::FrameLayer), LayerManager::FOREGROUND, 0);	//����͈�x�N��������A�I������܂ł�����
	this->getMainWindow()->addLayer(sull, LayerManager::MAIN,0);

	//�����̃��[�v
	while (this->getMainWindow()->isWindowOpening()) {
		sf::Event e;

		//�C�x���g�v���V�[�W��
		while (this->getMainWindow()->getWindowEvent(e)) {
			if (e.type == sf::Event::Closed) this->getMainWindow()->closeWindow();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) this->getMainWindow()->closeWindow();
			else if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Return) {
				//���S��������΂�
				this->setNextScene(std::move(std::unique_ptr<scenes::GameScene>(new scenes::GameScene())));
				sull->setExitCode(1);
				return 0;
			}
		}


		if (ck.getElapsedTime().asMilliseconds() > 5000) {
			this->setNextScene(std::move(std::unique_ptr<scenes::GameScene>(new scenes::GameScene())));
			sull->setExitCode(1);
			return 0;
		}


		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	return 1;
}
