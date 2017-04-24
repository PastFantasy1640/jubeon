#pragma once

#ifndef JUBEON_GAME_PANELPOSITION_HPP
#define JUBEON_GAME_PANELPOSITION_HPP

#include "Models/ModelBase.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#include <exception>

namespace jubeon {
	namespace game {
		
		class OutOfRangePanelNumberException : public std::out_of_range {
		public:
			OutOfRangePanelNumberException(const int number) throw () : std::out_of_range("Panel Number is Out of range. Number is " + std::to_string(number) + ".") {}
		};

		class PanelPositionNotInitializedException : public std::out_of_range {
		public:
			PanelPositionNotInitializedException() throw () : std::out_of_range("0 Panel Number is not existing.") {}
		};

		class PanelPosition : public jubeon::models::ModelBase, protected std::vector<sf::IntRect>{
		public:

			/** json�t�@�C���ǂݍ��݃R���X�g���N�^
			 * json�t�@�C������p�l���|�W�V�������w�肵�܂��B
			 * ��������͂���肭�s���Ȃ������ꍇ�A�f�t�H���g�̔z�u��ێ����܂��B
			 * @param json_file json�t�@�C���̃t�@�C�������w�肵�܂��B
			 */
			PanelPosition(const std::string json_file);
			
			/** �R�s�[�R���X�g���N�^
			 * �R�s�[�ɂ��R���X�g���N�^
			 * @param copy �R�s�[���̃C���X�^���X
			 */
			PanelPosition(const PanelPosition & copy);

			/** �f�R���X�g���N�^
			 */
			~PanelPosition();

			/** ModelBase�̃I�[�o�[���C�h�֐�
			 */
			virtual bool set() override;

			using std::vector<sf::IntRect>::at;
			using std::vector<sf::IntRect>::operator[];
			using std::vector<sf::IntRect>::size;

			/** PanelPosition::getBoundingBox�֐�
			 * �S�̂̍�����W�ƍ�������Ԃ��܂��B
			 * @returns sf::IntRect�^�B������W�ƍ��������������R�s�[��Ԃ��܂��B
			 */
			sf::IntRect getBoundingBox(void) const;



			//void set(const std::array<sf::IntRect, 16> & value);

			//static float get_ex(int origin, int to);

			

			//const sf::IntRect & get(unsigned char panel_no) const;


		private:
			PanelPosition();

			sf::IntRect bounding_box;
						
		};
	}
}

#endif