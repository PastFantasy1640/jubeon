#pragma once
#include <SFML/System.hpp>
#include "Systems/picojson.hpp"
#include "ModelBase.hpp"

#include "Graphics/Layer/LayerManager.hpp"


namespace jubeon {
	namespace models {

	class WindowConfig : public ModelBase {
	public:

		WindowConfig(const std::string filename);

		//get methods
		sf::Vector2i getSize() const;
		sf::Vector2i getPosition() const;
		bool getVsyncEnabled() const;
		graphics::LayerManager::LayoutType getLayoutType() const;

	private:
		
		virtual bool set() override;
		WindowConfig();

		graphics::LayerManager::LayoutType layoutType;
		sf::Vector2i size;
		sf::Vector2i position;
		bool vsyncEnabled;
	};
}};