//レイヤーのヘッダを読み込み
#include "TemplateLayer.hpp"

//名前空間を設定しても良い
//using namespace std;
//using namespace jubeon::game;
//using namespace jubeon::systems;

//コンストラクタ領域です。
//適宜引数付きも定義してください。
jubeon::game::layers::TemplateLayer::TemplateLayer()
{
}

//デストラクタです
jubeon::game::layers::TemplateLayer::~TemplateLayer()
{
}

//初期化
void jubeon::game::layers::TemplateLayer::Init()
{
	//リソースの読み込みなどを行ってください。
	//this->hogehoge.loadFromFile("foobar.png");
}

//描画
void jubeon::game::layers::TemplateLayer::Draw()
{
	//まずフレームをクリアします
	this->clearBuffer();	//透明にクリアするときはclearBuffer、もしくはclear(sf::Color(0,0,0,0))
	//this->clear();		//黒背景にクリアするときはこちら。この下にあるレイヤーは見えなくなります。

	//描写してください。
	//this->draw(sf::Sprite(this->hogehoge));
	//...

	//レイヤーを終了させたい場合はsetExitCodeを呼んでください
	if (false) {
		//この分岐に入るはずがない
		this->setExitCode(-1);	//0以外で終了です。1がSUCCESSを意味します。エラーの場合は負の値を渡すことを推奨します。
	}

	//描写が終了してもdisplayは呼ぶ必要はありません。
}

//終了処理を行います。
void jubeon::game::layers::TemplateLayer::Exit()
{
	//終了処理を行います。
	//描画スレッドで実行されるため時間には注意してください（改善の余地あり？）
}
