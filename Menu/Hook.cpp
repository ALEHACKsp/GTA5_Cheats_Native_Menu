#include "main.h"

HMODULE BaseModule=NULL;
HANDLE mainFiber;
DWORD wakeAt;

static eGameState *m_gameState;
static uint64_t  m_worldPtr;
static BlipList *m_blipList;
static Hook::NativeRegistration**						m_registrationTable;
static std::unordered_map<uint64_t,Hook::NativeHandler>	m_handlerCache;
std::vector<LPVOID>		Hook::m_hooks;
uint64_t* Hook::m_frameCount;
fpIsDLCPresent			Hook::is_DLC_present;
fpGetLabelText Hook::GetLabelText;
//初始化控制台
void Hook::InitConsole(){
    if(AllocConsole()){
        freopen("CONOUT$", "wb", stdout);
        SetConsoleTitleA("Output");
    }else{
        exit(0);
    }
}
//开始Hook
void Hook::Start(HMODULE hModule){
    BaseModule=hModule;
    //初始化控制台
    InitConsole();
    Log::Info("Console Created!");
    Log::Info("Start Find Patterns...");
    //开始查找Patterns
    FindPatterns();
    if (!InitializeHooks()) Cleanup();
}
void Hook::WAIT(DWORD ms)
{
    wakeAt = timeGetTime() + ms;
    SwitchToFiber(mainFiber);
}
//脚本主体
void ScriptMain(){
    srand(GetTickCount());
    Script::main();
}
//查找Patterns
void Hook::FindPatterns() {
    HANDLE steam = GetModuleHandleA("steam_api64.dll");
    if (!steam)Log::Info("Not Steam.");

    auto p_activeThread = Memory::pattern("E8 ? ? ? ? 48 8B 88 10 01 00 00");
    Log::Info("Find p_activeThread");

    auto p_blipList = Memory::pattern("4C 8D 05 ? ? ? ? 0F B7 C1");
    Log::Info("Find p_blipList");

    auto p_fixVector3Result = Memory::pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18");
    Log::Info("Found p_fixVector3Result");

    auto p_gameLegals = Memory::pattern("72 1F E8 ? ? ? ? 8B 0D");
    Log::Info("Found p_gameLegals");

    auto p_gameLogos = Memory::pattern("70 6C 61 74 66 6F 72 6D 3A");
    Log::Info("Found p_gameLogos");

    auto p_gameState = Memory::pattern("83 3D ? ? ? ? ? 8A D9 74 0A");
    Log::Info("Found p_gameState");

    auto p_nativeTable = Memory::pattern("76 32 48 8B 53 40 48 8D 0D");
    Log::Info("Found p_nativeTable");

    auto p_worldPtr = Memory::pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
    Log::Info("Found p_worldPtr");

    auto p_globalPtr = Memory::pattern("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11");
    Log::Info("Found p_globalPtr");

    auto p_eventHook = Memory::pattern(
            "48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03");
    Log::Info("Found p_eventHook");

    HookTool::setPat<uint64_t>("frame count",
                               (char*)"\x8B\x15\x00\x00\x00\x00\x41\xFF\xCF",
                               (char*)"xx????xxx",
                               &Hook::m_frameCount,
                               true,
                               2);
    Log::Info("Found frame_count");


    HookTool::setFn<fpIsDLCPresent>("is_DLC_present",
                                    (char*)"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x81\xF9\x00\x00\x00\x00",
                                    (char*)"xxxx?xxxxxxx????",
                                    &Hook::is_DLC_present);
    Log::Info("Found is_DLC_present");


    char* c_location = nullptr;
    void* v_location = nullptr;
    Sleep(5000);
    // 游戏状态地址
    c_location = p_gameState.count(1).get(0).get<char>(2);
    if(c_location==nullptr)FailPatterns("gameState");
    else{
        m_gameState = reinterpret_cast<decltype(m_gameState)>(c_location + *(int32_t*)c_location + 5);
        Log::Info("Get m_gameState");
    }
    //跳过Logo
    Memory::putVP<uint8_t>(p_gameLogos.count(1).get(0).get<void>(0), 0xC3);

    auto void_location = p_fixVector3Result.count(1).get(0).get<void>(0);
    if (void_location != nullptr) scrNativeCallContext::SetVectorResults = (void(*)(scrNativeCallContext*))(void_location);
    Log::Info("Get void_location");
    // 世界指针地址
    c_location = p_worldPtr.count(1).get(0).get<char>(0);
    if(c_location == nullptr)FailPatterns("world Pointer");
    else {
        m_worldPtr = reinterpret_cast<uint64_t>(c_location) +
                     *reinterpret_cast<int *>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;
        Log::Info("Get World Pointer");
    }
    //获取地图标记地址
    c_location = p_blipList.count(1).get(0).get<char>(0);
    if(c_location == nullptr)FailPatterns("blip List");else {
        m_blipList = (BlipList *) (c_location + *reinterpret_cast<int *>(c_location + 3) + 7);
        Log::Info("Get Blip List");
    }
    //Native函数表
    c_location = p_nativeTable.count(1).get(0).get<char>(9);
    if(c_location == nullptr)FailPatterns("native registration table");
    else
    {
        m_registrationTable = reinterpret_cast<decltype(m_registrationTable)>(c_location + *(int32_t *) c_location + 4);
        Log::Info("Get Native Function Table");
    }
    Log::Debug("Initializing natives..");
    CrossMapping::initNativeMap();
    Log::Info("Wait Game...");
    while(*m_gameState!=GameStatePlaying){
        Sleep(500);
    }
    Log::Info("Game Ready!");
}
//初始化钩子
BOOL Hook::InitializeHooks()
{
    BOOL returnVal = TRUE;
    // 初始化输入钩子
    if (!iHook.Initialize()) {
        Log::Error("Failed to initialize InputHook");
        returnVal = FALSE;
    }
    // 初始化MinHook
    if (MH_Initialize() != MH_OK) {
        Log::Error("MinHook failed to initialize");
        returnVal = FALSE;
    }
    //初始化native调用钩子
    if (!HookNatives()) {
        Log::Error("Failed to initialize NativeHooks");
        returnVal = FALSE;
    }
    return returnVal;
}
//寻找失败
void Hook::FailPatterns(const char* name)
{
    Log::Error("finding %s", name);
    Cleanup();
}
//Native处理器
Hook::NativeHandler _Handler(uint64_t origHash) {
    uint64_t newHash = CrossMapping::MapNative(origHash);
    if (newHash == 0) {
        return nullptr;
    }
    //函数表注册
    Hook::NativeRegistration * table = m_registrationTable[newHash & 0xFF];
    for (; table; table = table->getNextRegistration())
    {
        for (uint32_t i = 0; i < table->getNumEntries(); i++)
        {
            if (newHash == table->getHash(i))
            {
                return table->handlers[i];
            }
        }
    }
    return nullptr;
}
//获取Native 处理器
 Hook::NativeHandler Hook::GetNativeHandler(uint64_t origHash) {
    auto &handler = m_handlerCache[origHash];
    if (handler == nullptr) {
        handler = _Handler(origHash);
    }
    return handler;
}
//执行函数
void __stdcall ScriptFunction(LPVOID lpParameter)
{
    try
    {
        //调用函数主体
        ScriptMain();
    }
    catch (...)
    {
        Log::Error("Failed scriptFiber");
    }
}
void Hook::onTickInit()
{
    if (mainFiber == nullptr)
        mainFiber = ConvertThreadToFiber(nullptr);

    if (timeGetTime() < wakeAt)
        return;

    static HANDLE scriptFiber;
    if (scriptFiber)
        SwitchToFiber(scriptFiber);
    else
        scriptFiber = CreateFiber(0, ScriptFunction, nullptr);
}
fpIsDLCPresent	OG_IS_DLC_PRESENT = nullptr;
BOOL __cdecl HK_IS_DLC_PRESENT(Hash dlcHash)
{
    static uint64_t	last = 0;
    uint64_t		cur = *Hook::m_frameCount;
    if (last != cur)
    {
        last = cur;
        Hook::onTickInit();
    }
    else
        return OG_IS_DLC_PRESENT();
    return false;
}
fpGetLabelText ogGetLabelText = nullptr;

const char* hkGetLabelText(void* this_, const char* label)
{
    // 右下角加载部分
    if (strcmp(label, "HUD_JOINING") == 0)
    {
        return "Hook::正在加入中...";
    }
    return ogGetLabelText(this_, label);
}

//native挂钩
bool Hook::HookNatives()
{
    MH_STATUS status = MH_CreateHook((LPVOID)Hook::is_DLC_present, (LPVOID)HK_IS_DLC_PRESENT, (void**)& OG_IS_DLC_PRESENT);
    if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook((LPVOID)Hook::is_DLC_present) != MH_OK)
        return false;
    Hook::m_hooks.push_back((LPVOID)Hook::is_DLC_present);

    MH_STATUS statuslol = MH_CreateHook((LPVOID)Hook::GetLabelText, (LPVOID)hkGetLabelText, (void**)& ogGetLabelText);
    if (status != MH_OK || MH_EnableHook((LPVOID)Hook::GetLabelText) != MH_OK)
        return false;
    Hook::m_hooks.push_back((LPVOID)Hook::GetLabelText);
    Log::Info("Hook Successfully!");
    return true;
}
//获取游戏状态
eGameState Hook::GetGameState()
{
    return *m_gameState;
}
//地图标记列表
BlipList* Hook::GetBlipList()
{
    return m_blipList;
}
//世界指针
uint64_t Hook::getWorldPtr()
{
    return m_worldPtr;
}
void Hook::Cleanup()
{
    Log::Info("CleanUp");
    iHook.keyboardHandlerUnregister(OnKeyboardMessage);
    iHook.Remove();
    MH_Uninitialize();
    FreeLibraryAndExitThread(BaseModule, 0);
}