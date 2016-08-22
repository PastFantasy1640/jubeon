# jubeon2

## 環境構築

### 1.ライブラリを配置する
依存ライブラリはこんな感じだから、いい感じにlib以下に配置してね。SFMLは2.3.2で動作確認しています。
* [SFML](http://www.sfml-dev.org/files/SFML-2.3.2-windows-vc14-32-bit.zip)
* [Thor](http://www.bromeon.ch/libraries/thor/download/v2.0/thor-v2.0-msvc2015.7z)

`lib`ディレクトリ以下がこんな感じになればおっけーですよ。

```
├─SFML
│  │  license.txt
│  │  readme.txt
│  │  
│  ├─bin
...省略...
├─Thor
│  │  LicenseAurora.txt
│  │  LisenceThor.txt
│  │  ReadMe.txt
│  │  
│  ├─bin
```

### 2. VisualStudioのソリューションを作成する
[このへん](https://cmake.org/download/)から、CMakeを落として、インストールしてね。
cmake-guiを起動して、`where is the source code`にレポジトリのルートディレクトリを、
`Where to build the binaries`に`build`ディレクトリを指定して、

**Configure and Generate!!!**

そうすると、`./build/jubeon.sln`ができます。
開いてください

### 3. ソリューションの設定を変更
ソリューションエクスプローラーのソリューション名(jubeon)を右クリックして、「プロパティ」を開いてください。
「スタートアッププロジェクト」を選択する画面があるので、"jubeon"を選択してOKで閉じる感じで。
