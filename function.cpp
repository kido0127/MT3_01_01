#include "function.h"
#pragma region 定義
/// <summary>
/// 3次元ベクトルを表す構造体
/// </summary>
struct Vector3 {
    float x, y, z;
};

/// <summary>
/// 4x4行列を表す構造体
/// </summary>
struct Matrix4x4 {
    float m[4][4];
};

static const int kColuwidth = 60;
static const int kRowHeight = 20;
static const int kColumnWidth = 60;
#pragma endregion
#pragma region 数値表示関数
/// <summary>
/// 3次元ベクトルを画面に表示する
/// </summary>
/// <param name="x">表示位置のX座標</param>
/// <param name="y">表示位置のY座標</param>
/// <param name="vector">表示するベクトル</param>
/// <param name="label">ラベル文字列</param>
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
    Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
    Novice::ScreenPrintf(x + kColuwidth, y, "%0.2f", vector.y);
    Novice::ScreenPrintf(x + kColuwidth * 2, y, "%0.2f", vector.z);
    Novice::ScreenPrintf(x + kColuwidth * 3, y, "%s", label);
}

/// <summary>
/// 4x4行列を画面に表示する
/// </summary>
/// <param name="x">表示位置のX座標</param>
/// <param name="y">表示位置のY座標</param>
/// <param name="matrix">表示する行列</param>
/// <param name="label">ラベル文字列</param>
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    Novice::ScreenPrintf(x, y, "%s", label);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Novice::ScreenPrintf(x + j * kColumnWidth, y + (i + 1) * kRowHeight, "%6.02f", matrix.m[i][j]);
        }
    }
}
#pragma endregion
#pragma region 数値計算関数
/// 2つのベクトルを加算する
Vector3 Add(const Vector3& v1, const Vector3& v2) {
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// 2つのベクトルを減算する
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// ベクトルをスカラー倍する
Vector3 Multiply(float scalar, const Vector3& v) {
    return { scalar * v.x, scalar * v.y, scalar * v.z };
}

// 2つのベクトルの内積を計算する
float Dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// ベクトルの長さ（ノルム）を計算する
float Length(const Vector3& v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

// ベクトルを正規化する
Vector3 Normalize(const Vector3& v) {
    float length = Length(v);
    if (length != 0) {
        return { v.x / length, v.y / length, v.z / length };
    }
    return { 0.0f, 0.0f, 0.0f };
}

// 2つの行列を加算する
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m1.m[i][j] + m2.m[i][j];
        }
    }
    return result;
}

// 2つの行列を減算する
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m1.m[i][j] - m2.m[i][j];
        }
    }
    return result;
}

// 2つの行列を乗算する
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }
    return result;
}

// 平行移動行列を作成する
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
    Matrix4x4 result = {};
    result.m[0][0] = 1.0f;
    result.m[1][1] = 1.0f;
    result.m[2][2] = 1.0f;
    result.m[3][3] = 1.0f;
    result.m[3][0] = translate.x;
    result.m[3][1] = translate.y;
    result.m[3][2] = translate.z;
    return result;
}

// 拡大縮小行列を作成する
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
    Matrix4x4 result = {};
    result.m[0][0] = scale.x;
    result.m[1][1] = scale.y;
    result.m[2][2] = scale.z;
    result.m[3][3] = 1.0f;
    return result;
}

// X軸回転行列を作成する
Matrix4x4 MakeRotateXMatrix(float radian) {
    Matrix4x4 result = {};
    result.m[0][0] = 1.0f;
    result.m[1][1] = std::cos(radian);
    result.m[1][2] = std::sin(radian);
    result.m[2][1] = -std::sin(radian);
    result.m[2][2] = std::cos(radian);
    result.m[3][3] = 1.0f;
    return result;
}

// Y軸回転行列を作成する
Matrix4x4 MakeRotateYMatrix(float radian) {
    Matrix4x4 result = {};
    result.m[0][0] = std::cos(radian);
    result.m[0][2] = -std::sin(radian);
    result.m[1][1] = 1.0f;
    result.m[2][0] = std::sin(radian);
    result.m[2][2] = std::cos(radian);
    result.m[3][3] = 1.0f;
    return result;
}

// Z軸回転行列を作成する
Matrix4x4 MakeRotateZMatrix(float radian) {
    Matrix4x4 result = {};
    result.m[0][0] = std::cos(radian);
    result.m[0][1] = std::sin(radian);
    result.m[1][0] = -std::sin(radian);
    result.m[1][1] = std::cos(radian);
    result.m[2][2] = 1.0f;
    result.m[3][3] = 1.0f;
    return result;
}

// X, Y, Z軸の回転行列を合成する
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate) {
    Matrix4x4 rotateX = MakeRotateXMatrix(rotate.x);
    Matrix4x4 rotateY = MakeRotateYMatrix(rotate.y);
    Matrix4x4 rotateZ = MakeRotateZMatrix(rotate.z);
    return Multiply(Multiply(rotateX, rotateY), rotateZ);
}

// スケール、回転、平行移動を合成したアフィン行列を作成する
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
    Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
    Matrix4x4 rotateMatrix = MakeRotateXYZMatrix(rotate);
    Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
    return Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);
}
// ベクトルを行列で変換する
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
    Vector3 result;
    float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
    result.x = (vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0]) / w;
    result.y = (vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1]) / w;
    result.z = (vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2]) / w;
    return result;
}
Matrix4x4 Inverse(const Matrix4x4& m) {
    Matrix4x4 result = {};
    float determinant =
        m.m[0][0] * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2]
            - m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2])
        - m.m[0][1] * (m.m[1][0] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][2]
            - m.m[1][3] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][2])
        + m.m[0][2] * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
            - m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1])
        - m.m[0][3] * (m.m[1][0] * m.m[2][1] * m.m[3][2] + m.m[1][1] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][0] * m.m[3][1]
            - m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][2] - m.m[1][0] * m.m[2][2] * m.m[3][1]);

    if (determinant == 0.0f) {
        return result;
    }

    // 余因子行列を計算
    Matrix4x4 cofactor = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float minor[3][3];
            int row = 0, col = 0;
            for (int r = 0; r < 4; r++) {
                if (r != i) {
                    col = 0;
                    for (int c = 0; c < 4; c++) {
                        if (c != j) {
                            minor[row][col] = m.m[r][c];
                            col++;
                        }
                    }
                    row++;
                }
            }
            float minorDeterminant =
                minor[0][0] * (minor[1][1] * minor[2][2] - minor[1][2] * minor[2][1]) -
                minor[0][1] * (minor[1][0] * minor[2][2] - minor[1][2] * minor[2][0]) +
                minor[0][2] * (minor[1][0] * minor[2][1] - minor[1][1] * minor[2][0]);

            cofactor.m[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minorDeterminant;
        }
    }

    Matrix4x4 adjugate = Transpose(cofactor);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = adjugate.m[i][j] / determinant;
        }
    }

    return result;
}

// 透視投影行列を作成する
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspect, float nearClip, float farClip) {
    Matrix4x4 result = {};
    float tanHalfFovY = tanf(fovY / 2.0f);

    result.m[0][0] = 1.0f / (aspect * tanHalfFovY);
    result.m[1][1] = 1.0f / tanHalfFovY;
    result.m[2][2] = farClip / (farClip - nearClip);
    result.m[2][3] = 1.0f;
    result.m[3][2] = -(farClip * nearClip) / (farClip - nearClip);

    return result;
}

// ビューポート行列を作成する
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
    Matrix4x4 result = {};
    result.m[0][0] = width / 2.0f;
    result.m[1][1] = -height / 2.0f;
    result.m[2][2] = maxDepth - minDepth;
    result.m[3][0] = left + width / 2.0f;
    result.m[3][1] = top + height / 2.0f;
    result.m[3][2] = minDepth;
    result.m[3][3] = 1.0f;

    return result;
}



#pragma endregion