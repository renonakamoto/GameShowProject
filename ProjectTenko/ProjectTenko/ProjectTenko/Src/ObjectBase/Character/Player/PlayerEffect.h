#ifndef PLAYEREFFECT_H_
#define PLAYEREFFECT_H_

#include <string>
#include <map>

/**
* @brief プレイヤーのエフェクトタイプ
*/
enum class PlayerEffectType : unsigned char
{
	PlyaerChase,			//! チェイス
	PlayerSneak,			//! スニーク

	MaxPlayerEffectType,	//! エフェクトの数

	Non,					//! 無し
};

/**
* @brief プレイヤーのエフェクトクラス
*/
class PlayerEffect
{
	/**
	* @brief エフェクトデータ構造体
	*/
	struct PlayerEffectData
	{
		int  CurrentFrameNum;	//! 現在のエフェクトのフレーム数
		int  CurrentNum;		//! 現在のエフェクトの番号
		int  MaxNum;			//! エフェクトの数
		int  ChangeFlameNum;	//! 切り替えタイミング
	};

public:
	/**
	* @brief コンストラクタ
	*/
	PlayerEffect();

	/**
	* @brief デストラクタ
	*/
	~PlayerEffect();
	
	/**
	* @brief エフェクトの初期化
	* @param[in] type_ エフェクトタイプ
	*/
	void InitEffect(PlayerEffectType type_);

	/**
	* @brief エフェクト更新関数
	* @param[in] type_ エフェクトタイプ
	*/
	void Update(PlayerEffectType type_);

	/**
	* @brief エフェクト描画関数
	* @param[in] type_ エフェクトタイプ
	*/
	void Draw(PlayerEffectType type_);

private:	
	//! プレイヤーのエフェクト
	PlayerEffectData m_PlayerEffect[static_cast<int>(PlayerEffectType::MaxPlayerEffectType)];
	
	//! エフェクトのテクスチャーテーブル
	std::map<std::pair<PlayerEffectType, int>, std::string> m_TextureKeyTable;
};

#endif