#include "function.h"
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
//// ベクトルを行列で変換する
//Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
//    Vector3 result;
//    float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
//    result.x = (vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0]) / w;
//    result.y = (vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1]) / w;
//    result.z = (vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2]) / w;
//    return result;
//}
/// <summary>
/// 行列の転置を計算する
/// </summary>
/// <param name="m">元の行列</param>
/// <returns>転置された行列</returns>
Matrix4x4 Transpose(const Matrix4x4& m) {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m.m[j][i];
        }
    }
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
Vector3 TransformVector(const Vector3& vector, const Matrix4x4& matrix) {
    Vector3 result;
    float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
    result.x = (vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0]) / w;
    result.y = (vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1]) / w;
    result.z = (vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2]) / w;
    return result;
}
// クロス積を計算する
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

//正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2)
{
    //v1をv2に射影したベクトルを求める（ベクトル射影）
    float dot = Dot(v1, v2);
    float length = Length(v2);
    if (length != 0) {
        float scale = dot / (length * length);
        return Multiply(scale, v2);//これが正射影ベクトル？
    }

    return Vector3();
}

//最近接点を求める
Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
    Vector3 segmentVector = Subtract(segment.end, segment.start);
    Vector3 pointVector = Subtract(point, segment.start);
    float t = Dot(pointVector, segmentVector) / Dot(segmentVector, segmentVector);
    if (t < 0.0f) {
        return segment.start; // 最近接点は始点
    }
    if (t > 1.0f) {
        return segment.end; // 最近接点は終点
    }
    Vector3 closestPoint = Add(segment.start, Multiply(t, segmentVector));
    return closestPoint; // 最近接点

}

/// <summary>
/// ワールド座標をスクリーン座標に変換する
/// </summary>
/// <param name="worldPosition">ワールド座標</param>
/// <param name="viewProjectionMatrix">ビュー・プロジェクション行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
/// <returns>スクリーン座標</returns>
Vector3 TransformToScreen(const Vector3& worldPosition, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
    // ワールド座標をビュー・プロジェクション行列で変換
    Vector3 ndcPosition = TransformVector(worldPosition, viewProjectionMatrix);
    // NDC座標をビューポート行列で変換
    return TransformVector(ndcPosition, viewportMatrix);
}

/// <summary>
/// グリッドを描画する
/// </summary>
/// <param name="viewProjectionMatrix">ビュー・プロジェクション行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
    const float kGridHalfWidth = 2.0f; // グリッドの半分の幅
    const uint32_t kSubdivision = 10; // グリッドの分割数
    const float kGridSize = (kGridHalfWidth * 2.0f) / kSubdivision; // グリッドの1マスのサイズ

    // 奥から手前へ線を順々に引いていく
    for (uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {
        // ワールド座標系上の視点と終点を求める
        Vector3 start = { -kGridHalfWidth + xIndex * kGridSize, 0.0f, -kGridHalfWidth };
        Vector3 end = { -kGridHalfWidth + xIndex * kGridSize, 0.0f, kGridHalfWidth };

        // スクリーン座標系まで変換をかける
        Vector3 screenStart = TransformToScreen(start, viewProjectionMatrix, viewportMatrix);
        Vector3 screenEnd = TransformToScreen(end, viewProjectionMatrix, viewportMatrix);

        // 変換した座標を使って表示
        Novice::DrawLine(static_cast<int>(screenStart.x), static_cast<int>(screenStart.y),
            static_cast<int>(screenEnd.x), static_cast<int>(screenEnd.y), 0xAAAAAAFF);
    }

    // 左から右に線を順々に引いていく
    for (uint32_t zIndex = 0; zIndex <= kSubdivision; zIndex++) {
        // ワールド座標系上の視点と終点を求める
        Vector3 start = { -kGridHalfWidth, 0.0f, -kGridHalfWidth + zIndex * kGridSize };
        Vector3 end = { kGridHalfWidth, 0.0f, -kGridHalfWidth + zIndex * kGridSize };

        // スクリーン座標系まで変換をかける
        Vector3 screenStart = TransformToScreen(start, viewProjectionMatrix, viewportMatrix);
        Vector3 screenEnd = TransformToScreen(end, viewProjectionMatrix, viewportMatrix);

        // 変換した座標を使って表示
        Novice::DrawLine(static_cast<int>(screenStart.x), static_cast<int>(screenStart.y),
            static_cast<int>(screenEnd.x), static_cast<int>(screenEnd.y), 0xAAAAAAFF);
    }
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
    const uint32_t kSubdivision = 20; // 球の分割数
    const float kLonEvery = 2.0f * float(M_PI) / kSubdivision; // 経度の間隔
    const float kLatEvery = float(M_PI) / kSubdivision; // 緯度の間隔

    // 緯度の方向に分割
    for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++) {
        float lat = float(-M_PI) / 2.0f + kLatEvery * latIndex;
        float nextLat = lat + kLatEvery;

        // 経度の方向に分割
        for (uint32_t lonIndex = 0; lonIndex < kSubdivision; lonIndex++) {
            float lon = kLonEvery * lonIndex;
            float nextLon = lon + kLonEvery;

            // ワールド座標系で A, B, C を求める
            Vector3 a = {
                sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon),
                sphere.center.y + sphere.radius * std::sin(lat),
                sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon)
            };

            Vector3 b = {
                sphere.center.x + sphere.radius * std::cos(nextLat) * std::cos(lon),
                sphere.center.y + sphere.radius * std::sin(nextLat),
                sphere.center.z + sphere.radius * std::cos(nextLat) * std::sin(lon)
            };

            Vector3 c = {
                sphere.center.x + sphere.radius * std::cos(lat) * std::cos(nextLon),
                sphere.center.y + sphere.radius * std::sin(lat),
                sphere.center.z + sphere.radius * std::cos(lat) * std::sin(nextLon)
            };

            // A, B, C をスクリーン座標系まで変換
            Vector3 screenA = TransformToScreen(a, viewProjectionMatrix, viewportMatrix);
            Vector3 screenB = TransformToScreen(b, viewProjectionMatrix, viewportMatrix);
            Vector3 screenC = TransformToScreen(c, viewProjectionMatrix, viewportMatrix);

            // AB, BC の線を描画
            Novice::DrawLine(static_cast<int>(screenA.x), static_cast<int>(screenA.y),
                static_cast<int>(screenB.x), static_cast<int>(screenB.y), color);
            Novice::DrawLine(static_cast<int>(screenB.x), static_cast<int>(screenB.y),
                static_cast<int>(screenC.x), static_cast<int>(screenC.y), color);
        }
    }
}
/// <summary>
/// 球体同士の衝突判定を行う
/// 球体の中心間の距離が、半径の和よりも小さい場合、衝突しているとみなす
/// </summary>
/// <param name="sphere1"></param>
/// <param name="sphere2"></param>
bool CheckSphereCollision(const Sphere& sphere1, const Sphere& sphere2)
{
    // 球体1と球体2の中心間の二条の距離を計算
    float distance =
        (sphere1.center.x - sphere2.center.x) * (sphere1.center.x - sphere2.center.x) +
        (sphere1.center.y - sphere2.center.y) * (sphere1.center.y - sphere2.center.y) +
        (sphere1.center.z - sphere2.center.z) * (sphere1.center.z - sphere2.center.z);
    //半径の合計の２乗を計算
    float radiusSum = (sphere1.radius + sphere2.radius) * (sphere1.radius + sphere2.radius);
    // 衝突判定
    if (distance < radiusSum) {//衝突しているとかえす
        return true;
    }
    else {//衝突していない
        return false;
    }

}

/// <summary>
/// 平面と球の衝突判定を行う
/// </summary>
/// <param name="sphere"></param>
/// <param name="A">平面の任意の点A</param>
/// <param name="B">平面の任意の点B</param>
/// <param name="C">平面の任意の点C</param>
/// /// <param name="任意の点について">関数MakePositionFromPlaneで計算可能</param>
/// <returns></returns>
bool CheckSphereToPlaneCollision(const Sphere& sphere, const Vector3& A, const Vector3& B, const Vector3& C) {
    // 平面の法線を求める
    Vector3 normal = Normalize(Cross(Subtract(B, A), Subtract(C, B)));

    // 平面の方程式の D を求める
    float D = -Dot(normal, A);

    // 球の中心から平面への距離を計算
    float distance = Dot(normal, sphere.center) + D;

    // 衝突判定 (距離の絶対値が球の半径以下なら衝突)
    if (std::fabs(distance) <= sphere.radius) {
        return true;
    }
    else {
        return false;
    }
}


/// <summary>
/// 平面を描画する
/// </summary>
/// <param name="plane"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
/// <param name="size"></param>
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color, float size) {//size = 2.0f
    // 平面の中心点
    Vector3 center = Multiply(plane.distance, plane.normal);

    // 平面上の2つの直交ベクトルを生成（安定化対応）
    Vector3 tangent = Normalize(Cross(Vector3{ 0, 1, 0 }, plane.normal));
    if (Length(tangent) < 0.001f) {
        tangent = Normalize(Cross(Vector3{ 1, 0, 0 }, plane.normal));
    }
    Vector3 bitangent = Normalize(Cross(plane.normal, tangent));

    // 頂点を計算
    Vector3 points[4];
    points[0] = Add(center, Add(Multiply(size, tangent), Multiply(size, bitangent)));
    points[1] = Add(center, Add(Multiply(-size, tangent), Multiply(size, bitangent)));
    points[2] = Add(center, Add(Multiply(-size, tangent), Multiply(-size, bitangent)));
    points[3] = Add(center, Add(Multiply(size, tangent), Multiply(-size, bitangent)));

    // スクリーン座標変換
    for (int i = 0; i < 4; ++i) {
        points[i] = TransformToScreen(points[i], viewProjectionMatrix, viewportMatrix);
    }

    // 四辺を描画
    for (int i = 0; i < 4; ++i) {
        int next = (i + 1) % 4;
        Novice::DrawLine(static_cast<int>(points[i].x), static_cast<int>(points[i].y),
            static_cast<int>(points[next].x), static_cast<int>(points[next].y), color);
    }
}
/// <summary>
/// ベクトルとスカラーの積を計算する
/// </summary>
/// <param name="v"></param>
/// <param name="scalar"></param>
/// <returns></returns>
Vector3 Vector3ToScalarMultiply(const Vector3& v, float scalar) {
    return { v.x * scalar, v.y * scalar, v.z * scalar };
}
/// <summary>
/// 平面の任意の三点を求める
/// </summary>
/// <param name="plane"></param>
/// <param name="outA"></param>
/// <param name="outB"></param>
/// <param name="outC"></param>
void MakePointsFromPlane(const Plane& plane, Vector3* outA, Vector3* outB, Vector3* outC) {
    // 平面上の任意の1点（原点からdistance分法線の逆方向へ進んだ点）
    Vector3 A = Vector3ToScalarMultiply(plane.normal, plane.distance); // plane.normal * distance

    // 平面に対して垂直でない方向ベクトルを1つ用意（例：X軸とクロス）
    Vector3 tangent;
    if (std::fabs(plane.normal.y) < 0.99f) {
        tangent = Normalize(Cross(plane.normal, { 0, 1, 0 }));
    }
    else {
        tangent = Normalize(Cross(plane.normal, { 1, 0, 0 }));
    }

    Vector3 bitangent = Normalize(Cross(plane.normal, tangent));

    *outA = A;
    *outB = Add(A, tangent);   // A点からtangent方向に1進んだ点
    *outC = Add(A, bitangent); // A点からbitangent方向に1進んだ点
}
bool CheckSegmentToPlaneCollision(const Segment& segment, const Plane& plane) {
	// 平面の法線を求める
	Vector3 normal = Normalize(plane.normal);
	// 平面の方程式の D を求める
	float D = -Dot(normal, Multiply(plane.distance, normal));
	// 線分の始点と終点を平面の方程式に代入して距離を計算
	float distanceStart = Dot(normal, segment.start) + D;
	float distanceEnd = Dot(normal, segment.end) + D;
	// 衝突判定 (距離が0以下なら衝突)
	if (distanceStart * distanceEnd <= 0.0f) {
		return true;
	}
	else {
		return false;
	}
}
#pragma endregion