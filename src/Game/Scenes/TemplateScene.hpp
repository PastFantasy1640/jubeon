#pragma once

//�C���N���[�h�K�[�h�����܂��傤
#ifndef JUBEON_GAME_SCENES_TEMPLATESCENE_HPP
#define JUBEON_GAME_SCENES_TEMPLATESCENE_HPP

#include "../../Systems/Scene.hpp"

namespace jubeon {
	namespace game {
		namespace scenes {
			class TemplateScene : public jubeon::systems::Scene {
			public:
				//�R���X�g���N�^
				//�K�X�����t������`���邱��
				TemplateScene();

				//�f�X�g���N�^
				virtual ~TemplateScene();

				//�v���Z�X�֐�
				//�Ă΂��֐��B
				virtual int process(void) override;

				//�̂���K�X�����o���`���Ă��������B
				//������Layer����̃A�N�Z�X������ꍇ�̓X���b�h�Z�[�t�ɋC�����Ă��������B
			};
		};
	};
}; //end of jubeon

#endif //end of include guard