#include <Novice.h>
#include "function.h"

const char kWindowTitle[] = "MT3_01_01";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// 三角形の初期位置と回転角度
Vector3 trianglePosition = { 0.0f, 0.0f, 0.0f };
float rotationY = 0.0f;

// カメラの初期位置
Vector3 cameraPosition = { 0.0f, 0.0f, -5.0f };

// 三角形のローカル頂点
Vector3 kLocalVertices[3] = {
    { -0.5f, -0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f },
    { 0.0f, 0.5f, 0.0f }
};


// クロス積を計算する
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}
Vector3 v1{ 1.2f,-3.9f,2.5f };
Vector3 v2{ 2.8f,0.4f,-1.3f };
Vector3 cross = Cross(v1, v2);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///

        // 移動処理
        if (keys[DIK_W]) {
            trianglePosition.z += 0.1f; // 前進
        }
        if (keys[DIK_S]) {
            trianglePosition.z -= 0.1f; // 後退
        }
        if (keys[DIK_A]) {
            trianglePosition.x -= 0.1f; // 左移動
        }
        if (keys[DIK_D]) {
            trianglePosition.x += 0.1f; // 右移動
        }

        // 自動Y軸回転
        rotationY += 0.02f; // 回転速度

        // ワールド行列を作成
        Matrix4x4 worldMatrix = MakeAffineMatrix(
            { 1.0f, 1.0f, 1.0f }, // スケール
            { 0.0f, rotationY, 0.0f }, // 回転
            trianglePosition // 平行移動
        );

        // カメラ行列を作成
        Matrix4x4 cameraMatrix = MakeAffineMatrix(
            { 1.0f, 1.0f, 1.0f }, // スケール
            { 0.0f, 0.0f, 0.0f }, // 回転
            cameraPosition // 平行移動
        );

        // ビュー行列を計算（カメラ行列の逆行列）
        Matrix4x4 viewMatrix = Inverse(cameraMatrix);

        // プロジェクション行列を作成
        Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(
            0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f
        );

        // ビューポート行列を作成
        Matrix4x4 viewportMatrix = MakeViewportMatrix(
            0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f
        );

        // ワールド → ビュー → プロジェクション行列を合成
        Matrix4x4 worldViewProjectionMatrix = Multiply(
            worldMatrix, Multiply(viewMatrix, projectionMatrix)
        );

        // スクリーン座標に変換
        Vector3 screenVertices[3];
        for (int i = 0; i < 3; i++) {
            Vector3 worldVertex = TransformVector(kLocalVertices[i], worldViewProjectionMatrix);
            screenVertices[i] = TransformVector(worldVertex, viewportMatrix);
        }

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///
        VectorScreenPrintf(0, 0, cross, "Cross");
        // 三角形を描画
        Novice::DrawTriangle(
            static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
            static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
            static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
            RED, kFillModeSolid
        );

        ///
        /// ↑描画処理ここまで
        ///

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
