

/*
#include <unordered_map>
#include <memory>
//Singleton

namespace jubeon {
	namespace storages {

		template<class T>
		class ResourceManager {
		public:

		    /** SINGLETON. get the instance.
		     * @returns Instance of the ResourceManager<T>
		     * @notice You can assign T sf::Texture, sf::SoundBuffer, or sf::Font.
		     */
	//	    static ResourceManager * getInstance(void);
			
			/** Get the resource instance.
			 * @param fpath the file path of the resource.
			 * @returns constraint reference of the resource instance.
			 */
	//		const T & get(const std::string fpath);
			
			/** Get the resource instance from key.
			* @param key the key of filepath.
			* @returns constraint reference of the resource instance.
			*/
	//		std::shared_ptr<const T> operator[](const std::string key);


			/** Try to erase the resouce.
			 * @param fpath the file path of the resource which you want to erace.
			 * @returns true : release the resource successfully.
			 */
	//		bool eraseFile(const std::string fpath);
			
			/** Try to erase the resouce from key.
			* @param key the key of the file path of the resource which you want to erace.
			* @returns true : release the resource successfully.
			*/
	//		bool erase(const std::string key);

			/** Clear the all resource.
			 */
		//	void clear(void);
	//	
/*		private:
		    static std::unique_ptr<ResourceManager<T>> instance;
			std::unordered_map<std::string, T> data;
			std::unordered_map<std::string, std::string> file_key;

			/** Load Resource Key File.
			 */
	//		void loadResourceKeyFile(const std::string fpath);
	/*	};
	};
};
#endif
*/