// Bu kısmı
case MESSENGER_SUBHEADER_CG_ADD_BY_VID:
{
	...
}
// değiştir
case MESSENGER_SUBHEADER_CG_ADD_BY_VID:
{
	if (uiBytes < sizeof(TPacketCGMessengerAddByVID))
		return -1;

	TPacketCGMessengerAddByVID * p2 = (TPacketCGMessengerAddByVID *) c_pData;
	LPCHARACTER ch_companion = CHARACTER_MANAGER::instance().Find(p2->vid);

	if (!ch_companion)
		return sizeof(TPacketCGMessengerAddByVID);

	if (ch->IsObserverMode())
		return sizeof(TPacketCGMessengerAddByVID);

	if (ch_companion->IsBlockMode(BLOCK_MESSENGER_INVITE))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("»ó´ë¹æÀÌ ¸Ş½ÅÁ® Ãß°¡ °ÅºÎ »óÅÂÀÔ´Ï´Ù."));
		return sizeof(TPacketCGMessengerAddByVID);
	}

	LPDESC d = ch_companion->GetDesc();

	if (!d)
		return sizeof(TPacketCGMessengerAddByVID);

	if (ch->GetGMLevel() == GM_PLAYER && ch_companion->GetGMLevel() != GM_PLAYER)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<¸Ş½ÅÁ®> ¿î¿µÀÚ´Â ¸Ş½ÅÁ®¿¡ Ãß°¡ÇÒ ¼ö ¾ø½À´Ï´Ù."));
		return sizeof(TPacketCGMessengerAddByVID);
	}

	if (ch->GetDesc() == d) // ÀÚ½ÅÀº Ãß°¡ÇÒ ¼ö ¾ø´Ù.
		return sizeof(TPacketCGMessengerAddByVID);
	if (!MessengerManager::instance().isFriend(ch->GetName(), ch_companion->GetName()))
		MessengerManager::instance().RequestToAdd(ch, ch_companion);
	//MessengerManager::instance().AddToList(ch->GetName(), ch_companion->GetName());
}

// Bu kısmı
case MESSENGER_SUBHEADER_CG_ADD_BY_NAME:
{
	...
}
//değiştir
case MESSENGER_SUBHEADER_CG_ADD_BY_NAME:
{
	if (uiBytes < CHARACTER_NAME_MAX_LEN)
		return -1;

	char name[CHARACTER_NAME_MAX_LEN + 1];
	strlcpy(name, c_pData, sizeof(name));

	if (ch->GetGMLevel() == GM_PLAYER && gm_get_level(name) != GM_PLAYER)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<¸Ş½ÅÁ®> ¿î¿µÀÚ´Â ¸Ş½ÅÁ®¿¡ Ãß°¡ÇÒ ¼ö ¾ø½À´Ï´Ù."));
		return CHARACTER_NAME_MAX_LEN;
	}

	LPCHARACTER tch = CHARACTER_MANAGER::instance().FindPC(name);

	if (!tch)
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s ´ÔÀº Á¢¼ÓµÇ ÀÖÁö ¾Ê½À´Ï´Ù."), name);
	else
	{
		if (tch == ch) // ÀÚ½ÅÀº Ãß°¡ÇÒ ¼ö ¾ø´Ù.
			return CHARACTER_NAME_MAX_LEN;

		if (tch->IsBlockMode(BLOCK_MESSENGER_INVITE) == true)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("»ó´ë¹æÀÌ ¸Ş½ÅÁ® Ãß°¡ °ÅºÎ »óÅÂÀÔ´Ï´Ù."));
		}
		else
		{
			// ¸Ş½ÅÀú°¡ Ä³¸¯ÅÍ´ÜÀ§°¡ µÇ¸é¼­ º¯°æ
			if (!MessengerManager::instance().isFriend(ch->GetName(), tch->GetName()))
				MessengerManager::instance().RequestToAdd(ch, tch);
			//MessengerManager::instance().AddToList(ch->GetName(), tch->GetName());
		}
	}
}
