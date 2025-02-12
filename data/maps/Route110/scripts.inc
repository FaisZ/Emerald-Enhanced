Route110_MapScripts:: @ 81EF269
	map_script ON_TRANSITION, Route110_OnTransition
	map_script ON_FRAME, Route110_OnFrame
	.byte 0

R110_LanaSetup::
	lock
	clearflag FLAG_HIDE_TRICK_HOUSE_LANA
	setvar VAR_RYU_DS_LANA_STAGE, 11
	clearflag FLAG_RYU_HIDE_REL_OBJECTS
	release
	end
	
Route110_OnTransition: @ 81EF27D
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	end

Route110_OnFrame: @ 81EF297
	map_script_2 VAR_RYU_DS_LANA_STAGE, 95, R110_LeafEventKickstart
	.2byte 0
	
@==================================================================================================Lana Ending
r110_BGMChangeLeaf::
	fadenewbgm MUS_RG_SLOWMASARA
	return

r110_SetUpTrickHouseLanaEvent2::
	lock
	clearflag FLAG_HIDE_TRICK_HOUSE_LANA
	clearflag FLAG_RYU_HIDE_REL_OBJECTS
	setvar VAR_RYU_DS_LANA_STAGE, 91
	release
	end

	
R110_LeafEventKickstart::
	call_if_set FLAG_RYU_HAS_FOLLOWER, RyuCancelFollowerForQuest
	goto r110_LeafSceneEnding
	release
	end
	
r110_LeafSceneEnding::
	lock
	fadenewbgm MUS_RG_SLOWMASARA
	setvar VAR_RYU_DS_LANA_STAGE, 96
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	applymovement 31, Common_Movement_FaceLeft
	waitmovement 31
	msgbox r110_LeafSceneEndText MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox r110_LeafSceneEndText2 MSGBOX_DEFAULT
	closemessage
	applymovement 31, Common_Movement_HeartEmote
	waitmovement 31
	msgbox r110_LeafSceneEndText3 MSGBOX_DEFAULT
	closemessage
	applymovement 31, r110_LeafExitSouth
	applymovement OBJ_EVENT_ID_PLAYER, r110_PlayerExitSouth
	delay 5
	applymovement 31, Common_Movement_StepDown
	fadescreenspeed 1, 5
	setflag FLAG_RYU_DS_LEAF_PARTNERS
	setflag FLAG_RYU_DS_HAS_PARTNER
	ach give ACH_SILENT_STRONG_TYPE
	addvar VAR_RYU_PARTNER_COUNT, 1
	setflag FLAG_RYU_HIDE_REL_OBJECTS
	clearflag FLAG_HIDE_LANAS_HOUSE_LANA_AND_BRO
	delay 40
	removeobject 31
	setvar VAR_RYU_DS_LANA_STAGE, 100
	warp MAP_SLATEPORT_CITY, 255, 14, 20
	releaseall
	end
	
r110_LeafExitSouth:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
	
r110_PlayerExitSouth:
	delay_16
	delay_16
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
	
r110_LeafSceneEndText:
	.string "{COLOR LIGHT_BLUE}{SHADOW BLUE}Honestly, babe...I think he pulled\na fast one on us.$"
	
r110_LeafSceneEndText2:
	.string " {COLOR LIGHT_GREEN}{SHADOW GREEN}(Lana affectionately gives a\n lingering kiss to {PLAYER}!)$"
	
r110_LeafSceneEndText3:
	.string "{COLOR LIGHT_RED}{SHADOW RED}Nah, I think we got the better\ndeal. C'mon, let's go!$"

@==================================================================================================

Route110_EventScript_AquaGrunt1:: @ 81EF2AA
	lock
	faceplayer
	msgbox Route110_Text_WeCantTalkAboutAquaActivities, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt2:: @ 81EF2C0
	lock
	faceplayer
	msgbox Route110_Text_KickUpARuckus, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt3:: @ 81EF2D6
	lock
	faceplayer
	msgbox Route110_Text_MyFirstJobInAqua, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt4:: @ 81EF2EC
	lock
	faceplayer
	msgbox Route110_Text_AquaActionsBringSmiles, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_Boy1:: @ 81EF302
	msgbox Route110_Text_RideBikeAtFullSpeed, MSGBOX_NPC
	end

Route110_EventScript_CyclingGirl1:: @ 81EF30B
	msgbox Route110_Text_HairStreamsBehindMe, MSGBOX_NPC
	end

Route110_EventScript_CyclingGuy1:: @ 81EF314
	msgbox Route110_Text_YouGotBikeFromRydel, MSGBOX_NPC
	end

Route110_EventScript_OldMan:: @ 81EF31D
	msgbox Route110_Text_TwoRoads, MSGBOX_NPC
	end

Route110_EventScript_OldWoman:: @ 81EF326
	msgbox Route110_Text_WalkOnTheLowRoad, MSGBOX_NPC
	end

Route110_EventScript_CyclingGuy2:: @ 81EF32F
	msgbox Route110_Text_BikeTechniques, MSGBOX_NPC
	end

Route110_EventScript_Boy2:: @ 81EF338
	msgbox Route110_Text_WhichShouldIChoose, MSGBOX_NPC
	end

Route110_EventScript_SlateportCitySign:: @ 81EF341
	msgbox Route110_Text_SlateportCitySign, MSGBOX_SIGN
	end

Route110_EventScript_CyclingRoadSign:: @ 81EF34A
	msgbox Route110_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route110_EventScript_VandalizedSign:: @ 81EF353
	msgbox Route110_Text_AquaWasHere, MSGBOX_SIGN
	end

Route110_EventScript_Route103Sign:: @ 81EF35C
	msgbox Route110_Text_Route103Sign, MSGBOX_SIGN
	end

Route110_EventScript_SeasideParkingSign:: @ 81EF365
	msgbox Route110_Text_SeasideParkingSign, MSGBOX_SIGN
	end

Route110_EventScript_MauvilleCitySign:: @ 81EF36E
	msgbox Route110_Text_MauvilleCitySign, MSGBOX_SIGN
	end

Route110_EventScript_TrainerTipsPrlzSleep:: @ 81EF377
	msgbox Route110_Text_TrainerTipsPrlzSleep, MSGBOX_SIGN
	end

Route110_EventScript_TrainerTipsRegisterItems:: @ 81EF380
	msgbox Route110_Text_TrainerTipsRegisterItems, MSGBOX_SIGN
	end

Route110_EventScript_TrickHouseSign:: @ 81EF389
	msgbox Route110_Text_TrickHouseSign, MSGBOX_SIGN
	end

Route110_EventScript_Edward:: @ 81EF3F2
	trainerbattle_single TRAINER_EDWARD, Route110_Text_EdwardIntro, Route110_Text_EdwardDefeated
	msgbox Route110_Text_EdwardPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jaclyn:: @ 81EF409
	trainerbattle_single TRAINER_JACLYN, Route110_Text_JaclynIntro, Route110_Text_JaclynDefeated
	msgbox Route110_Text_JaclynPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Edwin:: @ 81EF420
	trainerbattle_single TRAINER_EDWIN_1, Route110_Text_EdwinIntro, Route110_Text_EdwinDefeated, Route110_EventScript_EdwinRegisterMatchCallAfterBattle
	msgbox Route110_Text_EdwinPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_EdwinRegisterMatchCallAfterBattle:: @ 81EF44C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_EdwinRegister, MSGBOX_DEFAULT
	@nop Trainer_EDWIN_1
	release
	end

Route110_EventScript_EdwinRematch:: @ 81EF46B
	trainerbattle_rematch TRAINER_EDWIN_1, Route110_Text_EdwinRematchIntro, Route110_Text_EdwinRematchDefeated
	msgbox Route110_Text_EdwinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Dale:: @ 81EF482
	trainerbattle_single TRAINER_DALE, Route110_Text_DaleIntro, Route110_Text_DaleDefeated
	msgbox Route110_Text_DalePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jacob:: @ 81EF499
	trainerbattle_single TRAINER_JACOB, Route110_Text_JacobIntro, Route110_Text_JacobDefeated
	msgbox Route110_Text_JacobPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Anthony:: @ 81EF4B0
	trainerbattle_single TRAINER_ANTHONY, Route110_Text_AnthonyIntro, Route110_Text_AnthonyDefeated
	msgbox Route110_Text_AnthonyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Benjamin:: @ 81EF4C7
	trainerbattle_single TRAINER_BENJAMIN_1, Route110_Text_BenjaminIntro, Route110_Text_BenjaminDefeated, Route110_EventScript_BenjaminRegisterMatchCallAfterBattle
	msgbox Route110_Text_BenjaminPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_BenjaminRegisterMatchCallAfterBattle:: @ 81EF4F3
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_BenjaminRegister, MSGBOX_DEFAULT
	@nop Trainer_BENJAMIN_1
	release
	end

Route110_EventScript_BenjaminRematch:: @ 81EF512
	trainerbattle_rematch TRAINER_BENJAMIN_1, Route110_Text_BenjaminRematchIntro, Route110_Text_BenjaminRematchDefeated
	msgbox Route110_Text_BenjaminRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jasmine:: @ 81EF529
	trainerbattle_single TRAINER_JASMINE, Route110_Text_JasmineIntro, Route110_Text_JasmineDefeated
	msgbox Route110_Text_JasminePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Abigail:: @ 81EF540
	trainerbattle_single TRAINER_ABIGAIL_1, Route110_Text_AbigailIntro, Route110_Text_AbigailDefeated, Route110_EventScript_AbigailRegisterMatchCallAfterBattle
	msgbox Route110_Text_AbigailPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_AbigailRegisterMatchCallAfterBattle:: @ 81EF56C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_AbigailRegister, MSGBOX_DEFAULT
	@nop Trainer_ABIGAIL_1
	release
	end

Route110_EventScript_AbigailRematch:: @ 81EF58B
	trainerbattle_rematch TRAINER_ABIGAIL_1, Route110_Text_AbigailRematchIntro, Route110_Text_AbigailRematchDefeated
	msgbox Route110_Text_AbigailRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Isabel:: @ 81EF5A2
	trainerbattle_single TRAINER_ISABEL_1, Route110_Text_IsabelIntro, Route110_Text_IsabelDefeated, Route110_EventScript_IsabelRegisterMatchCallAfterBattle
	msgbox Route110_Text_IsabelPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_IsabelRegisterMatchCallAfterBattle:: @ 81EF5CE
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_IsabelRegister, MSGBOX_DEFAULT
	@nop Trainer_ISABEL_1
	release
	end

Route110_EventScript_IsabelRematch:: @ 81EF5ED
	trainerbattle_rematch TRAINER_ISABEL_1, Route110_Text_IsabelRematchIntro, Route110_Text_IsabelRematchDefeated
	msgbox Route110_Text_IsabelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Timmy:: @ 81EF604
	trainerbattle_single TRAINER_TIMMY, Route110_Text_TimmyIntro, Route110_Text_TimmyDefeated
	msgbox Route110_Text_TimmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Unused:: @ 81EF61B
	end

Route110_EventScript_Kaleb:: @ 81EF61C
	trainerbattle_single TRAINER_KALEB, Route110_Text_KalebIntro, Route110_Text_KalebDefeated
	msgbox Route110_Text_KalebPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Joseph:: @ 81EF633
	trainerbattle_single TRAINER_JOSEPH, Route110_Text_JosephIntro, Route110_Text_JosephDefeated
	msgbox Route110_Text_JosephPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Alyssa:: @ 81EF64A
	trainerbattle_single TRAINER_ALYSSA, Route110_Text_AlyssaIntro, Route110_Text_AlyssaDefeated
	msgbox Route110_Text_AlyssaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_RivalScene:: @ 81EF76E	
	goto_if_set FLAG_RYU_INTERACTED_RIVAL_R110, ryu_end
	lockall
	faceplayer
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq Route110_EventScript_PlayDawnMusic
	compare VAR_RESULT, FEMALE
	call_if_eq Route110_EventScript_PlayBrendanMusic
	applymovement 23, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	applymovement 23, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 23, Common_Movement_Delay48
	waitmovement 0
	delay 30
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq Route110_EventScript_DawnBattle
	compare VAR_RESULT, FEMALE
	goto_if_eq Route110_EventScript_BrendanBattle
	releaseall
	end

Route110_EventScript_PlayDawnMusic:: @ 81EF7E1
	playbgm MUS_GIRL_SUP, 1
	return

Route110_EventScript_PlayBrendanMusic:: @ 81EF7E6
	playbgm MUS_BOY_SUP, 1
	return

Route110_EventScript_DawnBattle:: @ 81EF7EB
	delay 5
	fadescreen FADE_TO_BLACK
	drawfullscreenimage SCENEBGDAWN
	msgbox Route110_Text_DawnLetsBattle, MSGBOX_DEFAULT
	goto Route110_EventScript_DawnBattleTreecko
	end

Route110_EventScript_DawnBattleTreecko:: @ 81EF81A
	trainerbattle_no_intro TRAINER_DAWN_3, Route110_Text_DawnDefeated
	goto Route110_EventScript_DawnDefeated
	end

Route110_EventScript_DawnDefeated:: @ 81EF84A
	fadescreen FADE_TO_BLACK
	drawfullscreenimage SCENEBGDAWN
	msgbox Route110_Text_DawnTakeThis, MSGBOX_DEFAULT
	call Route110_EventScript_GiveWaystone
	msgbox Route110_Text_DawnExplainWaystone, MSGBOX_DEFAULT
	clearfullscreenimage
	fadescreen FADE_FROM_BLACK
	goto Route110_EventScript_RivalExit
	end

Route110_EventScript_BrendanBattle:: @ 81EF865
	delay 5	
	fadescreen FADE_TO_BLACK
	drawfullscreenimage SCENEBGBRENDAN
	msgbox Route110_Text_BrendayLetsBattle, MSGBOX_DEFAULT
	clearfullscreenimage
	fadescreen FADE_TO_BLACK
	goto Route110_EventScript_BrendanBattleMudkip
	end

Route110_EventScript_BrendanBattleMudkip:: @ 81EF8B4
	trainerbattle_no_intro TRAINER_BRENDAN_3, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanDefeated:: @ 81EF8C4
	delay 5	
	drawfullscreenimage SCENEBGBRENDAN
	msgbox Route110_Text_BrendanTakeThis, MSGBOX_DEFAULT
	call Route110_EventScript_GiveWaystone
	msgbox Route110_Text_BrendanExplainWaystone, MSGBOX_DEFAULT
	clearfullscreenimage
	goto Route110_EventScript_RivalExit
	end

Route110_EventScript_GiveWaystone:: @ 81EF8DF
	giveitem ITEM_WAYSTONE
	return

Route110_EventScript_RivalExit:: @ 81EF8EC
	closemessage
	compare VAR_0x8008, 1
	call_if_eq Route110_EventScript_MoveRival1
	compare VAR_0x8008, 2
	call_if_eq Route110_EventScript_MoveRival2
	compare VAR_0x8008, 3
	call_if_eq Route110_EventScript_MoveRival3
	setobjectmovementtype 23, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype 24, MOVEMENT_TYPE_FACE_RIGHT
	removeobject 23
	addobject 24
	delay 45
	compare VAR_0x8008, 1
	call_if_eq Route110_EventScript_RivalExit1
	compare VAR_0x8008, 2
	call_if_eq Route110_EventScript_RivalExit2
	compare VAR_0x8008, 3
	call_if_eq Route110_EventScript_RivalExit3
	removeobject 24
	setflag FLAG_RYU_INTERACTED_RIVAL_R110
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route110_EventScript_RivalApproachPlayer1:: @ 81EF94E
	applymovement 23, Route110_Movement_RivalApproachPlayer1
	waitmovement 0
	return

Route110_EventScript_RivalApproachPlayer2:: @ 81EF959
	applymovement 23, Route110_Movement_RivalApproachPlayer2
	waitmovement 0
	return

Route110_EventScript_RivalApproachPlayer3:: @ 81EF964
	applymovement 23, Route110_Movement_RivalApproachPlayer3
	waitmovement 0
	return

Route110_EventScript_RivalExit1:: @ 81EF96F
	applymovement 24, Route110_Movement_RivalExit1
	waitmovement 0
	return

Route110_EventScript_RivalExit2:: @ 81EF97A
	applymovement 24, Route110_Movement_RivalExit2
	waitmovement 0
	return

Route110_EventScript_RivalExit3:: @ 81EF985
	applymovement 24, Route110_Movement_RivalExit3
	waitmovement 0
	return

Route110_EventScript_MoveRival1:: @ 81EF990
	setobjectxyperm 24, 33, 55
	return

Route110_EventScript_MoveRival2:: @ 81EF998
	setobjectxyperm 24, 34, 55
	return

Route110_EventScript_MoveRival3:: @ 81EF9A0
	setobjectxyperm 24, 35, 55
	return

Route110_Movement_RivalApproachPlayer1: @ 81EF9A8
	walk_down
	walk_left
	walk_in_place_fastest_down
	step_end

Route110_Movement_RivalApproachPlayer2: @ 81EF9AC
	walk_down
	step_end

Route110_Movement_RivalApproachPlayer3: @ 81EF9AE
	walk_down
	walk_right
	walk_in_place_fastest_down
	step_end

Route110_Movement_RivalExit1: @ 81EF9B2
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route110_Movement_RivalExit2: @ 81EF9BA
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_down
	step_end

Route110_Movement_RivalExit3: @ 81EF9C3
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route110_EventScript_BirchScene1:: @ 81EF9CB
	lockall
	setvar VAR_0x8008, 1
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene2:: @ 81EF9D6
	lockall
	setvar VAR_0x8008, 2
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene3:: @ 81EF9E1
	lockall
	setvar VAR_0x8008, 3
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene4:: @ 81EF9EC
	lockall
	setvar VAR_0x8008, 4
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene:: @ 81EF9F7
	addobject 36
	applymovement 36, Route110_Movement_BirchEntrance
	waitmovement 0
	playse SE_PIN
	applymovement 36, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 36, Common_Movement_Delay48
	waitmovement 0
	compare VAR_0x8008, 1
	call_if_eq Route110_EventScript_BirchApproachPlayer1
	compare VAR_0x8008, 2
	call_if_eq Route110_EventScript_BirchApproachPlayer2
	compare VAR_0x8008, 3
	call_if_eq Route110_EventScript_BirchApproachPlayer3
	compare VAR_0x8008, 4
	call_if_eq Route110_EventScript_BirchApproachPlayer4
	msgbox Route110_Text_ImagineSeeingYouHere, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement 36, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	delay 10
	applymovement 36, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 20
	applymovement 36, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 30
	msgbox Route110_Text_HeardYouInstallMatchCall, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_ME_TORE_EYE
	msgbox Route110_Text_RegisteredBirchInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	msgbox Route110_Text_KeepAnEyeOutForRival, MSGBOX_DEFAULT
	closemessage
	compare VAR_0x8008, 1
	call_if_eq Route110_EventScript_BirchExit1
	compare VAR_0x8008, 2
	call_if_eq Route110_EventScript_BirchExit2
	compare VAR_0x8008, 3
	call_if_eq Route110_EventScript_BirchExit3
	compare VAR_0x8008, 4
	call_if_eq Route110_EventScript_BirchExit4
	removeobject 36
	setvar VAR_REGISTER_BIRCH_STATE, 2
	releaseall
	end

Route110_EventScript_BirchApproachPlayer1:: @ 81EFAD8
	applymovement 36, Route110_Movement_BirchApproachPlayer1
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer2:: @ 81EFAE3
	applymovement 36, Route110_Movement_BirchApproachPlayer2
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer3:: @ 81EFAEE
	applymovement 36, Route110_Movement_BirchApproachPlayer3
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer4:: @ 81EFAF9
	applymovement 36, Route110_Movement_BirchApproachPlayer4
	waitmovement 0
	return

Route110_EventScript_BirchExit1:: @ 81EFB04
	applymovement 36, Route110_Movement_BirchExit1
	waitmovement 0
	return

Route110_EventScript_BirchExit2:: @ 81EFB0F
	applymovement 36, Route110_Movement_BirchExit2
	waitmovement 0
	return

Route110_EventScript_BirchExit3:: @ 81EFB1A
	applymovement 36, Route110_Movement_BirchExit3
	waitmovement 0
	return

Route110_EventScript_BirchExit4:: @ 81EFB25
	applymovement 36, Route110_Movement_BirchExit4
	waitmovement 0
	return

Route110_Movement_BirchEntrance: @ 81EFB30
	walk_down
	walk_down
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer1: @ 81EFB34
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer2: @ 81EFB39
	walk_down
	walk_left
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer3: @ 81EFB3D
	walk_down
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer4: @ 81EFB40
	walk_down
	walk_right
	walk_down
	step_end

Route110_Movement_BirchExit1: @ 81EFB44
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit2: @ 81EFB4B
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit3: @ 81EFB51
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit4: @ 81EFB57
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Text_WeCantTalkAboutAquaActivities: @ 81EFB5D
	.string "Team Aqua's activities…\n"
	.string "We can't talk about them yet.$"

Route110_Text_KickUpARuckus: @ 81EFB93
	.string "I want to get going to Slateport and\n"
	.string "kick up a ruckus!$"

Route110_Text_MyFirstJobInAqua: @ 81EFBCA
	.string "This is my first job after joining\n"
	.string "Team Aqua. It's a little scary.$"

Route110_Text_AquaActionsBringSmiles: @ 81EFC0D
	.string "Team Aqua's actions should bring\n"
	.string "smiles to people's faces!$"

Route110_Text_DawnLetsBattle: @ 81EFC48
	.string "{COLOR LIGHT_RED}{SHADOW RED}Hi, {PLAYER}, long time no see!\p"
	.string "While I was searching for other\n"
	.string "Pokémon, my Pokémon grew stronger.\p"
	.string "So…\n"
	.string "How about a little battle?$"

Route110_Text_DawnDefeated: @ 81EFCCB
	.string "Ow!\n"
	.string "You really had your way with me!$"

Route110_Text_DawnTakeThis: @ 81EFCF1
	.string "{COLOR LIGHT_RED}{SHADOW RED}{PLAYER}, you've been busy\n"
	.string "training, too, haven't you?\p"
	.string "I think you deserve a reward!\n"
	.string "This is from me!$"

Route110_Text_DawnExplainWaystone: @ 81EFD58
	.string "{COLOR LIGHT_RED}{SHADOW RED}That's a Waystone.\p"
	.string "It lets you teleport to any city\n"
	.string "you have visited.\p"
	.string "Okay, {PLAYER}, let's meet again!\p"
	.string "I know it's a little silly coming from\n"
	.string "me, but I think you should train a lot\l"
	.string "harder for the next time.$"

Route110_Text_BrendayLetsBattle: @ 81EFE3F
	.string "{COLOR LIGHT_RED}{SHADOW RED}Hey, {PLAYER}. Fancy\n"
	.string "meeting you here.\p"
	.string "How's it going? Have you been\n"
	.string "raising your pokémon?\lI'll check for you.$"

r110_maleRivalIntroText2:
	.string "{COLOR LIGHT_BLUE}{SHADOW BLUE}How? With a battle, of course.\p"
	.string "Show me your stuff!$"

Route110_Text_BrendanDefeated: @ 81EFEB4
	.string "Hmm… not gonna lie, I'm pretty miffed.\n"
	.string "And maybe a little turned on.$"

Route110_Text_BrendanTakeThis: @ 81EFECD
	.string "{COLOR LIGHT_RED}{SHADOW RED}Jeez, {PLAYER}, You've\n"
	.string "trained up... \n"
	.string "I like that.\l"
	.string "Here, you can have this.$"

Route110_Text_BrendanExplainWaystone: @ 81EFF1C
	.string "{COLOR LIGHT_RED}{SHADOW RED}That thing's called a\n"
	.string "Waystone.\p"
	.string "Rub it the right way to travel\n"
	.string "anywhere you've been to before.\p"
	.string "… … …\p"
	.string "Well, I'll be heading off now.\n"
	.string "See ya around, {PLAYER}.\l"
	.string "Keep training!$"

Route110_Text_RideBikeAtFullSpeed: @ 81EFFC3
	.string "Wouldn't it be great to ride a Bike\n"
	.string "at full speed on Cycling Road?$"

Route110_Text_HairStreamsBehindMe: @ 81F0006
	.string "How do you like the way my raven-\n"
	.string "colored hair streams behind me?\p"
	.string "I grew my hair out just for that.$"

Route110_Text_YouGotBikeFromRydel: @ 81F006A
	.string "Oh, hey, you got that Bike from Rydel!\p"
	.string "Oh, it's glaringly obvious.\n"
	.string "It says right on your bike…\p"
	.string "Rydel, Rydel, Rydel, Rydel, Rydel,\n"
	.string "Rydel, Rydel, Rydel, Rydel, Rydel,\p"
	.string "Rydel, Rydel, Rydel, Rydel, Rydel,\n"
	.string "Rydel, Rydel, Rydel, Rydel, Rydel,\p"
	.string "Rydel, Rydel, Rydel, Rydel, Rydel,\n"
	.string "Rydel, Rydel, Rydel, Rydel, Rydel,\p"
	.string "Rydel, Rydel, Rydel, Rydel, Rydel,\n"
	.string "Rydel, Rydel, Rydel, Rydel, Rydel,\p"
	.string "Rydel, Rydel, Rydel, Rydel, Rydel…\n"
	.string "That name's everywhere.\p"
	.string "You should ride it around all over\n"
	.string "the place--it's good advertising!$"

Route110_Text_TwoRoads: @ 81F0261
	.string "The two roads, one above, one below…\p"
	.string "A road each for people and Pokémon.\n"
	.string "Perhaps that is right and fair.$"

Route110_Text_WalkOnTheLowRoad: @ 81F02CA
	.string "I don't have a Bike, so I'll take\n"
	.string "a leisurely walk on the low road.$"

Route110_Text_BikeTechniques: @ 81F030E
	.string "Learning techniques will make Bike\n"
	.string "riding even more fun.\p"
	.string "There are some places that you can\n"
	.string "reach only by using a Bike technique.$"

Route110_Text_WhichShouldIChoose: @ 81F0390
	.string "Which should I choose?\p"
	.string "Make a beeline for Mauville on\n"
	.string "Cycling Road, or take the low road\l"
	.string "and look for Pokémon?$"

Route110_Text_SlateportCitySign: @ 81F0812
	.string "Route 110\n"
	.string "{DOWN_ARROW} SLATEPORT CITY$"

Route110_Text_CyclingRoadSign: @ 81F082D
	.string "Seaside Cycling Road$"

Route110_Text_AquaWasHere: @ 81F0842
	.string "“Team Aqua was here!”\p"
	.string "Someone painted that onto this sign,\n"
	.string "but then someone else painted over it.\p"
	.string "“Team Magma rules!” is what it\n"
	.string "says now.$"

Route110_Text_Route103Sign: @ 81F08CD
	.string "Route 110\n"
	.string "{LEFT_ARROW} ROUTE 103$"

Route110_Text_SeasideParkingSign: @ 81F08E3
	.string "Seaside Parking$"

Route110_Text_MauvilleCitySign: @ 81F08F3
	.string "Route 110\n"
	.string "{UP_ARROW} MAUVILLE CITY$"

Route110_Text_TrainerTipsPrlzSleep: @ 81F090D
	.string "Trainer Tips\p"
	.string "The foe can be made helpless by\n"
	.string "paralyzing it or causing it to sleep.\p"
	.string "It is an important technique for\n"
	.string "Pokémon battles.$"

Route110_Text_TrainerTipsRegisterItems: @ 81F0992
	.string "Trainer Tips\p"
	.string "The items in the Pack can be reorganized\n"
	.string "by pressing Select.$"

Route110_Text_TrickHouseSign: @ 81F09DB
	.string "“Three steps {RIGHT_ARROW} and two steps {UP_ARROW}\n"
	.string "to reach the wondrous Trick House.”$"

Route110_Text_BestRecord: @ 81F0A1E
	.string "The Best Record TO Date…\p"
	.string "No. of collisions: {STR_VAR_1}\p"
	.string "Elapsed time: {STR_VAR_2}$"

Route110_Text_ThereIsNoRecord: @ 81F0A5E
	.string "The Best Record TO Date…\p"
	.string "No one seems to have taken the\n"
	.string "challenge. There is no record…$"

Route110_Text_ImagineSeeingYouHere: @ 81F0AB5
	.string "Prof. Birch: Oh, {PLAYER}!\n"
	.string "Imagine seeing you here!\p"
	.string "And where might my {RIVAL} be?$"

Route110_Text_HeardYouInstallMatchCall: @ 81F0AFF
	.string "Oh, I see!\n"
	.string "You two are running separately.\l"
	.string "Well, that's fine.\p"
	.string "Oh, yes, I heard that your Pokénav\n"
	.string "had the Match Call system installed.\p"
	.string "Well, then, I should register you in\n"
	.string "my Pokénav as well.\p"
	.string "That way, even when we're apart,\n"
	.string "I can rate your Pokédex anytime.\p"
	.string "… … … … … …$"

Route110_Text_RegisteredBirchInPokenav: @ 81F0C0C
	.string "Registered Prof. Birch\n"
	.string "in the Pokénav.$"

Route110_Text_KeepAnEyeOutForRival: @ 81F0C33
	.string "Prof. Birch: {PLAYER}…\p"
	.string "Please keep an eye out for my {RIVAL}.\n"
	.string "… … … … … …\p"
	.string "Well, I had better get going.\n"
	.string "See you again, {PLAYER}!$"


@@ Faction related

r110_Pikachu::
	goto_if_set FLAG_RYU_HELPED_POKEFAN_PIKACHU, r110_PikachuHelped
	goto_if_set FLAG_RYU_DID_NOT_HELP_POKEFAN, r110_PikachuNotHelped
	msgbox r110_PikachuLooksSick
	playmoncry SPECIES_PIKACHU, 3
	release
	end

r110_PikachuHelped::
	msgbox r110_PikachuLooksInGoodHealth
	playmoncry SPECIES_PIKACHU, 0
	release
	end

r110_PikachuNotHelped::
	msgbox r110_PikachuLooksFine
	playmoncry SPECIES_PIKACHU, 1
	release
	end

r110_PokefanSickPika::
	goto_if_set FLAG_RYU_HELPED_POKEFAN_PIKACHU, r110_PokefanHelped
	goto_if_set FLAG_RYU_DID_NOT_HELP_POKEFAN, r110_PokefanNotHelped
	playse SE_PIN
	applymovement 31, Common_Movement_ExclamationMark
	waitmovement 31
	msgbox r110_SickPikaIntro
	closemessage
	delay 30
	faceplayer
	msgbox r110_HealingItemQuery, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq r110_SickPikaDeclined
	setvar VAR_TEMP_2, 0
	special Bag_ChooseMedicine
	waitstate
	goto r110_CheckSelectedItem
	release
	end

r110_CheckSelectedItem::
	bufferitemname 0, VAR_ITEM_ID
	switch VAR_ITEM_ID
	case ITEM_ANTIDOTE, r110_SelectedAdequateItem
	case ITEM_CHERI_BERRY, r110_SelectedAdequateItem
	case ITEM_FULL_RESTORE, r110_SelectedBestItem
	case ITEM_FULL_HEAL, r110_SelectedAdequateItem
	case ITEM_NONE, r110_SelectedNoItem
	goto r110_SelectedWrongItem

r110_SelectedAdequateItem::
	removeitem VAR_ITEM_ID, 1
	msgbox r110_PikachuLooksBetter
	changefactionstanding FACTION_POKEFANS, 30, FALSE
	setflag FLAG_RYU_HELPED_POKEFAN_PIKACHU
	ach give ACH_FIELD_MEDIC
	release
	end

r110_SelectedBestItem::
	removeitem VAR_ITEM_ID, 1
	msgbox r110_PikaPerkedUp
	changefactionstanding FACTION_POKEFANS, 50, FALSE
	setflag FLAG_RYU_HELPED_POKEFAN_PIKACHU
	ach give ACH_FIELD_MEDIC
	release
	end

r110_SelectedNoItem::
	msgbox r110_PlayerDidntHelpPika
	changefactionstanding FACTION_POKEFANS 20, TRUE
	setflag FLAG_RYU_DID_NOT_HELP_POKEFAN
	release
	end

r110_SelectedWrongItem::
	removeitem VAR_ITEM_ID, 1
	addvar VAR_TEMP_2, 1
	compare VAR_TEMP_2, 3
	goto_if_ge r110_PikaItemTriesExceeded
	msgbox r110_TryAgainQuery, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq r110_SelectedNoItem
	special Bag_ChooseMedicine
	waitstate
	goto r110_CheckSelectedItem

r110_SickPikaDeclined::
	msgbox r110_PlayerLeftSickPikaAlone
	changefactionstanding FACTION_POKEFANS 50, TRUE
	setflag FLAG_RYU_DID_NOT_HELP_POKEFAN
	closemessage
	release
	end

r110_PikaItemTriesExceeded::
	msgbox r110_NothingSeemsToWork
	changefactionstanding FACTION_POKEFANS 20, TRUE
	setflag FLAG_RYU_DID_NOT_HELP_POKEFAN
	release
	end

r110_PokefanHelped::
	msgbox r110_PokefanRemembersPlayer
	closemessage
	goto_if_unset FLAG_RYU_REWARDED_FOR_HELPING_POKEFAN, r110_giveGift
	release
	end

r110_giveGift::
	setflag FLAG_RYU_REWARDED_FOR_HELPING_POKEFAN
	giveitem ITEM_RARE_CANDY, 5
	closemessage
	release
	end

r110_PokefanNotHelped::
	msgbox r110_LeaveUsAlone
	closemessage
	release
	end


r110_PikachuLooksInGoodHealth:
	.string "The Pikachu appears to be in\ngood health and happy.$"

r110_PikachuLooksFine:
	.string "It's a Pikachu. It looks happy.$"

r110_PikachuLooksSick:
	.string "The pikachu looks rather sick.\nIt has dark circles under its\leyes...$"

r110_LeaveUsAlone:
	.string "Oh... It's you...\nCould you go away, please?$"

r110_PlayerDidntHelpPika:
	.string "{COLOR LIGHT_BLUE}{SHADOW BLUE}Sorry... I thought I had something\nthat could help...$"

r110_TryAgainQuery:
	.string "The {STR_VAR_1} didn't seem to help...\nTry another item?$"

r110_PokefanRemembersPlayer:
	.string "Oh! It's you!\pPikachu's been doing great, thank\nyou so much for your kindness!\pTake this gift from me!$"

r110_NothingSeemsToWork:
	.string "{COLOR LIGHT_GREEN}{SHADOW GREEN} (Nothing seems to work...\n Best I leave it alone, don't want to\l make it worse...)$"

r110_PikachuLooksBetter:
	.string "Oh? OH! My beloved Pikachu looks\nbetter! Thank you so much!$"

r110_PikaPerkedUp:
	.string "{COLOR LIGHT_GREEN}{SHADOW GREEN} (The Pikachu perked right up.\n It's back to full health!)\p"
	.string "{COLOR DARK_GREY}{SHADOW LIGHT_GREY}Oh! Wow! Are you a doctor or\nsomething? Maybe a miracle worker?\pShe made a full recovery\nThank you so much!$"

r110_SickPikaIntro:
	.string "Ohhh, Pikachu, what do I do,\nhow can I help you?\p {COLOR LIGHT_GREEN}{SHADOW GREEN}(The lady is clearly distressed\n about something.)$"

r110_HealingItemQuery:
	.string "I think my Pikachu is sick, but I\n"
	.string "don't know how to help her!\p"
	.string "Do you have something that can\n"
	.string "help?\p"
	.string "{COLOR LIGHT_GREEN}{SHADOW GREEN} (Upon closer inspection, the Pikachu\n"
	.string " appears to be poisoned.)\p"
	.string "{COLOR DARK_GREY}{SHADOW LIGHT_GREY}Would you like to use an item\n"
	.string "on it to help?$"

r110_PlayerLeftSickPikaAlone:
	.string "{COLOR LIGHT_GREEN}{SHADOW GREEN} ({PLAYER} left the trainer and her Pikachu\n alone.)$"
