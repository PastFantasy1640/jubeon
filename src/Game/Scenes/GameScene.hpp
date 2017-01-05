#pragma once

#ifndef JUBEON_GAME_SCENES_GAMESCENE_HPP
#define JUBEON_GAME_SCENES_GAMESCENE_HPP

#include "Systems/Scene.hpp"
#include <SFML/Graphics.hpp>

//for Notes
#include "Game/Sequence.hpp"
#include "Game/Music.hpp"
#include "Game/PlayRecord.hpp"

//for Layer
#include "Game/Layers/PushframeLayer.hpp"

#include <map>

#include "strbuf/strbuf.hpp"

#include "Input/Event.hpp"

//Player
#include "Game/Player.hpp"
namespace jubeon {
	namespace game {
		namespace scenes {

			class EventBase {
			private:
				std::shared_ptr<strbuf::InputStream<input::PanelInput>> pinput_que;
				strbuf::StreamBuffer<input::PanelInput> pinput_sb;

			public:
				EventBase();
				virtual ~EventBase() {}

				Music * music;

				void pollEvent(sf::Event e);

				strbuf::StreamBuffer<jubeon::input::PanelInput> * jubeon::game::scenes::EventBase::getPanelStreamBuf(void);


			};

			class GameScene : public jubeon::systems::Scene{
			public:
				virtual void init() override;
				
				std::shared_ptr<Music> music;
				Player player;
				Player player1;

				//temp
				std::unique_ptr<Marker> marker;

				EventBase gs_event;

				GameScene();

				//ÉåÉCÉÑÅ[

				std::array<PanelPosition, 4> panel_position;

				virtual int process(void) override;

			};
		};
	};
};

#endif