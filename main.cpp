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
const char kWindowTitle[] = "GC1D_00_オオモリケンジ_タイトル";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	srand((unsigned)time(NULL) * 54321);
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, SCREENINFO_WIDTH, SCREENINFO_HEIGHT);
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Camera* camera = new Camera();
	Vector2Int cursor = {};
	Vector2 input = {};
	Player* player;
	player = new Player(&input, camera);
	BallManager* ballManager = new BallManager(player, camera);
	float frame = 0;




	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		//Novice::DrawBox(0,0,SCREENINFO_WIDTH, SCREENINFO_HEIGHT,0,0xeeeeeeff,kFillModeSolid);
		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Novice::GetMousePosition(&cursor.x, &cursor.y);


		Novice::SetJoystickDeadZone(0,0,0);
		int stickX = 0;
		int stickY = 0;
		Novice::GetAnalogInputLeft(0, &stickX, &stickY);
		float x = float(stickX);
		float y = float(stickY);
		input.x = x / 32768.f;
		input.y = y / 32768.f;


		Novice::GetAnalogInputRight(0, &stickX, &stickY);
		x = float(stickX);
		y = float(stickY);

		float cameraOffsetX = x / 32768.f * 200;
		float cameraOffsetY = y / 32768.f * 200;


		//if (input.x != 0 || input.y != 0) {
		//	float angle = atan2f(input.y, input.x);
		//	//float top = 1;
		//	//float bottom = 1 / sqrtf(2);
		//	float coefficient = ((cosf(angle) ));
		//	input = input * coefficient;
	
		//	Novice::ScreenPrintf(10, 10, "%.3f", angle * 180 / 3.1415f);
		//	Novice::ScreenPrintf(10, 30, "%.3f", coefficient);
		//}
		//Novice::ScreenPrintf(10, 130, "%.3f",input.x * 100);
		//Novice::ScreenPrintf(10, 150, "%.3f",input.y * 100);

	//	Novice::GetMousePosition(&(cursor.x), &(cursor.y));
		frame+=1;
		if (frame >= 360) { frame -= 360; }
		//cursor.x = int(cosf(frame*3.1415f/180.f) * float(SCREENINFO_WIDTH )/ 3.f + float(SCREENINFO_WIDTH )/ 2.f);
		//cursor.y = int(sinf(frame*3.1415f/180.f) * float(SCREENINFO_HEIGHT)/ 3.f + float(SCREENINFO_HEIGHT)/ 2.f);
		///
		/// ↓更新処理ここから
		///

		if (preKeys[DIK_SPACE] || Novice::IsPressButton(0,kPadButton12))
		{
			camera->Shake(60);
		}
		camera->Update();
		player->Update();
		ballManager->Update();
		camera->AddPosition({ -cameraOffsetX, -cameraOffsetY });
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
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
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
