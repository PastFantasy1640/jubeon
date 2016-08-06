#include "Music.hpp"
#include "Systems/Logger.hpp"
#include "Storages/JsonFileStorage.hpp"

jubeon::game::Music::Music()
{
}

jubeon::game::Music::~Music()
{
}


inline void jubeon::game::Music::set(const int music_id, const std::string meta_file_name)
{
}
;

std::shared_ptr<jubeon::game::Music> jubeon::game::Music::load(const std::string meta_file_name)
{
	//���[�h���悤
	//JSON����ǂݍ���

	systems::Logger::information("�y��[���^:" + meta_file_name + "]�̓ǂݍ��݂��J�n���܂��B");

	storages::JsonFileStorage jsonfile(meta_file_name);

	std::shared_ptr<Music> ret = jsonfile.getModel<Music>();

	if (ret) {
		//����ɑ������Ă���
		
	}
	else systems::Logger::error("�v���O�����G���[:Music.cpp");
}

bool jubeon::game::Music::Init(picojson::value val)
{

	if (!val.is<picojson::object>()) {
		return false;
	}

	auto root = val.get<picojson::object>();

	//notes{}�����邩
	if (root.find("notes") == root.end()
		|| !root["notes"].is<picojson::object>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : notes��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//notes
	auto notes = root["notes"].get<picojson::object>();

	//notes.filename
	if (notes.find("filename") == notes.end()
		|| !notes["filename"].is<std::string>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : notes.filename��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//notes.type
	if (notes.find("type") == notes.end()
		|| !notes["type"].is<std::string>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : notes.type��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//TO DO : �����ꂱ���Ńf�R�[�_�[�̗L�����m�F����

	//music{}�����邩
	if (root.find("music") == root.end()
		|| !root["music"].is<picojson::object>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music
	auto music = root["music"].get<picojson::object>();

	//music.name_artist
	if (music.find("name_artist") == music.end()
		|| !music["name_artist"].is<std::string>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.name_artist��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music.name_small
	if (music.find("name_small") == music.end()
		|| !music["name_small"].is<std::string>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.name_small��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music.soundfile
	if (music.find("soundfile") == music.end()
		|| !music["soundfile"].is<std::string>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.soundfile��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music.shortsoundfile
	if (music.find("shortsoundfile") == music.end()
		|| !music["shortsoundfile"].is<std::string>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.shortsoundfile��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music.thumbnail
	if (music.find("thumbnail") == music.end()
		|| !music["thumbnail"].is<std::string>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.thumbnail��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}


	//game�����邩
	if (root.find("game") == root.end()
		|| !root["game"].is<picojson::object>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : game��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//game
	auto game = root["game"].get<picojson::object>();
	if (game.find("level") == game.end()
		|| !game["level"].is<picojson::array>()) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : game.level��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	auto levels = game["level"].get<picojson::array>();
	if (levels.size() != 3) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : game.level���ُ�Ȓl�ł��B");
		return false;
	}


	//�G���[�`�F�b�N�͑��v������
	//�����ɂ�[

	this->notes_filepath = notes["filename"].get<std::string>();
}


int jubeon::game::Music::getID(void) const
{
	return this->music_id;
}

std::string jubeon::game::Music::getNotesFilePath(const Difficulty level) const
{
	return this->notes_filepath.at(level);	//�͈͊O���ɗ�O
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
