
#include "main.h"

void HotKey::HotKeyMain() {
    if(KeyJustUp(VK_F5)){
        Script::Teleport_to_Mark();
    }
}