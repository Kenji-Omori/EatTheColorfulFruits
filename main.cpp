#include <Novice.h>
#include <Vector2.h>
#include <Circle.h>
#include <Vector2Int.h>
#include <Player.h>
#include <ScreenInfo.h>
#include <time.h>
#include <BallManager.h>
#include <math.h>
#include <Camera.h>
#include <cstdio>
#include <Controller.h>


const char kWindowTitle[] = "GC1D_00_オオモリケンジ_タイトル";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	srand((unsigned)time(NULL) * 54321);
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREENINFO_WIDTH, SCREENINFO_HEIGHT);
	// キー入力結果を受け取る箱
	Controller* controller = new Controller();
	Camera* camera = new Camera(controller);
	Player* player = new Player(controller, camera);
	BallManager* ballManager = new BallManager(player, camera);


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		// キー入力を受け取る
		///
		/// ↓更新処理ここから
		///

		controller->Update();
		camera->Update();
		player->Update();
		ballManager->Update();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		ballManager->Draw();
		player->Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (controller->IsKeyDown(KeyCode::Exit)) {
			break;
		}
	}
	delete(player);
	delete(ballManager);
	delete(camera);


	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
