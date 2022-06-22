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
          // burası
					else if (MessengerManager::instance().isFriend(ch->GetName(), tch->GetName()))
					{
						// zaten ekli
					}
					else
					{
						// ¸Ş½ÅÀú°¡ Ä³¸¯ÅÍ´ÜÀ§°¡ µÇ¸é¼­ º¯°æ
						MessengerManager::instance().RequestToAdd(ch, tch);
						//MessengerManager::instance().AddToList(ch->GetName(), tch->GetName());
					}
				}
			}
