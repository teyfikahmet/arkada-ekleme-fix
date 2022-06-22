// ekle biryerlere
bool MessengerManager::isFriend(MessengerManager::keyA account, MessengerManager::keyA companion)
{
	if (m_Relation[account].find(companion) != m_Relation[account].end())
		return true;

	return false;
}
