
//shared_ptr, unique_ptr
#include <memory>

//LayerManager
#include "Graphics/Layer/LayerManager.hpp"

//Scene
#include "Systems/Scene.hpp"

//Starting Scene
#include "Game/Scenes/DemoLoadingScene.hpp"

#include "Storages/JsonFileStorage.hpp"
#include "Models/WindowConfig.hpp"


//Logger
#include "Systems/Logger.hpp"

//for config loading
#include "Storages/JsonFileStorage.hpp"
#include "Models/PanelConfig.hpp"

//for panel input
#include "Input/ListenPanel.hpp"


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
	LayerManager mainwindow("jubeon v0.1", sf::VideoMode(1080,1920,64), true, 80, sf::Vector2i(1920, -840), sf::Style::None);
	//LayerManager mainwindow("jubeon v0.1", sf::VideoMode(800, 1080), true, 80, sf::Vector2i(0,0), sf::Style::None);

	//���C���E�B���h�E�̐���
	mainwindow.createWindow();


	//�p�l���R���t�B�O
	jubeon::storages::JsonFileStorage keyconfig_storage("media/config/keyconfig.json");
	shared_ptr<jubeon::models::PanelConfig> pconfig = keyconfig_storage.getModel<jubeon::models::PanelConfig>();

	pconfig->setInstance(pconfig);	//�V���O���g���H

	//�p�l���N��
	jubeon::input::ListenPanel::Listen();

	//�ŏ��Ɏg�p����V�[���𐶐�
	shared_ptr<scenes::DemoLoadingScene> upSceneInstance(new scenes::DemoLoadingScene());
	
	int ret = Scene::process(&mainwindow, upSceneInstance);

	//�p�l���̏I��
	jubeon::input::ListenPanel::Close();

	//���݋N�����̃E�B���h�E���I�����A���C���[��S�����
	mainwindow.closeWindow();

	//�V�X�e���I��
	return ret;

}
