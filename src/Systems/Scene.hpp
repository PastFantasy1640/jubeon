/*
 *	Scene�N���X�ɂ���			-�쐬��:white-
 *		�y�N���X�T�v�z
 *		Scene�N���X�͏�ʂ��Ǘ����܂��B����C�ӂ̎���t�ɂ����āA���݂���C���X�^���X�͕K��1�����ł��B
 *		�V������ʂ��쐬����ꍇ�́A����Scene�N���X���p�������N���X�Ɏ������܂��B�����K����xxxScene�N���X�ɂ��Ă��������B
 *		���ꂼ��̃T�u�N���X��process�֐����������[�v����������֐��ł��B��x�֐��𔲂����炻��Scene�C���X�^���X�͏��ł���̂ŁA�������[�v�͎��O�Ŏ������Ă��������B
 *		process�֐��̖߂�l�͏I���X�e�[�^�X�ł��B0�ȊO�A�������͎��Ɏ��s����Scene��nullptr�̏ꍇ�V�X�e�����I�����܂��B
 *
 *		�y�}���`�X���b�h�΍�z
 *		Scene�̊��N���X��static���\�b�h�́A�X���b�h�A���Z�[�t�ł��B����āA�S���\�b�h�̓��C���X���b�h�ȊO����Ă΂Ȃ��ł��������B
 *		���ꂼ��̃T�u�N���X�Ɋւ��ẮA�`�ʃX���b�h��IO�X���b�h����̃A�N�Z�X�����邩�Ǝv���܂��̂ŁA�X���b�h�Z�[�t�΍�����Ă��������B
 *
 *		�y�V�[���Ǘ����\�b�h�z		
 *		static��process�֐��͌����ă��C���X���b�h�ȊO�ŌĂ΂Ȃ��ł��������B�܂��A�o�������main�֐��̒��ŃR�[�����Ă��������B
 *
 *		�yprocess�֐����ł̓���̃��[���z
 *		���C���E�B���h�E�iLayerManager�j�̃C���X�^���X�ւ̃|�C���^��getMainWindow()�Ŏ擾�ł��܂��B
 *		�C�x���g�̊Ǘ���getMainWindow()->getWindowEvent(e)�Ŏ擾���e���ōs���Ă��������B
 *		�ڂ�����LayerManager���Q�Ƃ��Ă��������B
 *		���C���E�B���h�E�𐶐��i�T�u�E�B���h�E�͐�������Ă��Ȃ��ꍇ������j�������static��process�֐��̓R�[������܂��B
 *		���̂��߁A���C���E�B���h�E�̃C���X�^���X�́Aprocess�֐����s���ł͊m�ۂ��Ă��邱�Ƃ�O��Ƃ���������`���ėǂ��ł��B
 *		�V�������C���[�𐶐�����ꍇ�́A���C���[�̃C���X�^���X�Ǘ��ɒ��ӂ��Ă��������B
 *		�ڂ�����LayerManager���Q�Ƃ��Ă��������B�V�����������ꂽ�C���X�^���X��shared_ptr�ŋ��L����邽�߁A�V�[�����ڂ��������ł͍폜����܂���B
 *		addLayer����ꍇ�́AInit�֐��ɒ��ӂ��Ă��������B���[�h�Ɏ��Ԃ�������ꍇ�A�����X���b�h���u���b�L���O���܂��B
 *		�u���b�L���O�������Ȃ����́A�X���b�h��V�������ĂāAaddLayer��ʃX���b�h�Ŏ��s���Ă��������B
 *
 *		�y���̃V�[���ւ̃C���X�^���X�̎󂯓n���z
 *		���̃V�[���ւ̃C���X�^���X�̎󂯓n�����K�v�ȏꍇ�́A�V�������V�[���̃R���X�g���N�^�œn�����A���\�b�h���������ēn���Ă��������B
 *		process�֐��ɂ͈������������߁A�����ł̎󂯓n���͕s�\�ł��B
 **/


#pragma once

#ifndef JUBEON_SYSTEMS_SCENE_HPP
#define JUBEON_SYSTEMS_SCENE_HPP

#include <memory>

#include "Graphics/Layer/LayerManager.hpp"

namespace jubeon {

	namespace systems {

		//Scene�N���X
		//static���\�b�h�̓I�[�o�[���C�h�ł��Ȃ����AScene�N���X��static���\�b�h�̓I�[�o�[���C�h���Ă͂Ȃ�Ȃ����̂ł���B
		//Scene�N���X���p�������N���X���쐬���A���ꂼ��̃V�[���Ƃ���B
		class Scene {
		private:
			//���̃V�[��
			static std::shared_ptr<Scene> next_scene;

			//���݂̃V�[��
			static std::shared_ptr<Scene> current_scene;

			//���ł�static process���\�b�h�͓����ċ��邩
			//�X���b�h�A���Z�[�t
			static bool is_running;

			static bool is_scene_change;

			//���C���E�B���h�E
			static jubeon::graphics::LayerManager * main_window;

		protected:
			//���̃V�[����ݒ肷��
			//�ݒ肵�����next_scene�ɂ͏��L�����������ߒ���
			static void setNextScene(const std::shared_ptr<Scene> & next_scene);

			//���C���E�B���h�E�̃C���X�^���X���擾����
			//TO DO : �o�����const��t���������ǁA�ǂ��H
			static jubeon::graphics::LayerManager * getMainWindow();

		public:
			//�R���X�g���N�^
			Scene() {};

			//�f�X�g���N�^
			virtual ~Scene() {};

			//process���z�֐��B���ꂼ��̃V�[���ŏ������L�q����
			//�v���Z�X���甲����Ƃ�����NextScene�֍s���̂ŁA���[�v�͎��O�Ő�������B
			//�߂�l��0�ȊO���ƃv���O�������I������B
			virtual int process(void) = 0;

			virtual void init(void) = 0;

			//���C���X���b�h�Ŏ��s�����process�֐��B
			//�ċA���Ă͂Ȃ�Ȃ����A�ł��Ȃ��݌v�ɂ��Ă���
			//���C���X���b�h�Ŏ��s����B�߂�l�͏I���X�e�[�^�X
			static int process(jubeon::graphics::LayerManager * main_window, const std::shared_ptr<Scene> & first_scene);

		};	
	};
};

#endif

