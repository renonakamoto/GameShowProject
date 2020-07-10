#ifndef NAVIGATIONAI_H_
#define NAVIGATIONAI_H_

#include "..//ExternalFle/Csv/Csv.h"
#include <string>
#include <vector>
#include <d3dx9.h>

class Navigator
{
public:
	/**
	* @biref �R���X�g���N�^
	*/
	Navigator();

	/**
	* @biref �f�X�g���N�^
	*/
	~Navigator();

	/**
	* @biref �G�l�~�[�̏��񃋁[�g�擾�֐�
	* �G�l�~�[�Ɏ��g�̏��񃋁[�g�������܂�
	* @return ���[�g��^����ꂽ��true�A���[�g�񋟂Ɏ��s������false
	*/
	bool GetEnemyRoute(std::string name_, std::vector<D3DXVECTOR3>& route_);

	/**
	* @biref �}�b�v�̈ړ��\���̏���^���܂�
	* @return ����^����ꂽ��true�A���s������false
	*/
	bool GetMapData();

private:
	bool LoadResouces();

private:
	std::vector<std::vector<std::string>> m_Route;
	std::vector<std::vector<std::string>> m_MovingPath;
};

#endif // !NAVIGATIONAI_H_
