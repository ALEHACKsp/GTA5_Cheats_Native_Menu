#pragma once

enum SubMenus;

struct VECTOR2 {
	float x, y;
};
struct VECTOR2_2 {
	float w, h;
};
struct RGBAF {
	int r, g, b, a, f, y;
};
struct RGBA {
	int r, g, b, a;
};
struct RGB {
	int r, g, b;
};

namespace Menu {
    //绘制
	namespace Drawing {
		void Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Title(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
		void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);

	}
	//设置
	namespace Settings {
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;

		extern int maxVisOptions;
		extern int currentOption;
		extern int optionCount;
		extern SubMenus currentMenu;
		extern int menuLevel;
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];

		extern float menuX;

		extern RGBAF titleText;
		extern RGBAF titleText2;
		extern RGBA line;
		extern RGBA lines;
		extern RGBAF title_end;
		extern RGBA titleRect;
		extern RGBAF integre;
		extern RGBAF integre2;
		extern RGBAF count;
		extern RGBAF SelectedText;
		extern RGBAF arrow;
		extern RGBA titleEnd;
		extern RGBAF arrow2;
		extern RGBAF breakText;
		extern RGBAF optionText;
		extern RGBA optionRect;
		extern RGBA lanseRect;
		extern RGBA scroller;

		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int keyPressDelay2;
		extern int keyPressPreviousTick2;
		extern int keyPressDelay3;
		extern int keyPressPreviousTick3;
	}
	namespace MenuLevelHandler {
		void MoveMenu(SubMenus menu);
		void BackMenu();
	}
	namespace Checks {
		void Keys();
	}
	namespace Tools {
		char* StringToChar(std::string string);

	}
	void DRAW_TEXTURE(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
	void Title(const char * title);
	void info(const char * title);
	void Vehicle(std::string texture1, std::string texture2);
	void Vehicle2(std::string texture1, std::string texture2);
	void Colorbox(std::string texture1, std::string texture2, RGBA rgba);
	void Colorbox2(std::string texture1, std::string texture2, int r, int g, int b, int a);
	bool Break(const char * option);
	bool Option(const char* option, std::function<void()> function);
	bool Option(const char* option);
	bool Option(const char* option, std::function<void()> function, const char* car, const char* cars);
	bool MenuOption(const char* option, SubMenus newSub);;
	bool MenuOption(const char* option, SubMenus newSub, std::function<void()> function);
	bool Bool(const char* option, bool& b00l);
	bool Bool(const char* option, bool& b00l, std::function<void()> function);
	bool Int(const char* option, int& _int, int min, int max);
	bool Int(const char* option, int& _int, int min, int max, int step);
	bool Int(const char* option, int& _int, int min, int max, std::function<void()> function);
	bool Int(const char* option, int& _int, int min, int max, int step, std::function<void()> function);
	bool Float(const char* option, float& _float, int min, int max);
	bool Float(const char* option, float& _float, int min, int max, int step);
	bool Float(const char* option, float& _float, int min, int max, std::function<void()> function);
	bool Float(const char* option, float& _float, int min, int max, int step, std::function<void()> function);
	bool IntVector(const char* option, std::vector<int> Vector, int& position);
	bool IntVector(const char* option, std::vector<int> Vector, int& position, std::function<void()> function);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position, std::function<void()> function);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position, std::function<void()> function);
	bool StringVector(const char* option, std::vector<char*> Vector, int& position);
	bool StringVector(const char* option, std::vector<char*> Vector, int& position, std::function<void()> function);
	void End();
}