/************************************************************
 *															*
 *	LayerManager.cpp										*
 *		Programmed by white									*
 *															*
 ************************************************************/


#include "LayerManager.hpp"
#include "../LayerBase/LayerBase.hpp"
#include <exception>
#include "../../../systems/exceptions/Exceptions.hpp"

using namespace jubeat_online::graphics::layer;


//#############  �R���X�g���N�^�@�E�@�f�X�g���N�^  ###############

jubeat_online::graphics::layer::LayerManager::LayerManager()
	: layer_list(nullptr),
	vmode(LAYERMANAGER_DEFAULT_WINDOW_WIDTH, LAYERMANAGER_DEFAULT_WINDOW_HEIGHT),
	window_title("Untitled window"),
	window_style(sf::Style::Default),
	scale(1.0f)
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
}




jubeat_online::graphics::layer::LayerManager::LayerManager(
	const std::string & window_title,
	const sf::VideoMode & vmode,
	const sf::Uint32 style)
	: LayerManager()
{

	//�f�t�H���g�l�̃E�B���h�E���̍X�V
	this->vmode = vmode;
	this->window_style = style;
	this->window_title = window_title;

}





jubeat_online::graphics::layer::LayerManager::~LayerManager()
{
	//�S�Ẵ��C���[�̉��
	for (std::list<LayerDetail>::iterator p = this->layer_list->begin(); p != this->layer_list->end(); ) {
		if ((*p).lb != nullptr) {
			(*p).lb->Exit();
			delete (*p).lb;
			(*p).lb = nullptr;
		}

		p = this->layer_list->erase(p);
	}

	//���X�g�̉��
	//delete this->layer_list;
	//this->layer_list = nullptr;

	//�E�B���h�E�̏I��
	this->window.close();
}


//#############  �E�B���h�E�̐���  ###############

void jubeat_online::graphics::layer::LayerManager::createWindow(void)
{

	this->window.setVerticalSyncEnabled(true);

	this->window.create(this->vmode, this->window_title, this->window_style);
	this->window.clear();

	//#################TEMPORARY
	this->window.setPosition(sf::Vector2i(0, 0));
	this->window.setVerticalSyncEnabled(true);
}

void jubeat_online::graphics::layer::LayerManager::setScale(const double rate)
{
	this->scale = rate;
	sf::Vector2u size = this->window.getSize();
	size.x *= rate;
	size.y *= rate;
	this->window.setSize(size);
}


//#############  ���C���[�̒ǉ�  ###############

void jubeat_online::graphics::layer::LayerManager::addLayer(LayerBase * layer, const LayerType type, const unsigned char layernumber)
{
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

	this->layer_list->insert(p,newlb);

	//layer->createScreenBuffer(this->window.getSize().x, this->window.getSize().y);
	
	layer->create(this->vmode.width, this->vmode.height, false);
	layer->setSmooth(true);
	layer->Init();
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
			for (std::list<LayerDetail>::iterator p = --this->layer_list->end(); /*p != this->layer_list->end()*/; p--) {
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


	for (std::list<LayerDetail>::iterator p = this->layer_list->begin(); p != this->layer_list->end(); ) {
		p->lb->Exit();
		p = this->layer_list->erase(p);
	}

	//���C���[�S�Ă�Exit����B
	//list�͊J�����Ȃ�
	//���ꂼ��̃��C���[��������Ȃ�
}
