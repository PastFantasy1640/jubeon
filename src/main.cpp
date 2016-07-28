#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <array>
#include <SFML/System/Clock.hpp>
#include "Theme/Drop.hpp"
#include "Graphics/Layer.hpp"
#include "Systems/Logger/Logger.hpp"
#include "Game/Layers/BackgroundLayer/BackgroundLayer.hpp"
#include "Game/Layers/FrameLayer/FrameLayer.hpp"
#include "Game/Layers/MusicInfoLayer/MusicInfoLayer.hpp"

using namespace jubeat_online::graphics::layer;
using namespace jubeat_online::systems;
using namespace jubeat_online::game::layers;
using namespace std;
int main() {
	Logger::information("jubeat online‚ª‹N“®‚µ‚Ü‚µ‚½");

	LayerManager layerManager(
		"test",
		sf::VideoMode(768, 1360),
		sf::Style::Default);
	layerManager.createWindow();
	layerManager.setScale(0.75);

	BackgroundLayer* bgLayer = new BackgroundLayer();
	FrameLayer* frameLayer = new FrameLayer();
	MusicInfoLayer* musicInfoLayer = new MusicInfoLayer();

	layerManager.addLayer(bgLayer, LayerManager::BACKGROUND, 0);
	layerManager.addLayer(frameLayer, LayerManager::FOREGROUND, 0);
	layerManager.addLayer(bgLayer, LayerManager::MAIN, 0);
	layerManager.process();

	delete bgLayer;
	delete frameLayer;
	delete musicInfoLayer;

	return 0;
}