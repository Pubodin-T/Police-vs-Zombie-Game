#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <fstream>

int State = 0;

float tempTotalTime = 0;
sf::Clock tempClock;
int XPolice = 0, XTroll = 0, XZombie = 0, XItem;
sf::IntRect rectPolice, rectTroll, rectBoss, rectZombie1, rectZombie2, rectZombie3, rectZombie4, rectZombie5, rectItem, rectMain, rectCat;

float timeZ1 = 0;
float timeZ2 = 0;
float timeZ3 = 0;
float timeZ4 = 0;
float timeZ5 = 0;
float timeTroll = 0;
float timeBoss = 0;
float timeEffect = 0;
float timeEffect2 = 0;
float PoliceX = 200, PoliceY = 500;
int Map = 1;
int BulletStat = 0;
int PoliceAction = 0;
int Z1Action = 0;
int HpZ1 = 300;
int HpZ2 = 200;
int HpZ3 = 500;
int HpZ4 = 400;
int HpZ5 = 100;
int HpTroll = 1000;
int HpBoss = 1000;
int HpPlayer = 200;
int MaxHp = 200;
int delayZ1 = 25;
int delayZ2 = 25;
int delayZ3 = 25;
int delayZ4 = 25;
int delayZ5 = 25;
int delayTroll = 30;
int delayBoss = 30;
int delayP = 30;
int delayEF = 5;
int EffectStat = 0;
int numTroll = 0;
int random;
int Batk = 100;
float Effect[20];
int boss = 0;
bool Statgun = false;
bool Statwalk = true;
bool Statcar = false;
bool cursorstate = false;
bool Statfuel = false;
char last_char = ' ';

std::string scoretext[10];



void update()
{
	tempTotalTime += tempClock.restart().asSeconds();
	if (tempTotalTime > 0.1)
	{
		tempTotalTime = 0;
		XPolice++;
		XTroll++;
		XZombie++;
		XItem++;
		if (XPolice > 7)
		{
			XPolice = 0;
		}

		if (XTroll > 6)
		{
			XTroll = 0;
		}
		if (XZombie > 5)
		{
			XZombie = 0;
		}
		if (XItem > 3)
		{
			XItem = 0;
		}
	}

	rectPolice.left = XPolice * rectPolice.width;
	rectMain.left = XPolice * rectMain.width;
	rectTroll.left = XTroll * rectTroll.width;
	rectBoss.left = XTroll * rectBoss.width;
	rectZombie1.left = XZombie * rectZombie1.width;
	rectZombie2.left = XZombie * rectZombie2.width;
	rectZombie3.left = XZombie * rectZombie3.width;
	rectZombie4.left = XZombie * rectZombie4.width;
	rectZombie5.left = XZombie * rectZombie5.width;
	rectItem.left = XItem * rectItem.width;
	rectCat.left = XItem * rectCat.width;
}

void Sortscore(int RecentScore, std::string RecentName)
{
	std::vector<std::pair<int, std::string> > score;
	std::fstream myFile;
	myFile.open("Score.txt");
	std::string temp;
	std::string tempString;
	int tempInt = 0, P = 1;
	bool state = false;


	while (getline(myFile, temp))
	{
		if (state == false)
		{
			tempString = temp;
		}
		else
		{
			for (int i = temp.length() - 1;i >= 0;i--, P *= 10)
			{
				tempInt += (temp[i] - '0') * P;
			}
			score.push_back(make_pair(tempInt, tempString));
			P = 1;
			tempInt = 0;
		}
		state = !state;
		//cout << Temp << endl;
	}
	myFile.close();
	score.push_back(make_pair(RecentScore, RecentName));
	sort(score.begin(), score.end());
	std::cout << "Sorted\n";
	myFile.open("Score.txt");
	for (int i = 5;i >= 1;i--)
	{
		myFile << score[i].second << "\n" << score[i].first << std::endl;
		std::cout << score[i].first << " -- " << score[i].second << std::endl;

	}
	myFile.close();
}

void showscore()
{
	std::fstream showscore1;
	showscore1.open("Score.txt");
	std::string show;
	int z = 0;

	while (getline(showscore1, show))
	{
		scoretext[z] = show;
		z++;

		if (z >= 10)
		{
			break;
		}


	}
	showscore1.close();
}

int main()
{
	srand(time(0));
	sf::Clock Efclock[20];
	for (int i = 0;i < 20;i++)
	{
		Effect[i] = 0;

	}

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Police VS. Zombie", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1920, 1080));
	sf::Image Icon;
	Icon.loadFromFile("images/Icon.png");
	window.setIcon(256, 256, Icon.getPixelsPtr());


	sf::Cursor iconcursor;
	sf::Image image_cursor;
	image_cursor.loadFromFile("images/Mouse.png");
	iconcursor.loadFromPixels(image_cursor.getPixelsPtr(), image_cursor.getSize(), { 8, 8 });
	window.setMouseCursor(iconcursor);
	std::cout << "Cursorloaded\n";




	sf::Event event;

	sf::Font font1, font2;
	int Score = 0;
	font1.loadFromFile("Font/Deanna.ttf");
	font2.loadFromFile("Font/Opun.ttf");
	sf::Text myText, myText2, PLAY, HOWTOPLAY, HIGHSCORE, EXIT, SCORE, Menu, ScoreText[10], Name, Resume;
	std::string myString, myString2, play, howtoplay, highscore, exit, yourscore, menu, name, resume;
	for (int i = 0;i < 10;i++)
	{
		ScoreText[i].setFont(font1);
		ScoreText[i].setFillColor(sf::Color::Green);
		ScoreText[i].setCharacterSize(100);

	}
	Name.setFont(font2);
	Name.setFillColor(sf::Color::White);
	name = "Create by  Pubodin Tieanthong   62010711";
	Name.setString(name);
	Name.setCharacterSize(30);
	Name.setPosition(450, 990);

	myText.setFont(font1);
	myText2.setFont(font1);
	PLAY.setFont(font1);
	HOWTOPLAY.setFont(font1);
	HIGHSCORE.setFont(font1);
	EXIT.setFont(font1);
	SCORE.setFont(font1);
	Menu.setFont(font1);
	Resume.setFont(font1);
	myText.setFillColor(sf::Color::Green);
	myText2.setFillColor(sf::Color::Green);
	PLAY.setFillColor(sf::Color::Green);
	HOWTOPLAY.setFillColor(sf::Color::Green);
	HIGHSCORE.setFillColor(sf::Color::Green);
	EXIT.setFillColor(sf::Color::Green);
	SCORE.setFillColor(sf::Color::Green);
	Menu.setFillColor(sf::Color::Green);
	Resume.setFillColor(sf::Color::Green);
	myString = "Score  " + std::to_string(Score);
	myString2 = "HP  " + std::to_string(HpPlayer);
	play = "Play";
	howtoplay = "How To Play";
	highscore = "HighScore";
	exit = "EXIT";
	menu = "Menu";
	resume = "Resume";
	Menu.setString(menu);
	myText.setString(myString);
	myText2.setString(myString2);
	PLAY.setString(play);
	HOWTOPLAY.setString(howtoplay);
	HIGHSCORE.setString(highscore);
	EXIT.setString(exit);
	Resume.setString(resume);
	myText.setCharacterSize(100);
	Menu.setCharacterSize(100);
	SCORE.setCharacterSize(100);
	myText2.setCharacterSize(100);
	PLAY.setCharacterSize(200);
	HIGHSCORE.setCharacterSize(200);
	HOWTOPLAY.setCharacterSize(200);
	EXIT.setCharacterSize(200);
	Resume.setCharacterSize(150);
	PLAY.setPosition(1350, 200);
	EXIT.setPosition(1350, 800);
	HOWTOPLAY.setPosition(1100, 400);
	HIGHSCORE.setPosition(1200, 600);
	SCORE.setPosition(700, 350);
	std::cout << "Fontloaded\n";

	sf::Texture Bg1, B1, S1, Bg2, B2, S2, Bg3, B3, S3, M, I, D, S4, W, H, High, P;
	Bg1.loadFromFile("images/back/Back1.png");
	B1.loadFromFile("images/back/Behind1.png");
	S1.loadFromFile("images/back/Sky1.png");

	Bg2.loadFromFile("images/back/Back2.png");
	B2.loadFromFile("images/back/Behind2.png");
	S2.loadFromFile("images/back/Sky2.png");

	Bg3.loadFromFile("images/back/Back3.png");
	B3.loadFromFile("images/back/Behind3.png");
	M.loadFromFile("images/back/Main-01.png");
	I.loadFromFile("images/back/Input-01.png");
	D.loadFromFile("images/back/Dead-01.png");
	S4.loadFromFile("images/back/Sky.png");
	W.loadFromFile("images/back/Win-01.png");
	H.loadFromFile("images/back/Howtoplay-01.png");
	High.loadFromFile("images/back/High-01.png");
	P.loadFromFile("images/back/Pause-01.png");
	std::cout << "Bgloaded\n";

	sf::Sprite Back1, Town1, Sky1, Back2, Town2, Sky2, Back3, Town3, MainBg, InputBg, DeadBg, Sky4, Sky5, WinBg, HowBg, HighBG, PauseBG;
	Back1.setTexture(Bg1);
	Town1.setTexture(B1);
	Sky1.setTexture(S1);
	MainBg.setTexture(M);
	InputBg.setTexture(I);
	DeadBg.setTexture(D);
	Sky4.setTexture(S4);
	Sky5.setTexture(S4);
	WinBg.setTexture(W);
	HowBg.setTexture(H);
	HighBG.setTexture(High);
	PauseBG.setTexture(P);
	Sky4.setPosition(0, 0);
	Sky5.setPosition(1920, 0);

	Back2.setTexture(Bg2);
	Town2.setTexture(B2);
	Sky2.setTexture(S2);

	Back3.setTexture(Bg3);
	Town3.setTexture(B3);
	std::cout << "SetBgloaded\n";

	sf::RectangleShape Mainpolice(sf::Vector2f(400.f, 925.f));
	Mainpolice.setPosition(0.f, 110.f);
	sf::Texture Maintex;
	Maintex.loadFromFile("images/back/Mainchar-01.png");
	Mainpolice.setTexture(&Maintex);
	rectMain = sf::IntRect(0, 0, Maintex.getSize().x / 8, Maintex.getSize().y);
	Mainpolice.setTextureRect(rectMain);
	std::cout << "MainPoloaded\n";


	sf::RectangleShape Black(sf::Vector2f(1920.f, 3300.f));
	Black.setFillColor(sf::Color::Black);
	Black.setPosition(5700, 0);

	sf::RectangleShape Black2(sf::Vector2f(1920.f, 3300.f));
	Black2.setFillColor(sf::Color::Black);
	Black2.setPosition(-1920, 0);

	std::cout << "Blackloaded\n";


	sf::RectangleShape police(sf::Vector2f(450.f, 430.0f));
	sf::Texture policeTexture, plWlak, plBack, plAttack1, plAttack2, plAttack3, plDie;
	plDie.loadFromFile("images/player/Hurt.png");
	plWlak.loadFromFile("images/player/Walk.png");
	plBack.loadFromFile("images/player/Back.png");
	plAttack1.loadFromFile("images/player/Attack1.png");
	plAttack2.loadFromFile("images/player/Attack2.png");
	plAttack3.loadFromFile("images/player/Attack3.png");
	policeTexture.loadFromFile("images/player/Idle.png");
	police.setTexture(&policeTexture);
	rectPolice = sf::IntRect(0, 0, policeTexture.getSize().x / 8, policeTexture.getSize().y);
	police.setTextureRect(rectPolice);

	std::cout << "Police loaded\n";

	sf::RectangleShape Bullet(sf::Vector2f(75.f, 50.0f));
	Bullet.setPosition(-100, -100);
	sf::Texture B;
	B.loadFromFile("images/player/BB2-01.png");
	Bullet.setTexture(&B);
	std::cout << "Bullet loaded\n";

	sf::RectangleShape HP(sf::Vector2f(100.f, 100.0f));
	HP.setPosition(9000.0f, 10.0f);
	sf::Texture HpTex;
	HpTex.loadFromFile("images/Item/Hp-01.png");
	HP.setTexture(&HpTex);
	rectItem = sf::IntRect(0, 0, HpTex.getSize().x / 4, HpTex.getSize().y);
	HP.setTextureRect(rectItem);
	std::cout << "Hp loaded\n";

	sf::RectangleShape Gun(sf::Vector2f(100.f, 100.0f));
	sf::Texture G;
	G.loadFromFile("images/Item/Gun1-01.png");
	Gun.setTexture(&G);
	rectItem = sf::IntRect(0, 0, G.getSize().x / 4, G.getSize().y);
	Gun.setTextureRect(rectItem);
	std::cout << "Gun loaded\n";

	sf::RectangleShape GunEF(sf::Vector2f(100.f, 100.0f));
	GunEF.setPosition(9000.0f, 10.0f);
	sf::Texture GEF;
	GEF.loadFromFile("images/Item/Gun1EF-01.png");
	GunEF.setTexture(&GEF);
	rectItem = sf::IntRect(0, 0, GEF.getSize().x / 4, GEF.getSize().y);
	GunEF.setTextureRect(rectItem);
	std::cout << "GunEF loaded\n";

	sf::RectangleShape Medkit(sf::Vector2f(100.f, 100.0f));
	sf::Texture med;
	Medkit.setPosition(9000.0f, 10.0f);
	med.loadFromFile("images/Item/Med-01.png");
	Medkit.setTexture(&med);
	rectItem = sf::IntRect(0, 0, med.getSize().x / 4, med.getSize().y);
	Medkit.setTextureRect(rectItem);
	std::cout << "Medkit loaded\n";

	sf::RectangleShape Atk(sf::Vector2f(100.f, 100.0f));
	sf::Texture atk;
	Atk.setPosition(9000.0f, 10.0f);
	atk.loadFromFile("images/Item/Atk3-01.png");
	Atk.setTexture(&atk);
	rectItem = sf::IntRect(0, 0, atk.getSize().x / 4, atk.getSize().y);
	Atk.setTextureRect(rectItem);
	std::cout << "Atk loaded\n";

	sf::RectangleShape Fuel(sf::Vector2f(100.f, 100.0f));
	sf::Texture fueltex;
	fueltex.loadFromFile("images/Item/Fuel-01.png");
	Fuel.setTexture(&fueltex);
	rectItem = sf::IntRect(0, 0, fueltex.getSize().x / 4, fueltex.getSize().y);
	Fuel.setTextureRect(rectItem);
	std::cout << "Fuel loaded\n";

	sf::RectangleShape CAT(sf::Vector2f(375.f, 350.0f));
	sf::Texture cattex;
	cattex.loadFromFile("images/Nyan.png");
	CAT.setTexture(&cattex);
	rectCat = sf::IntRect(0, 0, cattex.getSize().x / 4, cattex.getSize().y);
	CAT.setTextureRect(rectCat);
	std::cout << "CAT loaded\n";

	sf::RectangleShape Car(sf::Vector2f(900.f, 400.0f));
	sf::Texture cartex1, cartex2;
	cartex1.loadFromFile("images/Item/Care-01.png");
	cartex2.loadFromFile("images/Item/Car1-01.png");
	Car.setTexture(&cartex1);
	std::cout << "Car loaded\n";

	sf::RectangleShape Troll(sf::Vector2f(1080.f, 800.0f));
	sf::Texture TrollWalk, TrollAttack, TrollDie;
	TrollWalk.loadFromFile("images/Enemy/Troll/Walk-01.png");
	TrollAttack.loadFromFile("images/Enemy/Troll/Attack-01.png");
	TrollDie.loadFromFile("images/Enemy/Troll/Dead-01.png");
	Troll.setTexture(&TrollWalk);
	rectTroll = sf::IntRect(0, 0, TrollWalk.getSize().x / 7, TrollWalk.getSize().y);
	Troll.setTextureRect(rectTroll);
	std::cout << "Troll loaded\n";

	sf::RectangleShape Boss(sf::Vector2f(1550.f, 1080.0f));
	sf::Texture BossWalk, BossAttack, BossDie;
	BossWalk.loadFromFile("images/Enemy/Troll/BossWalk-01.png");
	BossAttack.loadFromFile("images/Enemy/Troll/BossAttack-01.png");
	BossDie.loadFromFile("images/Enemy/Troll/BossDead-01.png");
	Boss.setTexture(&BossWalk);
	rectBoss = sf::IntRect(0, 0, BossWalk.getSize().x / 7, BossWalk.getSize().y);
	Boss.setTextureRect(rectBoss);
	std::cout << "Boss loaded\n";


	sf::RectangleShape Zombie1(sf::Vector2f(490.f, 470.0f));
	sf::Texture Z1Walk, Z1Attack, Z1Die;
	Z1Attack.loadFromFile("images/Enemy/Zombie1/Attack-01.png");
	Z1Walk.loadFromFile("images/Enemy/Zombie1/Walk-01.png");
	Z1Die.loadFromFile("images/Enemy/Zombie1/Dead-01.png");
	Zombie1.setTexture(&Z1Walk);
	rectZombie1 = sf::IntRect(0, 0, Z1Walk.getSize().x / 6, Z1Walk.getSize().y);
	Zombie1.setTextureRect(rectZombie1);
	std::cout << "Z1 loaded\n";


	sf::RectangleShape Zombie2(sf::Vector2f(490.f, 470.0f));
	sf::Texture Z2Walk, Z2Attack, Z2Die;
	Z2Attack.loadFromFile("images/Enemy/Zombie2/Attack-01.png");
	Z2Walk.loadFromFile("images/Enemy/Zombie2/Walk-01.png");
	Z2Die.loadFromFile("images/Enemy/Zombie2/Dead-01.png");
	Zombie2.setTexture(&Z2Walk);
	rectZombie2 = sf::IntRect(0, 0, Z2Walk.getSize().x / 6, Z2Walk.getSize().y);
	Zombie2.setTextureRect(rectZombie2);
	std::cout << "Z2 loaded\n";


	sf::RectangleShape Zombie3(sf::Vector2f(490.f, 470.0f));

	sf::Texture Z3Walk, Z3Attack, Z3Die;
	Z3Attack.loadFromFile("images/Enemy/Zombie3/Attack-01.png");
	Z3Walk.loadFromFile("images/Enemy/Zombie3/Walk.png");
	Z3Die.loadFromFile("images/Enemy/Zombie3/Dead-01.png");
	Zombie3.setTexture(&Z3Walk);
	rectZombie3 = sf::IntRect(0, 0, Z3Walk.getSize().x / 6, Z3Walk.getSize().y);
	Zombie3.setTextureRect(rectZombie3);
	std::cout << "Z3 loaded\n";

	sf::RectangleShape Zombie4(sf::Vector2f(490.f, 470.0f));

	sf::Texture Z4Walk, Z4Attack, Z4Die;
	Z4Attack.loadFromFile("images/Enemy/Zombie4/Attack-01.png");
	Z4Walk.loadFromFile("images/Enemy/Zombie4/Walk-01.png");
	Z4Die.loadFromFile("images/Enemy/Zombie4/Dead-01.png");
	Zombie4.setTexture(&Z4Walk);
	rectZombie4 = sf::IntRect(0, 0, Z4Walk.getSize().x / 6, Z4Walk.getSize().y);
	Zombie4.setTextureRect(rectZombie4);
	std::cout << "Z4 loaded\n";

	sf::RectangleShape Zombie5(sf::Vector2f(490.f, 470.0f));

	sf::Texture Z5Walk, Z5Attack, Z5Die;
	Z5Attack.loadFromFile("images/Enemy/Zombie5/Attack-01.png");
	Z5Walk.loadFromFile("images/Enemy/Zombie5/Walk-01.png");
	Z5Die.loadFromFile("images/Enemy/Zombie5/Dead-01.png");
	Zombie5.setTexture(&Z5Walk);
	rectZombie5 = sf::IntRect(0, 0, Z5Walk.getSize().x / 6, Z5Walk.getSize().y);
	Zombie5.setTextureRect(rectZombie4);
	std::cout << "Z5 loaded\n";

	sf::SoundBuffer Main, M1, M2, M3;
	Main.loadFromFile("Sound/Main.wav");
	M1.loadFromFile("Sound/Map1.wav");
	M2.loadFromFile("Sound/Map2.wav");
	M3.loadFromFile("Sound/Map3.wav");
	sf::Sound sound_BG;
	sound_BG.setBuffer(Main);
	sound_BG.play();
	sound_BG.setLoop(true);
	sound_BG.setVolume(20.f);

	sf::SoundBuffer Gunbuffer, Hitbuffer;
	Gunbuffer.loadFromFile("Sound/Glock-1.wav");
	Hitbuffer.loadFromFile("Sound/Hit.wav");
	sf::Sound GunSound, Hit;
	GunSound.setBuffer(Gunbuffer);
	Hit.setBuffer(Hitbuffer);
	GunSound.setVolume(50.f);
	std::cout << "Sound loaded\n";

	sf::SoundBuffer ZombieWalk, ZombieDie, ZombieAttack, BAttack, BDead, BWalk, TAttack, TDead, Pick, Horn;
	ZombieWalk.loadFromFile("Sound/zombie2.wav");
	ZombieDie.loadFromFile("Sound/zombiedeath.wav");
	ZombieAttack.loadFromFile("Sound/ZAttack.wav");
	BAttack.loadFromFile("Sound/BossAttack.wav");
	TAttack.loadFromFile("Sound/TrollAttack.wav");
	BDead.loadFromFile("Sound/BossDeadV2.wav");
	TDead.loadFromFile("Sound/Trolldead.wav");
	BWalk.loadFromFile("Sound/FootStep.wav");
	Pick.loadFromFile("Sound/Pick.wav");
	Horn.loadFromFile("Sound/Car.wav");
	sf::Sound ZSound, ZDieSoud, ZAttackSoud, BossSound, TrollSound, ItemSound, CarSound;
	ZSound.setBuffer(ZombieWalk);
	BossSound.setBuffer(BWalk);
	TrollSound.setBuffer(TAttack);
	ItemSound.setBuffer(Pick);
	CarSound.setBuffer(Horn);
	std::cout << "Setbuf loaded\n";

	sf::RectangleShape object;
	object.setSize(sf::Vector2f(300.0f, 70.0f));
	object.setOrigin(sf::Vector2f(150.0f, 35.0f));
	object.setPosition(sf::Vector2f(950, 700.0f));

	sf::RectangleShape cursor;
	cursor.setSize(sf::Vector2f(5.0f, 64.0f));
	cursor.setOrigin(sf::Vector2f(2.5f, 32.0f));
	cursor.setPosition(sf::Vector2f(805, 700.0f));
	cursor.setFillColor(sf::Color::Black);

	sf::Font fontText;
	fontText.loadFromFile("Font/Deanna.ttf");
	sf::Text text;
	text.setFont(fontText);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Black);
	text.setPosition(800, 675);

	std::string input;

	std::cout << "Font loaded\n";


	sf::Clock clock1, clock2, clock3, clock4, clock5, clock6, clock7, clock8, clock9;




	while (window.isOpen())
	{

		while (State == 0)
		{
			window.setMouseCursorVisible(true);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					State = 9;
				}
			}


			if (Sky4.getPosition().x >= -1920)
			{
				Sky4.move(-1.f, 0);
			}
			else
			{
				Sky4.setPosition(0, 0);
			}
			if (Sky5.getPosition().x >= 0)
			{
				Sky5.move(-1.f, 0);
			}
			else
			{
				Sky5.setPosition(1920, 0);
			}

			if (PLAY.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				PLAY.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					State = 1;
					sound_BG.setBuffer(M1);
					sound_BG.play();
				}
			}
			else
			{
				PLAY.setFillColor(sf::Color::Green);
			}

			if (EXIT.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				EXIT.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					window.close();
					State = 9;
				}
			}
			else
			{
				EXIT.setFillColor(sf::Color::Green);
			}

			if (HOWTOPLAY.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				HOWTOPLAY.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					State = 5;
				}
			}
			else
			{
				HOWTOPLAY.setFillColor(sf::Color::Green);
			}

			if (HIGHSCORE.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				HIGHSCORE.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					State = 6;
				}
			}
			else
			{
				HIGHSCORE.setFillColor(sf::Color::Green);
			}

			update();
			window.clear();
			input.clear();
			window.draw(Sky4);
			window.draw(Sky5);
			window.draw(MainBg);
			Mainpolice.setTextureRect(rectMain);
			window.draw(Mainpolice);
			window.draw(Name);
			window.draw(PLAY);
			window.draw(HOWTOPLAY);
			window.draw(HIGHSCORE);
			window.draw(EXIT);
			window.display();



		}

		while (State == 1)
		{

			std::cout << input << std::endl;

			police.setPosition(200.0f, 550.0f);
			Troll.setPosition(2500.0f, 1280.0f);
			Boss.setPosition(4000.0f, 2060.0f);
			Back1.setPosition(0, 0);
			Town1.setPosition(0, 0);
			Sky1.setPosition(0, 0);
			Back2.setPosition(0, 1081);
			Town2.setPosition(-500, 1081);
			Sky2.setPosition(-700, 1081);
			Back3.setPosition(0, 2162);
			Town3.setPosition(-700, 2162);
			Fuel.setPosition(10000.0f, 10.0f);
			HpPlayer = 200;
			HpBoss = 2000;
			police.setPosition(200.0f, 550.0f);
			Gun.setPosition(1600.0f, 750.0f);
			Map = 1;
			Score = 0;
			numTroll = 0;
			boss = 0;
			Batk = 100;
			MaxHp = 200;
			PoliceX = 200;
			Statcar = false;
			cursorstate = false;
			Statgun = false;


			Boss.setTexture(&BossWalk);
			rectBoss = sf::IntRect(0, 0, BossWalk.getSize().x / 7, BossWalk.getSize().y);
			Boss.setTextureRect(rectBoss);
			Zombie1.setPosition((police.getPosition().x + 1800), (police.getPosition().y - 50));
			Zombie2.setPosition((police.getPosition().x + 3200), 500.0f);
			Zombie3.setPosition((police.getPosition().x + 3200), 1650.0f);
			Zombie4.setPosition((police.getPosition().x + 5400), 1650.0f);
			Zombie5.setPosition((police.getPosition().x + 5400), 500.0f);
			Car.setPosition(4000, 2800);

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					State = 9;
				}
			}

			if (event.type == sf::Event::EventType::TextEntered)
			{

				if (last_char != event.text.unicode && event.text.unicode == 8 &&
					input.length() > 0) // delete
				{

					last_char = event.text.unicode;
					input.erase(input.length() - 1);
					text.setString(input);
					cursor.setPosition(800.0f + text.getGlobalBounds().width + 5, 700.0f);
					std::cout << input << std::endl;

				}
				else if (last_char != event.text.unicode &&
					(event.text.unicode >= 'a' && event.text.unicode <= 'z' ||
						event.text.unicode >= 'A' && event.text.unicode <= 'Z' ||
						event.text.unicode >= '0' && event.text.unicode <= '9'))
				{
					//std::cout << event.text.unicode << std::endl;
					last_char = event.text.unicode;

					input += event.text.unicode;

					text.setString(input);

					cursor.setPosition(800.0f + text.getGlobalBounds().width + 5, 700.0f);

					std::cout << input << std::endl;
				}

			}

			if (event.type == sf::Event::EventType::KeyReleased && last_char != ' ')
			{
				last_char = ' ';
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && input.length() > 0)
			{
				State = 2;
			}

			if (Sky4.getPosition().x >= -1920)
			{
				Sky4.move(-1.f, 0);
			}
			else
			{
				Sky4.setPosition(0, 0);
			}
			if (Sky5.getPosition().x >= 0)
			{
				Sky5.move(-1.f, 0);
			}
			else
			{
				Sky5.setPosition(1920, 0);
			}
			window.clear();
			window.draw(Sky4);
			window.draw(Sky5);
			window.draw(InputBg);
			window.draw(object);

			Effect[17] += Efclock[17].restart().asSeconds();
			if (Effect[17] >= 0.5)
			{
				Effect[17] = 0;
				cursorstate = !cursorstate;
			}
			if (cursorstate == true)
			{
				window.draw(cursor);
			}


			window.draw(text);
			window.display();


		}
		while (State == 2)
		{


			timeZ1 += clock1.restart().asSeconds();
			timeZ2 += clock2.restart().asSeconds();
			timeZ3 += clock3.restart().asSeconds();
			timeZ4 += clock4.restart().asSeconds();
			timeZ5 += clock5.restart().asSeconds();
			timeTroll += clock6.restart().asSeconds();
			timeBoss += clock7.restart().asSeconds();
			timeEffect += clock8.restart().asSeconds();
			timeEffect2 += clock9.restart().asSeconds();

			for (int i = 0;i < 20;i++)
			{
				Effect[i] += Efclock[i].restart().asSeconds();

			}




			myText.setPosition(police.getPosition().x + 1300, police.getPosition().y - 580);
			myText2.setPosition(police.getPosition().x - 150, police.getPosition().y - 580);



			sf::Event event;
			while (window.pollEvent(event))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{

					State = 7;
				}
			}
			if (((Zombie1.getPosition().x - 100 <= police.getPosition().x) || (Zombie2.getPosition().x - 100 <= police.getPosition().x) || (Zombie5.getPosition().x - 100 <= police.getPosition().x)) && Map == 1)
			{
				Statwalk = false;

			}
			else if (((Zombie3.getPosition().x - 100 <= police.getPosition().x) || (Zombie4.getPosition().x - 100 <= police.getPosition().x) || (Troll.getPosition().x - 100 <= police.getPosition().x)) && Map == 2)
			{
				Statwalk = false;

			}
			else if (Boss.getPosition().x - 100 <= police.getPosition().x && Map == 3)
			{
				Statwalk = false;

			}
			else
			{
				Statwalk = true;
			}



			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && BulletStat == 0 && Statgun == true)
			{

				if (PoliceAction != 3)
				{
					PoliceAction = 3;
					rectPolice = sf::IntRect(0, 0, plAttack2.getSize().x / 8, plAttack2.getSize().y);
					police.setTexture(&plAttack2);

				}
				delayP--;
				EffectStat = 1;
				if (delayP <= 0)
				{
					GunSound.play();
					Bullet.setPosition(police.getPosition().x + 340, police.getPosition().y + 190);
					BulletStat = 1;

					delayP = 30;
				}


			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Statwalk == true)
				{

					if (PoliceAction != 2)
					{
						PoliceAction = 2;
						rectPolice = sf::IntRect(0, 0, plWlak.getSize().x / 8, plWlak.getSize().y);
						police.setTexture(&plWlak);
					}

					PoliceX += 20;
					police.move(8, 0);
					if (Map == 1)
					{
						Town1.move(3, 0);
						Sky1.move(8, 0);
					}
					else if (Map == 2)
					{
						Town2.move(3, 0);
						Sky2.move(8, 0);
					}
					else if (Map == 3)
					{
						Town3.move(3, 0);

					}
				}

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && PoliceX > 200)
				{

					if (PoliceAction != 1)
					{
						PoliceAction = 1;
						rectPolice = sf::IntRect(0, 0, plBack.getSize().x / 8, plBack.getSize().y);
						police.setTexture(&plBack);
					}

					PoliceX -= 20;
					police.move(-8, 0);


					if (Map == 1)
					{
						Town1.move(-3, 0);
						Sky1.move(-8, 0);
					}
					else if (Map == 2)
					{
						Town2.move(-3, 0);
						Sky2.move(-8, 0);
					}
					else if (Map == 3)
					{
						Town3.move(-3, 0);

					}
				}

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && PoliceX > 200) {
				if (PoliceAction != 1)
				{
					PoliceAction = 1;
					rectPolice = sf::IntRect(0, 0, plBack.getSize().x / 8, plBack.getSize().y);
					police.setTexture(&plBack);
				}

				PoliceX -= 10;
				police.move(-5, 0);


				if (Map == 1)
				{
					Town1.move(-2, 0);
					Sky1.move(-5, 0);
				}
				else if (Map == 2)
				{
					Town2.move(-2, 0);
					Sky2.move(-5, 0);
				}
				else if (Map == 3)
				{
					Town3.move(-2, 0);

				}

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Statwalk == true)
			{
				if (PoliceAction != 2)
				{
					PoliceAction = 2;
					rectPolice = sf::IntRect(0, 0, plWlak.getSize().x / 8, plWlak.getSize().y);
					police.setTexture(&plWlak);
				}

				PoliceX += 10;
				police.move(5, 0);
				if (Map == 1)
				{
					Town1.move(2, 0);
					Sky1.move(5, 0);
				}
				else if (Map == 2)
				{
					Town2.move(2, 0);
					Sky2.move(5, 0);
				}
				else if (Map == 3)
				{
					Town3.move(2, 0);

				}


			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (PoliceAction != 4)
				{
					PoliceAction = 4;
					rectPolice = sf::IntRect(0, 0, plAttack1.getSize().x / 8, plAttack1.getSize().y);
					police.setTexture(&plAttack1);
				}

				if (Map == 1)
				{
					if (timeZ1 >= 0.5 && (Zombie1.getPosition().x <= police.getPosition().x + 270))
					{
						HpZ1 -= 10;

					}
					if (timeZ2 >= 0.5 && (Zombie2.getPosition().x <= police.getPosition().x + 270))
					{
						HpZ2 -= 10;

					}
					if (timeZ5 >= 0.5 && (Zombie5.getPosition().x <= police.getPosition().x + 270))
					{
						HpZ5 -= 50;

					}
				}
				if (Map == 2)
				{
					if (timeZ3 >= 0.5 && (Zombie3.getPosition().x <= police.getPosition().x + 270))
					{
						HpZ3 -= 10;

					}
					if (timeZ4 >= 0.5 && (Zombie4.getPosition().x <= police.getPosition().x + 270))
					{
						HpZ4 -= 10;

					}
					if (timeTroll >= 0.5 && (Troll.getPosition().x <= police.getPosition().x + 270))
					{
						HpTroll -= 10;

					}
				}
				if (Map == 3)
				{
					if (timeBoss >= 0.5 && (Boss.getPosition().x <= police.getPosition().x + 270))
					{
						HpBoss -= 5;
					}
				}

				if (Effect[4] >= 1)
				{

					Hit.play();
					Effect[4] = 0;
				}



			}

			else {

				if (PoliceAction != 0)
				{
					PoliceAction = 0;
					rectPolice = sf::IntRect(0, 0, policeTexture.getSize().x / 8, policeTexture.getSize().y);
					police.setTexture(&policeTexture);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if (Gun.getPosition().x <= police.getPosition().x + 300)
				{
					if (Effect[11] >= 0.5)
					{
						ItemSound.play();
						Effect[11] = 0;
					}
					Gun.setPosition(10000, 1000);
					Statgun = true;

				}

				if (HP.getPosition().x <= police.getPosition().x + 300)
				{
					if (Effect[11] >= 0.5)
					{
						ItemSound.play();
						Effect[11] = 0;
					}
					HP.setPosition(10000, 1000);
					HpPlayer += 50;
				}

				if (Medkit.getPosition().x <= police.getPosition().x + 300)
				{
					if (Effect[11] >= 0.5)
					{
						ItemSound.play();
						Effect[11] = 0;
					}
					Medkit.setPosition(10000, 1000);
					HpPlayer += 100;
					MaxHp += 100;
				}
				if (HpPlayer >= MaxHp)
				{
					HpPlayer = MaxHp;
				}
				if (Atk.getPosition().x <= police.getPosition().x + 300)
				{
					if (Effect[11] >= 0.5)
					{
						ItemSound.play();
						Effect[11] = 0;
					}
					Atk.setPosition(10000, 1000);
					Batk += 50;
				}

				if (Fuel.getPosition().x <= police.getPosition().x + 300)
				{
					if (Effect[11] >= 0.5)
					{
						ItemSound.play();
						Effect[11] = 0;
					}
					Fuel.setPosition(10000, 1000);
					Statfuel = true;
				}

				if (Car.getPosition().x <= police.getPosition().x + 100 && Map == 3 && Statfuel == true)
				{
					Car.setTexture(&cartex2);
					police.setPosition(-1000, -1000);
					Statcar = true;

				}


			}

			/////EFFECT/////
			if (EffectStat == 1)
			{
				delayEF--;

				GunEF.setPosition(police.getPosition().x + 365, police.getPosition().y + 165);
				if (delayEF <= 0)
				{

					EffectStat = 0;
					delayEF = 2;
				}
			}
			else if (EffectStat == 0)
			{
				GunEF.setPosition(-300, -200);
			}



			if (BulletStat == 1)
			{
				Bullet.move(30, 0);


			}




			////////////Hp/////////////
			if (HpPlayer <= 0)
			{

				HpPlayer = 0;
				if (PoliceAction != 5)
				{
					PoliceAction = 5;
					rectPolice = sf::IntRect(0, 0, plDie.getSize().x / 8, plDie.getSize().y);
					police.setTexture(&plDie);
				}
				Sortscore(Score, input);
				State = 3;
			}



			if (Map == 1)
			{
				if (HpZ1 <= 0)
				{
					rectZombie1 = sf::IntRect(0, 0, Z1Die.getSize().x / 6, Z1Die.getSize().y);
					Zombie1.setTexture(&Z1Die);
					delayZ1--;
					if (Effect[0] >= 1)
					{
						ZSound.setBuffer(ZombieDie);
						ZSound.play();
						Effect[0] = 0;
					}
					if (delayZ1 <= 0)
					{
						HpZ1 = 300;
						Score += 300;
						Zombie1.setPosition((police.getPosition().x + 2400), (police.getPosition().y - 50));
						delayZ1 = 25;
					}
				}
				else if (Zombie1.getPosition().x <= police.getPosition().x + 250)
				{
					if (Effect[5] >= 1)
					{
						ZSound.setBuffer(ZombieAttack);
						ZSound.play();
						Effect[5] = 0;
					}
					rectZombie1 = sf::IntRect(0, 0, Z1Attack.getSize().x / 6, Z1Attack.getSize().y);
					Zombie1.setTexture(&Z1Attack);

					if (timeZ1 >= 3 && HpPlayer > 0 && police.getPosition().x <= 5700)
					{
						HpPlayer -= 15;
						timeZ1 = 0;
					}
				}
				else if (Zombie1.getPosition().x > police.getPosition().x + 250)
				{
					rectZombie1 = sf::IntRect(0, 0, Z1Walk.getSize().x / 6, Z1Walk.getSize().y);
					Zombie1.setTexture(&Z1Walk);
					Zombie1.move(-4.f, 0.0f);
				}
				///Z2///
				if (HpZ2 <= 0)
				{
					rectZombie2 = sf::IntRect(0, 0, Z2Die.getSize().x / 6, Z2Die.getSize().y);
					Zombie2.setTexture(&Z2Die);
					delayZ2--;
					if (timeEffect >= 1)
					{
						ZSound.setBuffer(ZombieDie);
						ZSound.play();
						timeEffect = 0;
					}
					if (delayZ2 <= 0)
					{
						random = rand() % 5 + 1;
						if (random == 2 || random == 4)
						{
							HP.setPosition(Zombie2.getPosition().x + 100, Zombie2.getPosition().y + 400);

						}

						HpZ2 = 200;
						Score += 200;
						Zombie2.setPosition((police.getPosition().x + 3200), (police.getPosition().y - 50));
						delayZ2 = 25;
					}
				}
				else if (Zombie2.getPosition().x <= police.getPosition().x + 250)
				{

					if (Effect[6] >= 1)
					{
						ZSound.setBuffer(ZombieAttack);
						ZSound.play();
						Effect[6] = 0;
					}
					rectZombie2 = sf::IntRect(0, 0, Z2Attack.getSize().x / 6, Z2Attack.getSize().y);
					Zombie2.setTexture(&Z2Attack);

					if (timeZ2 >= 3 && HpPlayer > 0 && police.getPosition().x <= 5700)
					{

						HpPlayer -= 20;
						timeZ2 = 0;
					}
				}
				else if (Zombie2.getPosition().x > police.getPosition().x + 250)
				{
					if (timeEffect2 >= 5)
					{
						ZSound.setBuffer(ZombieWalk);
						ZSound.play();
						timeEffect2 = 0;
					}
					rectZombie2 = sf::IntRect(0, 0, Z2Walk.getSize().x / 6, Z2Walk.getSize().y);
					Zombie2.setTexture(&Z2Walk);
					Zombie2.move(-4.7f, 0.0f);
				}

				///Z5///
				if (HpZ5 <= 0)
				{
					rectZombie5 = sf::IntRect(0, 0, Z5Die.getSize().x / 6, Z5Die.getSize().y);
					Zombie5.setTexture(&Z5Die);
					delayZ5--;
					if (Effect[3] >= 1)
					{
						ZSound.setBuffer(ZombieDie);
						ZSound.play();
						Effect[3] = 0;
					}
					if (delayZ5 <= 0)
					{
						HpZ5 = 100;
						Score += 100;
						Zombie5.setPosition((police.getPosition().x + 4000), (police.getPosition().y - 50));
						delayZ5 = 25;
					}
				}
				else if (Zombie5.getPosition().x <= police.getPosition().x + 200)
				{
					if (Effect[9] >= 1)
					{
						ZSound.setBuffer(ZombieAttack);
						ZSound.play();
						Effect[9] = 0;
					}
					rectZombie5 = sf::IntRect(0, 0, Z5Attack.getSize().x / 6, Z5Attack.getSize().y);
					Zombie5.setTexture(&Z5Attack);

					if (timeZ5 >= 2 && HpPlayer > 0)
					{
						HpPlayer -= 10;
						timeZ5 = 0;
					}
				}
				else if (Zombie5.getPosition().x > police.getPosition().x + 200)
				{
					rectZombie5 = sf::IntRect(0, 0, Z5Walk.getSize().x / 6, Z5Walk.getSize().y);
					Zombie5.setTexture(&Z5Walk);
					Zombie5.move(-7.f, 0.0f);
				}
			}
			if (Map == 2)
			{
				////Z3////
				if (HpZ3 <= 0)
				{
					rectZombie3 = sf::IntRect(0, 0, Z3Die.getSize().x / 6, Z3Die.getSize().y);
					Zombie3.setTexture(&Z3Die);
					delayZ3--;
					if (Effect[1] >= 1)
					{
						ZSound.setBuffer(ZombieDie);
						ZSound.play();
						Effect[1] = 0;
					}
					if (delayZ3 <= 0)
					{
						random = rand() % 5 + 1;
						if (random == 2 || random == 4)
						{
							Atk.setPosition(Zombie3.getPosition().x + 100, Zombie3.getPosition().y + 400);

						}
						HpZ3 = 500;
						Score += 500;
						Zombie3.setPosition((police.getPosition().x + 2800), (police.getPosition().y - 50));
						delayZ3 = 25;
					}
				}
				else if (Zombie3.getPosition().x <= police.getPosition().x + 250)
				{
					if (Effect[7] >= 1)
					{
						ZSound.setBuffer(ZombieAttack);
						ZSound.play();
						Effect[7] = 0;
					}
					rectZombie3 = sf::IntRect(0, 0, Z3Attack.getSize().x / 6, Z3Attack.getSize().y);
					Zombie3.setTexture(&Z3Attack);

					if (timeZ3 >= 3 && HpPlayer > 0 && police.getPosition().x <= 5700)
					{
						HpPlayer -= 25;
						timeZ3 = 0;
					}
				}
				else if (Zombie3.getPosition().x > police.getPosition().x + 250)
				{
					rectZombie3 = sf::IntRect(0, 0, Z3Walk.getSize().x / 6, Z3Walk.getSize().y);
					Zombie3.setTexture(&Z3Walk);
					Zombie3.move(-3.f, 0.0f);
				}


				///Z4///
				if (HpZ4 <= 0)
				{
					rectZombie4 = sf::IntRect(0, 0, Z4Die.getSize().x / 6, Z4Die.getSize().y);
					Zombie4.setTexture(&Z4Die);
					delayZ4--;
					if (Effect[2] >= 1)
					{
						ZSound.setBuffer(ZombieDie);
						ZSound.play();
						Effect[2] = 0;
					}
					if (delayZ4 <= 0)
					{
						random = rand() % 5 + 1;
						if (random == 2 || random == 4)
						{
							HP.setPosition(Zombie4.getPosition().x + 100, Zombie4.getPosition().y + 400);

						}

						HpZ4 = 400;
						Score += 400;
						Zombie4.setPosition((police.getPosition().x + 4000), (police.getPosition().y - 50));
						delayZ4 = 25;
					}
				}
				else if (Zombie4.getPosition().x <= police.getPosition().x + 250)
				{
					if (Effect[8] >= 1)
					{
						ZSound.setBuffer(ZombieAttack);
						ZSound.play();
						Effect[8] = 0;
					}
					rectZombie4 = sf::IntRect(0, 0, Z4Attack.getSize().x / 6, Z4Attack.getSize().y);
					Zombie4.setTexture(&Z4Attack);

					if (timeZ4 >= 3 && HpPlayer > 0 && police.getPosition().x <= 5700)
					{
						HpPlayer -= 20;
						timeZ4 = 0;
					}
				}
				else if (Zombie4.getPosition().x > police.getPosition().x + 250)
				{
					rectZombie4 = sf::IntRect(0, 0, Z4Walk.getSize().x / 6, Z4Walk.getSize().y);
					Zombie4.setTexture(&Z4Walk);
					Zombie4.move(-4.7f, 0.0f);
				}

				///Troll///
				if (Map == 2 && numTroll <= 4)
				{
					if (HpTroll <= 0)
					{
						if (Effect[16] >= 2)
						{
							TrollSound.setBuffer(TDead);
							TrollSound.play();
							Effect[16] = 0;
						}
						rectTroll = sf::IntRect(0, 0, TrollDie.getSize().x / 7, TrollDie.getSize().y);
						Troll.setTexture(&TrollDie);
						delayTroll--;

						if (delayTroll <= 0)
						{
							random = rand() % 5 + 1;
							if (random == 2)
							{
								Medkit.setPosition(Troll.getPosition().x + 500, Troll.getPosition().y + 700);

							}
							numTroll++;
							HpTroll = 1000;
							Score += 1000;
							Troll.setPosition((police.getPosition().x + 3000), (police.getPosition().y - 360));
							delayTroll = 25;
						}
						if (numTroll == 4)
						{
							std::cout << "Troll Gone\n";
							Troll.setPosition(-1000, -1000);
						}
					}
					else if (Troll.getPosition().x <= police.getPosition().x + 250)
					{
						if (Effect[15] >= 2)
						{
							TrollSound.setBuffer(TAttack);
							TrollSound.play();
							Effect[15] = 0;
						}
						rectTroll = sf::IntRect(0, 0, TrollAttack.getSize().x / 7, TrollAttack.getSize().y);
						Troll.setTexture(&TrollAttack);

						if (timeTroll >= 3 && HpPlayer > 0 && police.getPosition().x <= 5700)
						{
							HpPlayer -= 75;
							timeTroll = 0;
						}
					}
					else if (Troll.getPosition().x > police.getPosition().x + 250)
					{
						if (Effect[10] >= 5)
						{
							ZSound.setBuffer(ZombieWalk);
							ZSound.play();
							Effect[10] = 0;
						}
						rectTroll = sf::IntRect(0, 0, TrollWalk.getSize().x / 7, TrollWalk.getSize().y);
						Troll.setTexture(&TrollWalk);
						Troll.move(-1.0f, 0.0f);
					}
				}
			}

			if (Map == 3)
			{
				if (HpBoss <= 0)
				{

					rectBoss = sf::IntRect(0, 0, BossDie.getSize().x / 7, BossDie.getSize().y);
					Boss.setTexture(&BossDie);
					delayBoss--;
					if (Effect[12] >= 4 && boss == 0)
					{
						BossSound.setBuffer(BDead);
						BossSound.play();
						boss++;
						Effect[12] = 0;

					}



					if (delayBoss <= 0)
					{
						Score += 5000;
						Fuel.setPosition(Boss.getPosition().x + 500, Boss.getPosition().y + 900);
						Boss.setPosition(8000, -1000);
						if (Effect[12] >= 6)
						{
							BossSound.stop();
						}
						HpBoss = 5000;
					}


				}
				else if (Boss.getPosition().x <= police.getPosition().x + 250 && HpBoss <= 3000)
				{

					rectTroll = sf::IntRect(0, 0, BossAttack.getSize().x / 7, BossAttack.getSize().y);
					Boss.setTexture(&BossAttack);
					if (Effect[13] >= 1.5)
					{
						BossSound.setBuffer(BAttack);
						BossSound.play();
						Effect[13] = 0;
					}
					if (timeBoss >= 2.5f && HpPlayer > 0 && police.getPosition().x <= 5700)
					{
						HpPlayer -= 120;
						timeBoss = 0;
					}
				}
				else if (Boss.getPosition().x > police.getPosition().x + 250 && HpBoss <= 3000)
				{
					if (Effect[14] >= 1)
					{
						BossSound.setBuffer(BWalk);
						BossSound.play();
						Effect[14] = 0;
					}
					rectBoss = sf::IntRect(0, 0, BossWalk.getSize().x / 7, BossWalk.getSize().y);
					Boss.setTexture(&BossWalk);
					Boss.move(-4.0f, 0.0f);
				}
			}









			///Shoot///


			if ((Bullet.getPosition().x >= Zombie1.getPosition().x + 130) && Map == 1)
			{
				Zombie1.setFillColor(sf::Color::Red);
				HpZ1 -= Batk;
				BulletStat = 0;
				Bullet.setPosition(-100, -100);
			}
			else if ((Bullet.getPosition().x >= Zombie2.getPosition().x + 130) && Map == 1)
			{
				Zombie2.setFillColor(sf::Color::Red);
				HpZ2 -= Batk;
				BulletStat = 0;
				Bullet.setPosition(-100, -100);
			}
			else if ((Bullet.getPosition().x >= Zombie3.getPosition().x + 130) && Map == 2)
			{
				Zombie3.setFillColor(sf::Color::Red);
				HpZ3 -= Batk;
				BulletStat = 0;
				Bullet.setPosition(-100, -100);
			}
			else if ((Bullet.getPosition().x >= Zombie4.getPosition().x + 130) && Map == 2)
			{
				Zombie4.setFillColor(sf::Color::Red);
				HpZ4 -= Batk;
				BulletStat = 0;
				Bullet.setPosition(-100, -100);
			}
			else if ((Bullet.getPosition().x >= Troll.getPosition().x + 300) && Map == 2)
			{
				Troll.setFillColor(sf::Color::Red);
				HpTroll -= Batk;
				BulletStat = 0;
				Bullet.setPosition(-100, -100);
			}
			else if ((Bullet.getPosition().x >= Boss.getPosition().x + 300) && Map == 3)
			{
				Boss.setFillColor(sf::Color::Red);
				HpBoss -= Batk;
				BulletStat = 0;
				Bullet.setPosition(-100, -100);
			}
			else if ((Bullet.getPosition().x >= Zombie5.getPosition().x + 130) && Map == 1)
			{
				Zombie5.setFillColor(sf::Color::Red);
				HpZ5 -= Batk;
				BulletStat = 0;
				Bullet.setPosition(-100, -100);
			}
			else
			{
				Zombie1.setFillColor(sf::Color::White);
				Zombie2.setFillColor(sf::Color::White);
				Zombie3.setFillColor(sf::Color::White);
				Zombie4.setFillColor(sf::Color::White);
				Zombie5.setFillColor(sf::Color::White);
				Troll.setFillColor(sf::Color::White);
				Boss.setFillColor(sf::Color::White);
			}



			if (police.getPosition().x >= 5400)
			{

				if (Map == 1)
				{

					Zombie1.setPosition(8000, police.getPosition().y - 50);
					Zombie2.setPosition(8000, police.getPosition().y - 50);
					Zombie5.setPosition(8000, police.getPosition().y - 50);

				}
				else if (Map == 2)
				{

					Zombie3.setPosition(8000, police.getPosition().y - 50);
					Zombie4.setPosition(8000, police.getPosition().y - 50);
					Troll.setPosition(8000, police.getPosition().y - 360);

				}
			}



			//Warp
			if (police.getPosition().x >= 5900)
			{
				if (Map == 1)
				{
					sound_BG.setBuffer(M2);
					sound_BG.play();
					PoliceX = 200;
					police.setPosition(-500, 1630);
					Map++;
				}
				else if (Map == 2)
				{
					sound_BG.setBuffer(M3);
					sound_BG.play();
					PoliceX = 200;
					police.setPosition(-500, 2710);
					Map++;
				}

			}





			std::cout << input << "         " << Score << std::endl;


			auto cord = police.getPosition();
			view.setCenter(cord.x + 760, cord.y - 10);

			if (Statcar == true)
			{

				auto carview = Car.getPosition();
				view.setCenter(carview.x + 760, carview.y - 100);
				Car.move(5.f, 0.f);
				CarSound.play();
				if (Car.getPosition().x >= 5900)
				{
					Sortscore(Score, input);
					State = 4;
				}
			}
			view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

			update();
			myString = "Score  " + std::to_string(Score);
			myText.setString(myString);
			myString2 = "Hp  " + std::to_string(HpPlayer);
			myText2.setString(myString2);
			window.setView(view);

			police.setTextureRect(rectPolice);
			Troll.setTextureRect(rectTroll);
			Boss.setTextureRect(rectBoss);
			Zombie1.setTextureRect(rectZombie1);
			Zombie2.setTextureRect(rectZombie2);
			Zombie3.setTextureRect(rectZombie3);
			Zombie4.setTextureRect(rectZombie4);
			Zombie5.setTextureRect(rectZombie5);
			HP.setTextureRect(rectItem);
			Gun.setTextureRect(rectItem);
			GunEF.setTextureRect(rectItem);
			Medkit.setTextureRect(rectItem);
			Atk.setTextureRect(rectItem);
			Fuel.setTextureRect(rectItem);


			window.setMouseCursorVisible(false);


			window.draw(Sky1);
			window.draw(Sky2);
			window.draw(Town1);
			window.draw(Town2);

			window.draw(Back1);
			window.draw(Back2);
			window.draw(Back3);
			window.draw(Town3);
			window.draw(Gun);



			window.draw(Troll);
			window.draw(Zombie1);
			window.draw(Zombie2);
			window.draw(Zombie3);
			window.draw(Zombie4);
			window.draw(Zombie5);


			window.draw(Boss);
			window.draw(Bullet);

			window.draw(HP);
			window.draw(Medkit);
			window.draw(Atk);
			window.draw(Fuel);
			window.draw(police);
			window.draw(GunEF);
			window.draw(Car);

			window.draw(Black);
			window.draw(Black2);
			window.draw(myText);
			window.draw(myText2);


			window.display();
			window.clear();

		}

		while (State == 3)
		{
			Menu.setPosition(860, 500);
			window.setMouseCursorVisible(true);
			view.setCenter(DeadBg.getPosition().x + 960, DeadBg.getPosition().y + 540);
			window.setView(view);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					State = 9;
				}
			}


			if (Sky4.getPosition().x >= -1920)
			{
				Sky4.move(-1.f, 0);
			}
			else
			{
				Sky4.setPosition(0, 0);
			}
			if (Sky5.getPosition().x >= 0)
			{
				Sky5.move(-1.f, 0);
			}
			else
			{
				Sky5.setPosition(1920, 0);
			}

			if (Menu.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				Menu.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					State = 0;
					sound_BG.setBuffer(Main);
					sound_BG.play();


				}
			}
			else
			{
				Menu.setFillColor(sf::Color::Green);
			}
			yourscore = "Your Score is  " + std::to_string(Score);
			SCORE.setString(yourscore);

			window.draw(Sky4);
			window.draw(Sky5);
			window.draw(DeadBg);
			window.draw(SCORE);
			window.draw(Menu);
			window.display();
			window.clear();
		}

		while (State == 4)
		{
			Menu.setPosition(860, 500);
			window.setMouseCursorVisible(true);
			view.setCenter(WinBg.getPosition().x + 960, WinBg.getPosition().y + 540);
			window.setView(view);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					State = 9;
				}
			}


			if (Sky4.getPosition().x >= -1920)
			{
				Sky4.move(-1.f, 0);
			}
			else
			{
				Sky4.setPosition(0, 0);
			}
			if (Sky5.getPosition().x >= 0)
			{
				Sky5.move(-1.f, 0);
			}
			else
			{
				Sky5.setPosition(1920, 0);
			}

			if (Menu.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				Menu.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					State = 0;
					sound_BG.setBuffer(Main);
					sound_BG.play();


				}
			}
			else
			{
				Menu.setFillColor(sf::Color::Green);
			}
			yourscore = "Your Score is  " + std::to_string(Score);
			SCORE.setString(yourscore);

			window.draw(Sky4);
			window.draw(Sky5);
			window.draw(WinBg);
			window.draw(SCORE);
			window.draw(Menu);
			window.display();
			window.clear();
		}

		while (State == 5)
		{
			window.setMouseCursorVisible(true);
			view.setCenter(HowBg.getPosition().x + 960, HowBg.getPosition().y + 540);
			Menu.setPosition(1670, 850);
			window.setView(view);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					State = 9;
				}
			}


			if (Sky4.getPosition().x >= -1920)
			{
				Sky4.move(-1.f, 0);
			}
			else
			{
				Sky4.setPosition(0, 0);
			}
			if (Sky5.getPosition().x >= 0)
			{
				Sky5.move(-1.f, 0);
			}
			else
			{
				Sky5.setPosition(1920, 0);
			}

			if (Menu.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				Menu.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					State = 0;



				}
			}
			else
			{
				Menu.setFillColor(sf::Color::Green);
			}

			menu = "Menu";
			Menu.setString(menu);
			window.draw(Sky4);
			window.draw(Sky5);
			window.draw(HowBg);
			window.draw(Menu);
			window.display();
			window.clear();
		}

		while (State == 6)
		{
			window.setMouseCursorVisible(true);
			view.setCenter(HighBG.getPosition().x + 960, HighBG.getPosition().y + 540);
			Menu.setPosition(1670, 850);
			window.setView(view);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					State = 9;
				}
			}
			showscore();
			int name_y = 200;
			int score_y = 200;

			for (int a = 0;a < 10;a++)
			{
				if (a % 2 == 0)
				{
					ScoreText[a].setString(scoretext[a]);
					ScoreText[a].setPosition(400, name_y += 130);
				}
				else
				{
					ScoreText[a].setString(scoretext[a]);
					ScoreText[a].setPosition(1300, score_y += 130);
				}
				std::cout << scoretext[a] << std::endl;
			}



			if (Sky4.getPosition().x >= -1920)
			{
				Sky4.move(-1.f, 0);
			}
			else
			{
				Sky4.setPosition(0, 0);
			}
			if (Sky5.getPosition().x >= 0)
			{
				Sky5.move(-1.f, 0);
			}
			else
			{
				Sky5.setPosition(1920, 0);
			}

			if (Menu.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				Menu.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					State = 0;
				}
			}
			else
			{
				Menu.setFillColor(sf::Color::Green);
			}

			window.draw(Sky4);
			window.draw(Sky5);
			window.draw(HighBG);
			window.draw(Menu);
			for (int a = 0;a < 10;a++)
			{
				window.draw(ScoreText[a]);
			}
			window.display();
			window.clear();
		}

		while (State == 7)
		{
			window.setMouseCursorVisible(true);
			view.setCenter(PauseBG.getPosition().x + 960, PauseBG.getPosition().y + 540);
			window.setView(view);
			Menu.setPosition(880, 850);
			Resume.setPosition(800, 620);
			CAT.setPosition(750, 300);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{

					State = 2;
				}
			}


			if (Sky4.getPosition().x >= -1920)
			{
				Sky4.move(-1.f, 0);
			}
			else
			{
				Sky4.setPosition(0, 0);
			}
			if (Sky5.getPosition().x >= 0)
			{
				Sky5.move(-1.f, 0);
			}
			else
			{
				Sky5.setPosition(1920, 0);
			}

			if (Menu.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				Menu.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					State = 0;
					sound_BG.setBuffer(Main);
					sound_BG.play();
				}
			}
			else
			{
				Menu.setFillColor(sf::Color::Green);
			}


			if (Resume.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				Resume.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					State = 2;

				}
			}
			else
			{
				Resume.setFillColor(sf::Color::Green);
			}
			update();
			CAT.setTextureRect(rectCat);
			window.draw(Sky4);
			window.draw(Sky5);
			window.draw(PauseBG);
			window.draw(CAT);
			window.draw(Resume);
			window.draw(Menu);
			window.display();
			window.clear();
		}



	}
	return 0;
}


