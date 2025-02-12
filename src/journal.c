#include "global.h"
#include "main.h"
#include "ach_atlas.h"
#include "task.h"
#include "m4a.h"
#include "bg.h"
#include "malloc.h"
#include "gpu_regs.h"
#include "palette.h"
#include "scanline_effect.h"
#include "dma3.h"
#include "sprite.h"
#include "window.h"
#include "text.h"
#include "strings.h"
#include "menu.h"
#include "string_util.h"
#include "sound.h"
#include "overworld.h"
#include "event_data.h"
#include "script.h"
#include "random.h"
#include "graphics.h"
#include "mgba.h"
#include "item.h"
#include "money.h"
#include "new_game.h"
#include "constants/flags.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/items.h"

static const u8 sJournalBGMap[] = INCBIN_U8("graphics/journal/journal_tiles.bin");
static const u8 sJournalBGTiles[] = INCBIN_U8("graphics/journal/journal_tiles.4bpp");
static const u16 sJournalBGPalette[] = INCBIN_U16("graphics/journal/journal_tiles.gbapal");

static const u8 sAchAtlasJournalIconTiles[] = INCBIN_U8("graphics/journal/ach_atlas_icon.4bpp");
static const u16 sAchAtlasJournalIconPalette[] = INCBIN_U16("graphics/journal/ach_atlas_icon.gbapal");

static const u8 sPowersJournalIconTiles[] = INCBIN_U8("graphics/journal/powers_icon.4bpp");
static const u16 sPowersJournalIconPalette[] = INCBIN_U16("graphics/journal/powers_icon.gbapal");

static const u8 sQuestsJournalIconTiles[] = INCBIN_U8("graphics/journal/quests_icon.4bpp");
static const u16 sQuestsJournalIconPalette[] = INCBIN_U16("graphics/journal/quests_icon.gbapal");

static const u8 sJournalIconTiles[] = INCBIN_U8("graphics/journal/journal_icon.4bpp");
static const u16 sJournalIconPalette[] = INCBIN_U16("graphics/journal/journal_icon.gbapal");

enum // much window, such complexity 
{
    WIN_JOURNAL_STATS,
    WIN_JOURNAL_QUEST_STAGE,
    WIN_JOURNAL_IMPORTANT_VALUES,
    COUNT_JOURNAL_WINDOWS
};

static const struct WindowTemplate sJournalWindowTemplate[] =
{
    [WIN_JOURNAL_STATS] =
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 6,
        .width = 28,
        .height = 8,
        .paletteNum = 15,
        .baseBlock = 1,
    },
    [WIN_JOURNAL_QUEST_STAGE] =
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 15,
        .width = 28,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 309,
    },
    [WIN_JOURNAL_IMPORTANT_VALUES] =
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 4,
        .width = 28,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 421,
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sJournalBGTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 27,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 2,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 3,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    }
};

struct JournalEntryButtonData
{
    struct SpriteFrameImage spriteImages[2];
    const u16 * palette;
    void (*callback2)(void);
};

enum
{
    JOURNAL_OPTION_JOURNAL, // somehow this feels useless
    JOURNAL_OPTION_ACH_ATLAS,
    JOURNAL_OPTION_POWERS,
    //JOURNAL_OPTION_QUESTS,
    JOURNAL_OPTION_COUNT,
    JOURNAL_OPTION_EXIT,  // should always be after JOURNAL_OPTION_COUNT and at the end
};

void Task_InitAtlas(u8 taskId);
void Task_OpenAPMenu(u8); // should probably change the AP menu to not be stupid
void Task_InitAPMenu(u8 taskId);

void CB2_OpenQuestTracker(void);

static const struct JournalEntryButtonData sJounralButtons[JOURNAL_OPTION_COUNT] =
{
    [JOURNAL_OPTION_JOURNAL] = {
        .spriteImages = 
        {
            {
                .data = sJournalIconTiles,
                .size = TILE_SIZE_4BPP*64,
            },
            {
                .data = sJournalIconTiles+TILE_SIZE_4BPP*64,
                .size = TILE_SIZE_4BPP*64,
            },
        },
        .palette = sJournalIconPalette,
    },
    [JOURNAL_OPTION_ACH_ATLAS] = {
        .spriteImages = 
        {
            {
                .data = sAchAtlasJournalIconTiles,
                .size = TILE_SIZE_4BPP*64,
            },
            {
                .data = sAchAtlasJournalIconTiles+TILE_SIZE_4BPP*64,
                .size = TILE_SIZE_4BPP*64,
            },
        },
        .palette = sAchAtlasJournalIconPalette,
        .callback2 = CB2_OpenAtlas,
    },
    [JOURNAL_OPTION_POWERS] = {
        .spriteImages = 
        {
            {
                .data = sPowersJournalIconTiles,
                .size = TILE_SIZE_4BPP*64,
            },
            {
                .data = sPowersJournalIconTiles+TILE_SIZE_4BPP*64,
                .size = TILE_SIZE_4BPP*64,
            },
        },
        .palette = sPowersJournalIconPalette,
        .callback2 = CB2_OpenAPMenu,
    },
    /*
    [JOURNAL_OPTION_QUESTS] = {
        .spriteImages = 
        {
            {
                .data = sQuestsJournalIconTiles,
                .size = TILE_SIZE_4BPP*64,
            },
            {
                .data = sQuestsJournalIconTiles+TILE_SIZE_4BPP*64,
                .size = TILE_SIZE_4BPP*64,
            },
        },
        .palette = sQuestsJournalIconPalette,
        //.callback2 = CB2_OpenQuestTracker,
    },
    */
    /*
    [JOURNAL_OPTION_EXIT] = {
        .callback2 = CB2_ReturnToFieldWithOpenMenu,
    },
    */
};

const struct OamData sJournalIconsOam =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

static const union AnimCmd sButtonNormalAnimation[] = {
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END
};

static const union AnimCmd sButtonGlowAnimation[] = {
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_END,
};

static const union AnimCmd *const sButtonAnims[] =
{
    sButtonNormalAnimation,
    sButtonGlowAnimation
};

static void ButtonSpriteCB(struct Sprite *sprite);

static const struct SpriteTemplate sButtonSpriteTemplate =
{
    .tileTag = 0xFFFF,
    .paletteTag = 0xFFFF,
    .oam = &sJournalIconsOam,
    .anims = sButtonAnims,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = ButtonSpriteCB,
};

EWRAM_DATA static u8 sButtonSpriteIds[JOURNAL_OPTION_COUNT] = {0}; // TODO: fix array size

static void Task_InitJournal(u8 taskId);
static void Task_JournalMain(u8 taskId);

static bool8 IntializeJournal(void);

struct SpriteTemplate CreateButtonSpriteTemplate(u32 buttonId) // TODO: now useless don't use
{
    struct SpriteTemplate sprtTmplt;
    sprtTmplt.tileTag = 0xFFFF;
    sprtTmplt.tileTag = 0xFFFF;
    sprtTmplt.oam = &sJournalIconsOam;
    sprtTmplt.anims = sButtonAnims;
    sprtTmplt.images = sJounralButtons[buttonId].spriteImages;
    sprtTmplt.affineAnims = gDummySpriteAffineAnimTable;
    sprtTmplt.callback = SpriteCallbackDummy;
    return sprtTmplt;
}

void CB2_Journal(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_Journal(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_OpenJournal(void)
{
    switch (gMain.state)
    {
    case 0:
    default:
        SetVBlankCallback(NULL);
        DmaFill32(3, 0, (u8 *)VRAM, VRAM_SIZE);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        gMain.state = 1;
        break;
    case 1:
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        ResetPaletteFade();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 2;
        gMain.state++;
        break;
    case 2:
        CreateTask(Task_InitJournal, 0);
        gMain.state++;
        break;
    case 3:
        EnableInterrupts(1);
        SetVBlankCallback(VBlankCB_Journal);
        SetMainCallback2(CB2_Journal);
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFFFF, 0x80);
        break;
    }
}

#define TOP_SPACING 17
#define LEFT_MIDDLE 112

//Game stats
const static u8 sText_BerriesPlanted[] = _("Berries Planted");
const static u8 sText_TotalBattles[] = _("Total Battles");
const static u8 sText_PkmnCaptures[] = _("Pokemon Captures");
const static u8 sText_EggsHatched[] = _("Eggs Hatched");
const static u8 sText_PkmnEvolved[] = _("Pokemon Evolved");
const static u8 sText_BattlesWon[] = _("Battles Won");
const static u8 sText_RibbonsReceived[] = _("Ribbons Received");

const static u8 sText_ContestsWon[] = _("Contests Won");
const static u8 sText_ContestsEntered[] = _("Contests Entered");

//SaveBlock Vars
const static u8 sText_NumPartners[] = _("Num. Partners");

const static u8 sText_MiningSkill[] = _("Mining Skill");
const static u8 sText_MiningExp[] = _("Mining Exp");

const static u8 sText_BotanySkill[] = _("Botany Skill");
const static u8 sText_BotanySkillExp[] = _("Botany Skill Exp"); // Botany Skill Exp? Botany Exp? idk

const static u8 sText_AlchemySkill[] = _("Alchemy Skill");
const static u8 sText_AlchemyExp[] = _("Alchemy Exp");

const static u8 sText_KOs[] = _("KOs");

const static u8 sText_TitleDefenseWins[] = _("Title Defense Wins");

const static u8 sText_Achievements[] = _("Achievements");

const static u8 sText_ExpInDrive[] = _("EXP Stored in Drive");

const static u8 sText_Money[] = _("Money:");
const static u8 sText_BadgesEarned[] = _("Badges Earned");

const static u8 sText_TrainerNameId[] = _("Trainer Name   {PLAYER}      Badges Earned   {STR_VAR_1}\nTrainer Id       {STR_VAR_2}       Money   {STR_VAR_3}");

struct JournalStatData
{
    const u8 * statName;
    u32 (*statValueFunc)(void);
    u8 numberCount;
    u8 hideOnN1; // N1 = -1 = 0xFFFFFFFF
};

u32 GetPlantedBerries(void)
{
    return GetGameStat(GAME_STAT_PLANTED_BERRIES);
}

u32 GetTotalBattles(void)
{
    return GetGameStat(GAME_STAT_TOTAL_BATTLES);
}

u32 GetPokeCaptures(void)
{
    return GetGameStat(GAME_STAT_POKEMON_CAPTURES);
}

u32 GetEggsHatched(void)
{
    return GetGameStat(GAME_STAT_HATCHED_EGGS);
}

u32 GetEvolvedPokemonStat(void)
{
    return GetGameStat(GAME_STAT_EVOLVED_POKEMON);
}

u32 GetBattlesWon(void)
{
    return GetGameStat(GAME_STAT_BATTLES_WON);
}

u32 GetRibbonsReceived(void)
{
    return GetGameStat(GAME_STAT_RECEIVED_RIBBONS);
}

u32 GetPlayerContestsWon(void)
{
    return GetGameStat(GAME_STAT_WON_CONTEST);
}

u32 GetPlayerContestsEntered(void)
{
    return GetGameStat(GAME_STAT_ENTERED_CONTEST);
}

extern int RyuGetPartnerCount();
u32 GetPartnerCount(void)
{
    return RyuGetPartnerCount();
}

u32 GetMiningSkill(void)
{
    return VarGet(VAR_RYU_PLAYER_MINING_SKILL);
}

u32 GetMiningExp(void)
{
    return VarGet(VAR_RYU_PLAYER_MINING_EXP);
}

u32 GetBotanySkill(void)
{
    return VarGet(VAR_RYU_PLAYER_BOTANY_SKILL);
}

u32 GetBotanyExp(void)
{
    return VarGet(VAR_RYU_PLAYER_BOTANY_SKILL_EXP);
}

u32 GetAlchemySkill(void)
{
    return VarGet(VAR_RYU_PLAYER_ALCHEMY_SKILL);
}

u32 GetAlchemyExp(void)
{
    return VarGet(VAR_RYU_ALCHEMY_EXP);
}

u32 GetTotalKOs(void)
{
    return VarGet(VAR_RYU_TOTAL_FAINTS);
}

u32 GetTitleDefenseWins(void)
{
    return VarGet(VAR_RYU_TITLE_DEFENSE_WINS);
}

u32 GetDriveExp(void)
{
    return CheckBagHasItem(ITEM_EXP_DRIVE, 1) ? VarGet(VAR_RYU_EXP_BATTERY) : 0xFFFFFFFF; 
}

u32 GetAchivements(void)
{
    return CountTakenAchievements();
}

static const struct JournalStatData sJournalStatsGeneral[] =
{
    {
        sText_BerriesPlanted,
        GetPlantedBerries,
        4,
        FALSE,
    },
    {
        sText_TotalBattles,
        GetTotalBattles,
        4,
        FALSE,
    },
    {
        sText_PkmnCaptures,
        GetPokeCaptures,
        4,
        FALSE,
    },
    {
        sText_EggsHatched,
        GetEggsHatched,
        4,
        FALSE,
    },
    {
        sText_PkmnEvolved,
        GetEvolvedPokemonStat,
        4,
        FALSE,
    },
    {
        sText_BattlesWon,
        GetBattlesWon,
        4,
        FALSE,
    },
    {
        sText_RibbonsReceived,
        GetRibbonsReceived,
        4,
        FALSE,
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};

static const struct JournalStatData sJournalStatsContest[] =
{
    {
        sText_ContestsWon,
        GetPlayerContestsWon,
        4,
        FALSE,
    },
    {
        sText_ContestsEntered,
        GetPlayerContestsEntered,
        4,
        FALSE,
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};

static const struct JournalStatData sJournalStatsPartner[] =
{
    {
        sText_NumPartners,
        GetPartnerCount,
        1,
        FALSE
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};

static const struct JournalStatData sJournalStatsMining[] =
{
    {
        sText_MiningSkill,
        GetMiningSkill,
        1,
        FALSE
    },
    {
        sText_MiningExp,
        GetMiningExp,
        4,
        FALSE
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};


static const struct JournalStatData sJournalStatsBotany[] =
{
    {
        sText_BotanySkill,
        GetBotanySkill,
        1,
        FALSE
    },
    {
        sText_BotanySkillExp,
        GetBotanyExp,
        4,
        FALSE
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};


static const struct JournalStatData sJournalStatsAlchemy[] =
{
    {
        sText_AlchemySkill,
        GetAlchemySkill,
        1,
        FALSE
    },
    {
        sText_AlchemyExp,
        GetAlchemyExp,
        4,
        FALSE
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};


static const struct JournalStatData sJournalStatsKnockOuts[] =
{
    {
        sText_KOs,
        GetTotalKOs,
        3,
        FALSE
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};

static const struct JournalStatData sJournalStatsTitleDefense[] =
{
    {
        sText_TitleDefenseWins,
        GetTitleDefenseWins,
        3,
        FALSE
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};

static const struct JournalStatData sJournalStatsExpDrive[] = // TODO: caused problems in the past had to replace it
{
    {
        sText_ExpInDrive,
        GetDriveExp,
        5,
        TRUE
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};

static const struct JournalStatData sJournalStatsAchievements[] =
{
    {
        sText_Achievements,
        GetAchivements,
        3,
        FALSE
    },
    {
        NULL,
        NULL,
        0, 0,
    }
};

static const struct JournalStatData * sJournalStats[] = 
{
    sJournalStatsGeneral,
    sJournalStatsContest,
    sJournalStatsPartner,
    sJournalStatsMining,
    sJournalStatsBotany,
    sJournalStatsAlchemy,
    sJournalStatsKnockOuts,
    sJournalStatsTitleDefense,
    sJournalStatsAchievements, // TODO: placeholder to have even amount of single line stats
    //sJournalStatsExpDrive,
};

u32 CountStatArrayLength(const struct JournalStatData * journalData)
{
    u32 i;
    for(i = 0; journalData++->statValueFunc; i++);
    return i;
}
extern int CountBadges(void);
static void DrawJournalStatText(void)
{
    u32 i, j;
    u32 top = 0, left = 0;
    u32 statToDisplay = Random() % ARRAY_COUNT(sJournalStats);
    u8 color[3] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GREY, TEXT_COLOR_LIGHT_GREY};
    u8 * textBuffer;
    u8 stats[8];
    const struct JournalStatData * journalStat;
    u32 length = 0;

    for(i = 0; i < 8 && length < 8;) // this shit can break at any moment
    {
        u32 flag;
        u32 statCount;
        u32 newStat = Random() % ARRAY_COUNT(sJournalStats);
        do
        {
            for(j = 0; j < length; j++)
            {
                if(newStat == stats[j]) 
                {
                    newStat = Random() % ARRAY_COUNT(sJournalStats);
                    flag = TRUE;
                    break;
                }
                flag = FALSE;
            }
        }
        while(flag);
        // TODO: this is not gonna be fine
        //if(sJournalStats[newStat]->hideOnN1 && sJournalStats[newStat]->statValueFunc() == 0xFFFFFFFF && i != 7) // TODO: last comparison is a hack so that we can roll out update sooner be it with some rough edges 
            //continue; 
        statCount = CountStatArrayLength(sJournalStats[newStat]);
        mgba_printf(LOGINFO, "statCount %d, i %d", statCount, i);
        if(statCount > 8-i)
            continue;
        stats[length++] = newStat;
        i += statCount;
    }
    j = 0;
    journalStat = sJournalStats[stats[j]];
    for(i = 0; i < 8; i++, journalStat++)
    {
        u32 val;
        if(journalStat->statValueFunc == NULL)
            journalStat = sJournalStats[stats[++j]];
        
        val = journalStat->statValueFunc();
        //if(journalStat->hideOnN1 && val == 0xFFFFFFFF)
        //    continue; // failsafe which will get triggered too much
        
        AddTextPrinterParameterized3(WIN_JOURNAL_STATS, 0, left, top, color, 0, journalStat->statName); // TODO: speed 0xFF
        ConvertIntToDecimalStringN(gStringVar4, val, STR_CONV_MODE_LEADING_ZEROS, journalStat->numberCount);
        AddTextPrinterParameterized3(WIN_JOURNAL_STATS, 0, (left+LEFT_MIDDLE-2)-GetStringWidth(0, gStringVar4, 0), top, color, 0, gStringVar4);
        top += TOP_SPACING;
        if(i == 3)
        {
            top = 0;
            left = LEFT_MIDDLE+1;
        }
    }
    
    /*
    AddTextPrinterParameterized3(WIN_JOURNAL_IMPORTANT_VALUES, 0, 2, 1, color, 0, sText_Money); // TODO: speed 0xFF
    ConvertIntToDecimalStringN(gStringVar4, GetMoney(&gSaveBlock1Ptr->money), STR_CONV_MODE_RIGHT_ALIGN, 8);
    AddTextPrinterParameterized3(WIN_JOURNAL_IMPORTANT_VALUES, 0, 90-GetStringWidth(0, gStringVar4, 0), 1, color, 0, gStringVar4); // TODO: speed 0xFF
    ConvertIntToDecimalStringN(gStringVar4, CountBadges(), STR_CONV_MODE_LEFT_ALIGN, 1);
    AddTextPrinterParameterized3(WIN_JOURNAL_IMPORTANT_VALUES, 0, 142, 1, color, 0, gStringVar4); 
    AddTextPrinterParameterized3(WIN_JOURNAL_IMPORTANT_VALUES, 0, 224-GetStringWidth(0, sText_BadgesEarned, 0)-2, 1, color, 0, sText_BadgesEarned);
    */

    ConvertIntToDecimalStringN(gStringVar1, CountBadges(), STR_CONV_MODE_LEADING_ZEROS, 1);
    ConvertIntToDecimalStringN(gStringVar2, (u16)GetTrainerId(gSaveBlock2Ptr->playerTrainerId), STR_CONV_MODE_LEADING_ZEROS, 5);
    ConvertIntToDecimalStringN(gStringVar3, GetMoney(&gSaveBlock1Ptr->money), STR_CONV_MODE_LEFT_ALIGN, 8);
    StringExpandPlaceholders(gStringVar4, sText_TrainerNameId);
    AddTextPrinterParameterized3(WIN_JOURNAL_QUEST_STAGE, 1, 0, 1, color, 0, gStringVar4);
    
}

static void Task_InitJournal(u8 taskId)
{
    if(IntializeJournal())
    {
        gTasks[taskId].func = Task_JournalMain;
        // TODO: i'll decide what to do with these later
        //gKeyRepeatContinueDelay = -1;
        //gKeyRepeatStartDelay = -1;
    }
}

static bool8 IntializeJournal(void)
{
    u32 i;
    switch (gMain.state)
    {
    case 0:
    default:
        if (gPaletteFade.active)
            return 0;
        SetVBlankCallback(NULL);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sJournalBGTemplates, ARRAY_COUNT(sJournalBGTemplates));
        SetBgTilemapBuffer(3, AllocZeroed(BG_SCREEN_SIZE));
        SetBgTilemapBuffer(2, AllocZeroed(BG_SCREEN_SIZE));
        SetBgTilemapBuffer(1, AllocZeroed(BG_SCREEN_SIZE));
        SetBgTilemapBuffer(0, AllocZeroed(BG_SCREEN_SIZE));
        DmaCopy16(3, sJournalBGTiles, BG_CHAR_ADDR(2), sizeof(sJournalBGTiles));
        DmaCopy16(3, sJournalBGMap, GetBgTilemapBuffer(1), sizeof(sJournalBGMap));
        LoadPalette(sJournalBGPalette, 0, 0x20);
        InitWindows(sJournalWindowTemplate);
        InitTextBoxGfxAndPrinters();
        LoadPalette(gRyuDarkTheme_Pal, 0xF0, 0x20);
        DeactivateAllTextPrinters();
        PutWindowTilemap(0);
        CopyWindowToVram(0, 3);
        gMain.state = 1;
        break;
    case 1:
        ResetSpriteData();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 2;
        gMain.state++;
        break;
    case 2:
    {
        u32 i;
        struct SpriteTemplate spriteTemplate = sButtonSpriteTemplate;
        static const u8 buttonXPos[JOURNAL_OPTION_COUNT] = {32, 90, 160}; //! EVIL hardcoding
        for(i = 0; i < JOURNAL_OPTION_COUNT; i++)
        {
            spriteTemplate.images = sJounralButtons[i].spriteImages;
            sButtonSpriteIds[i] = CreateSprite(&spriteTemplate, 32 + buttonXPos[i], 42, 0); // temporary
            gSprites[sButtonSpriteIds[i]].data[0] = !i;
        }
        LoadPalette(sJounralButtons[0].palette, 0x100, 0x20);
        gMain.state++;
        break;
    }
    case 3:
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        gMain.state++;
        break;
    case 4:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0x10, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB_Journal);
        gMain.state++;
        break;
    case 5:
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG3HOFS, 0);
        SetGpuReg(REG_OFFSET_BG3VOFS, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);
        // TODO: Will get rid of STD frames later i would imagine
        for(i = 0; i < COUNT_JOURNAL_WINDOWS; i++)
        {
            PutWindowTilemap(i);
            CopyWindowToVram(i, 3);
            //DrawStdWindowFrame(i, TRUE);
        }
        DrawJournalStatText();
        gMain.state++;
        break;
    case 6:
        if (!gPaletteFade.active)
        {
            gMain.state = 0;
            return TRUE;
        }
        break;
    }
    return FALSE;
}

#define JOURNAL_ACTION_NONE 0
#define JOURNAL_ACTION_RIGHT (1 << 1)
#define JOURNAL_ACTION_LEFT (1 << 2)
#define JOURNAL_ACTION_CHOOSE (1 << 3)
#define JOURNAL_ACTION_EXIT (1 << 4)
//#define JOURNAL_ACTION_LEFT (1 << 1)
//#define JOURNAL_ACTION_LEFT (1 << 1)
//#define JOURNAL_ACTION_LEFT (1 << 1)


static u32 InputToJournalAction(void)
{
    u32 finalAction = JOURNAL_ACTION_NONE;
    switch(gMain.newAndRepeatedKeys & (DPAD_LEFT | DPAD_RIGHT))
    {
        case DPAD_LEFT:
            return JOURNAL_ACTION_LEFT;
        case DPAD_RIGHT:
            return JOURNAL_ACTION_RIGHT;
    }
    if(gMain.newKeys & A_BUTTON)
        finalAction = JOURNAL_ACTION_CHOOSE;
    else if(gMain.newKeys & B_BUTTON)
        finalAction = JOURNAL_ACTION_EXIT;
    return finalAction;
}

#define tCurrentButton data[0]

static void Task_ExitJournalTaskIntoNewUI(u8 taskId)
{
    u32 i;

    if(gPaletteFade.active)
        return;
    if(gTasks[taskId].tCurrentButton != JOURNAL_OPTION_EXIT && sJounralButtons[gTasks[taskId].tCurrentButton].callback2 == NULL)
    {
        mgba_printf(LOGFATAL, "Line %d, Button task is NULL", __LINE__);
        return; // how did we end up here
    }   
    
    FreeAllWindowBuffers();
    for(i = 0; i < 4; i++)
    {
        Free(GetBgTilemapBuffer(i));
        UnsetBgTilemapBuffer(i);
    }
    RemoveWindow(WIN_JOURNAL_QUEST_STAGE);
    RemoveWindow(WIN_JOURNAL_STATS);
    DmaFill32(3, 0, VRAM, VRAM_SIZE);
    DestroyTask(taskId);
    //gTasks[taskId].func = sJounralButtons[gTasks[taskId].tCurrentButton].callback2; //! SHOULD IDEALLY JUST GO TO PROPER CALLBACKS FOR THE UIs BUT I'M LAZY AND I HAD TO WORK ON EXISTING CODE WHICH GOT EDITED ANYWAYS
    if(gTasks[taskId].tCurrentButton == JOURNAL_OPTION_EXIT) 
        SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
    else
        SetMainCallback2(sJounralButtons[gTasks[taskId].tCurrentButton].callback2);
}

static void Task_JournalMain(u8 taskId)
{
    u32 action = InputToJournalAction();
    switch(action)
    {
        case JOURNAL_ACTION_LEFT:
        case JOURNAL_ACTION_RIGHT:
            gSprites[gTasks[taskId].tCurrentButton].data[0] = 0;
            if(action & JOURNAL_ACTION_RIGHT)
                gTasks[taskId].tCurrentButton++;
            else
                gTasks[taskId].tCurrentButton--;
            // TODO: add bound check
            if(gTasks[taskId].tCurrentButton < 0) // task data is signed
                gTasks[taskId].tCurrentButton = JOURNAL_OPTION_COUNT-1;
            if(gTasks[taskId].tCurrentButton >= JOURNAL_OPTION_COUNT)
                gTasks[taskId].tCurrentButton = 0;
            gSprites[gTasks[taskId].tCurrentButton].data[0] = 1;
            break;
        case JOURNAL_ACTION_CHOOSE:
            if(sJounralButtons[gTasks[taskId].tCurrentButton].callback2 == NULL)
                return;
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
            gTasks[taskId].func = Task_ExitJournalTaskIntoNewUI;
            break;
        case JOURNAL_ACTION_EXIT:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
            gTasks[taskId].tCurrentButton = JOURNAL_OPTION_EXIT;
            gTasks[taskId].func = Task_ExitJournalTaskIntoNewUI;
    }
}

static void ButtonSpriteCB(struct Sprite *sprite)
{
    StartSpriteAnimIfDifferent(sprite, !!sprite->data[0]); // TODO: might need to support different frames
}

// Quest stuff

#if 0 // TODO: was removed to get journal screen out early, will finish later
// these are all u16 because apparently it breaks otherwise... wonder if it's alignment bullshit
static const u16 sQuestTrackerBGMap[] = INCBIN_U16("graphics/quest_tracker/quest_tracker_map.bin");
static const u16 sQuestTrackerBGTiles[] = INCBIN_U16("graphics/quest_tracker/quest_tracker.4bpp");
static const u16 sQuestTrackerBGPalette[] = INCBIN_U16("graphics/quest_tracker/quest_tracker.gbapal");

static void Task_InitQuestTracker(u8 taskId);
static void Task_QuestMain(u8 taskId);

enum
{
    WIN_QUEST_QUESTS,
    WIN_QUEST_QUEST_DATA,
    WIN_QUEST_QUEST_STAGE_DESC
};

static const struct WindowTemplate sQuestWindowTemplate[] =
{
    [WIN_QUEST_QUESTS] =
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 4,
        .width = 13,
        .height = 9,
        .paletteNum = 15,
        .baseBlock = 1,
    },
    [WIN_QUEST_QUEST_DATA] =
    {
        .bg = 0,
        .tilemapLeft = 16,
        .tilemapTop = 4,
        .width = 13,
        .height = 9,
        .paletteNum = 15,
        .baseBlock = 118,
    },
    [WIN_QUEST_QUEST_STAGE_DESC] =
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 15,
        .width = 28,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 235,
    },
    DUMMY_WIN_TEMPLATE
};

void CB2_OpenQuestTracker(void)
{
    switch (gMain.state)
    {
    case 0:
    default:
        SetVBlankCallback(NULL);
        DmaFill32(3, 0, (u8 *)VRAM, VRAM_SIZE);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        gMain.state = 1;
        break;
    case 1:
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        ResetPaletteFade();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 2;
        gMain.state++;
        break;
    case 2:
        CreateTask(Task_InitQuestTracker, 0);
        gMain.state++;
        break;
    case 3:
        EnableInterrupts(1);
        SetVBlankCallback(VBlankCB_Journal);
        SetMainCallback2(CB2_Journal);
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, 0xFFFF, 0x80);
        break;
    }
}

static bool8 IntializeQuest(void);

static void Task_InitQuestTracker(u8 taskId)
{
    if(IntializeQuest())
        gTasks[taskId].func = Task_QuestMain;
}

static bool8 IntializeQuest(void)
{
    u32 i;
    switch (gMain.state)
    {
    case 0:
    default:
        if (gPaletteFade.active)
            return 0;
        SetVBlankCallback(NULL);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sJournalBGTemplates, ARRAY_COUNT(sJournalBGTemplates));
        SetBgTilemapBuffer(3, AllocZeroed(BG_SCREEN_SIZE));
        SetBgTilemapBuffer(2, AllocZeroed(BG_SCREEN_SIZE));
        SetBgTilemapBuffer(1, AllocZeroed(BG_SCREEN_SIZE));
        SetBgTilemapBuffer(0, AllocZeroed(BG_SCREEN_SIZE));
        DmaCopy16(3, sQuestTrackerBGTiles, BG_CHAR_ADDR(2), sizeof(sQuestTrackerBGTiles));
        DmaCopy16(3, sQuestTrackerBGMap, GetBgTilemapBuffer(1), sizeof(sQuestTrackerBGMap));
        LoadPalette(sQuestTrackerBGPalette, 0, 0x20);
        InitWindows(sQuestWindowTemplate);
        InitTextBoxGfxAndPrinters();
        DeactivateAllTextPrinters();
        PutWindowTilemap(0);
        CopyWindowToVram(0, 3);
        gMain.state = 1;
        break;
    case 1:
        ResetSpriteData();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 2;
        gMain.state++;
        break;
    case 2:
    {
        /*
        u32 i;
        struct SpriteTemplate spriteTemplate = sButtonSpriteTemplate;
        for(i = 0; i < JOURNAL_OPTION_COUNT; i++)
        {
            spriteTemplate.images = sJounralButtons[i].spriteImages;
            sButtonSpriteIds[i] = CreateSprite(&spriteTemplate, 32 + i*64, 42, 0); // temporary
            gSprites[sButtonSpriteIds[i]].data[0] = !i;
        }
        LoadPalette(sJounralButtons[0].palette, 0x100, 0x20);
        */
        gMain.state++;
        break;
    }
    case 3:
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        gMain.state++;
        break;
    case 4:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0x10, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB_Journal);
        gMain.state++;
        break;
    case 5:
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG3HOFS, 0);
        SetGpuReg(REG_OFFSET_BG3VOFS, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);
        // TODO: Will get rid of STD frames later i would imagine
        for(i = 0; i <= 2; i++)
        {
            PutWindowTilemap(i);
            CopyWindowToVram(i, 3);
            DrawStdWindowFrame(i, TRUE);
        }
        gMain.state++;
        break;
    case 6:
        if (!gPaletteFade.active)
        {
            gMain.state = 0;
            return TRUE;
        }
        break;
    }
    return FALSE;
}

#define QUEST_ACTION_NONE 0
#define QUEST_ACTION_UP (1 << 1)
#define QUEST_ACTION_DOWN (1 << 2)
#define QUEST_ACTION_CHOOSE (1 << 3)

static u32 InputToQuestAction(void)
{
    u32 finalAction = QUEST_ACTION_NONE;
    switch(gMain.newKeys & (DPAD_UP | DPAD_DOWN))
    {
        case DPAD_LEFT:
            return QUEST_ACTION_UP;
        case DPAD_RIGHT:
            return QUEST_ACTION_DOWN;
    }
    if(gMain.newKeys & A_BUTTON) 
        finalAction = QUEST_ACTION_CHOOSE;
    return finalAction;
}

static void Task_QuestMain(u8 taskId)
{

}
#endif