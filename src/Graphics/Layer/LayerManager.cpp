//////////////////////////////////////////////////
// (c) 2016 white LayerManager.cpp
//////////////////////////////////////////////////


//////////////////////////////////////////////////
// Header file is LayerManager.hpp
// namespace is jubeon::graphics
//////////////////////////////////////////////////

//for header file
#include "LayerManager.hpp"

//for logger
#include "Systems/Logger.hpp"

//for thread sleep
#include <thread>
#include <chrono>

//using namespace
using namespace jubeon::graphics;

//static defition
const sf::Vector2u jubeon::graphics::LayerManager::RENDER_TEXTURE_SIZE = sf::Vector2u(768, 1360);
std::unordered_map<std::string, LayerManager *> jubeon::graphics::LayerManager::layermanager_map;

//Constructor with arguments
jubeon::graphics::LayerManager::LayerManager(const std::string & mapping_name, const LayoutType window_type)
	: layout_type(window_type)
{
    //create window buffer
	if (!this->window_buffer.create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y)) {
		jubeon::systems::Logger::error("Failed to create the window render buffer.");
		return;
	}
	this->window_buffer.clear();
	this->window_buffer.setSmooth(true);
	
	//layer mapping
	this->layermanager_map[mapping_name] = this;
}


//Destructor
jubeon::graphics::LayerManager::~LayerManager()
{

}

//���C���[�̒ǉ�
void jubeon::graphics::LayerManager::addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber)
{
	//�܂����C���[�̏��������s���B
	layer->Init();

	//�����^�C�v�Ń��C���[�i���o�[�̏ꏊ�ɓ����
	unsigned char i = 0;
	std::vector<std::shared_ptr<LayerBase>>::iterator  p;
	for (p = this->layer_list.begin(); p != this->layer_list.end(); p++) {

		//�����^�C�v���ǂ����}�b�s���O���m�F����
		if (this->layer_map[*p] == type) {
			if (i == layernumber) break;	//�ԍ��������ł���΁A�������}������ꏊ
			i++;	//�����łȂ���Δԍ����C���N�������g
		}
		else if (this->layer_map[*p] > type) break;	//��΂��Ď��֍s���Ă����A�܂�ⓚ���p�ő}���ꏊ

	}

	//�V�����}������
	this->layer_map[layer] = type;
	this->layer_list.insert(p, layer);

}


//�E�B���h�E���I��������
void jubeon::graphics::LayerManager::closeWindow(void)
{
	
	//�܂����ׂĂ�Exit���Ă�
	for (auto p = this->layer_list.begin(); p != this->layer_list.end(); p++) {
		(*p)->setExitCode(1);
		(*p)->Exit();
	}

	this->close();
}


//���C���[�`��
void jubeon::graphics::LayerManager::process(void) {


	this->window_buffer.clear();


	if (this->layer_list.size() > 0) {
		for (auto p = --this->layer_list.end(); ; p--) {
			(*p)->createBuffer(this->RENDER_TEXTURE_SIZE);

			//�`��
			(*p)->Draw();

			//�I�����m
			if ((*p)->getExitCode() != 0) {
				//�I������
				(*p)->Exit();
				//���X�g����폜
				//�f�N�������g������S���[�v�ɂ�����p--���\
				p = this->layer_list.erase(p);
			}
			else {				
				this->window_buffer.draw((*p)->getSprite());
			}

			if (p == this->layer_list.begin()) break;	//�S�Ẵ��C���[��`�ʍς�
		}
	}




	//�E�B���h�E�o�b�t�@�̃A�b�v�f�[�g
	window_buffer.display();

	//�X�v���C�g�̍쐬
	sf::Sprite wsp(window_buffer.getTexture());

	//�X�v���C�g���ɂ傲�ɂ�
	sf::Vector2f scale;

	sf::Vector2u size = window_buffer.getSize();
	float rotate = 0.0f;

	if (this->layout_type == LayoutType::Y_PLUS) {
		unsigned int n = size.x;
		size.x = size.y;
		size.y = n;
		rotate = 90.0f;
	}
	else if (this->layout_type == LayoutType::X_MINUS) {
		rotate = 180.0f;
	}
	else if (this->layout_type == LayoutType::Y_MINUS) {
		rotate = 270.0f;
		unsigned int n = size.x;
		size.x = size.y;
		size.y = n;
	}
	

	scale.x = static_cast<float>(this->getSize().x) / static_cast<float>(size.x);
	scale.y = static_cast<float>(this->getSize().y) / static_cast<float>(size.y);

	if (scale.x > scale.y) scale.x = scale.y;
	else scale.y = scale.x;

	wsp.setOrigin(static_cast<float>(this->RENDER_TEXTURE_SIZE.x) / 2.0f, static_cast<float>(this->RENDER_TEXTURE_SIZE.y) / 2.0f);
	wsp.setPosition(this->getSize().x / 2.0f, this->getSize().y / 2.0f);
	wsp.setRotation(rotate);
	wsp.setScale(scale);

    { //mutable area
        std::lock_guard<std::mutex> lock(this->mtx);
        
        //Clear Window
	    this->clear();

	    //Draw Window
	    this->draw(wsp);

	    //Update Window
	    this->display();
    }
    
}

void jubeon::graphics::LayerManager::eventLoop(void)
{
	bool is_exit = false;

	this->setKeyRepeatEnabled(false);

	while (!is_exit && this->isOpen()) {
		sf::Event e;
		if (!this->waitEvent(e)) break;

		if (e.type == sf::Event::KeyPressed && e.key.alt == true && e.key.code == sf::Keyboard::F4) break;

		if (this->event_cb) this->event_cb(e);
	}

	systems::Logger::information("Closed event queuing function.");
}

void jubeon::graphics::LayerManager::setCallback(Callback function)
{
	{ //Mutable Area
		std::lock_guard<std::mutex> lock(this->mtx);
		this->event_cb = function;
	}
}


jubeon::graphics::LayerManager * jubeon::graphics::LayerManager::getInstance(const std::string & name){
    return layermanager_map.at(name);
}

void jubeon::graphics::LayerManager::processAll(void){
    for(auto p : layermanager_map){
        p.second->process();
    }
}

