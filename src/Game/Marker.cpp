#include "Marker.hpp"
#include "../Systems/Logger.hpp"


//************************** MarkerTexture�֘A ******************************
//�R���X�g���N�^
jubeat_online::game::Marker::Marker(const std::string directory, const std::string meta_filepath)
	: directory(directory),
	meta_filepath(directory + "/" +  meta_filepath)
{
}

//�f�X�g���N�^
jubeat_online::game::Marker::~Marker()
{
}

//�ǂݍ���
bool jubeat_online::game::Marker::load(void)
{

	//�}�[�J�[�̃��[�h�J�n
	const std::string logstr = "[" + this->meta_filepath + "]";

	systems::Logger::information(logstr + "�}�[�J�[�̃��[�h���J�n���܂�");


	//�t�@�C���̓ǂݍ���
	std::ifstream ifs(this->meta_filepath);
	if (ifs.fail())
	{
		std::cerr << "Failed to open marker setting file." << std::endl << "marker name : " << this->marker_name << std::endl << "filename : " << this->meta_filepath << std::endl;
		return false;
	}
	std::string json((std::istreambuf_iterator<char>(ifs)),std::istreambuf_iterator<char>());


	systems::Logger::information(logstr + "json��������擾���܂���");

	picojson::value v;
	std::string err;

	//�p�[�X
	picojson::parse(v, json.c_str(), json.c_str() + json.size(), &err);
	systems::Logger::information(logstr + "json�̃p�[�X���������܂���");
	
	if (err.empty())
	{
		picojson::object& o = v.get<picojson::object>();

		//�}�[�J�[�̖��O���擾
		this->marker_name = o["name"].get<std::string>();
		systems::Logger::information(logstr + "�}�[�J�[��:" + this->marker_name);

		//�e�N�X�`���Ǝ��ۂ̌��ʂ̑Ή��t��
		std::array<int, 7> assign;
		
		picojson::object& e = o["assign"].get<picojson::object>();
				
		assign[NOJUDGE] = static_cast<int>(e["appear"].get<double>());
		assign[PERFECT] = static_cast<int>(e["perfect"].get<double>());
		assign[GREAT] = static_cast<int>(e["great"].get<double>());
		assign[GOOD] = static_cast<int>(e["good"].get<double>());
		assign[EARLY] = static_cast<int>(e["early"].get<double>());
		assign[LATE] = static_cast<int>(e["late"].get<double>());
		assign[MISS] = static_cast<int>(e["miss"].get<double>());


		systems::Logger::information(logstr + "���\�[�X�̎擾���J�n���܂�");

		//���\�[�X�̈ꗗ���擾
		picojson::array& resources = o["resources"].get<picojson::array>();
		
		for (auto p = resources.begin(); p != resources.end(); p++) {
			picojson::object& o2 = p->get<picojson::object>();

			int id = static_cast<int>(o2["id"].get<double>());
			int duration = static_cast<int>(o2["duration"].get<double>());


			systems::Logger::information(logstr + "���\�[�Xid[" + std::to_string(id)
				+ "]: D[" + std::to_string(duration) + "] �̓ǂݍ��݂��J�n���܂�");

			//�摜�̖{��
			picojson::array& images = o2["rectangle"].get<picojson::array>();

			SPMarkerTextures mktexes(new MarkerTextures(id,duration));

			for (auto p2 = images.begin(); p2 != images.end(); p2++) {

				//���ꂼ���ǂݏo��

				picojson::array& param = p2->get<picojson::array>();

				if (param.size() != 5) {
					//�v�f���G���[
					std::cerr << "Illegal rectangle elements." << std::endl << "marker name : " << this->marker_name << std::endl << "filename : " << this->meta_filepath << std::endl;
					return false;
				}

				std::string image_str = param[0].get<std::string>();
				sf::IntRect rectangle;
				rectangle.left = static_cast<int>(param[1].get<double>());
				rectangle.top = static_cast<int>(param[2].get<double>());
				rectangle.width = static_cast<int>(param[3].get<double>());
				rectangle.height = static_cast<int>(param[4].get<double>());

				sf::Clock ckt;
				ckt.restart();

				//�܂��摜��map�ɂ��邩�ǂ����T��
				if (this->images.find(image_str) == this->images.end()) {
					//����
					//���[�h���悤
					this->images[image_str].loadFromFile(this->directory + "/" + image_str);
				}
				
				//�V�����e�N�X�`�������
				std::unique_ptr<sf::Texture> tex(new sf::Texture());

				//�C���[�W����ǂݍ���
				tex->loadFromImage(this->images[image_str], rectangle);
				tex->setSmooth(true);


				systems::Logger::information(logstr + "FN[" + this->directory + image_str
					+ "] RECT[" + std::to_string(rectangle.left) + "," + std::to_string(rectangle.top) + "," + std::to_string(rectangle.width) + "," + std::to_string(rectangle.height)
					+ "] TIME[" + std::to_string(ckt.getElapsedTime().asMicroseconds()) + "microsec");

				//�V�����摜��ǉ�
				mktexes->push_back(std::move(tex));
			}

			//���蓖�Ă����Ƃɉ摜��Ώۂ̃|�C���^�֊i�[
			for (size_t i = 0; i < 6;i++) {
				if (assign[i] == mktexes->getID()) {
					this->disappear[i] = mktexes;
				}
			}

			//appear�����͕ʂ�
			if (assign[6] == mktexes->getID()) this->appear = mktexes;

			systems::Logger::information(logstr + "���\�[�Xid[" + std::to_string(id)
				+ "] �̓ǂݍ��݁A���蓖�Ă��������܂���");
		}

		systems::Logger::information(logstr + "�ǂݍ��݂��������܂���");
		
	}
	else {
		std::cerr << "Illegal json format." << std::endl << "error msg : " << err << std::endl << "marker name : " << this->marker_name << std::endl << "filename : " << this->meta_filepath << std::endl;
		systems::Logger::warning(logstr + "FAILED : json�t�H�[�}�b�g���s���ł� -> " + err);
		return false;
	}

	return true;
}

const sf::Texture * jubeat_online::game::Marker::getTexturePtr(const int diff_ms, const jubeat_online::game::Judge judge) const
{
	if (diff_ms < 0) {
		return this->appear->getTexture(diff_ms);
	}
	else{
		return this->disappear[(judge == NOJUDGE ? MISS : judge)]->getTexture(diff_ms);
	}
	return nullptr;
}

jubeat_online::game::Marker::MarkerTextures::MarkerTextures(const int id, const unsigned int duration)
	: std::vector<std::unique_ptr<sf::Texture>>(),
	id(id),
	duration(duration)
{

}

int jubeat_online::game::Marker::MarkerTextures::getID() const
{
	return this->id;
}

const sf::Texture * jubeat_online::game::Marker::MarkerTextures::getTexture(int diff_ms) const
{
	if (diff_ms < 0) diff_ms = this->duration + diff_ms;
	if (diff_ms >= this->duration || diff_ms < 0) return nullptr;	//�͈͊O
	
	double pd = static_cast<double>(diff_ms) * this->size() / this->duration;
	std::size_t p = static_cast<size_t>(pd);

	return this->at(p).get();
}
