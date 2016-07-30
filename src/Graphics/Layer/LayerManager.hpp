#pragma once

#ifndef JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP
#define JUBEAT_ONLINE_GRAPHICS_LAYER_LAYERMANAGER_HPP

#include <string>
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>


#define LAYERMANAGER_DEFAULT_WINDOW_WIDTH 960
#define LAYERMANAGER_DEFAULT_WINDOW_HEIGHT 540


namespace jubeat_online {
	namespace graphics {
		namespace layer {

			class LayerBase;

			/** ���C���[�̊Ǘ��N���X�B�ЂƂ̃E�B���h�E�ɂ��ЂƂ̃C���X�^���X�����������B
			 */
			class LayerManager {
			public:
				/** �f�t�H���g�R���X�g���N�^�B
				 */
				LayerManager();


				/** �����t���R���X�g���N�^�B
				 * @param window_title �E�B���h�E�̃^�C�g��
				 * @param width �E�B���h�E�̕�(px)
				 * @param height �E�B���h�E�̍���(px)
				 */
				LayerManager(
					const std::string & window_title,
					const sf::VideoMode & vmode,
					const sf::Uint32 style = sf::Style::Default
					);

				/** �f�N�X�X�g���N�^
				 */
				virtual ~LayerManager();

				void createWindow(void);
				void setScale(const double rate);

				typedef enum : unsigned char{
					FOREGROUND = 0,
					MAIN = 1,
					BACKGROUND = 2
				}LayerType;

				void addLayer(LayerBase * layer, const LayerType type, const unsigned char layernumber);

				void process(void);

			private:
				typedef struct {
					LayerBase * lb;
					LayerType lt;
				} LayerDetail;

				LayerManager(const LayerManager & cp);		//�R�s�[�R���X�g���N�^�̋֎~
				
				std::unique_ptr< std::list<LayerDetail>>	layer_list;		//���C���[�̃��X�g

				sf::VideoMode				vmode;			//��������E�B���h�E�̃T�C�Y�Ȃ�
				std::string					window_title;	//��������E�B���h�E�̃^�C�g��
				sf::Uint32					window_style;	//��������E�B���h�E�̃X�^�C��
				
				sf::RenderWindow			window;			//��������E�B���h�E�̎��́i�p���͂��Ȃ��B�O������G���Ăق����Ȃ�public������j

				double scale;


			};
		};
	};
};

#endif /* --- end of LayerManager --- */