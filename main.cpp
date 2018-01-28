//
// アプリ雛形
//
// VisualStudioでもコンパイルできるようにするため
// ソースコードをUTF-8(BOM付き)で用意:D
//
#include "lib/framework.hpp"


enum Size {
	WIDTH = 1280,
	HEIGHT = 720
};

//以下、グローバル変数
double PlayerX, PlayerY;
double PvX, PvY;

//以下、関数の宣言
void Field(AppEnv& env);

int main() {
	AppEnv env(Size::WIDTH, Size::HEIGHT, Screen::DYNAMIC);//ウィンドウ生成
	while (env.isOpen()) {
		env.begin();

		Field(env);
		env.end();
	}
}
void Field(AppEnv& env)
{
	bool FieldEnd = false;
	bool LastMove = 0;//0=RIGHT,1=LEFT;
	bool Jumping = 0;
	int MoveKeep = 0;
	Texture Pose;
	Texture Stand1("res/Stand1.png");
	Texture Stand2("res/Stand2.png");
	Texture Run1("res/Run1.png");
	Texture Run2("res/Run2.png");
	Texture Jump("res/Jump.png");

	PlayerX = 0;
	PlayerY = 0;
	PvX = 0;
	PvY = 0;

	while (FieldEnd == false)
	{
		env.begin();

		drawFillBox(-640, -360, WIDTH, 60, Color(1, 1, 1));
		MoveKeep++;

		if (Jumping == true)
		{
			Pose = Jump;
			if (LastMove == 0)drawTextureBox(PlayerX, PlayerY, 86, 86, 0, 0, 86, 86, Pose, Color(1, 1, 1), 0, Vec2f(1, 1), Vec2f(43, 0));
			else drawTextureBox(PlayerX, PlayerY, 86, 86, 86, 0, -86, 86, Pose, Color(1, 1, 1), 0, Vec2f(1, 1), Vec2f(43, 0));
		}
		else if (PvX * PvX > 0.1)//もしも動いているならば
		{
			if (MoveKeep % 30 > 15)Pose = Run2;
			else Pose = Run1;
			if (PvX > 0)drawTextureBox(PlayerX, PlayerY, 86, 86, 0, 0, 86, 86, Pose, Color(1, 1, 1), 0, Vec2f(1, 1), Vec2f(43, 0));
			else drawTextureBox(PlayerX, PlayerY, 86, 86, 86, 0, -86, 86, Pose, Color(1, 1, 1), 0, Vec2f(1, 1), Vec2f(43, 0));
		}
		else //立ち止まっている
		{
			if (MoveKeep % 120 > 60)Pose = Stand2;
			else Pose = Stand1;
			if (LastMove == 0)drawTextureBox(PlayerX, PlayerY, 86, 86, 0, 0, 86, 86, Pose, Color(1, 1, 1), 0, Vec2f(1, 1), Vec2f(43, 0));
			else drawTextureBox(PlayerX, PlayerY, 86, 86, 86, 0, -86, 86, Pose, Color(1, 1, 1), 0, Vec2f(1, 1), Vec2f(43, 0));
		}
		PlayerX += PvX;
		PlayerY += PvY;
		PvY -= 0.5;
		PvX *= 0.8;

		if (PlayerY < -300)
		{
			Jumping = false;
			PvY = 0;
			PlayerY = -300;
		}

		if (env.isKeyPushed(' '))
		{
			Jumping = true;
			PvY += 10;
		}
		if (env.isKeyPressing(KEY_RIGHT))
		{
			LastMove = 0;
			PvX = 8;
		}
		if (env.isKeyPressing(KEY_LEFT))
		{
			LastMove = 1;
			PvX = -8;
		}
		env.end();
	}

}