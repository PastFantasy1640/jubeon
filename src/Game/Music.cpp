#include "Music.hpp"
#include "Systems/Logger.hpp"
#include "Storages/JsonFileStorage.hpp"
#include "Systems/picojson_util.hpp"


jubeon::game::Music::Music(std::string meta_file_path)
	: metafile_path(meta_file_path)
{
}

jubeon::game::Music::~Music()
{
}


picojson::value jubeon::game::Music::GetJsonValue()
{
	return picojson::value();
}

void jubeon::game::Music::set(const int music_id, const std::string meta_file_name)
{
	this->music_id = music_id;
	this->metafile_path = meta_file_name;
}

std::shared_ptr<jubeon::game::Music> jubeon::game::Music::load(const std::string meta_file_name)
{
	//���[�h���悤
	//JSON����ǂݍ���

	systems::Logger::information("�y��[���^:" + meta_file_name + "]�̓ǂݍ��݂��J�n���܂��B");

	static_assert(std::is_base_of<jubeon::models::ModelBase, Music>::value, "");
	std::ifstream ifs(meta_file_name);
	if (!ifs.is_open()) std::cerr << "failed to open json" << std::endl;
	std::istreambuf_iterator<char> it(ifs), itEnd;
	std::shared_ptr<Music> model(new Music(meta_file_name));
	
	model->jubeon::models::ModelBase::Init(std::string(it, itEnd));

	if (model) {
		//����ɑ������Ă���
		if (model->isInit()) {
			systems::Logger::information("�y��[���^:" + meta_file_name + "]�̓ǂݍ��݂��������܂����B");
		}
		else {
			systems::Logger::warning("�y��[���^:" + meta_file_name + "]�̓ǂݍ��݂Ɏ��s���܂����B");
		}
	}
	else systems::Logger::error("�v���O�����G���[:Music.cpp");

	return model;
}

bool jubeon::game::Music::Init(picojson::value val)
{

	if (!val.is<picojson::object>()) {
		return false;
	}

	auto root = val.get<picojson::object>();

	//notes{}�����邩
	if (!picojson_util::has_field<picojson::object>(val, "notes")){
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : notes��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//notes
	auto notes = root["notes"].get<picojson::object>();

	//notes.filename
	if (!picojson_util::has_field<picojson::array>(root["notes"], "filename")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : notes.filename��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	auto filenames = notes["filename"].get<picojson::array>();
	if (filenames.size() != 3) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : notes.filename���ُ�Ȓl�ł��B");
		return false;
	}

	//notes.type
	if (!picojson_util::has_field<std::string>(root["notes"], "type")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : notes.type��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//TO DO : �����ꂱ���Ńf�R�[�_�[�̗L�����m�F����

	//music{}�����邩
	if (!picojson_util::has_field<picojson::object>(val, "music")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music
	auto music = root["music"].get<picojson::object>();

	//music.name_artist
	if (!picojson_util::has_field<std::string>(root["music"], "name_artist")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.name_artist��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music.name_small
	if (!picojson_util::has_field<std::string>(root["music"], "name_small")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.name_small��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music.soundfile
	if (!picojson_util::has_field<std::string>(root["music"], "soundfile")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.soundfile��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music.shortsoundfile
	if (!picojson_util::has_field<std::string>(root["music"], "shortsoundfile")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.shortsoundfile��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//music.thumbnail
	if (!picojson_util::has_field<std::string>(root["music"], "thumbnail")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.thumbnail��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}
		
	//music.bpm_string
	if (!picojson_util::has_field<std::string>(root["music"], "bpm_string")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : music.thumbnail��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}



	//game�����邩
	if (!picojson_util::has_field<picojson::object>(val, "game")) {
		systems::Logger::warning("�ǂݍ��݂Ɏ��s : game��������Ȃ����ُ�Ȓl�ł��B");
		return false;
	}

	//game
	auto game = root["game"].get<picojson::object>();
	if (!picojson_util::has_field<picojson::array>(root["game"], "level")) {
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
	const std::string::size_type pos = std::max<signed>(this->metafile_path.find_last_of('/'), this->metafile_path.find_last_of('\\'));
	std::string directory = (pos == std::string::npos) ? std::string() : this->metafile_path.substr(0, pos + 1);
	

	for (int i = 0; i < 3;i++) this->notes_filepath[i] = directory + filenames[i].get<std::string>();
	this->decode_type = notes["type"].get<std::string>();

	this->music_name_artist.loadFromFile(music["name_artist"].get<std::string>());
	this->music_name_mini.loadFromFile(directory + music["name_small"].get<std::string>());
	this->sound_filepath = directory + music["soundfile"].get<std::string>();
	this->sound_short_loop.loadFromFile(directory + music["shortsoundfile"].get<std::string>());
	this->thumbnail.loadFromFile(directory + music["thumbnail"].get<std::string>());
	this->bpm_string = music["bpm_string"].get<std::string>();
	for (int i = 0; i < 3; i++) this->level[i] = static_cast<unsigned char>(levels[i].get<double>());

	this->is_init_success = true;
	return true;
}


int jubeon::game::Music::getID(void) const
{
	return this->music_id;
}

std::string jubeon::game::Music::getNotesFilePath(const Difficulty level) const
{
	return this->notes_filepath.at(level);	//�͈͊O���ɗ�O
}

std::string jubeon::game::Music::getBpm(void) const
{
	return this->bpm_string;
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
	//�y�Ȃ̃��[�h
	this->up_sound_buffer.reset(new sf::SoundBuffer());
	if (!this->up_sound_buffer->loadFromFile(this->sound_filepath)) {
		//���[�h�Ɏ��s
		systems::Logger::warning("�y�Ȃ̃��[�h�Ɏ��s���܂����B");
		return;
	}

	this->sound.setBuffer(*this->up_sound_buffer);
	this->sound.play();
	this->sound.pause();
	return;
}

void jubeon::game::Music::playSound(unsigned int wait_offset)
{
	this->wait_offset = wait_offset;
	this->wait_offset_ck.restart();
	auto th1 = std::thread([this, wait_offset] {
		while(this->wait_offset_ck.getElapsedTime().asMilliseconds() < wait_offset) std::this_thread::sleep_for(std::chrono::microseconds(10));
		this->sound.play();
	});
	th1.detach();
}

unsigned int jubeon::game::Music::getPlayingCurrentTime(void) const
{
	if (this->isInit()) {
		if (this->sound.getStatus() == sf::SoundSource::Status::Playing)
			return this->sound.getPlayingOffset().asMilliseconds();
		else return -(wait_offset - wait_offset_ck.getElapsedTime().asMilliseconds());
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
