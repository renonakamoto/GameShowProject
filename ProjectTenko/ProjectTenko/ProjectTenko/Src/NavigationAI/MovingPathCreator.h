#ifndef MOVINGPATHCREATOR
#define MOVINGPATHCREATOR

#include <vector>

struct PathInfo
{
	unsigned Num;
	bool MovableInfo[8];
};

class MovingPathCreator
{
public:
	MovingPathCreator();
	~MovingPathCreator();

	/**
	* @biref �}�b�v�̈ړ��\�o�H�����쐬���܂�
	*/
	bool CreateMovingPath();

private:
	std::vector<PathInfo> m_PathInfo;
};

#endif // !MOVINGPATHCREATOR
