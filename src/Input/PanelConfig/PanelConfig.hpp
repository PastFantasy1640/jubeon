#pragma once

#ifndef JUBEAT_ONLINE_PANEL_CONFIG_HPP_
#define JUBEAT_ONLINE_PANEL_CONFIG_HPP_

#include <string>
#include <SFML/Graphics.hpp>


namespace jubeat_online {
	namespace config {

		/// <summary>�p�l���֌W�̐ݒ���i�[����N���X</summary>
		class Panel {
		public:

			enum Result : int {
				SUCCESS = 0,
				INVALID_CONFIG_CONTROLER_ID = -1,
				INVALID_CONFIG_KEYBOARD_NUM = -2
			};

			/// <summary>�ݒ�t�@�C���̓ǂݏo���B0�ȊO�Ȃ�ǂݍ��݂͎��s���A�r���ō�Ƃ𒆒f���Ă��܂��B</summary>
			/// <param name='fpath'>�ǂ݂���INI�t�@�C���p�X</param>
			/// <returns>���s���ʁB0�Ȃ琳��A����ȊO�̓G���[�R�[�h��Ԃ�</returns>
			static int set(const std::string fpath);

			/// <summary>HID��ID���擾����B�L�[�{�[�h�̏ꍇ-1���AJoystick�̏ꍇ0�`7��Ԃ�</summary>
			/// <param name='p_index'>�p�l���ԍ�</param>
			/// <returns>ID</returns>
			static int getHidID(const unsigned int p_index);

			/// <summary>�L�[�R�[�h���擾����B</summary>
			/// <param name='p_index'>�p�l���ԍ�</param>
			/// <returns>sf::Keyboard::Key�^�̃L�[�R�[�h</returns>
			static sf::Keyboard::Key getKeyCode(const unsigned int p_index);

			/// <summary>�W���C�X�e�B�b�N�̃R�[�h���擾����B�L�[�{�[�h�̏ꍇ-1���AJoystick�̏ꍇ0�`7��Ԃ�</summary>
			/// <param name='p_index'>�p�l���ԍ�</param>
			/// <returns>�����^�R�[�h</returns>
			static int getJoystickCode(const unsigned int p_index);

		private:
			static int hid_id_[16];
			static sf::Keyboard::Key key_code_[16];
			static int joystick_code_[16];
		};
	}
}

#endif