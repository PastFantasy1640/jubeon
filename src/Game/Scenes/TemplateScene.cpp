#include "TemplateScene.hpp"

jubeon::game::scenes::TemplateScene::TemplateScene()
{
}

jubeon::game::scenes::TemplateScene::~TemplateScene()
{
}

int jubeon::game::scenes::TemplateScene::process(void)
{
	//���s�֐��͈�x�̂݌Ă΂�܂��B
	//LayerBase�̓��C���[���I������܂ŌĂ΂ꑱ���܂����A����͈��݂̂ŁA�֐����I������ƃV�[���̏I���ƂȂ�܂��B
	//�߂�l��1�ȊO�ł���΁A���̃V�[�����ݒ肳��Ă��Ă��I�����܂��B
	//�܂��ANextScene��ݒ肵�Ă��Ȃ������ꍇ���I�����܂��B
	
	//�܂�A���O�Ń��[�v����������K�v������܂��B
	while (this->getMainWindow()->isWindowOpening()) {
		sf::Event e;
		while (this->getMainWindow()->getWindowEvent(e)) {
			if (e.type == sf::Event::Closed) this->getMainWindow()->closeWindow();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) this->getMainWindow()->closeWindow();
			//�����ɃE�B���h�E�C�x���g�̒ǉ�
		}

		//�����ɏ����̒ǉ�


		//�ړ������͂���Ȋ�����
		//if(...){
		//	this->setNextScene(std::move(std::unique_ptr<HogehogeScene>(Layer�Ƃ��������p�������Ȃ炱���Őݒ�)));
		//	return 0;
		//}

		//1micro second�҂B0.001msec�ł���B�ق�̂�����ƁB
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	return 0;
}
