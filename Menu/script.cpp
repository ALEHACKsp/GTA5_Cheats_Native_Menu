#include "main.h"
Script::Var *v=new Script::Var;
Script::Cars * vehicle=new Script::Cars;
//在线玩家
Online * online=new Online;
//事件指针
static std::vector<void*> EventPtr;
Cam cam;
static char EventRestore[82] = {};
//上次撞击的车辆
Vehicle Impactlast=0;
//noreturn 不返回值
[[noreturn]] void Script::main() {
    notify((char *) "Hello,%s", PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()));
    while (true) {
        //键位设置
        Menu::Checks::Keys();
        //菜单部分
        switch (Menu::Settings::currentMenu) {
            case mainmenu:
                Menu::Title("主菜单");
                Menu::MenuOption("玩家选项", player_option);
                Menu::MenuOption("在线玩家",online_option);
                Menu::MenuOption("全部玩家",all_player_option);
                Menu::MenuOption("保护选项",protect_option);
                Menu::MenuOption("传送选项", teleport_option);
                Menu::MenuOption("车辆选项", vehicle_option);
                Menu::MenuOption("线上修改", recovery_option);
                Menu::MenuOption("杂项", misc_option);
                break;
                //在线玩家
                case online_option:
                    Menu::Title("在线玩家");
                    //遍历战局玩家
                    for(int item=0;item<32;item++){
                        //获取玩家
                        Player Net_Player=PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(item);
                        //是否为玩家
                        if(PED::IS_PED_A_PLAYER(Net_Player)) {
                            if(Menu::MenuOption(PLAYER::GET_PLAYER_NAME(item),online_sub_option)){
                                online->selectPlayer=item;
                            }
                        }
                    }
                    break;
                    case all_player_option:
                        Menu::Title("所有玩家");
                        if(Menu::Option("给予全部武器")) {
                            for (int item = 0; item < 32; item++) {
                                Player Net_Player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(item);
                                if (PED::IS_PED_A_PLAYER(Net_Player)) {
                                    GiveAllWeapon(Net_Player);
                                }
                            }
                        }
                        Menu::Bool("无限子弹",online->bAllPlayerInfiniteAmmo);
                        break;
                    case online_sub_option:
                    {
                        Menu::Title("玩家操作");
                        Player selectPlayer=PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online->selectPlayer);
                        Menu::Break(PLAYER::GET_PLAYER_NAME(online->selectPlayer));
                        //不观看自己
                        if(selectPlayer != PLAYER::PLAYER_PED_ID())
                        if (Menu::Bool("观看", v->bSpectatePlayer)) Online::SpectatePlayer(v->bSpectatePlayer, selectPlayer);
                        Menu::MenuOption("友好选项",online_peaceful_option);
                        Menu::MenuOption("恶意选项",online_griefing_option);
                }
                        break;
                    //恶意
            case online_griefing_option:
            {
                Menu::Title("恶意选项");
                Player selectPlayer=PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online->selectPlayer);
                if(Menu::Option("爆炸")) Online::ExplosionPlayer(selectPlayer, 65535, eExplosionType::ExplosionTypeGrenade, 0,false,true);
                if(Menu::Option("爆炸+镜头摇晃")) Online::ExplosionPlayer(selectPlayer, 65535, eExplosionType::ExplosionTypeGrenade, 65535,false,true);
                if(Menu::Option("镜头摇晃")) Online::ExplosionPlayer(selectPlayer, 0, eExplosionType::ExplosionTypeGrenade, 65535,false,true);
                if(Menu::Option("喷水")) Online::ExplosionPlayer(selectPlayer, 5, eExplosionType::ExplosionTypeWaterHydrant, 0,true,false);
                if(Menu::Option("喷火")) Online::ExplosionPlayer(selectPlayer, 5, eExplosionType::ExplosionTypeFlame, 0,false,true);
                if(Menu::Option("火车撞击")) Online::VehicleImpact(selectPlayer);
                Menu::Bool("循环爆炸",online->bLoopExplosion);
                Menu::Bool("循环喷水",online->bLoopWater);
                Menu::Bool("循环喷火",online->bLoopFlame);
                if(Menu::Option("欢乐送")) Online::CoffinDance(selectPlayer);
                Menu::Bool("掉帧攻击",online->bDropFrame);
            }
            break;
                    //友好选项
            case online_peaceful_option: {
                Menu::Title("友好选项");
                Player selectPlayer=PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online->selectPlayer);
                if (Menu::Option("传送到玩家")) {
                    Vector3 c = ENTITY::GET_ENTITY_COORDS(selectPlayer, true);
                    c.z += 2;
                    Teleport_Vector3(PLAYER::PLAYER_PED_ID(), c);
                }
                if (Menu::Option("无伤害爆炸")) Online::ExplosionPlayer(selectPlayer, 0, eExplosionType::ExplosionTypeBullet, 0,false,true);
                //给予全武器
                if (Menu::Option("给予全武器")) GiveAllWeapon(selectPlayer);
            }
            break;
                //玩家选项
            case player_option:
                Menu::Title("玩家选项");
                Menu::MenuOption("武器选项", weapon_option);
                Menu::MenuOption("模型更改",player_model_option);
                if(Menu::Bool("无敌", v->bGodMode)) GodMode(v->bGodMode);
                Menu::Bool("子弹无敌",v->bGodMode2);
                Menu::Bool("永不通缉",v->bNeverWanted);
                if(Menu::Option("清除通缉")) ClearWanted();
                //获取当前通缉
                v->iWantedLevel = PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
                if(Menu::Int("通缉等级", v->iWantedLevel, 0, 5)) ChangeWantedLevel(v->iWantedLevel);
                Menu::Bool("超级跳", v->bSuperJump);
                if(Menu::Bool("摔不到", v->bNoRagdoll)) NoRagdoll(v->bNoRagdoll);
                Menu::IntBool("闲置回血速度",v->bRestoreHealth,v->iRestoreLevel,0,20,[]{
                    RestoreHealth(v->bRestoreHealth, v->iRestoreLevel);});
                Menu::IntBool("防弹衣恢复速度",v->bRestoreArmour,v->iArmourValue,1,10);
                break;
                //武器选项
            case weapon_option:
                Menu::Title("武器选项");
                if(Menu::Option("给予全武器")) GiveAllWeapon(PLAYER::PLAYER_PED_ID());
                if(Menu::Option("全武器满子弹")) GiveFullAmmo();
                if(Menu::Bool("无限子弹", v->bInfiniteAmmo)) InfiniteAmmo(v->bInfiniteAmmo);
                if(Menu::Bool("无限备用弹夹",v->bInfiniteSpareAmmo)) InfiniteSpareAmmo(v->bInfiniteSpareAmmo);
                break;
                //传送选项
            case teleport_option:
                Menu::Title("传送选项");
                if(Menu::Option("传送到标记点")) Teleport_to_Mark();
                if (Menu::Option("奇力耶德山")) {
                    Vector3 Coords;
                    Coords.x = 496.75f;
                    Coords.y = 5591.17f;
                    Coords.z = 795.03f;
                    Teleport_Vector3(PLAYER::PLAYER_PED_ID(), Coords);
                }
                if (Menu::Option("洛圣都国际机场")) {
                    Vector3 Coords;
                    Coords.x = -1102.2910f;
                    Coords.y = -2854.5160f;
                    Coords.z = 13.9467f;
                    Teleport_Vector3(PLAYER::PLAYER_PED_ID(), Coords);
                }
                if (Menu::Option("海面安全区")) {
                    Vector3 Coords;
                    Coords.x = -5002.2910f;
                    Coords.y = -6054.5160f;
                    Coords.z = 5.9467f;
                    Teleport_Vector3(PLAYER::PLAYER_PED_ID(), Coords);
                }
                if (Menu::Option("向上传送")) {
                    Vector3 coords=ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(),0,0,3);
                    Teleport_Vector3(PLAYER::PLAYER_PED_ID(), coords);
                }
                if (Menu::Option("向前传送")) {
                    Vector3 coords=ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(),0,3,0);
                    Teleport_Vector3(PLAYER::PLAYER_PED_ID(), coords);
                }
                break;
            case protect_option:
                Menu::Title("保护选项");
                Menu::MenuOption("常规防护",protect_general_option);
                Menu::MenuOption("崩溃防护", protect_crash_option);
                if(Menu::Option("重置线上男角色")) Script::ChangeModel("mp_m_freemode_01");
                if(Menu::Option("重置线上女角色")) Script::ChangeModel("mp_f_freemode_01");
                break;
            case protect_general_option:
                Menu::Title("常规防护");
                if(Menu::Bool("脚本踢出",online->bRemoteScriptKickEvent)){
                    Online::defuseEvent(RockstarEvent::REMOTE_SCRIPT_LEAVE_EVENT,online->bRemoteScriptKickEvent);
                }
                if(Menu::Bool("爆炸",online->bProtectExplosionEvent)){
                    Online::defuseEvent(RockstarEvent::EXPLOSION_EVENT,online->bProtectExplosionEvent);
                }
                if(Menu::Bool("天气更改",online->bWeatherEvent)){
                    Online::defuseEvent(RockstarEvent::GAME_WEATHER_EVENT,online->bWeatherEvent);
                }
                if(Menu::Bool("着火",online->bFireEvent)){
                    Online::defuseEvent(RockstarEvent::FIRE_EVENT,online->bFireEvent);
                }
                if(Menu::Bool("掉落物",online->bPickup_Event)){
                    Online::defuseEvent(RockstarEvent::REQUEST_PICKUP_EVENT,online->bPickup_Event);
                }
                if(Menu::Bool("邀请传送",online->bTP_Event)){
                    Online::defuseEvent(RockstarEvent::NETWORK_REQUEST_SYNCED_SCENE_EVENT,online->bTP_Event);
                    Online::defuseEvent(RockstarEvent::NETWORK_UPDATE_SYNCED_SCENE_EVENT,online->bTP_Event);
                    Online::defuseEvent(RockstarEvent::NETWORK_START_SYNCED_SCENE_EVENT,online->bTP_Event);
                }
                if(Menu::Bool("粒子",online->bPTFX_Event)){
                    Online::defuseEvent(RockstarEvent::NETWORK_PTFX_EVENT,online->bPTFX_Event);
                }
                if(Menu::Bool("删除全部武器",online->bRemoveAllWeaponsEvent)){
                    Online::defuseEvent(RockstarEvent::REMOVE_ALL_WEAPONS_EVENT,online->bRemoveAllWeaponsEvent);
                }
                if(Menu::Bool("给予武器",online->bGiveWeaponEvent)){
                    Online::defuseEvent(RockstarEvent::GIVE_WEAPON_EVENT,online->bGiveWeaponEvent);
                }
                if(Menu::Bool("时间更改",online->bClockEvent)){
                    Online::defuseEvent(RockstarEvent::GAME_CLOCK_EVENT,online->bClockEvent);
                }
                break;

            case player_model_option:
                Menu::Title("模型更改");
                Menu::MenuOption("动物",player_model_animal);
                for (auto model : v->Ped_List) {
                    if(Menu::Option(model)) Script::ChangeModel(model);
                }
                break;
            case player_model_animal:
                Menu::Title("动物");
                for (auto model : v->Ped_List_animal) {
                    if(Menu::Option(model)) Script::ChangeModel(model);
                }
                break;
            case protect_crash_option:
                Menu::Title("崩溃防护");
                if(Menu::Bool("安全空间",online->bSecurityCamera)) Online::SecurityCamera(online->bSecurityCamera);
                break;
            case vehicle_spawn_option:
                Menu::Title("刷出选项");
                Menu::Bool("刷出在车内",v->bSpawnInVehicle);
                break;
            case sub_vehicle_option:
                Menu::Title("载具选项");
                Menu::Bool("载具无敌",v->bVehicleGodMode);
                Menu::Bool("循环修车",v->bLoopFixVeh);
                break;
            case vehicle_option:
                Menu::Title("车辆选项");
                Menu::MenuOption("刷出选项",vehicle_spawn_option);
                Menu::MenuOption("载具选项",sub_vehicle_option);
                Menu::MenuOption("名钻赌场豪劫DLC", casinoHeist_dlc);
                Menu::MenuOption("名钻赌场DLC", diamond_dlc);
                Menu::MenuOption("末日豪劫", doomsday_DLC);
                Menu::MenuOption("南圣安地列斯超级赛", south_sport_series);
                Menu::MenuOption("竞技场之战DLC", arenawar_DLC);
                Menu::MenuOption("走私大暴走DLC", Smugglers_DLC);
                Menu::MenuOption("军火霸业DLC", Gunrunning_DLC);
                Menu::MenuOption("摩托车", motorcycles);
                Menu::MenuOption("自行车", cycles);
                Menu::MenuOption("经典跑车", sports_classics);
                Menu::MenuOption("超级跑车", super);
                Menu::MenuOption("跑车", sports);
                Menu::MenuOption("轿车", sedans);
                Menu::MenuOption("轿跑车", coupes);
                Menu::MenuOption("小型车辆", compacts);
                Menu::MenuOption("肌肉车", muscle);
                Menu::MenuOption("SUV", SUVs);
                Menu::MenuOption("军用车辆", military);
                Menu::MenuOption("越野车", off_road);
                Menu::MenuOption("工业车辆", industrial);
                Menu::MenuOption("警用车辆", emergency);
                Menu::MenuOption("公共服务车", services);
                Menu::MenuOption("商业车辆", commercial);
                Menu::MenuOption("公共事业车", utility);
                Menu::MenuOption("货车", vans);
                Menu::MenuOption("火车", trains);
                Menu::MenuOption("船", boats);
                Menu::MenuOption("直升机", helicopters);
                Menu::MenuOption("飞机", planes);

                break;

                //摩托刷出
            case motorcycles:
                Menu::Title("摩托车");
                for (auto car : vehicle->Motorcycles) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;

                //名钻赌场豪劫
            case diamond_dlc:
                Menu::Title("名钻赌场");
                for (auto car : vehicle->DiamondDLC) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //末日豪劫
            case doomsday_DLC:
                Menu::Title("末日豪劫");
                for (auto car : vehicle->DoomsdayDLC) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //名钻赌场
            case casinoHeist_dlc:
                Menu::Title("名钻赌场豪劫");
                for (auto car : vehicle->CasinoHeistDLC) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //SUV
            case SUVs:
                Menu::Title("SUV");
                for (auto car : vehicle->SUVs) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //竞技场之战
            case arenawar_DLC:
                Menu::Title("竞技场之战DLC");
                for (auto car : vehicle->ArenaWarDLC) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //船
            case boats:
                Menu::Title("船");
                for (auto car : vehicle->Boats) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //商业车辆
            case commercial:
                Menu::Title("商业车辆");
                for (auto car : vehicle->Commercial) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //小型车辆
            case compacts:
                Menu::Title("小型车辆");
                for (auto car : vehicle->Compacts) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //商业车辆
            case coupes:
                Menu::Title("商业车辆");
                for (auto car : vehicle->Coupes) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //自行车
            case cycles:
                Menu::Title("自行车");
                for (auto car : vehicle->Cycles) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //警用车辆
            case emergency:
                Menu::Title("警用车辆");
                for (auto car : vehicle->Emergency) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //直升机
            case helicopters:
                Menu::Title("直升机");
                for (auto car : vehicle->Helicopters) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //工业车辆
            case industrial:
                Menu::Title("工业车辆");
                for (auto car : vehicle->Industrial) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //军用车辆
            case military:
                Menu::Title("军用车辆");
                for (auto car : vehicle->Military) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //肌肉车
            case muscle:
                Menu::Title("肌肉车");
                for (auto car : vehicle->Muscle) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //越野车
            case off_road:
                Menu::Title("越野车");
                for (auto car : vehicle->OffRoad) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //飞机
            case planes:
                Menu::Title("飞机");
                for (auto car : vehicle->Planes) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //轿车
            case sedans:
                Menu::Title("轿车");
                for (auto car : vehicle->Sedans) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //公共服务车辆
            case services:
                Menu::Title("公共服务车辆");
                for (auto car : vehicle->Services) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //跑车
            case sports:
                Menu::Title("跑车");
                for (auto car : vehicle->Sports) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //运动跑车
            case south_sport_series:
                Menu::Title("运动跑车");
                for (auto car : vehicle->SportSeries) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //经典跑车
            case sports_classics:
                Menu::Title("经典跑车");
                for (auto car : vehicle->SportsClassics) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //超级跑车
            case super:
                Menu::Title("超级跑车");
                for (auto car : vehicle->Super) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //拖车
            case trailer:
                Menu::Title("拖车");
                for (auto car : vehicle->Trailer) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //火车
            case trains:
                Menu::Title("火车");
                for (auto car : vehicle->Trains) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //公共事业车
            case utility:
                Menu::Title("公共事业车");
                for (auto car : vehicle->Utility) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //货车
            case vans:
                Menu::Title("货车");
                for (auto car : vehicle->Vans) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //走私大暴走
            case Smugglers_DLC:
                Menu::Title("走私大暴走");
                for (auto car : vehicle->SmugglersDLC) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
                //军火霸业
            case Gunrunning_DLC:
                Menu::Title("军火霸业");
                for (auto car : vehicle->GunrunningDLC) {
                    if(Menu::Option(UI::_GET_LABEL_TEXT(car))) Spawn_Vehicle(car);
                }
                break;
            case misc_option:
                Menu::Title("杂项");
                Menu::Bool("显示坐标", v->bShowCoords);
                if(Menu::Option("离开战局到线下")) NETWORK::NETWORK_SESSION_LEAVE_SINGLE_PLAYER();
                if(Menu::Option("关闭GTA5")) exit(0);
                break;
                //线上恢复
            case recovery_option:
                Menu::Title("线上修改");
                if (Menu::Option("重置赌场冷却")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3_COMPLETEDPOSIX"), -1, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3_COMPLETEDPOSIX"), -1, true);
                    notify((char *) "完成!");
                }

                if (Menu::Option("完成赌场计划板1")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_BITSET1"), -1, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_BITSET1"), -1, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("完成赌场计划板2")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_BITSET0"), -1, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_BITSET0"), -1, true);
                    notify((char *) "完成!");
                }
                Menu::MenuOption("赌场任务方案", casino_scheme);
                Menu::MenuOption("赌场目标", casino_target);
                Menu::MenuOption("赌场车手分红", casino_driver);
                Menu::MenuOption("赌场枪手分红", casino_gun);
                Menu::MenuOption("赌场黑客分红", casino_hacker);

                if (Menu::Option("完成赌场杜根")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_DISRUPTSHIP"), 3, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_DISRUPTSHIP"), 3, true);
                }
                if (Menu::Option("获得赌场2级权限卡")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_KEYLEVELS"), 2, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_KEYLEVELS"), 2, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("重置赌场转盘")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MPPLY_LUCKY_WHEEL_USAGE"), 0, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("清除精神状态")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_PLAYER_MENTAL_STATE"), 0, 1);
                    notify((char *) "完成!");
                }
                break;
                //赌场方案
            case casino_scheme:
                Menu::Title("任务方案");
                if (Menu::Option("隐迹潜踪")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_APPROACH"), 1, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_APPROACH"), 1, true);
                    notify((char *) "已更改为 隐迹潜踪");
                }
                if (Menu::Option("兵不厌诈")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_APPROACH"), 2, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_APPROACH"), 2, true);
                    notify((char *) "已更改为 兵不厌诈");
                }
                if (Menu::Option("气势汹汹")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_APPROACH"), 3, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_APPROACH"), 3, true);
                    notify((char *) "已更改为 气势汹汹");
                }
                break;
                //赌场枪手
            case casino_gun:
                Menu::Title("枪手分红");
                if (Menu::Option("未选择")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWWEAP"), 0, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWWEAP"), 0, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("5%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWWEAP"), 1, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWWEAP"), 1, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("9%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWWEAP"), 2, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWWEAP"), 2, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("7%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWWEAP"), 3, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWWEAP"), 3, true);
                    notify((char *) "完成");
                }
                if (Menu::Option("10%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWWEAP"), 4, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWWEAP"), 4, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("8%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWWEAP"), 5, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWWEAP"), 5, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("0%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWWEAP"), 6, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWWEAP"), 6, true);
                    notify((char *) "完成!");
                }
                break;

                //赌场车手
            case casino_driver:
                Menu::Title("车手分红");
                if (Menu::Option("未选择")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWDRIVER"), 0, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWDRIVER"), 0, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("5%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWDRIVER"), 1, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWDRIVER"), 1, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("7%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWDRIVER"), 2, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWDRIVER"), 2, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("9%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWDRIVER"), 3, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWDRIVER"), 3, true);
                    notify((char *) "完成");
                }
                if (Menu::Option("6%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWDRIVER"), 4, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWDRIVER"), 4, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("10%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWDRIVER"), 5, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWDRIVER"), 5, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("0%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWDRIVER"), 6, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWDRIVER"), 6, true);
                    notify((char *) "完成!");
                }
                break;

            case casino_hacker:
                Menu::Title("黑客分红");
                if (Menu::Option("未选择")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWHACKER"), 0, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWHACKER"), 0, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("3%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWHACKER"), 1, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWHACKER"), 1, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("7%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWHACKER"), 2, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWHACKER"), 2, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("5%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWHACKER"), 3, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWHACKER"), 3, true);
                    notify((char *) "完成");
                }
                if (Menu::Option("10%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWHACKER"), 4, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWHACKER"), 4, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("9%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWHACKER"), 5, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWHACKER"), 5, true);
                    notify((char *) "完成!");
                }
                if (Menu::Option("0%")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_CREWHACKER"), 6, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_CREWHACKER"), 6, true);
                    notify((char *) "完成!");
                }
                break;
                //赌场目标
            case casino_target:
                Menu::Title("任务目标");
                if (Menu::Option("现金")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_TARGET"), 0, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_TARGET"), 0, true);
                    notify((char *) "已更改为 现金");
                }
                if (Menu::Option("黄金")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_TARGET"), 1, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_TARGET"), 1, true);
                    notify((char *) "已更改为 黄金");
                }
                if (Menu::Option("名画")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_TARGET"), 2, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_TARGET"), 2, true);
                    notify((char *) "已更改为 名画");
                }
                if (Menu::Option("钻石")) {
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP0_H3OPT_TARGET"), 3, true);
                    STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY((char *) "MP1_H3OPT_TARGET"), 3, true);
                    notify((char *) "已更改为 钻石");
                }
                break;
        }
        Menu::End();
        updateFeatures();
        Hook::WAIT(0);
    }
}
void Script::updateFeatures() {
    //持续检测功能
    //无敌
    if (v->bGodMode) GodMode(v->bGodMode);
    //无限子弹
    if (v->bInfiniteAmmo) InfiniteAmmo(v->bInfiniteAmmo);
    //摔不到
    if (v->bNoRagdoll) NoRagdoll(v->bNoRagdoll);
    //无限备用弹夹
    if (v->bInfiniteSpareAmmo) InfiniteSpareAmmo(v->bInfiniteSpareAmmo);
    //超级跳
    if (v->bSuperJump) {
        //如果是true那么每帧都能 超级跳
        GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
    }
    //永不通缉
    if (v->bNeverWanted) PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
    //显示坐标
    if (v->bShowCoords) {
        Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
        char out[32];
        sprintf(out, "X:%d Y:%d Z:%d", (int) coords.x, (int) coords.y, (int) coords.z);
        Menu::Drawing::Text(out, {255, 255, 255, 255}, {0.1f, 0.02f}, {0.36f, 0.36f}, true);
    }
    //防弹衣恢复
    if (v->bRestoreArmour) RestoreArmour(v->bRestoreArmour, v->iArmourValue);
    //循环套餐
    if (online->bLoopWater) {
        Player selectPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online->selectPlayer);
        Online::ExplosionPlayer(selectPlayer, 5, eExplosionType::ExplosionTypeWaterHydrant, 0, false, true);
    }
    if (online->bLoopExplosion) {
        Player selectPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online->selectPlayer);
        Online::ExplosionPlayer(selectPlayer, 65535, eExplosionType::ExplosionTypeGrenadeL, 2, false, true);
    }
    if (online->bLoopFlame) {
        Player selectPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online->selectPlayer);
        Online::ExplosionPlayer(selectPlayer, 5, eExplosionType::ExplosionTypeFlame, 0, false, true);
    }
    //车辆无敌
    if (v->bVehicleGodMode) VehicleGodMode(v->bVehicleGodMode);
    //锁血
    if (v->bGodMode2) {
        ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 400);
        PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 400);
    }
    //掉帧
    if (online->bDropFrame) {
        Player selectPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online->selectPlayer);
        Online::DropFrameAttack(selectPlayer);
    }
    //无限子弹
    if (online->bAllPlayerInfiniteAmmo) {
        Online::GiveAllPlayerFullAmmo();
    }
    //循环修车
    if(v->bLoopFixVeh){
        Vehicle veh=PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
        //修复
        VEHICLE::SET_VEHICLE_FIXED(veh);
        VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
        //清灰
        VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
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
    if(toggle) {
        ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 400);
        PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 400);
        ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
    }else{
        ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
    }
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
void Script::GiveAllWeapon(Ped player) {
    for (unsigned long hWeapon : v->hWeapons) {
        WEAPON::GIVE_DELAYED_WEAPON_TO_PED(player, hWeapon, 9999, true);
    }
}
//给予全武器满子弹
void Script::GiveFullAmmo() {
    for (unsigned long hWeapon : v->hWeapons) {
        WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), hWeapon, 9999);
    }
}
void Script::Teleport_Vector3(Ped player,Vector3 coords){
    if(PED::IS_PED_IN_ANY_VEHICLE(player,false)) {
        player=PED::GET_VEHICLE_PED_IS_USING(player);
    }
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
        static float groundCheckHeight[] = {20.0,40.0,60.0,100.0, 200.0, 300.0, 400.0, 500.0,600.0, 700.0, 800.0, 900.0};
        for (float i : groundCheckHeight) {
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, coords.x, coords.y, i, 0, 0,
                                                1);
            Hook::WAIT(100);
            //检测坐标高度中的准确坐标
            if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, i, &coords.z, true)) {
                groundFound = true;
                coords.z += 2.0;
                //检测到地面直接传送到坐标
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
//无限备用弹夹
void Script::InfiniteSpareAmmo(bool toggle) {
    if(toggle) {
        Hash *currentWeapon = new Hash();
        WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), currentWeapon, false);
        //给手持武器设置满子弹
        WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), *currentWeapon, 9999);
    }
}
//刷出车辆
void Script::Spawn_Vehicle(char *car_tag) {
    //没有这个刷部分车会消失
    *Hook::getGlobalPatern(4268190) = 1;
    *(int*)Hook::getGlobalPatern(1628955 + PLAYER::GET_PLAYER_INDEX()) |= (1 << 3);
    //获得车辆hash
    Hash vehicle_hash = GAMEPLAY::GET_HASH_KEY(car_tag);
    if(checkModel(vehicle_hash)){
        //玩家坐标偏移
        Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0, 6.0, 1);
        //创建车辆
        Vehicle veh = VEHICLE::CREATE_VEHICLE(vehicle_hash, pos.x, pos.y, pos.z,ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), true, true);
        //保持引擎开启
        VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
        VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
        DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
        Hook::WAIT(120);
        if(v->bSpawnInVehicle){
            PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
        }
        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicle_hash);
    }
}
//血量恢复
void Script::RestoreHealth(bool toggle, int level) {
    if(toggle){
        PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(PLAYER::PLAYER_ID(), (float)level);
    } else{
        PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(PLAYER::PLAYER_ID(), 1.0);
    }
}
//防弹衣恢复
void Script::RestoreArmour(bool toggle, int value) {
    if(toggle){
        PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(),value);
    }
}
//观看玩家
void Online::SpectatePlayer(bool toggle, Ped targetPlayer) {
    NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(toggle,targetPlayer);
}
//爆炸玩家
void Online::ExplosionPlayer(Ped targetPlayer, int damage, int type, int cam,bool Invisible,bool Audio) {
    Vector3 coords=ENTITY::GET_ENTITY_COORDS(targetPlayer,true);
    coords.z-=1;
    FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, type, (float)damage, Audio, Invisible, (float)cam);
}
//检查模型
bool Script::checkModel(Hash hash) {
    //镜像
    if (STREAMING::IS_MODEL_IN_CDIMAGE(hash)) {
        //模型有效
        if (STREAMING::IS_MODEL_VALID(hash)) {
            //请求模型
            STREAMING::REQUEST_MODEL(hash);
            while (!STREAMING::HAS_MODEL_LOADED(hash)) {
                Hook::WAIT(0);
            }
            //如果模型加载了
                return true;
        }
    }
        return false;
}
bool Script::checkAnim(char *dict) {
    if(!STREAMING::HAS_ANIM_DICT_LOADED(dict)) {
        STREAMING::REQUEST_ANIM_DICT(dict);
        while (!STREAMING::HAS_ANIM_DICT_LOADED(dict)) {
            Hook::WAIT(0);
        }
        return true;
    }
}
void Online::CoffinDance(Ped selectPlayer) {
    Hash hash = 0;
    Vector3 coords = ENTITY::GET_ENTITY_COORDS(selectPlayer, true);
    //棺材
    hash = GAMEPLAY::GET_HASH_KEY("prop_coffin_01");
    if (Script::checkModel(hash)) {
        Object coffin_obj = OBJECT::CREATE_OBJECT(hash, coords.x, coords.y, coords.z, true, true, true);
        //如果创建成功
        if (ENTITY::DOES_ENTITY_EXIST(coffin_obj)) {
            //开始附加
            ENTITY::ATTACH_ENTITY_TO_ENTITY(coffin_obj, selectPlayer, 31086, 0, 0, 0, 0, 0, 0, true,
                                            true, false, false, 2, true);
        }
    }
    //黑人
    hash = GAMEPLAY::GET_HASH_KEY("ig_fbisuit_01");
    if (Script::checkModel(hash)) {
        int block_offsetX[6]={1,-1,1,-1,1,-1};
        int block_offsetY[6]={0,0,1,1,-1,-1};
        for (int i = 0; i < 6; i++) {
            Ped block=PED::CREATE_PED(26,hash,coords.x,coords.y,coords.z,1,true,true);
            //设置无敌
            ENTITY::SET_ENTITY_INVINCIBLE(block, true);
            //https://los-santos-multiplayer.com/forum/3-discussions-generales/45-0-how-to-use-entity%3A%3Aplay-entity-anim%3F
            Script::checkAnim("mini@strip_club@idles@dj@base");
            AI::TASK_PLAY_ANIM(block,"mini@strip_club@idles@dj@base","base",4.0f,1.4f,-1,9,0,0,0,0);
            //如果创建成功
            if (ENTITY::DOES_ENTITY_EXIST(block)) {
                //开始附加
                ENTITY::ATTACH_ENTITY_TO_ENTITY(block, selectPlayer, 31086, block_offsetX[i], block_offsetY[i], 0, 0, 0, 0,
                                                true, true, false, false, 2, true);
            }
        }
    }
}
void Script::VehicleGodMode(bool toggle) {
    if(toggle) {
        if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true)) {
            ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
        }
    }else{
        if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), true)) {
            ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), false);
        }
    }
}
void Online::VehicleImpact(Ped selectPlayer) {
    //火车头
    Hash train=GAMEPLAY::GET_HASH_KEY("FREIGHT");
    if(Script::checkModel(train)) {
        //Y偏移-10
        Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(selectPlayer,0,-10,0);
        //获取高度旋转
        float rot = ENTITY::GET_ENTITY_ROTATION(selectPlayer, 0).z;
        if(Impactlast!=0) {
            //删除上一辆
           VEHICLE::DELETE_VEHICLE(&Impactlast);
        }
        coords.z-=1;
        //创建载具
        Vehicle veh=VEHICLE::CREATE_VEHICLE(train,coords.x,coords.y,coords.z,rot,true,true);
        Impactlast = veh;
        VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
        //给予700的向前速度
        VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 700.0);
    }
}
void Online::DropFrameAttack(Ped selectPlayer) {
        Hash vehHash = GAMEPLAY::GET_HASH_KEY("Blimp");
        if (Script::checkModel(vehHash)) {
            Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(selectPlayer, 0, 0, 13);
            Vehicle veh = VEHICLE::CREATE_VEHICLE(vehHash, coords.x, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(selectPlayer), true, true);
            ENTITY::SET_ENTITY_INVINCIBLE(veh,true);
    }
}
void Online::SecurityCamera(bool toggle) {
   // https://www.unknowncheats.me/forum/grand-theft-auto-v/144028-gta-reversal-thread-151.html
    if(toggle) {
        //创建相机
        cam= CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", true);
        //将相机设置到海面上空
        CAM::SET_CAM_COORD(cam, -5000.f, -6000.f, 1500.f);
        CAM::SET_CAM_ROT(cam, 90, 0, 20, 0);
        //渲染相机
        CAM::RENDER_SCRIPT_CAMS(true, true, 10, false, false);
        //激活相机
        CAM::SET_CAM_ACTIVE(cam, true);
    }else{
        CAM::DESTROY_CAM(cam,0);
        CAM::RENDER_SCRIPT_CAMS(false, false, 3000, true, false);
        //重置玩家模型 避免返回依然崩溃
        Script::ChangeModel("mp_m_freemode_01");
        Vector3 v3;
        v3.x=-5000.f;
        v3.y=-6000.f;
        v3.z=5.f;
        //传送到安全区避免二次伤害
        Script::Teleport_Vector3(PLAYER::PLAYER_PED_ID(),v3);
    }
}
//给予全武器满子弹
void Online::GiveAllPlayerFullAmmo() {
    for (int item = 0; item < 32; item++) {
        Player selectPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(online->selectPlayer);
        if (PED::IS_PED_A_PLAYER(selectPlayer)) {
            for (unsigned long hWeapon : v->hWeapons) {
                WEAPON::SET_PED_AMMO(selectPlayer, hWeapon, 9999);
            }
        }
    }
}
//事件拦截
void Online::defuseEvent(RockstarEvent event, bool toggle)
{
    char* p = (char*)EventPtr[event];
    if (toggle)
    {
        if (EventRestore[event] == 0)
            EventRestore[event] = p[0];
        *p = 0xC3;
    }
    else
    {
        if (EventRestore[event] != 0)
            * p = EventRestore[event];
    }
}

void Script::ChangeModel(char *name) {
    Hash h=GAMEPLAY::GET_HASH_KEY(name);
    if(Script::checkModel(h))
        PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(),h);
}