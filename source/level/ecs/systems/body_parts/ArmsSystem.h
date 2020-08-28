
#ifndef GAME_ARMSSYSTEM_H
#define GAME_ARMSSYSTEM_H

#include "../EntitySystem.h"
#include "../../../room/Room.h"
#include "../../components/body_parts/Arm.h"
#include "../../components/physics/Physics.h"

class ArmsSystem : public EntitySystem
{
    using EntitySystem::EntitySystem;

  protected:
    void update(double deltaTime, Room *room) override
    {

        room->entities.view<Arm, AABB>().each([&](auto e, Arm &arm, AABB &handAABB) {

            AABB *grabTarget = room->entities.try_get<AABB>(arm.grab);
            AABB *bodyAABB = room->entities.try_get<AABB>(arm.body);
            Physics *bodyPhysics = room->entities.try_get<Physics>(arm.body);

            if (!bodyAABB || !bodyPhysics)
                return; // arm is not attached to body

            if (grabTarget)
            {
                // the hand is grabbig something -> set position of hand to the grabbed entity:
                handAABB.center = grabTarget->center;
            }
            else
            {
                handAABB.center += bodyPhysics->pixelsMovedByPolyPlatform;

                vec2 anchor = bodyAABB->center + arm.anchor;

                vec2 target = anchor;
                target.x += (arm.anchor.x > 0 ? 1 : -1) * arm.length * .2;
                target.y -= arm.length * .35;

                vec2 diff = target - (vec2(handAABB.center) + arm.moveAccumulator);
                float dist = length(diff);

                if (dist > 0)
                {
                    vec2 dir = diff / dist;
                    vec2 move = dir * min<float>(arm.moveSpeed * deltaTime, dist);
                    arm.moveAccumulator += move;

                    ivec2 movePixels = arm.moveAccumulator;
                    arm.moveAccumulator -= movePixels;
                    handAABB.center += movePixels;
                }
            }
            room->entities.get_or_assign<DistanceConstraint>(e, arm.length, arm.body, arm.anchor);

        });
    }

};


#endif
