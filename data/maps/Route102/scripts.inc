Route102_MapScripts:: @ 81EC0E0
	.byte 0

Route102_EventScript_LittleBoy:: @ 81EC0E1
	msgbox Route102_Text_ImNotVeryTall, MSGBOX_NPC
	end

Route102_EventScript_RouteSignOldale:: @ 81EC0EA
	msgbox Route102_Text_RouteSignOldale, MSGBOX_SIGN
	end

Route102_EventScript_RouteSignPetalburg:: @ 81EC0F3
	msgbox Route102_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route102_EventScript_Boy:: @ 81EC0FC
	msgbox Route102_Text_CatchWholeBunchOfPokemon, MSGBOX_NPC
	end

Route102_EventScript_Calvin:: @ 81EC105
	trainerbattle_single TRAINER_CALVIN_1, Route102_Text_CalvinIntro, Route102_Text_CalvinDefeated
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_Rick:: @ 81EC1B3
	trainerbattle_single TRAINER_RICK, Route102_Text_RickIntro, Route102_Text_RickDefeated
	msgbox Route102_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Tiana:: @ 81EC1CA
	trainerbattle_single TRAINER_TIANA, Route102_Text_TianaIntro, Route102_Text_TianaDefeated
	msgbox Route102_Text_TianaPostBattle
	closemessage
	checkfactionstanding FACTION_STUDENTS, 50
	compare VAR_RESULT, TRUE
	goto_if_eq ryu_end
	goto_if_set FLAG_RYU_HAS_FOLLOWER, ryu_end
	msgbox r102_FollowerTianaQuery, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq r102_FollowerTiana
	release
	end

r102_FollowerTiana::
	setflag FLAG_RYU_HIDE_101_TIANA
	removeobject 4
	createfollower OBJ_EVENT_GFX_LASS, r102_FollowerTianaScript, DIR_NORTH
	msgbox r102_TianaStartsFollowing
	closemessage
	call_if_unset FLAG_RYU_RECRUITED_TIANA, r102_AdjustSchoolkidsFaction
	setflag FLAG_TEMP_D
	closemessage
	release
	end

r102_AdjustSchoolkidsFaction::
	changefactionstanding FACTION_STUDENTS, 30, FALSE
	setflag FLAG_RYU_RECRUITED_TIANA
	return

Route102_EventScript_Allen:: @ 81EC1E1
	trainerbattle_single TRAINER_ALLEN, Route102_Text_AllenIntro, Route102_Text_AllenDefeated
	msgbox Route102_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

r102_FollowerTianaQuery:
	.string "Wait, Do you think I could\n"
	.string "follow you around so I can\p"
	.string "watch how you battle and\n"
	.string "learn from you?$"

r102_TianaStartsFollowing:
	.string "Okay! I'll keep a close eye\n"
	.string "on your battling style!$"

r102_FollowerTianaScript:
	goto_if_set FLAG_TEMP_D, r102_InitialTianaMsg
	random 9
	switch VAR_RESULT
	case 0, r102_TianaMsg0
	case 1, r102_TianaMsg1
	case 2, r102_TianaMsg2
	case 3, r102_TianaMsg3
	case 4, r102_TianaMsg4
	case 5, r102_TianaMsg5
	case 6, r102_TianaMsg6
	case 7, r102_TianaMsg7
	case 8, r102_TianaMsg8
	release
	end

r102_TianaMsg0::
	msgbox r102_tm0
	closemessage
	call r102_DismissTianaQuery
	release
	end

r102_TianaMsg1::
	msgbox r102_tm1
	closemessage
	call r102_DismissTianaQuery
	release
	end

r102_TianaMsg2::
	msgbox r102_tm2
	closemessage
	call r102_DismissTianaQuery
	release
	end
	
r102_TianaMsg3::
	msgbox r102_tm3
	closemessage
	call r102_DismissTianaQuery
	release
	end
	
r102_TianaMsg4::
	msgbox r102_tm4
	closemessage
	call r102_DismissTianaQuery
	release
	end
	
r102_TianaMsg5::
	msgbox r102_tm5
	closemessage
	call r102_DismissTianaQuery
	release
	end
	
r102_TianaMsg6::
	msgbox r102_tm6
	closemessage
	call r102_DismissTianaQuery
	release
	end
	
r102_TianaMsg7::
	msgbox r102_tm7
	closemessage
	call r102_DismissTianaQuery
	release
	end
	
r102_TianaMsg8::
	msgbox r102_tm8
	closemessage
	call r102_DismissTianaQuery
	release
	end

r102_DismissTianaQuery::
	msgbox r102_ShouldDismissTiana, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_ne ryu_end
	msgbox r102_TianaBye
	call RyuForceCancelFollowerForQuest
	goto ryu_end

r102_ShouldDismissTiana:
	.string "Should I head out?$"

r102_TianaBye:
	.string "Okay! Come find me again\nif you want my company!$"
	
r102_tm0::
	.string "I see. We didn't learn that\nin school.$"

r102_tm1::
	.string "Wow! I'm learning lots of things.$"
	
r102_tm2::
	.string "Roxanne's a good teacher, but\nshe doesn't give practical\llessons.$"
	
r102_tm3::
	.string "A lot of my friends are super\njealous that I get to follow\pa real trainer around.$"
	
r102_tm4::
	.string "Ugh, I hope we don't see any\nnerds, they gross me out!$"
	
r102_tm5::
	.string "Small Pokémon really are the\nbest! They're so cute and\lsnuggly!$"
	
r102_tm6::
	.string "Ooh! You have such cool Pokémon!$"
	
r102_tm7::
	.string "I hope I get to meet the Elite\nFour someday.$"
	
r102_tm8::
	.string "So how long have you been a\ntrainer?\p{COLOR LIGHT_BLUE}{SHADOW BLUE}...\p{COLOR DARK_GREY}{SHADOW LIGHT_GREY}Oh wow, not much longer\nthan me!\pYou're already so strong though!$"
	
r102_InitialTianaMsg::
	msgbox r102_FollowerTianaFirstMsg
	closemessage
	call r102_DismissTianaQuery
	release
	end

r102_FollowerTianaFirstMsg:
	.string "I'm ready to move on from here!$"

Route102_Text_ImNotVeryTall: @ 81EC2C0
	.string "I'm…not very tall, so I sink right\n"
	.string "into tall grass.\p"
	.string "The grass goes up my nose and…\n"
	.string "Fwafwafwafwafwa…\p"
	.string "Fwatchoo!$"

Route102_Text_CatchWholeBunchOfPokemon: @ 81EC32E
	.string "I'm going to catch a whole bunch of\n"
	.string "Pokémon!$"

Route102_Text_RouteSignOldale: @ 81EC35B
	.string "Route 102\n"
	.string "{RIGHT_ARROW} OLDALE TOWN$"

Route102_Text_RouteSignPetalburg: @ 81EC373
	.string "Route 102\n"
	.string "{LEFT_ARROW} PETALBURG CITY$"
