#include "ComboLayer.hpp"


#include "Storages/Resource.hpp"

void jubeon::game::layers::ComboLayer::Init()
{

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


	for (int i = 0; i <= 10; i++) {
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
	}


	sprintf(combo_buf,"%d",combo->get());
	keta1 = combo_buf[0];
	keta2 = combo_buf[1];
	keta3 = combo_buf[2];
	keta4 = combo_buf[3];
	
	if (combo->get() >= 6 && combo->get() <= 9) {
		this->combo_sp[keta1].setPosition(this->w / 3 * 8, get_Coordinates());
	}
	if (combo->get() >= 10 && combo->get() <= 99) {
		this->combo_sp[keta1].setPosition(this->w / 4, get_Coordinates());
		this->combo_sp[keta2].setPosition(this->w / 2, get_Coordinates());
	}
	if (combo->get() >= 100 && combo->get() <= 999) {
		this->combo_sp[keta1].setPosition(this->w / 8, get_Coordinates());
		this->combo_sp[keta2].setPosition(this->w / 8 * 3, get_Coordinates());
		this->combo_sp[keta3].setPosition(this->w / 8 * 5, get_Coordinates());
	}
	if (combo->get() >= 1000 && combo->get() <= 9999) {
		this->combo_sp[keta1].setPosition(0, get_Coordinates());
		this->combo_sp[keta2].setPosition(this->w / 4, get_Coordinates());
		this->combo_sp[keta3].setPosition(this->w / 2, get_Coordinates());
		this->combo_sp[keta4].setPosition(this->w / 4 *3, get_Coordinates());
	}

}

void jubeon::game::layers::ComboLayer::Draw()
{
	if (combo->get() >= 6 && combo->get() <= 9) {
		this->draw(this->combo_sp[keta1]);
	}
	if (combo->get() >= 10 && combo->get() <= 99) {
		this->draw(this->combo_sp[keta1]);
		this->draw(this->combo_sp[keta2]);
	}
	if (combo->get() >= 100 && combo->get() <= 999) {
		this->draw(this->combo_sp[keta1]);
		this->draw(this->combo_sp[keta2]);
		this->draw(this->combo_sp[keta3]);
	}
	if (combo->get() >= 1000 && combo->get() <= 9999) {
		this->draw(this->combo_sp[keta1]);
		this->draw(this->combo_sp[keta2]);
		this->draw(this->combo_sp[keta3]);
		this->draw(this->combo_sp[keta4]);
	}
}

void jubeon::game::layers::ComboLayer::Exit()
{
}

void jubeon::game::layers::ComboLayer::restart()
{
	if (combo->isUpdate() == true) {
		
		//���Ԃ�0��
		clock.restart();

		//y���W���f�t�H���g�ɖ߂�
		//this->y = this->y_def;

	}
}

int jubeon::game::layers::ComboLayer::get_Coordinates()
{
	this->t = this->clock.getElapsedTime().asMilliseconds();


	//�オ�肫��܂ł̍��W���v�Z���
	if (this->t <= 40) {
		return this->y_def+1 / 8 * this->t;
	}

	//�����肫��܂ł̍��W���v�Z���
	if (40 < this->t && this->t <= 160) {
		return this->y_def - 1 / 24 * this->t;
	}

	//�����肫�������Ƃ̍��W���v�Z���
	if (160 < this->t) {
		return this->y_def;
	}
	return 0;
}

jubeon::game::layers::ComboLayer::ComboLayer(int m)
{
	//std::array<sf::Texture *, 10> textures;



	//�`�ʔ͈͂��󂯎��悤�ɂ��Ȃ���? ����ł����̂��ȁ�
	this -> w = m;
}

jubeon::game::layers::ComboLayer::~ComboLayer()
{
}

