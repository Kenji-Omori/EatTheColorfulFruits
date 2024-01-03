#pragma once
#include <Vector2.h>
#include <Vector2Int.h>

enum KeyCode
{
	Ok,
	Cancel,
	Exit,
};

enum StickCode
{
	Main,
	Sub
};

class Controller
{
public:
	Controller();
	~Controller();
	void Update();
	bool IsKeyDown(KeyCode code);
	bool IsKey(KeyCode code);
	bool IsKeyUp(KeyCode code);
	Vector2 GetStick(StickCode code);
	Vector2Int GetMousePosition();

private:
	int CodeToKey(KeyCode code);
	int CodeToButtonBit(KeyCode code);
	void UpdateSticks();

	bool IsDownPreKey(KeyCode code);
	bool IsDownCurKey(KeyCode code);
	bool IsDownPreButton(KeyCode code);
	bool IsDownCurButton(KeyCode code);

	char curKeys_[256] = {0};
	char preKeys_[256] = {0};

	int curButtons_ = 0;
	int preButtons_ = 0;

	Vector2 mainStick_;
	Vector2 subStick_;

	const int maxButtonsNum = 20;
};


