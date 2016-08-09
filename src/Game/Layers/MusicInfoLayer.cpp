#include "MusicInfoLayer.hpp"

jubeon::game::layers::MusicInfoLayer::MusicInfoLayer(const std::shared_ptr<game::Music>& music)
	: music(music)
{
}

void jubeon::game::layers::MusicInfoLayer::Init()
{
	this->createBuffer(sf::Vector2u(768, 90));
	this->buffer_sprite.setPosition(0, 0);
	
	//ƒŒƒxƒ‹‚É‚æ‚Á‚Äƒ[ƒh‚·‚é‚à‚Ì‚ğ•ª‚¯‚é
	
	this->difficulty_tex.loadFromFile("media/image/extreme_01.png");
	this->difficulty_tex.setSmooth(true);

	this->level_string_tex.loadFromFile("media/image/level_string.png");
	this->level_string_tex.setSmooth(true);

	this->level_numeric_tex.loadFromFile("media/image/level_10.png");
	this->level_numeric_tex.setSmooth(true);
}

void jubeon::game::layers::MusicInfoLayer::Draw()
{

	this->clearBuffer();

	/////////////////////
	// ƒTƒ€ƒlƒCƒ‹
	/////////////////////
	{
		sf::Sprite sp(this->music->getThumbnailTexture());
		sf::Vector2u size = this->music->getThumbnailTexture().getSize();

		//Šg‘å—¦‚ÌŒvZ
		sf::Vector2f ex(42.0f / static_cast<float>(size.x), 42.0f / static_cast<float>(size.y));

		//‚æ‚è¬‚³‚¢•û‚Åk‚ß‚é
		if (ex.x <= ex.y) ex.y = ex.x;
		else ex.x = ex.y;

		//•`Ê384,20
		sp.setPosition(384, 20);
		sp.setScale(ex);
		this->draw(sp);
	}

	////////////////////
	// ‹È–¼
	////////////////////
	{
		sf::Sprite sp(this->music->getMusicNameAndArtistTexture());
		//•`Ê440,20
		sp.setPosition(440, 20);
		this->draw(sp);
	}

	////////////////////
	// Difficulty
	////////////////////
	{
		sf::Sprite sp(this->difficulty_tex);
		sp.setPosition(210, 40);
		this->draw(sp);
	}

	////////////////////
	// level_string
	////////////////////
	{
		sf::Sprite sp(this->level_string_tex);
		sp.setPosition(210, 19);
		this->draw(sp);
	}

	////////////////////
	// level numeric
	////////////////////
	{
		sf::Sprite sp(this->level_numeric_tex);
		sp.setPosition(330, 20);
		this->draw(sp);
	}
}

void jubeon::game::layers::MusicInfoLayer::Exit()
{

}
