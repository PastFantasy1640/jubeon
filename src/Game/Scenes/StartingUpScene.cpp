#include "StartingUpScene.hpp"

//レイヤー群
#include "../Layers/StartingUpLogoLayer.hpp"
#include "Game/Layers/FrameLayer.hpp"

//次のシーン
#include "GameScene.hpp"

using namespace jubeon::game;
using namespace jubeon::graphics;
using namespace jubeon::systems;
using namespace std;

int jubeon::game::scenes::StartingUpScene::process(void)
{
	//タイマをリセット
	this->ck.restart();

	//レイヤーを起動
	shared_ptr<LayerBase> sull(new layers::StartingUpLogoLayer(this));
	this->getMainWindow()->addLayer(shared_ptr<LayerBase>(new layers::FrameLayer), LayerManager::FOREGROUND, 0);	//これは一度起動したら、終了するまでずっと
	this->getMainWindow()->addLayer(sull, LayerManager::MAIN,0);

	//処理のループ
	while (this->getMainWindow()->isWindowOpening()) {
		sf::Event e;

		//イベントプロシージャ
		while (this->getMainWindow()->getWindowEvent(e)) {
			if (e.type == sf::Event::Closed) this->getMainWindow()->closeWindow();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) this->getMainWindow()->closeWindow();
			else if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Return) {
				//ロゴをすっ飛ばす
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
