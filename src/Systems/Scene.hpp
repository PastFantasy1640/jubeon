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
			static std::unique_ptr<Scene> next_scene;

			//���ł�static process���\�b�h�͓����ċ��邩
			//�X���b�h�A���Z�[�t
			static bool is_running;

		protected:
			//���̃V�[����ݒ肷��
			//�ݒ肵�����next_scene�ɂ͏��L�����������ߒ���
			static void setNextScene(std::unique_ptr<Scene> next_scene);

		public:
			//�R���X�g���N�^
			Scene() {};

			//�f�X�g���N�^
			virtual ~Scene() {};

			//process���z�֐��B���ꂼ��̃V�[���ŏ������L�q����
			//�v���Z�X���甲����Ƃ�����NextScene�֍s���̂ŁA���[�v�͎��O�Ő�������B
			//�߂�l��0�ȊO���ƃv���O�������I������B
			virtual int process(void) = 0;

			//���C���X���b�h�Ŏ��s�����process�֐��B
			//�ċA���Ă͂Ȃ�Ȃ����A�ł��Ȃ��݌v�ɂ��Ă���
			//���C���X���b�h�Ŏ��s����B�߂�l�͏I���X�e�[�^�X
			static int process(std::unique_ptr<Scene> first_scene);

		};	
	};
};

#endif

