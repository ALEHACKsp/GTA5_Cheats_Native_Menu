namespace Script {
    [[noreturn]] void main();
    //车辆名
    class Cars {
    public:
        //名钻赌场DLC
        char *DiamondDLC[21] = {
                "CARACARA2",
                "DRAFTER",
                "DYNASTY",
                "EMERUS",
                "GAUNTLET3",
                "GAUNTLET4",
                "HELLION",
                "ISSI7",
                "JUGULAR",
                "KRIEGER",
                "LOCUST",
                "NEBULA",
                "NEO",
                "NOVAK",
                "PARAGON",
                "PARAGON2",
                "PEYOTE2",
                "RROCKET",
                "THRAX",
                "ZION3",
                "ZORRUSSO"
        };
        //名钻赌场豪劫DLC更新
        char *CasinoHeistDLC[20] = {
                "asbo",
                "everon",
                "formula",
                "formula2",
                "furia",
                "imorgon",
                "jb7002",
                "kanjo",
                "komoda",
                "minitank",
                "outlaw",
                "rebla",
                "retinue2",
                "stryder",
                "sugoi",
                "sultan2",
                "vagrant",
                "vstr",
                "yosemite2",
                "zhaba"
        };
        //竞技场之战DLC
        char *ArenaWarDLC[46] = {
                "impaler", "toros", "tulip", "vamos", "deveste", "deviant", "rcbandito", "schlagen", "italigto",
                "bruiser", "bruiser2", "bruiser3", "brutus", "brutus2", "brutus3", "cerberus", "cerberus2", "cerberus3",
                "clique", "deathbike", "deathbike2",
                "deathbike3", "dominator4", "dominator5", "dominator6", "impaler2", "impaler3", "impaler4", "imperator",
                "imperator2", "imperator3", "issi4", "issi5", "issi6", "monster3", "monster4", "monster5", "scarab",
                "scarab2", "scarab3", "slamvan4", "slamvan5",
                "slamvan6", "zr380", "zr3802", "zr3803"
        };
        //船只
        char *Boats[21] = {
                "DINGHY", "DINGHY2", "DINGHY3", "DINGHY4", "JETMAX",
                "MARQUIS", "PREDATOR", "SEASHARK", "SEASHARK2", "SEASHARK3",
                "SPEEDER", "SPEEDER2", "SQUALO", "SUBMERSIBLE", "SUBMERSIBLE2",
                "SUNTRAP", "TORO", "TORO2", "TROPIC", "TROPIC2",
                "TUG"
        };
        //商业广告车辆
        char *Commercial[11] = {
                "BENSON", "BIFF", "HAULER", "MULE", "MULE2",
                "MULE3", "PACKER", "PHANTOM", "POUNDER", "STOCKADE",
                "STOCKADE3"
        };
        //小型车辆
        char *Compacts[8] = {
                "BLISTA", "BRIOSO", "DILETTANTE", "DILETTANTE2", "ISSI2",
                "PANTO", "PRAIRIE", "RHAPSODY"
        };
        //轿跑车
        char *Coupes[14] = {
                "COGCABRIO", "EXEMPLAR", "F620", "FELON", "FELON2",
                "JACKAL", "ORACLE", "ORACLE2", "SENTINEL", "SENTINEL2",
                "WINDSOR", "WINDSOR2", "ZION", "ZION2"
        };
        //自行车
        char *Cycles[7] = {
                "BMX", "CRUISER", "FIXTER", "SCORCHER", "TRIBIKE",
                "TRIBIKE2", "TRIBIKE3"
        };
        //警用
        char *Emergency[18] = {
                "AMBULANCE", "FBI", "FBI2", "FIRETRUK", "LGUARD",
                "PBUS", "PRANGER", "POLICE", "POLICE2", "POLICE3",
                "POLICE4", "POLICEB", "POLICEOLD1", "POLICEOLD2", "POLICET",
                "SHERIFF", "SHERIFF2", "RIOT"
        };
        //直升机
        char *Helicopters[22] = {
                "ANNIHILATOR", "BLIMP", "BLIMP2", "BUZZARD", "BUZZARD2",
                "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "CARGOBOB4", "FROGGER",
                "FROGGER2", "MAVERICK", "POLMAV", "SAVAGE", "SKYLIFT",
                "SUPERVOLITO", "SUPERVOLITO2", "SWIFT", "SWIFT2", "VALKYRIE",
                "VALKYRIE2", "VOLATUS"
        };
        //工业车辆
        char *Industrial[11] = {
                "BULLDOZER", "CUTTER", "DUMP", "FLATBED", "GUARDIAN",
                "HANDLER", "MIXER", "MIXER2", "RUBBLE", "TIPTRUCK",
                "TIPTRUCK2"
        };
        //军用
        char *Military[5] = {
                "BARRACKS", "BARRACKS2", "BARRACKS3", "CRUSADER", "RHINO"
        };
        //摩托
        char *Motorcycles[46] = {
                "AKUMA", "AVARUS", "BAGGER", "BATI", "BATI2",
                "BF400", "CARBONRS", "CHIMERA", "CLIFFHANGER", "DAEMON",
                "DAEMON2", "DEFILER", "DOUBLE", "ENDURO", "ESSKEY",
                "FAGGIO", "FAGGIO2", "FAGGIO3", "GARGOYLE", "HAKUCHOU",
                "HAKUCHOU2", "HEXER", "INNOVATION", "LECTRO", "MANCHEZ",
                "NEMESIS", "NIGHTBLADE", "PCJ", "RATBIKE", "RUFFIAN",
                "SANCHEZ", "SANCHEZ2", "SANCTUS", "SHOTARO", "SOVEREIGN",
                "THRUST", "VADER", "VINDICATOR", "VORTEX", "WOLFSBANE",
                "ZOMBIEA", "ZOMBIEB", "DIABLOUS", "DIABLOUS2", "FCR",
                "FCR2"
        };
        //美式肌肉车
        char *Muscle[41] = {
                "BLADE", "BUCCANEER", "BUCCANEER2", "CHINO", "CHINO2",
                "COQUETTE3", "DOMINATOR", "DOMINATOR2", "DUKES", "DUKES2",
                "GAUNTLET", "GAUNTLET2", "FACTION", "FACTION2", "FACTION3",
                "HOTKNIFE", "LURCHER", "MOONBEAM", "MOONBEAM2", "NIGHTSHADE",
                "PHOENIX", "PICADOR", "RATLOADER", "RATLOADER2", "RUINER", "RUINER2", "RUINER3",
                "SABREGT", "SABREGT2", "SLAMVAN", "SLAMVAN2", "SLAMVAN3",
                "STALION", "STALION2", "TAMPA", "VIGERO", "VIRGO",
                "VIRGO2", "VIRGO3", "VOODOO", "VOODOO2"
        };
        //越野车
        char *OffRoad[31] = {
                "BFINJECTION", "BIFTA", "BLAZER", "BLAZER2", "BLAZER3",
                "BLAZER4", "BODHI2", "BRAWLER", "DLOADER", "DUBSTA3",
                "DUNE", "DUNE2", "INSURGENT", "INSURGENT2", "KALAHARI",
                "MARSHALL", "MESA3", "MONSTER", "RANCHERXL", "RANCHERXL2",
                "REBEL", "REBEL2", "SANDKING", "SANDKING2", "TECHNICAL",
                "TROPHYTRUCK", "TROPHYTRUCK2", "TECHNICAL2", "DUNE4", "DUNE5",
                "BLAZER5"
        };
        //飞机
        char *Planes[19] = {
                "BESRA", "CARGOPLANE", "CUBAN800", "DODO", "DUSTER",
                "HYDRA", "JET", "LAZER", "LUXOR", "LUXOR2",
                "MAMMATUS", "MILJET", "NIMBUS", "SHAMAL", "STUNT",
                "TITAN", "VELUM", "VELUM2", "VESTRA"
        };
        //轿车
        char *Sedans[31] = {
                "ASEA", "ASEA2", "ASTEROPE", "COG55", "COG552",
                "COGNOSCENTI", "COGNOSCENTI2", "EMPEROR", "EMPEROR2", "EMPEROR3",
                "FUGITIVE", "GLENDALE", "INGOT", "INTRUDER", "LIMO2",
                "PREMIER", "PRIMO", "PRIMO2", "REGINA", "ROMERO",
                "SCHAFTER2", "SCHAFTER5", "SCHAFTER6", "STANIER", "STRATUM",
                "STRETCH", "SUPERD", "SURGE", "TAILGATER", "WARRENER",
                "WASHINGTON"
        };
        //公共服务车辆
        char *Services[11] = {
                "AIRBUS", "BRICKADE", "BUS", "COACH", "RALLYTRUCK",
                "RENTALBUS", "TAXI", "TOURBUS", "TRASH", "TRASH2",
                "WASTELANDER",
        };
        //跑车
        char *Sports[46] = {
                "ALPHA", "BANSHEE", "BESTIAGTS", "BLISTA2", "BLISTA3",
                "BUFFALO", "BUFFALO2", "BUFFALO3", "CARBONIZZARE", "COMET2",
                "COQUETTE", "ELEGY", "ELEGY2", "FELTZER2", "FUROREGT", "FUSILADE",
                "FUTO", "JESTER", "JESTER2", "KHAMELION", "KURUMA",
                "KURUMA2", "LYNX", "MASSACRO", "MASSACRO2", "NINEF",
                "NINEF2", "OMNIS", "PENUMBRA", "RAPIDGT", "RAPIDGT2",
                "RAPTOR", "SCHAFTER3", "SCHAFTER4", "SCHWARTZER", "SEVEN70",
                "SULTAN", "SURANO", "SPECTER", "SPECTER2", "TAMPA2", "TROPOS", "VERLIERER2",
                "RUINER2", "PHANTOM2", "RUSTON"
        };
        //经典跑车
        char *SportsClassics[23] = {
                "BTYPE", "BTYPE2", "BTYPE3", "CASCO", "COQUETTE2",
                "FELTZER3", "JB700", "MAMBA", "MANANA", "MONROE",
                "PEYOTE", "PIGALLE", "STINGER", "STINGERGT", "TORNADO",
                "TORNADO2", "TORNADO3", "TORNADO4", "TORNADO5", "TORNADO6",
                "ZTYPE", "INFERNUS2", "TURISMO2",
        };
        //超级跑车
        char *Super[28] = {
                "ADDER", "BANSHEE2", "BULLET", "CHEETAH", "ENTITYXF",
                "FMJ", "SHEAVA", "INFERNUS", "NERO", "NERO2", "OSIRIS", "LE7B",
                "ITALIGTB", "ITALIGTB2", "PFISTER811", "PROTOTIPO", "REAPER", "SULTANRS", "T20",
                "TEMPESTA", "TURISMOR", "TYRUS", "VACCA", "VOLTIC", "ZENTORNO", "VOLTIC2", "PENETRATOR", "GP1"
        };
        //SUV
        char *SUVs[27] = {
                "BALLER", "BALLER2", "BALLER3", "BALLER4", "BALLER5",
                "BALLER6", "BJXL", "CAVALCADE", "CAVALCADE2", "CONTENDER",
                "DUBSTA", "DUBSTA2", "FQ2", "GRANGER", "GRESLEY",
                "HABANERO", "HUNTLEY", "LANDSTALKER", "MESA", "MESA2",
                "PATRIOT", "RADI", "ROCOTO", "SEMINOLE", "SERRANO",
                "XLS", "XLS2"
        };
        //拖车
        char *Trailer[22] = {
                "ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2", "BALETRAILER", "BOATTRAILER",
                "DOCKTRAILER", "FREIGHTTRAILER", "GRAINTRAILER", "PROPTRAILER", "RAKETRAILER",
                "TANKER", "TANKER2", "TR2", "TR3", "TR4",
                "TRAILERLOGS", "TRAILERS", "TRAILERS2", "TRAILERS3", "TRAILERSMALL",
                "TRFLAT", "TVTRAILER"
        };
        //火车
        char *Trains[8] = {
                "CABLECAR", "FREIGHT", "FREIGHTCAR", "FREIGHTCONT1", "FREIGHTCONT2",
                "FREIGHTGRAIN", "METROTRAIN", "TANKERCAR"
        };
        //公共事业
        char *Utility[18] = {
                "AIRTUG", "CADDY", "CADDY2", "DOCKTUG", "FORKLIFT",
                "MOWER", "RIPLEY", "SADLER", "SADLER2", "SCRAP",
                "TOWTRUCK", "TOWTRUCK2", "TRACTOR", "TRACTOR2", "TRACTOR3",
                "UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3"
        };
        //货车
        char *Vans[32] = {
                "BISON", "BISON2", "BISON3", "BOBCATXL", "BOXVILLE",
                "BOXVILLE2", "BOXVILLE3", "BOXVILLE4", "BURRITO", "BURRITO2",
                "BURRITO3", "BURRITO4", "BURRITO5", "CAMPER", "GBURRITO",
                "GBURRITO2", "JOURNEY", "MINIVAN", "MINIVAN2", "PARADISE",
                "PONY", "PONY2", "RUMPO", "RUMPO2", "RUMPO3",
                "SPEEDO", "SPEEDO2", "SURFER", "SURFER2", "TACO",
                "YOUGA", "YOUGA2"
        };
        //走私大暴走dlc
        char *SmugglersDLC[19] = {
                "VIGILANTE", "BOMBUSHKA", "ALPHAZ1", "TULA", "HUNTER",
                "ROGUE", "PYRO", "MOGUL", "NOKOTA", "MOLOTOK", "SEABREEZE",
                "HAVOK", "microlight", "HOWARD", "STARLING", "RAPIDGT3",
                "RETINUE", "CYCLONE", "VISIONE"
        };
        //军火霸业DLC
        char *GunrunningDLC[15] = {
                "APC", "Ardent", "Caddy3", "Cheetah2", "Dune3", "Halftrack", "Hauler2", "Insurgent3",
                "Nightshark", "Oppressor", "Phantom3", "Tampa3", "Torero", "Vagner", "Xa21"
        };
        //末日豪劫DLC
        char *DoomsdayDLC[30] = {
                "Z190", "akula", "autarch", "avenger", "avenger2", "barrage", "chernobog",
                "comet4", "comet5", "deluxo", "gt500", "hermes", "hustler", "kamacho",
                "khanjali", "neon", "pariah", "raiden", "revolter", "riata", "riot2", "savestra",
                "sc1", "sentinel3", "streiter", "stromberg", "thruster",
                "viseris", "volatol", "yosemite"
        };
        //南圣安地列斯超级系列赛
        char *SportSeries[15] = {
                "cheburek", "dominator3", "ellie", "entity2", "fagaloa", "flashgt", "gb200",
                "hotring", "issi3", "jester3", "michelli", "seasparrow", "taipan", "tezeract",
                "tyrant"
        };
    };
    //功能控制变量
    class Var {
    public:
        char *Ped_List[18] = {
                "player_zero", "player_one", "player_two", "ig_mp_agent14", "ig_taocheng", "ig_stevehains",
                "ig_orleans", "ig_amandatownley", "mp_s_m_armoured_01", "mp_m_claude_01", "ig_wade", "ig_lestercrest_2",
                "ig_avon", "ig_rashcosvki", "ig_paige", "mp_m_marston_01", "ig_lestercrest", "ig_lamardavis"
        };
        //动物
        char *Ped_List_animal[30] = {
                "a_c_boar", "a_c_chickenhawk", "a_c_chop", "a_c_cormorant", "a_c_crow", "a_c_cow", "a_c_coyote",
                "a_c_deer", "a_c_dolphin", "a_c_fish", "a_c_sharkhammer", "a_c_hen", "a_c_humpback", "a_c_husky",
                "a_c_killerwhale", "a_c_mtlion", "a_c_pig", "a_c_pigeon", "a_c_poodle", "a_c_pug", "a_c_rabbit_01",
                "a_c_rat", "a_c_retriever", "a_c_rhesus", "a_c_rottweiler", "a_c_seagull", "a_c_shepherd",
                "a_c_stingray", "a_c_sharktiger", "a_c_westy"
        };
        bool bGodMode = false;
        bool bInfiniteAmmo = false;
        bool bNoRagdoll = false;
        //超级跳
        bool bSuperJump=false;
        //通缉等级
        int iWantedLevel = 0;
        //永不通缉
        bool bNeverWanted=false;
        //无限备用弹夹
        bool bInfiniteSpareAmmo=false;
        //回血等级
        int iRestoreLevel=0;
        //回防弹衣值
        int iArmourValue=1;
        //回防弹衣
        bool bRestoreArmour=false;
        //在线玩家选项
        //观看玩家
        bool bSpectatePlayer=false;
        //是否在车内
        bool bSpawnInVehicle=false;
        //载具无敌
        bool bVehicleGodMode=false;
        //另类无敌
        bool bGodMode2=false;
        //----------------------
        //回血
        bool bRestoreHealth=false;
        //显示坐标
        bool bShowCoords=false;
        //循环修车
        bool bLoopFixVeh=false;
        //显示fps
        //bool bShowFps=false;
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
    //更新
   void updateFeatures();
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
    void GiveAllWeapon(Ped player);
    //无限备用弹
    void InfiniteSpareAmmo(bool toggle);
    //全武器满子弹
    void GiveFullAmmo();
    //传送到标记点
    void Teleport_to_Mark();
    //获取标记点位置
    Vector3 get_blip_marker();
    //传送到坐标
    void Teleport_Vector3(Ped player,Vector3 coords);
    //刷出车辆
    void Spawn_Vehicle(char* car_tag);
    //回血
    void RestoreHealth(bool toggle, int level);
    //回防弹衣值
    void RestoreArmour(bool toggle,int value);
    //检查模型
    bool checkModel(Hash hash);
    //检查动画
    bool checkAnim(char* dict);
    //    车辆无敌
    void VehicleGodMode(bool toggle);
    //更改模型
    void ChangeModel(char* name);
}

class Online{
public:
    //选择的玩家
    int selectPlayer;
    //事件指针
    static std::vector<void*> EventPtr;
    //循环爆炸
    bool bLoopExplosion=false;
    //循环喷火
    bool bLoopWater=false;
    //循环喷水
    bool bLoopFlame=false;
    //掉帧攻击
    bool bDropFrame=false;
    //切换安全相机
    bool bSecurityCamera=false;
    //全部人无限子弹
    bool bAllPlayerInfiniteAmmo=false;
    //拦截爆炸事件
    bool bProtectExplosionEvent=false;
    //天气更改
    bool bWeatherEvent=false;
    //着火事件
    bool bFireEvent=false;
    //粒子事件
    bool bPTFX_Event=false;
    //删除所有武器
    bool bRemoveAllWeaponsEvent=false;
    //给予武器
    bool bGiveWeaponEvent=false;
    //时间更改
    bool bClockEvent=false;
    //远程脚本踢出
    bool bRemoteScriptKickEvent=false;
    //传送事件
    bool bTP_Event=false;
    //掉落物
    bool bPickup_Event=false;
    //观看玩家
    static void SpectatePlayer(bool toggle, Ped targetPlayer);
    //爆炸玩家
    static void ExplosionPlayer(Ped targetPlayer,int damage,int type,int cam,bool Invisible,bool Audio);
    //黑人抬棺
    static void CoffinDance(Ped selectPlayer);
    //撞击
    static void VehicleImpact(Ped selectPlayer);
    //掉帧
    static void DropFrameAttack(Ped selectPlayer);
    //安全相机
    static void SecurityCamera(bool toggle);
    //事件拦截
    static void defuseEvent(RockstarEvent event, bool toggle);
    //全玩家无限子弹
    static void GiveAllPlayerFullAmmo();
};