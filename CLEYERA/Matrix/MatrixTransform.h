#pragma once
#include"Matrix2x2.h"
#include"Matrix3x3.h"
#include"Matrix4x4.h"
#include"../Vector/Vector4.h"
#include"../Vector/Vector3.h"



#include<cmath>


#include <cassert>
class MatrixTransform
{
public:
	MatrixTransform();
	~MatrixTransform();

#pragma region 4ł

#pragma region +-*

	/// <summary>
	/// 4x4sńĚŤľZ
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 4x4sńĚřŤZ
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Subract(const Matrix4x4& m1, const Matrix4x4& m2);


	/// <summary>
	/// 4x4sńĚćZ
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);
#pragma endregion 

#pragma region sńĚÚŽEĺŤłEń]
	/// <summary>
	/// 4x4XP[sń
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Matrix4x4 MakeScaleMatrix(const Vector3 scale);

	/// <summary>
	/// 4x4˝sÚŽsń
	/// </summary>
	/// <param name="translate"></param>
	/// <returns></returns>
	Matrix4x4 MakeTranslateMatrix(Vector3 translate);

#pragma region ń]
	/// <summary>
	/// 4x4Y˛Ěń]
	/// </summary>
	/// <param name="px"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXMatrix(float radian);

	/// <summary>
	/// 4x4X˛Ěń]
	/// </summary>
	/// <param name="px"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateYMatrix(float radian);

	/// <summary>
	/// 4x4Z˛Ěń]
	/// </summary>
	/// <param name="px"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateZMatrix(float radian);


	/// <summary>
	/// XYZˇ×ÄĚń]
	/// </summary>
	/// <param name="Xradian"></param>
	/// <param name="Yradian"></param>
	/// <param name="Zradian"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXYZMatrix(float Xradian, float radianY, float Zradian);
#pragma endregion

#pragma endregion

#pragma region sńĚĎˇ

	/// <summary>
	/// 4x4AtBĎˇsń
	/// </summary>
	/// <param name="scale"></param>
	/// <param name="rotate"></param>
	/// <param name="translate"></param>
	/// <returns></returns>
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	/// <summary>
	/// 4x4]ˇsń
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	Matrix4x4 Transpose(const Matrix4x4 m);

	/// <summary>
	/// 4x4tsń
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Matrix4x4 Inverse(Matrix4x4& matrix);

	/// <summary>
	/// 4x4PĘsń
	/// </summary>
	/// <returns></returns>
	Matrix4x4 Identity();


	/// <summary>
	/// 4x4łËesń
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="right"></param>
	/// <param name="bottom"></param>
	/// <param name="neaCrlip"></param>
	/// <param name="farClip"></param>
	/// <returns></returns>
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float neaCrlip, float farClip);

	/// <summary>
	/// 4x4r[|[gsń
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="minDepth"></param>
	/// <param name="maxDepth"></param>
	/// <returns></returns>
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	/// <summary>
	/// ]Ú
	/// </summary>
	/// <param name="theta"></param>
	/// <returns></returns>
	static float Cot(float theta);

	/// <summary>
	/// §esń
	/// </summary>
	/// <param name="fovY"></param>
	/// <param name="aspectRatio"></param>
	/// <param name="nearClip"></param>
	/// <param name="farClip"></param>
	/// <returns></returns>
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	Matrix4x4 toDeviceSpace(Matrix4x4 worldViewProjectionMatrix, int32_t kWindowWidth, int32_t kWindowHeight);
#pragma endregion 





private:

};

