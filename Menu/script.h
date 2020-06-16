namespace Script {
    [[noreturn]] void main();

    //功能控制变量
    class Var {
    public:
        bool bGodMode = 0;
        bool bInfiniteAmmo = 0;
        bool bNoRagdoll = 0;
        //超级跳
        bool bSuperJump=0;
        int iWantedLevel = 0;
        //武器数组
        uint hWeapons[94] = {0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0x8BB05FD7, 0x440E4788, 0x4E875F73,
                             0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0,
                             0xCD274149, 0x94117305, 0x3813FC08, 0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39,
                             0x3656C8C1, 0x99AEEB3B, 0xBFD21232,
                             0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F,
                             0x97EA20B8, 0xAF3696A1, 0x2B5EF5EC, 0x917F6C8C, 0x917F6C8C, 0x2BE6766B, 0x78A97CD0,
                             0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, 0x1D073A89, 0x555AF99A,
                             0x7846A318, 0xE284C527, 0x9D61E50F, 0x9D61E50F, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D,
                             0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67,
                             0x7F229F94, 0x84D6FAFD, 0x624FE830, 0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683,
                             0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, 0xB1CA77B1, 0xA284510B,
                             0x4DD2DC56, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67,
                             0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8,
                             0x23C9F95C, 0xFDBC8A50, 0x497FACC3, 0x34A67B97, 0xFBAB5776, 0x060EC506, 0xBA536372};
    };

    //功能函数
    //地图通知
    void notify(char *str, ...);

    //无敌
    void GodMode(bool toggle);

    //无限子弹
    void InfiniteAmmo(bool toggle);

    //清除通缉等级
    void ClearWanted();

    //更改通缉等级
    void ChangeWantedLevel(int level);

    //摔不到
    void NoRagdoll(bool toggle);

    //给予全部武器
    void GiveAllWeapon();

    //全武器满子弹
    void GiveFullAmmo();
    //传送到标记点
    void Teleport_to_Mark();
    //获取标记点位置
    Vector3 get_blip_marker();
}