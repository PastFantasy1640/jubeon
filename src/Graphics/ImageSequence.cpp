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

//コンストラクタ
wlib::ImageSequence::ImageSequence(const std::string filename)
	: filename(filename), is_loaded(false), is_error(false), is_thread_exit(false), nonload_thread(false), loaded_frame(false), load_type(ALL_LOAD), data_size(0),
	play_frame(0), start_frame(0), in_frame(0), in_frame_(0), out_frame(0xffffffffU), fps(30), speed(1.0f), is_play(false), loop(false)
{
}

//コピーコンストラクタ
wlib::ImageSequence::ImageSequence(const ImageSequence & copy)
	: filename(copy.filename), is_loaded(copy.is_loaded.load()), is_error(copy.is_error.load()), is_thread_exit(copy.is_thread_exit.load()),
	nonload_thread(copy.nonload_thread.load()), loaded_frame(false), load_type(copy.load_type), data_size(copy.data_size),
	play_frame(copy.play_frame), start_frame(copy.start_frame), in_frame(copy.in_frame), in_frame_(copy.in_frame_), out_frame(copy.out_frame),
	fps(copy.fps), speed(copy.speed), is_play(copy.is_play), loop(copy.loop), image(copy.image)
{
}

//デコンストラクタ
wlib::ImageSequence::~ImageSequence(void) {
}

void wlib::ImageSequence::play(const double speed){
	if (this->is_loaded == false) return;	//まだ再生不可能
	if (this->data_size == 0) return;
	this->play_frame = this->in_frame;

	this->is_play = true;
	this->start_frame = this->in_frame;
	this->timer.restart();

}

void wlib::ImageSequence::stop(void) {
	if (this->is_loaded == false && this->is_play == false) return;	//まだ再生不可能

	this->is_play = false;

}

void wlib::ImageSequence::DrawSequence(sf::RenderTexture * screen_buffer, const float x, const float y, const float ex){
	//エラーチェック
	assert(screen_buffer != nullptr);

	//ロードは完了しているか
	if (this->is_loaded == false) return;

	//再生中か
	if (this->is_play) {
		this->play_frame = static_cast<int>(this->timer.getElapsedTime().asSeconds() * this->fps) + this->in_frame;
		if (this->play_frame >= this->data_size || this->play_frame >= this->out_frame) {
			if (this->loop == true) {
				//リピート処理
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
			//このフレームは描写できるか
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
		std::cout << "ImageSequence>" + this->filename + ":メモリの確保失敗" << std::endl;
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
		std::cout << "ImageSequence>" + this->filename + ":すでにロードが終了しています" << std::endl;
		return;
	}
	this->load_type = type;
	std::thread th(&ImageSequence::pBufTh, this);
	th.detach();
}

void wlib::ImageSequence::pBufTh(void) {

	sf::Clock time_watch;
	//ファイルを開く
	std::cout << "ImageSequence>" + this->filename + ":ロードを開始" << std::endl;

	time_watch.restart();

	std::ifstream fp(this->filename, std::ios::binary | std::ios::in);
	if (!fp) {
		//ファイルの開封に失敗
		std::cout << "ImageSequence>" + this->filename + ":ロードに失敗" << std::endl;
		this->is_error = true;
		return;
	}

	sf::Time time_capture = time_watch.getElapsedTime();
	std::cout << "ImageSequence>" + this->filename + ":ファイル開封\t" << time_capture.asMicroseconds() << "microsec." << std::endl;
	

	//基本データの読出し
	char type[4] = {'\0', '\0', '\0', '\0'};
	char length = 0x00, fps = 0x00;
	char tm[2] = { 0x00, 0x00 };
	char start_pos[8];
	std::streampos spos;


	//まず識別子の取得
	fp.read(type, 3);
	fp.read(&length, 1);
	fp.read(&fps, 1);
	fp.read(tm, 2);
	fp.read(start_pos, 8);

	if (fp.bad()) {
		std::cout << "ImageSequence>" + this->filename + ":ヘッダの読み込み失敗" << std::endl;
		this->is_error = true;
		return;
	}

	//タイプの選別
	//もしもisfでないなら、分割画像として処理する。
	std::string type_s = type;
	if (type_s.compare("ISF") != 0) {
		//isfでない場合
		//フレーム数1枚の画像として読み込む
/*		std::cout << "ImageSequence>" + this->filename + ":分割画像と判定" << std::endl;
		size_t fileSize = static_cast<std::size_t>(fp.seekg(0, std::ios::end).tellg());
		fp.seekg(0, std::ios::beg);
		
		this->data_size = 0;
		try {
			this->data = new ImageSequence::Data[1];
			this->data[0].data = new char[fileSize];
			this->image = new sf::Image;
		}
		catch (std::bad_alloc) {
			std::cout << "ImageSequence>" + this->filename + ":メモリの確保失敗" << std::endl;
			this->is_error = true;
			return;
		}
		fp.read(this->data[0].data, fileSize);
		if (!this->image->loadFromMemory(this->data[0].data, fileSize)) {
			std::cout << "ImageSequence>" + this->filename + ":画像ファイル読み込み失敗" << std::endl;
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
		std::cout << "ImageSequence>" + this->filename + ":ロード完了" << std::endl;
		return;*/
	}

	//fps
	this->fps = static_cast<int>(fps);

	//総フレーム数
	this->data_size = 0;
	for (int i = 0; i < 2; i++) {
		unsigned int t = static_cast<unsigned int>(0x000000ff & tm[i]);
		t <<= 8 * i;
		this->data_size |= t;
	}

	out_frame = this->data_size;
	in_frame = 0;

	//スタートポジション
	unsigned long spos_l = 0;
	for (int i = 0; i < length; i++) {
		long t = static_cast<size_t>(0x000000ff & start_pos[i]);
		t <<= 8 * i;
		spos_l |= t;
	}
	spos = spos_l;

	//フレーム数のメモリ確保
	try {
		this->data.reserve(this->data_size);
	}
	catch (std::bad_alloc) {
		std::cout << "ImageSequence>" + this->filename + ":メモリの確保失敗" << std::endl;
		this->is_error = true;
		return;
	}

	{
		//size_strのスコープらしい。
		std::vector<char> size_str(length);

		for (int i = 0; i < this->data_size; i++) {
			//ファイル長を取得		
			fp.read(size_str.data(), size_str.size());
			if (fp.bad()) {
				std::cout << "ImageSequence>" + this->filename + "[" << i << "]:ファイル長の読み込み失敗" << std::endl;
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
	std::cout << "ImageSequence>" + this->filename + ":ヘッダ読み取り終了" << time_capture.asMicroseconds() << "usec.\t総フレーム数:" << this->data_size << "f" << std::endl;

	time_watch.restart();

	this->nonload_thread = this->data_size;

	//タイプによって分ける
	//***ALL_LOAD
	//先にdataにすべて代入する
	//そしてスレッドを分けて実行

	//***STREAMING
	//先にdataにすべて代入する
	//CHECK_LOADTIME_FRAMES読む
	//そしてスレッドを分けて実行

	//STREAMING_DELETE
	//

	//すべてdataに代入
	std::cout << "ImageSequence>" + this->filename + ":メモリに読み出し開始" << std::endl;
	for (std::size_t i = 0; i < this->data_size; i++, this->nonload_thread--) {
		if (i % 200 == 0 && i > 0) std::cout << "ImageSequence>" + this->filename + ":" << static_cast<int>(static_cast<float>(i) * 100.0f / static_cast<float>(this->data_size)) << "%完了" << std::endl;
		
		this->data.at(i)->load();

	}

	time_capture = time_watch.getElapsedTime();
	std::cout << "ImageSequence>" + this->filename + ":ファイルの読出しを完了\t" << time_capture.asMilliseconds() << "msec." << std::endl;
	std::cout << "ImageSequence>" + this->filename + ":フレームのロードを開始" << std::endl;

	fp.close();

	//ストリーミングする必要がない場合
	if (this->data_size <= ImageSequence::CHECK_LOADTIME_FRAMES) this->load_type = ImageSequence::ALL_LOAD;

	//##代入終了

	int load_start_frame = 0;
	int frame = static_cast<int>(this->data_size);
	if (this->load_type != ImageSequence::ALL_LOAD) {
		long all_time = 0;
		const int sampling_frame = ImageSequence::CHECK_LOADTIME_FRAMES;

		//まずsampling_frame分だけ振り分ける
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
		//全ロードが終わるまで待つ
		for (int i = 0; i < thvec.size(); i++) thvec[i]->join();

		thvec.clear();

		for (int i = 0; i < works_t.size(); i++) {
			for (int n = 0; n < works_t[i].size(); n++) {
				all_time += works_t[i][n]->getLoadTime();
			}
		}

		//ストリーミング時間の算出
		double ave_time = all_time / static_cast<double>(sampling_frame * ImageSequence::MAX_THREAD_NUM);
		std::cout << "ImageSequence>" + this->filename + ":読み込み平均時間" << ave_time << "ms" << std::endl;
		frame = static_cast<int>(this->data_size) - static_cast<int>(this->data_size * 1000.0f / fps / ave_time) + 10;
		if (frame <= 0)	std::cout << "ImageSequence>" + this->filename + ":初期ロードフレームなし" << std::endl;
		else std::cout << "ImageSequence>" + this->filename + ":初期ロードフレーム:" << frame << "f" << std::endl;

		load_start_frame = sampling_frame * ImageSequence::MAX_THREAD_NUM;
	}

	//オールロード
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

	//どこまで読み込み終わったかを計算
	this->loaded_frame = 0;
	while(this->loaded_frame < this->data_size){
		if (this->data[this->loaded_frame]->isLoaded()) loaded_frame++;
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}

		//ロード加算されたとき

		if (this->loaded_frame % 100 == 0 && this->loaded_frame > 0) {
			std::cout << "ImageSequence>" + this->filename + ":" << static_cast<int>(static_cast<float>(this->loaded_frame) * 100.0f / static_cast<float>(this->data_size)) << "%完了" << std::endl;
		}
		
		if (static_cast<int>(this->loaded_frame) >= frame && this->is_loaded == false) {
			std::cout << "ImageSequence>" + this->filename + "再生のためのロードが完了" << std::endl;
			this->is_loaded = true;
		}
	}
	std::cout << "ImageSequence>" + this->filename + ":全ロードが完了\t総ロード時間:" << time_watch.getElapsedTime().asMilliseconds() << "msec." << std::endl;
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

