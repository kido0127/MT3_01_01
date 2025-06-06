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
    ball.position = { 0.0f,1.2f,0.3f };
    ball.mass = 2.0f;
    ball.radius = 0.05f;
    Vector3 gravity = { 0.0f, -9.8f, 0.0f };
    ball.acceleration = gravity;

    float e = 0.7f; // 反発係数（0〜1）
    //0.5だと滑る。0.8だとすこし反発

    plane.normal = Normalize({ -0.2f,0.9f,-0.3f });
    plane.distance = 0.0f;


  
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
        ball.velocity += ball.acceleration*deltaTime;
        ball.position += ball.velocity*deltaTime;

        Sphere tempSphere = { ball.position, ball.radius };
        Vector3 incidentVelocity = ball.velocity;

        if (CheckSphereToPlaneCollision(tempSphere, plane)) {
            Vector3 reflected = Reflect(ball.velocity, plane.normal);
            Vector3 projectToNormal = Project(reflected, plane.normal);
            Vector3 movingDirection = reflected - projectToNormal;
            ball.velocity = projectToNormal * e + movingDirection;
        }


      

        ///
        /// ↑更新処理ここまで
        ///
        ///
        /// ↓描画処理ここから
        ///
        ImGui::Begin("Window");
        ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
        ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
        ImGui::DragFloat3("Plane Normal", &plane.normal.x, 0.01f);
        ImGui::DragFloat3("Plane Distance", &plane.distance, 0.01f);
        if (ImGui::Button("Start")) {
            ball.position = { 0.0f,1.2f,0.3f };
            ball.velocity = { 0.0f,0.0f,0.0f };
            ball.acceleration = { 0.0f,-9.8f,0.0f };
       }
        DrawSphere(tempSphere, viewProjectionMatrix, viewportMatrix, WHITE);
        DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE, 1.0f);
        ImGui::End();
        DrawGrid(viewProjectionMatrix, viewportMatrix);
        Novice::ScreenPrintf(0, 0, "%f", ball.position.x);
        Novice::ScreenPrintf(0, 20, "%f", ball.position.y);
        Novice::ScreenPrintf(0, 40, "%f", ball.position.z
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
