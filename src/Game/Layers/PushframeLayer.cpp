#include "PushframeLayer.hpp"
#include "Storages/ResourceManager.hpp"

jubeon::game::layers::PushframeLayer::PushframeLayer(const std::shared_ptr<PanelPosition> & panelposition, const std::shared_ptr<Music> & music)
	: playrecord(), panelposition(panelposition), music(music)
{
}

jubeon::game::layers::PushframeLayer::PushframeLayer(const std::shared_ptr<PanelPosition> & panelposition, const std::shared_ptr<Music> & music, const std::shared_ptr<PlayRecord>& playrecord)
	: playrecord(playrecord), panelposition(panelposition), music(music)
{
}

void jubeon::game::layers::PushframeLayer::Init()
{

	//�p�l���g�̓ǂݍ���
	storages::Resource res = storages::Resource::setf("media/image/panel_shadow.png", storages::Resource::TEX);
	storages::Resource::setKey("panel_shadow", res);
	
	//��ʃv�b�V���͖���
	this->pushing = 0;

}

void jubeon::game::layers::PushframeLayer::Draw()
{
	//��ʃN���A
	this->clearBuffer();

	jMillisec mms = this->music->getPlayingCurrentTime();

	if (this->playrecord) {
		//�Đ��̎�

		//### �p�l���t���[���̕\�� ###
		//�ǂ̃p�l����������Ă������A�O�񒲍�����ms���L�^���Ă��� ->before_check_ms

		//�������Abcm�ȑO��PanelInput��ǉ�����ꍇ�́Abcm�����̎��Ԃ܂ň����߂��ċL�^����B
		//�܂��Abcm�̎��Ԃ̏ꏊ���ɓ񕪒T���ɂĒT���o��
		auto p = this->playrecord->getIteratorFromTime(*this->playrecord->getJudgedList(), this->before_check_ms);

		//�O�񒲍��ƍ��񒲍���ms�������ꍇ�̓X�L�b�v���Ă����B
		//�Ⴄ�ꍇ�̂ݍX�V
		if (this->before_check_ms != mms) {

			//����ȍ~����A���݂�ms�܂ł���`��͂��A�p�l���̉�����Ԃ��X�V����
			for (; p != this->playrecord->getJudgedList()->end(); p++) {
				//���̏������ƂɁA�����ɂ��g���̃O���f�[�V�����`�ʁA�������́A�z�[���h���ʂ̕`�ʂɎg���B
				if ((*p).ms > mms) break;	//�����V�����Ƃ���֍s�����ꍇ�A��͂͏I��

				if ((*p).t) {
					//����
					this->setPushing((*p).panel_no);
				}
				else {
					//������
					this->setReleasing((*p).panel_no);
				}

				//�������A�Ȃ������߂����肵�āA�`�ʂ���V���Ȃ���΂Ȃ�Ȃ��ꍇ�Abcm��0ms���w�肵�A�S�X�V���Ȃ��Ă͂Ȃ�Ȃ��B

			}

			this->before_check_ms = mms;
		}
	}

	//�ŏI�I��push����Ă�ꏊ�ɕ`��
	for (int i = 0; i < 16; i++) {
		if (this->isPushing(i)) {
			const sf::Texture & pframe = *storages::Resource::setk("panel_shadow").gett();
			sf::Sprite sp(pframe);
			const sf::IntRect & rect = this->panelposition->get(i);

			sp.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
			sp.setScale(PanelPosition::get_ex(pframe.getSize().x, rect.width), PanelPosition::get_ex(pframe.getSize().y, rect.height));
			this->draw(sp);
		}
	}
}

void jubeon::game::layers::PushframeLayer::Exit()
{

}
