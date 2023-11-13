#include "MyMath.h"

float MyMath::Dot(const Vector3& v1, const Vector3& v2)
{
	// 結果格納用
	float result;

	// 計算処理
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return result;
}

float MyMath::Length(const Vector3& v)
{
	// 計算処理
	return sqrtf(Dot(v, v));
}

float MyMath::LerpShortAngle(float a, float b, float t)
{
	// 結果格納用
	float result;

	// 角度差分を求める
	float diff = b - a;

	// 角度差分が-2πを下回る、または上回る時
	if (diff <= (float)(-std::numbers::pi * 2.0f) || diff >= (float)(std::numbers::pi * 2.0f))
		diff = std::fmod(a, b); // 角度差分を補正する

	// -πからπに補正する
	if (diff >= (float)std::numbers::pi) {
		diff -= (float)std::numbers::pi * 2.0f;
	}
	else if (diff <= (float)-std::numbers::pi)
		diff += (float)std::numbers::pi * 2.0f;

	// 求めた角度を元に線形補間を行う
	return result = a + (diff * t);

}

Vector3 MyMath::Normalize(const Vector3& v)
{
	// 正規化するベクトルの長さを求める
	float length = Length(v);
	// 結果格納用
	Vector3 result;

	// 計算処理
	if (v.x != 0.0f) {
		result.x = v.x / length;
	}
	else {
		result.x = 0.0f;
	}
	if (v.y != 0.0f) {
		result.y = v.y / length;
	}
	else {
		result.y = 0.0f;
	}
	if (v.z != 0.0f) {
		result.z = v.z / length;
	}
	else {
		result.z = 0.0f;
	}

	return result;
}

Vector3 MyMath::Transform(const Vector3& v, const Matrix4x4& m)
{
	// 結果格納用
	Vector3 result;

	// 生成処理
	result.x = (v.x * m.m[0][0]) + (v.y * m.m[1][0]) + (v.z * m.m[2][0]) + (1.0f * m.m[3][0]);
	result.y = (v.x * m.m[0][1]) + (v.y * m.m[1][1]) + (v.z * m.m[2][1]) + (1.0f * m.m[3][1]);
	result.z = (v.x * m.m[0][2]) + (v.y * m.m[1][2]) + (v.z * m.m[2][2]) + (1.0f * m.m[3][2]);
	float w = (v.x * m.m[0][3]) + (v.y * m.m[1][3]) + (v.z * m.m[2][3]) + (1.0f * m.m[3][3]);

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Vector3 MyMath::TransformNormal(const Vector3& v, const Matrix4x4& m)
{
	// 結果格納用
	Vector3 result;

	// 生成処理
	result.x = (v.x * m.m[0][0]) + (v.y * m.m[1][0]) + (v.z * m.m[2][0]);
	result.y = (v.x * m.m[0][1]) + (v.y * m.m[1][1]) + (v.z * m.m[2][1]);
	result.z = (v.x * m.m[0][2]) + (v.y * m.m[1][2]) + (v.z * m.m[2][2]);

	return result;
}

Matrix4x4 MyMath::Inverse(const Matrix4x4 m)
{
	// 結果格納用
	Matrix4x4 result = {};

	// 行列式
	float d;

	// 行列式を求める
	d = (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -

		(m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
		(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
		(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -

		(m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
		(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
		(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +

		(m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
		(m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
		(m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +

		(m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
		(m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
		(m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -

		(m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
		(m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
		(m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -

		(m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
		(m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
		(m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +

		(m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
		(m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
		(m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	// 計算処理
	if (d != 0) {

		result.m[0][0] = (1.0f / d) *
			(m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
				- m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);
		result.m[0][1] = (1.0f / d) *
			(-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2]
				+ m.m[0][3] * m.m[2][2] * m.m[3][1] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);
		result.m[0][2] = (1.0f / d) *
			(+m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2]
				- m.m[0][3] * m.m[1][2] * m.m[3][1] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);
		result.m[0][3] = (1.0f / d) *
			(-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2]
				+ m.m[0][3] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);


		result.m[1][0] = (1.0f / d) *
			(-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2]
				+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);
		result.m[1][1] = (1.0f / d) *
			(m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2]
				- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);
		result.m[1][2] = (1.0f / d) *
			(-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2]
				+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);
		result.m[1][3] = (1.0f / d) *
			(m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
				- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);


		result.m[2][0] = (1.0f / d) *
			(m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
				- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);
		result.m[2][1] = (1.0f / d) *
			(-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1]
				+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);
		result.m[2][2] = (1.0f / d) *
			(m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
				- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);
		result.m[2][3] = (1.0f / d) *
			(-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1]
				+ m.m[0][3] * m.m[1][1] * m.m[2][0] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);


		result.m[3][0] = (1.0f / d) *
			(-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1]
				+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);
		result.m[3][1] = (1.0f / d) *
			(m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
				- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);
		result.m[3][2] = (1.0f / d) *
			(-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1]
				+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);
		result.m[3][3] = (1.0f / d) *
			(m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1]
				- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);

	}

	return result;
}

Matrix4x4 MyMath::MakeIdentity4x4()
{
	// 結果格納用
	Matrix4x4 result{};

	// 生成処理
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	// 生成したものを返す
	return result;
}

Matrix4x4 MyMath::MakeTranslateMatrix(const Vector3& translate)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	// 生成結果を返す
	return result;
}

Matrix4x4 MyMath::MakeScaleMatrix(const Vector3& scale)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	// 生成結果を返す
	return result;
}

Matrix4x4 MyMath::MakeRotateXMatrix(const float& X)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	result.m[1][1] = std::cosf(X);
	result.m[1][2] = std::sinf(X);
	result.m[2][1] = -(std::sinf(X));
	result.m[2][2] = std::cosf(X);

	// 生成結果を返す
	return result;
}

Matrix4x4 MyMath::MakeRotateYMatrix(const float& Y)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	result.m[0][0] = std::cosf(Y);
	result.m[0][2] = -(std::sinf(Y));
	result.m[2][0] = std::sinf(Y);
	result.m[2][2] = std::cosf(Y);

	// 生成結果を返す
	return result;
}

Matrix4x4 MyMath::MakeRotateZMatrix(const float& Z)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	result.m[0][0] = std::cosf(Z);
	result.m[0][1] = std::sinf(Z);
	result.m[1][0] = -(std::sinf(Z));
	result.m[1][1] = std::cosf(Z);
	// 生成結果を返す
	return result;
}

Matrix4x4 MyMath::MakeRotateXYZMatrix(const Vector3& rotate)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	Matrix4x4 tempRotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 tempRotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 tempRotateZMatrix = MakeRotateZMatrix(rotate.z);

	result = tempRotateXMatrix * tempRotateYMatrix * tempRotateZMatrix;

	// 生成結果を返す
	return result;
}

Matrix4x4 MyMath::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	Matrix4x4 S = MakeScaleMatrix(scale);
	Matrix4x4 R = MakeRotateXYZMatrix(rotate);
	Matrix4x4 T = MakeTranslateMatrix(translate);

	result = S * R * T;

	// 生成結果を返す
	return result;
}

Matrix4x4 MyMath::MakeOrthGraphicMatrix(const float& left, const float& top, const float& right, const float& bottom, const float& nearClip, const float& farClip)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	result.m[0][0] = 2 / (right - left);
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);

	return result;
}

Matrix4x4 MyMath::MakePerspectiveFovMatrix(const float& fovY, const float& aspectRatio, const float& nearClip, const float& farClip)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	result.m[0][0] = (1 / aspectRatio) * (1 / tanf(fovY / 2));
	result.m[1][1] = (1 / tanf(fovY / 2));
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = -(nearClip * farClip) / (farClip - nearClip);
	result.m[3][3] = 0.0f;

	return result;
}

Matrix4x4 MyMath::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	// 結果格納用単位行列を生成
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	result.m[0][0] = width / 2;
	result.m[1][1] = -height / 2;
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + (width / 2);
	result.m[3][1] = top + (height / 2);
	result.m[3][2] = minDepth;

	return result;
}

Matrix4x4 MyMath::MakeRotateAxisAngle(Vector3 axis, float angle)
{
	// 結果格納用単位行列
	Matrix4x4 result = MakeIdentity4x4();

	// 計算処理
	result.m[0][0] = (float)(pow(axis.x, 2) * (1 - cos(angle)) + cos(angle));
	result.m[0][1] = (axis.x * axis.y) * (1 - cos(angle)) + (axis.z * sin(angle));
	result.m[0][2] = (axis.x * axis.z) * (1 - cos(angle)) - (axis.y * sin(angle));

	result.m[1][0] = (axis.x * axis.y) * (1 - cos(angle)) - (axis.z * sin(angle));
	result.m[1][1] = (float)(pow(axis.y, 2) * (1 - cos(angle)) + cos(angle));
	result.m[1][2] = (axis.y * axis.z) * (1 - cos(angle)) + (axis.x * sin(angle));

	result.m[2][0] = (axis.x * axis.z) * (1 - cos(angle)) + (axis.y * sin(angle));
	result.m[2][1] = (axis.y * axis.z) * (1 - cos(angle)) - (axis.x * sin(angle));
	result.m[2][2] = (float)(pow(axis.z, 2) * (1 - cos(angle)) + cos(angle));

	// 結果を返す
	return result;
}
