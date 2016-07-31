#include "Marker.hpp"


jubeat_online::game::Marker::MarkerTextures::MarkerTextures()
{
}



jubeat_online::game::Marker::Marker(const std::string directory, const std::string meta_filepath)
	: directory(directory), meta_filepath(directory + "/" +  meta_filepath)
{
}

jubeat_online::game::Marker::~Marker()
{
}

bool jubeat_online::game::Marker::load(void)
{
	std::ifstream ifs(this->meta_filepath);
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
		std::array<int, 7> assign;
		
		picojson::object& e = o["assign"].get<picojson::object>();
				
		assign[NOJUDGE] = static_cast<int>(e["appear"].get<double>());
		assign[PERFECT] = static_cast<int>(e["perfect"].get<double>());
		assign[GREAT] = static_cast<int>(e["great"].get<double>());
		assign[GOOD] = static_cast<int>(e["good"].get<double>());
		assign[EARLY] = static_cast<int>(e["early"].get<double>());
		assign[LATE] = static_cast<int>(e["late"].get<double>());
		assign[MISS] = static_cast<int>(e["miss"].get<double>());



		//リソースの一覧を取得
		picojson::array& resources = o["resources"].get<picojson::array>();
		
		for (auto p = resources.begin(); p != resources.end(); p++) {
			picojson::object& o2 = p->get<picojson::object>();

			int id = static_cast<int>(o2["id"].get<double>());
			int duration = static_cast<int>(o2["duration"].get<double>());

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
				rectangle.left =	static_cast<int>(param[1].get<double>());
				rectangle.top =		static_cast<int>(param[2].get<double>());
				rectangle.width	=	static_cast<int>(param[3].get<double>());
				rectangle.height =	static_cast<int>(param[4].get<double>());
				
				std::unique_ptr<sf::Texture> tex(new sf::Texture());
				tex->loadFromFile(this->directory + "/" + image_str, rectangle);
				tex->setSmooth(true);

				//新しく画像を追加
				mktexes->push_back(std::move(tex));
			}

			//割り当てをもとに画像を対象のポインタへ格納
			for (size_t i = 0; i < 6;i++) {
				if (assign[i] == mktexes->getID()) {
					this->disappear[i] = mktexes;
				}
			}

			//appearだけは別で
			if (assign[6] == mktexes->getID()) this->appear = mktexes;
		}

		
	}
	else {
		std::cerr << "Illegal json format." << std::endl << "marker name : " << this->marker_name << std::endl << "filename : " << this->meta_filepath << std::endl;
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

const sf::Texture * jubeat_online::game::Marker::MarkerTextures::getTexture(int diff_ms) const
{
	if (diff_ms < 0) diff_ms = this->duration + diff_ms;
	if (diff_ms >= this->duration || diff_ms < 0) return nullptr;	//範囲外
	
	double pd = static_cast<double>(diff_ms) * this->size() / this->duration;
	std::size_t p = static_cast<size_t>(pd);

	std::cout << p << std::endl;
	if (p < 0 || p >= this->size()) 
		std::cout << "!!![" << p << "]!!!!!!!!!!";
	else return this->at(p).get();
	return false;
}
