#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "Group.h"

class BGQPlayerScript : public PlayerScript
{
public:
    BGQPlayerScript() : PlayerScript("BGQPlayerScript") { }

    bool OnPlayerCanJoinInBattlegroundQueue(
        Player* player,
        ObjectGuid /*BattlemasterGuid*/,
        BattlegroundTypeId /*BGTypeID*/,
        uint8 joinAsGroup,
        GroupJoinBattlegroundResult& err) override
        {
            if (!sConfigMgr->GetOption<bool>("BGQueueChecker.Enable", false))
            {
                return true;
            }

            if (!player || !joinAsGroup)
            {
                return true;
            }

            Group* group = player->GetGroup();
            if (!group)
            {
                return true;
            }

            uint32 leaderFaction = player->GetFaction();

            for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
            {
                Player* member = itr->GetSource();
                if (!member)
                {
                    continue;
                }

                if (member->GetFaction() != leaderFaction)
                {
                    err = ERR_BATTLEGROUND_JOIN_FAILED;

                    ChatHandler(player->GetSession()).PSendSysMessage(
                        "Unable to join battleground queue. "
                        "All party members must be the same faction as the party leader."
                    );

                    return false;
                }
            }

            return true;
        }
};

void AddSC_BGQueueChecker()
{
    new BGQPlayerScript();
}
