#include <iostream>
#include <raylib.h>
#include <vector>

#define PI 3.1415926538

struct Vec2
{
	double x, y;

	Vec2& operator -(Vec2 SubtractingVector)
	{
		Vec2 ReturnVector;
		ReturnVector.x = x - SubtractingVector.x;
		ReturnVector.y = y - SubtractingVector.y;

		return ReturnVector;
	}
	Vec2 operator +(Vec2 SubtractingVector)
	{
		Vec2 ReturnVector;
		ReturnVector.x = x + SubtractingVector.x;
		ReturnVector.y = y + SubtractingVector.y;

		return ReturnVector;
	}
};

struct Sprite
{
	Texture2D Texture;
	Vector2 Pos = {0,0};

	Sprite(std::string FileName, Vector2 Pos)
	{
		Texture = LoadTexture(FileName.c_str());
		this->Pos = Pos;
	}

	Sprite() {};

	void DrawSprite()
	{
		DrawTexture(Texture, Pos.x, Pos.y, WHITE);
	}
};

class Ship
{
public:
	Sprite Starship;
	Vec2 Position;
	Vec2 Thrust = { 0,0 };

	//if Wraping = 0 then bounce
	bool Wraping = 1;

	Ship()
	{
		Starship = Sprite(std::string("Starship.png"), { 500 - 50, 250 - 50 });
		Position.x = Starship.Pos.x;
		Position.y = Starship.Pos.y;
	}

	void SharePosition()
	{
		Starship.Pos.x = Position.x;
		Starship.Pos.y = Position.y;
	}

	void GetInput()
	{
		if (IsKeyDown(KEY_W))
		{
			Thrust = Thrust + Vec2{ 0, 0.1 * GetFrameTime() };
		}
		if (IsKeyDown(KEY_S))
		{
			Thrust = Thrust + Vec2{ 0, -0.1 * GetFrameTime() };
		}
		if (IsKeyDown(KEY_A))
		{
			Thrust = Thrust + Vec2{ 0.1 * GetFrameTime(), 0 };
		}
		if (IsKeyDown(KEY_D))
		{
			Thrust = Thrust + Vec2{ -0.1 * GetFrameTime(), 0 };
		}
		if (IsKeyDown(KEY_R))
		{
			Position.x = 500 - 50;
			Position.y = 250 - 50;
			Thrust = { 0 };
		}
		if (IsKeyPressed(KEY_E))
		{
			Wraping = !Wraping;
			std::cout << "Wrapping: " << Wraping << "\n";
		}
	}

	void Update()
	{
		GetInput();

		if (Wraping == 1)
		{
			//-100 if is sprite is fully off screen
			if (Position.x < -100)
			{
				Position.x = 1000;
			}
			//1000 is if sprite is on far right
			if (Position.x > 1000)
			{
				Position.x = -100;
			}

			if (Position.y < -100)
			{
				Position.y = 500;
			}

			if (Position.y > 500)
			{
				Position.y = -100;
			}
		}
		if (Wraping == 0)
		{
			if (Position.x < 0 || Position.x > 1000 - 100)
			{
				Thrust.x *= -1;
			}
			if (Position.y < 0 || Position.y > 500 - 100)
			{
				Thrust.y *= -1;
			}
		}
		Position = Position - Thrust;
		SharePosition();
		Starship.DrawSprite();
	}
};

int main()
{
	constexpr int Height = 500;
	constexpr int Width = 1000;

	InitWindow(Width, Height, "Starship");

	Ship Starship;
	Sprite Background(std::string("Background2.png"), {0,0});

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		Background.DrawSprite();
		Starship.Update();

		EndDrawing();
	}
}