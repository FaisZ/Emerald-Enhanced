MtPyre_6F_MapScripts:: @ 8231D3A
	map_script ON_FRAME, MP_CheckHexerQuest
	.byte 0

MP_CheckHexerQuest::
	map_script_2 VAR_TEMP_0, 0, MP_DoHexerQuestSetup
	.2byte 0

MP_DoHexerQuestSetup:
	setvar VAR_TEMP_0, 10
	goto_if_set FLAG_RYU_HEXER_FACTION_QUEST_ACTIVE, MP_HexerStartFactionEvent
	end

MP_HexerStartFactionEvent::
	playse SE_PIN
	applymovement OBJ_EVENT_ID_FOLLOWER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_FOLLOWER
	applymovement OBJ_EVENT_ID_FOLLOWER, MP_FollowerToGraveStone
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, MP_PlayerToFollower
	waitmovement OBJ_EVENT_ID_PLAYER
	fadescreen FADE_TO_BLACK
	playse SE_W091
	waitse
	delay 10
	playse SE_W091
	waitse
	delay 10
	playse SE_W091
	waitse
	fadescreen FADE_FROM_BLACK
	msgbox MP_HexerEventFinish
	closemessage
	playmoncry SPECIES_MIMIKYU, 2
	msgbox MP_HexerThanks
	closemessage
	changefactionstanding FACTION_OUTCASTS, 50, FALSE
	applymovement OBJ_EVENT_ID_FOLLOWER, MP_FollowerOffScreen
	waitmovement OBJ_EVENT_ID_FOLLOWER
	playse SE_DOOR
	waitse
	destroyfollower
	clearflag FLAG_RYU_HEXER_FACTION_QUEST_ACTIVE
	msgbox MP_FQ_FactionStandingChanged
	ach give ACH_UNDERTAKER
	closemessage
	release
	end

MP_FQ_MimisGrave::
	goto_if_unset FLAG_RYU_HIDE_MTPYRE_HEXER, MP_EmptyGrave
	playmoncry SPECIES_MIMIKYU, 0
	waitmoncry
	msgbox MP_FQ_MimiSaysHi
	closemessage
	goto_if_unset FLAG_RYU_PLAYER_RECEIVED_STANDING_FROM_MIMIS_GRAVE, MP_FQ_GiveStanding
	release
	end

MP_FQ_GiveStanding::
	setflag FLAG_RYU_PLAYER_RECEIVED_STANDING_FROM_MIMIS_GRAVE
	changefactionstanding FACTION_OUTCASTS, 10, FALSE
	release
	end

MP_EmptyGrave::
	msgbox MP_FQ_Empty
	closemessage
	release
	end

MP_FQ_MimiSaysHi:
	.string " {COLOR LIGHT_GREEN}{SHADOW GREEN}(Mimi briefly appears before you\n"
	.string " from behind the gravestone.\p"
	.string " She dances around a little\n"
	.string " and phases back into the grave\l"
	.string " stone.)\p"
	.string "{COLOR LIGHT_BLUE}{SHADOW BLUE}Well, Mimi seems happy.$"


MP_FQ_Empty:
	.string "The gravestone is blank.\nIt must be empty.$"

MP_PlayerToFollower:
	walk_down
	walk_left
	face_left
	step_end


MP_FollowerToGraveStone:
	walk_down
	walk_down
	walk_left
	walk_left
	face_up
	step_end

MP_FollowerOffScreen:
	walk_down
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

MP_HexerEventFinish:
	.string "There! All finished. You can\n"
	.string "move on, now, Mimi!\p"
	.string " {COLOR LIGHT_GREEN}{SHADOW GREEN}(The ghostly Mimikyu spirit\n"
	.string " shows herself once more.\p"
	.string " She floats up to your face\n"
	.string " and gives a flourish then\l"
	.string " disapparates with a final cry...)$"

MP_HexerThanks:
	.string "It seems that in the short time\nwe knew each other, Mimi\lalso took a liking to you!\pThank you so much for helping.\nMimi seemed very grateful as well.$"

MP_FQ_FactionStandingChanged:
	.string " {COLOR LIGHT_BLUE}{SHADOW BLUE}(Your reputation with the Outcasts\n increased considerably.)$"

MtPyre_6F_EventScript_Valerie:: @ 8231D3B
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie:: @ 8231D67
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	@nop Trainer_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie:: @ 8231D86
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric:: @ 8231D9D
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MP_EmptyChanneler::
	msgbox MP_BlankChanneler
	release
	end

MP_BlankChanneler:
	.string "I'm channeling the spirits.\nGo away.$"

MtPyre_6F_Text_ValerieIntro: @ 8231DB4
	.string "When I'm here…\n"
	.string "A curious power flows into me…$"

MtPyre_6F_Text_ValerieDefeat: @ 8231DE2
	.string "The power is ebbing away…$"

MtPyre_6F_Text_ValeriePostBattle: @ 8231DFC
	.string "Perhaps the power is from the spirits\n"
	.string "of Pokémon in fitful sleep here…$"

MtPyre_6F_Text_ValerieRegister: @ 8231E43
	.string "Fufufu… I lost the match, but…\n"
	.string "I have this little ability…\p"
	.string "Without ever laying my hands on\n"
	.string "your POKéNAV… Hiyah!$"

MtPyre_6F_Text_ValerieRematchIntro: @ 8231EB3
	.string "Behind you…\n"
	.string "What is it…$"

MtPyre_6F_Text_ValerieRematchDefeat: @ 8231ECB
	.string "Something faded away…$"

MtPyre_6F_Text_ValeriePostRematch: @ 8231EE1
	.string "The Pokémon at rest here…\n"
	.string "Sometimes, they play…$"

MtPyre_6F_Text_CedricIntro: @ 8231F11
	.string "Have you lost your bearings?\n"
	.string "Have no fear for I am here!$"

MtPyre_6F_Text_CedricDefeat: @ 8231F4A
	.string "Weren't you lost?$"

MtPyre_6F_Text_CedricPostBattle: @ 8231F5C
	.string "I had this feeling that a lost Trainer\n"
	.string "would be panicked and easy to beat.\p"
	.string "It's dirty and I won't try it again…$"

@===================================================================== Leaf Scripts
MP_SetupLeafEvent::
	lock
	goto_if_unset FLAG_RYU_LEAF_ALTERNATE_LINE, ryu_end
	special SpawnCameraObject
	clearflag FLAG_HIDE_CHAMPIONS_ROOM_RIVAL
	addobject 4
	applymovement OBJ_EVENT_ID_CAMERA, MP_CameraMovement1
	waitmovement OBJ_EVENT_ID_CAMERA
	delay 20
	applymovement 4 Common_Movement_FaceUp
	waitmovement 4
	delay 20
	applymovement OBJ_EVENT_ID_CAMERA, MP_CameraMovement2
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	release
	end
	
MP_LeafAltStory1::
	lock
	faceplayer
	msgbox MP_Story1 MSGBOX_DEFAULT
	closemessage
	fadenewbgm MUS_HIDERI
	msgbox MP_Story1_5 MSGBOX_DEFAULT
	closemessage
	applymovement 4 MP_LeafLeave
	waitmovement 4
	playse SE_TK_WARPOUT
	removeobject 4
	setflag FLAG_HIDE_CHAMPIONS_ROOM_RIVAL
	setflag FLAG_RYU_LEAF_MTPYRE
	setflag FLAG_RYU_HIDE_LCC_DEPT_ROOF_NPC
	fadedefaultbgm
	release
	end
	
MP_HexerTalksToPlayer::
	lock
	goto_if_unset FLAG_RYU_LEAF_MTPYRE, ryu_end
	applymovement 5, MP_ToPlayer
	waitmovement 5
	faceplayer
	msgbox MP_Story2 MSGBOX_DEFAULT
	closemessage
	applymovement 5 MP_AwayFromPlayer
	waitmovement 5
	release
	end
	
MP_CameraMovement1:
	walk_diag_southeast
	walk_diag_southeast
	walk_diag_southeast
	walk_diag_southeast
	walk_down
	walk_down
	step_end
	
MP_CameraMovement2:
	walk_up
	walk_up
	walk_diag_northwest
	walk_diag_northwest
	walk_diag_northwest
	walk_diag_northwest
	step_end
	
MP_LeafLeave:
	walk_left
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end
	
MP_ToPlayer:
	walk_down
	step_end
	
MP_AwayFromPlayer:
	walk_up
	walk_in_place_fast_down
	step_end
	
MP_Story1:
	.string "{COLOR LIGHT_RED}{SHADOW RED}This place also...brings back\nthose unpleasant memories.\pI won't let that frighten me\nthough...I've made my decision,\land I won't turn back.\p... ... ... ...$"
	
	
MP_Story1_5:
	.string "{COLOR LIGHT_RED}{SHADOW RED}Ironic, isn't it {PLAYER}? This is\n"
	.string "the most you've heard me speak,\nand yet...\p... ... ... ...\pForget it, it doesn't matter.\pNothing matters anymore.$"
	
MP_Story2:
	.string "I couldn't help but overhear what\nthat girl said...\pThat look on her face...I've seen\nit all too often in a place like\lthis...\pIt's not a pleasant one.\nBut...she's a pokémon trainer,\pisn't she? Surely she wouldn't\ntake them with her...I'd rather\p"
	.string "leave them at a place where they'd\nbe treated well...to those who\ldeal with many different pokémon\lon a regular basis.\p... ... ... ...\pAnyways, clock's ticking.$"


