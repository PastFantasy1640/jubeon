//���C���[�̃w�b�_��ǂݍ���
#include "TemplateLayer.hpp"

//���O��Ԃ�ݒ肵�Ă��ǂ�
//using namespace std;
//using namespace jubeon::game;
//using namespace jubeon::systems;

//�R���X�g���N�^�̈�ł��B
//�K�X�����t������`���Ă��������B
jubeon::game::layers::TemplateLayer::TemplateLayer()
{
}

//�f�X�g���N�^�ł�
jubeon::game::layers::TemplateLayer::~TemplateLayer()
{
}

//������
void jubeon::game::layers::TemplateLayer::Init()
{
	//���\�[�X�̓ǂݍ��݂Ȃǂ��s���Ă��������B
	//this->hogehoge.loadFromFile("foobar.png");
}

//�`��
void jubeon::game::layers::TemplateLayer::Draw()
{
	//�܂��t���[�����N���A���܂�
	this->clearBuffer();	//�����ɃN���A����Ƃ���clearBuffer�A��������clear(sf::Color(0,0,0,0))
	//this->clear();		//���w�i�ɃN���A����Ƃ��͂�����B���̉��ɂ��郌�C���[�͌����Ȃ��Ȃ�܂��B

	//�`�ʂ��Ă��������B
	//this->draw(sf::Sprite(this->hogehoge));
	//...

	//���C���[���I�����������ꍇ��setExitCode���Ă�ł�������
	if (false) {
		//���̕���ɓ���͂����Ȃ�
		this->setExitCode(-1);	//0�ȊO�ŏI���ł��B1��SUCCESS���Ӗ����܂��B�G���[�̏ꍇ�͕��̒l��n�����Ƃ𐄏����܂��B
	}

	//�`�ʂ��I�����Ă�display�͌ĂԕK�v�͂���܂���B
}

//�I���������s���܂��B
void jubeon::game::layers::TemplateLayer::Exit()
{
	//�I���������s���܂��B
	//�`��X���b�h�Ŏ��s����邽�ߎ��Ԃɂ͒��ӂ��Ă��������i���P�̗]�n����H�j
}
