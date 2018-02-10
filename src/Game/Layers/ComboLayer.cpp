#include "ComboLayer.hpp"


#include "Storages/Resource.hpp"

void jubeon::ComboLayer::Init()
{

	this->buffer_sprite.setPosition(this->panel_position->getBoundingBox().left,this->panel_position->getBoundingBox().top);
	this->createBuffer(sf::Vector2u(this->panel_position->getBoundingBox().width,this->panel_position->getBoundingBox().height));

	storages::Resource::setf("media/image/combo_0.png", storages::Resource::TEX).setKey("ComboLayer.combo0");
	storages::Resource::setf("media/image/combo_1.png", storages::Resource::TEX).setKey("ComboLayer.combo1");
	storages::Resource::setf("media/image/combo_2.png", storages::Resource::TEX).setKey("ComboLayer.combo2");
	storages::Resource::setf("media/image/combo_3.png", storages::Resource::TEX).setKey("ComboLayer.combo3");
	storages::Resource::setf("media/image/combo_4.png", storages::Resource::TEX).setKey("ComboLayer.combo4");
	storages::Resource::setf("media/image/combo_5.png", storages::Resource::TEX).setKey("ComboLayer.combo5");
	storages::Resource::setf("media/image/combo_6.png", storages::Resource::TEX).setKey("ComboLayer.combo6");
	storages::Resource::setf("media/image/combo_7.png", storages::Resource::TEX).setKey("ComboLayer.combo7");
	storages::Resource::setf("media/image/combo_8.png", storages::Resource::TEX).setKey("ComboLayer.combo8");
	storages::Resource::setf("media/image/combo_9.png", storages::Resource::TEX).setKey("ComboLayer.combo9");


	//コンボ画像のWeight取得

	//scaleの計算
	this->scale_ = this->w_ / this->combo_w_ / 4.0f;


	this->combo_sp[0].setTexture(*storages::Resource::setk("ComboLayer.combo0").gett());
	this->combo_sp[1].setTexture(*storages::Resource::setk("ComboLayer.combo1").gett());
	this->combo_sp[2].setTexture(*storages::Resource::setk("ComboLayer.combo2").gett());
	this->combo_sp[3].setTexture(*storages::Resource::setk("ComboLayer.combo3").gett());
	this->combo_sp[4].setTexture(*storages::Resource::setk("ComboLayer.combo4").gett());
	this->combo_sp[5].setTexture(*storages::Resource::setk("ComboLayer.combo5").gett());
	this->combo_sp[6].setTexture(*storages::Resource::setk("ComboLayer.combo6").gett());
	this->combo_sp[7].setTexture(*storages::Resource::setk("ComboLayer.combo7").gett());
	this->combo_sp[8].setTexture(*storages::Resource::setk("ComboLayer.combo8").gett());
	this->combo_sp[9].setTexture(*storages::Resource::setk("ComboLayer.combo9").gett());

	for (int i = 0; i <= 10; i++) {
		this->combo_sp[i].setScale(this->scale_, this->scale_);
	}

}

void jubeon::ComboLayer::Draw()
{


	sprintf(this->combo_buf_, "%d", combo->get());
	this->keta1_ = this->combo_buf_[0] - '0';
	this->keta2_ = this->combo_buf_[1] - '0';
	this->keta3_ = this->combo_buf_[2] - '0';
	this->keta4_ = this->combo_buf_[3] - '0';


	if (combo->get() <= 5){
	}
	else if (combo->get() <= 9) {
		this->combo_sp[keta1_].setPosition(this->w_ / 3.0f * 8.0f, get_Coordinates());
		this->draw(this->combo_sp[keta1_]);
	}
	else if (combo->get() <= 99) {
		this->combo_sp[keta1_].setPosition(this->w_ / 4.0f, get_Coordinates());
		this->combo_sp[keta2_].setPosition(this->w_ / 2.0f, get_Coordinates());
		this->draw(this->combo_sp[keta1_]);
		this->draw(this->combo_sp[keta2_]);
	}
	else if (combo->get() <= 999) {
		this->combo_sp[keta1_].setPosition(this->w_ / 8.0f, get_Coordinates());
		this->combo_sp[keta2_].setPosition(this->w_ / 8.0f * 3.0f, get_Coordinates());
		this->combo_sp[keta3_].setPosition(this->w_ / 8.0f * 5.0f, get_Coordinates());
		this->draw(this->combo_sp[keta1_]);
		this->draw(this->combo_sp[keta2_]);
		this->draw(this->combo_sp[keta3_]);
	}
	else if (combo->get() <= 9999) {
		this->combo_sp[keta1_].setPosition(0, get_Coordinates());
		this->combo_sp[keta2_].setPosition(this->w_ / 4, get_Coordinates());
		this->combo_sp[keta3_].setPosition(this->w_ / 2, get_Coordinates());
		this->combo_sp[keta4_].setPosition(this->w_ / 4 * 3, get_Coordinates());
		this->draw(this->combo_sp[keta1_]);
		this->draw(this->combo_sp[keta2_]);
		this->draw(this->combo_sp[keta3_]);
		this->draw(this->combo_sp[keta4_]);
	}
	
}

void jubeon::ComboLayer::Exit()
{
}

void jubeon::ComboLayer::restart()
{
	if (combo->isUpdate() == true) {
		
		//時間を0に
		clock.restart();
		n_ = 0;

		//y座標をデフォルトに戻す
		//this->y = this->y_def;

	}
}

float jubeon::ComboLayer::get_Coordinates()
{

	if (this->no_ == 0) { //記録が終わっていない

		this->t_ = this->clock.getElapsedTime().asMilliseconds();

		//上がりきるまでの座標を計算代入
		if (this->t_ <= 40) {
			this->y_[n_] = this->y_def_ + 1.0f / 8.0f * this->t_; //記録しておく
		}

		//下がりきるまでの座標を計算代入
		if (40 < this->t_ && this->t_ <= 160) {
			this->y_[n_] = this->y_def_ - 1.0f / 24.0f * this->t_;
		}

		//下がりきったあとの座標を計算代入 //記録終わったか？
		if (160 < this->t_) {
			this->y_[n_] = this->y_def_;
			this->no_ = 1; //記録が終わったフラグ立てる
		}
		return this->y_[n_];
	}
	else { //記録が終わっている
		return this->y_[this->n_]; //一回目でn回目に記録した座標
	}
	this->n_++;
	return 0;
}

jubeon::ComboLayer::ComboLayer(const Combo * combo, const PanelPosition * panel_position)
	: combo(combo), panel_position(panel_position)
{
	//初期のｙ座標を設定...受け取る？計算する？勝手に設定？
	//this->y_def = ;

	//描写範囲を受け取るようにしなきゃ? これでいいのかな↓
	this -> w_ = panel_position->getBoundingBox().width;

	//とりあえず設定、取得関数作成後削除
	this->combo_w_ = 160;
}

jubeon::ComboLayer::~ComboLayer()
{
}

