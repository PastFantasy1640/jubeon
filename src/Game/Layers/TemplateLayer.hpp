#pragma once

//auther white
//����m�F�ς�2016/08/04

//!!!!����!!!!!
//�t�@�C���𕡐����܂������H�܂���cpp�Ahpp���ɕ������āA���O��ς��Ă���ύX���Ă��������B

//1.�܂��ŏ��ɁAcpp�t�@�C����hpp�t�@�C���𕡐����Ė��O��ς��܂��傤�B
//�����K����HogehogeLayer.[c/h]pp�ł�

//�C���N���[�h�K�[�h��ݒ肵�Ă�������
#ifndef JUBEON_GAME_LAYERS_TEMPLATELAYER_HPP
#define JUBEON_GAME_LAYERS_TEMPLATELAYER_HPP

#include "../../Graphics/Layer/LayerBase.hpp"

namespace jubeon {
	namespace game {
		namespace layers {
			//�N���X����ύX���Ă��������B
			class TemplateLayer : public jubeon::graphics::LayerBase{
			public:
				//�R���X�g���N�^�ł��B�K�v�ɉ����Ĉ����t���R���X�g���N�^����`���Ă��������B
				TemplateLayer();
				virtual ~TemplateLayer();

				virtual void Init() override;						//�������֐�
				virtual void Draw() override;						//�`�ʊ֐�
				virtual void Exit() override;						//�I���֐�
			};


		};	//end of layers
	};	//end of game

};	//end of jubeon

#endif	//end of include gurd