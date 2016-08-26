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
#include <unordered_map>

//for window modules
#include <SFML/Graphics.hpp>

//LayerManager manages the instances of LayerBase class.
#include "LayerBase.hpp"

//Polling Stream
#include "strbuf/strbuf.hpp"

//for thread safe
#include <mutex>


//namespace is jubeon::graphics
namespace jubeon{
	namespace graphics {

		/** This class manages the instances of LayerBase class. Create a instance of LayerManager for each a window.
		 * @version 1.1
		 */
		class LayerManager : private sf::RenderWindow{
		public:

            //Default Constructor
			LayerManager(const std::string & name);

            //Destructor
			virtual ~LayerManager();
            

			///////////////////////////////////////
			// Definition of LayerType.
			///////////////////////////////////////
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

			/** Close the window.
			 */
			void closeWindow(void);

			/** Drawing function. This is called by Scene::process function.
			 */
			void process(void);
			
			/** get event buffer instance
			 */
			strbuf::StreamBuffer<sf::Event> * getEventBuffer();
			
			/** get instance from name
			 */
			static LayerManager * getInstance(const std::string & name);
			
			static void processAll(void);

            /////////////////////////////////////////////
            // using
            /////////////////////////////////////////////
            using sf::RenderWindow::create;
            using sf::RenderWindow::isOpen;
            using sf::RenderWindow::getSettings;
            using sf::RenderWindow::getPosition;
            using sf::RenderWindow::setPosition;
            using sf::RenderWindow::getSize;
            using sf::RenderWindow::setSize;
            using sf::RenderWindow::setTitle;
            using sf::RenderWindow::setIcon;
            using sf::RenderWindow::setVisible;
            using sf::RenderWindow::setVerticalSyncEnabled;
            using sf::RenderWindow::setMouseCursorVisible;
            using sf::RenderWindow::setFramerateLimit;
            using sf::RenderWindow::setActive;
            using sf::RenderWindow::clear;
            using sf::RenderWindow::waitEvent;

		private:
            //Copy Constructor[forbidden]
            LayerManager(const LayerManager & copy);
            
            //Default Constructor[forbidden]
            LayerManager();

            //Layer Map
			std::map<std::shared_ptr<LayerBase>, LayerType> layer_map;
			
			//Layer List
			std::vector<std::shared_ptr<LayerBase>> layer_list;

            //RenderTexture
			sf::RenderTexture window_buffer;

            //mutex
            std::mutex mtx;
            
            //Event Buffer
            strbuf::StreamBuffer<sf::Event> event_buffer;

            //Size of render texture
			const static sf::Vector2u RENDER_TEXTURE_SIZE;
			
			//layermanager mapping
			static std::unordered_map<std::string, LayerManager *> layermanager_map;

		};	//end of LayerManager
	};//end of graphics
};//end of jubeon

#endif /* --- end of JUBEON_GRAPHICS_LAYERMANAGER_HPP --- */
