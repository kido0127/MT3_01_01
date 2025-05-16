#include <Novice.h>
#include "function.h"
#include "imgui.h"
const char kWindowTitle[] = "MT3";

Vector3 controlPoint[3] = {
	{ -0.8f, 0.58f, 1.0f },
	{ 1.76f, 1.0f, -0.3f },
	{ 0.94f, -0.7f, 2.3f }
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
    Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
    Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };
    uint32_t color = WHITE;

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
#pragma region カメラ 
        // カメラ行列を作成
        Matrix4x4 cameraMatrix = MakeAffineMatrix(
            { 1.0f, 1.0f, 1.0f }, // スケール
            cameraRotate,      // 回転
            cameraTranslate        // 平行移動
        );

        // ビュー行列を計算（カメラ行列の逆行列）
        Matrix4x4 viewMatrix = Inverse(cameraMatrix);

        // プロジェクション行列を作成
        Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(
            0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f
        );

        // ビュー・プロジェクション行列を合成
        Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);

        // ビューポート行列を作成
        Matrix4x4 viewportMatrix = MakeViewportMatrix(
            0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f
        );
#pragma endregion
		
        

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///
        ImGui::Begin("Window");
        ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
        ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("controlPoint[0]", &controlPoint[0].x, 0.01f);
		ImGui::DragFloat3("controlPoint[1]", &controlPoint[1].x, 0.01f);
		ImGui::DragFloat3("controlPoint[2]", &controlPoint[2].x, 0.01f);
		ImGui::End();
		// グリッドを描画
		DrawGrid(viewProjectionMatrix, viewportMatrix);
        DrawBezier(controlPoint[0], controlPoint[1], controlPoint[2], 0.01f, color, viewProjectionMatrix, viewportMatrix);

        // コントロールポイントに黒い球を描画
        for (int i = 0; i < 3; i++) {
            Vector3 ndc = Transform(controlPoint[i], viewProjectionMatrix); // NDC座標に変換
            Vector3 screen = Transform(ndc, viewportMatrix); // スクリーン座標に変換
            Novice::DrawEllipse(
                static_cast<int>(screen.x),
                static_cast<int>(screen.y),
                8, 8, 0.0f, 0x000000FF, kFillModeSolid // 半径8の黒い塗りつぶし円
            );
        }



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
