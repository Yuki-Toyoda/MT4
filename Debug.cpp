#include "Debug.h"

void Debug::MatrixScreenPrintf(int x, int y, Matrix4x4 matrix, std::string name)
{
	// 各要素	の描画
	Novice::ScreenPrintf(x, y, "%s", name.c_str()); // 名前表示
	Novice::ScreenPrintf(x, y + 20, "%.3f  %.3f  %.3f  %.3f", matrix.m[0][0], matrix.m[0][1], matrix.m[0][2], matrix.m[0][3]);
	Novice::ScreenPrintf(x, y + 40, "%.3f  %.3f  %.3f  %.3f", matrix.m[1][0], matrix.m[1][1], matrix.m[1][2], matrix.m[1][3]);
	Novice::ScreenPrintf(x, y + 60, "%.3f  %.3f  %.3f  %.3f", matrix.m[2][0], matrix.m[2][1], matrix.m[2][2], matrix.m[2][3]);
	Novice::ScreenPrintf(x, y + 80, "%.3f  %.3f  %.3f  %.3f", matrix.m[3][0], matrix.m[3][1], matrix.m[3][2], matrix.m[3][3]);
}
