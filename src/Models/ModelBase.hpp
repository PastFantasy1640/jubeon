///////////////////////////////////////////
// ModelBase.hpp
//
// 2016 (c)   white  darao
///////////////////////////////////////////

//json file io

#pragma once

#ifndef JUBEON_MODELS_MODELBASE_HPP
#define JUBEON_MODELS_MODELBASE_HPP

#include <string>
#include <memory>

#include "wlib_Json.hpp"


namespace jubeon { 
	namespace models {
		class ModelBase {
		public:

			/** Constructor. This function do not load the file. Only to set the filename value.
			 *@param filename json file name.
			 */
			ModelBase(const std::string filename);
			
			/** Destructor. This function call release function.
			 *@see jubeon::models::ModelBase::release()
			 */
			virtual ~ModelBase(void);
			
			/** Load the file and create Json class.
			 *@returns true means the file loaded successfully. false means it occured some error while loading the file.
			 */
			bool load(void);

			/** Release the Json data.
			 */
			void release(void);

			/** Check if the load finished successfully.
			 *@returns true means yes.
			 */
			bool isLoaded(void) const;

			/** Get the json's filename.
			 *@returns filename
			 */
			std::string getFilename(void) const;

		protected:

			//Json data SHP
			std::unique_ptr<wlib::Json> json;


		private:

			std::string filename;

			//Default Constructor is private.
			ModelBase();
			
			
		};
	}
}

#endif