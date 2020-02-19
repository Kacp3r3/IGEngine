#pragma once

enum class KeyState
{
	UNDEFINED = 0,
	PRESSED =   1,
	RELEASED =  2,
	HELD =      3
};

enum class Event
{
	CURSOR_ENTER_SCREEN,
	CURSOR_LEFT_SCREEEN,
	MOUSE_MOVE,
	MOUSE_SCROLL,
	MOUSE_KEY_DOWN,
	MOUSE_KEY_UP,
	MOUSE_KEY_HELD,
	KBD_KEY_DOWN,
	KBD_KEY_UP,
	KBD_KEY_HELD
};

enum class Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

enum class Display
{
	PRIMARY=1,
	SECONDARY=2
};

enum class MeshType
{
	MESH,
	OBJ
};