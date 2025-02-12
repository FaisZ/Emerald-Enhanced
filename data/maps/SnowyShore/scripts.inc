SnowyShore_MapScripts::
	map_script ON_TRANSITION, SnowyShore_OnTransition
	.byte 0

SnowyShore_OnTransition:
	setflag FLAG_LANDMARK_SNOWY_SHORE
	call RyuCheckForLNSUAch
	end

SnowyShore_EventScript_TownSign::
	msgbox SnowyShore_Text_TownSign, MSGBOX_SIGN
	end

SS_TemporaryPortal::
	msgbox SS_TemporaryMagic
	closemessage
	fadescreen FADE_TO_BLACK
	drawfullscreenimage SCENEBGSUNSET
	msgbox SS_Warping
	closemessage
	delay 20
	clearfullscreenimage
	warpteleport MAP_LITTLEROOT_TOWN, 255, 8, 8
	waitstate

SS_TemporaryMagic:
	.string "You see a mysterious statue.\nThis must be the one\lthey were talking about...$"

SS_Warping:
	.string "{PLAYER} Touched the stone...$"

SnowyShore_Text_TownSign:
	.string "Snowy Shore\n"
	.string "“Come ashore this winter wonderland”$"

SnowyShore_EventScript_CraggyCoastSign::
	msgbox SnowyShore_Text_CraggyCoastSign, MSGBOX_SIGN
	end

SnowyShore_Text_CraggyCoastSign:
	.string "{LEFT_ARROW} Craggy Coast\n"
	.string "Snowy Shore {RIGHT_ARROW} $"

SnowyShore_EventScript_MrFrigusSign::
	msgbox SnowyShore_Text_MrFrigusSign, MSGBOX_SIGN
	end

SnowyShore_Text_MrFrigusSign:
	.string "Mr Frigus's house\n"
	.string "“Learn about the island's past”$"

SnowyShore_BigPearl::
	lockall
	goto_if_set FLAG_HIDDEN_SNOWY_SHORE_BIG_PEARL, FrostyForestEnd
	giveitem ITEM_BIG_PEARL
	setflag FLAG_HIDDEN_SNOWY_SHORE_BIG_PEARL
	release
	end

SnowyShore_HeartScale::
	lockall
	goto_if_set FLAG_HIDDEN_SNOWY_SHORE_HEART_SCALE, FrostyForestEnd
	giveitem ITEM_HEART_SCALE
	setflag FLAG_HIDDEN_SNOWY_SHORE_HEART_SCALE
	release
	end

SnowyShore_EventScript_Girl::
	lock
	faceplayer
	msgbox SnowyShore_Text_MyGarden, MSGBOX_DEFAULT
	release
	end

SnowyShore_Text_MyGarden:
	.string "Isn't my garden pretty? I take\n"
	.string "good care of it!$"

SnowyShore_EventScript_LittleGirl::
	lock
	faceplayer
	msgbox SnowyShore_Text_SlidingOnIce, MSGBOX_DEFAULT
	release
	end

SnowyShore_Text_SlidingOnIce:
	.string "I love sliding on ice!$"

SnowyShore_EventScript_OldWoman::
	lock
	faceplayer
	msgbox SnowyShore_Text_MtFreeze, MSGBOX_DEFAULT
	release
	end

SnowyShore_Text_MtFreeze:
	.string "Further north along this path is\n"
	.string "Mt. Freeze.\p"
	.string "The mountain is actually a volcano,\n"
	.string "it's been dormant for centuries.\p"
	.string "According to old folklore, a\n"
	.string "legendary bird lives on top, and\l"
	.string "it's the cause of the cold climate.$"

SnowyShore_EventScript_Woman::
	lock
	faceplayer
	msgbox SnowyShore_Text_Compost, MSGBOX_DEFAULT
	release
	end

SnowyShore_Text_Compost:
	.string "Despite the cold climate, we are\n"
	.string "able to grow flowers with compost\l"
	.string "made from Aspear Berries.$"

SnowyShore_EventScript_Man::
	lock
	faceplayer
	msgbox SnowyShore_Text_ThickFat, MSGBOX_DEFAULT
	release
	end

SnowyShore_Text_ThickFat:
	.string "My Azumarill doesn't care about the\n"
	.string "cold, it has Thick Fat!$"

SnowyShore_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, 0
	msgbox SnowyShore_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SnowyShore_Text_Azumarill:
	.string "Azumarill: Mari mareeeeeeeeeeeeeee\n"
	.string "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\p"
	.string "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n"
	.string "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\p"
	.string "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n"
	.string "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\p"
	.string "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n"
	.string "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\p"
	.string "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n"
	.string "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee!$"

SnowyShore_EventScript_Harold::
	trainerbattle_single TRAINER_HAROLD, SnowyShore_Text_HaroldIntro, SnowyShore_Text_HaroldDefeated
	msgbox SnowyShore_Text_HaroldPostBattle, MSGBOX_AUTOCLOSE
	end

SnowyShore_EventScript_Tim::
	trainerbattle_single TRAINER_TIM, SnowyShore_Text_TimIntro, SnowyShore_Text_TimDefeated
	msgbox SnowyShore_Text_TimPostBattle, MSGBOX_AUTOCLOSE
	end

SnowyShore_EventScript_Jim::
	trainerbattle_single TRAINER_JIM, SnowyShore_Text_JimIntro, SnowyShore_Text_JimDefeated
	msgbox SnowyShore_Text_JimPostBattle, MSGBOX_AUTOCLOSE
	end

SnowyShore_EventScript_Joyce::
	trainerbattle_single TRAINER_JOYCE, SnowyShore_Text_JoyceIntro, SnowyShore_Text_JoyceDefeated
	msgbox SnowyShore_Text_JoycePostBattle, MSGBOX_AUTOCLOSE
	end

SnowyShore_EventScript_Delton::
	trainerbattle_single TRAINER_DELTON, SnowyShore_Text_DeltonIntro, SnowyShore_Text_DeltonDefeated
	msgbox SnowyShore_Text_DeltonPostBattle, MSGBOX_AUTOCLOSE
	end

SnowyShore_EventScript_Marcus::
	trainerbattle_single TRAINER_MARCUS, SnowyShore_Text_MarcusIntro, SnowyShore_Text_MarcusDefeated
	msgbox SnowyShore_Text_MarcusPostBattle, MSGBOX_AUTOCLOSE
	end

SnowyShore_EventScript_Nick::
	trainerbattle_single TRAINER_NICK, SnowyShore_Text_NickIntro, SnowyShore_Text_NickDefeated
	msgbox SnowyShore_Text_NickPostBattle, MSGBOX_AUTOCLOSE
	end
