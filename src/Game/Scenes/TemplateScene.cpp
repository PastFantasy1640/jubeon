#include "TemplateScene.hpp"

jubeon::game::scenes::TemplateScene::TemplateScene()
{
}

jubeon::game::scenes::TemplateScene::~TemplateScene()
{
}

int jubeon::game::scenes::TemplateScene::process(void)
{
	//実行関数は一度のみ呼ばれます。
	//LayerBaseはレイヤーを終了するまで呼ばれ続けますが、これは一回のみで、関数が終了するとシーンの終了となります。
	//戻り値が1以外であれば、次のシーンが設定されていても終了します。
	//また、NextSceneを設定していなかった場合も終了します。
	
	//つまり、自前でループを実装する必要があります。
	while (this->getMainWindow()->isWindowOpening()) {
		sf::Event e;
		while (this->getMainWindow()->getWindowEvent(e)) {
			if (e.type == sf::Event::Closed) this->getMainWindow()->closeWindow();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) this->getMainWindow()->closeWindow();
			//ここにウィンドウイベントの追加
		}

		//ここに処理の追加


		//移動処理はこんな感じで
		//if(...){
		//	this->setNextScene(std::move(std::unique_ptr<HogehogeScene>(Layerとかを引き継ぎたいならここで設定)));
		//	return 0;
		//}

		//1micro second待つ。0.001msecである。ほんのちょっと。
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	return 0;
}
