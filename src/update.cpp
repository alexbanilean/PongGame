#include "gamescreen.h"

void GameScreen::updateBall(){
	// Update ball position
	if(timeSinceLastMove.asSeconds() >= seconds(1.f / float(ballSpeed)).asSeconds()){
		Vector2f BallPosition = ball.getPosition();

		const float offset = float(ballSpeed) / float(FPS);
		ballSpeed = min(maxSpeed, ballSpeed);

		// Blades collision detection

		bool blade_collision = false;
		const float acceleration_factor = 10;

		FloatRect result;

		if(blade1.getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds(), result)){
			blade_collision = true;

			ballSpeed += blade1.nr_collisions * acceleration_factor;
			++blade1.nr_collisions;

			Vector2f referenceIntersectionPoint(result.left + result.width / 2, result.top + result.height / 2);
			Vector2f referenceBladePoint(blade1.getPosition().x - blade1.getShape().getSize().x / 2,
										 blade1.getPosition().y - blade1.getShape().getSize().y / 2);

			if(referenceIntersectionPoint.y < (referenceBladePoint.y + blade1.getShape().getSize().y / 3)){
				// Upper third
				ballDirection = Direction::UPRIGHT;
			} else if((referenceBladePoint.y + blade1.getShape().getSize().y / 3) <= referenceIntersectionPoint.y &&
					  referenceIntersectionPoint.y < (referenceBladePoint.y + 2 * blade1.getShape().getSize().y / 3)){
				// Middle third

				if(ballDirection == Direction::DOWNLEFT)
					ballDirection = Direction::DOWNRIGHT;
				else if(ballDirection == Direction::LEFT)
					ballDirection = Direction::RIGHT;
				else
					ballDirection = Direction::UPRIGHT;

			} else if((referenceBladePoint.y + 2 * blade1.getShape().getSize().y / 3) <= referenceIntersectionPoint.y &&
					  referenceIntersectionPoint.y <= (referenceBladePoint.y + blade1.getShape().getSize().y)){
				// Lower third
				ballDirection = Direction::DOWNRIGHT;
			}

		} else if(blade2.getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds(), result)){
			blade_collision = true;

			ballSpeed += blade2.nr_collisions * acceleration_factor;
			++blade2.nr_collisions;

			Vector2f referenceIntersectionPoint(result.left + result.width / 2, result.top + result.height / 2);
			Vector2f referenceBladePoint(blade2.getPosition().x - blade2.getShape().getSize().x / 2,
										 blade2.getPosition().y - blade2.getShape().getSize().y / 2);

			if(referenceIntersectionPoint.y < (referenceBladePoint.y + blade2.getShape().getSize().y / 3)){
				// Upper third
				ballDirection = Direction::UPLEFT;
			} else if((referenceBladePoint.y + blade2.getShape().getSize().y / 3) <= referenceIntersectionPoint.y &&
					  referenceIntersectionPoint.y < (referenceBladePoint.y + 2 * blade2.getShape().getSize().y / 3)){
				// Middle third

				if(ballDirection == Direction::DOWNRIGHT)
					ballDirection = Direction::DOWNLEFT;
				else if(ballDirection == Direction::RIGHT)
					ballDirection = Direction::LEFT;
				else
					ballDirection = Direction::UPLEFT;

			} else if((referenceBladePoint.y + 2 * blade2.getShape().getSize().y / 3) <= referenceIntersectionPoint.y &&
					  referenceIntersectionPoint.y <= (referenceBladePoint.y + blade2.getShape().getSize().y)){
				// Lower third
				ballDirection = Direction::DOWNLEFT;
			}
		}

		if(!blade_collision){
			// Walls collision detection

			for(int index = 0; index < 4; ++index){
				if(index == 0 || index == 3){
					// Collision with top/bottom -> redirect the ball

					if(walls[index].getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds())){
						switch( ballDirection ){
							case Direction::UP:
								// Ball should go DOWN
								ballDirection = Direction::DOWN;
								break;

							case Direction::DOWN:
								// Ball should go UP
								ballDirection = Direction::UP;
								break;

							case Direction::LEFT:
								// Ball should go RIGHT
								ballDirection = Direction::RIGHT;
								break;

							case Direction::RIGHT:
								// Ball should go LEFT
								ballDirection = Direction::LEFT;
								break;

							case Direction::UPRIGHT:
								// Ball should go DOWNRIGHT
								ballDirection = Direction::DOWNRIGHT;
								break;

							case Direction::DOWNRIGHT:
								// Ball should go UPRIGHT
								ballDirection = Direction::UPRIGHT;
								break;

							case Direction::UPLEFT:
								// Ball should go DOWNLEFT
								ballDirection = Direction::DOWNLEFT;
								break;

							case Direction::DOWNLEFT:
								// Ball should go UPLEFT
								ballDirection = Direction::UPLEFT;
								break;
						}
						break;
					}
				} else{
					if(walls[index].getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds())){
						if(index == 1){
							// Left wall collision, let the ball pass, update player2's score and reset the game
							++score2;

							if(score2 >= player2.getHighScore()){
								player2.setHighScore(score2);

								Score aux(player2.getId(), player2.getName(), player2.getHighScore());
								table.updateTable(aux);
							}

							ballDirection = Direction::LEFT;
							ball.setPosition(Vector2f(BallPosition.x - 100, BallPosition.y));
							ball.update();

							draw();

							sleep(milliseconds(100));

							startTheGame();
							return;

						} else{
							// Right wall collision, let the ball pass, update player1's score and reset the game
							++score1;

							if(score1 >= player1.getHighScore()){
								player1.setHighScore(score1);

								Score aux(player1.getId(), player1.getName(), player1.getHighScore());
								table.updateTable(aux);
							}

							ballDirection = Direction::RIGHT;
							ball.setPosition(Vector2f(BallPosition.x + 100, BallPosition.y));
							ball.update();

							draw();

							sleep(milliseconds(100));

							startTheGame();
							return;
						}
					}
				}
			}
		}

		// Update ball position (possibly no collision)

		switch( ballDirection ){
			case Direction::UP:
				ball.setPosition(Vector2f(BallPosition.x, BallPosition.y - offset));
				break;

			case Direction::DOWN:;
				ball.setPosition(Vector2f(BallPosition.x, BallPosition.y + offset));
				break;

			case Direction::LEFT:
				ball.setPosition(Vector2f(BallPosition.x - offset, BallPosition.y));
				break;

			case Direction::RIGHT:
				ball.setPosition(Vector2f(BallPosition.x + offset, BallPosition.y));
				break;

			case Direction::UPRIGHT:
				ball.setPosition(Vector2f(BallPosition.x + offset, BallPosition.y - offset));
				break;

			case Direction::DOWNRIGHT:
				ball.setPosition(Vector2f(BallPosition.x + offset, BallPosition.y + offset));
				break;

			case Direction::UPLEFT:
				ball.setPosition(Vector2f(BallPosition.x - offset, BallPosition.y - offset));
				break;

			case Direction::DOWNLEFT:
				ball.setPosition(Vector2f(BallPosition.x - offset, BallPosition.y + offset));
				break;
		}

		ball.update();

		timeSinceLastMove = Time::Zero;
	}

}

void GameScreen::updateBlades(){
	// Update blades
	if(timeSinceBladesMove.asSeconds() >= seconds(1.f / float(bladeSpeed)).asSeconds()){
		Vector2f blade1Position = blade1.getPosition();
		Vector2f blade2Position = blade2.getPosition();

		const float update_val = float(bladeSpeed) / float(FPS);

		// Blade 1 update
		if(blade1Direction == Direction::UP){
			blade1.setPosition(Vector2f(blade1Position.x, blade1Position.y - update_val));
		} else if(blade1Direction == Direction::DOWN){
			blade1.setPosition(Vector2f(blade1Position.x, blade1Position.y + update_val));
		}

		// Blade 2 update
		if(blade2Direction == Direction::UP){
			blade2.setPosition(Vector2f(blade2Position.x, blade2Position.y - update_val));
		} else if(blade2Direction == Direction::DOWN){
			blade2.setPosition(Vector2f(blade2Position.x, blade2Position.y + update_val));
		}

		// Check collision with walls

		for(int index = 0; index < 4; ++index){
			if(index == 0 || index == 3){
				// Collision with top/bottom -> block the blade to go further
				// Collision with left/right not possible

				if(walls[index].getShape().getGlobalBounds().intersects(blade1.getShape().getGlobalBounds())){
					blade1.setPosition(blade1Position);
					if(index == 0){
						blade1Direction = Direction::DOWN;
						blade1.setPosition(Vector2f(blade1Position.x, blade1Position.y + update_val));
					} else{
						blade1Direction = Direction::UP;
						blade1.setPosition(Vector2f(blade1Position.x, blade1Position.y - update_val));
					}
				}

				if(walls[index].getShape().getGlobalBounds().intersects(blade2.getShape().getGlobalBounds())){
					blade2.setPosition(blade2Position);
					if(index == 0){
						blade2Direction = Direction::DOWN;
						blade2.setPosition(Vector2f(blade2Position.x, blade2Position.y + update_val));
					} else{
						blade2Direction = Direction::UP;
						blade2.setPosition(Vector2f(blade2Position.x, blade2Position.y - update_val));
					}
				}
			}
		}

		blade1.update();
		blade2.update();

		timeSinceBladesMove = Time::Zero;
	}
}