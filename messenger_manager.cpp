// ekle biryerlere
bool MessengerManager::isFriend(char char_name[CHARACTER_NAME_MAX_LEN + 1], char target_name[CHARACTER_NAME_MAX_LEN + 1])
{
	if (m_Relation[char_name].find(target_name) != m_Relation[char_name].end())
		return true;

	return false;
}
