#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include<stdlib.h>
#include<time.h>
#include<player.h>
#include<Enemy.h>

const char kWindowTitle[] = "Shooting2000";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player* player = new Player();
	Enemy* enemy = new Enemy();

	//時間による乱数調整
	unsigned int currentTime = unsigned int(time(nullptr));
	srand(currentTime);

	//自機とオブジェクトの距離
	float playerToEnemyX = 0.0f;
	float playerToEnemyY = 0.0f;
	float playerToEnemy = 0.0f;
	//弾とオブジェクトの距離
	float bulletToEnemyX = 0.0f;
	float bulletToEnemyY = 0.0f;
	float bulletToEnemy = 0.0f;

	//背景画像の変数宣言
	int backSpeed = 5;
	int back1X = 0;
	int back1Y = 0;
	int back2X = 0;
	int back2Y = -720;
	int back3X = 0;
	int back3Y = 0;
	int back4X = 0;
	int back4Y = -720;
	int back5X = 0;
	int back5Y = 0;
	int back6X = 0;
	int back6Y = 0;
	int number = 0;
	//シーン管理用
	enum Scene {
		Scene1,
		Scene2,
		Scene3,
		Scene4
	};

	//テクスチャ

	int Back1 = Novice::LoadTexture("./images/C.png");
	int Back2 = Novice::LoadTexture("./images/C.png");
	int Back3 = Novice::LoadTexture("./images/C.png");
	int Back4 = Novice::LoadTexture("./images/C.png");
	int Back5 = Novice::LoadTexture("./images/WHITE.png");
	int Back6 = Novice::LoadTexture("./images/DeadScene.png");

	
	int START = Novice::LoadTexture("./images/START.png");
	int PUSH = Novice::LoadTexture("./images/PUSH.png");
	int SPACE = Novice::LoadTexture("./images/SPACE.png");
	int bullet = Novice::LoadTexture("./images/bullet.png");
	int gameOver = Novice::LoadTexture("./images/GAME OVER.png");
	int gameClear = Novice::LoadTexture("./images/GAMECLEAR.png");
	int title = Novice::LoadTexture("./images/TITLE.png");
	//被弾エフェクト
	int bakuhats = Novice::LoadTexture("./images/bakuhatu2.png");
	//弾
	int bulletRadius = 25;
	int bulletPosX = 0;
	int bulletPosY = 0;
	int bulletSpeedY = 10;
	//SE
	/*
	int enemyDeadSound = Novice::LoadAudio("./sounds/enemyDeadSound.wav");
	int shotSound = Novice::LoadAudio("./sounds/shotSound.wav");*/
	bool isBulletShot = true;//弾が撃たれているか
	//クリアタイマー
	int clearTimer = 0;
	int timer = 0;
	//スペシャルタイマー
	int specialTimer = 0;
	//自機の生存フラグ
	bool playerIsAlive = true;
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
		/// 傾きの決定


		switch (number) {
		case Scene1:
			player->Ini();
			enemy->Ini();


			if (back1Y > 720) {
				back1X = 0;
				back1Y = -720;
			}
			if (back2Y > 720) {
				back2X = 0;
				back2Y = -720;
			}

			back1Y = back1Y + backSpeed;
			back2Y = back2Y + backSpeed;

			if (Novice::CheckHitKey(DIK_SPACE) && !preKeys[DIK_SPACE]) {
				clearTimer = 0;
				specialTimer = 0;
				number = 1;

			}
			break;

		case Scene2:
			clearTimer++;
			specialTimer++;

			player->Update(keys);
			enemy->Update();
			

			//自機の初期化
		

		
			/// 自機の移動
		
			//背景処理
			if (back3Y > 720) {
				back3X = 0;
				back3Y = -720;
			}
			if (back4Y > 720) {
				back4X = 0;
				back4Y = -720;
			}

			back3Y = back3Y + backSpeed;
			back4Y = back4Y + backSpeed;


			
			//SPACEキーが押された瞬間に実行する処理

			if (isBulletShot == false) {
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
					//弾を発射する処理

					isBulletShot = true;
					bulletPosX = player->GetPos().x;
					bulletPosY = player->GetPos().y;
					//Novice::PlayAudio(shotSound, false, 1);

				}
			}

			if (isBulletShot == true) {

				bulletSpeedY = -20;
				if (bulletPosY <= 0) {
					bulletPosY = player->GetPos().x;
					isBulletShot = false;


				}

			}

			//弾の移動
			bulletPosY = bulletPosY + bulletSpeedY;

			//弾とエネミー１の衝突処理
			if (enemy->GetAlive()) {
				bulletToEnemyX = float(enemy->GetPos().x - bulletPosX);
				bulletToEnemyY = float(enemy->GetPos().x - bulletPosY);
				bulletToEnemy = sqrtf((bulletToEnemyX * bulletToEnemyX) + (bulletToEnemyY * bulletToEnemyY));
			}
			if ((enemy->GetRadius() + bulletRadius > bulletToEnemy) && isBulletShot) {
				bulletPosY = player->GetPos().y;
				enemy->SetAlive(false);
				isBulletShot = false;
			}
			
			


			//エネミー１のリポップ処理
			if (enemy->GetAlive() == false) {
				timer++;//毎フレームenemyDeadtimerに1加算する


				if (timer > 180) {//二秒経った時
					enemy->SetPos({ rand() % 1000 + 100,-200});
					
					enemy->SetAlive(true);

					timer = 0;
				}
			}
			
			
			//自機とオブジェクトの衝突処理
			if (enemy->GetAlive()) {
				playerToEnemyX = float(enemy->GetPos().x - player->GetPos().x);
				playerToEnemyY = float(enemy->GetPos().y - player->GetPos().y);
				playerToEnemy = sqrtf((playerToEnemyX * playerToEnemyX) + (playerToEnemyY * playerToEnemyY));

			}

			if (enemy->GetRadius() + player->GetRadius() >= playerToEnemy) {
				enemy->SetPos({-100,0});
			
				
				playerIsAlive = false;

			}
			
			

			

			//クリアのシーン切り替え
			if (number == 1 && clearTimer >= 2000) {
				number = 2;

			}

			//！クリアのシーン切り替え
			if (playerIsAlive == false) {
				playerIsAlive = true;

				number = 3;
			}

			break;
		case Scene3:
			if (number == 2) {
				if (Novice::CheckHitKey(DIK_SPACE) && !preKeys[DIK_SPACE]) {


					number = 0;
				}
			}


			break;


		case Scene4:
			if (number == 3) {

				if (Novice::CheckHitKey(DIK_SPACE) && !preKeys[DIK_SPACE]) {


					number = 0;
				}
				break;
			}




		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		switch (number) {

		case Scene1:
			Novice::DrawSprite(back1X, back1Y, Back1, 1.0f, 1.1f, 0.0f, WHITE);
			Novice::DrawSprite(back2X, back2Y, Back2, 1.0f, 1.1f, 0.0f, WHITE);
			Novice::DrawSprite(50, 200, title, 1.6f, 1.6f, 0.0f, WHITE);
			Novice::DrawSprite(360, 400, START, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(760, 440, PUSH, 0.5f, 0.5f, 0.0f, WHITE);
			Novice::DrawSprite(900, 440, SPACE, 0.5f, 0.5f, 0.0f, WHITE);

			break;
		case Scene2:

			Novice::DrawSprite(back3X, back3Y, Back3, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(back4X, back4Y, Back4, 1.0f, 1.0f, 0.0f, WHITE);
			enemy->Draw();
			player->Draw();

			//弾の描画
			if (isBulletShot) {


				Novice::DrawSprite(int(bulletPosX + 25), int(bulletPosY + 25), bullet, 0.3f, 0.3f, 0.0f, WHITE);

			}

			//自機
			//敵オブジェクト
			
			

			
			//爆破エフェクト
			if (timer >= 1 && timer <= 10)
			{
				Novice::DrawSprite(enemy->GetPos().x,enemy->GetPos().y, bakuhats, 1.5f, 1.5f, 0.0f, 0xffffffff);

			}
			
			

			break;

		case Scene3:
			Novice::DrawSprite(back5X, back5Y, Back5, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(250, 300, gameClear, 1.5f, 1.5f, 0.0f, WHITE);
			break;

		case Scene4:
			Novice::DrawSprite(back6X, back6Y, Back6, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite(250, 350, gameOver, 1.5f, 1.5f, 0.0f, WHITE);
			break;
		}
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
