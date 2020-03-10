#ifndef DIRECTGRAPHICS_H_
#define DIRECTGRAPHICS_H_

#include "../../Utility/SingletonTemplate.h"
#include <d3dx9.h>
#include <Windows.h>

/**
* @namespace MyDirectGraphics
* @brief DirectGraphics�ނ��܂Ƃ߂����O���
*/
namespace MyDirectGraphics
{
	/**
	* @brief �ȒP�ȃN���X�̐���
	* @details �ڍׂȃN���X�̐���
	*/
	class DirectGraphics
	{

		friend MySingletonTemplate::SingletonTemplate<DirectGraphics>;
	public:
		/**
		* @brief �O���t�B�b�N�G���W���̏�����
		* @return bool �����������ǂ���
		* @details true->���� | false->���s
		* @details �Q�[�����[�v�O�Ɉ�x�������s����
		*/
		bool Init(HWND windowHandle_, bool isFullScreen_);

		/**
		* @brief �`��J�n�֐�
		* @details �`��J�n���Ɉ�x�����Ăяo��
		*/
		void StartDraw();

		/**
		* @brief �`��I���֐�
		* @details �`��I�����Ɉ�x�����Ăяo��
		*/
		void EndDraw();

		/**
		* @brief �f�o�C�X��Ԃ��֐�
		* @return LPDIRECT3DDEVICE9 �O���t�B�b�N�f�o�C�X
		*/
		const LPDIRECT3DDEVICE9 GetD3DDevice() const { return m_pD3DDevice; }

		/**
		* @brief �v���[���g�p�����[�^�[��Ԃ��֐�
		* @return D3DPRESENT_PARAMETERS* �v���[���g�p�����[�^�[
		*/
		const D3DPRESENT_PARAMETERS* GetD3DPresentParam() const { return m_pD3DPresentParam; }



	private:
		/**
		* @brief �R���X�g���N�^�̊ȒP�Ȑ���
		*/
		DirectGraphics() :
			m_pD3DInterface(nullptr),
			m_pD3DDevice(nullptr),
			m_pD3DPresentParam(nullptr)
		{}

		/**
		* @brief �f�X�g���N�^�̊ȒP�Ȑ���
		*/
		//~DirectGraphics() {}

		/**
		* @brief �O���t�B�b�N�C���^�[�t�F�[�X�̍쐬
		* @return bool �����������ǂ���
		* @details true->���� | false->���s
		*/
		bool CreateGraphicsInterface();

		/**
		* @brief �O���t�B�b�N�f�o�C�X�̍쐬
		* @return bool �����������ǂ���
		* @details true->���� | false->���s
		*/
		bool CreateGraphicsDevice(HWND windowHandle_, bool isFullScreen_);

		/**
		* @brief �r���[�|�[�g�̐ݒ�
		* @return bool �����������ǂ���
		* @details true->���� | false->���s
		*/
		bool SetViewPort();

		//! �قɂ���Ŏg���ϐ�
		LPDIRECT3D9			   m_pD3DInterface;
		//! �قɂ���Ŏg���ϐ�
		LPDIRECT3DDEVICE9	   m_pD3DDevice;
		//! �قɂ���Ŏg���ϐ�
		D3DPRESENT_PARAMETERS* m_pD3DPresentParam;
	};
}

#endif