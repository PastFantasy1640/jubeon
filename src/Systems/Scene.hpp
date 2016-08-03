#pragma once

#ifndef JUBEON_SYSTEMS_SCENE_HPP
#define JUBEON_SYSTEMS_SCENE_HPP

#include <memory>

namespace jubeon {
	namespace systems {

		//Scene�N���X
		class Scene {
		private:
			//���̃V�[��
			std::unique_ptr<Scene> next_scene;

		protected:
			virtual void setNextScene(std::unique_ptr<Scene> next_scene) final;

		public:
			virtual int process(void) = 0;

			static int process(std::unique_ptr<Scene> first_scene);

		};	
	};
};

#endif

