RusturfTunnel_MapScripts:: @ 822CE27
	map_script ON_TRANSITION, RusturfTunnel_OnTransition
	map_script ON_FRAME, RusturfTunnel_OnFrame
	.byte 0

RusturfTunnel_OnFrame: @ 822CE32
	map_script_2 VAR_RUSTURF_TUNNEL_STATE, 4, RusturfTunnel_EventScript_ClearTunnelScene
	map_script_2 VAR_RUSTURF_TUNNEL_STATE, 5, RusturfTunnel_EventScript_ClearTunnelScene
	.2byte 0

RusturfTunnel_OnTransition: @ 822CE44
	compare VAR_RUSTURF_TUNNEL_STATE, 2
	call_if_eq RusturfTunnel_EventScript_SetAquaGruntAndPeekoPos
	end

RusturfTunnel_EventScript_SetAquaGruntAndPeekoPos:: @ 822CE50
	setobjectxyperm 7, 13, 4
	setobjectxyperm 6, 13, 5
	return


RusturfTunnel_EventScript_ClearTunnelScene:: @ 822CEAE
	lockall
	releaseall
	end

RusturfTunnel_EventScript_TunnelBlockagePos1:: @ 822D071
	setvar VAR_TEMP_1, 1
	end

RusturfTunnel_EventScript_TunnelBlockagePos2:: @ 822D077
	setvar VAR_TEMP_1, 2
	end

RusturfTunnel_EventScript_TunnelBlockagePos3:: @ 822D07D
	setvar VAR_TEMP_1, 3
	end

RusturfTunnel_EventScript_AquaGruntBackUp:: @ 822D083
	goto_if_set FLAG_RYU_PLAYER_NOOB, RT_SummonMagmaGruntBecausePlayerNoob
	lockall
	msgbox RusturfTunnel_Text_ComeAndGetSome, MSGBOX_DEFAULT
	closemessage
	applymovement 3, RusturfTunnel_Movement_GruntAndPeekoBackUp
	waitmovement 0
	copyobjectxytoperm 6
	setvar VAR_RUSTURF_TUNNEL_STATE, 3
	releaseall
	end

RT_SummonMagmaGruntBecausePlayerNoob::
	addobject 4
	applymovement 4, RT_MagmaToPlayer @6 left
	applymovement OBJ_EVENT_ID_PLAYER, RT_PlayerToMagma @6 right
	waitmovement OBJ_EVENT_ID_PLAYER
	goto RT_MagmaPortion

RT_MagmaToPlayer::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RT_PlayerToMagma::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RusturfTunnel_Movement_GruntAndPeekoBackUp: @ 822D0AB
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

RusturfTunnel_EventScript_Peeko:: @ 822D0AF
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, 0
	msgbox RusturfTunnel_Text_Peeko, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RusturfTunnel_EventScript_Grunt:: @ 822D0C2
	lock
	faceplayer
	playbgm MUS_AQA_0, 0
	msgbox RusturfTunnel_Text_GruntIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_RUSTURF_TUNNEL, RusturfTunnel_Text_GruntDefeat
	playbgm 366, 0
	msgbox RusturfTunnel_Text_GruntTakePackage, MSGBOX_DEFAULT
	additem ITEM_DEVON_GOODS
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, RusturfTunnel_Movement_PushPlayerAsideForGrunt
	applymovement 3, RusturfTunnel_Movement_GruntEscape
	waitmovement 0
	removeobject 3
	delay 50
	applymovement OBJ_EVENT_ID_PLAYER, RusturfTunnel_Movement_PlayerWatchBrineyExit
	clearflag FLAG_DEVON_GOODS_STOLEN
	setflag FLAG_RECOVERED_DEVON_GOODS
	setvar VAR_RUSTBORO_CITY_STATE, 4
	msgbox RT_ThiefLeftMsg MSGBOX_DEFAULT
	waitmessage
	closemessage
	playse SE_PIN
	waitse
	msgbox RT_ThiefNote MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE@@Magma intro starts here
	addobject 4
	applymovement 4, RT_MagmaGruntEnters
	waitmovement 4
	applymovement OBJ_EVENT_ID_PLAYER, RT_DelayedFace
	msgbox RT_WhatAChump
	closemessage
	playse SE_PIN
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 4
	goto RT_MagmaPortion

RT_MagmaPortion::
	setflag FLAG_RYU_PLAYER_NOOB
	setvar VAR_RUSTURF_TUNNEL_STATE, 2
	setflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	clearflag FLAG_HIDE_CHAMPIONS_ROOM_STEVEN
	trainerbattle_single TRAINER_GRUNT_RUSTURF_MAGMA, RT_SoItsAFight, RT_MG_Defeat, RT_PostBattle
	goto RT_PostBattle
	
RT_PostBattle::
	clearflag FLAG_RYU_PLAYER_NOOB
	setflag FLAG_HIDE_CHAMPIONS_ROOM_STEVEN
	setvar VAR_RUSTURF_TUNNEL_STATE, 3
	playbgm 366, 0
	msgbox RT_SoThisIsHow
	delay 60
	msgbox RT_Listen
	closemessage
	multichoice 0, 102, MULTI_MAGMA_CHOICE, 1
	switch VAR_RESULT
	case 0, RT_ADIntro
	case 1, RT_MagmaIntro
	case 2, RT_AquaIntro
	release
	end

RT_AquaIntro::
	setflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_CHAMPIONS_ROOM_STEVEN
	applymovement OBJ_EVENT_ID_PLAYER, RT_PlayerEscapeMagma
	msgbox RT_WaitWhereYou
	closemessage
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_RYU_AQUA, 5 @player started aqua
	setflag FLAG_RYU_PLAYER_HELPING_AQUA
	changefactionstanding FACTION_STUDENTS, 10, TRUE
	changefactionstanding FACTION_OUTCASTS, 20, FALSE
	changefactionstanding FACTION_ATHLETES, 20, FALSE
	setvar VAR_RYU_QUESTLINE_ID, 1
	ach give ACH_ADVENTURE_TIME
	warp MAP_ROUTE116, 255, 47, 9
	waitstate

RT_PlayerEscapeMagma:
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	walk_fastest_left
	step_end

RT_WaitWhereYou:
	.string "Wait! Where are you going?\pGet back here!$"

RT_ADIntro:
	setvar VAR_RYU_DEVON, 5 @Player chose devon quest. Player should go to Devon Corp.
	msgbox RT_IsEverything
	playse SE_PIN
	applymovement 4, Common_Movement_ExclamationMark
	waitmovement 4
	msgbox RT_Darn
	closemessage
	applymovement 4, RT_MagmaEscaped
	waitmovement 4
	fadescreen FADE_TO_BLACK
	removeobject 5
	addobject 5
	fadescreen FADE_FROM_BLACK
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	msgbox RT_OhItsYou
	closemessage
	playse SE_PIN
	applymovement 5, Common_Movement_QuestionMark
	waitmovement 5
	msgbox RT_WhyAmIHere
	fadescreen FADE_TO_BLACK
	removeobject 5
	fadescreen FADE_FROM_BLACK
	release
	end
	
RT_MagmaIntro::
	setflag FLAG_RYU_PLAYER_HELPING_MAGMA
	changefactionstanding FACTION_STUDENTS, 10, TRUE
	changefactionstanding FACTION_NOBLES, 20, FALSE
	changefactionstanding FACTION_NATURALISTS, 20, FALSE
	ach give ACH_ADVENTURE_TIME
	setvar VAR_RYU_MAGMA, 100 @@player chose magma
	setvar VAR_RYU_QUESTLINE_ID, 2
	msgbox RT_AndThats
	closemessage
	applymovement 4 Common_Movement_StepRight
	waitmovement 4
	delay 30
	applymovement 4, Common_Movement_FaceLeft
	waitmovement 4
	msgbox RT_YKnow
	closemessage
	applymovement 4, Common_Movement_StepLeft
	waitmovement 4
	msgbox RT_SoHow
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_StepRight
	waitmovement 0xff
	msgbox RT_OneCompleted
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement 0xff
	msgbox RT_Nevermind
	applymovement 4, RT_MagmaEscaped2
	waitmovement 4
	removeobject 4
	clearflag FLAG_RYU_HIDE_BRINEY_GUARD
	setvar VAR_RYU_MAGMA, 105 @player completed event in rusturf
	removeitem ITEM_DEVON_GOODS, 1
	clearflag FLAG_RECOVERED_DEVON_GOODS
	clearflag FLAG_RYU_WAYSTONE_DISABLED
	release
	end
	
RT_OhItsYou:
	.string "Oh, it's you {PLAYER}! I'm glad\n"
    .string "you're okay.$"

RT_Listen:
	.string "Listen, I know you beat me and all\n"
    .string "but I've got my orders, and there\p"
    .string "will be hell to pay if I don't\n"
    .string "follow through, so...$"

RT_SoThisIsHow:
	.string "Huh, so this is how things became.$"
	
RT_AndThats:
	.string "And that's mission accomplished. Good\n"
    .string "to know when you're about to fail and\p"
    .string "need to bail. Pleasure doing business\n"
    .string "with you!$"

RT_YKnow:
	.string "Y'know, you're an interesting one...\n"
    .string "and skilled. It's not my place to say\p"
    .string "but we could really use someone like\n"
    .string "you on our side.$"

RT_SoHow:
	.string "So how about it? Will you join Team\n"
    .string "Magma?$"

RT_OneCompleted:
	.string "One completed mission, and one new\n"
    .string "member...sounds like a good day's\p"
    .string "work to me! Maybe I'll get a bonus\n"
    .string "from this.$"

RT_Nevermind:
	.string "Nevermind. Let's head over to the\n"
    .string "rendezvous point.\p"
    .string "Y'know, the empty sea cottage, the\n"
    .string "one on Route 104. Don't keep us\p"
    .string "waiting!$"

	
RT_IsEverything:
	.string "Is everything alright in there!?$"

RT_Darn:
	.string "Darn, reinforcements...$"
	
RT_WhyAmIHere:
	.string "Why am I here? The miners heard a\n"
    .string "lot of commotion going on in here\p"
    .string "and called me to check it out.\n"
    .string "This place is known to be unstable\p"
    .string "and it's my duty as Gym Leader to\n"
    .string "make sure everyone's safe...although\p"
    .string "it seems like you're doing just fine\n"
    .string "so I'll be heading back. Drop by\l"
    .string "for a visit sometime!$"

	
RT_SoItsAFight:
	.string "So it's a fight you want. Let's\n"
    .string "not waste any time then!$"
	
RT_MG_Defeat:
	.string "Well isn't this something...$"

	
RT_WhatAChump:
	.string "Haha, what a chump!\p"
	.string "Such a pleasant sight to see Aqua\n"
    .string "running with their tails between\l"
    .string "their legs.\p"
    .string "{COLOR LIGHT_BLUE}{SHADOW BLUE}... ... ... ...\p"
    .string "{COLOR DARK_GREY}{SHADOW LIGHT_GREY}C'mon now, what's with the stern\n"
    .string "look?$"
	
RT_MagmaEscaped:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end
	
RT_MagmaEscaped2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end
	
RT_DelayedFace:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_right
	step_end
	
RT_MagmaGruntEnters:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RusturfTunnel_Movement_PushPlayerAsideForGrunt: @ 822D178
	face_down
	lock_facing_direction
	walk_up
	unlock_facing_direction
	walk_in_place_fastest_left
	step_end

RusturfTunnel_Movement_PlayerMoveAsideForBriney: @ 822D17E
	walk_down
	walk_in_place_fastest_up
	step_end

RusturfTunnel_Movement_GruntEscape: @ 822D181
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

RusturfTunnel_Movement_BrineyApproachPeeko1: @ 822D18B
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RusturfTunnel_Movement_BrineyExit: @ 822D193
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RusturfTunnel_Movement_PlayerWatchBrineyExit: @ 822D19F
	delay_16
	delay_8
	delay_4
	walk_in_place_fastest_left
	step_end

RusturfTunnel_Movement_BrineyApproachPeeko2: @ 822D1A4
	delay_16
	walk_right
	step_end

RusturfTunnel_Movement_PeekoExit: @ 822D1A7
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RusturfTunnel_EventScript_Mike:: @ 822D1B1
	trainerbattle_single TRAINER_MIKE_2, RusturfTunnel_Text_MikeIntro, RusturfTunnel_Text_MikeDefeat
	msgbox RusturfTunnel_Text_MikePostBattle, MSGBOX_AUTOCLOSE
	end

RT_ThiefLeftMsg:
	.string " {COLOR LIGHT_GREEN}{SHADOW GREEN}(You read the label on the package.)\n"
	.string "It would appear that this package\p"
	.string "belongs to Devon Corporation\n"
	.string "in Rustboro.There's probably a reward\p"
	.string "for returning it.$"
	
RT_ThiefNote:
	.string " {COLOR LIGHT_GREEN}{SHADOW GREEN}({PLAYER} sees a note on the ground\n presumably dropped by the soldier.)\p{COLOR DARK_GREY}{SHADOW LIGHT_GREY}It says:\p"
	.string "{COLOR DARK_GREY}{SHADOW BLUE}Your instructions are to obtain the\nnew LIDAR tech developed by Devon.\p"
	.string "{COLOR DARK_GREY}{SHADOW LIGHT_GREY}It seems like Aqua would be happy\n"
	.string "to recover this package. They'll\pprobably pay well too.\pYou will have to decide where to\ntake the package.$"


RusturfTunnel_Text_ComeAndGetSome: @ 822D1C8
	.string "What, are you coming?\n"
	.string "Come and get some, then!$"

RusturfTunnel_Text_Peeko: @ 822D1F7
	.string "Peeko: Pii pihyoh!$"

RusturfTunnel_Text_GruntIntro: @ 822D20A
	.string "And to think I made a getaway…\n"
	.string "In this tunnel to nowhere!\p"
	.string "Hey! You!\n"
	.string "So you want to battle me?$"

RusturfTunnel_Text_GruntDefeat: @ 822D2B0
	.string "Urrrggh! My career in crime comes to\n"
	.string "a dead end!$"

RusturfTunnel_Text_GruntTakePackage: @ 822D2E1
	.string "This is plain not right…\p"
	.string "The admin told me this would be a\n"
	.string "slick-and-easy job to pull.\p"
	.string "All I had to do was steal some package\n"
	.string "from Devon.\p"
	.string "Tch!\n"
	.string "You want it back that badly, take it!$"

RusturfTunnel_Text_PeekoGladToSeeYouSafe: @ 822D395
	.string "Peeko!\n"
	.string "Am I glad to see you're safe!$"

RusturfTunnel_Text_ThankYouLetsGoHomePeeko: @ 822D3BA
	.string "Peeko owes her life to you!\p"
	.string "They call me MR. Briney.\n"
	.string "And, you are?\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "Ah, so you are {PLAYER}!\n"
	.string "I sincerely thank you!\p"
	.string "Now, if there's anything that troubles\n"
	.string "you, don't hesitate to tell me!\p"
	.string "You can usually find me in my cottage\n"
	.string "by the sea near Petalburg Woods.\p"
	.string "Come, Peeko, we should make our way\n"
	.string "home.\p"
	.string "Peeko: Pihyoh!$"

RusturfTunnel_Text_WhyCantTheyKeepDigging: @ 822D510
	.string "… …\p"
	.string "Why can't they keep digging?\n"
	.string "Is the bedrock too hard?\p"
	.string "My beloved awaits me in Verdanturf\n"
	.string "Town just beyond here…\p"
	.string "If Rustboro and Verdanturf were\n"
	.string "joined by this tunnel, I could visit\l"
	.string "her every day…\p"
	.string "But this…\n"
	.string "What am I to do?$"

RusturfTunnel_Text_ToGetToVerdanturf: @ 822D5F3
	.string "To get from Rustboro to Verdanturf,\n"
	.string "you need to go to Dewford, then pass\l"
	.string "through Slateport and Mauville…$"

RusturfTunnel_Text_YouShatteredBoulderTakeHM: @ 822D65C
	.string "Wow! You shattered that boulder\n"
	.string "blocking the way.\p"
	.string "To show you how much I appreciate it,\n"
	.string "I'd like you to have this HM.$"

RusturfTunnel_Text_ExplainStrength: @ 822D6D2
	.string "That HM contains Strength.\p"
	.string "If a muscular Pokémon were to learn\n"
	.string "that, it would be able to move even\l"
	.string "large boulders.$"

RusturfTunnel_Text_WandaReunion: @ 822D745
	.string "Wanda!\n"
	.string "Now I can see you anytime!\p"
	.string "Wanda: That's…wonderful.\p"
	.string "Please, take some rest at my home.$"

RusturfTunnel_Text_BoyfriendOnOtherSideOfRock: @ 822D7A3
	.string "On the other side of this rock…\n"
	.string "My boyfriend is there.\p"
	.string "He… He's not just digging the tunnel\n"
	.string "to come see me.\p"
	.string "He works his hands raw and rough\n"
	.string "for the benefit of everyone.$"

RusturfTunnel_Text_MikeIntro: @ 822D84D
	.string "What do you call a wild man up in the\n"
	.string "mountains? A mountain man, right?\p"
	.string "So why don't they call a Pokémon in\n"
	.string "the mountains a mountain Pokémon?$"

RusturfTunnel_Text_MikeDefeat: @ 822D8DB
	.string "My Pokémon…\n"
	.string "Ran out of power…$"

RusturfTunnel_Text_MikePostBattle: @ 822D8F9
	.string "They halted development here to\n"
	.string "protect Pokémon, right?\l"
	.string "There's a feel-good story!$"

