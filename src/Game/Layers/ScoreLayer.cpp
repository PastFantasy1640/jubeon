#include "ScoreLayer.hpp"

#include "Storages/Resource.hpp"

jubeon::game::layers::ScoreLayer::ScoreLayer(Player * const player, Music * const music)
	: player(player), music(music), music_length(0)
{

}

void jubeon::game::layers::ScoreLayer::Init()
{
	this->createBuffer(sf::Vector2u(768, 150));
	this->buffer_sprite.setPosition(0, 314);

	
	storages::Resource::setf("media/image/musicbar_start.png", storages::Resource::TEX).setKey("ScoreLayer.start");
	storages::Resource::setf("media/image/musicbar_end.png", storages::Resource::TEX).setKey("ScoreLayer.end");
	storages::Resource::setf("media/image/musicbar_bpm.png", storages::Resource::TEX).setKey("ScoreLayer.bpm");

	storages::Resource::setf("media/image/gray_chip.png", storages::Resource::TEX).setKey("ScoreLayer.graychip");
	storages::Resource::setf("media/image/blue_chip.png", storages::Resource::TEX).setKey("ScoreLayer.bluechip");
	storages::Resource::setf("media/image/yellow_chip.png", storages::Resource::TEX).setKey("ScoreLayer.yellowchip");
	storages::Resource::setf("media/image/seekbar.png", storages::Resource::TEX).setKey("ScoreLayer.seekbar");

	storages::Resource::setf("media/font/Frutiger.ttf", storages::Resource::FONT).setKey("ScoreLayer.scorefont");
	
	this->seek_sp.setColor(sf::Color(255,255,255, 255));

	this->start_sp.setTexture(*storages::Resource::setk("ScoreLayer.start").gett());
	this->end_sp.setTexture(*storages::Resource::setk("ScoreLayer.end").gett());
	this->bpm_sp.setTexture(*storages::Resource::setk("ScoreLayer.bpm").gett());
	this->bpm_string_sp.setTexture(*this->music->tex_music_bpm.gett());
	this->gray_chip_sp.setTexture(*storages::Resource::setk("ScoreLayer.graychip").gett());
	this->blue_chip_sp.setTexture(*storages::Resource::setk("ScoreLayer.bluechip").gett());
	this->yellow_chip_sp.setTexture(*storages::Resource::setk("ScoreLayer.yellowchip").gett());
	this->seek_sp.setTexture(*storages::Resource::setk("ScoreLayer.seekbar").gett());
	
	this->start_sp.setPosition(14, 92);
	this->end_sp.setPosition(722, 92);
	this->bpm_sp.setPosition(15, 113);
	this->bpm_string_sp.setPosition(44, 113);

	this->play_name.setString(this->player->name);
	this->play_name.setColor(sf::Color::Black);
	this->play_name.setPosition(33, 31);
	this->play_name.setFont(*storages::Resource::setk("default_font").getf());
	
	this->score_text.setColor(sf::Color::Black);
	this->score_text.setCharacterSize(48);
	this->score_text.setFont(*storages::Resource::setk("ScoreLayer.scorefont").getf());

	this->musicbar.init(this->player->getSequence(), this->music);
	this->music_length = this->music->getMusicLength();

}

void jubeon::game::layers::ScoreLayer::Draw()
{

	this->clearBuffer();

	this->musicbar.update(this->music);

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

	//ミュージックバーの描写
	for (size_t i = 0; i < BAR_SIZE; i++) {
		for (int p = 0; p < this->musicbar[i].num; p++) {
			sf::Vector2f pos;
			pos.x = 85 + i * 5;
			pos.y = 105 - p * 5;
			switch (this->musicbar[i].result) {
			case Bar::GRAY:
			case Bar::NJDGE:
				this->gray_chip_sp.setPosition(pos);
				this->draw(this->gray_chip_sp);
				break;
			case Bar::BLUE:
				this->blue_chip_sp.setPosition(pos);
				this->draw(this->blue_chip_sp);
				break;
			case Bar::YELLOW:
				this->yellow_chip_sp.setPosition(pos);
				this->draw(this->yellow_chip_sp);
				break;
			}

		}
	}

	double length = this->music->getPlayingCurrentTime() * 600.0f / this->music_length;
	this->seek_sp.setPosition(68 + length, 69);

	this->draw(this->seek_sp);

	//Draw Score
	std::string str = std::to_string(this->player->getPlayRecord()->getScore()->getAnimatedScore());
	int x = 463;
	for (auto c = str.rbegin(); c != str.rend(); c++) {
		char buf[2]{ *c, '\0' };
		this->score_text.setString(std::string(buf));
		this->score_text.setPosition(x, 12);
		this->draw(this->score_text);
		x -= 30;
	}
}

void jubeon::game::layers::ScoreLayer::Exit()
{
}
