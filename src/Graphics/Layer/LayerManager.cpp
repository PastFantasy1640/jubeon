/************************************************************
 *															*
 *	LayerManager.cpp										*
 *		Programmed by white									*
 *															*
 ************************************************************/


#include "LayerManager.hpp"
#include "LayerBase.hpp"

#include <thread>

#include "../../Systems/Exceptions.hpp"



using namespace jubeon::graphics;

const sf::Vector2u jubeon::graphics::LayerManager::RENDER_TEXTURE_SIZE = sf::Vector2u(768, 1360);

//�R���X�g���N�^
jubeon::graphics::LayerManager::LayerManager(
	const std::string & window_title,
	const sf::VideoMode & vmode,
	const bool isVSync,
	const unsigned int fpsLimit,
	const sf::Vector2i startWindowPosition,
	const sf::Uint32 style)
	: vmode(vmode),
	window_title(window_title),
	window_style(style),
	isVSync(isVSync),
	fpsLimit(fpsLimit),
	window_position(startWindowPosition),
	is_thread_running(new bool(false)),
	is_open_window(new bool(false))
{
}

//�f�X�g���N�^
jubeon::graphics::LayerManager::~LayerManager()
{
	//�����ă����[�X����K�v�͖����H
}

//���C���[�̒ǉ�
void jubeon::graphics::LayerManager::addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber)
{
	//�܂����C���[�̏��������s���B
	layer->create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y);
	layer->setSmooth(true);
	layer->Init();

	{
		//���C���[�̒ǉ�
		//�ȉ���layer_list�ɑ΂��ă��b�N���|������ԂŎ��s�����
		//������₷���悤�ɃX�R�[�v�𕪂���
		std::lock_guard<std::mutex> lock(this->layer_list_mtx);

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
}

//�X���b�h�̊J�n
void jubeon::graphics::LayerManager::run(void)
{
	//�܂��E�B���h�E�𐶐�
	this->window.reset(new sf::RenderWindow(this->vmode, this->window_title, this->window_style));
	this->window->clear();

	this->window->setVerticalSyncEnabled(this->isVSync);
	this->window->setFramerateLimit(this->fpsLimit);
	this->window->setPosition(this->window_position);

	//���ɃE�B���h�E�o�b�t�@�̐���
	this->window_buffer.reset(new sf::RenderTexture());
	this->window_buffer->create(this->RENDER_TEXTURE_SIZE.x, this->RENDER_TEXTURE_SIZE.y);
	this->window_buffer->clear();
	this->window_buffer->setSmooth(true);

	//�X���b�h�̐���
	*this->is_thread_running = true;
	*this->is_open_window = true;
	std::thread th(&LayerManager::process, this);
	th.detach();	//�X���b�h�̊J�n
}

//�E�B���h�E���J���Ă��邩
bool jubeon::graphics::LayerManager::isWindowOpening(void) const
{
	return *this->is_thread_running;
}

//�E�B���h�E���I��������
void jubeon::graphics::LayerManager::closeWindow(void)
{
	*this->is_open_window = false;
	while(*this->is_thread_running) std::this_thread::sleep_for(std::chrono::microseconds(1000));	//1ms�҂��Ė₢���킹�i���b�L���O�j
}

bool jubeon::graphics::LayerManager::getWindowEvent(sf::Event & e)
{
	return this->window->pollEvent(e);
}

//���C���[�`��
void jubeon::graphics::LayerManager::process(void)
{
	//���[�v�J�n
	while (this->window->isOpen()) {
	
		//�X���b�h�I�����m
		if (*this->is_open_window == false) {
			this->window->close();
			*this->is_open_window = false;
			break;	//�I����
		}

		this->window->clear();
		this->window_buffer->clear();

		if (this->layer_list.size() > 0) {
			for (auto p = --this->layer_list.end(); ; p--) {
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

					//��ʍX�V
					(*p)->display();

					//sf::Sprite sp(p->lb->getTexture());

					//�E�B���h�E�o�b�t�@�ɕ`��
					this->window_buffer->draw(sf::Sprite((*p)->getTexture()));
				}

				if (p == this->layer_list.begin()) break;	//�S�Ẵ��C���[��`�ʍς�
			}
		}

		//�E�B���h�E�o�b�t�@�̃A�b�v�f�[�g
		this->window_buffer->display();

		//�X�v���C�g�̍쐬
		sf::Sprite wsp(this->window_buffer->getTexture());

		//�X�v���C�g���ɂ傲�ɂ�
		sf::Vector2f scale;
		scale.x = static_cast<float>(this->window->getSize().x) / static_cast<float>(this->window_buffer->getSize().x);
		scale.y = static_cast<float>(this->window->getSize().y) / static_cast<float>(this->window_buffer->getSize().y);

		if (scale.x > scale.y) scale.x = scale.y;
		else scale.y = scale.x;

		wsp.setOrigin(static_cast<float>(this->RENDER_TEXTURE_SIZE.x) / 2.0f, static_cast<float>(this->RENDER_TEXTURE_SIZE.y) / 2.0f);
		wsp.setPosition(this->vmode.width / 2.0f, this->vmode.height / 2.0f);
		wsp.setScale(scale);
		
		//��ʕ`��
		this->window->draw(wsp);

		//��ʃA�b�v�f�[�g
		this->window->display();

	}

	//�c���Ă���̂��ׂč폜
	for (auto p = this->layer_list.begin(); p != this->layer_list.end(); ) {
		(*p)->Exit();
		p = this->layer_list.erase(p);
	}

	//�X���b�h�̏I��
	*this->is_thread_running = false;

}

