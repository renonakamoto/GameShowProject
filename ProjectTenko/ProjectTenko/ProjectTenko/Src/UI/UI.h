#ifndef UI_H_
#define UI_H_

#include <string>
#include <d3dx9.h>

/**
* @brief UI�̊��N���X
*/
class UI
{
public:
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~UI(){}

	/**
	* @brief �X�V�֐�
	*/
	virtual void Update() = 0;

	/**
	* @brief �`��
	*/
	virtual void Draw() = 0;

protected:
	/**
	* @brief UI�p�����[�^�\����
	*/
	struct UI_PARAMETER
	{
		/**
		* @brief �R���X�g���N�^
		*/
		UI_PARAMETER():
			m_Pos(D3DXVECTOR2(0.0f,0.0f)),
			m_SpriteWidth(0.0f),
			m_SpriteHeight(0.0f),
			m_TexturHandleKey("")
		{}

		/**
		* @brief �R���X�g���N�^
		*/
		UI_PARAMETER(D3DXVECTOR2 pos_, float spriteWidth_, float spriteHeight, std::string texHandleKey):
			m_Pos(pos_),
			m_SpriteWidth(spriteWidth_),
			m_SpriteHeight(spriteHeight),
			m_TexturHandleKey(texHandleKey)
		{}

		D3DXVECTOR2 m_Pos;				//! ������W
		float m_SpriteWidth;			//! ����
		float m_SpriteHeight;			//! �c��
		std::string m_TexturHandleKey;	//! �e�N�X�`���L�[
	};
	
};

#endif