//***********************************************
//*		ImageSequence Class Source File			*
//*			Programmed by white					*
//***********************************************

#include "ImageSequence.hpp"

#include <iostream>
#include <fstream>
#include <thread>
#include <cassert>
#include <exception>

#include <vector>
#include <array>

//�R���X�g���N�^
wlib::ImageSequence::ImageSequence(const std::string filename)
	: filename(filename), is_loaded(false), is_error(false), is_thread_exit(false), nonload_thread(false), loaded_frame(false), load_type(ALL_LOAD), data_size(0),
	play_frame(0), start_frame(0), in_frame(0), in_frame_(0), out_frame(0xffffffffU), fps(30), speed(1.0f), is_play(false), loop(false)
{
}

//�R�s�[�R���X�g���N�^
wlib::ImageSequence::ImageSequence(const ImageSequence & copy)
	: filename(copy.filename), is_loaded(copy.is_loaded.load()), is_error(copy.is_error.load()), is_thread_exit(copy.is_thread_exit.load()),
	nonload_thread(copy.nonload_thread.load()), loaded_frame(false), load_type(copy.load_type), data_size(copy.data_size),
	play_frame(copy.play_frame), start_frame(copy.start_frame), in_frame(copy.in_frame), in_frame_(copy.in_frame_), out_frame(copy.out_frame),
	fps(copy.fps), speed(copy.speed), is_play(copy.is_play), loop(copy.loop), image(copy.image)
{
}

//�f�R���X�g���N�^
wlib::ImageSequence::~ImageSequence(void) {
}

void wlib::ImageSequence::play(const double speed){
	if (this->is_loaded == false) return;	//�܂��Đ��s�\
	if (this->data_size == 0) return;
	this->play_frame = this->in_frame;

	this->is_play = true;
	this->start_frame = this->in_frame;
	this->timer.restart();

}

void wlib::ImageSequence::stop(void) {
	if (this->is_loaded == false && this->is_play == false) return;	//�܂��Đ��s�\

	this->is_play = false;

}

void wlib::ImageSequence::DrawSequence(sf::RenderTexture * screen_buffer, const float x, const float y, const float ex){
	//�G���[�`�F�b�N
	assert(screen_buffer != nullptr);

	//���[�h�͊������Ă��邩
	if (this->is_loaded == false) return;

	//�Đ�����
	if (this->is_play) {
		this->play_frame = static_cast<int>(this->timer.getElapsedTime().asSeconds() * this->fps) + this->in_frame;
		if (this->play_frame >= this->data_size || this->play_frame >= this->out_frame) {
			if (this->loop == true) {
				//���s�[�g����
/*				this->play_frame %= (this->out_frame - this->in_frame);
				this->play_frame += in_frame;*/
				this->stop();
				this->in_frame = this->in_frame_;
				this->play();
			}
			else {
				this->is_play = false;
				this->play_frame = 0;
			}
		}

		if (is_play == true) {
			//���̃t���[���͕`�ʂł��邩
			assert(this->play_frame < this->data_size);
			if (this->data[this->play_frame]->isLoaded()) {
				sf::Sprite graph(*this->data[this->play_frame]->texture_up.get());
				graph.setPosition(x, y);
				graph.setScale(ex, ex);
				screen_buffer->draw(graph);
			}
		}
	}

}

void wlib::ImageSequence::DrawFrame(const unsigned int frame, sf::RenderTexture * screen_buffer, const float x, const float y, const float ex)
{
	if (frame < this->data_size && this->is_loaded) {
		if (this->data[frame]->isLoaded()) {
			sf::Sprite graph(*this->data[frame]->texture_up.get());
			graph.setPosition(x, y);
			graph.setScale(ex, ex);
			screen_buffer->draw(graph);
		}
	}
}

const sf::Texture * wlib::ImageSequence::operator[](unsigned int frame) const
{
	if (frame < this->data_size) {
		return this->data[frame]->texture_up.get();
	}
	return nullptr;
}

std::string wlib::ImageSequence::getFilePath(void) const
{
	return this->filename;
}

std::size_t wlib::ImageSequence::getNonloadFrame(void) const
{
	return this->nonload_thread;
}

std::size_t wlib::ImageSequence::getAllFrames(void) const
{
	return this->data_size;
}

size_t wlib::ImageSequence::getPlayFrame(void) const
{
	if(this->is_play) return play_frame;
	return -1;
}

bool wlib::ImageSequence::getIsPlaying(void) const
{
	return this->is_play;
}

sf::Time wlib::ImageSequence::getPlayingTime(void) const
{
	return this->timer.getElapsedTime();
}

void wlib::ImageSequence::setFPS(unsigned int fps)
{
	this->fps = fps;
}

void wlib::ImageSequence::divideImage(const unsigned int width, const unsigned int height, const unsigned int div_xnum, const unsigned int div_ynum, const unsigned int frame)
{/*
	if (is_loaded == false) return;
	unsigned int now_frame = 0;
	try {
		this->data = new ImageSequence::Data[frame];
		for (unsigned int i = 0; i < frame; i++) {
			this->data[i].image = new sf::Texture;
		}
	}
	catch (std::bad_alloc) {
		std::cout << "ImageSequence>" + this->filename + ":�������̊m�ێ��s" << std::endl;
		this->is_error = true;
		return;
	}
	for (unsigned int x = 0; x < div_xnum && now_frame < frame; x++) {
		for (unsigned int y = 0; y < div_ynum && now_frame < frame; y++) {
			sf::IntRect area(x * width, y * height, width, height);
			this->data[now_frame++].image->loadFromImage(*this->image, area);
		}
	}
	this->data_size = frame;
	*/
	return;
}

bool wlib::ImageSequence::getLoadedFlag(void) const
{
	return this->is_loaded;
}

bool wlib::ImageSequence::getErrorFlag(void) const
{
	return this->is_error;
}

void wlib::ImageSequence::load(const LoadType type) {
	if (this->is_loaded == true) {
		std::cout << "ImageSequence>" + this->filename + ":���łɃ��[�h���I�����Ă��܂�" << std::endl;
		return;
	}
	this->load_type = type;
	std::thread th(&ImageSequence::pBufTh, this);
	th.detach();
}

void wlib::ImageSequence::pBufTh(void) {

	sf::Clock time_watch;
	//�t�@�C�����J��
	std::cout << "ImageSequence>" + this->filename + ":���[�h���J�n" << std::endl;

	time_watch.restart();

	std::ifstream fp(this->filename, std::ios::binary | std::ios::in);
	if (!fp) {
		//�t�@�C���̊J���Ɏ��s
		std::cout << "ImageSequence>" + this->filename + ":���[�h�Ɏ��s" << std::endl;
		this->is_error = true;
		return;
	}

	sf::Time time_capture = time_watch.getElapsedTime();
	std::cout << "ImageSequence>" + this->filename + ":�t�@�C���J��\t" << time_capture.asMicroseconds() << "microsec." << std::endl;
	

	//��{�f�[�^�̓Ǐo��
	char type[4] = {'\0', '\0', '\0', '\0'};
	char length = 0x00, fps = 0x00;
	char tm[2] = { 0x00, 0x00 };
	char start_pos[8];
	std::streampos spos;


	//�܂����ʎq�̎擾
	fp.read(type, 3);
	fp.read(&length, 1);
	fp.read(&fps, 1);
	fp.read(tm, 2);
	fp.read(start_pos, 8);

	if (fp.bad()) {
		std::cout << "ImageSequence>" + this->filename + ":�w�b�_�̓ǂݍ��ݎ��s" << std::endl;
		this->is_error = true;
		return;
	}

	//�^�C�v�̑I��
	//������isf�łȂ��Ȃ�A�����摜�Ƃ��ď�������B
	std::string type_s = type;
	if (type_s.compare("ISF") != 0) {
		//isf�łȂ��ꍇ
		//�t���[����1���̉摜�Ƃ��ēǂݍ���
/*		std::cout << "ImageSequence>" + this->filename + ":�����摜�Ɣ���" << std::endl;
		size_t fileSize = static_cast<std::size_t>(fp.seekg(0, std::ios::end).tellg());
		fp.seekg(0, std::ios::beg);
		
		this->data_size = 0;
		try {
			this->data = new ImageSequence::Data[1];
			this->data[0].data = new char[fileSize];
			this->image = new sf::Image;
		}
		catch (std::bad_alloc) {
			std::cout << "ImageSequence>" + this->filename + ":�������̊m�ێ��s" << std::endl;
			this->is_error = true;
			return;
		}
		fp.read(this->data[0].data, fileSize);
		if (!this->image->loadFromMemory(this->data[0].data, fileSize)) {
			std::cout << "ImageSequence>" + this->filename + ":�摜�t�@�C���ǂݍ��ݎ��s" << std::endl;
			this->is_error = true;
			delete[] this->data[0].data;
			return;
		}
		delete[] this->data[0].data;
		this->data[0].data = nullptr;
		delete[] this->data;
		this->data = nullptr;
		fp.close();
		
		this->is_loaded = true;
		std::cout << "ImageSequence>" + this->filename + ":���[�h����" << std::endl;
		return;*/
	}

	//fps
	this->fps = static_cast<int>(fps);

	//���t���[����
	this->data_size = 0;
	for (int i = 0; i < 2; i++) {
		unsigned int t = static_cast<unsigned int>(0x000000ff & tm[i]);
		t <<= 8 * i;
		this->data_size |= t;
	}

	out_frame = this->data_size;
	in_frame = 0;

	//�X�^�[�g�|�W�V����
	unsigned long spos_l = 0;
	for (int i = 0; i < length; i++) {
		long t = static_cast<size_t>(0x000000ff & start_pos[i]);
		t <<= 8 * i;
		spos_l |= t;
	}
	spos = spos_l;

	//�t���[�����̃������m��
	try {
		this->data.reserve(this->data_size);
	}
	catch (std::bad_alloc) {
		std::cout << "ImageSequence>" + this->filename + ":�������̊m�ێ��s" << std::endl;
		this->is_error = true;
		return;
	}

	{
		//size_str�̃X�R�[�v�炵���B
		std::vector<char> size_str(length);

		for (int i = 0; i < this->data_size; i++) {
			//�t�@�C�������擾		
			fp.read(size_str.data(), size_str.size());
			if (fp.bad()) {
				std::cout << "ImageSequence>" + this->filename + "[" << i << "]:�t�@�C�����̓ǂݍ��ݎ��s" << std::endl;
				this->is_error = true;
				return;
			}

			long size = 0;
			for (int i = 0; i < size_str.size(); i++) {
				long t = static_cast<size_t>(0x000000ff & size_str[i]);
				t <<= i * 8;
				size |= t;
			}

			this->data.emplace_back(new ImageSequenceData(fp, spos, size));
			spos += size;
		}
	}


	time_capture = time_watch.getElapsedTime() - time_capture;
	std::cout << "ImageSequence>" + this->filename + ":�w�b�_�ǂݎ��I��" << time_capture.asMicroseconds() << "usec.\t���t���[����:" << this->data_size << "f" << std::endl;

	time_watch.restart();

	this->nonload_thread = this->data_size;

	//�^�C�v�ɂ���ĕ�����
	//***ALL_LOAD
	//���data�ɂ��ׂđ������
	//�����ăX���b�h�𕪂��Ď��s

	//***STREAMING
	//���data�ɂ��ׂđ������
	//CHECK_LOADTIME_FRAMES�ǂ�
	//�����ăX���b�h�𕪂��Ď��s

	//STREAMING_DELETE
	//

	//���ׂ�data�ɑ��
	std::cout << "ImageSequence>" + this->filename + ":�������ɓǂݏo���J�n" << std::endl;
	for (std::size_t i = 0; i < this->data_size; i++, this->nonload_thread--) {
		if (i % 200 == 0 && i > 0) std::cout << "ImageSequence>" + this->filename + ":" << static_cast<int>(static_cast<float>(i) * 100.0f / static_cast<float>(this->data_size)) << "%����" << std::endl;
		
		this->data.at(i)->load();

	}

	time_capture = time_watch.getElapsedTime();
	std::cout << "ImageSequence>" + this->filename + ":�t�@�C���̓Ǐo��������\t" << time_capture.asMilliseconds() << "msec." << std::endl;
	std::cout << "ImageSequence>" + this->filename + ":�t���[���̃��[�h���J�n" << std::endl;

	fp.close();

	//�X�g���[�~���O����K�v���Ȃ��ꍇ
	if (this->data_size <= ImageSequence::CHECK_LOADTIME_FRAMES) this->load_type = ImageSequence::ALL_LOAD;

	//##����I��

	int load_start_frame = 0;
	int frame = static_cast<int>(this->data_size);
	if (this->load_type != ImageSequence::ALL_LOAD) {
		long all_time = 0;
		const int sampling_frame = ImageSequence::CHECK_LOADTIME_FRAMES;

		//�܂�sampling_frame�������U�蕪����
		std::array<std::vector<ImageSequenceData *>, ImageSequence::MAX_THREAD_NUM> works_t;
		for (int i = 0; i < works_t.size(); i++) {
			works_t[i].clear();
		}

		for (int i = 0; i < this->data_size && i < sampling_frame * ImageSequence::MAX_THREAD_NUM; i++) {
			works_t.at(i % ImageSequence::MAX_THREAD_NUM).push_back(this->data[i].get());
		}

		std::vector<std::unique_ptr<std::thread>> thvec;
		for (int i = 0; i < ImageSequence::MAX_THREAD_NUM; i++) {
			thvec.emplace_back(new std::thread(&ImageSequence::loadTh, this, works_t[i]));
		}
		//�S���[�h���I���܂ő҂�
		for (int i = 0; i < thvec.size(); i++) thvec[i]->join();

		thvec.clear();

		for (int i = 0; i < works_t.size(); i++) {
			for (int n = 0; n < works_t[i].size(); n++) {
				all_time += works_t[i][n]->getLoadTime();
			}
		}

		//�X�g���[�~���O���Ԃ̎Z�o
		double ave_time = all_time / static_cast<double>(sampling_frame * ImageSequence::MAX_THREAD_NUM);
		std::cout << "ImageSequence>" + this->filename + ":�ǂݍ��ݕ��ώ���" << ave_time << "ms" << std::endl;
		frame = static_cast<int>(this->data_size) - static_cast<int>(this->data_size * 1000.0f / fps / ave_time) + 10;
		if (frame <= 0)	std::cout << "ImageSequence>" + this->filename + ":�������[�h�t���[���Ȃ�" << std::endl;
		else std::cout << "ImageSequence>" + this->filename + ":�������[�h�t���[��:" << frame << "f" << std::endl;

		load_start_frame = sampling_frame * ImageSequence::MAX_THREAD_NUM;
	}

	//�I�[�����[�h
	std::array<std::vector<ImageSequenceData *>, ImageSequence::MAX_THREAD_NUM> works;
	for (int i = 0; i < works.size(); i++) {
		works[i].clear();
	}
	
	for (int i = load_start_frame; i < this->data_size; i++) {
		works[i % ImageSequence::MAX_THREAD_NUM].emplace_back(this->data[i].get());
	}

	for (int i = 0; i < ImageSequence::MAX_THREAD_NUM; i++) {
		std::thread loadth(&ImageSequence::loadTh, this, works[i]);
		loadth.detach();
	}

	//�ǂ��܂œǂݍ��ݏI����������v�Z
	this->loaded_frame = 0;
	while(this->loaded_frame < this->data_size){
		if (this->data[this->loaded_frame]->isLoaded()) loaded_frame++;
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}

		//���[�h���Z���ꂽ�Ƃ�

		if (this->loaded_frame % 100 == 0 && this->loaded_frame > 0) {
			std::cout << "ImageSequence>" + this->filename + ":" << static_cast<int>(static_cast<float>(this->loaded_frame) * 100.0f / static_cast<float>(this->data_size)) << "%����" << std::endl;
		}
		
		if (static_cast<int>(this->loaded_frame) >= frame && this->is_loaded == false) {
			std::cout << "ImageSequence>" + this->filename + "�Đ��̂��߂̃��[�h������" << std::endl;
			this->is_loaded = true;
		}
	}
	std::cout << "ImageSequence>" + this->filename + ":�S���[�h������\t�����[�h����:" << time_watch.getElapsedTime().asMilliseconds() << "msec." << std::endl;
}

void wlib::ImageSequence::loadTh(std::vector<ImageSequenceData *> data){
	sf::Clock lt;
	for (std::size_t i = 0; i < data.size(); i++, this->nonload_thread--) {
		lt.restart();
		
		data.at(i)->texture_up.reset(new sf::Texture);
		if (data.at(i)->texture_up->loadFromStream(*(data.at(i))) == false) {
			this->is_error = true;
		}
		data[i]->texture_up->setSmooth(true);
		
	}
}

void wlib::ImageSequence::setLoopFlag(const bool flag){
	this->loop = true;
}

bool wlib::ImageSequence::getLoopFlag(void) const
{
	return this->loop;
}

void wlib::ImageSequence::setInPoint(const unsigned int frame)
{
	in_frame_ = frame;
}

void wlib::ImageSequence::setOutPoint(const unsigned int frame)
{
	out_frame = frame;
}

