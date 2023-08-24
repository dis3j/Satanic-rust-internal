#pragma once
#include "disrpc/Includes/discord_register.h"
#include "disrpc/Includes/discord_rpc.h"
#include <Windows.h>

class Discord {
public:

    void injected();
    void inject();
    void Initialize();
    void Update();
    void Shutdown();
};
