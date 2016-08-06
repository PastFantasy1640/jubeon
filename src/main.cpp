
//shared_ptr, unique_ptr
#include <memory>

//LayerManager
#include "Graphics/Layer/LayerManager.hpp"

//Scene
#include "Systems/Scene.hpp"

//Starting Scene
#include "Game/Scenes/GameScene.hpp"

#include "Storages/JsonFileStorage.hpp"
#include "Models/WindowConfig.hpp"


//Logger
#include "Systems/Logger.hpp"


#ifdef _DEBUG
#include <crtdbg.h>	//���������[�N���O�p
#endif

using namespace jubeon::game;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;

int main(int argc, char * argv[]) {

#ifdef _DEBUG
	//���������[�N�̃��O���o�͂��Ă����炵��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//�N�����̃��O
	Logger::information("jubeon���N�����܂���");
	
	//���C���E�B���h�E�̃C���X�^���X�𐶐�
	//TO DO : �ݒ�t�@�C������̓ǂݏo��
	LayerManager mainwindow("jubeon v0.1", sf::VideoMode(1080, 1920), false, 0, sf::Vector2i(1920, -840), sf::Style::None);

	//���C���E�B���h�E�̐���
	mainwindow.createWindow();

	//�ŏ��Ɏg�p����V�[���𐶐�
	unique_ptr<scenes::GameScene> upGameSceneInstance(new scenes::GameScene());

	int ret = Scene::process(&mainwindow, std::move(upGameSceneInstance));

	//���݋N�����̃E�B���h�E���I�����A���C���[��S�����
	mainwindow.closeWindow();

	//�V�X�e���I��
	return ret;

}
