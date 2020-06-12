#ifndef NAVIGATIONAI_H_
#define NAVIGATIONAI_H_

#include "..//ExternalFle/Csv/Csv.h"

struct EnemyRoute
{
	std::string Name;
	std::vector<float> RouteList;
};

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
	bool GetEnemyRoute(std::string Name_);

	/**
	* @biref �}�b�v�̈ړ��\���̏���^���܂�
	* @return ����^����ꂽ��true�A���s������false
	*/
	bool GetMapData();

private:
	bool LoadResouces();

private:
	std::vector <EnemyRoute> m_EnemyRoute;

};

#endif // !NAVIGATIONAI_H_
