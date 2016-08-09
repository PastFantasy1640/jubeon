//////////////////////////////////////////////////
// (c) 2016 white LayerManager.hpp
//////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_GRAPHICS_LAYERMANAGER_HPP
#define JUBEON_GRAPHICS_LAYERMANAGER_HPP

//////////////////////////////////////////////////
// LayerManager Class
//////////////////////////////////////////////////

//for string
#include <string>

//for LayerBase list.(vector)
#include <vector>

//for shared_ptr
#include <memory>

//for mapping layer to layer type
#include <map>

//for window modules
#include <SFML/Graphics.hpp>

//LayerManager manages the instances of LayerBase class.
#include "LayerBase.hpp"


//namespace is jubeon::graphics
namespace jubeon{
	namespace graphics {

		/** This class manages the instances of LayerBase class. Create a instance of LayerManager for each a window.
		 * @version 1.1
		 */
		class LayerManager {
		public:


			/** Constructor having arguments. Even if you call this function, the window do not create.
			 * @param window_title The title of the window. 
			 * @param vmode The window's settings. You can designate the window size and color bits.
			 * @param isVSync TRUE and the window waits for vertical synchronizing of the display.
			 * @param fpsLimit Limit the frame per second by sleeping thread. Default value is 0, and it means no limit.
			 * @param startWindowPosition The position of the window when starting up.
			 * @param style The window style. See at RenderWindow Reference of SFML.
			 */
			LayerManager(
				const std::string & window_title,
				const sf::VideoMode & vmode,
				const bool isVSync,
				const unsigned int fpsLimit = 0,
				const sf::Vector2i startWindowPosition = sf::Vector2i(0, 0),
				const sf::Uint32 style = sf::Style::Default
				);

			/** Destructor. When you release this instance, this function called and gets the window to close.
			 */
			virtual ~LayerManager();

			/** Definition of LayerType.
			 */
			typedef enum LayerType : unsigned char {
				SYSTEM = 0, //SYSTEM is only used in LayerManager. You cannot addLayer with this mode.
				FOREGROUND = 1, //FOREGROUND is top of the layers.
				MAIN = 2,	//MAIN is main layers, below top layers.
				BACKGROUND = 3	//BACKGROUND is bottom of the layers.
			}LayerType;

			/** Adds(Insert) layer.
			 * @param layer Shared pointer of the layer.
			 * @param type LayerType value. See at LayerType description.
			 * @param layernumber The Number to which Layer insert.
			 */
			void addLayer(std::shared_ptr<LayerBase> layer, const LayerType type, const unsigned char layernumber);

			/** Creating window.
			 */
			void createWindow(void);

			/** Get that is the window opening.
			 * @returns TRUE means yes.
			 */
			bool isWindowOpening(void) const;

			/** Close the window.
			 */
			void closeWindow(void);

			/** Get the window event.
			 * @param The reference of event valiable.
			 * @returns TRUE and there is an event.
			 */
			bool getWindowEvent(sf::Event & e);

			/** Drawing function. This is called by Scene::process function.
			 */
			void process(void);

		private:

			std::map<std::shared_ptr<LayerBase>, LayerType> layer_map;	//���C���[�}�b�v
			std::vector<std::shared_ptr<LayerBase>> layer_list;			//���C���[���X�g

			LayerManager(const LayerManager & cp);						//�R�s�[�R���X�g���N�^�̋֎~
			LayerManager();												//�f�t�H���g�R���X�g���N�^���֎~

			const sf::VideoMode					vmode;					//��������E�B���h�E�̃T�C�Y�Ȃ�
			const std::string					window_title;			//��������E�B���h�E�̃^�C�g��
			const sf::Uint32					window_style;			//��������E�B���h�E�̃X�^�C��
			const bool							isVSync;				//�����������Ƃ邩
			const unsigned int					fpsLimit;				//0�Ő����Ȃ�
			const sf::Vector2i					window_position;		//�E�B���h�E�𐶐�����|�W�V����


			std::shared_ptr<sf::RenderWindow>	window;					//��������E�B���h�E�̎��́i�p���͂��Ȃ��B�O������G���Ăق����Ȃ�public������j
			sf::RenderTexture					window_buffer;

			
			bool								is_open_window;

			const static sf::Vector2u			RENDER_TEXTURE_SIZE;

		};	//end of LayerManager
	};//end of graphics
};//end of jubeon

#endif /* --- end of JUBEON_GRAPHICS_LAYERMANAGER_HPP --- */