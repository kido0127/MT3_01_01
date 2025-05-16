#include <Novice.h>
#include "function.h"
#include "imgui.h"
const char kWindowTitle[] = "MT3";
Segment segment = { {1.0f,1.0f,1.0f},1.0f };
Triangle triangle = { { { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } }, 1.0f, 1.0f };


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


		bool isCollision = TriangleToSegmentIsCollision(triangle, segment);
		if (isCollision==true) {
			color = RED;
        }
        else {
			color = WHITE;
        }

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///
		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawTriangle(triangle, viewProjectionMatrix, viewportMatrix, WHITE);
		DrawSegment(segment, viewProjectionMatrix, viewportMatrix, color);

        ImGui::Begin("Window");
		ImGui::DragFloat3("Triangle0", &triangle.vertices[0].x, 0.01f);
		ImGui::DragFloat3("Triangle1", &triangle.vertices[1].x, 0.01f);
		ImGui::DragFloat3("Triangle2", &triangle.vertices[2].x, 0.01f);
		ImGui::DragFloat3("SegmentStart", &segment.start.x, 0.01f);
		ImGui::DragFloat3("SegmentEnd", &segment.end.x, 0.01f);
        ImGui::End();

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
