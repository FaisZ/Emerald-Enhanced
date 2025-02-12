RustboroCity_DevonCorp_3F_MapScripts:: @ 821242D
	map_script ON_FRAME, RustboroCity_DevonCorp_3F_OnFrame
	.byte 0

RustboroCity_DevonCorp_3F_OnFrame: @ 8212464
	map_script_2 VAR_RYU_DEVON, 50, DC_CorporateInterrogation
	.2byte 0
@==================================================================================================RYU DEVON

DC_QuestCheck::
	lock
	goto_if_set FLAG_RYU_PLAYER_HELPING_AQUA, DC_ENEMY
	compare VAR_RYU_DEVON, 15
	goto_if_ge ryu_end
	clearflag FLAG_RYU_DEVON_CORPORATE_HIDE_MRSTONE2
	goto_if_set FLAG_RYU_DEVON_CORPORATE, DC_BeginCorporate
	goto_if_set FLAG_RYU_PLAYER_HELPING_DEVON, ryu_end
	checkitem ITEM_DEVON_GOODS, 1
	compare VAR_RESULT, 1
	goto_if_eq DC_BeginQuest
	msgbox DC_NoQuest MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER DC_Turnaround
	waitmovement 0
	warpsilent MAP_RUSTBORO_CITY_DEVON_CORP_2F, 255, 2, 1
	release
	end
	
DC_BeginCorporate::
	clearflag FLAG_RYU_DEVON_CORPORATE_HIDE_MRSTONE
	setflag FLAG_RYU_DEVON_CORPORATE_HIDE_MRSTONE2
	setflag FLAG_RYU_DEVON_CORPORATE_HIDE_MRSTONE4
	special DrawWholeMapView
	release
	end
	
DC_ENEMY::
	msgbox DC_NoQuest MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER DC_Turnaround
	waitmovement 0
	warpsilent MAP_RUSTBORO_CITY_DEVON_CORP_2F, 255, 2, 1
	release
	end
	
DC_QuestCheck2::
	lock
	goto_if_set FLAG_RYU_PLAYER_HELPING_AQUA, DC_ENEMY
	clearflag FLAG_RYU_DEVON_CORPORATE_HIDE_MRSTONE2
	compare VAR_RYU_DEVON, 15
	goto_if_ge ryu_end
	goto_if_set FLAG_RYU_DEVON_CORPORATE, DC_BeginCorporate
	goto_if_set FLAG_RYU_PLAYER_HELPING_DEVON, ryu_end
	checkitem ITEM_DEVON_GOODS, 1
	compare VAR_RESULT, 1
	goto_if_eq DC_BeginQuest
	msgbox DC_NoQuest MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetPlayerFacingDirection
	switch VAR_RESULT
	case DIR_WEST, DC_MovePlayer1Scr@right 1 up 1 warp
	case DIR_SOUTH, DC_MovePlayer2Scr@Up 2
	case DIR_EAST, DC_MovePlayer3Scr@left 1 up one
	applymovement OBJ_EVENT_ID_PLAYER, DC_MovePlayer2@Up
	waitmovement 0
	warpsilent MAP_RUSTBORO_CITY_DEVON_CORP_2F, 255, 2, 1
	release
	end
	
DC_MovePlayer1Scr::
	applymovement OBJ_EVENT_ID_PLAYER, DC_MovePlayer1
	waitmovement OBJ_EVENT_ID_PLAYER
	warpsilent MAP_RUSTBORO_CITY_DEVON_CORP_2F, 255, 2, 1
	release
	end
	
DC_MovePlayer2Scr::
	applymovement OBJ_EVENT_ID_PLAYER, DC_MovePlayer2
	waitmovement OBJ_EVENT_ID_PLAYER
	warpsilent MAP_RUSTBORO_CITY_DEVON_CORP_2F, 255, 2, 1
	release
	end
	
DC_MovePlayer3Scr::
	applymovement OBJ_EVENT_ID_PLAYER, DC_MovePlayer3
	waitmovement OBJ_EVENT_ID_PLAYER
	warpsilent MAP_RUSTBORO_CITY_DEVON_CORP_2F, 255, 2, 1
	release
	end

DC_NoQuest:
	.string "I'm sorry, but the Ceo is busy.\n"
	.string "Please come back later.$"

RustboroCity_DevonCorp_3F_EventScript_MrStone:: @ 821256C
	lock
	faceplayer
	switch VAR_RYU_DEVON
	case 5, RustboroCity_DevonCorp_3F_EventScript_MeetPresident
	case 18, DC_DeliveredLetterAndGoods
	case 19, DC_GoToMeteorFalls
	case 20, DC_Mission2
	goto_if_set FLAG_RYU_DEVON_SCIENTIST, DC_Scientist
	goto_if_set FLAG_RYU_DEVON_LINE_FINISHED, DC_Afterstory
	release
	end

DC_MovePlayer1:
	walk_right
	walk_up
	step_end
	
DC_MovePlayer2:
	walk_up
	walk_up
	step_end
	
DC_MovePlayer3:
	walk_left
	walk_up
	step_end

DC_Turnaround:
	face_up
	walk_up
	step_end
	
DC_Turnaround1:
	walk_left
	walk_up
	step_end
	
DC_Turnaround2:
	walk_right
	walk_up
	step_end

DC_Release::
	release
	end

DC_CorporateLine::
	lock
	setflag FLAG_RYU_WAYSTONE_DISABLED
	applymovement 5, DC_FranticPace
	msgbox DC_WhatToDo MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, DC_ApproachStone
	waitmovement OBJ_EVENT_ID_PLAYER
	closemessage
	applymovement 5, Common_Movement_FaceLeft
	waitmovement 5
	msgbox DC_PlayerReturned
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_SituationCritical
	closemessage
	applymovement 5, Common_Movement_FaceDown
	waitmovement 5
	msgbox DC_RightToKnow
	closemessage
	applymovement 5, Common_Movement_FaceLeft
	waitmovement 5
	msgbox DC_StoneExpShareDriveInfo
	closemessage
	applymovement 5, Common_Movement_FaceUp
	waitmovement 5
	msgbox DC_LeakInfo
	closemessage
	applymovement 5, Common_Movement_FaceLeft
	waitmovement 5
	msgbox DC_NewsMediaLeak
	closemessage
	applymovement 5, Common_Movement_FaceRight
	waitmovement 5
	msgbox DC_StufStolenTwice
	closemessage
	applymovement 5, Common_Movement_StepLeft
	waitmovement 5
	msgbox DC_Turncoat
	closemessage
	applymovement 5, Common_Movement_StepRight
	waitmovement 5
	msgbox DC_DireSituation
	closemessage
	playse SE_PIN
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 5
	msgbox DC_SplendidIdea
	closemessage
	applymovement 5, Common_Movement_FaceLeft
	waitmovement 5
	msgbox DC_Internment
	closemessage
	additem ITEM_TRI_PASS
	msgbox DC_OfficialEmployee
	closemessage
	setvar VAR_RYU_DEVON, 30
	clearflag FLAG_RYU_DEVON_CORPORATE_HIDE_MRSTONE3
	warpsilent MAP_RUSTBURO_CITY_DEVON_CORP2F_STORY_MAP, 255, 9, 2
	release
	end
	
	
DC_IntroDone::
	msgbox DC_INTROQUEST_MSG MSGBOX_DEFAULT
	release
	end
	
DC_INTROQUEST_MSG:
	.string "Steven was last spotted in Dewford.$"
	
DC_WhatToDo:
	.string "Oh, what to do...what am I going\nto do?$"
	
DC_PlayerReturned:
	.string "{PLAYER}, you've returned...\n... ... ...$"
	
DC_SituationCritical:
	.string "Honestly, now's not the best time.\nThe situation is critical.$"
	
DC_RightToKnow:
	.string "... ... ...\pYou've assisted us time and time\nagain, even becoming a devout\pmember of the corporation, so I\nbelieve you've earned the right to\lknow.$"
	
DC_StoneExpShareDriveInfo:
	.string "The corporation has recently been \n"
	.string "making several strides towards\p"
	.string "production of a one-of-a-kind item\n"
	.string "...technically speaking however,\p"
	.string "it's essentially a variant of the\n"
	.string "Exp Share we produced a few\l"
	.string "years back.\p"
	.string "Dubbed the Exp Drive, its\n"
	.string "function is to accumulate\p"
	.string "experience gained from pokémon\n"
	.string "battles, to which it can then be\p"
	.string "applied to a pokémon of your\n"
	.string "choosing.\p"
	.string "We're still working out the\n"
	.string "specifics...however, any trainer\p"
	.string "can see how much of a boon such a\n"
	.string "device would be for them.$"
	
DC_LeakInfo:
	.string "It was a closely guarded secret...\p"
	.string "only those who were actively\n"
	.string "involved on the project from the\p"
	.string "very initiation of its' conception\n"
	.string "knew about its' existence.\p"
	.string "Not even Steven knew!\p"
	.string "It was going to be the epitomé of\n"
	.string "Devon technology, an invention\p"
	.string "that would forever alter the scope\n"
	.string "of pokémon practice...and yet...$"
	
DC_NewsMediaLeak:
	.string "Like moths to a flame, news media\n"
	.string "came in droves! They demanded\p"
	.string "further information of a rumored\n"
	.string "device said to revolutionize\p"
	.string "pokémon battling and training.\n"
	.string "I was flabbergasted...how'd they\p"
	.string "know about it? How could Anyone\n"
	.string "Else know about it!?\p"
	.string "... ... ...$"
	
DC_StufStolenTwice:
	.string "Not once, but Twice now has our\n"
	.string "products been snatched right from\l"
	.string "under our noses...\p"
	.string "I didn't want to admit it, however\n"
	.string "there's no other feasible\l"
	.string "explanation...$"
	
DC_Turncoat:
	.string "There's a turncoat within the\n"
	.string "company. And I have reason to\p"
	.string "believe this individual was also\n"
	.string "the one involved with the Devon\p"
	.string "goods being stolen.$"
	
DC_DireSituation:
	.string "This is a dire situation indeed...\pHow can this be resolved...?\p... ... ...$"
	
DC_SplendidIdea:
	.string "Oh ho! I just had a splendid idea!\p{COLOR LIGHT_BLUE}{SHADOW BLUE}I don't like where this is going.$"
	
DC_Internment:
	.string "Come now, at least hear me out.\pUp 'til now, you've been hired to\nwork as an...intern of sorts. I\pthink it's high time you move on\nto become an in-house employee of\pthe corporation.\pHere, take this.$"
	
DC_OfficialEmployee:
	.string "Having risen to become an official\n"
	.string "employee of Devon, you'll be able\p"
	.string "to utilize our facility's PCs, as\n"
	.string "well as be able to closely\p"
	.string "associate with the other workers\n"
	.string "without suspicion.\p"
	.string "... ... ...\p"
	.string "It really hurts that I have to\n"
	.string "resort to this...I trust the\p"
	.string "people here. They're family in a\n"
	.string "way. Please assist me in this\p"
	.string "matter so it can be quickly put\n"
	.string "behind us.\p"
	.string "Follow me, I'll formally introduce\n"
	.string "you to the staff.$"
	
DC_ApproachStone:
	walk_right
	walk_down
	walk_down
	walk_in_place_right
	step_end
	
DC_FranticPace:
	walk_up
	walk_up
	walk_down
	walk_down
    walk_down	
	walk_down
	walk_up
	walk_up
	step_end

DC_CorporateInterrogation:: @Due to size limitations, all dialogue and movement are in data/scripts/RyuDevonLine.inc
	setvar VAR_RYU_DEVON, 55
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	playbgm 438, 1
	applymovement 6, Common_Movement_StepLeft
	waitmovement 6
	msgbox DC_ThanksForJoining
	closemessage
	applymovement 6, Common_Movement_FaceUp
	waitmovement 6
	msgbox DC_BeforeIGoFurther
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_StepLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_FirstIMustSay
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_AfterTalking
	closemessage
	applymovement 8, Common_Movement_FaceRight
	waitmovement 8
	msgbox DC_WhatsThis
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_YouHaventLetMeFinish
	closemessage
	applymovement 11, Common_Movement_FaceDown
	waitmovement 11
	msgbox DC_CanSomeonePlease
	closemessage
	applymovement 7, Common_Movement_FaceLeft
	waitmovement 7
	msgbox DC_ToMakeALongStory
	closemessage
	applymovement 7, Common_Movement_FaceUp
	waitmovement 7
	msgbox DC_HasAConclusion
	closemessage
	applymovement 6, Common_Movement_FaceLeft
	waitmovement 6
	msgbox DC_ItHasInFact
	closemessage
	applymovement 6, Common_Movement_FaceUp
	waitmovement 6
	msgbox DC_IfYouWill
	goto DC_CorporateInterrogation2
	release
	end
	
DC_CorporateInterrogation2::
	playbgm 443, 1
	msgbox DC_InOrderToMake
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_StepRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_NoDoubt
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, DC_ToHajio@Red Suit Worker to the right
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_NowMrHajio
	closemessage
	applymovement 9, Common_Movement_FaceRight
	waitmovement 9
	msgbox DC_ThoseTwo
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_AhYesTheNews
	closemessage
	playse SE_PIN
	applymovement 10, Common_Movement_ExclamationMark
	waitmovement 10
	msgbox DC_HoldOnASec
	closemessage
	applymovement 10, Common_Movement_FaceLeft
	waitmovement 10
	msgbox DC_IfMsIto
	closemessage
	playse SE_PIN
	applymovement 11, Common_Movement_ExclamationMark
	waitmovement 11
	applymovement 11, Common_Movement_FaceRight
	waitmovement 11
	msgbox DC_ExcuseMe
	closemessage
	applymovement 9, Common_Movement_FaceDown
	waitmovement 9
	msgbox DC_AndImDiabetic
	closemessage
	applymovement 10, Common_Movement_FaceDown
	waitmovement 10
	msgbox DC_ISuppose
	closemessage
	applymovement 11, Common_Movement_FaceDown
    waitmovement 11
	msgbox DC_AtLeastImResponsible
	closemessage
	applymovement 8, Common_Movement_FaceUp
	waitmovement 8
	msgbox DC_HoweverJustLikeToday
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	applymovement 6, Common_Movement_FaceLeft
	applymovement 7, Common_Movement_FaceLeft
	waitmovement 7
	msgbox DC_IfIRecall
	closemessage
	applymovement 8, Common_Movement_FaceRight
	waitmovement 8
	msgbox DC_AreYouSerious
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, DC_ReturnToPrez
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_SoIfImUnderstanding
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_ItsNoLonger
	closemessage
	applymovement 6, Common_Movement_FaceUp
	waitmovement 6
	msgbox DC_Negligence
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_AccordingToPrez
	closemessage
	goto DC_CorporateInterrogation3
	
DC_CorporateInterrogation3::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_YouAndYourPartner
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_ChainOfEvents
	closemessage
	applymovement 7, Common_Movement_FaceUp
	waitmovement 7
	msgbox DC_YouExpectMe
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	applymovement 6, Common_Movement_FaceLeft
	waitmovement 6
	msgbox DC_OthersAddress
	closemessage
	playbgm 373, 1
	applymovement 10, Common_Movement_StepDown
	waitmovement 10
	msgbox DC_ForgiveUs
	closemessage
	applymovement 9, Common_Movement_StepDown
	waitmovement 9
	msgbox DC_WhatHeSaid
	closemessage
	applymovement 8, Common_Movement_StepRight
	waitmovement 8
	msgbox DC_ItsNotJust
	closemessage
	applymovement 11, Common_Movement_StepDown
	waitmovement 11
	msgbox DC_AndINeed
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_WellThereYaGo
	closemessage
	playbgm 392, 1
	applymovement 6, Common_Movement_QuestionMark
	waitmovement 6
	msgbox DC_IsThatARing
	closemessage
	playse SE_PIN
	applymovement 11, Common_Movement_ExclamationMark
	waitmovement 11
	msgbox DC_WellThats
	closemessage
	applymovement 6, Common_Movement_FaceLeft
	waitmovement 6
	msgbox DC_Shyness
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, DC_Chuckle
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_OhBoy
	goto DC_CorporateInterrogation4
	
DC_CorporateInterrogation4::
	fadescreen 1
	setflag FLAG_RYU_DEVON_CORPORATE_HIDE_MRSTONE4
	clearflag FLAG_RYU_DEVON_CORPORATE_HIDE_MRSTONE2
	removeobject 6
	removeobject 7
	removeobject 8
	removeobject 9
	removeobject 10
	removeobject 11
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_StepRight
	waitmovement OBJ_EVENT_ID_PLAYER
	fadedefaultbgm
	delay 10
	fadescreen 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox DC_ToThinkThe
	closemessage
	additem ITEM_EXP_DRIVE
	setvar VAR_RYU_EXP_BATTERY, 1
	closemessage
	additem ITEM_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	closemessage
	msgbox DC_TheExpDrive
	closemessage
	setvar VAR_RYU_DEVON, 60 @player finished the Devon Corporate line.
	setflag FLAG_RYU_DEVON_LINE_FINISHED
	clearflag FLAG_RYU_WAYSTONE_DISABLED
	ach give ACH_CORPORATE_SHILL
	releaseall
	end
	
DC_Chuckle:
	walk_in_place_fast_down
	step_end

RustboroCity_DevonCorp_3F_Movement_212534: @ 8212534
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_left
	step_end

RustboroCity_DevonCorp_3F_Movement_212543: @ 8212543
	delay_16
	walk_in_place_fastest_down
	step_end

RustboroCity_DevonCorp_3F_Movement_212546: @ 8212546
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_21254F: @ 821254F
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Movement_212558: @ 8212558
    walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_212566: @ 8212566
	delay_16
	delay_16
	walk_down
	walk_down
	walk_in_place_fastest_right
	step_end

DC_Scientist:
	lock
	msgbox DC_YouAreScientist
	closemessage
	release
	end

DC_YouAreScientist:
	.string "I heard you became Cozmo's\nunderstudy. Congratulations!$"
	
DC_BeginQuest::
	goto_if_eq DC_HelpingDevon

DC_HelpingDevon::
	applymovement 2, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox DC_TalkToCEO MSGBOX_DEFAULT
	setflag FLAG_RYU_PLAYER_HELPING_DEVON
	changefactionstanding FACTION_STUDENTS, 10, FALSE
	changefactionstanding FACTION_PROFESSIONALS, 20, FALSE
	changefactionstanding FACTION_POKEFANS, 20, FALSE
	setvar VAR_RYU_QUESTLINE_ID, 0
	ach give ACH_ADVENTURE_TIME
	clearflag FLAG_HIDE_GRANITE_CAVE_STEVEN
	release
	end
	
DC_Mission2::
	msgbox DC_M2Msg MSGBOX_DEFAULT
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_1_PROF_COZMO
	release
	end
	
RC_ES_Recieved::
	msgbox RC_AlreadyDeliveredLetter MSGBOX_DEFAULT
	release
	end
	
RC_AlreadyDeliveredLetter:
	.string "Mr Stone: Thanks for delivering\nmy letter. My son already replied.\pHave you had a chance to visit\nSlateport yet?$"

DC_WorkForDevon:
	.string "Devon Employee: Oh, hi!\ndid you come here for a job?\p {COLOR LIGHT_GREEN} {SHADOW GREEN}(Are you sure you want to\n work for Devon Corp? You won't be\l able to pursue any other main line\l if you do!)$"
	
RC_DG_Delivered:
	.string "I heard you managed to get the\p"
	.string "trade secret to Stern, and protect\n"
    .string "him from the Aqua thugs.$"
	
RC_DevonThanks:
	.string "It's a proprietary Lidar system!\p"
	.string "top of the line! Almost priceless!\n"
	.string "Here, take this Master Ball, it's the only\p"
	.string "thing I can give that's equal in value.$"

DC_CEO_DeliveredLetter: @ 8212A29
	.string "Mr. Stone: You delivered my letter?\n"
	.string "Thank you kindly!\p"
	.string "This is my way of thanking you.\n"
	.string "It should help you, a trainer.$"

DC_TalkToCEO: @ 8212C37
	.string "I can't tell you how much I'm\n"
	.string "grateful for what you've done.\p"
	.string "Oh, that's right.\n"
	.string "Could you go talk to the Ceo?\p"
	.string "He's behind his desk to our right.$"
	
DC_M1CMSG:
	.string "Mr Stone: {PLAYER}! Thanks for\nhelping cozmo.$"
	
DC_M2Msg:
	.string "Prof. Cozmo wanted to thank you, \nso go visit him at his house\land chat with him.\pHe might have other tasks for you.\pPlease treat him with the\nsame respect you treat me.$"
	
DC_GoSeeCozmo:
	.string "Mr. Stone: {PLAYER}! Please go visit Cozmo,\nhe's waiting for you.$"
	
DC_OnQuest1::
	msgbox DC_M1Desc MSGBOX_DEFAULT
	clearflag FLAG_HIDE_METEOR_FALLS_TEAM_MAGMA
	clearflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_METEOR_FALLS_TEAM_AQUA
	release
	end
	
DC_GoToMeteorFalls::
	msgbox DC_MFQuestdescription MSGBOX_DEFAULT
	release
	end


RustboroCity_DevonCorp_3F_EventScript_MeetPresident:: @ 821246E
	lockall
	compare VAR_RYU_DEVON, 15
	goto_if_eq DC_IntroDone
	setvar VAR_RYU_DEVON, 15 @Player met president. Go deliver letter to steven in dewford cave.
	msgbox DC_CEOIntro, MSGBOX_DEFAULT
	additem ITEM_LETTER
	playfanfare MUS_FANFA4
	msgbox DC_CEO_GivesPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp, MSGBOX_DEFAULT
	closemessage
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_DEVON_CORP_3F_STATE, 1
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident: @ 8212534
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_left
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk: @ 8212543
	delay_16
	walk_in_place_fastest_down
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen: @ 8212546
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer: @ 821254F
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident: @ 8212558
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk: @ 8212566
	delay_16
	delay_16
	walk_down
	walk_down
	walk_in_place_fastest_right
	step_end

DC_DeliveredLetterAndGoods:: @ 8212595
	msgbox RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	msgbox DC_CEO_ExpShareDesc, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	setvar VAR_RYU_DEVON, 19 @Player completed Mr. Stone's tasks. Talk to him again for the next mission.
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_Employee:: @ 82125E1
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REPEAT_BALL, RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls
	msgbox RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls:: @ 82125F6
	msgbox RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_RareRocksDisplay:: @ 8212600
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksDisplay, MSGBOX_SIGN
	end

DC_Afterstory:
	goto_if_set FLAG_DEFEATED_RAYQUAZA, DC_AfterAfterStory
	goto_if_unset FLAG_SYS_GAME_CLEAR, DC_NotReadyYet
	msgbox DC_AfterstoryMsg
	giveitem ITEM_TRI_PASS
	setvar VAR_RYU_DEVON, 69
	release
	end
	
DC_NotReadyYet::
	msgbox DC_NRYMsg
	closemessage
	release
	end
	
	
DC_AfterAfterStory::
	msgbox DC_AASMsg
	additem ITEM_TRI_PASS @for those who didn't get it before.
	closemessage
	release
	end

DC_Msg_StoneLookingAtPaperwork: @ 8212B78
	.string " {COLOR LIGHT_GREEN}{SHADOW GREEN}(Mr. Stone appears to be looking over some\npaperwork.)$"

DC_MFQuestdescription:
	.string "Mr. Stone: One of our associates\nreached out.\pProf. Cozmo is having trouble with\ncriminals interfering with his work\l in Meteor Falls.\pDo you think you can go over there\nand provide some help for him there?$"
	
DC_M1Desc:
	.string "Mr. Stone: {PLAYER}! Hurry to Meteor Falls\nand help Prof. Cozmo!$"

DC_AASMsg:
	.string "Mr Stone: I heard you encountered\nRayquaza. I hope that went well for you.\pWell, Best of luck on your other plans!$"
	
DC_AfterstoryMsg:
	.string "You've more than proven yourself\na capable Trainer. I've had a guardian\passigned to Sky Pillar since we discovered\nit's significance.\pJust show him your Devon Card,\n and he'll allow you entry!$"
	
DC_NRYMsg:
	.string "You've been very valuable to us as\nan employee of Devon.\pWhen you amass more power, I\nwill give you access to a special\pplace that we have been researching.$"
	
DC_CEOIntro: @ 8212609
	.string "I'm MR. Stone, the President of\n"
	.string "the Devon Corporation.\p"
	.string "I'd just got word about you!\p"
	.string "You saved our staff not just once,\n"
	.string "but twice!\p"
	.string "I have a favor to ask of an amazing\n"
	.string "person like you.\p"
	.string "I understand that you're delivering\n"
	.string "a package to Slateport's Shipyard.\p"
	.string "Well, on the way, could you stop off in\n"
	.string "Dewford Town?\p"
	.string "I was hoping that you'd deliver a\n"
	.string "Letter to Steven in Dewford.$"

RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis: @ 821277C
	.string "MR. Stone: Now, you should know that\n"
	.string "I am a great President.\p"
	.string "So, I'd never be so cheap as to ask\n"
	.string "a favor for nothing in return.\p"
	.string "That's why I want you to have this!$"

RustboroCity_DevonCorp_3F_Text_ReceivedPokenav:
DC_CEO_GivesPokenav: @ 8212820
	.string "{PLAYER} received a Pokénav.$"

RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp: @ 8212837
	.string "Mr. Stone: That device…\p"
	.string "It's a Pokénav\p"
	.string "It's an indispensable tool for any\n"
	.string "trainer on an adventure.\p"
	.string "It has a map of the Hoenn region.\p"
	.string "You can check the locations of\n"
	.string "Dewford and Slateport easily!\p"
	.string "By the way, I've heard that sinister\n"
	.string "criminals--Magma and Aqua, I believe--\l"
	.string "have been making trouble far and wide.\p"
	.string "I think it would be best if you rested\n"
	.string "up before you go on your way.$"

RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare: @ 82129D2
	.string "MR. Stone: Well, then, {PLAYER},\n"
	.string "go with caution and care!$"

RustboroCity_DevonCorp_3F_Text_CountingOnYou: @ 8212A09
	.string "MR. Stone: I'm counting on you!$"

RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter: @ 8212A29
	.string "MR. Stone: You delivered my Letter?\n"
	.string "And the package for Stern as well?\p"
	.string "Excellent work!\p"
	.string "This is my way of thanking you.\n"
	.string "It should help you, a Trainer.$"

DC_CEO_ExpShareDesc: @ 8212A9E
	.string "That is our most cutting edge\n"
	.string "ball. It will capture any\l"
	.string "pokémon without fail.$"

RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends: @ 8212B78
	.string "MR. Stone: Since my youth, I've immersed\n"
	.string "myself in work.\p"
	.string "Consequently, I'm not familiar with\n"
	.string "trends and that sort of thing.\p"
	.string "But do young people all want to be\n"
	.string "Trainers in the Pokémon League?$"

RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere: @ 8212C37
	.string "This is the Devon Corporation's\n"
	.string "third floor.\p"
	.string "Our President's Office is on\n"
	.string "this floor.\p"
	.string "Anyway, I can't tell you how much I'm\n"
	.string "grateful for what you've done.\p"
	.string "Um… By the way, that parcel\n"
	.string "you got back for us…\p"
	.string "Could I get you to deliver that to\n"
	.string "the Shipyard in Slateport?\p"
	.string "It would be awful if those robbers\n"
	.string "tried to take it again.\p"
	.string "Uh… Hehehe, so, uh, could I count\n"
	.string "on you to do that for me?\p"
	.string "Oh, that's right.\n"
	.string "Could you wait here a second?$"

RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe: @ 8212DE8
	.string "Our President would like to have\n"
	.string "a word with you.\p"
	.string "Please come with me.$"

RustboroCity_DevonCorp_3F_Text_PleaseGoAhead: @ 8212E2F
	.string "Please, go ahead.$"

RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard: @ 8212E41
	.string "If you visit the Shipyard in Slateport,\n"
	.string "you should go see Capt. Stern.$"

RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular: @ 8212E88
	.string "Devon's new products, the Repeat Ball\n"
	.string "and Timer Ball, have become hugely\l"
	.string "popular among Trainers.$"

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay: @ 8212EE9
	.string "It's a collection of rare rocks and\n"
	.string "stones assembled by the President.$"

