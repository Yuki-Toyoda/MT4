#pragma once
#include <Novice.h>
#include <string>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"

/// <summary>
/// デバック関連関数クラス
/// </summary>
class Debug
{
public: // メンバ関数

	/// <summary>
	/// 行列内の情報を表示する関数
	/// </summary>
	/// <param name="x">描画開始位置x座標</param>
	/// <param name="y">描画開始位置y座標</param>
	/// <param name="matrix">描画する行列</param>
	/// <param name="name">名前</param>
	static void MatrixScreenPrintf(int x, int y, Matrix4x4 matrix, std::string name);

};

