#pragma once

#ifndef JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP
#define JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP

#include <string>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>


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

				/** �f�N�X�X�g���N�^
				 */
				virtual ~LayerManager();

				/** �E�B���h�E�𐶐����܂��B
				 */
				void createWindow(void);

				typedef enum : unsigned char{
					FOREGROUND = 0,
					MAIN = 1,
					BACKGROUND = 2
				}LayerType;

				void addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber);

				void run(void);

				bool isThreadRunning(void) const;

			private:
				void process(void);
				typedef struct {
					std::shared_ptr<LayerBase> lb;
					LayerType lt;
				} LayerDetail;

				LayerManager(const LayerManager & cp);		//�R�s�[�R���X�g���N�^�̋֎~
				LayerManager();								//�f�t�H���g�R���X�g���N�^���֎~
				
				std::shared_ptr< std::list<LayerDetail>>	layer_list;		//���C���[�̃��X�g

				sf::VideoMode				vmode;			//��������E�B���h�E�̃T�C�Y�Ȃ�
				std::string					window_title;	//��������E�B���h�E�̃^�C�g��
				sf::Uint32					window_style;	//��������E�B���h�E�̃X�^�C��
				bool						isVSync;		//�����������Ƃ邩
				unsigned int				fpsLimit;		//0�Ő����Ȃ�
				sf::Vector2i				window_position;//�E�B���h�E�𐶐�����|�W�V����


				sf::RenderWindow			window;			//��������E�B���h�E�̎��́i�p���͂��Ȃ��B�O������G���Ăق����Ȃ�public������j
				sf::RenderTexture			window_buffer;	//��ʒ����̂��߂̃��X�g�o�b�t�@

				std::shared_ptr<bool>		is_thread_running;

				const static sf::Vector2u RENDER_TEXTURE_SIZE;

			};
		};
	};
};

#endif /* --- end of LayerManager --- */