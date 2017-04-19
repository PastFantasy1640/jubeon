#include "ImageSequencer.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>

jubeon::graphics::ImageSequencer::ImageSequencer(const std::string filenames, const unsigned int fps)
	: filename(filenames),
	fps(fps),
	frame_count(sf::Vector2u(0, 0)),
	bounding_size(sf::Vector2u(0, 0)),
	frames(0),
	now_frame(0),
	is_loaded(false)
{
}

jubeon::graphics::ImageSequencer::ImageSequencer(const std::string filename, const sf::Vector2u & frame_count, const sf::Vector2u & boundingbox_size, const unsigned int frames, const unsigned int fps)
	: filename(filename),
	fps(fps),
	frame_count(frame_count),
	bounding_size(boundingbox_size),
	frames(frames),
	now_frame(0),
	is_loaded(false)
{
}

jubeon::graphics::ImageSequencer::~ImageSequencer()
{
}

void jubeon::graphics::ImageSequencer::start()
{
	this->is_playing = true;
	this->clk.restart();
}

void jubeon::graphics::ImageSequencer::startFromHead()
{
	this->now_frame = 0;
	this->start();
}

void jubeon::graphics::ImageSequencer::stop()
{
	this->is_playing = false;
}

const sf::Texture * jubeon::graphics::ImageSequencer::getTexture() const
{
	if (this->is_playing) {
	}

	if (this->now_frame < this->size()) return this->at(this->now_frame).get();
	return nullptr;
}

bool jubeon::graphics::ImageSequencer::load()
{
	if (this->is_loaded) return true;

	//printf�̃t�H�[�}�b�g��
	int count = 0;
	std::string fname1 = "";
	std::string fname2 = "";
	{
		std::string * fname = &fname1;
		for (auto p : this->filename) {
			if (p == '#') { fname = &fname2; count++; }
			else fname->push_back(p);
		}
	}

	if (count > 0) {
		//�V�[�P���X�摜
		std::ostringstream fname;
		systems::Logger::information("ImageSequencer���A�ԉ摜�̃��[�h���J�n���܂��� : " + this->filename);
		for (int i = 1; i < pow(10, count); i++) {
			std::unique_ptr<sf::Texture> temp_tex(new sf::Texture);
			fname << fname1 << std::setw(count) << std::cout.fill(0) << i << fname2;
			if (!temp_tex->loadFromFile(fname.str())) {
				//�G���[�i�I�������\�����j
				systems::Logger::information("ImageSequencer���A�ԉ摜�̃��[�h���I�����܂��� : �ǂݍ��񂾉摜��" + std::to_string(count));
				break;
			}
			else this->emplace_back(std::move(temp_tex));
		}
	}
	else {
		//�����摜
		sf::Image tmp_img;
		systems::Logger::information("ImageSequencer���^�C���摜�̃��[�h���J�n���܂��� : " + this->filename);
		if (tmp_img.loadFromFile(fname1)) {
			//�؂�o�����
			for (int i = 0; i < this->frames; i++) {
				std::unique_ptr<sf::Texture> temp_tex(new sf::Texture);
				if (!temp_tex->loadFromImage(tmp_img, 
					sf::IntRect(this->bounding_size.x * (i % this->frame_count.x),this->bounding_size.y * (i / this->frame_count.y),this->bounding_size.x, this->bounding_size.y))) {
					//�G���[
					systems::Logger::warning("ImageSequencer�͑S�Ẵ^�C���摜��ǂݍ��߂܂���ł��� : �ǂݍ��񂾐�" + std::to_string(count));
					break;
				}
				else this->emplace_back(std::move(temp_tex));
			}
		}
		else systems::Logger::warning("ImageSequencer�̓^�C���摜��ǂݍ��߂܂���ł��� : " + this->filename);
	}

	if (this->size() > 0) {
		this->is_loaded = true;
	}

	return this->isLoaded();
}

void jubeon::graphics::ImageSequencer::unload()
{
	this->clear();
}

inline int jubeon::graphics::ImageSequencer::getFPS() const
{
	return this->fps;
}

inline void jubeon::graphics::ImageSequencer::setFPS(const unsigned int fps)
{
	this->fps = fps;
}

inline int jubeon::graphics::ImageSequencer::getNowFrame() const
{
	return this->now_frame;
}

inline void jubeon::graphics::ImageSequencer::seekNowFrame(const unsigned int to)
{
	if(to < this->size()) this->now_frame = to;
}

inline bool jubeon::graphics::ImageSequencer::isLoaded() const
{
	return this->is_loaded;
}
