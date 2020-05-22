#ifndef GRAPHICS2DHELPER_H_
#define GRAPHICS2DHELPER_H_

struct CustomVertex
{
	float m_X;			// X座標
	float m_Y;			// Y座標
	float m_Z;			// Z座標	
	float m_Rhw;			// 除算数

	float m_TextureX;		// テクスチャ座標X
	float m_TexrureY;		// テクスチャ座標Y
};

#endif