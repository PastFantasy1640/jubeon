//////////////////////////////////////
// (c) 2016  white   wlib_Json
//////////////////////////////////////

#include "wlib_Json.hpp"




//////////////////////////////////////
// Constructors and Destructor
//////////////////////////////////////
wlib::Json::Json(const std::string json_str, std::string * err_dump)
	: err_str("")
{
	this->err_str = picojson::parse(this->json_value, json_str);
	if (err_dump != nullptr) *err_dump = this->getError();
}

wlib::Json::Json(const picojson::value & v, const std::string err_str)
	: json_value(v), err_str(err_str)
{
}

wlib::Json::Json(const Json & copy)
	: json_value(copy.json_value), err_str(copy.err_str)
{
}

wlib::Json::~Json()
{
}

///////////////////////////////////////
// Object Accessor
///////////////////////////////////////
wlib::Json wlib::Json::operator[](const std::string key)
{
	if (!this->isError()) {
		if (this->json_value.is<picojson::object>()) {
			picojson::object tobj = this->json_value.get<picojson::object>();
			if (tobj.count(key) > 0)	return Json(tobj[key], "");
			else						return Json(this->json_value, "No Keys.");
		}
		else							return Json(this->json_value, "Not Object.");
	}

	//Error
	return *this;
}

wlib::Json wlib::Json::operator[](const std::size_t index)
{
	if (!this->isError()) {
		if (this->json_value.is<picojson::array>()) {
			picojson::array tarray = this->json_value.get<picojson::array>();
			if (tarray.size() > index)	return Json(tarray.at(index), "");
			else						return Json(this->json_value, "Index Out of Bounds.");
		}
		else							return Json(this->json_value, "Not Array.");
	}

	//Error
	return *this;
}



/////////////////////////////////////////
// Value Accessor
/////////////////////////////////////////
template<typename T>
T wlib::Json::get(std::string * err_dump)
{
	if (!this->isError()) {
		if (this->json_value.is<T>()) {
			return this->json_value.get<T>();
		}
		this->err_str = "Different Type.";
	}
	if (err_dump != nullptr) *err_dump = this->err_str;
	return T();
}

template double wlib::Json::get<double>(std::string * err_dump);
template std::string wlib::Json::get<std::string>(std::string * err_dump);


double wlib::Json::num(std::string * err_dump)
{
	return this->get<double>(err_dump);
}

std::string wlib::Json::str(std::string * err_dump)
{
	return this->get<std::string>(err_dump);
}


/////////////////////////////////////////
// Error
/////////////////////////////////////////
inline bool wlib::Json::isError(void) const
{
	return !this->getError().empty();
}

std::string wlib::Json::getError(void) const
{
	return this->err_str;
}




