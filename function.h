#pragma once
#include <Novice.h>
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#pragma region 定義
/// <summary>
/// 3次元ベクトルを表す構造体
/// </summary>
struct Vector3 {
    float x, y, z;

    // 加算
    Vector3 operator+(const Vector3& other) const {
        return { x + other.x, y + other.y, z + other.z };
    }

    // 減算
    Vector3 operator-(const Vector3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }

    // スカラー乗算（ベクトル × スカラー）
    Vector3 operator*(float scalar) const {
        return { x * scalar, y * scalar, z * scalar };
    }

    // 要素ごとのベクトル同士の掛け算（Hadamard積）
    Vector3 operator*(const Vector3& other) const {
        return { x * other.x, y * other.y, z * other.z };
    }
    // スカラー除算
    Vector3 operator/(float scalar) const {
        return { x / scalar, y / scalar, z / scalar };
    }

};

struct Vector4 {
    float x, y, z, w;
};;
/// <summary>
/// 4x4行列を表す構造体
/// </summary>
struct Matrix4x4 {
    float m[4][4];
};
#pragma region Sphere（球関連）
struct Sphere {
    Vector3 center;
    float radius;
};
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
#pragma endregion
#pragma region Segment（線分関連）
struct Segment {
    Vector3 start;
    Vector3 end;
};

#pragma endregion
#pragma region Plane(平面関係)
struct Plane {
    Vector3 normal;
    float distance;
    Vector3 A, B, C;
};
#pragma endregion
#pragma region Triangle（三角形関係）
struct Triangle {
    Vector3 vertices[3];
    float Line;
    float Ray;
};
#pragma endregion
#pragma region AABB（軸平行境界ボックス）
struct AABB {
	Vector3 min; // 最小点
	Vector3 max; // 最大点
};
#pragma endregion
#pragma region 定数
// 横幅
static const int kColuwidth = 60;
static const int kColumnWidth = 60;
// 縦幅
static const int kRowHeight = 20;

// 画面の大きさ
const int kWindowWidth = 1280;
const int kWindowHeight = 720;




#pragma endregion
#pragma region 関数宣言 
/// <summary>
/// VectorScreenPrintf: Vector座標の表示
/// </summary>
/// <param name="x">x座標</param>
/// <param name="y">y座標</param>
/// <param name="vector">表示したい変数名</param>
/// <param name="label">表示したい変数の名前（英語のみ可）</param>
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

/// <summary>
/// MatrixScreenPrintf: Matrix座標の表示
/// </summary>
/// <param name="x">x座標</param>
/// <param name="y">y座標</param>
/// <param name="matrix">表示したい変数名</param>
/// <param name="label">表示したい変数の名前（英語のみ可）</param>
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

/// <summary>
/// Vector型の加算
/// </summary>
/// <param name="v1">変数1</param>
/// <param name="v2">変数2</param>
/// <returns>加算結果のVector3</returns>
Vector3 Add(const Vector3& v1, const Vector3& v2);

/// <summary>
/// Vector型の減算
/// </summary>
/// <param name="v1">変数1</param>
/// <param name="v2">変数2</param>
/// <returns>減算結果のVector3</returns>
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

/// <summary>
/// Vector型のスカラー倍
/// </summary>
/// <param name="scalar">倍率</param>
/// <param name="v">変数</param>
/// <returns>スカラー倍されたVector3</returns>
Vector3 Multiply(float scalar, const Vector3& v);

/// <summary>
/// 内積の計算
/// </summary>
/// <param name="v1">変数1</param>
/// <param name="v2">変数2</param>
/// <returns>内積の結果</returns>
float Dot(const Vector3& v1, const Vector3& v2);

/// <summary>
/// 長さの計算
/// </summary>
/// <param name="v">変数</param>
/// <returns>ベクトルの長さ</returns>
float Length(const Vector3& v);

/// <summary>
/// 正規化
/// </summary>
/// <param name="v">変数</param>
/// <returns>正規化されたVector3</returns>
Vector3 Normalize(const Vector3& v);

/// <summary>
/// Matrix型の加算
/// </summary>
/// <param name="m1">変数1</param>
/// <param name="m2">変数2</param>
/// <returns>加算結果のMatrix4x4</returns>
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// Matrix型の減算
/// </summary>
/// <param name="m1">変数1</param>
/// <param name="m2">変数2</param>
/// <returns>減算結果のMatrix4x4</returns>
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// Matrix型の乗算
/// </summary>
/// <param name="m1">変数1</param>
/// <param name="m2">変数2</param>
/// <returns>乗算結果のMatrix4x4</returns>
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

/// <summary>
/// 平行移動行列を作成
/// </summary>
/// <param name="translate">平行移動量</param>
/// <returns>平行移動行列</returns>
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

/// <summary>
/// 拡大縮小行列を作成
/// </summary>
/// <param name="scale">拡大縮小量</param>
/// <returns>拡大縮小行列</returns>
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

/// <summary>
/// X軸回転行列を作成
/// </summary>
/// <param name="radian">回転量（ラジアン）</param>
/// <returns>X軸回転行列</returns>
Matrix4x4 MakeRotateXMatrix(float radian);

/// <summary>
/// Y軸回転行列を作成
/// </summary>
/// <param name="radian">回転量（ラジアン）</param>
/// <returns>Y軸回転行列</returns>
Matrix4x4 MakeRotateYMatrix(float radian);

/// <summary>
/// Z軸回転行列を作成
/// </summary>
/// <param name="radian">回転量（ラジアン）</param>
/// <returns>Z軸回転行列</returns>
Matrix4x4 MakeRotateZMatrix(float radian);

/// <summary>
/// X, Y, Z軸の回転行列を合成
/// </summary>
/// <param name="rotate">各軸の回転量</param>
/// <returns>合成された回転行列</returns>
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);

/// <summary>
/// スケール、回転、平行移動を合成したアフィン行列を作成
/// </summary>
/// <param name="scale">スケール</param>
/// <param name="rotate">回転</param>
/// <param name="translate">平行移動</param>
/// <returns>アフィン行列</returns>
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

/// <summary>
/// 行列の転置を計算
/// </summary>
/// <param name="m">元の行列</param>
/// <returns>転置された行列</returns>
Matrix4x4 Transpose(const Matrix4x4& m);

/// <summary>
/// 行列の逆行列を計算
/// </summary>
/// <param name="matrix">元の行列</param>
/// <returns>逆行列</returns>
Matrix4x4 Inverse(const Matrix4x4& matrix);

/// <summary>
/// 透視投影行列を作成
/// </summary>
/// <param name="fovY">視野角（ラジアン）</param>
/// <param name="aspect">アスペクト比</param>
/// <param name="nearClip">近クリップ面</param>
/// <param name="farClip">遠クリップ面</param>
/// <returns>透視投影行列</returns>
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspect, float nearClip, float farClip);

/// <summary>
/// ビューポート行列を作成
/// </summary>
/// <param name="left">ビューポートの左端</param>
/// <param name="top">ビューポートの上端</param>
/// <param name="width">ビューポートの幅</param>
/// <param name="height">ビューポートの高さ</param>
/// <param name="minDepth">最小深度</param>
/// <param name="maxDepth">最大深度</param>
/// <returns>ビューポート行列</returns>
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

/// <summary>
/// ベクトルを行列で変換
/// </summary>
/// <param name="vector">変換するベクトル</param>
/// <param name="matrix">変換行列</param>
/// <returns>変換後のベクトル</returns>
Vector3 TransformVector(const Vector3& vector, const Matrix4x4& matrix);

/// <summary>
/// クロス積を計算
/// </summary>
/// <param name="v1">ベクトル1</param>
/// <param name="v2">ベクトル2</param>
/// <returns>クロス積の結果</returns>
Vector3 Cross(const Vector3& v1, const Vector3& v2);
Vector3 TransformToScreen(const Vector3& worldPosition, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
void DrawSphere(const  Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
//bool CheckSphereToSphereCollision(const Sphere& sphere1, const Sphere& sphere2);
bool CheckSphereToPlaneCollision(const Sphere& sphere, const Vector3& A, const Vector3& B, const Vector3& C);

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color, float size);
Vector3 Vector3ToScalarMultiply(const Vector3& v, float scalar);
void MakePointsFromPlane(const Plane& plane, Vector3* outA, Vector3* outB, Vector3* outC);
bool CheckSegmentToPlaneCollision(const Segment& segment, const Plane& plane);
void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

bool TriangleToSegmentIsCollision(const Triangle& triangle, const Segment& segment);
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

bool AABBTOAABBIsCollision(const AABB& aabb1, const AABB& aabb2);
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
bool AABBToSphereIsCollision(const AABB& aabb, const Sphere& sphere);

bool AABBToSegmentIsCollision(const AABB& aabb, const Segment& segment);
Vector3 CubicBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t);
void DrawBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float step, uint32_t color, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

Vector3 Transform(const Vector3& v, const Matrix4x4& m);
#pragma endregion
#pragma region 関数位置リスト
// 20行目: VectorScreenPrintf: Vector座標の表示
// 27行目: MatrixScreenPrintf: Matrix座標の表示
// 34行目: Add: Vector型の加算
// 40行目: Subtract: Vector型の減算
// 46行目: Multiply: Vector型のスカラー倍
// 52行目: Dot: 内積の計算
// 58行目: Length: 長さの計算
// 64行目: Normalize: 正規化
// 70行目: Add: Matrix型の加算
// 76行目: Subtract: Matrix型の減算
// 82行目: Multiply: Matrix型の乗算
// 88行目: MakeTranslateMatrix: 平行移動行列を作成
// 94行目: MakeScaleMatrix: 拡大縮小行列を作成
// 100行目: MakeRotateXMatrix: X軸回転行列を作成
// 106行目: MakeRotateYMatrix: Y軸回転行列を作成
// 112行目: MakeRotateZMatrix: Z軸回転行列を作成
// 118行目: MakeRotateXYZMatrix: X, Y, Z軸の回転行列を合成
// 124行目: MakeAffineMatrix: スケール、回転、平行移動を合成したアフィン行列を作成
// 130行目: Transpose: 行列の転置を計算
// 136行目: Inverse: 行列の逆行列を計算
// 142行目: MakePerspectiveFovMatrix: 透視投影行列を作成
// 148行目: MakeViewportMatrix: ビューポート行列を作成
// 154行目: TransformVector: ベクトルを行列で変換
// 160行目: Cross: クロス積を計算
#pragma endregion

