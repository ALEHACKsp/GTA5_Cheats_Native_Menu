typedef bool(__cdecl* fpIsDLCPresent)();
class Hook{
public:
    static void InitConsole();
    static void Start(HMODULE hModule);
    static void FindPatterns();
    static BOOL InitializeHooks();
    static bool HookNatives();
    static void onTickInit();
    static eGameState GetGameState();
    static BlipList* GetBlipList();
    static uint64_t getWorldPtr();
    static void Cleanup();
    static void FailPatterns(const char* name);
    static void WAIT(DWORD ms);
    __int64 static * getGlobalPatern(int index);
    //变量
    static uint64_t* m_frameCount;
    static std::vector<LPVOID>		m_hooks;
    ////////////////////////////////////
    static fpIsDLCPresent			is_DLC_present;

    typedef void(__cdecl* NativeHandler)(scrNativeCallContext* context);
    struct NativeRegistration
    {
        uint64_t nextRegistration1;
        uint64_t nextRegistration2;
        Hook::NativeHandler handlers[7];
        uint32_t numEntries1;
        uint32_t numEntries2;
        uint64_t hashes;

        inline NativeRegistration* getNextRegistration()
        {
            uintptr_t result;
            auto v5 = reinterpret_cast<uintptr_t>(&nextRegistration1);
            auto v12 = 2LL;
            auto v13 = v5 ^ nextRegistration2;
            auto v14 = (char*)& result - v5;
            do
            {
                *(DWORD*)& v14[v5] = v13 ^ *(DWORD*)v5;
                v5 += 4LL;
                --v12;
            } while (v12);

            return reinterpret_cast<NativeRegistration*>(result);
        }
        inline uint32_t getNumEntries()
        {
            return ((uintptr_t)& numEntries1) ^ numEntries1 ^ numEntries2;
        }
        inline uint64_t getHash(uint32_t index)
        {
            auto naddr = 16 * index + reinterpret_cast<uintptr_t>(&nextRegistration1) + 0x54;
            auto v8 = 2LL;
            uint64_t nResult;
            auto v11 = (char*)& nResult - naddr;
            auto v10 = naddr ^ *(DWORD*)(naddr + 8);
            do
            {
                *(DWORD*)& v11[naddr] = v10 ^ *(DWORD*)(naddr);
                naddr += 4LL;
                --v8;
            } while (v8);

            return nResult;
        }
    };
    static NativeHandler GetNativeHandler(uint64_t origHash);
};