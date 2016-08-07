#pragma once

#ifndef JUBEAT_ONLINE_PANEL_CONFIG_HPP_
#define JUBEAT_ONLINE_PANEL_CONFIG_HPP_

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ModelBase.hpp"

namespace jubeon {
	namespace models {

		/// <summary>�p�l���֌W�̐ݒ���i�[����N���X</summary>
		class PanelConfig : public ModelBase{
		public:

			enum Result : int {
				SUCCESS = 0,
				INVALID_CONFIG_CONTROLER_ID = -1,
				INVALID_CONFIG_KEYBOARD_NUM = -2
			};

			virtual bool Init(picojson::value val) override;
			virtual picojson::value GetJsonValue() override;

			/// <summary>HID��ID���擾����B�L�[�{�[�h�̏ꍇ-1���AJoystick�̏ꍇ0�`7��Ԃ�</summary>
			/// <param name='p_index'>�p�l���ԍ�</param>
			/// <returns>ID</returns>
			int getHidID(const unsigned int p_index) const;

			/// <summary>�L�[�R�[�h���擾����B</summary>
			/// <param name='p_index'>�p�l���ԍ�</param>
			/// <returns>sf::Keyboard::Key�^�̃L�[�R�[�h</returns>
			sf::Keyboard::Key getKeyCode(const unsigned int p_index) const;

			/// <summary>�W���C�X�e�B�b�N�̃R�[�h���擾����B�L�[�{�[�h�̏ꍇ-1���AJoystick�̏ꍇ0�`7��Ԃ�</summary>
			/// <param name='p_index'>�p�l���ԍ�</param>
			/// <returns>�����^�R�[�h</returns>
			int getJoystickCode(const unsigned int p_index) const;

			void setInstance(std::shared_ptr<PanelConfig> ptr);
			static PanelConfig * getInstance();

		private:
			
			static std::shared_ptr<PanelConfig> instance;

			int hid_id_[16];
			sf::Keyboard::Key key_code_[16];
			int joystick_code_[16];
		};
	}
}

#endif