#include "menuBase.h"
#include "field.h"
#include "packman.h"

using namespace sf;

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
    Color menuTextColor = Color::Yellow, int bord = 0, Color borderColor = Color::Blue);

void PlayGame(RenderWindow& window, Font& font, double width, double height);

void GamеStart(RenderWindow& window, Font& font, double width, double height);

void MainMenu(RenderWindow& window, Font& font, double width, double height);

void Pause(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape backgroundPlay(Vector2f(1920, 1080));

    Texture texturePlay;
    if (!texturePlay.loadFromFile("C:\\Users\\user\\Desktop\\image\\pause.png")) exit(1);
    backgroundPlay.setTexture(&texturePlay);

    Text TitulPause;
    TitulPause.setFont(font);
    InitText(TitulPause, 800, -80, L"PAUSE", 200, Color::Yellow, 3, Color::Black);

    String namePause[]{ L"RESUME",L"RESTART",L"EXIT GAME" };

    game::Pause myPause(window, 950, 175, 3, namePause, 200, 200);

    myPause.setColorTextMenu(Color::Blue, Color::Yellow, Color::Blue);

    myPause.AlignMenu(2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up) { myPause.MovePrev(); }

                if (event.key.code == Keyboard::Down) { myPause.MoveNext(); }

                if (event.key.code == Keyboard::Return)
                {
                    switch (myPause.getSelectedMenuNumber())
                    {
                    case 0:PlayGame(window, font, width, height);      break;
                    case 1:GamеStart(window, font, width, height);     break;
                    case 2:MainMenu(window, font, width, height);                      break;
                    }
                }
            }
        }
        window.clear();
        window.draw(backgroundPlay);
        window.draw(TitulPause);
        myPause.draw();
        window.display();
    }
}

void PlayGame(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape backgroundPlay(Vector2f(1920, 1080));

    Texture texturePlay;
    if (!texturePlay.loadFromFile("C:\\Users\\user\\Desktop\\image\\play-game.png")) exit(1);
    backgroundPlay.setTexture(&texturePlay);

    Text TitulRounds;
    TitulRounds.setFont(font);
    InitText(TitulRounds, 690, -80, L"ROUND 1/3", 200, Color::Yellow, 3, Color::Black);

    Text TitulPackman;
    TitulPackman.setFont(font);
    InitText(TitulPackman, 750, 840, L"PACKMAN", 200, Color::Yellow, 3, Color::Black);

    Text TitulFirstPlayer;
    TitulFirstPlayer.setFont(font);
    InitText(TitulFirstPlayer, 150, 150, L"Player 1", 100, Color::Yellow, 3, Color::Blue);

    Text TitulFirstNick;
    TitulFirstNick.setFont(font);
    InitText(TitulFirstNick, 120, 250, L"Nickname 1", 90, Color::Yellow, 3, Color::Blue);

    Text TitulFirstScore;
    TitulFirstScore.setFont(font);
    InitText(TitulFirstScore, 75, 500, L"Score: ", 80, Color::Yellow, 3, Color::Blue);

    Text TitulSecondPlayer;
    TitulSecondPlayer.setFont(font);
    InitText(TitulSecondPlayer, 1550, 150, L"Player 2", 100, Color::Yellow, 3, Color::Blue);

    Text TitulSecondNick;
    TitulSecondNick.setFont(font);
    InitText(TitulSecondNick, 1520, 250, L"Nickname 2", 90, Color::Yellow, 3, Color::Blue);

    Text TitulSecondScore;
    TitulSecondScore.setFont(font);
    InitText(TitulSecondScore, 1475, 500, L"Score: ", 80, Color::Yellow, 3, Color::Blue);

    Packman packman;

    packman.direction = Direction::NONE;
    packman.figure.setRadius(18);
    packman.figure.setFillColor(sf::Color::Yellow);
    packman.figure.setPosition(getPackmanStartPosition());

    Field field;
    initializeField(field);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased)
            {
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Up) {
                        packman.direction = Direction::UP;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        packman.direction = Direction::DOWN;
                    }
                    if (event.key.code == sf::Keyboard::Left) {
                        packman.direction = Direction::LEFT;
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        packman.direction = Direction::RIGHT;
                    }
                }
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape) { Pause(window, font, width, height); }
            }
        }
        const float speed = 200.f;

        const float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        const float step = speed * elapsedTime;

        packman.direction = Direction::NONE;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            packman.direction = Direction::UP;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            packman.direction = Direction::DOWN;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            packman.direction = Direction::LEFT;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            packman.direction = Direction::RIGHT;
        }

        sf::Vector2f movement(0.f, 0.f);
        if (packman.direction == Direction::UP) {
            movement.y -= step;
        }
        if (packman.direction == Direction::DOWN) {
            movement.y += step;
        }
        if (packman.direction == Direction::LEFT) {
            movement.x -= step;
        }
        if (packman.direction == Direction::RIGHT) {
            movement.x += step;
        }

        const sf::FloatRect packmanBounds = packman.figure.getGlobalBounds();
        if (checkFieldWallsCollision(field, packmanBounds, movement, speed)) {
            packman.direction = Direction::NONE;
        }
        if (packman.figure.getPosition().x < 535) {
            packman.figure.setPosition(packman.figure.getPosition().x + field.width * BLOCK_SIZE - 35, packman.figure.getPosition().y);
        }
        else if (packman.figure.getPosition().x > 500 + field.width * BLOCK_SIZE) {
            packman.figure.setPosition(535, packman.figure.getPosition().y);
        }
        packman.figure.move(movement);

        window.clear();
        window.draw(backgroundPlay);
        drawField(window, field);
        window.draw(packman.figure);
        window.draw(TitulRounds);
        window.draw(TitulPackman);
        window.draw(TitulFirstPlayer);
        window.draw(TitulFirstNick);
        window.draw(TitulFirstScore);
        window.draw(TitulSecondPlayer);
        window.draw(TitulSecondNick);
        window.draw(TitulSecondScore);
        window.display();
    }
}

void GamеStart(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape backgroundPlay(Vector2f(1920, 1080));

    Texture texturePlay;
    if (!texturePlay.loadFromFile("C:\\Users\\user\\Desktop\\image\\start-game.png")) exit(1);
    backgroundPlay.setTexture(&texturePlay);

    Text TitulStart;
    TitulStart.setFont(font);
    InitText(TitulStart, 800, -80, L"GAME", 200, Color::Yellow, 3, Color::Black);

    Text TitulGameSelection;
    TitulGameSelection.setFont(font);
    InitText(TitulGameSelection, 150, 200, L"GAME SELECTION", 100, Color::Yellow, 3, Color::Blue);

    Text TitulCountBots;
    TitulCountBots.setFont(font);
    InitText(TitulCountBots, 200, 535, L"COUNT BOTS", 100, Color::Yellow, 3, Color::Blue);

    Text TitulChoseMap;
    TitulChoseMap.setFont(font);
    InitText(TitulChoseMap, 1025, 140, L"CHOSE MAP", 200, Color::Yellow, 3, Color::Blue);

    Text TitulStartGame;
    TitulStartGame.setFont(font);
    InitText(TitulStartGame, 775, 840, L"START", 200, Color::Yellow, 3, Color::Black);

    String nameGameSelection[]{ L"Classic",L"Fast Game" };

    game::GameSelection myGameSelection(window, 210, 320, 2, nameGameSelection, 90, 270);

    myGameSelection.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    myGameSelection.AlignMenu(2);

    String bots[]{ L"1",L"2",L"3",L"4" };

    game::ChoseBots myBots(window, 175, 650, 4, bots, 90, 120);

    myBots.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    myBots.AlignMenu(2);

    String maps[]{ L"1",L"2",L"3" };

    game::Maps myMaps(window, 950, 725, 3, maps, 90, 370);

    myMaps.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    myMaps.AlignMenu(2);
    int countBots = 1;
    int page = 0;
    while (window.isOpen())
    {
        Event eventPlay;
        while (window.pollEvent(eventPlay))
        {
            switch (page)
            {
            case 0:
                if (eventPlay.type == Event::KeyReleased)
                {
                    if (eventPlay.key.code == Keyboard::Left) { myGameSelection.MovePrev(); }

                    if (eventPlay.key.code == Keyboard::Right) { myGameSelection.MoveNext(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {
                        page = 1;
                    }
                }
                break;
            case 1:
                if (eventPlay.type == Event::KeyReleased)
                {
                    if (eventPlay.key.code == Keyboard::Left) { myBots.MovePrev(); }
                    if (eventPlay.key.code == Keyboard::Right) { myBots.MoveNext(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {
                        page = 2;
                    }
                }
                break;
            case 2:
                if (eventPlay.type == Event::KeyReleased)
                {
                    if (eventPlay.key.code == Keyboard::Left) { myMaps.MovePrev(); }
                    if (eventPlay.key.code == Keyboard::Right) { myMaps.MoveNext(); }
                    if (eventPlay.key.code == Keyboard::Return)
                    {
                        PlayGame(window, font, width, height);
                    }
                }
                break;
            }
            if (eventPlay.type == Event::KeyPressed)
            {
                if (eventPlay.key.code == Keyboard::Escape) { MainMenu(window, font, 1920, 1080); }
            }
        }
        window.clear();
        window.draw(backgroundPlay);
        window.draw(TitulStart);
        window.draw(TitulGameSelection);
        window.draw(TitulCountBots);
        window.draw(TitulChoseMap);
        window.draw(TitulStartGame);
        myGameSelection.draw();
        myBots.draw();
        myMaps.draw();
        window.display();
    }
}

void Settings(sf::RenderWindow& window, sf::Font& font, double width, double height)
{
    RectangleShape backgroundOpt(Vector2f(width, height));

    Texture textureOpt;
    if (!textureOpt.loadFromFile("C:\\Users\\user\\Desktop\\image\\settings.png")) exit(2);
    backgroundOpt.setTexture(&textureOpt);

    Text Titul, SettingsMenu1, SettingsMenu2, Save;
    SettingsMenu1.setFont(font);
    SettingsMenu2.setFont(font);
    Titul.setFont(font);
    Save.setFont(font);

    InitText(Titul, 780, -30, "Settings", 150, Color::Yellow, 3, Color::Black);
    InitText(SettingsMenu1, 300, 150, "Management", 100, Color::Yellow, 3, Color::Black);
    InitText(SettingsMenu2, 1400, 150, "Game", 100, Color::Yellow, 3, Color::Black);
    InitText(Save, 830, 840, L"SAVE", 200, Color::Blue, 3, Color::Black);

    String ManagementCount[]{ L"1",L"2" };

    game::Settings Management(window, 260, 550, 2, ManagementCount, 90, 430);

    Management.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Management.AlignMenu(2);

    String name_user[]{ L"Name :" };
    game::Settings Name(window, 1150, 340, 1, name_user, 90);

    Name.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Name.AlignMenu(2);

    String color_menu[]{ L"Color :" };
    game::Settings Color(window, 1150, 560, 1, color_menu, 90);

    Color.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Color.AlignMenu(2);

    String Color_count[]{ L"1",L"2", L"3" };

    game::Settings Color_name(window, 1450, 700, 3, Color_count, 90, 150);

    Color_name.setColorTextMenu(Color::Blue, Color::Yellow, Color::Black);

    Color_name.AlignMenu(2);

    Text message("", font, 20);
    int page = 0;
    while (window.isOpen())
    {
        Event eventOpt;
        while (window.pollEvent(eventOpt))
        {
            switch (page)
            {
            case 0:
                if (eventOpt.type == Event::KeyReleased)
                {
                    if (eventOpt.key.code == Keyboard::Left) { Management.MovePrev(); }

                    if (eventOpt.key.code == Keyboard::Right) { Management.MoveNext(); }
                    if (eventOpt.key.code == Keyboard::Return)
                    {
                        page = 1;
                    }
                }
                break;
            case 1:
                if (eventOpt.type == Event::TextEntered)
                {
                    std::string text = message.getString();
                    int digit = eventOpt.text.unicode;
                    if (text.length() < 12) {
                        message.setString(text + (char)(digit));
                    }
                    if (digit == 57) {
                        message.setString(text + '9');
                    }
                    if (digit == 8) {
                        message.setString(text.substr(0, text.length() - 1));
                    }

                    InitText(message, 1395, 320, message.getString(), 100, Color::Blue, 3, Color::Black);
                }
                if (eventOpt.type == Event::KeyReleased)
                {
                    if (eventOpt.key.code == Keyboard::Return)
                    {
                        page = 2;
                    }
                }
                break;
            case 2:
                if (eventOpt.type == Event::KeyReleased)
                {
                    if (eventOpt.key.code == Keyboard::Left) { Color_name.MovePrev(); }
                    if (eventOpt.key.code == Keyboard::Right) { Color_name.MoveNext(); }
                    if (eventOpt.key.code == Keyboard::Return)
                    {
                        MainMenu(window, font, 1920, 1080);
                    }
                }
                break;
            };

            if (eventOpt.type == Event::KeyPressed)
            {
                if (eventOpt.key.code == Keyboard::Escape) { MainMenu(window, font, 1920, 1080); }
            }
        }
        window.clear();
        window.draw(backgroundOpt);
        window.draw(Titul);
        window.draw(SettingsMenu1);
        window.draw(SettingsMenu2);
        window.draw(Save);
        window.draw(message);
        Name.draw();
        Color.draw();
        Color_name.draw();
        Management.draw();
        window.display();
    }
}

void Exit(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape backgroundExit(Vector2f(width, height));

    Texture textureExit;
    if (!textureExit.loadFromFile("C:\\Users\\user\\Desktop\\image\\exit.png")) exit(1);
    backgroundExit.setTexture(&textureExit);

    Text TitulExit;
    TitulExit.setFont(font);
    InitText(TitulExit, 525, 250, L"ARE YOU SURE?", 200, Color::Yellow, 3, Color::Blue);

    String nameExit[]{ L"YES",L"NO" };

    game::Exit myExit(window, 775, 450, 2, nameExit, 200, 300);

    myExit.setColorTextMenu(Color::Blue, Color::Yellow, Color::Blue);

    myExit.AlignMenu(2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Left) { myExit.MovePrev(); }

                if (event.key.code == Keyboard::Right) { myExit.MoveNext(); }

                if (event.key.code == Keyboard::Return)
                {
                    switch (myExit.getSelectedMenuNumber())
                    {
                    case 0:window.close();                        break;
                    case 1:MainMenu(window, font, width, height); break;
                    }
                }
            }
        }
        window.clear();
        window.draw(backgroundExit);
        window.draw(TitulExit);
        myExit.draw();
        window.display();
    }
}

void MainMenu(RenderWindow& window, Font& font, double width, double height)
{
    RectangleShape background(Vector2f(width, height));

    Texture textureWindow;
    if (!textureWindow.loadFromFile("C:\\Users\\user\\Desktop\\image\\packman-menu.png")) exit(1);
    background.setTexture(&textureWindow);

    String nameMenu[]{ L"START",L"SETTINGS",L"EXIT" };

    game::Menu mymenu(window, 1400, 250, 3, nameMenu, 150, 160);

    mymenu.setColorTextMenu(Color::Blue, Color::Yellow, Color::Blue);

    mymenu.AlignMenu(2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up) { mymenu.MovePrev(); }

                if (event.key.code == Keyboard::Down) { mymenu.MoveNext(); }

                if (event.key.code == Keyboard::Return)
                {
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:GamеStart(window, font, width, height);    break;
                    case 1:Settings(window, font, width, height);     break;
                    case 2:Exit(window, font, width, height);         break;
                    }
                }
            }
        }
        window.clear();
        window.draw(background);
        mymenu.draw();
        window.display();
    }
}

int main()
{
    RenderWindow window;

    window.create(VideoMode::getDesktopMode(), L"Packman", Style::Fullscreen);

    window.setMouseCursorVisible(false);

    double width = VideoMode::getDesktopMode().width;
    double height = VideoMode::getDesktopMode().height;

    Font font;
    if (!font.loadFromFile("C:\\Users\\user\\Desktop\\font\\EightBits.ttf")) return 5;

    MainMenu(window, font, width, height);

    return 0;
}

void InitText(Text& mtext, float xpos, float ypos, String str, int size_font,
    Color menu_text_color, int bord, Color border_color)
{
    mtext.setCharacterSize(size_font);
    mtext.setPosition(xpos, ypos);
    mtext.setString(str);
    mtext.setFillColor(menu_text_color);
    mtext.setOutlineThickness(bord);
    mtext.setOutlineColor(border_color);
}
