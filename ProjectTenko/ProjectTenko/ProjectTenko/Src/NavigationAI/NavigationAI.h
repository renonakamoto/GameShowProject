#ifndef NAVIGATIONAI_H_
#define NAVIGATIONAI_H_

#include "..//Utility/Singleton.h"
#include "Node.h"
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <d3dx9.h>

struct NavData
{
	std::vector<D3DXVECTOR3> Route;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Goal;
};

class Navigator : public Singleton<Navigator>
{
public:

	friend Singleton<Navigator>;

	/**
	* @biref �G�l�~�[�̏��񃋁[�g�擾�֐�
	* �G�l�~�[�Ɏ��g�̏��񃋁[�g�������܂�
	* @return ���[�g��^����ꂽ��true�A���[�g�񋟂Ɏ��s������false
	* @param[in] name_	�G�l�~�[�̖��O
	* @param[out] route_ �G�l�~�[�̏��񃋁[�g�i�[�p�R���e�i
	*/
	bool GetEnemyRoute(std::string name_, std::vector<D3DXVECTOR3>& route_);

	/**
	* @biref �}�b�v�̈ړ��\���̏���^���܂�
	* @return ����^����ꂽ��true�A���s������false
	* @param[in] data_ �n�_�A�I�_�A�A�Ҍo�H�i�[�p�R���e�i��������NavData�^�\����
	*/
	static unsigned __stdcall GetReturnRoute(void* data_);

	/**
	* @biref �}�b�v�̈ړ��o�H���ƃG�l�~�[�̏��񃋁[�g�̓ǂݍ��݊֐�
	*/
	bool LoadResouces();

	/**
	* @biref �}�b�v�̈ړ��o�H��񂩂�}�b�v�̃O���t���쐬����֐�
	*/
	void CreateGraph();

private:

	/**
	* @biref �R���X�g���N�^
	*/
	Navigator();

	/**
	* @biref �f�X�g���N�^
	*/
	~Navigator();

	/**
	* @biref �Z�����O���t���ɑ��݂��邩�m�F����֐�
	* @return �O���t���ɂ����true, �Ȃ��ꍇ��false
	* @param[in] row_  �Z����row
	* @param[in] column_ �Z����column
	* @param[in] width_ �O���t��column�̍ő�l
	* @param[in] height_ �O���t��row�̍ő�l
	*/
	bool IsCellInRange(int row_, int column_, int width_, int height_);

	/**
	* @biref �Z�����������̂����肷��֐�
	* @return �Z���������ł����true, �����łȂ��Ȃ�false
	* @param[in] a_ ���肷��Z��
	* @param[in] b_ ���肷��Z��
	*/
	static bool IsEqualCell(const Cell& a_, const Cell& b_);

	/**
	* @biref �q���[���X�e�B�b�N�R�X�g���Z�o����֐�
	* @return �Z�o���ꂽ�R�X�g�i���[�N���b�h�����j
	* @param[in] node_ ���݂̃m�[�h
	* @param[in] goal_ �I�_�̃m�[�h
	*/
	static float CalculateHeruristicCost(const Node* node_, const Node* goal_);

	/**
	* @biref �T�����̃m�[�h���I�[�v�����X�g�ɒǉ����鏈��
	* @param[in] open_ �I�[�v�����X�g
	* @param[in] close_ �N���[�Y���X�g
	* @param[in] current_ �T�����̃��[�g
	* @param[in] add_ �ǉ��\��̃m�[�h
	* @param[in] cost_ �ǉ��\��̃m�[�h�̃q���[���X�e�B�b�N�R�X�g
	*/
	static void AddRoute(std::list<std::unique_ptr<Route>>& open_, std::list<std::unique_ptr<Route>>& close_, std::unique_ptr<Route>& current_, Node* add_, float cost_);

private:
	std::vector<std::vector<std::string>> m_Route;	//!< �G�l�~�[�̏��񃋁[�g
	static std::vector<std::vector<std::string>> m_MovingPath; //!< �}�b�v�̈ړ��o�H���
	static std::vector<std::vector<Node>> m_Graph; //!< �ړ��o�H���O���t�ɂ�������
};

#endif // !NAVIGATIONAI_H_
