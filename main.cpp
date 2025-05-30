#include <Novice.h>
#include "function.h"
#include "imgui.h"
const char kWindowTitle[] = "MT3";

Ball ball;
Plane plane;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
    Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
    Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };
  // uint32_t color = WHITE;
   // 変数定義
   
  // float elaspedTime = 0.0f;
    ball.acceleration = { 0.0f,-9.8f,0.0f };
    plane.normal = { 0.0f,1.0f,0.0f };
    plane.distance = 0.0f;
    plane.A = { -1.0f,0.0f,-1.0f };
    plane.B = { 1.0f,0.0f,-1.0f };
    plane.C = { 0.0f,0.0f,1.0f };

  
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

        ball.velocity = Add(ball.velocity, Multiply(deltaTime, ball.acceleration));
        ball.position = Add(ball.position, Multiply(deltaTime, ball.velocity));

        if (CheckSphereToPlaneCollision(ball, plane.A, plane.B, plane.C)) {
            // 反射ベクトルに変更
            Vector3 reflected = Reflect(ball.velocity, plane.normal);
            // 反発係数をかけて速度調整
            float restitution = 0.8f; // 反発係数(例)
            ball.velocity = Multiply(restitution, reflected);

            // めり込み防止（法線方向に押し戻す）
            float dist = Dot(ball.position, plane.normal) + plane.distance;
            ball.position = Subtract(ball.position, Multiply(dist, plane.normal));

        }
        ///
        /// ↑更新処理ここまで
        ///
        ///
        /// ↓描画処理ここから
        ///
        ImGui::Begin("Window");
       // ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
       // ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
        if (ImGui::Button("Start")) {
       }
        ImGui::End();
        DrawGrid(viewProjectionMatrix, viewportMatrix);
      
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
