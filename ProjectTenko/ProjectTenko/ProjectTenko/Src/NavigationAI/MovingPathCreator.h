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
	* @biref マップの移動可能経路情報を作成します
	*/
	bool CreateMovingPath();

private:
	std::vector<PathInfo> m_PathInfo;
};

#endif // !MOVINGPATHCREATOR
