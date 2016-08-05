#include "Music.hpp"

jubeon::game::Music::Music(const int id, const std::string meta_filepath)
	: metafile_path(meta_filepath), music_id(id)
{
}

jubeon::game::Music::~Music()
{
}

bool jubeon::game::Music::load(void)
{
	return false;
}

int jubeon::game::Music::getID(void) const
{
	return this->music_id;
}

std::string jubeon::game::Music::getNotesFilePath(const Difficulty level) const
{
	return this->notes_filepath.at(level);	//”ÍˆÍŠOŽž‚É—áŠO
}

const sf::Texture & jubeon::game::Music::getBpmTexture(void) const
{
	return this->bpm_texture;
}

const sf::Texture & jubeon::game::Music::getMusicNameAndArtistTexture(void) const
{
	return this->music_name_artist;
}

const sf::Texture & jubeon::game::Music::getThumbnailTexture(void) const
{
	return this->thumbnail;
}

const sf::Texture & jubeon::game::Music::getMusicNameTexture(void) const
{
	return this->music_name_mini;
}

const sf::SoundBuffer & jubeon::game::Music::getSoundForShortLoop(void) const
{
	return this->sound_short_loop;
}

jubeon::game::Level jubeon::game::Music::getLevel(const Difficulty difficulty) const
{
	return this->level.at(difficulty);
}

unsigned int jubeon::game::Music::getHighScore(const Difficulty difficulty) const
{
	return this->high_score.at(difficulty);
}

std::string jubeon::game::Music::getHighPlayRecordFilePath(const Difficulty difficulty) const
{
	return this->high_score_pr_filepath.at(difficulty);
}

std::string jubeon::game::Music::getLatestPlayRecordFilePath(const Difficulty difficulty) const
{
	return this->latest_score_pr_filepath.at(difficulty);
}

void jubeon::game::Music::setForPlay(void)
{
	
}

void jubeon::game::Music::playSound(void)
{
}

unsigned int jubeon::game::Music::getPlayingCurrentTime(void) const
{
	return this->sound.getPlayingOffset().asMilliseconds();
}

void jubeon::game::Music::deleteSound(void)
{
}
