#include "Collision_System.h"
#include "game.h"   // For access to Game, Player, Aliens, Walls, Projectiles
#include <algorithm>
#include <cmath>


static float DistanceSquared(const Vector2& a, const Vector2& b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return dx * dx + dy * dy;
}

static Vector2 ClosestPointOnSegment(const Vector2& A, const Vector2& B, const Vector2& P)
{
    Vector2 AB{ B.x - A.x, B.y - A.y };
    Vector2 AP{ P.x - A.x, P.y - A.y };

    float ab2 = AB.x * AB.x + AB.y * AB.y;
    if (ab2 == 0.0f) return A;

    float t = (AP.x * AB.x + AP.y * AB.y) / ab2;

    if (t < 0.0f) t = 0.0f;
    else if (t > 1.0f) t = 1.0f;

    return Vector2{ A.x + AB.x * t, A.y + AB.y * t };
}

bool CollisionSystem::CheckCollisionCircleLine(Vector2 circlePos, float radius, Vector2 lineStart, Vector2 lineEnd)
{
Vector2 closest = ClosestPointOnSegment(lineStart, lineEnd, circlePos);
    float dist2 = DistanceSquared(circlePos, closest);
    return dist2 <= radius * radius;
}

void CollisionSystem::HandleProjectileCollisions(Game& game)
{
    std::erase_if(game.Projectiles, [&](Projectile& proj)
        {
            if (proj.type == EntityType::PLAYER_PROJECTILE)
            {
                // Aliens
                auto alienIt = std::find_if(game.Aliens.begin(), game.Aliens.end(),
                    [&](Alien& a) { return CheckCollisionCircleLine(a.GetPosition(), a.GetRadius(), proj.lineStart, proj.lineEnd); });

                if (alienIt != game.Aliens.end())
                {
                    game.Aliens.erase(alienIt);
                    game.score += 100;
                    return true; // remove projectile
                }

                // Walls
                auto wallIt = std::find_if(game.Walls.begin(), game.Walls.end(),
                    [&](Wall& w) { return CheckCollisionCircleLine(w.GetPosition(), w.GetRadius(), proj.lineStart, proj.lineEnd); });

                if (wallIt != game.Walls.end())
                {
                    wallIt->TakeDamage();
                    if (wallIt->IsDestroyed()) game.Walls.erase(wallIt);
                    return true; // remove projectile
                }

                return false;
            }
            else if (proj.type == EntityType::ENEMY_PROJECTILE)
            {
                // Player
                if (CheckCollisionCircleLine(game.player.GetPosition(), game.player.GetRadius(), proj.lineStart, proj.lineEnd))
                {
                    game.player.TakeDamage();
                    return true;
                }

                // Walls
                auto wallIt = std::find_if(game.Walls.begin(), game.Walls.end(),
                    [&](Wall& w) { return CheckCollisionCircleLine(w.GetPosition(), w.GetRadius(), proj.lineStart, proj.lineEnd); });

                if (wallIt != game.Walls.end())
                {
                    wallIt->TakeDamage();
                    if (wallIt->IsDestroyed()) game.Walls.erase(wallIt);
                    return true;
                }

                return false;
            }

            return false;
        });
}