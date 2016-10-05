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

## インスタンスの取得
ファイルパスをキーにしてリソースを取得します。と思ったけど、実際使ってみたら毎回毎回ファイルパス使うのは非常にダルいので、operator[]を実装して、連想配列っぽくアクセスできるように変更予定です。もしもリソースが読み込まれていなければ新規で読み込みます。サイズが大きい素材などは読み込みに時間がかかります。例えば、そういう素材を読み込むときは、ローディング中に新たにスレッドを作成し、getメソッドを呼び出してください。すでに読み込まれているときはすぐに終わりますし、新規に読み込む場合は時間が掛かるでしょう。

### getメソッド

```
const T & get(const std::string fpath);
```

※バージョンアップでこうなります多分。

```
shared_ptr<const T> ResourceManager::get(const std::string fpath);
shared_ptr<const T> ResourceManager::operator[](const std::string key);
```

## 解放
リソースを解放しようとします。ただし、リソースの所持権が他にある場合は解放できません。

### eraseFileメソッド
ファイル名を指定してリソースの解放をします。

### eraseメソッド
キーを指定してリソースの解放をします。

```
bool eraseFile(const std::string fpath);
bool erase(const std::string key);
```

## 完全解放
全てのリソースを解放します。

### clearメソッド
所有権の無いリソースを全て解放します。

```
void clear(void);
```

