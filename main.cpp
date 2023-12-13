#include <Novice.h>
#include <Vector2.h>
#include <Circle.h>
#include <Vector2Int.h>
#include <Player.h>
#include <ScreenInfo.h>
#include <time.h>
#include <BallManager.h>
#include <math.h>
const char kWindowTitle[] = "GC1D_00_オオモリケンジ_タイトル";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	srand((unsigned)time(NULL) * 54321);
	// ライブラリの初期化
	SCREENINFO_WIDTH = 1280;
	SCREENINFO_HEIGHT = 720;
	Novice::Initialize(kWindowTitle, SCREENINFO_WIDTH, SCREENINFO_HEIGHT);
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Vector2Int cursor = {};
	Player* player;
	player = new Player(&cursor);
	BallManager* ballManager = new BallManager(player);




	float frame = 0;
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		Novice::DrawBox(0,0,SCREENINFO_WIDTH, SCREENINFO_HEIGHT,0,0xeeeeeeff,kFillModeSolid);
		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Novice::GetMousePosition(&(cursor.x), &(cursor.y));
		frame+=1;
		if (frame >= 360) { frame -= 360; }
		cursor.x = int(cosf(frame*3.1415f/180.f) * float(SCREENINFO_WIDTH )/ 3.f + float(SCREENINFO_WIDTH )/ 2.f);
		cursor.y = int(sinf(frame*3.1415f/180.f) * float(SCREENINFO_HEIGHT)/ 3.f + float(SCREENINFO_HEIGHT)/ 2.f);
		///
		/// ↓更新処理ここから
		///
		player->Update();
		ballManager->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		player->Draw();
		ballManager->Draw();

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
	delete(player);
	delete(ballManager);



	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
