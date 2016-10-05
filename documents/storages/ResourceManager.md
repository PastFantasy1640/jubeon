@Auther ほわいと

@Version 1.0

# ResourceManagerについて
sf::Texture、sf::SoundBuffer、sf::Fontに対応しています。リソースの無駄な多重読み込みを防ぎます。ゲーム中で使用するファイルは全てResourceManagerを通してください。

## スレッドセーフについて
現在はまだスレッドアンセーフです。近々対策します。

# 開発メモ
SharedPointerにしたらどう？getメソッドとか。で、erase時にcountが2以上なら、まだどこかが持ってるということになるので消せない、みたいな。

# 使い方
シングルトン設計を採用しています。そのため、使用するときは

```
ResourceManager::getInstance()::hogehoge
```

と続けてください。


			
			/** Get the resource instance.
			 * @param fpath the file path of the resource.
			 * @returns constraint reference of the resource instance.
			 */
			const T & get(const std::string fpath);
			
			/** Erase the resouce.
			 * @param fpath the file path of the resource which you want to erace.
			 */
			void erase(const std::string fpath);
			
			/** Clear the all resource.
			 */
			void clear(void);
		
		private:

		    static std::unique_ptr<ResourceManager<T>> instance;
			std::unordered_map<std::string, T> data;
		};
