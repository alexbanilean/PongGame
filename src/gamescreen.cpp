#include "gamescreen.h"
#include "iostream"

GameScreen::GameScreen(){
    resolution = Vector2f(1200, 800);
    window.create(VideoMode(resolution.x, resolution.y), "PongGame", Style::Default);
    window.setFramerateLimit(FPS);

    currentGameState = lastGameState = GameState::INITIAL;

    StartMenu();
}

void GameScreen::StartMenu(){

    currentGameState = GameState::INITIAL;

    score1 = score2 = 0;
    displayHighscoresTable = false;

    window.clear(Color::Black);

    Font font;
    if(font.loadFromFile("../arial.ttf")){
        Text optionStartGame, optionInstructions, optionShowHighScores, optionExit;

        optionStartGame.setFont(font);
        optionStartGame.setString("Press 1 to start the game");
        optionStartGame.setCharacterSize(20);
        optionStartGame.setFillColor(Color::Blue);
        optionStartGame.setStyle(Text::Regular);
        optionStartGame.setOrigin(optionStartGame.getLocalBounds().width / 2, optionStartGame.getLocalBounds().height / 2);
        optionStartGame.setPosition(600, 325);

        optionInstructions.setFont(font);
        optionInstructions.setString("Press 2 to show instructions");
        optionInstructions.setCharacterSize(20);
        optionInstructions.setFillColor(Color::Blue);
        optionInstructions.setStyle(Text::Regular);
        optionInstructions.setOrigin(optionInstructions.getLocalBounds().width / 2, optionInstructions.getLocalBounds().height / 2);
        optionInstructions.setPosition(600, 375);

        optionShowHighScores.setFont(font);
        optionShowHighScores.setString("Press 3 to show highscores table");
        optionShowHighScores.setCharacterSize(20);
        optionShowHighScores.setFillColor(Color::Blue);
        optionShowHighScores.setStyle(Text::Regular);
        optionShowHighScores.setOrigin(optionShowHighScores.getLocalBounds().width / 2, optionShowHighScores.getLocalBounds().height / 2);
        optionShowHighScores.setPosition(600, 425);

        optionExit.setFont(font);
        optionExit.setString("Press Esc to exit the game");
        optionExit.setCharacterSize(20);
        optionExit.setFillColor(Color::Blue);
        optionExit.setStyle(Text::Regular);
        optionExit.setOrigin(optionExit.getLocalBounds().width / 2, optionExit.getLocalBounds().height / 2);
        optionExit.setPosition(600, 475);

        window.draw(optionStartGame);
        window.draw(optionInstructions);
        window.draw(optionShowHighScores);
        window.draw(optionExit);
    }

    window.display();
}

void GameScreen::read() {

    Font font;
    if(font.loadFromFile("../arial.ttf")) {

        string name1 = "", name2 = "";
        bool toName2 = false, completed = false;

        Text player1Display, player2Display, name1Display, name2Display;

        player1Display.setFont(font);
        player1Display.setString("Player 1");
        player1Display.setCharacterSize(30);
        player1Display.setFillColor(Color::Blue);
        player1Display.setStyle(Text::Regular);
        player1Display.setOrigin(player1Display.getLocalBounds().width / 2, player1Display.getLocalBounds().height / 2);
        player1Display.setPosition(300, 300);

        player2Display.setFont(font);
        player2Display.setString("Player 2");
        player2Display.setCharacterSize(30);
        player2Display.setFillColor(Color::Blue);
        player2Display.setStyle(Text::Regular);
        player2Display.setOrigin(player2Display.getLocalBounds().width / 2, player2Display.getLocalBounds().height / 2);
        player2Display.setPosition(900, 300);

        line.setSize(Vector2f(2, resolution.y));
        line.setFillColor(Color::White);
        line.setPosition(Vector2f(599, 0));

        while (window.isOpen() && !completed) {
            // Update names

            name1Display.setFont(font);
            name1Display.setString("Name: " + name1);
            name1Display.setCharacterSize(30);
            name1Display.setFillColor(Color::Blue);
            name1Display.setStyle(Text::Regular);
            name1Display.setOrigin(name1Display.getLocalBounds().width / 2, name1Display.getLocalBounds().height / 2);
            name1Display.setPosition(300, 400);

            name2Display.setFont(font);
            name2Display.setString("Name: " + name2);
            name2Display.setCharacterSize(30);
            name2Display.setFillColor(Color::Blue);
            name2Display.setStyle(Text::Regular);
            name2Display.setOrigin(name2Display.getLocalBounds().width / 2, name2Display.getLocalBounds().height / 2);
            name2Display.setPosition(900, 400);

            // Display

            window.clear(Color::Black);
            window.draw(player1Display);
            window.draw(player2Display);

            window.draw(line);

            window.draw(name1Display);
            window.draw(name2Display);

            window.display();

            Event event{};

            while (window.pollEvent(event)) {

                if (event.type == Event::Closed)
                     window.close();

                if (event.type == Event::TextEntered) {
                    if (isprint(event.text.unicode)) {
                        if (!toName2)
                            name1 += event.text.unicode;
                        else
                            name2 += event.text.unicode;
                    }
                }

                if (event.type == Event::KeyPressed) {
                    // Back to menu
                    if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                        currentGameState = GameState::INITIAL;
                        return;
                    }
                    else if (event.key.code == Keyboard::BackSpace) {
                        // BackSpace functionality
                        if (!toName2) {
                            if (!name1.empty())
                                name1.pop_back();
                        } else {
                            if (!name2.empty())
                                name2.pop_back();
                        }
                    } else if (event.key.code == Keyboard::Return) {
                        // Enter to go to next name or finish the reading process
                        if (!toName2) {
                            player1 = Player(name1);
                            toName2 = true;
                        }
                        else if(toName2 && !completed){
                            player2 = Player(name2);
                            completed = true;
                        }

                    }
                }
            }

        }

        startTheGame();
    }
}

void GameScreen::startTheGame(){

    currentGameState = GameState::RUNNING;

    ball.circle.setOrigin(ball.circle.getRadius() / 2, ball.circle.getRadius() / 2);
    ball.setPosition(Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    ball.update();

    blade1.blade.setOrigin(blade1.blade.getLocalBounds().width / 2, blade1.blade.getLocalBounds().height / 2);
    blade1.setPosition(Vector2f(50, window.getSize().y / 2));
    blade1.update();
    blade2.blade.setOrigin(blade2.blade.getLocalBounds().width / 2, blade2.blade.getLocalBounds().height / 2);
    blade2.setPosition(Vector2f(window.getSize().x - 50, window.getSize().y / 2));
    blade2.update();

    ballSpeed = 500;
    bladeSpeed = 500;

    srand(time(NULL));
    int dir = rand() % 2;

    ballDirection = (dir == 0) ? Direction::LEFT : Direction::RIGHT;
    blade1Direction = blade2Direction = -1;

    timeSinceBladesMove = Time::Zero;
    timeSinceLastMove = Time::Zero;

    walls = {
             Wall(Vector2f(0, 0), Vector2f(resolution.x, 10)), // top wall
             Wall(Vector2f(0, 0), Vector2f(5, resolution.y)),
             Wall(Vector2f(resolution.x - 5, 0), Vector2f(5, resolution.y)),
             Wall(Vector2f(0, resolution.y - 10), Vector2f(resolution.x, 10)) // down wall
            };

    draw();

    sleep(milliseconds(500));
}

void GameScreen::input(){
    Event event{};

    while(window.pollEvent(event)){
        // Window closed
        if(event.type == Event::Closed){
            window.close();
        }

        // Keyboard Input
        if (event.type == Event::KeyPressed) {
            if (currentGameState == GameState::INITIAL) {
                // Start
                if (event.key.code == Keyboard::Num1 || event.key.code == Keyboard::Numpad1) {
                    currentGameState = GameState::READING;
                }

                // Instructions
                if (event.key.code == Keyboard::Num2 || event.key.code == Keyboard::Numpad2)
                    drawInstructions();

                // Show HighScores Table
                if (event.key.code == Keyboard::Num3 || event.key.code == Keyboard::Numpad3)
                    drawHighscoresTable();

                // Quit
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                    window.close();

            } else {
                // Go back to menu
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                    currentGameState = GameState::INITIAL;

                if(currentGameState == GameState::RUNNING) {
                    // Pause
                    if (Keyboard::isKeyPressed(Keyboard::Space))
                        togglePause();

                    // Direction

                    if (event.key.code == Keyboard::W) {
                        blade1Direction = Direction::UP;
                    } else if (event.key.code == Keyboard::S) {
                        blade1Direction = Direction::DOWN;
                    }

                    if (event.key.code == Keyboard::Up) {
                        blade2Direction = Direction::UP;
                    } else if (event.key.code == Keyboard::Down) {
                        blade2Direction = Direction::DOWN;
                    }
                }
                else if(currentGameState == GameState::PAUSED){
                    // Pause
                    if (Keyboard::isKeyPressed(Keyboard::Space))
                        togglePause();

                }
                else if(currentGameState == GameState::DISPLAY){
                    if(event.key.code == Keyboard::Escape){
                        currentGameState = GameState::INITIAL;
                    }
                }

            }
        }

    }
}

void GameScreen::togglePause(){
    if(currentGameState == GameState::RUNNING){
        lastGameState = currentGameState;
        currentGameState = GameState::PAUSED;
    }
    else if(currentGameState == GameState::PAUSED){
        lastGameState = currentGameState;
        currentGameState = GameState::RUNNING;
    }
}

void GameScreen::draw(){
    window.clear(Color::Black);

    for(auto w: walls)
        window.draw(w.getShape());

    window.draw(ball.getShape());
    window.draw(blade1.getShape());
    window.draw(blade2.getShape());

    // Score
    Font fontScore;
    if(fontScore.loadFromFile("../arial.ttf")){
        Text score;
        score.setFont(fontScore);
        score.setString("SCORE");
        score.setCharacterSize(25);
        score.setFillColor(Color::White);
        score.setStyle(Text::Bold);
        score.setOrigin(score.getLocalBounds().width / 2,score.getLocalBounds().height / 2);
        score.setPosition(600, 50);

        window.draw(score);
    }


    Font font;
    if(font.loadFromFile("../arial.ttf")){
        // Player 1 score

        Text player1Score;
        player1Score.setFont(font);
        player1Score.setString(to_string(score1));
        player1Score.setCharacterSize(25);
        player1Score.setFillColor(Color::White);
        player1Score.setStyle(Text::Bold);
        player1Score.setOrigin(player1Score.getLocalBounds().width / 2, player1Score.getLocalBounds().height / 2);
        player1Score.setPosition(300, 50);

        // Player 1 name

        Text player1Name;
        player1Name.setFont(font);
        player1Name.setString(player1.getName());
        player1Name.setCharacterSize(25);
        player1Name.setFillColor(Color::White);
        player1Name.setStyle(Text::Bold);
        player1Name.setOrigin(player1Name.getLocalBounds().width / 2, player1Name.getLocalBounds().height / 2);
        player1Name.setPosition(300, 750);

        // Player 2 score

        Text player2Score;
        player2Score.setFont(font);
        player2Score.setString(to_string(score2));
        player2Score.setCharacterSize(25);
        player2Score.setFillColor(Color::White);
        player2Score.setStyle(Text::Bold);
        player2Score.setOrigin(player2Score.getLocalBounds().width / 2, player2Score.getLocalBounds().height / 2);
        player2Score.setPosition(900, 50);

        // Player 2 name

        Text player2Name;
        player2Name.setFont(font);
        player2Name.setString(player2.getName());
        player2Name.setCharacterSize(25);
        player2Name.setFillColor(Color::White);
        player2Name.setStyle(Text::Bold);
        player2Name.setOrigin(player2Name.getLocalBounds().width / 2, player2Name.getLocalBounds().height / 2);
        player2Name.setPosition(900, 750);

        window.draw(player1Score);
        window.draw(player1Name);
        window.draw(player2Score);
        window.draw(player2Name);
    }

    // Pause text
    if(currentGameState == GameState::PAUSED){

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

//    cout << player1.getHighScore() << ' ' << player2.getHighScore() << '\n';
//
//    if (score1 >= player1.getHighScore()) {
//        player1.setHighScore(score1);
//
//        Score aux(player1.getId(), player1.getName(), player1.getHighScore());
//
//        table.updateTable(aux);
//    }
//
//    if (score2 >= player2.getHighScore()) {
//        player2.setHighScore(score2);
//
//        Score aux(player2.getId(), player2.getName(), player2.getHighScore());
//
//        table.updateTable(aux);
//    }

    window.display();
}

void GameScreen::drawInstructions(){

    currentGameState = GameState::DISPLAY;

    window.clear(Color::Black);

    vector<string> instructions = {"Insert Player1's name and press Enter",
                                   "Insert Players'2 name and press Enter", "Player 1 press W to move the blade UP and S to move the blade DOWN",
                                   "Player 2 press ARROW UP to move the blade UP and ARROW DOWN to move the blade DOWN",
                                   "Press SPACE when the game is running to pause it",
                                   "Press ESC once to return to the menu and twice to exit the game",
                                   "Have fun and enjoy your time!"};

    Font font;
    float startPos = 250;
    if(font.loadFromFile("../arial.ttf")) {
        Text instr0;

        instr0.setFont(font);
        instr0.setString("Instructions for playing Pong");
        instr0.setCharacterSize(35);
        instr0.setFillColor(Color::White);
        instr0.setStyle(Text::Bold);
        instr0.setPosition(50, 100);

        window.draw(instr0);

        for (const auto& i: instructions) {
            Text instr;

            instr.setFont(font);
            instr.setString(i);
            instr.setCharacterSize(25);
            instr.setFillColor(Color::White);
            instr.setStyle(Text::Regular);
            instr.setPosition(50, startPos);

            startPos += 50;

            window.draw(instr);
        }
    }

    window.display();
}

void GameScreen::drawHighscoresTable(){
    currentGameState = GameState::DISPLAY;
    displayHighscoresTable = true;

    window.clear(Color::Black);

    Font font;
    float startPosY = 150;
    if(font.loadFromFile("../arial.ttf")) {

        // Header

        Text headerId, headerName, headerScore;

        headerId.setFont(font);
        headerId.setString("Player Id");
        headerId.setCharacterSize(35);
        headerId.setFillColor(Color::White);
        headerId.setStyle(Text::Bold);
        headerId.setOrigin(0, 0);
        headerId.setPosition(Vector2f(200, 50));

        headerName.setFont(font);
        headerName.setString("Name");
        headerName.setCharacterSize(35);
        headerName.setFillColor(Color::White);
        headerName.setStyle(Text::Bold);
        headerName.setOrigin(0, 0);
        headerName.setPosition(Vector2f(500, 50));

        headerScore.setFont(font);
        headerScore.setString("HighScore");
        headerScore.setCharacterSize(35);
        headerScore.setFillColor(Color::White);
        headerScore.setStyle(Text::Bold);
        headerScore.setOrigin(0, 0);
        headerScore.setPosition(Vector2f(800, 50));

        window.draw(headerId);
        window.draw(headerName);
        window.draw(headerScore);

        // Data

        table.sort();

        for (const auto& elem: table.getHighScoreTable()) {
            Text dataId, dataName, dataScore;

            dataId.setFont(font);
            dataId.setString(to_string(elem.id));
            dataId.setCharacterSize(25);
            dataId.setFillColor(Color::White);
            dataId.setStyle(Text::Regular);
            dataId.setOrigin(0, 0);
            dataId.setPosition(Vector2f(200, startPosY));

            dataName.setFont(font);
            dataName.setString(elem.name);
            dataName.setCharacterSize(25);
            dataName.setFillColor(Color::White);
            dataName.setStyle(Text::Regular);
            dataName.setOrigin(0, 0);
            dataName.setPosition(Vector2f(500, startPosY));

            dataScore.setFont(font);
            dataScore.setString(to_string(elem.score));
            dataScore.setCharacterSize(25);
            dataScore.setFillColor(Color::White);
            dataScore.setStyle(Text::Regular);
            dataScore.setOrigin(0, 0);
            dataScore.setPosition(Vector2f(800, startPosY));
            
            startPosY += 50.f;

            window.draw(dataId);
            window.draw(dataName);
            window.draw(dataScore);
        }

    }

    window.display();
}