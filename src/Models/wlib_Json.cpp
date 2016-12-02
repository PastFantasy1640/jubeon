//////////////////////////////////////
// (c) 2016  white   wlib_Json
//////////////////////////////////////

#include "wlib_Json.hpp"




//////////////////////////////////////
// Constructors and Destructor
//////////////////////////////////////
wlib::Json::Json(const std::string json_str)
	: shp_err_str(new std::string()), shp_first_flag(new bool(true))
{
	//public constructor
	*this->shp_err_str = picojson::parse(this->json_value, json_str);
}

wlib::Json::Json(const picojson::value & v, const std::shared_ptr<std::string> & shp_err_str, const std::shared_ptr<bool> & shp_first_flag)
	: json_value(v), shp_err_str(shp_err_str), shp_first_flag(shp_first_flag)
{
	*shp_first_flag = false;
}

wlib::Json::Json(const Json & copy)
	: json_value(copy.json_value), shp_err_str(copy.shp_err_str), shp_first_flag(copy.shp_first_flag)
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
	if (*this->shp_first_flag) this->shp_err_str->clear();	//error clear;

	if (!this->isError()) {
		if (this->json_value.is<picojson::object>()) {
			picojson::object tobj = this->json_value.get<picojson::object>();
			if (tobj.count(key) > 0)	return Json(tobj[key], this->shp_err_str, this->shp_first_flag);
			else						{ *this->shp_err_str = "No key"; return Json(this->json_value, this->shp_err_str, this->shp_first_flag); }
		}
		else							{ *this->shp_err_str = "Not Object"; return Json(this->json_value, this->shp_err_str, this->shp_first_flag); }
	}

	//Error
	return *this;
}

wlib::Json wlib::Json::operator[](const std::size_t index)
{
	if (*this->shp_first_flag) this->shp_err_str->clear();	//error clear;

	if (!this->isError()) {
		if (this->json_value.is<picojson::array>()) {
			picojson::array tarray = this->json_value.get<picojson::array>();
			if (tarray.size() > index)	return Json(tarray.at(index), this->shp_err_str, this->shp_first_flag);
			else						{ *this->shp_err_str = "Index Out Of Bounds"; return Json(this->json_value, this->shp_err_str, this->shp_first_flag); }
		}
		else							{ *this->shp_err_str = "Not Array"; return Json(this->json_value, this->shp_err_str, this->shp_first_flag); }
	}

	//Error
	return *this;
}



/////////////////////////////////////////
// Value Accessor
/////////////////////////////////////////
template<typename T>
T wlib::Json::get()
{
	*this->shp_first_flag = true;

	if (!this->isError()) {
		if (this->json_value.is<T>()) {
			return this->json_value.get<T>();
		}
		*this->shp_err_str = "Mismatched Type.";
	}
	return T();
}

template double wlib::Json::get<double>();
template std::string wlib::Json::get<std::string>();


double wlib::Json::num()
{
	return this->get<double>();
}

std::string wlib::Json::str()
{
	return this->get<std::string>();
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
	return *this->shp_err_str;
}




