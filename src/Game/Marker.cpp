#include "Marker.hpp"
#include <map>
#include "JudgeDefinition.hpp"

jubeat_online::game::Marker::MarkerTextures::MarkerTextures()
{
}



jubeat_online::game::Marker::Marker(const std::string meta_filepath)
	: meta_filepath(meta_filepath)
{
}

jubeat_online::game::Marker::~Marker()
{
}

bool jubeat_online::game::Marker::load(void)
{
	std::ifstream ifs(this->marker_name);
	if (ifs.fail())
	{
		std::cerr << "Failed to open marker setting file." << std::endl << "marker name : " << this->marker_name << std::endl << "filename : " << this->meta_filepath << std::endl;
		return false;
	}
	std::string json((std::istreambuf_iterator<char>(ifs)),std::istreambuf_iterator<char>());

	picojson::value v;
	std::string err;

	//�p�[�X
	picojson::parse(v, json.c_str(), json.c_str() + json.size(), &err);
	
	if (err.empty())
	{
		picojson::object& o = v.get<picojson::object>();

		//�}�[�J�[�̖��O���擾
		this->marker_name = o["name"].get<std::string>();

		//�e�N�X�`���Ǝ��ۂ̌��ʂ̑Ή��t��
		std::map<int, SPMarkerTextures> assign;
		
		picojson::object& e = o["assign"].get<picojson::object>();
				
		assign[e["appear"].get<int>()] = this->appear;
		assign[e["perfect"].get<int>()] = this->disappear[PERFECT];
		assign[e["great"].get<int>()] = this->disappear[GREAT];
		assign[e["good"].get<int>()] = this->disappear[GOOD];
		assign[e["early"].get<int>()] = this->disappear[EARLY];
		assign[e["late"].get<int>()] = this->disappear[LATE];
		assign[e["miss"].get<int>()] = this->disappear[MISS];


		//���\�[�X�̈ꗗ���擾
		picojson::array& resources = o["resources"].get<picojson::array>();
		
		for (auto p = resources.begin(); p != resources.end(); p++) {
			picojson::object& o2 = p->get<picojson::object>();

			int id = o2["id"].get<int>();
			int duration = o2["duration"].get<int>();

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
				rectangle.left = param[1].get<int>();
				rectangle.top = param[2].get<int>();
				rectangle.width = param[3].get<int>();
				rectangle.height = param[4].get<int>();
				
				std::unique_ptr<sf::Texture> tex(new sf::Texture());
				tex->loadFromFile(image_str, rectangle);

				//�V�����摜��ǉ�
				mktexes->push_back(std::move(tex));
			}

			//���蓖�ă}�b�v�����Ƃɉ摜��Ώۂ̃|�C���^�֊i�[
			assign[mktexes->getID()] = mktexes;

		}

		
	}
	else {
		std::cerr << "Illegal json format." << std::endl << "marker name : " << this->marker_name << std::endl << "filename : " << this->meta_filepath << std::endl;
		return false;
	}

	return true;
}

jubeat_online::game::Marker::MarkerTextures::MarkerTextures(int id, unsigned int duration)
	: std::vector<std::unique_ptr<sf::Texture>>(),
	id(id),
	duration(duration)
{

}

int jubeat_online::game::Marker::MarkerTextures::getID()
{
	return this->id;
}
