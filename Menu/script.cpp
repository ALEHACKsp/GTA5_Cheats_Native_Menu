#include "main.h"
Script::Var *v=new Script::Var;
//noreturn 不返回值
[[noreturn]] void Script::main(){
    notify((char*)"Hello,%s",PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()));
    while(true){
        //键位设置
        Menu::Checks::Keys();
        //菜单部分
        switch (Menu::Settings::currentMenu) {
            case mainmenu:
                Menu::Title("主菜单");
                Menu::MenuOption("玩家选项",player_option);
                Menu::MenuOption("传送选项",teleport_option);
                break;
                //玩家选项
                case player_option:
                    Menu::Title("玩家选项");
                    Menu::MenuOption("武器选项",weapon_option);
                    Menu::Bool("无敌",v->bGodMode,[]{GodMode(v->bGodMode);});
                    Menu::Option("清除通缉",[]{ClearWanted();});
                    //获取当前通缉
                    v->iWantedLevel=PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
                    Menu::Int("通缉等级",v->iWantedLevel,0,5,[]{ChangeWantedLevel(v->iWantedLevel);});
                    Menu::Bool("超级跳",v->bSuperJump);
                    Menu::Bool("摔不到",v->bNoRagdoll,[]{NoRagdoll(v->bNoRagdoll);});
                    break;
                    //武器选项
                    case weapon_option:
                        Menu::Title("武器选项");
                        Menu::Option("给予全武器",[]{GiveAllWeapon();});
                        Menu::Option("全武器满子弹",[]{GiveFullAmmo();});
                        Menu::Bool("无限子弹",v->bInfiniteAmmo,[]{InfiniteAmmo(v->bInfiniteAmmo);});
                        break;
                        //传送选项
                        case teleport_option:
                            Menu::Title("传送选项");
                            Menu::Option("传送到标记点",[]{Teleport_to_Mark();});
                            break;
        }
        Menu::End();
        //因为玩家死了会重置这些操作 所以需要判断下
        if(PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID())){
            //玩家死亡后等待1秒
            Hook::WAIT(1000);
            //重新恢复功能
            GodMode(v->bGodMode);
            InfiniteAmmo(v->bInfiniteAmmo);
            NoRagdoll(v->bNoRagdoll);
        }
        if(v->bSuperJump){
            //如果是true那么每帧都能 超级跳
            GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
        }
       Hook::WAIT(0);
    }
}
//地图上Toast通知
void Script::notify(char* str,...){
    va_list list;
    char Str[512];
    char Params[512];
    va_start(list, str);
    _vsnprintf_s(Params, sizeof(Params), str, list);
    va_end(list);
    sprintf_s(Str, "%s", Params);
    UI::SET_TEXT_OUTLINE();
    UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
    UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Str);
    UI::_DRAW_NOTIFICATION(FALSE, FALSE);
}
//无敌
void Script::GodMode(bool toggle){
    ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(),toggle);
}
//无限子弹
void Script::InfiniteAmmo(bool toggle){
    Hash *currentWeapon =new Hash();
    WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(),currentWeapon,false);
    //给手持武器设置满子弹
    WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(),*currentWeapon,9999);
    //无限子弹
    WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(),toggle);
}
//清除通缉等级
void Script::ClearWanted() {
    PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
}
//更改通缉等级
void Script::ChangeWantedLevel(int level){
    //设置通缉等级
    PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID(),level,false);
    //立刻生效
    PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(),false);
}
//摔不到
void Script::NoRagdoll(bool toggle) {
    if(toggle){
        Ped ped = PLAYER::PLAYER_PED_ID();
        Player player = PLAYER::PLAYER_ID();
        //布娃娃
        PED::SET_PED_CAN_RAGDOLL(ped, false);
        //撞击
        PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(ped, false);
        //飞出车辆
        PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, false);
        //布娃娃控制
        PLAYER::GIVE_PLAYER_RAGDOLL_CONTROL(player, true);
        //碰撞
        PED::SET_PED_RAGDOLL_ON_COLLISION(ped, false);
    }else{
        Ped ped = PLAYER::PLAYER_PED_ID();
        Player player = PLAYER::PLAYER_ID();
        //布娃娃
        PED::SET_PED_CAN_RAGDOLL(ped, true);
        //撞击
        PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(ped, true);
        //飞出车辆
        PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, true);
        //布娃娃控制
        PLAYER::GIVE_PLAYER_RAGDOLL_CONTROL(player, false);
        //碰撞
        PED::SET_PED_RAGDOLL_ON_COLLISION(ped, true);
    }
}
//给予全武器
void Script::GiveAllWeapon() {
    for (int i = 0; i < (sizeof(v->hWeapons) / 4); i++) {
        WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), v->hWeapons[i], 9999, true);
    }
}
//给予全武器满子弹
void Script::GiveFullAmmo() {
    for (int i = 0; i < (sizeof(v->hWeapons) / 4); i++) {
        WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), v->hWeapons[i], 9999);
    }
}
void Teleport_Vector3(Player player,Vector3 coords){
    ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, coords.x, coords.y, coords.z, 0, 0,1);
    Hook::WAIT(0);
}
void Script::Teleport_to_Mark() {
    Vector3 coords=get_blip_marker();
    if (coords.x==0&&coords.y==0) {
        notify((char*)"未找到标记点!");
        return;
    }
    Entity player=PLAYER::PLAYER_PED_ID();
    //如果玩家在车内
    if(PED::IS_PED_IN_ANY_VEHICLE(player,false)){
        //把目标从玩家转到车辆 直接传送车子
        player=PED::GET_VEHICLE_PED_IS_USING(player);
    }
        bool groundFound = false;
        static float groundCheckHeight[] = {10.0,30.0, 50.0,60.0, 80.0,100.0, 120.0,150.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0,
                                            550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0};
        for (int i = 0; i < sizeof(groundCheckHeight) / 4; i++) {
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, coords.x, coords.y, groundCheckHeight[i], 0, 0,
                                                1);
            Hook::WAIT(100);
            //检测坐标高度中的准确坐标
            if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, true)) {
                groundFound = true;
                coords.z += 3.0;
                Teleport_Vector3(player,coords);
                break;
            }
        }
        //如果不在地面 就往下传送 触发虚空传送
        if (!groundFound) {
            coords.z = -150.0;
        }
}
//获取标记
//https://www.unknowncheats.me/forum/grand-theft-auto-v/307084-waypoint-coord.html
Vector3 Script::get_blip_marker()
{
    static Vector3 markCoords;
    Vector3 coords;

    bool blipFound = false;
    // search for marker blip
    int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
    for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
    {
        if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
        {
            coords = UI::GET_BLIP_INFO_ID_COORD(i);
            blipFound = true;
            break;
        }
    }
    if (blipFound)
    {
        return coords;
    }
    return markCoords;
}