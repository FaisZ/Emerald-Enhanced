SlateportCity_OceanicMuseum_2F_MapScripts:: @ 820BAFF
	map_script ON_FRAME, OM_OnFrameScript
	.byte 0

OM_OnFrameScript::
	map_script_2 VAR_RYU_AQUA, 30, OM_AquaEvent2
	map_script_2 VAR_TEMP_5, 0, OM_ReEnableStern
	map_script_2 VAR_RYU_DEVON, 165, OM_SetupSternForDevon
	.2byte 0

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1:: @ 820BD0A
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2:: @ 820BD13
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment:: @ 820BD1C
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel:: @ 820BD25
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay:: @ 820BD2E
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay:: @ 820BD37
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica:: @ 820BD40
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica:: @ 820BD49
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica:: @ 820BD52
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica:: @ 820BD5B
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1:: @ 820BD64
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2:: @ 820BD6D
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3:: @ 820BD76
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip: @ 820C43F
	.string "I saw a model of a ship here.\p"
	.string "It reminded me of the Abandoned Ship\n"
	.string "near Dewford Town…$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum: @ 820C495
	.string "Don't you dare run around inside\n"
	.string "the Museum!$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine: @ 820C4C2
	.string "Wow, the submarine's awesome!\n"
	.string "I want to go for a ride!$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1: @ 820C4F9
	.string "“WATER Quality Sample 1,” the\n"
	.string "label says.\p"
	.string "The sea is all connected, but the\n"
	.string "water seems to differ by region.$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2: @ 820C566
	.string "“WATER Quality Sample 2,” the\n"
	.string "label says.\p"
	.string "Does the saltiness of seawater differ\n"
	.string "by region, too?$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment: @ 820C5C6
	.string "A rubber ball is expanding and\n"
	.string "shrinking.\p"
	.string "“In the sea, the weight of water itself\n"
	.string "exerts pressure.\p"
	.string "“In shallow water, the pressure is not\n"
	.string "very heavy.\p"
	.string "“However, in extremely deep water,\n"
	.string "the pressure can reach even tens of\l"
	.string "thousands of tons on a small area.”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel: @ 820C6C7
	.string "“MODEL OF Hoenn REGION”\p"
	.string "It's a miniature diorama of the\n"
	.string "Hoenn region.\p"
	.string "Where is Littleroot Town on this?$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay: @ 820C72F
	.string "It's a display on the flow of seawater.\p"
	.string "“Near the bottom of the sea, water\n"
	.string "flows due to differences in such\l"
	.string "factors as temperature and salinity.”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay: @ 820C7C1
	.string "It's a display on the flow of seawater.\p"
	.string "“Toward the surface, seawater flows\n"
	.string "as currents driven by the winds.”$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica: @ 820C82F
	.string "“THE Ferry S.S. Tidal\p"
	.string "“A scale replica of the ship under\n"
	.string "construction at Stern's Shipyard.”$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica: @ 820C88B
	.string "“SUBMARINE Explorer 1\p"
	.string "“A replica of the high-performance\n"
	.string "ocean floor exploration submarine.”$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica: @ 820C8E8
	.string "“SUBMERSIBLE Pod\p"
	.string "“A replica of a compact, unmanned\n"
	.string "pod for seafloor exploration.”$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica: @ 820C93A
	.string "“S.S. Anne\p"
	.string "“A replica of the luxury liner that\n"
	.string "circles the globe.”$"



@==================================================================================================Aqua Events

OM_AquaEvent2::
	setvar VAR_RYU_AQUA, 35 @player entered museum 2f
	addobject 4
	addobject 5
	clearflag FLAG_HIDE_CHAMPIONS_ROOM_STEVEN
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, OM_CameraToStern
	waitmovement OBJ_EVENT_ID_CAMERA
	msgbox OM_ISeeThats
	closemessage
	playse SE_PIN
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 5
	msgbox OM_WhosThere
	closemessage
	applymovement 5, Common_Movement_FaceLeft
	waitmovement 5
	applymovement OBJ_EVENT_ID_CAMERA, OM_CameraToPlayer
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, OM_PlayerToSteven
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox OM_ATrainer
	closemessage
	msgbox OM_StevenNotices
	closemessage
	msgbox OM_NoYoure
	closemessage
	applymovement 5, Common_Movement_FaceRight
	waitmovement 5
	msgbox OM_WellContinue
	closemessage
	applymovement 4, OM_SternExit
	waitmovement 4
	removeobject 4
	applymovement 5, Common_Movement_StepLeft
	waitmovement 5
	setvar VAR_RYU_AQUA, 40@Player is about to lose to steven
	setflag FLAG_TEMP_E@Required for calcDmg to make steven actually deadly.
	trainerbattle_single TRAINER_STEVEN, OM_IllMakeYouRegret, OM_YouBroughtThis, OM_PlayerLostTheFight

OM_PlayerLostTheFight::
	fadescreen FADE_TO_BLACK
	playbgm MUS_DUMMY
	msgbox OM_PlayerWhitedOut
	closemessage
	setvar VAR_RYU_AQUA, 45 @player lost to steven, teleporting to aqua office
	clearflag FLAG_TEMP_E
	warpsilent MAP_LILYCOVE_CITY_AQUA_CORPORATE_OFFICE, 255, 30, 2
	waitstate


OM_ISeeThats:
	.string "I see...that's quite a setback.\n"
    .string "On behalf of President Stone, as well\p"
    .string "as Devon Corp., rest assured that we\n"
    .string "will be able to-$"

OM_WhosThere:
	.string "Who's there?$"
	
OM_ATrainer:
	.string "A Trainer?$"
	
OM_StevenNotices:
	.string "{COLOR LIGHT_GREEN}{SHADOW GREEN} (Steven notices the Aqua Pendant.)$"
	
OM_NoYoure:
	.string "No...you're with Team Aqua, aren't\n"
    .string "you?\p"
    .string "The lot of you are becoming quite\n"
    .string "bold as of late.$"

OM_WellContinue:
	.string "We'll continue our talks later.\n"
    .string "For now, it'd be best if you're not\p"
    .string "here.\n"
    .string "Let my employee downstairs accompany\p"
    .string "you.$"

OM_IllMakeYouRegret:
	.string "I'll make you regret choosing to walk\n"
    .string "this path.$"

OM_YouBroughtThis:
	.string "You brought this upon yourself.$"
	
OM_PlayerWhitedOut:
	.string "{COLOR LIGHT_GREEN}{SHADOW GREEN} {PLAYER}'s vision fades...$"
	
OM_CameraToStern:
	walk_diag_southeast
	walk_diag_southeast
	walk_diag_southeast
	walk_diag_southeast
	walk_down
	step_end
	
OM_CameraToPlayer:
	walk_up
	walk_diag_northwest
	walk_diag_northwest
	walk_diag_northwest
	walk_diag_northwest
	step_end
	
OM_PlayerToSteven:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
	
OM_SternExit:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
	
	
@==================================================================================================Devon Events

OM_checkFollowerForDevonEvent::
	lockall
	setvar VAR_RYU_DEVON, 165
	goto_if_unset FLAG_RYU_HAS_FOLLOWER, ryu_end
	compare VAR_RYU_FOLLOWER_ID, OBJ_EVENT_GFX_NURSE
	goto_if_eq OMDevonCheckForNurse
	call RyuForceCancelFollowerForQuest
	releaseall
	end

OMDevonCheckForNurse::
	compare VAR_RYU_DS_NURSE_STAGE, 10
	goto_if_ne OM_CantDoThisQuestBecauseNurse
	setvar VAR_RYU_DEVON, 165
	releaseall
	end

OM_CantDoThisQuestBecauseNurse::
	msgbox OM_NurseCancel
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_StepDown
	applymovement OBJ_EVENT_ID_FOLLOWER, Common_Movement_StepDown
	waitmovement OBJ_EVENT_ID_FOLLOWER
	release
	end

OM_NurseCancel:
	.string "{COLOR LIGHT_GREEN}{SHADOW GREEN}You cannot do this quest stage\n"
	.string "because you are presently doing\l"
	.string "the Nurse quest.\p"
	.string "Please come back when you have\n"
	.string "finished the Nurse quest.$"

OM_SetupSternForDevon::
OM_ReEnableStern::
	setvar VAR_TEMP_5, 10
	goto_if_set FLAG_RYU_DEVON_STERN_EVENT_DONE, OM_FinishedSternEvent
	compare VAR_RYU_AQUA, 70
	goto_if_ge ryu_end
	setvar VAR_RYU_DEVON, 17 @Player is on second floor to speak with Stern.
	addobject 4
	end

OM_FinishedSternEvent::
	setvar VAR_RYU_DEVON, 18
	release
	end
	
OM_CaptainStern::
	goto_if_set FLAG_RYU_PLAYER_HELPING_AQUA, ryu_end
	compare VAR_RYU_DEVON, 18
	goto_if_ge OM_AlreadyDoneScene
	msgbox OM_ThanksForBringing
	closemessage
	fadescreen FADE_TO_BLACK
	msgbox OM_WhatHappenedToTheLights
	closemessage
	createfollower OBJ_EVENT_GFX_ARCHIE, NULL, DIR_WEST
	applymovement OBJ_EVENT_ID_FOLLOWER, OM_ArchieToEntrance
	waitmovement OBJ_EVENT_ID_FOLLOWER
	fadescreen FADE_FROM_BLACK
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 4
	msgbox OM_WhatAreYouDoing
	closemessage
	applymovement OBJ_EVENT_ID_FOLLOWER, OM_ArchieToPlayer
	waitmovement OBJ_EVENT_ID_FOLLOWER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox OM_ImArchieHandOver
	closemessage
	setflag FLAG_RYU_GAME_OVER
	trainerbattle_single TRAINER_ARCHIE, OM_ArchieIntro, OM_ArchieDefeat, OM_ArchieSceneEnd
	goto OM_ArchieSceneEnd
	
OM_ArchieSceneEnd::
	clearflag FLAG_RYU_GAME_OVER
	applymovement 4, Common_Movement_FaceLeft
	waitmovement 4
	msgbox OM_IllLetYouGetAway
	closemessage
	applymovement OBJ_EVENT_ID_FOLLOWER, OM_ArchieToEntrance
	waitmovement OBJ_EVENT_ID_FOLLOWER
	playse SE_KAIDAN
	destroyfollower
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox OM_ThanksForProtecting
	removeitem ITEM_DEVON_GOODS, 1
	setvar VAR_RYU_DEVON, 18 @player spoke with stern and protected him from archie. Return to Devon.
	setflag FLAG_RYU_DEVON_STERN_EVENT_DONE
	release
	end

OM_AlreadyDoneScene::
	msgbox OM_ReturnToDevon
	closemessage
	release
	end

OM_ReturnToDevon:
	.string "I've got the package, please\nreturn to Devon.$"
	
OM_ThanksForBringing:
	.string "Thanks for bringing the package.\nIt's late, but from what I hear,\pI'm lucky we were able to get\nit at all.$"
	
OM_WhatHappenedToTheLights:
	.string "What's happening, why were the\nlights turned off?!$"
	
OM_WhatAreYouDoing:
	.string "Aqua? What are you doing here?$"
	
OM_ImArchieHandOver:
	.string "I'm Archie of team Aqua.\nI'm here to liberate those\lgoods from you.$"
	
OM_ArchieIntro:
	.string "If you won't hand them over\nthen I'll just have to take them!$"
	
OM_ArchieDefeat:
	.string "Just my luck to attack at\nthe one time a competent trainer\lis around...$"
	
OM_IllLetYouGetAway:
	.string "Grr... I'll let you get away\nthis time.$"

OM_ThanksForProtecting:
	.string "Oh, wow, am I fortunate.\nThank you so much for protecting\lme!$"


OM_ArchieToEntrance:
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	walk_fastest_up
	face_down
	step_end

OM_ArchieToPlayer:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
	













