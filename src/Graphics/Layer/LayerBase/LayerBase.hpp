#pragma once

#ifndef WG_SYSTEMS_LayerBase_HPP_
#define WG_SYSTEMS_LayerBase_HPP_

#include <SFML/Graphics.hpp>

namespace jubeat_online {
	namespace graphics {
		namespace layer {

			class LayerBase : public sf::RenderTexture{
			private:

				//�R�s�[�R���X�g���N�^�͋֎~
//				LayerBase(const LayerBase & copy);

				int						exit_code;
				//unsigned int			layer_no;						//0����Ԏ�O

			protected:
				//�R���X�g���N�^�A�f�X�g���N�^
				LayerBase();
				//sf::RenderTexture *		screen_buffer;

			public:

				/** LayerManager��Init�֐�������ɌĂяo���܂��Bscreen_buffer�̏���������x�����s���܂��B��x�ڈȍ~�Ăяo���Ă�������������܂���B
				 * @param width �X�N���[���̕�(px)
				 * @param height �X�N���[���̏c(px)
				 */
				//virtual void			createScreenBuffer(const unsigned int width, const unsigned int height) final;
				virtual void			Init() = 0;						//�������֐�
				virtual void			Draw() = 0;						//�`�ʊ֐�
				virtual void			Exit() = 0;						//�I���֐�

				virtual ~LayerBase();

				/** ���C���[���I�����܂��B0�ȊO�̃R�[�h��ݒ肷�邱�ƂŃ��C���[�̏I�������L���ɂ��܂��B
				 * @param code �I���R�[�h
				 */
				void setExitCode(const int code);

				/** �I���R�[�h���擾���܂��B�������擾�ł���̂̓C���X�^���X�����݂���Ԃ݂̂ł��B
				 * @returns �I���R�[�h
				 */
				unsigned int getExitCode(void) const;

				/** RenderTexture�̃X�v���C�g���擾���܂��BLayerManager�ɂ���Ď��s����܂��B
				 * @returns �X�N���[���o�b�t�@��Sprite
				 */
				//const sf::Texture * getScreenBufferTexture(void) const;


//				void _setScreenBuffer(sf::RenderTexture * rt);
//				void _setWindowTarget(sf::RenderWindow * wd);

//				unsigned int getLayerNumber(void) const;
//				void setLayerNumber(const unsigned int layer_no);
			};
		}
	}
}


#endif