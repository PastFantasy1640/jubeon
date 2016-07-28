#include "LayerBase.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>
#include "../../../systems/Logger/Logger.hpp"
#include "../../../systems/exceptions/Exceptions.hpp"

using namespace jubeat_online::graphics::layer;

jubeat_online::graphics::layer::LayerBase::LayerBase()
	: exit_code(0),
	sf::RenderTexture()
	//screen_buffer(nullptr)//,
/*	window(nullptr),*/
//	layer_no(10000)
{
}
/*
void jubeat_online::graphics::layer::LayerBase::createScreenBuffer(const unsigned int width, const unsigned int height)
{
	if (this->screen_buffer == nullptr) {	//2度目移行はスルー。
		try {
			this->screen_buffer = new sf::RenderTexture();
			if (this->screen_buffer == nullptr) throw std::bad_alloc();

			this->screen_buffer->create(width, height, false);
		}
		catch (std::bad_alloc e) {
			throw systems::exceptions::bad_alloc("LayerBaseにおいて描写用バッファの確保に失敗しました。メモリに十分な空きがあるか確認してください。");
		}
	}
	else {
		systems::Logger::warning("プログラムエラー。2度以上createScreenBuffer関数がコールされました。");
	}
}*/

jubeat_online::graphics::layer::LayerBase::~LayerBase()
{
	/*//もし確保していれば描写バッファの解放
	if (this->screen_buffer != nullptr) {
		delete this->screen_buffer;
		this->screen_buffer = nullptr;
	}*/
}

void jubeat_online::graphics::layer::LayerBase::setExitCode(const int code)
{
	this->exit_code = code;
	if (this->exit_code != 0) {
		systems::Logger::information("終了コード" + std::to_string(code) + "にてレイヤーが終了します。");
	}
}

unsigned int jubeat_online::graphics::layer::LayerBase::getExitCode() const {
	return this->exit_code;
}
/*
const sf::Texture * jubeat_online::graphics::layer::LayerBase::getScreenBufferTexture(void) const
{
	//screen_bufferはnullptrではないとしたうえでの動作
	this->screen_buffer->display();
	return &this->screen_buffer->getTexture();
}
*/
/*
const sf::RenderWindow * wg::systems::LayerBase::getWindow(void) const
{
	return this->window;
}

void wg::systems::LayerBase::_setWindowTarget(sf::RenderWindow * wd)
{
	if (this->window == nullptr) this->window = wd;
}

unsigned int wg::systems::LayerBase::getLayerNumber(void) const
{
	return this->layer_no;
}

void wg::systems::LayerBase::setLayerNumber(const unsigned int layer_no)
{
	this->layer_no = layer_no;
}

void wg::systems::LayerBase::drawToBuffer(const sf::Drawable * target, sf::RenderStates states)
{
	this->screen_buffer->draw(*target, states);
}

void wg::systems::LayerBase::drawToBuffer(const sf::Drawable * target)
{
	this->screen_buffer->draw(*target);
}

void wg::systems::LayerBase::clearBuffer(void) {
	this->screen_buffer->clear();
}


void wg::systems::LayerBase::_setScreenBuffer(sf::RenderTexture * rt)
{
	if(this->screen_buffer == nullptr) this->screen_buffer = rt;
}*/