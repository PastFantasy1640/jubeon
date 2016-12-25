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

//Player
#include "Game/Player.hpp"
namespace jubeon {
	namespace game {
		namespace scenes {
			class GameScene : public jubeon::systems::Scene{
			public:
				virtual void init() override;
				
				std::shared_ptr<Sequence> sequence;
				std::shared_ptr<Music> music;
				Player player;



				//ÉåÉCÉÑÅ[
				std::shared_ptr<layers::PushframeLayer> push_frame_layer;


				virtual int process(void) override;

				strbuf::StreamBuffer<input::PanelInput> * getPanelStreamBuf(void);

				void EventToPanel(sf::Event e);

			private:
				strbuf::InputStream<input::PanelInput> pinput_que;
				strbuf::StreamBuffer<input::PanelInput> pinput_sb;

			};
		};
	};
};

#endif