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

	//パース
	picojson::parse(v, json.c_str(), json.c_str() + json.size(), &err);
	
	if (err.empty())
	{
		picojson::object& o = v.get<picojson::object>();

		//マーカーの名前を取得
		this->marker_name = o["name"].get<std::string>();

		//テクスチャと実際の効果の対応付け
		std::map<int, SPMarkerTextures> assign;
		
		picojson::object& e = o["assign"].get<picojson::object>();
				
		assign[e["appear"].get<int>()] = this->appear;
		assign[e["perfect"].get<int>()] = this->disappear[PERFECT];
		assign[e["great"].get<int>()] = this->disappear[GREAT];
		assign[e["good"].get<int>()] = this->disappear[GOOD];
		assign[e["early"].get<int>()] = this->disappear[EARLY];
		assign[e["late"].get<int>()] = this->disappear[LATE];
		assign[e["miss"].get<int>()] = this->disappear[MISS];


		//リソースの一覧を取得
		picojson::array& resources = o["resources"].get<picojson::array>();
		
		for (auto p = resources.begin(); p != resources.end(); p++) {
			picojson::object& o2 = p->get<picojson::object>();

			int id = o2["id"].get<int>();
			int duration = o2["duration"].get<int>();

			//画像の本体
			picojson::array& images = o2["rectangle"].get<picojson::array>();

			SPMarkerTextures mktexes(new MarkerTextures(id,duration));

			for (auto p2 = images.begin(); p2 != images.end(); p2++) {
				
				//それぞれを読み出す
				
				picojson::array& param = p2->get<picojson::array>();

				if (param.size() != 5) {
					//要素数エラー
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

				//新しく画像を追加
				mktexes->push_back(std::move(tex));
			}

			//割り当てマップをもとに画像を対象のポインタへ格納
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
