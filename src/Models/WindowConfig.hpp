#pragma once
#include <SFML/System.hpp>
#include "Systems/picojson.hpp"
#include "ModelBase.hpp"

namespace jubeat_online {namespace models {
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
	private:
		LayoutType layoutType;
		sf::Vector2f size;
		sf::Vector2f position;
		bool vsyncEnabled;
	};
}};