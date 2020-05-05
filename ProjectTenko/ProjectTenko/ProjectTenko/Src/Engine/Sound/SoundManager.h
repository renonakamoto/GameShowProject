#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <dsound.h>
#include <unordered_map>
#include <string>

class SoundManager
{
public:
	/**
	* @brief サウンド初期化関数
	* DirectSoundを使用可能にするため初期化を行います
	* @return 成功の場合はtrue、失敗した場合はfalse
	*/
	bool Init(HWND hw_);

	/**
	* @biref サウンド開放関数
	* 読み込んだデータとDirectSoundの解放を行います
	*/
	void Release();

	/**
	* @brief waveデータの読み込み関数
	* 指定したパスのwaveデータをセカンダリ・バッファに読み込みます
	* @return 成功した場合はtrue、そうでないならfalse
	* @param[in] file_name 読み込むパスを含むファイル名
	* @param[in] key_name 読み込むデータを管理するキー
	*/
	bool LoadSound(std::string filename_, std::string keyname_);

	/**
	* @brief サウンド再生関数
	* 指定したセカンダリ・バッファのサウンドを再生します
	* @param[in] key_ 再生したいサウンドのキー
	*/
	void Play(std::string key_);

	/**
	* @brief サウンド停止関数
	* 指定したセカンダリ・バッファのサウンドを停止します
	* @param[in] key_ 停止したいサウンドのキー
	*/
	void Stop(std::string key_);

private:
	/**
	* @biref コンストラクタ
	*/
	SoundManager() : m_Interface(nullptr) { }

	/**
	* @biref デストラクタ
	*/
	~SoundManager() { }

	/**
	* @biref キーチェック関数
	* 引数のキーが既に登録されているか確認する関数です
	* @return 登録済みの場合はtrue、未登録はfalse
	* @param[in] key_ 確認するキー
	*/
	bool HasKey(std::string key_);

private:
	LPDIRECTSOUND8 m_Interface;
	std::unordered_map<std::string, LPDIRECTSOUNDBUFFER8> m_SoundData;
};

#endif // !SOUNDMANAGER_H_
