#include <Novice.h>
#include "function.h"
#include "imgui.h"

const char kWindowTitle[] = "MT3";

// 各種パラメータ
Vector3 translates[3] = {
    {0.2f,1.0f,0.0f},
    {0.4f,0.0f,0.0f},
    {0.3f,0.0f,0.0f},
};
Vector3 rotates[3] = {
    {0.0f,0.0f,-6.8f},
    {0.0f,0.0f,-1.4f},
    {0.0f,0.0f,0.0f},
};
Vector3 scales[3] = {
    {1.0f,1.0f,1.0f},
    {1.0f,1.0f,1.0f},
    {1.0f,1.0f,1.0f},
};

// ノード
Node shoulderNode;
Node elbowNode;
Node handNode;

// Windowsアプリケーションのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

    Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
    Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };

    // ノード初期化
    shoulderNode.translate = translates[0];
    shoulderNode.rotate = rotates[0];
    shoulderNode.scale = scales[0];
    shoulderNode.parent = nullptr;

    elbowNode.translate = translates[1];
    elbowNode.rotate = rotates[1];
    elbowNode.scale = scales[1];
    elbowNode.parent = &shoulderNode;

    handNode.translate = translates[2];
    handNode.rotate = rotates[2];
    handNode.scale = scales[2];
    handNode.parent = &elbowNode;

    // キー入力用
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // メインループ
    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // カメラの行列
        Matrix4x4 cameraMatrix = MakeAffineMatrix(
            { 1.0f, 1.0f, 1.0f },
            cameraRotate,
            cameraTranslate
        );
        Matrix4x4 viewMatrix = Inverse(cameraMatrix);
        Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(
            0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f
        );
        Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
        Matrix4x4 viewportMatrix = MakeViewportMatrix(
            0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f
        );

        // ノードの更新
        UpdateNodeMatrix(shoulderNode);
        UpdateNodeMatrix(elbowNode);
        UpdateNodeMatrix(handNode);

        // ImGui操作
        ImGui::Begin("Window");
        ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
        ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
        ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);
        ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
        ImGui::DragFloat3("scales[0]", &scales[0].x, 0.01f);
        ImGui::DragFloat3("translates[1]", &translates[1].x, 0.01f);
        ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.01f);
        ImGui::DragFloat3("scales[1]", &scales[1].x, 0.01f);
        ImGui::DragFloat3("translates[2]", &translates[2].x, 0.01f);
        ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.01f);
        ImGui::DragFloat3("scales[2]", &scales[2].x, 0.01f);

        ImGui::End();

        // グリッド描画
        DrawGrid(viewProjectionMatrix, viewportMatrix);

        // ↓追加（毎フレーム、ノードに値を再代入）
        shoulderNode.translate = translates[0];
        shoulderNode.rotate = rotates[0];
        shoulderNode.scale = scales[0];

        elbowNode.translate = translates[1];
        elbowNode.rotate = rotates[1];
        elbowNode.scale = scales[1];

        handNode.translate = translates[2];
        handNode.rotate = rotates[2];
        handNode.scale = scales[2];
        // 座標取得
        Vector3 shoulderPos = GetTranslateFromMatrix(shoulderNode.worldMatrix);
        Vector3 elbowPos = GetTranslateFromMatrix(elbowNode.worldMatrix);
        Vector3 handPos = GetTranslateFromMatrix(handNode.worldMatrix);

        // 修正済みの描画（Sphere構造体で描く）
        Sphere shoulderSphere = { shoulderPos, 0.1f };
        Sphere elbowSphere = { elbowPos, 0.1f };
        Sphere handSphere = { handPos, 0.1f };

        DrawSphere(shoulderSphere, viewProjectionMatrix, viewportMatrix, RED);
        DrawSphere(elbowSphere, viewProjectionMatrix, viewportMatrix, GREEN);
        DrawSphere(handSphere, viewProjectionMatrix, viewportMatrix, BLUE);
        DrawNodeLine(shoulderNode, elbowNode, viewProjectionMatrix, viewportMatrix, WHITE);
        DrawNodeLine(elbowNode, handNode, viewProjectionMatrix, viewportMatrix, WHITE);


        // フレーム終了
        Novice::EndFrame();

        // 終了判定
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
