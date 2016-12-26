//////////////////////////////////////////////////////
// (c) 2016 white Resource.cpp
//////////////////////////////////////////////////////

#include "Resource.hpp"

#include "Systems/Logger.hpp"

jubeon::storages::Resource::Resource(const Resource & cp)
	: id(cp.id), type(cp.type), resm(cp.resm)
{
}

jubeon::storages::Resource::~Resource()
{
}

bool jubeon::storages::Resource::load(void)
{
	bool result = false;

	if (this->isReady()) return true;

	if (this->id == 0) return false;
	else if (this->resm->filename_map.count(this->id) > 0) {
		//filename
		std::string filename = this->resm->filename_map.at(this->id);
		//not yet
		switch (this->type) {
		case TEX:
			this->resm->getInstance()->textures[this->id] = std::shared_ptr<sf::Texture>(new sf::Texture());
			result = this->resm->getInstance()->textures[this->id]->loadFromFile(filename);
			this->resm->getInstance()->textures[this->id]->setSmooth(true);
			break;
		case FONT:
			this->resm->getInstance()->fonts[this->id] = std::shared_ptr<sf::Font>(new sf::Font());
			result = this->resm->getInstance()->fonts[this->id]->loadFromFile(filename);
			break;
		case SOUND:
			this->resm->getInstance()->sounds[this->id] = std::shared_ptr<sf::SoundBuffer>(new sf::SoundBuffer());
			result = this->resm->getInstance()->sounds[this->id]->loadFromFile(filename);
			break;
		}
	}
	else if(this->resm->inputstream_map.count(this->id) > 0){
		//inputstream
		sf::InputStream * is = this->resm->inputstream_map.at(this->id).get();
		//not yet
		switch (this->type) {
		case TEX:
			this->resm->getInstance()->textures[this->id] = std::shared_ptr<sf::Texture>(new sf::Texture());
			result = this->resm->getInstance()->textures[this->id]->loadFromStream(*is);
			this->resm->getInstance()->textures[this->id]->setSmooth(true);
			break;
		case FONT:
			this->resm->getInstance()->fonts[this->id] = std::shared_ptr<sf::Font>(new sf::Font());
			result = this->resm->getInstance()->fonts[this->id]->loadFromStream(*is);
			break;
		case SOUND:
			this->resm->getInstance()->sounds[this->id] = std::shared_ptr<sf::SoundBuffer>(new sf::SoundBuffer());
			result = this->resm->getInstance()->sounds[this->id]->loadFromStream(*is);
			break;
		}
	}


	return result;
}

bool jubeon::storages::Resource::isReady(void) const
{
	bool result = false;

	if (this->id == 0) return false;

	switch (this->type) {
	case TEX:
		if (this->resm->getInstance()->textures.count(this->id) > 0) result = true;
		break;
	case FONT:
		if (this->resm->getInstance()->fonts.count(this->id) > 0) result = true;
		break;
	case SOUND:
		if (this->resm->getInstance()->sounds.count(this->id) > 0) result = true;
		break;
	}
	return result;
}

std::shared_ptr<sf::Texture> jubeon::storages::Resource::gett(void)
{
	if (!this->isReady()) {
		if (!this->load()) {
			//error
			return std::shared_ptr<sf::Texture>();
		}
	}
	this->tex_sp = this->resm->textures.at(this->id);
	return this->tex_sp;
}

std::shared_ptr<sf::SoundBuffer> jubeon::storages::Resource::gets(void)
{
	if (!this->isReady()) {
		if (!this->load()) {
			//error
			return std::shared_ptr<sf::SoundBuffer>();
		}
	}
	this->snd_sp = this->resm->sounds.at(this->id);
	return this->snd_sp;
}

std::shared_ptr<sf::Font> jubeon::storages::Resource::getf(void)
{
	if (!this->isReady()) {
		if (!this->load()) {
			//error
			return std::shared_ptr<sf::Font>();
		}
	}
	this->font_sp = this->resm->fonts.at(this->id);
	return this->font_sp;
}

jubeon::storages::Resource jubeon::storages::Resource::setf(const std::string filename, const TYPE type)
{
	if (ResourceManager::getInstance()->filename_map_id.count(filename)) return Resource(ResourceManager::getInstance()->filename_map_id.at(filename), type);
	
	//‘¶İ‚µ‚È‚¢‚Ì‚Å’Ç‰Á
	Resource res(ResourceManager::getInstance()->getNextID(), type);

	ResourceManager::getInstance()->filename_map[res.id] = filename;
	ResourceManager::getInstance()->filename_map_id[filename] = res.id;
	return res;
}

jubeon::storages::Resource jubeon::storages::Resource::seti(std::unique_ptr<sf::InputStream> * inputstream, const TYPE type)
{

	if (ResourceManager::getInstance()->inputstream_map_id.count(inputstream->get())) return Resource(ResourceManager::getInstance()->inputstream_map_id.at(inputstream->get()), type);

	//‘¶İ‚µ‚È‚¢‚Ì‚Å’Ç‰Á
	Resource res(ResourceManager::getInstance()->getNextID(), type);

	ResourceManager::getInstance()->inputstream_map[res.id] = std::move(*inputstream);
	ResourceManager::getInstance()->inputstream_map_id[inputstream->get()] = res.id;
	return res;
}

jubeon::storages::Resource jubeon::storages::Resource::setk(const std::string key)
{
	if (ResourceManager::getInstance()->key_map.count(key)) return ResourceManager::getInstance()->key_map.at(key);
	systems::Logger::error("Failed to get key. There is no Key : " + key);
	return Resource(0,TEX);
}

bool jubeon::storages::Resource::setKey(const std::string key)
{
	if (ResourceManager::getInstance()->key_map.count(key)) return false;

	bool res =  ResourceManager::getInstance()->key_map.insert(std::pair<std::string,Resource>(key,*this)).second;

	if (!res) {
		systems::Logger::error("Failed to set key. (Resource.cpp  setKey function)  Key : " + key);
	}
	return res;
}

jubeon::storages::Resource::Resource(const unsigned int id, const TYPE type)
	: id(id), type(type), resm(ResourceManager::getInstance())
{
}

void jubeon::storages::Resource::operator=(Resource p)
{
	this->id = p.id;
	this->type = p.type;
}

jubeon::storages::Resource::Resource()
	: id(0), type(TEX), resm(ResourceManager::getInstance())
{
}
