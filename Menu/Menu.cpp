#include "main.h"

float Menu::Settings::menuX = 0.17f;
bool Menu::Settings::selectPressed = false;
bool Menu::Settings::leftPressed = false;
bool Menu::Settings::rightPressed = false;
int Menu::Settings::maxVisOptions = 16;
int Menu::Settings::currentOption = 0;
int Menu::Settings::optionCount = 0;
SubMenus Menu::Settings::currentMenu;
int Menu::Settings::menuLevel = 0;
int Menu::Settings::optionsArray[1000];
SubMenus Menu::Settings::menusArray[1000];
//字体颜色
RGBAF Menu::Settings::titleText{ 255, 255, 255, 255, 7 };
RGBAF Menu::Settings::titleText2{255,255,255,255,7};
//标题矩阵
RGBA Menu::Settings::titleRect{ 33,150,243,255 };
//中的
RGBAF Menu::Settings::integre{ 255, 255, 255, 255, 2 };
//综合
RGBAF Menu::Settings::integre2{ 255, 255, 255, 255, 2 };
RGBAF Menu::Settings::SelectedText{ 255, 255, 255, 255, 0 };
RGBAF Menu::Settings::count{ 255, 255, 255, 255, 6 };
//箭头
RGBAF Menu::Settings::arrow{ 255, 255, 255, 255, 3 };
//选中箭头
RGBAF Menu::Settings::arrow2{ 0, 151, 243, 255, 3 };
//break字体
RGBAF Menu::Settings::breakText{ 255, 255, 255, 255, 1 };
//尾部标题
RGBA Menu::Settings::titleEnd{ 0, 0, 0, 150 };
//标题结尾色
RGBAF Menu::Settings::title_end{ 255,255,255,255,4 };
//选项文字
RGBAF Menu::Settings::optionText{ 255, 255, 255, 255, 6 };
//选中条目的颜色
RGBA Menu::Settings::optionRect{ 20, 20, 20, 150 };
RGBA Menu::Settings::lanseRect{ 0, 0, 0, 255 };
RGBA Menu::Settings::scroller{ 33,150,243, 255 };
RGBA Menu::Settings::line{ 255,255,255,255 };
//最下面的条
RGBA Menu::Settings::lines{ 255,255,255,255 };


//绘制文字
void Menu::Drawing::Text(const char * text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}
//绘制标题
void Menu::Drawing::Title(const char * text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
    UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}
//绘制贴图
void Menu::Drawing::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}
//绘制方形
void Menu::Drawing::Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a);
}

namespace Globe
{
	int gGlareHandle; // int
	float gGlareDir;

	// Function(s)
	float conv360(float base, float min, float max) {
		// This is the function the script used. I just adapted it for C++.
		float fVar0;
		if (min == max) return min;
		fVar0 = max - min;

		if (base < min) base += fVar0;
		return base;
	}
	void drawGlare(float pX, float pY, float sX = 1, float sY = 1, int r = 255, int g = 255, int b = 255) {
		gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE((char*)"MP_MENU_GLARE");
		Vector3 rot = CAM::_GET_GAMEPLAY_CAM_ROT(2);
		float dir = conv360(rot.z, 0, 360);
		if ((gGlareDir == 0 || gGlareDir - dir > 0.5) || gGlareDir - dir < -0.5) {
			gGlareDir = dir;
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(gGlareHandle, (char*)"SET_DATA_SLOT");
			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(gGlareDir);
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
		}
		GRAPHICS::DRAW_SCALEFORM_MOVIE(gGlareHandle, pX, pY, sX, sY, r, g, b, 255, 0);

	}
};

void Menu::DRAW_TEXTURE(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}

//标题
void Menu::Title(const char * title)
{
    Drawing::Rect({33,150,243},{Settings::menuX, 0.0800f},{0.21f, 0.090f});
    Drawing::Rect(Settings::titleRect, { Settings::menuX, 0.0800f }, { 0.21f, 0.090f });
    Drawing::Spriter("commonmenu", "interaction_bgd", Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1065f, 0.21f, 0.035f, 180, Settings::titleEnd.r, Settings::titleEnd.g, Settings::titleEnd.b, Settings::titleEnd.a);
	Drawing::Text(title, Settings::optionText, { Settings::menuX, 0.128f }, { 0.32f, 0.32f }, true);
    UI::HIDE_HELP_TEXT_THIS_FRAME();
    CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
    UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
    UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
    UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
    UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
    UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
    //禁用控制
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
    CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
}
//选项
bool Menu::Option(const char* option)
{
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		Drawing::Text(option, onThis ? Settings::SelectedText : Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount) * 0.035f + 0.128f }, { 0.32f, 0.32f }, false);
		Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		if(onThis)Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f, }, { 0.21f, 0.035f });else return NULL;
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, onThis ? Settings::SelectedText : Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.128f }, { 0.32f, 0.32f }, false);
		Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		if(onThis)Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f, }, { 0.21f, 0.035f }); else return NULL;
	}
	if (Settings::currentOption == Settings::optionCount)
	{
		if (Settings::selectPressed)
		{
			return true;
		}
	}
	return false;
}
bool Menu::Break(const char * option)
{
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		Drawing::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount)*0.035f + 0.125f }, { 0.40f, 0.40f }, true);
		Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount)*0.035f + 0.1415f }, { 0.21f, 0.035f });
		if(onThis) Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f, }, { 0.21f, 0.035f });else return NULL;
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.125f }, { 0.40f, 0.40f }, true);
		Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.1415f }, { 0.21f, 0.035f });
		if(onThis)Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f, }, { 0.21f, 0.035f }); else return NULL;
	}
	return false;
}

bool Menu::Option(const char* option, std::function<void()> function, const char* car, const char* cars)
{
	Option(option);
	if (Menu::Settings::optionCount == Menu::Settings::currentOption)
	{
		Menu::Drawing::Spriter(car, cars, Menu::Settings::menuX + 0.21f, 0.2f, 0.15f, 0.15f, 0, 255, 255, 255, 255);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}
bool Menu::Option(const char* option, std::function<void()> function)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::MenuOption(const char* option, SubMenus newSub)
{
	Option(option);

	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		Drawing::Text("2", onThis ? Settings::arrow2 : Settings::arrow, { Settings::menuX + 0.099f, Settings::optionCount * 0.035f + 0.128f }, { 0.25f, 0.25f }, true);
	}
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text("2", onThis ? Settings::arrow2 : Settings::arrow, { Settings::menuX + 0.099f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.25f, 0.25f }, true);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		MenuLevelHandler::MoveMenu(newSub);
		return true;
	}
	return false;
}
bool Menu::MenuOption(const char * option, SubMenus newSub, std::function<void()> function)
{
	MenuOption(option, newSub);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}
//这个是专门用来处理玩家列表用的
//void Menu::PlayerListMenu(const char * option, SubMenus newSub)
//{
//	MenuOption(option, newSub);
//
//	if (Settings::selectPressed) {
//		if (Settings::optionCount == 1) {
//		Features::Online::selectedPlayer = Settings::currentOption-1;
//		}
//	}
//}
bool Menu::Bool(const char* option, bool& switch_bool)
{
	Option(option);
	if (switch_bool)
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("commonmenu", "shop_box_tick", Settings::menuX + 0.095f, (Settings::optionCount * 0.035f + 0.141f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("commonmenu", "shop_box_tick", Settings::menuX + 0.095f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
	}
	else
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("commonmenu", "shop_box_blank", Settings::menuX + 0.095f, (Settings::optionCount * 0.035f + 0.141f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("commonmenu", "shop_box_blank", Settings::menuX + 0.095f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f), 0.03f, 0.05f, 0, 255, 255, 255, 255);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		switch_bool ^= 1;
		return true;
	}
	return false;
}

bool Menu::Bool(const char* option, bool& b00l, std::function<void()> function)
{
	Bool(option, b00l);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}


bool Menu::Int(const char* option, int& _int, int min, int max)
{
	Option(option);
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			//左键处理
			//如果当前值小于min 就调整到最大 否则继续-1
			_int <= min ? _int = max : _int -= 1;
		}
		if (Settings::rightPressed) {
			//右键处理
			//如果当前值大于max 就调整到最小 否则继续+1
			_int >= max ? _int = min : _int += 1;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), onThis ? Settings::integre2 : Settings::integre, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.12f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Menu::Int(const char * option, int & _int, int min, int max, int step)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			//左键处理
			//如果当前值小于min 就调整到最大 否则继续-1
			_int <= min ? _int = max : _int -= 1;
		}
		if (Settings::rightPressed) {
			//右键处理
			//如果当前值大于max 就调整到最小 否则继续+1
			_int >= max ? _int = min : _int += 1;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::Int(const char* option, int& _int, int min, int max, std::function<void()> function)
{
	Int(option, _int, min, max);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}
bool Menu::Int(const char * option, int & _int, int min, int max, int step, std::function<void()> function)
{
	Int(option, _int, min, max, step);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}
bool Menu::Float(const char * option, float & _float, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float <= min ? _float = max : _float -= 0.1f;
		}
		if (Settings::rightPressed) {
			_float >= max ? _float = min : _float += 0.1f;
		}
		_float < min ? _float = max : _float > max ? _float = min : 0LL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.05f, Settings::optionCount * 0.035f + 0.128f }, { 0.3f, 0.3f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.05f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.3f, 0.3f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::Float(const char * option, float & _float, int min, int max, int step)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float <= min ? _float = max : _float -= 0.1f;
		}
		if (Settings::rightPressed) {
			_float >= max ? _float = min : _float += 0.1f;
		}
		_float < min ? _float = max : _float > max ? _float = min : 0LL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.05f, Settings::optionCount * 0.035f + 0.128f }, { 0.43f, 0.43f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.05f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Menu::Float(const char * option, float & _float, int min, int max, std::function<void()> function)
{
	Float(option, _float, min, max);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::Float(const char * option, float & _float, int min, int max, int step, std::function<void()> function)
{
	Float(option, _float, min, max, step);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::IntVector(const char * option, std::vector<int> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		int max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::IntVector(const char * option, std::vector<int> Vector, int & position, std::function<void()> function)
{
	IntVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::FloatVector(const char * option, std::vector<float> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::FloatVector(const char * option, std::vector<float> Vector, int & position, std::function<void()> function)
{
	FloatVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::StringVector(const char * option, std::vector<std::string> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::StringVector(const char * option, std::vector<std::string> Vector, int & position, std::function<void()> function)
{
	StringVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::StringVector(const char * option, std::vector<char*> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
#pragma warning(default: 4267)

bool Menu::StringVector(const char * option, std::vector<char*> Vector, int & position, std::function<void()> function)
{
	StringVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}
void Menu::info(const char * info)
{
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		if (bool onThis = true) {
			Drawing::Text(info, Settings::optionText, { Settings::menuX - 0.100f, 17 * 0.035f + 0.1600f }, { 0.25f, 0.25f }, false), Drawing::Rect(Settings::optionRect, { Settings::menuX, 17 * 0.035f + 0.1820f }, { 0.21f, 0.045f });
		}
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		if (bool onThis = true) {
			Drawing::Text(info, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.1300f }, { 0.25f, 0.25f }, false), Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1820f }, { 0.21f, 0.045f });
		}
	}
}

//结尾

void Menu::End()
{
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;
	float rate = 16.00 / (float)opcount;
	if (opcount >= 16) {
		Drawing::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.080f, 17 * 0.035f /*- 0.467f*/ + 0.125f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::lanseRect, { Settings::menuX, 17 * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		Drawing::Rect(Settings::lines, { Settings::menuX, 17 * 0.035f + 0.1235f }, { 0.21f, 0.002f });
	}
	else if (opcount > 0) {
		Drawing::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.080f, (Settings::optionCount + 1) * 0.035f /*- 0.467f*/ + 0.125f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::lanseRect, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		Drawing::Rect(Settings::lines, { Settings::menuX, (opcount + 1) * 0.035f + 0.1235f }, { 0.21f, 0.002f });
		}
}

void PlaySoundFrontend_default(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, (char*)"HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}
char * Menu::Tools::StringToChar(std::string string)
{
	return _strdup(string.c_str());
}

int Menu::Settings::keyPressDelay = 200;
int Menu::Settings::keyPressPreviousTick = GetTickCount();
int Menu::Settings::keyPressDelay2 = 150;
int Menu::Settings::keyPressPreviousTick2 = GetTickCount();
int Menu::Settings::keyPressDelay3 = 140;
int Menu::Settings::keyPressPreviousTick3 = GetTickCount();

#pragma warning(disable: 4018)
bool firstopen = true;
void Menu::Checks::Keys()
{
	Settings::selectPressed = false;
	Settings::leftPressed = false;
	Settings::rightPressed = false;
	if (GetTickCount() - Settings::keyPressPreviousTick > Settings::keyPressDelay) {
		if (GetTickCount() - Settings::keyPressPreviousTick2 > Settings::keyPressDelay2) {
			if (GetTickCount() - Settings::keyPressPreviousTick3 > Settings::keyPressDelay3) {
				if (IsKeyPressed(VK_F4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight)) {
					if(Settings::menuLevel == 0)MenuLevelHandler::MoveMenu(SubMenus::mainmenu);else if(Settings::menuLevel == 1)MenuLevelHandler::BackMenu();
					if (firstopen) {
						firstopen = false;
					}
					Settings::keyPressPreviousTick = GetTickCount();
				}
				//返回键
				else if (IsKeyPressed(VK_BACK) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel)) {
					if(Settings::menuLevel > 0) MenuLevelHandler::BackMenu();;
					if (Settings::menuLevel > 0)
						PlaySoundFrontend_default((char*)"BACK");
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (IsKeyPressed(VK_UP) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp)) {
					Settings::currentOption > 1 ? Settings::currentOption-- : Settings::currentOption = Settings::optionCount;
					if (Settings::menuLevel > 0)
						PlaySoundFrontend_default((char*)"NAV_UP_DOWN");
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (IsKeyPressed(VK_DOWN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown)) {
					Settings::currentOption < Settings::optionCount ? Settings::currentOption++ : Settings::currentOption = 1;
					if (Settings::menuLevel > 0)
						PlaySoundFrontend_default((char*)"NAV_UP_DOWN");
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (IsKeyPressed(VK_LEFT) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft)) {
					Settings::leftPressed = true;
					if (Settings::menuLevel > 0)
						PlaySoundFrontend_default((char*)"NAV_UP_DOWN");
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (IsKeyPressed(VK_RIGHT) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight)) {
					Settings::rightPressed = true;
					if (Settings::menuLevel > 0)
						PlaySoundFrontend_default((char*)"NAV_UP_DOWN");
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (IsKeyPressed(VK_RETURN) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Settings::selectPressed = true;
					if (Settings::menuLevel > 0)
					    PlaySoundFrontend_default((char*)"SELECT");
					Settings::keyPressPreviousTick = GetTickCount();
				}
				//热键处理
				HotKey::HotKeyMain();
			}
		}
	}
	Settings::optionCount = 0;
}
void Menu::MenuLevelHandler::MoveMenu(SubMenus menu)
{
	Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
	Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
	Settings::menuLevel++;
	Settings::currentMenu = menu;
	Settings::currentOption = 1;
}

void Menu::MenuLevelHandler::BackMenu()
{
	Settings::menuLevel--;
	Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
	Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
}
//------Colorbox----------------
void Menu::Colorbox2(std::string texture1, std::string texture2, int r, int g, int b, int a)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (Menu::Settings::optionCount == Menu::Settings::currentOption) { Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX + 0.24f, 0.2f, 0.11f, 0.11f, 0, r, g, b, a); }
	}
	else { if (Menu::Settings::optionCount == Menu::Settings::currentOption) { Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX - 0.24f, 0.2f, 0.11f, 0.11f, 0, r, g, b, a); } }
}
void Menu::Colorbox(std::string texture1, std::string texture2, RGBA rgba)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (Menu::Settings::optionCount == Menu::Settings::currentOption) { Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX + 0.24f, 0.2f, 0.11f, 0.11f, 0, rgba.r, rgba.g, rgba.b, rgba.a); }
	}
	else { if (Menu::Settings::optionCount == Menu::Settings::currentOption) { Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX - 0.24f, 0.2f, 0.11f, 0.11f, 0, rgba.r, rgba.g, rgba.b, rgba.a); } }
}
//---------Vehicle----------------
void Menu::Vehicle(std::string texture1, std::string texture2)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (Menu::Settings::optionCount == Menu::Settings::currentOption) { Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX + 0.24f, 0.2f, 0.11f, 0.11f, 0, 255, 255, 255, 255); }
	}
	else { if (Menu::Settings::optionCount == Menu::Settings::currentOption) { Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX - 0.24f, 0.2f, 0.11f, 0.11f, 0, 255, 255, 255, 255); } }
}
void Menu::Vehicle2(std::string texture1, std::string texture2)
{
	if (Menu::Settings::optionCount == Menu::Settings::currentOption) {
	    Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX - 0.24f, 0.362f, 0.15f, 0.18f, 0, 255, 255, 255, 255);
	}
}
