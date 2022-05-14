#include "gamescreen.h"

void GameScreen::updateBall(){
    // Update ball position
    if(timeSinceLastMove.asSeconds() >= seconds(1.f / float(ballSpeed)).asSeconds()){
        Vector2f BallPosition = ball.getPosition();

        if(!directionQueue.empty()){
            // Ball can go in all directions, no restrictions
            ballDirection = directionQueue.front();
            directionQueue.pop_front();
        }

        switch(ballDirection){
            case Direction::UP:
                ball.setPosition(Vector2f(BallPosition.x, BallPosition.y - 10));
                break;

            case Direction::DOWN:
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

        // Walls collision detection

        for(int index = 0; index < 3; ++index){
            if(index == 0 || index == 3){
                // Collision with top/bottom -> redirect the ball
                if (walls[index].getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds())) {
                    switch (ballDirection) {
                        case Direction::UP:
                            // Ball should go DOWN
                            ball.setPosition(Vector2f(BallPosition.x, BallPosition.y + 10));
                            break;

                        case Direction::DOWN:
                            // Ball should go UP
                            ball.setPosition(Vector2f(BallPosition.x, BallPosition.y - 10));
                            break;

                        case Direction::LEFT:
                            // Ball should go RIGHT
                            ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y));
                            break;

                        case Direction::RIGHT:
                            // Ball should go LEFT
                            ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y));
                            break;

                        case Direction::UPRIGHT:
                            // Ball should go DOWNRIGHT
                            ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y + 10));
                            break;

                        case Direction::DOWNRIGHT:
                            // Ball should go UPRIGHT
                            ball.setPosition(Vector2f(BallPosition.x + 10, BallPosition.y - 10));
                            break;

                        case Direction::UPLEFT:
                            // Ball should go DOWNLEFT
                            ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y + 10));
                            break;

                        case Direction::DOWNLEFT:
                            // Ball should go UPLEFT
                            ball.setPosition(Vector2f(BallPosition.x - 10, BallPosition.y - 10));
                            break;
                    }
                    break;
                }
            }
            else{
                if(index == 1){
                    // Left wall collision, let the ball pass, update player1's score and reset the game

                }
                else{
                    // Right wall collision, let the ball pass, update player2's score and reset the game
                }
            }
        }

        ball.update();

        timeSinceLastMove = Time::Zero;
    }


}