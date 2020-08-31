
#include "SingleplayerSession.h"
#include "../../ecs/components/PlayerControlled.h"

void SingleplayerSession::join(std::string username)
{
    std::string declineReason;
    validateUsername(username, declineReason);

    if (!declineReason.empty())
    {
        onJoinRequestDeclined(declineReason);
        return;
    }
    assert(players.empty()); // splitscreen not yet supported

    localPlayer = std::make_shared<Player>();
    localPlayer->id = 69420;
    localPlayer->name = username;
    players.push_back(localPlayer);
}

void SingleplayerSession::update(double deltaTime)
{
    if (firstUpdate)
    {
        firstUpdate = false;
        level->initialize();
        onNewLevel(level);

        if (level->getNrOfRooms() >= 1)
        {
            Room *spawnRoom = level->getRoomByName(level->spawnRoom.c_str());
            if (!spawnRoom)
                spawnRoom = &level->getRoom(0);

            auto e = spawnRoom->getTemplate("Player").create();
            spawnRoom->entities.assign<PlayerControlled>(e, localPlayer->id);
            spawnRoom->entities.assign<LocalPlayer>(e);
        }
    }
    level->update(deltaTime);
}

SingleplayerSession::SingleplayerSession(Level *lvl) {
    assert(lvl != NULL);
    level = lvl;
}