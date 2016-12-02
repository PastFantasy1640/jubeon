#pragma once
#include <SFML/System.hpp>
#include "Systems/picojson.hpp"
#include "ModelBase.hpp"

namespace jubeon {
	namespace models {

	class WindowConfig : public ModelBase {
	public:
		enum class LayoutType {
			VERTICAL,
			HORIZONTAL
		};
		WindowConfig()
			: layoutType(LayoutType::HORIZONTAL),
			size(sf::Vector2f(0, 0)),
			position(sf::Vector2f(0, 0)),
			vsyncEnabled(true) {};

		virtual bool Init(picojson::value) override;
		virtual picojson::value GetJsonValue() override;
		
		inline LayoutType getLayoutType() { return this->layoutType; };
		inline void setLayoutType(LayoutType type) { this->layoutType = type; };
		inline sf::Vector2f getSize() { return this->size; };
		inline void setSize(sf::Vector2f size) { this->size = size; };
		inline sf::Vector2f getPosition() { return this->position; };
		inline void setPosition(sf::Vector2f position) { this->position = position; };
		inline bool getVsyncEnabled() { return this->vsyncEnabled; };
		inline void setVsyncEnabled(bool b) { this->vsyncEnabled = b; };

	private:
		LayoutType layoutType;
		sf::Vector2f size;
		sf::Vector2f position;
		bool vsyncEnabled;
	};
}};