//////////////////////////////////////////////////
// (c) 2016   white
//////////////////////////////////////////////////

#include "ModelBase.hpp"

#include <fstream>
#include <iterator>

#include "Systems/Logger.hpp"

jubeon::models::ModelBase::ModelBase(const std::string filename)
	: filename(filename)
{
}

jubeon::models::ModelBase::~ModelBase(void)
{
	this->release();
}

bool jubeon::models::ModelBase::load(void)
{
	std::ifstream ifs(this->getFilename());
	if (!ifs){
		systems::Logger::warning("Failed to load the json data. Cannot open the file. FILENAME:" + this->getFilename());
		return false;
	}

	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	std::string jsonstr(it, last);

	this->json.reset(new wlib::Json(jsonstr));
	if (this->json->isError()) {
		systems::Logger::warning("Failed to load the json data. Illegal json data. FILENAME:" + this->getFilename() + " DETAIL:" + this->json->getError());
		return false;
	}

	//successfully finished
	
	return this->set();
}

void jubeon::models::ModelBase::release(void)
{
	//Delete json data.
	if (this->json.get() != nullptr) delete this->json.release();
}

bool jubeon::models::ModelBase::isLoaded(void) const
{
	return (this->json.get() != nullptr);
}

std::string jubeon::models::ModelBase::getFilename(void) const
{
	return this->filename;
}

bool jubeon::models::ModelBase::set(void)
{

	//YOU CAN OVERRIDE THIS FUNCTION.

	return true;
}


