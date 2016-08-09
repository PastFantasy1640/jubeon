#pragma once

#ifndef JUBEON_GRAPHICS_LAYERBASE_HPP
#define JUBEON_GRAPHICS_LAYERBASE_HPP

#include <SFML/Graphics.hpp>
#include <atomic>

namespace jubeon {
	namespace graphics {

		class LayerBase : public sf::RenderTexture {
		private:

			//�R�s�[�R���X�g���N�^�͋֎~
			LayerBase(const LayerBase & copy);

			//�I���R�[�h
			std::atomic<int>		exit_code;

			bool					is_create_buffer;

		protected:
			//�R���X�g���N�^�A�f�X�g���N�^
			LayerBase();

			//���ߏ����������ăo�b�t�@���N���A
			inline void clearBuffer(void) {
				this->clear(sf::Color(0, 0, 0, 0));
			}
			
			sf::Sprite sp;

		public:

			virtual void			Init() = 0;						//�������֐�
			virtual void			Draw() = 0;						//�`�ʊ֐�
			virtual void			Exit() = 0;						//�I���֐�

			virtual ~LayerBase();

			void prepareBuffer(const sf::Vector2u size);

			/** �I���R�[�h���擾���܂��B�������擾�ł���̂̓C���X�^���X�����݂���Ԃ݂̂ł��B
			 * @returns �I���R�[�h
			 */
			unsigned int getExitCode(void) const;

			/** ���C���[���I�����܂��B0�ȊO�̃R�[�h��ݒ肷�邱�ƂŃ��C���[�̏I�������L���ɂ��܂��B
			* @param code �I���R�[�h
			*/
			void setExitCode(const int code);

			/** �X�v���C�g���擾
			 */
			const sf::Sprite & getSprite(void);


		};	//end of LayerBase

	};//end of graphics
};//end of jubeon


#endif	// end of 