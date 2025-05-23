#include <Novice.h>
#include "function.h"
#include "imgui.h"
const char kWindowTitle[] = "MT3";

Vector3 a{ 0.2f,1.0f,0.0f };
Vector3 b{ 2.4f,3.1f,1.2f };
Vector3 c = a + b;
Vector3 d = a - b;
Vector3 e = a * 2.4f;
Vector3 rotate{ 0.4f,1.43f,-0.8f };
Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
Matrix4x4 rotateXYZMatrix = MakeRotateXYZMatrix(rotate);


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
   // Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
  //  Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };
  // uint32_t color = WHITE;

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
//        /// 
//#pragma region カメラ 
//        // カメラ行列を作成
//        Matrix4x4 cameraMatrix = MakeAffineMatrix(
//            { 1.0f, 1.0f, 1.0f }, // スケール
//            cameraRotate,      // 回転
//            cameraTranslate        // 平行移動
//        );
//
//        // ビュー行列を計算（カメラ行列の逆行列）
//        Matrix4x4 viewMatrix = Inverse(cameraMatrix);
//
//        // プロジェクション行列を作成
//        Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(
//            0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f
//        );
//
//        // ビュー・プロジェクション行列を合成
//        Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
//
//        // ビューポート行列を作成
//        Matrix4x4 viewportMatrix = MakeViewportMatrix(
//            0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f
//        );
//#pragma endregion
//		
        

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///
        ImGui::Begin("Window");
       // ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
       // ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
        ImGui::Text("c:%f,%f,%f", c.x, c.y, c.z);
        ImGui::Text("d:%f,%f,%f", d.x, d.y, d.z);
        ImGui::Text("e:%f,%f,%f", e.x, e.y, e.z);
        ImGui::Text("matrix:\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n",
            rotateXYZMatrix.m[0][0], rotateXYZMatrix.m[0][1], rotateXYZMatrix.m[0][2], rotateXYZMatrix.m[0][3],
            rotateXYZMatrix.m[1][0], rotateXYZMatrix.m[1][1], rotateXYZMatrix.m[1][2], rotateXYZMatrix.m[1][3],
            rotateXYZMatrix.m[2][0], rotateXYZMatrix.m[2][1], rotateXYZMatrix.m[2][2], rotateXYZMatrix.m[2][3],
            rotateXYZMatrix.m[3][0], rotateXYZMatrix.m[3][1], rotateXYZMatrix.m[3][2], rotateXYZMatrix.m[3][3]);

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
