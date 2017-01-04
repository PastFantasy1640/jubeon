#pragma once

#ifndef JUBEON_GAME_COMBO_HPP
#define JUBEON_GAME_COMBO_HPP

namespace jubeon {
	namespace game {
		class Combo {

		private:

			unsigned int combo;

			unsigned int combo_baf;

		public:

			//�R���{��1���₷�B �߂�l:���₵����̃R���{��
			unsigned int increase(void);

			//�R���{���₷�i�O�ɂ���j
			void reset(void);

			//���݂̃R���{����Ԃ��B �߂�l:���݂̃R���{��
			unsigned int get(void) const;

			//���L���\�b�hclearUpdateCount���Ă΂�Ă���l�ɕύX�������������m����B �߂�l:[true]�ύX����B
			bool isUpdate(void) const;

			//�l�ύX�̌��m�t���O�𕚂���B
			void clearUpdateCount(void);

			Combo();
			~Combo();
		
		};

	}
}


#endif