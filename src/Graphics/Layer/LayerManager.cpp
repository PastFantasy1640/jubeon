/************************************************************
 *															*
 *	LayerManager.cpp										*
 *		Programmed by white									*
 *															*
 ************************************************************/


#include "LayerManager.hpp"
#include "LayerBase.hpp"
#include <exception>
#include "../../Systems/Exceptions.hpp"

using namespace jubeat_online::graphics::layer;


//#############  �R���X�g���N�^�@�E�@�f�X�g���N�^  ###############

jubeat_online::graphics::layer::LayerManager::LayerManager()
{

}


jubeat_online::graphics::layer::LayerManager::LayerManager(
	const std::string & window_title, 
	const sf::VideoMode & vmode,
	const bool isVSync,
	const int fpsLimit, 
	const sf::Vector2i startWindowPosition,
	const sf::Uint32 style)
	: vmode(vmode),
	window_style(style),
	window_title(window_title),
	isVSync(isVSync),
	fpsLimit(fpsLimit)
{

	//�E�B���h�E�̐����͕ʁB

	//���X�g�C���X�^���X�̐���
	try {
		this->layer_list.reset(new std::list<LayerDetail>);

		if (this->layer_list == nullptr) throw std::bad_alloc();
	}
	catch (std::bad_alloc e) {
		this->layer_list = nullptr;
		//�������̊m�ۂɎ��s�����ꍇ�ăX���[
		throw jubeat_online::systems::exceptions::bad_alloc(
			"LayerManager�ɂ����ă��C���[���X�g�p�̗̈�m�ۂɎ��s���܂����B�������ɏ\���ȋ󂫂����邩�m�F���Ă��������B");
	}
	
	this->window.setPosition(startWindowPosition);
}





jubeat_online::graphics::layer::LayerManager::~LayerManager()
{
	//�S�Ẵ��C���[�̉��
	for (auto p = this->layer_list->begin(); p != this->layer_list->end(); ) {
		if ((*p).lb) {
			(*p).lb->Exit();
		}

		p = this->layer_list->erase(p);
	}

	//�E�B���h�E�̏I��
	this->window.close();
}


//#############  �E�B���h�E�̐���  ###############

void jubeat_online::graphics::layer::LayerManager::createWindow(void)
{
	
	this->window.create(this->vmode, this->window_title, this->window_style);
	this->window.clear();

	this->window.setPosition(sf::Vector2i(1920, -835));
	this->window.setVerticalSyncEnabled(true);
	this->window.setFramerateLimit(30);
}


//#############  ���C���[�̒ǉ�  ###############

void jubeat_online::graphics::layer::LayerManager::addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber)
{

	//���C���[�̏�����
	layer->create(this->vmode.width, this->vmode.height, false);
	layer->setSmooth(true);
	layer->Init();

	//���������������Ă���Draw���͂��߂�

	//���C���[�̒ǉ�
	//�����^�C�v�Ń��C���[�i���o�[�̏ꏊ�ɓ����
	unsigned char i = 0;
	std::list<LayerDetail>::iterator  p;
	for (p = this->layer_list->begin(); p != this->layer_list->end(); p++) {
		if ((*p).lt == type) {
			if (i == layernumber) break;
			i++;
		}
		else if ((*p).lt > type) break;
	}

	LayerDetail newlb;
	newlb.lb = layer;
	newlb.lt = type;

	//shared_ptr�̓X���b�h�Z�[�t
	this->layer_list->insert(p,newlb);

	
}


//#############  ���C���[�`�ʃt���[  ###############
void jubeat_online::graphics::layer::LayerManager::process(void)
{



	while (this->window.isOpen()) {
		sf::Event event;
		while (this->window.pollEvent(event)) {
			//�u�N���[�Y���v�����ꂽ�v�C�x���g�F�E�C���h�E�����
			if (event.type == sf::Event::Closed)
				this->window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) this->window.close();
		}


		this->window.clear();
		if (this->layer_list->size() > 0) {
			for (auto p = --this->layer_list->end(); /*p != this->layer_list->end()*/; p--) {
				//�`��
				p->lb->Draw();

				p->lb->display();
				sf::Sprite sp(p->lb->getTexture());
				
				//sp.setTexture(*p->lb->getScreenBufferTexture());
				//sp.setPosition(0, 0);
				if (this->scale != 1.0f) {
					//sp.setScale(1.0f / this->scale, 1.0f / this->scale);
					sp.setScale(1, 1);
				}
				this->window.draw(sp);
				

				if (p->lb->getExitCode() != 0) {
					//�I������
					p->lb->Exit();
					//���X�g����폜
					p = this->layer_list->erase(p);
				}
				//else p--;
				if (p == this->layer_list->begin()) break;	//�S�Ẵ��C���[��`�ʍς�
			}
		}

		window.display();   //�`��A�b�v�f�[�g
	}


	for (auto p = this->layer_list->begin(); p != this->layer_list->end(); ) {
		p->lb->Exit();
		p = this->layer_list->erase(p);
	}

	//���C���[�S�Ă�Exit����B
	//list�͊J�����Ȃ�
	//���ꂼ��̃��C���[��������Ȃ�
}
