//***************************************************
//*   ImageSequence Class Library					*
//*													*
//*		Programmed by �ق킢��						*
//***************************************************

//### ImageSequence�ɂ���
//#[1]�T�v
//#		ImageSequence�́Asfml�œ�����Đ��������Ƃ�����A
//#		������Ƃ����A�j���[�V�������Đ����������܂ŁA
//#		�l�X�ȃA�j���[�V�����̍Đ��ɑΉ����Ă��܂��B
//#		��p�t�@�C��isf�𐶐�����AImageSequenceEditor�ƂƂ��Ɏg�p���Ă��������B
//#
//#[2]���[�v�@�\
//#		ImageSequence�̓��[�v�@�\�ɑΉ����Ă��܂��B�f�t�H���g�ł���΍ŏ�����Ō�܂ŕύX���܂��B
//#		setInPoint�AsetOutPoint�֐��ŁA���[�v�̃C���|�C���g�A�A�E�g�|�C���g���w��ł��܂��B
//#		�����͍Đ����ɂ��ύX�ł��܂��B�������A���ꂼ��̎w��͓���I�ɊԂɍ����悤��
//#		�w�肵�Ȃ���΂Ȃ�܂���B
//#
//#[3]���[�h
//#		�A�ԉ摜�t�@�C���Ȃ̂ŁA�摜�t�@�C�����͑����Ȃ肪���ł��B
//#		ImageSequenceEditor�ɂāA��̃t�@�C���ɂȂ�Ƃ͂����A���F���ׂẴt���[�����܂Ƃ߂����̂�
//#		�߂��܂���B���̂܂ܓǂނƃ��[�h���Ԃ��c��オ��ꍇ������܂��B
//#		�����Ń��[�h�Ɋւ��Ă̓��[�h������܂��B
//#		�E�S���[�h
//#		�E�X�g���[�~���O
//#		�E�X�g���[�~���O�j��
//#		���ׂāA���[�f�B���O���ł����Ă��m���u���b�L���O�ł��B
//#		getLoadedFlag�֐��ɂĎ擾�ł���t���O��true�ɂȂ莟��Đ��ł��܂��B
//#
//#		���S���[�h(ImageSequence::LoadType::ALL_LOAD) ; �f�t�H���g
//#			�Ō�܂œǂݍ���ł���Đ����܂��B�X���b�h�������
//#			ImageSequence�N���X�w�b�_��MAX_THREAD_NUM��ύX���邩�A
//#			setThreadNum�ɂĕύX���Ă��������B���x���g�������A
//#			����ȂɃ��[�h���Ԃ�������Ȃ����́A�t�@�C���T�C�Y���㔼��
//#			�傫���Ȃ�Ȃǂ̖��ő��X�g���[�~���O�`���̎��ɓr���œ��悪�~�܂�Ȃǂ̖�肪
//#			����������̂͂���Ń��[�h���Ă��������B�������铮��Ȃǂ̓��[�h�ɕ��������Ԃ�
//#			������\��������̂ŁA���X�g���[�~���O�`���̎g�p�������߂��܂��B
//#
//#		���X�g���[�~���O(ImageSequence::LoadType::STREAMING)
//#			�ǂݍ��݂��Đ����ɂ��s���܂��B�ŏ���CHECK_LOADTIME_FRAMES���������[�h���A
//#			�������烍�[�h���ώ��Ԃ��Z�o���܂��B�������邽�߂ɕK�v�ȃo�b�t�@�����O��
//#			�ς񂾒i�K�ŁA�Đ����J�n�ł��܂��B1�t���[���̗e�ʂ��y��fps��30�Ƃ��A���ǒ�������Ȃǂ̏ꍇ��
//#			���̋@�\�͍ő�����������ƍl���Ă��܂��B�ǂ�ȏꍇ�ł�CHECK_LOADTIME_FRAMES����
//#			���[�h���Ԃ͕K�v�ł��B�������Ȃ�����ƁA�ŏ��̃��[�h���Ԃ�����A�ꍇ�ɂ���Ă͂ق�
//#			�m�[�E�F�C�g�ōĐ��ł��邱�Ƃ�����܂����A���x�������܂��B�r���ōĐ������[�h�ɒǂ���
//#			�~�܂�Ȃǂ̖�肪��������ꍇ�́A���̐������������Ă݂邱�Ƃ������߂��܂��B
//#			�܂��A�Z�o���ꂽ�o�b�t�@�����O�t���[��������CHECK_LOADTIME_FRAMES����
//#			�I�t�Z�b�g�Ƃ��ė]�T������̂ŁA�����������_�ł��ACHEKC_LOADTIME_FRAMES�͑傫������
//#			���삪���肷��ƍl�����܂��B
//#
//#		���X�g���[�~���O�j��(ImageSequence::LoadType::STREAMING_DELETE)
//#			�ǂݍ��݂Ɋւ��Ă̓o�b�N�O���E���h�ǂݍ��݂ƑS�������ł����A��x�Đ������t���[����
//#			�폜����Ă����܂��B�e�ʂ̌y�ʉ���}���Ẵ��[�h�ł��B���[�v�ɂ��Ή����Ă��܂��B
//#			���[�v���s����̈�Ɋւ��Ă̓f�[�^�̔j�����s���܂���B���[�v�͈͊O�ɂ����Ă�
//#			�Đ���폜���Ă����܂��B
//#
//#		�������摜
//#			�X�g���[�~���O�͂ł��Ȃ��B�����摜��ǂݍ��ށB
//#
//#		���[�h�̎��s�Ɋւ��ẮAgetLoadedFlag��true�ɂȂ邱�Ƃ͂Ȃ��AgetErrorFlag��true�ɂȂ��
//#		���[�h�̎��s�ƂȂ�܂��B
//#
//###


#pragma once
#ifndef WG_IMAGESEQUENCE_IMAGESEQUENCE_H_
#define WG_IMAGESEQUENCE_IMAGESEQUENCE_H_

//�X���b�h�����ϐ�
#include <atomic>

//sf::Texture
//sf::RenderTexture
//sf::Clock
#include <SFML/Graphics.hpp>

/// <summary>wg���C�u����</summary>
namespace jubeat_online {

	/// <summary>�C���[�W�V�[�P���X�B�ЂƂ̘A�ԓ���̃N���X�B</summary>
	class ImageSequence {
	public:
		/// <summary>���[�h�^�C�v</summary>
		enum LoadType : unsigned int {
			/// <summary>�S�Ẵt���[����ǂݍ���ł���Đ����܂�</summary>
			ALL_LOAD = 0,

			/// <summary>�X�g���[�~���O�ǂݍ���</summary>
			STREAMING = 1,

			/// <summary>�X�g���[�~���O</summary>
			STREAMING_DELETE = 2
		};

		/// <summary>�R���X�g���N�^</summary>
		ImageSequence();

		/// <summary>�R�s�[�R���X�g���N�^</summary>
		/// <param name='copy'>�R�s�[��</param>
		ImageSequence(const ImageSequence & copy);

		/// <summary>�f�R���X�g���N�^</summary>
		~ImageSequence();


		//### ���[�h ###

		/// <summary>���[�h����t�@�C�����w�肷��</summary>
		/// <param name='fpath'>���[�h����t�@�C���̃p�X</param>
		void setLoadFile(const std::string fpath);

		/// <summary>�t�@�C���̃��[�h</summary>
		/// <param name='type'>���[�h����</param>
		void LoadFile(const LoadType type);

		/// <summary>�t�@�C���̃��[�h</summary>
		/// <param name='type'>���[�h����</param>
		/// <param name='fpath'>���[�h����t�@�C���̃p�X</param>
		void LoadFile(const LoadType type, const std::string fpath);

		/// <summary>�摜�𕪊�����</summary>
		/// <remarks>ISF�t�@�C���ɂ͓K�p�ł��܂���</remarks>
		/// <param name='width'>��R�}�̉����T�C�Y(px)</param>
		/// <param name='height'>��R�}�̏c���T�C�Y(px)</param>
		/// <param name='div_xnum'>�������̕�����</param>
		/// <param name='div_ynum'>�c�����̕�����</param>
		/// <param name='frame'>���t���[����</param>
		void DivideImage(const unsigned int width, const unsigned int height, const unsigned int div_xnum, const unsigned int div_ynum, const unsigned int frame);



		/// <summary>���[�h�t���O��ǂ݂���</summary>
		/// <returns>���[�h������������</returns>
		bool getLoadedFlag(void) const;

		/// <summary>���[�h���̃G���[�t���O�擾</summary>
		/// <returns>�G���[�t���O</returns>
		bool getErrorFlag(void) const;


		//### �Đ� ###
		/// <summary>�Đ�</summary>
		/// <param name='speed'>�X�s�[�h</param>
		void play(const double speed = 1.0f);


		/// <summary>��~</summary>
		/// <remarks>�X�g���[�~���O�j�����[�h�̏ꍇ�́A���Đ��̕������폜����܂��B</remarks>
		void stop(void);

		/// <summary>���[�v�t���O��ݒ肷��</summary>
		/// <param name='flag'>���[�v�t���O</param>
		void setLoopFlag(const bool flag);

		/// <summary>���[�v�t���O���擾����</summary>
		/// <returns>���[�v�t���O</returns>
		bool getLoopFlag(void) const;

		/// <summary>�C���|�C���g��ݒ肷��</summary>
		/// <remarks>���[�v�Ŗ߂����ꍇ�̊J�n�_�B��������O����Đ����邱�Ƃ��\�ł��B</remarks>
		/// <param name="frame">�C���|�C���g</param>
		void setInPoint(const unsigned int frame);

		/// <summary>�A�E�g�|�C���g��ݒ肷��</summary>
		/// <remarks>�Đ����I�����ă��[�v����t���[���B</remarks>
		/// <param name="frame">�C���|�C���g</param>
		void setOutPoint(const unsigned int frame);

		//�`��
		/// <summary>�V�[�P���X�`�ʊ֐�</summary>
		/// <param name='screen_buffer'>�X�N���[���o�b�t�@</param>
		/// <param name='x'>�`�ʂ���x���W</param>
		/// <param name='y'>�`�ʂ���y���W</param>
		/// <param name='ex'>�g�嗦</param>
		void DrawSequence(sf::RenderTexture * screen_buffer, const float x, const float y, const float ex = 1.0f);

		/// <summary>�t���[���̕`��</summary>
		/// <param name='frame'>�t���[���ԍ�</param>
		/// <param name='screen_buffer'>�X�N���[���o�b�t�@</param>
		/// <param name='x'>�`�ʂ���x���W</param>
		/// <param name='y'>�`�ʂ���y���W</param>
		/// <param name='ex'>�g�嗦</param>
		void DrawFrame(const unsigned int frame, sf::RenderTexture * screen_buffer, const float x, const float y, const float ex = 1.0f);

		/// <summary>�t���[���̃e�N�X�`�����擾����</summary>
		/// <returns>sf::Texture���p������SequenceData��Ԃ��܂��B</returns>
		/// <param name='frame'>�擾����t���[���ԍ�</param>
		const sf::Texture * operator[] (unsigned int frame) const;

		//�A�N�Z�T
		/// <summary>�t�@�C���p�X���擾����</summary>
		/// <returns>�t�@�C���p�X</returns>
		std::string getFilePath(void) const;

		/// <summary>�ǂݍ��߂Ă��Ȃ��t���[�������擾����</summary>
		/// <returns>�ǂݍ��߂Ă��Ȃ��t���[����</returns>
		std::size_t getNonloadFrame(void) const;

		/// <summary>�S�t���[�������擾����</summary>
		/// <returns>�S�t���[����</returns>
		std::size_t getAllFrames(void) const;

		/// <summary>���ݍĐ����̃t���[�������擾����</summary>
		/// <returns>�Đ����̃t���[����</returns>
		size_t getPlayFrame(void) const;

		/// <summary>�Đ������擾����</summary>
		/// <returns>�v���C���t���O</returns>
		bool getIsPlaying(void) const;

		/// <summary>�Đ����̎��Ԃ��擾����</summary>
		/// <returns>�Đ����̎���</returns>
		sf::Time getPlayingTime(void) const;

		/// <summary>fps��ύX����</summary>
		/// <remarks>���[�h�^�C�v��ALL_LOAD�̎��A���Đ����łȂ��Ƃ��ɂ����ύX�ł��Ȃ��B</remarks>
		/// <param name='fps'>�ݒ肷��fps</param>
		void setFPS(unsigned int fps);

	private:
		enum {
			CHECK_LOADTIME_FRAMES = 10,
			MAX_THREAD_NUM = 2
		};

		//�t�@�C�����
		std::string filepath;

		//���[�h
		std::atomic<bool> is_loaded;
		std::atomic<bool> is_error;
		std::atomic<bool> is_thread_exit;
		std::atomic<std::size_t> nonload_thread;
		std::size_t loaded_frame;
		LoadType load_type;

		//�t�@�C������
		struct Data {
			std::atomic<bool> is_loaded;
			std::streampos pos;
			size_t size;
			char * data;
			sf::Texture * image;
			sf::Time load_time;
		};
		Data * data;
		std::size_t data_size;
		sf::Image * image;

		//�Đ��p�����[�^
		size_t play_frame;
		size_t start_frame;
		size_t in_frame;
		size_t in_frame_;
		size_t out_frame;
		unsigned int fps;
		double speed;

		bool is_play;
		sf::Clock timer;
		bool loop;

		void pBufTh(void);
		void loadTh(std::vector<Data *>data);
	};


}

#endif