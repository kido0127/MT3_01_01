#include <Novice.h>
#include "function.h"
#include "imgui.h"
const char kWindowTitle[] = "MT3";
Spring spring;
Ball ball;

Segment segment;
Sphere sphere;



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
    Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
    Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };
  // uint32_t color = WHITE;
    spring.anchor = { 0.0f,0.0f,0.0f };
    spring.naturalLength = 1.0f;
    spring.stiffness = 100.0f;
    spring.dampingCoefficient = 2.0f;
    
    ball.position = { 1.2f,0.0f,0.0f };
    ball.mass = 2.0f;
    ball.radius = 0.05f;
    ball.color = BLUE;

    Vector3 diff = ball.position - spring.anchor;
    float length = Length(diff);
    float deltaTime = 1.0f / 60.0f;

    segment.start = spring.anchor;
    segment.end = ball.position;

    sphere.center = ball.position;
    sphere.radius = ball.radius;


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
        diff = ball.position - spring.anchor;
        length = Length(diff);
        if (length != 0.0f) {
            Vector3 direction = Normalize(diff);
            Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
            Vector3 displacement = ball.position - restPosition;
            Vector3 restoringForce = -spring.stiffness * displacement;
            Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;
            Vector3 force = restoringForce + dampingForce;;
            ball.acceleration = force / ball.mass;
        }
        ball.velocity += ball.acceleration * deltaTime;
        ball.position += ball.velocity * deltaTime;

        segment.start = spring.anchor;
        segment.end = ball.position;

        sphere.center = ball.position;
        sphere.radius = ball.radius;
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
            ResetSimulation(spring, ball, segment, sphere);
       }
		ImGui::End();
        DrawGrid(viewProjectionMatrix, viewportMatrix);
        DrawSegment(segment, viewProjectionMatrix, viewportMatrix, WHITE);
        DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, ball.color);


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
