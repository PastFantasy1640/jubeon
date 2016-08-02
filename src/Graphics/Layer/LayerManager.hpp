#pragma once

#ifndef JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP
#define JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP

#include <string>
#include <list>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

//window�𐶐�����̂͐�΂Ƀ��C���X���b�h
//event���[�v�͎����Ȃ�
//event���[�v�̓��C���X���b�h

namespace jubeat_online {
	namespace graphics {
		namespace layer {

			class LayerBase;

			/** ���C���[�̊Ǘ��N���X�B�ЂƂ̃E�B���h�E�ɂ��ЂƂ̃C���X�^���X�����������B
			 */
			class LayerManager {
			public:


				/** �����t���R���X�g���N�^�B
				 * @param window_title �E�B���h�E�̃^�C�g��
				 * @param width �E�B���h�E�̕�(px)
				 * @param height �E�B���h�E�̍���(px)
				 */
				LayerManager(
					const std::string & window_title,
					const sf::VideoMode & vmode,
					const bool isVSync,
					const unsigned int fpsLimit = 0,
					const sf::Vector2i startWindowPosition = sf::Vector2i(0,0),
					const sf::Uint32 style = sf::Style::Default
					);

				/** �f�X�g���N�^
				 */
				virtual ~LayerManager();
				
				typedef enum : unsigned char{
					SYSTEM = 0,
					FOREGROUND = 1,
					MAIN = 2,
					BACKGROUND = 3
				}LayerType;

				void addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber);

				//�X���b�h�𗧂ĂċN��
				//�K�����C���X���b�h�ŌĂԂ��ƁB
				void run(void);

				//�E�B���h�E���J���Ă��邩
				bool isWindowOpening(void) const;

				//�E�B���h�E���I��������
				void closeWindow(void);


			private:

				void process(void);


				std::mutex layer_list_mtx;							//layer_list�ɑ΂��郍�b�N
				std::map<std::shared_ptr<LayerBase>, LayerType> layer_list;	//���C���[���X�g

				LayerManager(const LayerManager & cp);				//�R�s�[�R���X�g���N�^�̋֎~
				LayerManager();										//�f�t�H���g�R���X�g���N�^���֎~
				
				const sf::VideoMode					vmode;			//��������E�B���h�E�̃T�C�Y�Ȃ�
				const std::string					window_title;	//��������E�B���h�E�̃^�C�g��
				const sf::Uint32					window_style;	//��������E�B���h�E�̃X�^�C��
				const bool							isVSync;		//�����������Ƃ邩
				const unsigned int					fpsLimit;		//0�Ő����Ȃ�
				const sf::Vector2i					window_position;//�E�B���h�E�𐶐�����|�W�V����


				std::unique_ptr<sf::RenderWindow>	window;			//��������E�B���h�E�̎��́i�p���͂��Ȃ��B�O������G���Ăق����Ȃ�public������j
				std::unique_ptr<sf::RenderTexture>	window_buffer;	//��ʒ����̂��߂̃��X�g�o�b�t�@

				std::shared_ptr<bool>				is_thread_running;

				const static sf::Vector2u			RENDER_TEXTURE_SIZE;

			};
		};
	};
};

#endif /* --- end of LayerManager --- */