
#include "main.h"

void HotKey::HotKeyMain() {
    if(KeyJustUp(VK_F5)){
        Script::Teleport_to_Mark();
    }
    if(KeyJustUp(VK_F6)){
        NETWORK::NETWORK_SESSION_LEAVE_SINGLE_PLAYER();
    }
    if(KeyJustUp(VK_F7)){
        Vehicle veh= PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
        //修复
        VEHICLE::SET_VEHICLE_FIXED(veh);
        VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
        //清灰
        VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
    }
}