#include "../include/Renderer.h"

void Renderer::draw(sf::RenderWindow& window, World world, std::vector<Pipe*> pipes, Bird player, Text text, bool gameStart, bool gameLost, bool gamePause, bool showBoundingBoxes)
{
    window.draw(world.get_background());

    for (auto& p : pipes)
    {
        window.draw(p->get_Pipe().first);
        window.draw(p->get_Pipe().second);

        if (gameStart && showBoundingBoxes)
        {
            window.draw(p->get_BoundingBox().first);
            window.draw(p->get_BoundingBox().second);

            window.draw(player.get_boundingBox());
        }
    }

    window.draw(text.get_score());

    window.draw(world.get_ground().first);
    window.draw(world.get_ground().second);

    window.draw(player.get_bird());

    if (!gameStart)
        window.draw(text.get_start());
    if (gameStart && gamePause && !gameLost)
        window.draw(text.get_pause());
    if (gameLost && !gamePause)
    {
        window.draw(text.get_lost());
        window.draw(text.get_restartInfo());
        window.draw(text.get_highscore());
    }
}