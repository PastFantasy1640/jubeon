#include "RivalShutterLayer.hpp"

#include "Storages/ResourceManager.hpp"

jubeon::game::layers::RivalShutterLayer::RivalShutterLayer(const sf::Vector2f position, const std::shared_ptr<Music>& music, const Difficulty & difficulty)
	: music(music), difficulty(difficulty), enable(true)
{
	this->buffer_sprite.setPosition(position);
}

jubeon::game::layers::RivalShutterLayer::RivalShutterLayer(const sf::Vector2f position)
	: enable(false), music(), difficulty()
{
	this->buffer_sprite.setPosition(position);
}

void jubeon::game::layers::RivalShutterLayer::Init()
{
	this->createBuffer(sf::Vector2u(192,192));

	//プレイヤーが居る時といない時で背景が切り替わる
	if (this->enable) {
		storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/combowhite.png");
		storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/rival_frame.png");
		switch (this->difficulty) {
		case BASIC:		storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/rival_basic_frame.png"); break;
		case ADVANCED:	storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/rival_advanced_frame.png"); break;
		case EXTREME:	storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/rival_extreme_frame.png"); break;
		}
	}
	else {
		storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/default_rival.png");
	}
}


void jubeon::game::layers::RivalShutterLayer::Draw()
{
	this->clearBuffer();

	if (this->enable) {
		//####################TEMPORARY
		sf::Sprite tmp(storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/combowhite.png"));
		tmp.setScale(0.25263, 0.25263);
		this->draw(tmp);

		sf::Sprite sp;
		switch (this->difficulty) {
		case BASIC:		sp.setTexture(storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/rival_basic_frame.png")); break;
		case ADVANCED:	sp.setTexture(storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/rival_advanced_frame.png")); break;
		case EXTREME:	sp.setTexture(storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/rival_extreme_frame.png")); break;
		}
		this->draw(sp);

		sf::Sprite rival_frame(storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/rival_frame.png"));

	}
	else {
		//プレイヤー無し
		this->draw(sf::Sprite(storage::ResourceManager<sf::Texture>::getInstance()->get("media/image/default_rival.png")));
	}
}

void jubeon::game::layers::RivalShutterLayer::Exit()
{
}
