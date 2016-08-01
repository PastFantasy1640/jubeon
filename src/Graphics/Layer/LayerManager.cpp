/************************************************************
 *															*
 *	LayerManager.cpp										*
 *		Programmed by white									*
 *															*
 ************************************************************/


#include "LayerManager.hpp"
#include "LayerBase.hpp"
#include <exception>
#include <thread>
#include "../../Systems/Exceptions.hpp"

using namespace jubeat_online::graphics::layer;

const sf::Vector2u jubeat_online::graphics::layer::LayerManager::RENDER_TEXTURE_SIZE = sf::Vector2u(768,1360);

//#############  �R���X�g���N�^�@�E�@�f�X�g���N�^  ###############

jubeat_online::graphics::layer::LayerManager::LayerManager()
{

}


jubeat_online::graphics::layer::LayerManager::LayerManager(
	const std::string & window_title,
	const sf::VideoMode & vmode,
	const bool isVSync,
	const unsigned int fpsLimit,
	const sf::Vector2i startWindowPosition,
	const sf::Uint32 style)
	: vmode(vmode),
	window_style(style),
	window_title(window_title),
	isVSync(isVSync),
	fpsLimit(fpsLimit),
	is_thread_running(new bool(false))
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
	
	this->window_position = startWindowPosition;
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

	this->window.setVerticalSyncEnabled(this->isVSync);
	this->window.setFramerateLimit(this->fpsLimit);
	this->window.setPosition(this->window_position);

	this->window_buffer.create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y);
	this->window_buffer.clear();
	this->window_buffer.setSmooth(true);
}


//#############  ���C���[�̒ǉ�  ###############

void jubeat_online::graphics::layer::LayerManager::addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber)
{

	//���C���[�̏�����
	layer->create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y);
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

void jubeat_online::graphics::layer::LayerManager::run(void)
{
	std::thread th(&LayerManager::process, this);
	th.detach();	//�X���b�h�̊J�n
}

bool jubeat_online::graphics::layer::LayerManager::isThreadRunning(void) const
{
	return *this->is_thread_running;
}


//#############  ���C���[�`�ʃt���[  ###############
void jubeat_online::graphics::layer::LayerManager::process(void)
{

	*this->is_thread_running = true;

	while (this->window.isOpen()) {
		sf::Event event;
		while (this->window.pollEvent(event)) {
			//�u�N���[�Y���v�����ꂽ�v�C�x���g�F�E�C���h�E�����
			if (event.type == sf::Event::Closed)
				this->window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) this->window.close();
		}


		this->window.clear();
		this->window_buffer.clear();

		if (this->layer_list->size() > 0) {
			for (auto p = --this->layer_list->end(); /*p != this->layer_list->end()*/; p--) {
				//�`��
				p->lb->Draw();

				
				//�I�����m
				if (p->lb->getExitCode() != 0) {
					//�I������
					p->lb->Exit();
					//���X�g����폜
					//�f�N�������g������S���[�v�ɂ�����p--���\
					p = this->layer_list->erase(p);
				}
				else {

					//��ʍX�V
					p->lb->display();

					sf::Sprite sp(p->lb->getTexture());

					//�E�B���h�E�o�b�t�@�ɕ`��
					this->window_buffer.draw(sp);
				}

				if (p == this->layer_list->begin()) break;	//�S�Ẵ��C���[��`�ʍς�
			}
		}

		//�E�B���h�E�o�b�t�@�̃A�b�v�f�[�g
		this->window_buffer.display();

		//�X�v���C�g�̍쐬
		sf::Sprite wsp(this->window_buffer.getTexture());

		//�X�v���C�g���ɂ傲�ɂ�
		sf::Vector2f scale;
		scale.x = static_cast<float>(this->window.getSize().x) / static_cast<float>(this->window_buffer.getSize().x);
		scale.y = static_cast<float>(this->window.getSize().y) / static_cast<float>(this->window_buffer.getSize().y);

		if (scale.x > scale.y) scale.x = scale.y;
		else scale.y = scale.x;

		wsp.setOrigin(static_cast<float>(this->RENDER_TEXTURE_SIZE.x) / 2.0f, static_cast<float>(this->RENDER_TEXTURE_SIZE.y) / 2.0f);
		wsp.setPosition(this->vmode.width / 2.0f, this->vmode.height / 2.0f);
		wsp.setScale(scale);
		
		//��ʕ`��
		this->window.draw(wsp);

		//��ʃA�b�v�f�[�g
		this->window.display();

	}


	for (auto p = this->layer_list->begin(); p != this->layer_list->end(); ) {
		p->lb->Exit();
		p = this->layer_list->erase(p);
	}

	*this->is_thread_running = false;

}
