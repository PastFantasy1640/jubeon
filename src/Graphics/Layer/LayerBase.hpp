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
				LayerBase(const LayerBase & copy);

				//�I���R�[�h
				int						exit_code;


			protected:
				//�R���X�g���N�^�A�f�X�g���N�^
				LayerBase();
				inline void clearBuffer(void) {
					this->clear(sf::Color(0, 0, 0, 0));
				}

			public:

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

			};
		}
	}
}


#endif