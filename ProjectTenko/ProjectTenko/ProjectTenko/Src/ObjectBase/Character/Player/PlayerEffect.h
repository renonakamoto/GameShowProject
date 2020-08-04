#ifndef PLAYEREFFECT_H_
#define PLAYEREFFECT_H_

#include <string>
#include <map>

/**
* @brief �v���C���[�̃G�t�F�N�g�^�C�v
*/
enum class PlayerEffectType : unsigned char
{
	PlyaerChase,			//! �`�F�C�X
	PlayerSneak,			//! �X�j�[�N

	MaxPlayerEffectType,	//! �G�t�F�N�g�̐�

	Non,					//! ����
};

/**
* @brief �v���C���[�̃G�t�F�N�g�N���X
*/
class PlayerEffect
{
	/**
	* @brief �G�t�F�N�g�f�[�^�\����
	*/
	struct PlayerEffectData
	{
		int  CurrentFrameNum;	//! ���݂̃G�t�F�N�g�̃t���[����
		int  CurrentNum;		//! ���݂̃G�t�F�N�g�̔ԍ�
		int  MaxNum;			//! �G�t�F�N�g�̐�
		int  ChangeFlameNum;	//! �؂�ւ��^�C�~���O
	};

public:
	/**
	* @brief �R���X�g���N�^
	*/
	PlayerEffect();

	/**
	* @brief �f�X�g���N�^
	*/
	~PlayerEffect();
	
	/**
	* @brief �G�t�F�N�g�̏�����
	* @param[in] type_ �G�t�F�N�g�^�C�v
	*/
	void InitEffect(PlayerEffectType type_);

	/**
	* @brief �G�t�F�N�g�X�V�֐�
	* @param[in] type_ �G�t�F�N�g�^�C�v
	*/
	void Update(PlayerEffectType type_);

	/**
	* @brief �G�t�F�N�g�`��֐�
	* @param[in] type_ �G�t�F�N�g�^�C�v
	*/
	void Draw(PlayerEffectType type_);

private:	
	//! �v���C���[�̃G�t�F�N�g
	PlayerEffectData m_PlayerEffect[static_cast<int>(PlayerEffectType::MaxPlayerEffectType)];
	
	//! �G�t�F�N�g�̃e�N�X�`���[�e�[�u��
	std::map<std::pair<PlayerEffectType, int>, std::string> m_TextureKeyTable;
};

#endif