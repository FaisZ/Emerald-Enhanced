MtPyre_1F_MapScripts:: @ 8230F3E
	.byte 0

MtPyre_1F_EventScript_CleanseTagWoman:: @ 8230F3F
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag:: @ 8230F6E
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF:: @ 8230F78
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man:: @ 8230F81
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_Text_TakeThisForYourOwnGood: @ 8230F8A
	.string "All sorts of beings wander the slopes\n"
	.string "of Mt. Pyre…\p"
	.string "There is no telling what may happen.\n"
	.string "Take this. It's for your own good.$"

MtPyre_1F_Text_ExplainCleanseTag: @ 8231005
	.string "Have a Pokémon hold that\n"
	.string "Cleanse Tag.\p"
	.string "It will help ward off wild Pokémon.$"

MtPyre_1F_Text_ComeToPayRespects: @ 823104F
	.string "Did you come to pay your respect\n"
	.string "to the spirits of departed Pokémon?\p"
	.string "You must care for your Pokémon a lot.$"

MtPyre_1F_Text_RestingPlaceOfZigzagoon: @ 82310BA
	.string "This is the final resting place of my\n"
	.string "Zigzagoon. I cherished it…$"


@@--------------------------------------------------------------Faction Related

MP_PreventLeavingIfOnFactionQuest::
	goto_if_unset FLAG_RYU_HEXER_FACTION_QUEST_ACTIVE, ryu_end
	lock
	msgbox MP_CantLeave
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_StepUp
	applymovement OBJ_EVENT_ID_FOLLOWER, Common_Movement_StepUp
	waitmovement OBJ_EVENT_ID_FOLLOWER
	release
	end

MP_CantLeave:
	.string "You must escort the Wiccan\nto the 6th floor of Mt. Pyre.$"

MP_FactionQuestHexer::
	compare VAR_RYU_AQUA, 80
	goto_if_ge MP_FQ_NotAvailable
	checkfactionstanding FACTION_OUTCASTS, 50
	compare VAR_RESULT, TRUE
	goto_if_eq MP_FQ_NotAvailable
	lock
	faceplayer
	msgbox MP_FQ_HexerIntroQuery, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_set FLAG_RYU_HAS_FOLLOWER, MP_FQ_NotAvailable
	msgbox MP_FQ_HexerExplain
	playmoncry SPECIES_MIMIKYU, 1
	closemessage
	waitmoncry
	msgbox MP_FQ_HexerStartQuest
	closemessage
	removeobject 4
	setflag FLAG_RYU_HIDE_MTPYRE_HEXER
	createfollower OBJ_EVENT_GFX_HEX_MANIAC, RyuFollowerSelectNPCScript, DIR_SOUTH
	setflag FLAG_RYU_WAYSTONE_DISABLED
	setflag FLAG_RYU_HEXER_FACTION_QUEST_ACTIVE
	release
	end

MP_FQ_CancelledQuest::
	msgbox MP_FQ_PlayerCancelledQuest
	playmoncry SPECIES_MIMIKYU, 2
	waitmoncry
	releaseall
	end

MP_FQ_PlayerCancelledQuest:
	.string "Maybe another trainer will come\nalong, Mimi.$"

MP_FQ_NotAvailable::
	msgbox MP_FQ_Hexer_Cantdoquestmsg
	playmoncry SPECIES_MIMIKYU, 1
	closemessage
	release
	end

MP_FQ_HexerFollowerScript::
	msgbox MP_FQ_HexerFollowDialogue
	closemessage
	playmoncry SPECIES_MIMIKYU, 0
	waitmoncry
	msgbox MP_FQ_MimikyuLikesYou
	release
	end

MP_FQ_Hexer_Cantdoquestmsg:
	.string "I'm sorry, Mimi, I'll get you\nthere eventually.$"

MP_FQ_HexerIntroQuery:
	.string "I need to get my Mimi to her\n"
	.string "final resting place, her spirit\l"
	.string "is following me around.\p"
	.string "I fear she won't be able to rest\n"
	.string "until I get her up there.\p"
	.string "Mimi was my only Pokémon, and um...\n"
	.string "she... unfortunately passed away.\p"
	.string "Could you escort me to the\n"
	.string "sixth floor?$"

MP_FQ_HexerExplain::
	.string "I can see you're confused.\p"
	.string "Let me explain...\p"
	.string "My mimikyu has been with me\n"
	.string "for forty years.\p"
	.string "Her spirit is following me\n"
	.string "around, and she really wants\l"
	.string "to rest.$"

MP_FQ_HexerStartQuest::
	.string "Since I don't have any living\n"
	.string "Pokémon, I need a trainer to\l"
	.string "take me to the sixth floor, so\p"
	.string "I can bury my dear Mimi.$"

MP_FQ_HexerFollowDialogue::
	.string " {COLOR LIGHT_GREEN}{SHADOW GREEN}(You swear you feel something\n brush up against your leg.)$"

MP_FQ_MimikyuLikesYou::
	.string " {COLOR LIGHT_GREEN}{SHADOW GREEN}(A mimikyu's faint outline fades\n in from nothing, floating in\l the air.)$"
	

