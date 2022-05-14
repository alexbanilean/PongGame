#include "gamescreen.h"
#include "iostream"

const sf::Time GameScreen::TimePerFrame = seconds(1.f/60.f);

GameScreen::GameScreen(){
    resolution = Vector2f(1200, 800);
    window.create(VideoMode(resolution.x, resolution.y), "PongGame", Style::Default);
    window.setFramerateLimit(FPS);

    currentGameState = lastGameState = GameState::INITIAL;

    StartMenu();
}

void GameScreen::StartMenu(){

    currentGameState = lastGameState = GameState::INITIAL;

    window.clear(Color::Black);

    Font font;
    if(font.loadFromFile("../arial.ttf")){
        Text optionStartGame, optionShowHighScores, optionExit;

        optionStartGame.setFont(font);
        optionStartGame.setString("Press 1 to start the game");
        optionStartGame.setCharacterSize(20);
        optionStartGame.setFillColor(Color::Blue);
        optionStartGame.setStyle(Text::Regular);
        optionStartGame.setOrigin(optionStartGame.getLocalBounds().width / 2, optionStartGame.getLocalBounds().height / 2);
        optionStartGame.setPosition(600, 350);

        optionShowHighScores.setFont(font);
        optionShowHighScores.setString("Press 2 to show highscores table");
        optionShowHighScores.setCharacterSize(20);
        optionShowHighScores.setFillColor(Color::Blue);
        optionShowHighScores.setStyle(Text::Regular);
        optionShowHighScores.setOrigin(optionShowHighScores.getLocalBounds().width / 2, optionShowHighScores.getLocalBounds().height / 2);
        optionShowHighScores.setPosition(600, 400);

        optionExit.setFont(font);
        optionExit.setString("Press Esc to exit the game");
        optionExit.setCharacterSize(20);
        optionExit.setFillColor(Color::Blue);
        optionExit.setStyle(Text::Regular);
        optionExit.setOrigin(optionExit.getLocalBounds().width / 2, optionExit.getLocalBounds().height / 2);
        optionExit.setPosition(600, 450);

        window.draw(optionStartGame);
        window.draw(optionShowHighScores);
        window.draw(optionExit);
    }

    window.display();

}

void GameScreen::drawHighscoresTable(){

}

void GameScreen::startTheGame(){
    currentGameState = lastGameState = GameState::RUNNING;

    score1 = score2 = 0;

    ball.circle.setOrigin(ball.circle.getRadius() / 2, ball.circle.getRadius() / 2);
    ball.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    ball.update();

    cout << ball.getPosition().x << ' ' << ball.getPosition().y << '\n';

    blade1.blade.setOrigin(blade1.blade.getLocalBounds().width / 2, blade1.blade.getLocalBounds().height / 2);
    blade1.setPosition(Vector2f(50, window.getSize().y / 2));
    blade1.update();
    blade2.blade.setOrigin(blade2.blade.getLocalBounds().width / 2, blade2.blade.getLocalBounds().height / 2);
    blade2.setPosition(Vector2f(window.getSize().x - 50, window.getSize().y / 2));
    blade2.update();

    ballSpeed = 100;

    srand(time(NULL));
    int dir = rand() % 2;

    ballDirection = (dir == 0) ? Direction::LEFT : Direction::RIGHT;
    directionQueue.clear();
    timeSinceLastMove = Time::Zero;

    walls = {
             Wall(Vector2f(0, 0), Vector2f(resolution.x, 10)), // top wall
             Wall(Vector2f(0, 0), Vector2f(5, resolution.y)),
             Wall(Vector2f(resolution.x - 5, 0), Vector2f(5, resolution.y)),
             Wall(Vector2f(0, resolution.y - 10), Vector2f(resolution.x, 10)) // down wall
            };
}

void GameScreen::input(){
    Event event{};

    while(window.pollEvent(event)){
        // Window closed
        if(event.type == Event::Closed){
            window.close();
        }

        // Keyboard Input
        if(currentGameState != GameState::INITIAL){
            if(event.type == Event::KeyPressed){
                // Go back to menu
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                    StartMenu();

                // Pause
                if (Keyboard::isKeyPressed(Keyboard::Space))
                    togglePause();

//            // Direction
//
//            if(event.key.code == Keyboard::Up)
//                addDirection(Direction::UP);
//            else if(event.key.code == Keyboard::Down)
//                addDirection(Direction::DOWN);
//            else if(event.key.code == Keyboard::Left)
//                addDirection(Direction::LEFT);
//            else if(event.key.code == Keyboard::Right)
//                addDirection(Direction::RIGHT);

            }
        }
        else{
            if(event.type == Event::KeyPressed) {
                // Start
                if(Keyboard::isKeyPressed(Keyboard::Num1) || Keyboard::isKeyPressed(Keyboard::Numpad1))
                    startTheGame();

                // Show HighScores Table
                if(Keyboard::isKeyPressed(Keyboard::Num2) || Keyboard::isKeyPressed(Keyboard::Numpad2))
                    drawHighscoresTable();

                // Quit
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                    window.close();
            }
        }

    }
}

void GameScreen::addDirection(int newDirection){
    if(directionQueue.empty()){
        directionQueue.emplace_back(newDirection);
    }
    else{
        if(directionQueue.back() != newDirection){
            directionQueue.emplace_back(newDirection);
        }
    }
}

void GameScreen::togglePause(){
    if(currentGameState == GameState::RUNNING){
        lastGameState = currentGameState;
        currentGameState = GameState::PAUSED;
    }
    else if(currentGameState == GameState::PAUSED){
        currentGameState = lastGameState;
    }
}

void GameScreen::draw(){
    window.clear(Color::Black);

    for(auto w: walls)
        window.draw(w.getShape());

    window.draw(ball.getShape());
    window.draw(blade1.getShape());
    window.draw(blade2.getShape());

    if(currentGameState == PAUSED){
        Font font;
        if(font.loadFromFile("../arial.ttf")){
            Text paused;
            paused.setFont(font);
            paused.setString("Game paused");
            paused.setCharacterSize(30);
            paused.setFillColor(Color::Yellow);
            paused.setStyle(Text::Bold);
            paused.setOrigin(paused.getLocalBounds().width / 2, paused.getLocalBounds().height / 2);
            paused.setPosition(600, 400);

            window.draw(paused);
        }
    }

    window.display();
}