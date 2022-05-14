#include "gamescreen.h"
#include "iostream"

void GameScreen::updateBall(){
    // Update ball position
    if(timeSinceLastMove.asSeconds() >= seconds(1.f / float(ballSpeed)).asSeconds()){
        Vector2f BallPosition = ball.getPosition();

        switch (ballDirection) {
            case Direction::UP:
                ball.setPosition(Vector2f(BallPosition.x, BallPosition.y - 10));
                break;

            case Direction::DOWN:;
                ball.setPosition(Vector2f(BallPosition.x, BallPosition.y + 10));
                break;

            case Direction::LEFT:
                ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y));
                break;

            case Direction::RIGHT:
                ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y));
                break;

            case Direction::UPRIGHT:
                ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y - 10));
                break;

            case Direction::DOWNRIGHT:
                ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y + 10));
                break;

            case Direction::UPLEFT:
                ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y - 10));
                break;

            case Direction::DOWNLEFT:
                ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y + 10));
                break;
        }

        // Blades collision detection

        bool blade_collision = false;

        if (blade1.getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds())) {
            blade_collision = true;
            if (ballDirection == Direction::DOWNLEFT) {
                ballDirection = Direction::DOWNRIGHT;
                ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y + 10));
            }
            else if (ballDirection == Direction::LEFT) {
                ballDirection = Direction::RIGHT;
                ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y));
            }
            else {
                ballDirection = Direction::UPRIGHT;
                ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y - 10));
            }
        }

        if (blade2.getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds())) {
            blade_collision = true;
            if (ballDirection == Direction::DOWNRIGHT) {
                ballDirection = Direction::DOWNLEFT;
                ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y + 10));
            }
            else if (ballDirection == Direction::RIGHT) {
                ballDirection = Direction::LEFT;
                ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y));
            }
            else {
                ballDirection = Direction::UPLEFT;
                ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y - 10));
            }
        }

        if(!blade_collision){
            // Walls collision detection

            for (int index = 0; index < 4; ++index) {
                if (index == 0 || index == 3) {
                    // Collision with top/bottom -> redirect the ball

                    if (walls[index].getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds())) {
                        switch (ballDirection) {
                            case Direction::UP:
                                // Ball should go DOWN
                                ballDirection = Direction::DOWN;
                                ball.setPosition(Vector2f(BallPosition.x, BallPosition.y + 10));
                                break;

                            case Direction::DOWN:
                                // Ball should go UP
                                ballDirection = Direction::UP;
                                ball.setPosition(Vector2f(BallPosition.x, BallPosition.y - 10));
                                break;

                            case Direction::LEFT:
                                // Ball should go RIGHT
                                ballDirection = Direction::RIGHT;
                                ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y));
                                break;

                            case Direction::RIGHT:
                                // Ball should go LEFT
                                ballDirection = Direction::LEFT;
                                ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y));
                                break;

                            case Direction::UPRIGHT:
                                // Ball should go DOWNRIGHT
                                ballDirection = Direction::DOWNRIGHT;
                                ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y + 10));
                                break;

                            case Direction::DOWNRIGHT:
                                // Ball should go UPRIGHT
                                ballDirection = Direction::UPRIGHT;
                                ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y - 10));
                                break;

                            case Direction::UPLEFT:
                                // Ball should go DOWNLEFT
                                ballDirection = Direction::DOWNLEFT;
                                ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y + 10));
                                break;

                            case Direction::DOWNLEFT:
                                // Ball should go UPLEFT
                                ballDirection = Direction::UPLEFT;
                                ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y - 10));
                                break;
                        }
                        break;
                    }
                }
                else {
                    if (walls[index].getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds())) {
                        if (index == 1) {
                            // Left wall collision, let the ball pass, update player2's score and reset the game
                            ++score2;
                            if(score2 > player2.getHighScore()) {
                                player2.setHighScore(score2);
                            }

                            ballDirection = Direction::LEFT;
                            ball.setPosition(Vector2f(BallPosition.x - 40, BallPosition.y));
                            ball.update();

                            draw();

                            sleep(milliseconds(100));

                            startTheGame();

                        }
                        else {
                            // Right wall collision, let the ball pass, update player1's score and reset the game
                            ++score1;
                            if(score1 > player1.getHighScore()) {
                                player1.setHighScore(score1);
                            }

                            ballDirection = Direction::RIGHT;
                            ball.setPosition(Vector2f(BallPosition.x + 40, BallPosition.y));
                            ball.update();

                            draw();

                            sleep(milliseconds(100));

                            startTheGame();
                        }
                    }
                }
            }
        }

        ball.update();

        timeSinceLastMove = Time::Zero;
    }

}

void GameScreen::updateBlades(){
    // Update blades
    if(timeSinceBladesMove.asSeconds() >= seconds(1.f/ float(bladeSpeed)).asSeconds()){
        Vector2f blade1Position = blade1.getPosition();
        Vector2f blade2Position = blade2.getPosition();

        // Blade 1 update
        if(blade1Direction == Direction::UP){
            blade1.setPosition(Vector2f(blade1Position.x, blade1Position.y - 10));
        }
        else if(blade1Direction == Direction::DOWN){
            blade1.setPosition(Vector2f(blade1Position.x, blade1Position.y + 10));
        }

        // Blade 2 update
        if(blade2Direction == Direction::UP){
            blade2.setPosition(Vector2f(blade2Position.x, blade2Position.y - 10));
        }
        else if(blade2Direction == Direction::DOWN){
            blade2.setPosition(Vector2f(blade2Position.x, blade2Position.y + 10));
        }

        // Check collision with walls

        for (int index = 0; index < 4; ++index) {
            if (index == 0 || index == 3) {
                // Collision with top/bottom -> block the blade to go further
                // Collision with left/right not possible

                if (walls[index].getShape().getGlobalBounds().intersects(blade1.getShape().getGlobalBounds())) {
                    blade1.setPosition(blade1Position);
                    if(index == 0){
                        blade1Direction = Direction::DOWN;
                        blade1.setPosition(Vector2f(blade1Position.x, blade1Position.y + 10));
                    }
                    else{
                        blade1Direction = Direction::UP;
                        blade1.setPosition(Vector2f(blade1Position.x, blade1Position.y - 10));
                    }
                }

                if (walls[index].getShape().getGlobalBounds().intersects(blade2.getShape().getGlobalBounds())) {
                    blade2.setPosition(blade2Position);
                    if(index == 0){
                        blade2Direction = Direction::DOWN;
                        blade2.setPosition(Vector2f(blade2Position.x, blade2Position.y + 10));
                    }
                    else {
                        blade2Direction = Direction::UP;
                        blade2.setPosition(Vector2f(blade2Position.x, blade2Position.y - 10));
                    }
                }
            }
        }

        blade1.update();
        blade2.update();

        timeSinceBladesMove = Time::Zero;
    }
}