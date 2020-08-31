
#ifndef GAME_PLATFORMERMOVEMENT_H
#define GAME_PLATFORMERMOVEMENT_H

#include "../../macro_magic/component.h"

COMPONENT(
    PlatformerMovementInput,
    HASH(jump, fall, left, right),

    FIELD_DEF_VAL(bool, jump, false),
    FIELD_DEF_VAL(bool, fall, false),
    FIELD_DEF_VAL(bool, left, false),
    FIELD_DEF_VAL(bool, right, false),
    FIELD_DEF_VAL(bool, attack, false)
)
END_COMPONENT(PlatformerMovementInput)

COMPONENT(
    PlatformerMovement,
    HASH(jumpVelocity, walkVelocity, coyoteTime),

    FIELD_DEF_VAL(float, walkVelocity, 90),
    FIELD_DEF_VAL(float, jumpVelocity, 380),
    FIELD_DEF_VAL(float, maxJumpVelocity, 500),
    FIELD_DEF_VAL(float, coyoteTime, .25),
    FIELD_DEF_VAL(float, jumpAntiGravity, .7),
    FIELD_DEF_VAL(float, airControl, 6),
    FIELD_DEF_VAL(float, swimVelocity, 960),
    FIELD_DEF_VAL(bool, spawnDustTrails, true)
)
    // used by system:
    float fallPressedTimer = 0;

    bool jumpPressedSinceBegin = false, currentlyJumping = false;

END_COMPONENT(PlatformerMovement)

COMPONENT(
    Flip,
    HASH(horizontal, vertical),

    FIELD_DEF_VAL(bool, horizontal, false),
    FIELD_DEF_VAL(bool, vertical, false)
)
END_COMPONENT(Flip)

#endif