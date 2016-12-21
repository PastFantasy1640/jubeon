#include "Music.hpp"
#include "Systems/Logger.hpp"
#include "Storages/JsonFileStorage.hpp"
#include "Systems/picojson_util.hpp"
#include <thread>

using namespace jubeon::storages;

jubeon::game::Music::Music(std::string meta_file_path, std::string root_path)
	: ModelBase(meta_file_path), root_path(root_path)
{
}

jubeon::game::Music::~Music()
{
}


bool jubeon::game::Music::set()
{
	if (!this->root_path.empty()) this->root_path += "/";

	for (int i = 0; i < 3; i++) this->notes_filepath[i] = this->root_path + this->getJson()["notes"]["filename"][i].str();
	for (int i = 0; i < 3; i++) this->level[i] = (Level)this->getJson()["notes"]["filename"][i].num();

	
	this->decode_type = this->getJson()["notes"]["type"].str();
	this->tex_title = Resource::setf(this->root_path + this->getJson()["music"]["name_artist"].str(), Resource::TEX);
	this->tex_title_bottom = Resource::setf(this->root_path + this->getJson()["music"]["name_small"].str(), Resource::TEX);
	this->tex_jacket = Resource::setf(this->root_path + this->getJson()["music"]["thumbnail"].str(), Resource::TEX);
	this->snd_music = Resource::setf(this->root_path + this->getJson()["music"]["soundfile"].str(), Resource::SOUND);
	this->snd_shortloop = Resource::setf(this->root_path + this->getJson()["music"]["shortsoundfile"].str(), Resource::SOUND);

	this->bpm_str = this->getJson()["music"]["bpm_string"].str();


	return true;
}



int jubeon::game::Music::getID(void) const
{
	return this->music_id;
}

std::string jubeon::game::Music::getNotesFilePath(const Difficulty level) const
{
	return this->notes_filepath.at(level);	//”ÍˆÍŠOŽž‚É—áŠO
}

std::string jubeon::game::Music::getBpmString(void) const
{
	return this->bpm_str;
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


	this->sound.setBuffer(*this->snd_music->gets());
	this->sound.play();
	this->sound.pause();
	return;
}

void jubeon::game::Music::playSound(int wait_offset)
{
	this->wait_offset = wait_offset;
	this->wait_offset_ck.restart();
	auto th1 = std::thread([this, wait_offset] {
		while(this->wait_offset_ck.getElapsedTime().asMilliseconds() < wait_offset) std::this_thread::sleep_for(std::chrono::microseconds(10));
		this->sound.play();
	});
	th1.detach();
}

int jubeon::game::Music::getPlayingCurrentTime(void) const
{
	if (this->isInit()) {
		if (this->sound.getStatus() == sf::SoundSource::Status::Playing)
			return static_cast<int>(this->sound.getPlayingOffset().asMilliseconds());
		else return -(static_cast<int>(wait_offset) - static_cast<int>(wait_offset_ck.getElapsedTime().asMilliseconds()));
	}
	return 0;
}

void jubeon::game::Music::deleteSound(void)
{
	this->sound.resetBuffer();

}

bool jubeon::game::Music::isInit(void) const
{
	return this->is_init_success;
}
