#include <Novice.h>
#include <Enemy.h>
#include <math.h>

const char kWindowTitle[] = "LC1A_12_スヤマハナ";

bool Enemy::IsAlive;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int BulletTimer = 10;

	struct Vector2 {
		int x = 720;
		int y = 600;
	};

	struct Player {
		Vector2 pos;
	};
	Player player;

	struct Bullet {
		Vector2 pos;
		bool IsUse = 0;
	};
	Bullet bullet[50];

	Enemy enemyA;
	Enemy enemyB;
	enemyA.Pos.x = 300;
	enemyB.Pos.x = 600;
	enemyA.Pos.y = 200;
	enemyB.Pos.y = 300;

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

		if (Novice::CheckHitKey(DIK_W)) {
			player.pos.y -= 3;
		}
		if (Novice::CheckHitKey(DIK_A)) {
			player.pos.x -= 3;
		}
		if (Novice::CheckHitKey(DIK_S)) {
			player.pos.y += 3;
		}
		if (Novice::CheckHitKey(DIK_D)) {
			player.pos.x += 3;
		}

		if (Novice::CheckHitKey(DIK_R)) {
			enemyA.IsAlive = true;
		}

		if (Novice::CheckHitKey(DIK_SPACE)) {
			BulletTimer--;
			if (BulletTimer < 0) {
				for (int i = 0; i < 50; i++) {
					if (!bullet[i].IsUse) {
						bullet[i].IsUse = true;
						bullet[i].pos = player.pos;
						BulletTimer = 10;
						break;
					}
				}
			}
		}

		for (int i = 0; i < 50; i++) {
			if (bullet[i].IsUse) {
				bullet[i].pos.y -= 10;
				if (bullet[i].pos.y < 0) {
					bullet[i].IsUse = false;
				}
			}
		}

		for (int i = 0; i < 50; i++) {
			float A = enemyA.Pos.x - bullet[i].pos.x;
			float B = enemyA.Pos.y - bullet[i].pos.y;
			float Dis = sqrtf(A * A + B * B);
			if (Dis <= 10 + 30) {
				enemyA.IsAlive = false;
			}
		}
		for (int i = 0; i < 50; i++) {
			float A = enemyB.Pos.x - bullet[i].pos.x;
			float B = enemyB.Pos.y - bullet[i].pos.y;
			float Dis = sqrtf(A * A + B * B);
			if (Dis <= 10 + 30) {
				enemyB.IsAlive = false;
			}
		}


		enemyA.Update();
		enemyB.Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse(player.pos.x, player.pos.y, 30, 30, 0, WHITE, kFillModeSolid);
		for (int i = 0; i < 50; i++) {
			if (bullet[i].IsUse) {
				Novice::DrawEllipse(bullet[i].pos.x, bullet[i].pos.y, 10, 10, 0, RED, kFillModeSolid);
			}
		}
		Novice::ScreenPrintf(0, 0, "EnemyA IsAlive = %d", enemyA.IsAlive);
		Novice::ScreenPrintf(0, 20, "EnemyB IsAlive = %d", enemyB.IsAlive);
		Novice::ScreenPrintf(0, 40, "WASD : player Move");
		Novice::ScreenPrintf(0, 60, "shot : SPACE");
		Novice::ScreenPrintf(0, 80, "enemy respawn : R");


		enemyA.Draw();
		enemyB.Draw();

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
