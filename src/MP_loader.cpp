/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

// Forward declaration of the actual function in BGQueueChecker.cpp
void AddSC_BGQueueChecker();

// This is the wrapper function AzerothCore's build system looks for
void AddBGQueueCheckerScripts()
{
    AddSC_BGQueueChecker();
}
