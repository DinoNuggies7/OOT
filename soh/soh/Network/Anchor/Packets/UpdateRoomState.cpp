#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include "soh/Network/Anchor/JsonConversions.hpp"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>
#include "soh/OTRGlobals.h"

extern "C" {
#include "variables.h"
extern PlayState* gPlayState;
}

/**
 * UPDATE_ROOM_STATE
 */

nlohmann::json Anchor::PrepRoomState() {
    nlohmann::json payload;
    payload["ownerClientId"] = ownClientId;
    payload["pvpMode"] = CVarGetInteger(CVAR_REMOTE_ANCHOR("RoomSettings.pvpMode"), 0);

    return payload;
}

void Anchor::SendPacket_UpdateRoomState() {
    nlohmann::json payload;
    payload["type"] = UPDATE_ROOM_STATE;
    payload["state"] = PrepRoomState();

    SendJsonToRemote(payload);
}

void Anchor::HandlePacket_UpdateRoomState(nlohmann::json payload) {
    if (!payload.contains("state")) {
        return;
    }

    roomState.ownerClientId = payload["state"]["ownerClientId"].get<uint32_t>();
    roomState.pvpMode = payload["state"]["pvpMode"].get<u8>();
}

#endif // ENABLE_REMOTE_CONTROL
