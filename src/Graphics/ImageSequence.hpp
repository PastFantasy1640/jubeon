//***************************************************
//*   ImageSequence Class Library					*
//*													*
//*		Programmed by ほわいと						*
//***************************************************

//### ImageSequenceについて
//#[1]概要
//#		ImageSequenceは、sfmlで動画を再生したいときから、
//#		ちょっとしたアニメーションを再生したい時まで、
//#		様々なアニメーションの再生に対応しています。
//#		専用ファイルisfを生成する、ImageSequenceEditorとともに使用してください。
//#
//#[2]ループ機能
//#		ImageSequenceはループ機能に対応しています。デフォルトであれば最初から最後まで変更します。
//#		setInPoint、setOutPoint関数で、ループのインポイント、アウトポイントを指定できます。
//#		これらは再生中にも変更できます。ただし、それぞれの指定は動画的に間に合うように
//#		指定しなければなりません。
//#
//#[3]ロード
//#		連番画像ファイルなので、画像ファイル数は多くなりがちです。
//#		ImageSequenceEditorにて、一つのファイルになるとはいえ、所詮すべてのフレームをまとめたものに
//#		過ぎません。そのまま読むとロード時間が膨れ上がる場合があります。
//#		そこでロードに関してはモードがあります。
//#		・全ロード
//#		・ストリーミング
//#		・ストリーミング破棄
//#		すべて、ローディング中であってもノンブロッキングです。
//#		getLoadedFlag関数にて取得できるフラグがtrueになり次第再生できます。
//#
//#		○全ロード(ImageSequence::LoadType::ALL_LOAD) ; デフォルト
//#			最後まで読み込んでから再生します。スレッド数上限は
//#			ImageSequenceクラスヘッダのMAX_THREAD_NUMを変更するか、
//#			setThreadNumにて変更してください。何度も使う動画や、
//#			そんなにロード時間がかからないもの、ファイルサイズが後半に
//#			大きくなるなどの問題で他ストリーミング形式の時に途中で動画が止まるなどの問題が
//#			発生するものはこれでロードしてください。長すぎる動画などはロードに物凄い時間が
//#			かかる可能性があるので、他ストリーミング形式の使用をお勧めします。
//#
//#		○ストリーミング(ImageSequence::LoadType::STREAMING)
//#			読み込みを再生中にも行います。最初にCHECK_LOADTIME_FRAMES分だけロードし、
//#			そこからロード平均時間を算出します。完走するために必要なバッファリングが
//#			済んだ段階で、再生を開始できます。1フレームの容量が軽くfpsも30とか、けど長い動画などの場合に
//#			この機能は最大限発揮されると考えています。どんな場合でもCHECK_LOADTIME_FRAMES分の
//#			ロード時間は必要です。数を少なくすると、最初のロード時間が減り、場合によってはほぼ
//#			ノーウェイトで再生できることがありますが、精度が落ちます。途中で再生がロードに追いつき
//#			止まるなどの問題が発生する場合は、この数字を見直してみることをお勧めします。
//#			また、算出されたバッファリングフレーム数よりもCHECK_LOADTIME_FRAMES分は
//#			オフセットとして余裕があるので、そういった点でも、CHEKC_LOADTIME_FRAMESは大きい方が
//#			動作が安定すると考えられます。
//#
//#		○ストリーミング破棄(ImageSequence::LoadType::STREAMING_DELETE)
//#			読み込みに関してはバックグラウンド読み込みと全く同じですが、一度再生したフレームは
//#			削除されていきます。容量の軽量化を図ってのモードです。ループにも対応しています。
//#			ループが行われる領域に関してはデータの破棄を行いません。ループ範囲外においては
//#			再生後削除していきます。
//#
//#		○分割画像
//#			ストリーミングはできない。分割画像を読み込む。
//#
//#		ロードの失敗に関しては、getLoadedFlagがtrueになることはなく、getErrorFlagがtrueになれば
//#		ロードの失敗となります。
//#
//###


#pragma once
#ifndef WG_IMAGESEQUENCE_IMAGESEQUENCE_H_
#define WG_IMAGESEQUENCE_IMAGESEQUENCE_H_

//スレッド競合変数
#include <atomic>

//sf::Texture
//sf::RenderTexture
//sf::Clock
#include <SFML/Graphics.hpp>

/// <summary>wgライブラリ</summary>
namespace jubeat_online {

	/// <summary>イメージシーケンス。ひとつの連番動画のクラス。</summary>
	class ImageSequence {
	public:
		/// <summary>ロードタイプ</summary>
		enum LoadType : unsigned int {
			/// <summary>全てのフレームを読み込んでから再生します</summary>
			ALL_LOAD = 0,

			/// <summary>ストリーミング読み込み</summary>
			STREAMING = 1,

			/// <summary>ストリーミング</summary>
			STREAMING_DELETE = 2
		};

		/// <summary>コンストラクタ</summary>
		ImageSequence();

		/// <summary>コピーコンストラクタ</summary>
		/// <param name='copy'>コピー元</param>
		ImageSequence(const ImageSequence & copy);

		/// <summary>デコンストラクタ</summary>
		~ImageSequence();


		//### ロード ###

		/// <summary>ロードするファイルを指定する</summary>
		/// <param name='fpath'>ロードするファイルのパス</param>
		void setLoadFile(const std::string fpath);

		/// <summary>ファイルのロード</summary>
		/// <param name='type'>ロード方式</param>
		void LoadFile(const LoadType type);

		/// <summary>ファイルのロード</summary>
		/// <param name='type'>ロード方式</param>
		/// <param name='fpath'>ロードするファイルのパス</param>
		void LoadFile(const LoadType type, const std::string fpath);

		/// <summary>画像を分割する</summary>
		/// <remarks>ISFファイルには適用できません</remarks>
		/// <param name='width'>一コマの横幅サイズ(px)</param>
		/// <param name='height'>一コマの縦幅サイズ(px)</param>
		/// <param name='div_xnum'>横方向の分割数</param>
		/// <param name='div_ynum'>縦方向の分割数</param>
		/// <param name='frame'>総フレーム数</param>
		void DivideImage(const unsigned int width, const unsigned int height, const unsigned int div_xnum, const unsigned int div_ynum, const unsigned int frame);



		/// <summary>ロードフラグを読みだす</summary>
		/// <returns>ロードが完了したか</returns>
		bool getLoadedFlag(void) const;

		/// <summary>ロード時のエラーフラグ取得</summary>
		/// <returns>エラーフラグ</returns>
		bool getErrorFlag(void) const;


		//### 再生 ###
		/// <summary>再生</summary>
		/// <param name='speed'>スピード</param>
		void play(const double speed = 1.0f);


		/// <summary>停止</summary>
		/// <remarks>ストリーミング破棄モードの場合は、未再生の部分も削除されます。</remarks>
		void stop(void);

		/// <summary>ループフラグを設定する</summary>
		/// <param name='flag'>ループフラグ</param>
		void setLoopFlag(const bool flag);

		/// <summary>ループフラグを取得する</summary>
		/// <returns>ループフラグ</returns>
		bool getLoopFlag(void) const;

		/// <summary>インポイントを設定する</summary>
		/// <remarks>ループで戻った場合の開始点。これよりも前から再生することも可能です。</remarks>
		/// <param name="frame">インポイント</param>
		void setInPoint(const unsigned int frame);

		/// <summary>アウトポイントを設定する</summary>
		/// <remarks>再生を終了してループするフレーム。</remarks>
		/// <param name="frame">インポイント</param>
		void setOutPoint(const unsigned int frame);

		//描写
		/// <summary>シーケンス描写関数</summary>
		/// <param name='screen_buffer'>スクリーンバッファ</param>
		/// <param name='x'>描写するx座標</param>
		/// <param name='y'>描写するy座標</param>
		/// <param name='ex'>拡大率</param>
		void DrawSequence(sf::RenderTexture * screen_buffer, const float x, const float y, const float ex = 1.0f);

		/// <summary>フレームの描写</summary>
		/// <param name='frame'>フレーム番号</param>
		/// <param name='screen_buffer'>スクリーンバッファ</param>
		/// <param name='x'>描写するx座標</param>
		/// <param name='y'>描写するy座標</param>
		/// <param name='ex'>拡大率</param>
		void DrawFrame(const unsigned int frame, sf::RenderTexture * screen_buffer, const float x, const float y, const float ex = 1.0f);

		/// <summary>フレームのテクスチャを取得する</summary>
		/// <returns>sf::Textureを継承したSequenceDataを返します。</returns>
		/// <param name='frame'>取得するフレーム番号</param>
		const sf::Texture * operator[] (unsigned int frame) const;

		//アクセサ
		/// <summary>ファイルパスを取得する</summary>
		/// <returns>ファイルパス</returns>
		std::string getFilePath(void) const;

		/// <summary>読み込めていないフレーム数を取得する</summary>
		/// <returns>読み込めていないフレーム数</returns>
		std::size_t getNonloadFrame(void) const;

		/// <summary>全フレーム数を取得する</summary>
		/// <returns>全フレーム数</returns>
		std::size_t getAllFrames(void) const;

		/// <summary>現在再生中のフレーム数を取得する</summary>
		/// <returns>再生中のフレーム数</returns>
		size_t getPlayFrame(void) const;

		/// <summary>再生中か取得する</summary>
		/// <returns>プレイ中フラグ</returns>
		bool getIsPlaying(void) const;

		/// <summary>再生中の時間を取得する</summary>
		/// <returns>再生中の時間</returns>
		sf::Time getPlayingTime(void) const;

		/// <summary>fpsを変更する</summary>
		/// <remarks>ロードタイプがALL_LOADの時、かつ再生中でないときにしか変更できない。</remarks>
		/// <param name='fps'>設定するfps</param>
		void setFPS(unsigned int fps);

	private:
		enum {
			CHECK_LOADTIME_FRAMES = 10,
			MAX_THREAD_NUM = 2
		};

		//ファイル情報
		std::string filepath;

		//ロード
		std::atomic<bool> is_loaded;
		std::atomic<bool> is_error;
		std::atomic<bool> is_thread_exit;
		std::atomic<std::size_t> nonload_thread;
		std::size_t loaded_frame;
		LoadType load_type;

		//ファイル実体
		struct Data {
			std::atomic<bool> is_loaded;
			std::streampos pos;
			size_t size;
			char * data;
			sf::Texture * image;
			sf::Time load_time;
		};
		Data * data;
		std::size_t data_size;
		sf::Image * image;

		//再生パラメータ
		size_t play_frame;
		size_t start_frame;
		size_t in_frame;
		size_t in_frame_;
		size_t out_frame;
		unsigned int fps;
		double speed;

		bool is_play;
		sf::Clock timer;
		bool loop;

		void pBufTh(void);
		void loadTh(std::vector<Data *>data);
	};


}

#endif