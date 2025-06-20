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



    //複合代入演算子
    //複合代入演算子はメンバ関数としておなじVector3の中で定義しないといけない
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }

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
#pragma endregion
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
#pragma region 階層構造
struct Node {
    Vector3 scale;
    Vector3 rotate;
    Vector3 translate;

    Matrix4x4 localMatrix;
    Matrix4x4 worldMatrix;
    Node* parent = nullptr;
};
#pragma endregion
#pragma region Spring (ばね)
struct Spring {
    //アンカー。固定された橋の位置
    Vector3 anchor;
    float naturalLength;//自然長
    float stiffness;//剛性。ばね定数ｋ
    float dampingCoefficient;//減衰係数
};
#pragma endregion
#pragma region Ball(ボール)
struct Ball {
    Vector3 position;//ボールの位置
    Vector3 velocity;//ボールの速度
    Vector3 acceleration;//ボールの加速度
    float mass;//ボールの質量
    float radius;//ボールの半径
    unsigned int color;//ボールの色
};
#pragma region Pendulum(振り子)
struct Pendulum {
    Vector3 anchor;//アンカーポイント。固定された端の位置
    float length;//紐の長さ
    float angle;//現在の角度
    float angularVelocity;//角速度w
    float angularAcceleration;//各加速度
};
#pragma region ConicalPendulum(円錐振り子)
struct ConicalPendulum {
    Vector3 anchor;//アンカーポイント。固定された端の位置
    float length;//紐の長さ
    float halfApexAngle;//円錐の頂角の半分
    float angle;//現在の角度
    float angularVelocity;//角速度w
};
#pragma endregion
#pragma endregion
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

//時間
const float deltaTime = 1.0f/60.0f;



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
#pragma region 基本の計算
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
#pragma endregion
#pragma region 二項演算子と単項演算子
//二項演算子
//Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); };
//Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); };
//Vector3 operator* (float s, const Vector3& v) { return Multiply(s, v); };
//Vector3 operator*(const Vector3 v, float s) { return s * v; };
//Vector3 operator/(const Vector3& v, float s) { return Multiply(1.0f / s, v); };
inline Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Add(m1, m2); };
inline Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Subtract(m1, m2); };
inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); };
//単項演算子
inline Vector3 operator-(const Vector3& v) { return{ -v.x,-v.y,-v.z }; };
inline Vector3 operator+(const Vector3& v) { return v; };
inline Vector3 operator*(float scalar, const Vector3& v) {
    return { v.x * scalar, v.y * scalar, v.z * scalar };
}
#pragma endregion




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

/// <summary>
/// スクリーン座標に変換する
/// </summary>
/// <param name="worldPosition">変換したいモノのワールド座標</param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <returns></returns>
Vector3 TransformToScreen(const Vector3& worldPosition, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

/// <summary>
/// ベクトル v1 をベクトル v2 上に射影（プロジェクション）した結果のベクトルを返します。
/// この関数は、v1 の成分のうち、v2 の方向に沿った成分だけを取り出す操作に相当します。
/// たとえば、力の分解や、ある軸方向への影響成分を抽出したい場面などで利用されます。
/// v2 がゼロベクトルの場合、結果もゼロベクトルとなります。
/// </summary>
/// <param name="v1">射影される対象のベクトル。これを v2 の方向へ投影します。</param>
/// <param name="v2">射影先となるベクトル。このベクトルの方向に対して v1 を投影します。</param>
/// <returns>
/// ベクトル v1 を v2 上に射影した結果のベクトル。
/// 計算式としては、(dot(v1, v2) / dot(v2, v2)) * v2 に相当します。
/// v2 がゼロベクトルの場合は、(0, 0, 0) を返します。
/// </returns>
Vector3 Project(const Vector3& v1, const Vector3& v2);

/// <summary>
/// 指定された点 point に最も近い位置にある、線分 segment 上の点を計算して返します。
/// この関数は、点と線分との最短距離を求めるために用いられ、
/// その距離が 0 のときは、point が segment 上にあることを意味します。
/// 計算では、まず無限直線上の最近点を求めた後、それが線分外にある場合は端点のいずれかを返します。
/// </summary>
/// <param name="point">基準となる任意の空間上の点。この点から線分に最も近い点を探します。</param>
/// <param name="segment">対象となる線分。始点と終点を持つ有限長の線分です。</param>
/// <returns>
/// 線分 segment 上で、指定された点 point に最も近い位置にある点（= 最近接点）。
/// 計算には内積やクランプ（0～1）による補間係数を使い、線分内に制限した上で最近点を算出します。
/// </returns>
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

/// <summary>
/// 3D 空間上にグリッド（格子線）を描画します。
/// この関数は、主にデバッグ表示やエディタビューなどで、空間の基準となる床面のようなビジュアルガイドを描くために使用されます。
/// 描画は、渡されたビュー・プロジェクション行列およびビューポート行列を用いて、カメラ視点に合わせて行われます。
/// </summary>
/// <param name="viewProjectionMatrix">
/// カメラのビュー行列とプロジェクション行列を掛け合わせた行列。
/// モデル座標をクリップ空間に変換するために使用します。
/// </param>
/// <param name="viewportMatrix">
/// ビューポート行列。クリップ空間の座標を画面座標に変換するために使用します。
/// 通常はスクリーン解像度や描画領域に依存します。
/// </param>
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

/// <summary>
/// 指定された球体（Sphere）を、指定のビュー・プロジェクション行列およびビューポート行列を用いて描画します。
/// 主にデバッグ用の可視化として使用され、球体の境界や当たり判定の確認、空間的な配置の把握などに役立ちます。
/// 描画はワイヤーフレームで行われることが一般的です。
/// </summary>
/// <param name="sphere">
/// 描画対象の球体。中心座標と半径を持つ Sphere 構造体（またはクラス）です。
/// </param>
/// <param name="viewProjectionMatrix">
/// カメラのビュー行列とプロジェクション行列を掛け合わせた行列。
/// 球体のモデル座標をクリップ空間に変換するために使用します。
/// </param>
/// <param name="viewportMatrix">
/// ビューポート行列。クリップ空間の座標を画面座標に変換するために使用します。
/// 通常はウィンドウサイズや描画領域に基づいて設定されます。
/// </param>
/// <param name="color">
/// 球体の描画色。RGBA形式（またはARGB形式）で指定される 32bit 整数カラーコードです。
/// デバッグ用などで視認性を高めるために色分けが可能です。
/// </param>
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

/// <summary>
/// 2つの球体（Sphere）が衝突しているかどうかを判定します。
/// 球体同士の衝突判定は、両球体の中心間の距離と、それぞれの半径の和を比較することで行われます。
/// 中心間の距離が半径の和以下であれば、球体同士は衝突（交差）していると判断されます。
/// </summary>
/// <param name="sphere1">
/// 判定対象となる1つ目の球体。中心座標と半径を持ちます。
/// </param>
/// <param name="sphere2">
/// 判定対象となる2つ目の球体。sphere1と同様に、中心座標と半径を持ちます。
/// </param>
/// <returns>
/// 衝突していれば true、衝突していなければ false を返します。
/// なお、球体の表面が触れている場合（距離がぴったり半径の和と等しい）も true を返します。
/// </returns>
//bool CheckSphereToSphereCollision(const Sphere& sphere1, const Sphere& sphere2);

/// <summary>
/// 球体（Sphere）が、3点（A, B, C）によって定義される平面と衝突（交差）しているかどうかを判定します。
/// 判定は、球の中心から平面への垂直距離が、球の半径以下であるかどうかに基づいて行われます。
/// 平面は、3点 A, B, C によって一意に定義される三角形の含まれる無限平面です。
/// </summary>
/// <param name="sphere">
/// 衝突判定対象の球体。中心座標と半径を持ちます。
/// </param>
/// <param name="A">
/// 平面を構成する三角形の1点目。Vector3 型の座標。
/// </param>
/// <param name="B">
/// 平面を構成する三角形の2点目。Vector3 型の座標。
/// </param>
/// <param name="C">
/// 平面を構成する三角形の3点目。Vector3 型の座標。
/// </param>
/// <returns>
/// 球体と平面が衝突している（交差している）場合は true を返します。
/// 衝突していない（中心から平面までの距離が半径を超えている）場合は false を返します。
/// なお、この判定は三角形との交差ではなく、あくまで三角形が含まれる「平面」との衝突を判定します。
/// </returns>
bool CheckSphereToPlaneCollision(const Sphere& sphere, const Vector3& A, const Vector3& B, const Vector3& C);

/// <summary>
/// 指定された平面（Plane）を、ビュー・プロジェクション行列およびビューポート行列を用いて描画します。
/// この関数は、デバッグ表示やエディタ上での可視化目的に利用され、
/// 平面の位置や傾きを視覚的に確認するためのガイドラインや面表示を行います。
/// 描画される平面は、与えられた中心と法線ベクトルをもとに、指定されたサイズで四角形として表示されます。
/// </summary>
/// <param name="plane">
/// 描画対象となる平面。位置ベクトルおよび法線（法線ベクトル）を含む Plane 型の構造体。
/// </param>
/// <param name="viewProjectionMatrix">
/// ビュー行列とプロジェクション行列を掛け合わせた行列。モデル空間からクリップ空間への変換に使用されます。
/// </param>
/// <param name="viewportMatrix">
/// ビューポート行列。クリップ空間から画面座標への変換に使用されます。
/// 通常はウィンドウの幅・高さなどに基づいて構築されます。
/// </param>
/// <param name="color">
/// 描画する平面の色。RGBA 形式（または ARGB）で指定される 32bit のカラー値。
/// </param>
/// <param name="size">
/// 描画する平面の大きさ（スケール）。中心からの距離として解釈され、
/// size が大きいほど平面の描画範囲（正方形の幅と高さ）は広くなります。
/// </param>
void DrawPlane(const Plane& plane, const Matrix4x4&  viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color, float size);
/// <summary>
/// 指定されたベクトル v を、スカラー値 scalar 倍した結果のベクトルを返します。
/// 各成分（x, y, z）を scalar で一括して乗算することで、ベクトルの大きさ（長さ）を拡大・縮小します。
/// ベクトルの方向は変わらず、大きさのみが変化します（scalar が負の場合は方向も反転します）。
/// </summary>
/// <param name="v">
/// スカラー倍の対象となる 3 次元ベクトル。各成分は float 型を想定します。
/// </param>
/// <param name="scalar">
/// ベクトルに掛けるスカラー値。大きさを調整するための係数です。
/// </param>
/// <returns>
/// 元のベクトル v に scalar を掛けた結果のベクトル（x, y, z 成分すべてに scalar を乗算）。
/// 例えば v = (1, 2, 3), scalar = 2 のとき、戻り値は (2, 4, 6) となります。
/// </returns>
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
void UpdateNodeMatrix(Node& node);
void DrawNodeLine(const Node& parent, const Node& child, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
Vector3 GetTranslateFromMatrix(const Matrix4x4& m);

void ResetSimulation(Spring& spring, Ball& ball, Segment& segment, Sphere& sphere);
void UpdateSphereTocircleMove(Sphere& sphere, float time, float radius);

void ResetPendulum(Pendulum& pendulum, const Vector3& anchor, float length, float initializeAngle, float angularVelocity, float angularAcceleration);
Vector3 GetPendulumPosition(const Pendulum& pendulum);
void UpdatePendulum(Pendulum& pendulum, float dt);

void ResetConicalPendulum(ConicalPendulum& conicalPendulum, const Vector3& anchor, float length, float halfApexAngle, float initialAngle);
void UpdateConicalPendulum(ConicalPendulum& conicalPendulum, float deltaTime);
Vector3 GetConicalPendulumPosition(const ConicalPendulum & conicalPendulum);


Vector3 Reflect(const Vector3 input, const Vector3 normal);
bool CheckSphereToPlaneCollision(const Sphere& sphere, const Plane& plane);


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

