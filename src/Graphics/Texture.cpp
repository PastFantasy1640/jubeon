#include "Texture.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>

jubeon::graphics::Texture::Texture(const std::string filenames, const unsigned int fps)
	: filename(filenames),
	fps(fps),
	frame_count(sf::Vector2u(0, 0)),
	bounding_size(sf::Vector2u(0, 0)),
	frames(0),
	now_frame(0),
	is_loaded(false)
{
}

jubeon::graphics::Texture::Texture(const std::string filename, const sf::Vector2u & frame_count, const sf::Vector2u & boundingbox_size, const unsigned int frames, const unsigned int fps)
	: filename(filename),
	fps(fps),
	frame_count(frame_count),
	bounding_size(boundingbox_size),
	frames(frames),
	now_frame(0),
	is_loaded(false)
{
}

jubeon::graphics::Texture::~Texture()
{
}

void jubeon::graphics::Texture::start()
{
	this->is_playing = true;
	this->clk.restart();
}

void jubeon::graphics::Texture::startFromHead()
{
	this->now_frame = 0;
	this->start();
}

void jubeon::graphics::Texture::stop()
{
	this->is_playing = false;
}

const sf::Texture * jubeon::graphics::Texture::getTexture() const
{
	if (this->is_playing) {
	}

	if (this->now_frame < this->size()) return this->at(this->now_frame).get();
	return nullptr;
}

bool jubeon::graphics::Texture::load()
{
	if (this->is_loaded) return true;

	//printfのフォーマット化
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
		//シーケンス画像
		std::ostringstream fname;
		systems::Logger::information("Textureが連番画像のロードを開始しました : " + this->filename);
		for (int i = 1; i < pow(10, count); i++) {
			std::unique_ptr<sf::Texture> temp_tex(new sf::Texture);
			fname << fname1 << std::setw(count) << std::cout.fill(0) << i << fname2;
			if (!temp_tex->loadFromFile(fname.str())) {
				//エラー（終了した可能性も）
				systems::Logger::information("Textureが連番画像のロードを終了しました : 読み込んだ画像数" + std::to_string(count));
				break;
			}
			else this->emplace_back(std::move(temp_tex));
		}
	}
	else {
		//分割画像
		sf::Image tmp_img;
		systems::Logger::information("Textureがタイル画像のロードを開始しました : " + this->filename);
		if (tmp_img.loadFromFile(fname1)) {
			//切り出し作業
			for (int i = 0; i < this->frames; i++) {
				std::unique_ptr<sf::Texture> temp_tex(new sf::Texture);
				if (!temp_tex->loadFromImage(tmp_img, 
					sf::IntRect(this->bounding_size.x * (i % this->frame_count.x),this->bounding_size.y * (i / this->frame_count.y),this->bounding_size.x, this->bounding_size.y))) {
					//エラー
					systems::Logger::warning("Textureは全てのタイル画像を読み込めませんでした : 読み込んだ数" + std::to_string(count));
					break;
				}
				else this->emplace_back(std::move(temp_tex));
			}
		}
		else systems::Logger::warning("Textureはタイル画像を読み込めませんでした : " + this->filename);
	}

	if (this->size() > 0) {
		this->is_loaded = true;
	}

	return this->isLoaded();
}

void jubeon::graphics::Texture::unload()
{
	this->clear();
}

inline int jubeon::graphics::Texture::getFPS() const
{
	return this->fps;
}

inline void jubeon::graphics::Texture::setFPS(const unsigned int fps)
{
	this->fps = fps;
}

inline int jubeon::graphics::Texture::getNowFrame() const
{
	return this->now_frame;
}

inline void jubeon::graphics::Texture::seekNowFrame(const unsigned int to)
{
	if(to < this->size()) this->now_frame = to;
}

inline bool jubeon::graphics::Texture::isLoaded() const
{
	return this->is_loaded;
}
