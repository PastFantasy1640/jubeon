#include "ScoreLayer.hpp"

#include "Storages/Resource.hpp"

jubeon::game::layers::ScoreLayer::ScoreLayer(Player * const player, Music * const music)
	: player(player), music(music)
{

}

void jubeon::game::layers::ScoreLayer::Init()
{
	this->createBuffer(sf::Vector2u(768, 150));
	this->buffer_sprite.setPosition(0, 314);
	this->setSmooth(true);
	
	storages::Resource::setf("media/image/musicbar_start.png", storages::Resource::TEX).setKey("ScoreLayer.start");
	storages::Resource::setf("media/image/musicbar_end.png", storages::Resource::TEX).setKey("ScoreLayer.end");
	storages::Resource::setf("media/image/musicbar_bpm.png", storages::Resource::TEX).setKey("ScoreLayer.bpm");



	this->start_sp.setTexture(*storages::Resource::setk("ScoreLayer.start").gett());
	this->end_sp.setTexture(*storages::Resource::setk("ScoreLayer.end").gett());
	this->bpm_sp.setTexture(*storages::Resource::setk("ScoreLayer.bpm").gett());
	this->bpm_string_sp.setTexture(*this->music->tex_music_bpm.gett());
	
	this->start_sp.setPosition(14, 92);
	this->end_sp.setPosition(722, 92);
	this->bpm_sp.setPosition(15, 111);
	this->bpm_string_sp.setPosition(44, 111);

	this->play_name.setString(this->player->name);
	this->play_name.setColor(sf::Color::Black);
	this->play_name.setPosition(33, 31);
	this->play_name.setFont(*storages::Resource::setk("default_font").getf());

}

void jubeon::game::layers::ScoreLayer::Draw()
{

	sf::RectangleShape rct(sf::Vector2f(768,1));
	rct.setFillColor(sf::Color::Red);
	rct.setPosition(0,110);
	this->draw(rct);

	sf::RectangleShape rct2(sf::Vector2f(193,1));
	rct2.setFillColor(sf::Color::Black);
	rct2.setPosition(31,38);
	this->draw(rct2);


	this->draw(this->start_sp);
	this->draw(this->end_sp);
	this->draw(this->bpm_sp);
	this->draw(this->bpm_string_sp);
	this->draw(this->play_name);
}

void jubeon::game::layers::ScoreLayer::Exit()
{
}
