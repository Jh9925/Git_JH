#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>      // sin(), cos()
#include <thread>
#include <fstream>
#include <filesystem>

#include "Player.h"
#include "Enemy.h"
#include "EnemyPool.h"
#include "Projectile.h"
#include "ProjectilePool.h"
#include "Stopwatch.h"
#include "Interface.h"
#include "RankingShow.h"
#include "Bgm.h"


const int WIDTH = 50;       // 게임 화면의 가로 크기
const int HEIGHT = 50;      // 게임 화면의 세로 크기
const int UI_WIDTH = 75;    // UI 영역을 포함한 전체 화면의 가로 크기

///////////////////////////////////////////////////
// 보스스테이지
const int width = 150;  // 콘솔 가로 크기
const int height = 55; // 콘솔 세로 크기
const int UI_width = 175;
const int centerX = width / 2;
const int centerY = height / 2;
///////////////////////////////////////////////////

int shootTimer = 0;         // 총알 발사 타이머
int enemySpawnTimer = 0;    // 적 생성 타이머
int playerShootTimer = 0;   // 플레이어 총알 발사 타이머

int h = 0;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들

void gotoxy(int x, int y);
void setcursor(bool visible, DWORD size);
void setConsoleSize(int width, int height);
void clearScreen();
void clearScreen1(); // 보스 스테이지용

void Scoring(); // 점수 기록

// Player player(WIDTH / 2 - 3, HEIGHT - 5, 5); // 플레이어 초기화 (체력 5)

EnemyPool<EnemyA> enemyPoolA(5);     // 적 최대 5마리
EnemyPool<EnemyB> enemyPoolB(5);     // 적 최대 5마리
EnemyPool<EnemyC> enemyPoolC(5);     // 적 최대 5마리
EnemyPool<Boss>   enemyPoolBoss(1);  // 보스 1 마리 


//일반스테이지 총알 전체 100개
ProjectilePool projectilePool(100);  // 총알 100개
BossStagePlayerProjectilePool BossStagePlayerProjectpool(200); // 보스전 플레이어 총알 200개
BossStagePlayerSkillPool BSPlayerSkillPool(100); // 플레이어 스킬 
AsteroidPool AsteroidPool1(100); // 보스총알

// 키보드 방향키 조작 입력, 플레이어 공격 주기 
// 일반스테이지
void processInput();

// 보스스테이지용
void processInput_BOSS_STAGE();


// 일반 스테이지 게임 상황 업데이트 
void update();

// 일반 스테이지에 필요한 요소 그리기
void draw();

/// ///////////////////////////////////////////////////////////////////////////////////////////
/// ///////////////////////////////////////////////////////////////////////////////////////////
// 보스스테이지 필요한 것들
int BackGround(); // 보스스테이지

// 메인 함수
int main() 
{
    
    CONSOLE_CURSOR_INFO c = { 0 };
    c.dwSize = 1; //두께 : 1
    c.bVisible = 0; //커서 숨기기
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);

    setConsoleSize(UI_WIDTH, HEIGHT + 5);
    srand(time(NULL));
    setcursor(0, 0);
    StartBgm(); // 오프닝곡 시작
    while (true)
    {
        Title();
        int i = 0;
        cin >> i;
        system("cls");
        switch (i)
        {
        case 1:
            StopBgm(); // 오프닝곡 종료
            normalStage(); // 일반스테이지 시작
            while (true)
            {
                

                sw.start(); // 스톱워치

                processInput();
                update();
                draw();
                if (player.score > 5000)// 보스스테이지 입장
                {
                    break;
                }
            }
            clearScreen1();
            gotoxy(75, 30);
            std::cout << " 적 폭격기 출현!!!" << endl;
            StopBgm(); // 노래 종료
            BossStageBgm(); // 보스스테이지
            // 3초대기
            std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // 또는 std::chrono::seconds(3)
            while (true)
            {
                processInput_BOSS_STAGE();
                BackGround();
            }

            break;
        case 3:
            return 0;
        case 2:
            RankingShow();
            // cout << " 메인으로 돌아가기 : 1 입력 " << endl;
            if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
            {
                system("cls");
                break;
            }
            else return 0;
            
        default:
            break;
        }
    }
    return 0;
}

void gotoxy(int x, int y)
{
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(console, coord);
}

void setcursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 50;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    SetConsoleCursorInfo(console, &lpCursor);
}

void setConsoleSize(int width, int height)
{
    SMALL_RECT windowSize = { 0, 0, (SHORT)(width), (SHORT)(height) };
    SetConsoleWindowInfo(console, TRUE, &windowSize);
}

void clearScreen()
{
    gotoxy(0, 0);
    std::cout << std::string(WIDTH + 2, ' ') << std::endl;
    for (int i = 1; i < HEIGHT + 1; ++i)
    {
        gotoxy(0, i);
        std::cout << std::string(UI_width + 100, ' ') << std::endl;
    }
}

void clearScreen1() // 보스 스테이지용
{

    gotoxy(0, 0);
    cout << string(UI_width + 100, ' ') << endl;
    for (int i = 1; i < height; i++)
    {
        gotoxy(0, i);
        cout << string(UI_width + 100, ' ') << endl;
    }
}

// 키보드 방향키 조작 입력, 플레이어 공격 주기 
// 일반스테이지
void processInput()
{
    playerShootTimer++;

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        if (player.x > 1)
            player.x -= 2;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        if (player.x < WIDTH - 8)
            player.x += 2;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        if (player.y > 1)
            player.y -= 1;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        if (player.y < HEIGHT - 3)
            player.y += 1;
    }
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && playerShootTimer >= player.Shooting) // 공속 변경 
    {
        auto p = projectilePool.get();
        if (p)
        {
            p->x = player.x + 5;
            p->y = player.y;
            // 플레이어 데미지 수정 부분
            p->damage = player.GetDamage();

            p->isEnemy = false;
            playerShootTimer = 0;
        }
    }
}

// 보스스테이지용
void processInput_BOSS_STAGE()
{
    playerShootTimer++;

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        if (player.x > 1)
            player.x -= 2;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        if (player.x < 38)// 고정
            player.x += 2;
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        if (player.y > 1)
            player.y -= 1;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        if (player.y < height - 6)
            player.y += 1;
    }
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && playerShootTimer >= player.Shooting) // 공속 변경 
    {
        auto p1 = BossStagePlayerProjectpool.get1();
        if (p1)
        {
            // 플레이어 초기화 다시 필요?
            // 왼쪽 총알
            p1->x1 = player.x;
            p1->y1 = player.y;
            // 오른쪽 총알
            p1->x2 = player.x;
            p1->y2 = player.y;


            // 플레이어 데미지 수정 부분
            p1->damage = player.GetDamage();

            // p1->isEnemy = false;
            playerShootTimer = 0;
        }
    }
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) /*&& playerShootTimer >= player.Shooting*/)  // ctrl 키 감지
    {
        auto ps = BSPlayerSkillPool.get();
        if (ps && player.health > 1)
        {

            // 기체 중앙 레이저
            ps->xs = player.x;
            ps->ys = player.y;

            // 플레이어 데미지 수정 부분
            ps->damage = 10;

            // p1->isEnemy = false;
            playerShootTimer = 0;
            h += 1;
            if (h % 10 == 0)
            {
                player.health -= 1;
            }
        }
    }
}

void update()
{
    // 일반 스테이지
    //////////////////////////////////////////////////////
    // 적 스폰 타이머로 적 스폰
    // 풀에 접근 스폰가능시에만 꺼내서 스폰
    if (player.score <= 5000)
    {

        enemySpawnTimer++;
        if (enemySpawnTimer >= 25)
        {
            int randomSpawn = rand() % 6;
            // 각 적마다 스폰 확률 다르게
            if (randomSpawn == 0 || randomSpawn == 3 || randomSpawn == 5)
            {
                auto e = enemyPoolA.get();
                if (e)
                {
                    e->x = rand() % (WIDTH - 2);
                    e->y = 2;
                }
            }

            if (randomSpawn == 1)
            {
                auto e = enemyPoolB.get();
                if (e)
                {
                    e->x = rand() % (WIDTH - 2);
                    e->y = 2;
                }
            }

            if (randomSpawn == 2 || randomSpawn == 4)
            {
                auto e = enemyPoolC.get();
                if (e)
                {
                    e->x = rand() % (WIDTH - 2);
                    e->y = 2;
                }
            }

            enemySpawnTimer = 0;
        }
    }

    // 풀 업데이트 움직임 반영
    enemyPoolA.update();
    enemyPoolB.update();
    enemyPoolC.update();
    // enemyPoolBoss.update();

    // 총알 업데이트
    projectilePool.update();


    // 적 총알과 플레이어 충돌 처리
    for (auto& p : projectilePool.getAll())
    {
        if (p.active && p.isEnemy && p.x >= player.x && p.x <= player.x + 7 && p.y == player.y)
        {
            player.takeDamage(p.damage);
            p.active = false;
        }
    }


    // 플레이어 총알과 적 충돌 처리
    for (auto& p : projectilePool.getAll())
    {
        // 각 적마다 피격 처리 했고 점수가 다름
        if (p.active && !p.isEnemy)
        {
            for (auto& e : enemyPoolA.getAll())
            {
                if (e.active && p.x >= e.x - 2 && p.x <= e.x + 2 && p.y < e.y + 3)
                {
                    e.takeDamage(p.damage);
                    p.active = false;
                    player.score += 100;
                    player.upgrade();
                }
            }
            for (auto& e : enemyPoolB.getAll())
            {
                if (e.active && p.x >= e.x - 2 && p.x <= e.x + 2 && p.y < e.y + 3)
                {
                    e.takeDamage(p.damage);
                    p.active = false;
                    player.score += 200;
                    player.upgrade();
                }
            }
            for (auto& e : enemyPoolC.getAll())
            {
                if (e.active && p.x >= e.x && p.x <= e.x + 2 && p.y == e.y)
                {
                    e.takeDamage(p.damage);
                    p.active = false;
                    player.score += 150;
                    player.upgrade();
                }
            }
        }
    }

    // 적 총알 발사
    for (auto& e : enemyPoolA.getAll())
    {
        if (e.shouldShoot())
        {
            auto ep = projectilePool.get();
            if (ep)
            {
                ep->x = e.x + 1;
                ep->y = e.y + 1;
                ep->damage = e.damage;
                ep->isEnemy = true;
            }
            e.resetShootTimer();
        }
    }

    for (auto& e : enemyPoolB.getAll())
    {
        if (e.shouldShoot())
        {
            auto ep = projectilePool.get();
            if (ep)
            {
                ep->x = e.x + 1;
                ep->y = e.y + 1;
                ep->damage = e.damage;
                ep->isEnemy = true;
            }
            e.resetShootTimer();
        }
    }

    for (auto& e : enemyPoolC.getAll())
    {
        if (e.shouldShoot())
        {
            auto ep = projectilePool.get();
            if (ep)
            {
                ep->x = e.x + 1;
                ep->y = e.y + 1;
                ep->damage = e.damage;
                ep->isEnemy = true;
            }
            e.resetShootTimer();
        }
    }
}

void draw()
{
    clearScreen();
    setcursor(0, 0);

    /////////////////////////////////////////////////////////////////////////////////////////////
    // 일반스테이지
    gotoxy(0, 0);
    std::cout << "*";
    for (int i = 0; i < WIDTH; i++) std::cout << "-";
    std::cout << "*";
    for (int i = WIDTH + 1; i < UI_WIDTH; i++) std::cout << "-";
    std::cout << "*";

    for (int i = 1; i <= HEIGHT; i++)
    {
        gotoxy(0, i);
        std::cout << "|";
        gotoxy(WIDTH + 1, i);
        std::cout << "|";
        gotoxy(UI_WIDTH, i);
        std::cout << "|";
    }

    gotoxy(0, HEIGHT + 1);
    std::cout << "*";
    for (int i = 0; i < WIDTH; i++) std::cout << "-";
    std::cout << "*";
    for (int i = WIDTH + 1; i < UI_WIDTH; i++) std::cout << "-";
    std::cout << "*";


    ////////////////////////////////////////////////////////////////////////////////////////////
    gotoxy(WIDTH + 2, 5);
    std::cout << "Energy : " << player.health;
    gotoxy(WIDTH + 2, 6);
    for (int i = 0; i < player.health; i++)
    {
        TextColor(10, 0);
        std::cout << "■";
        TextColor(15, 0);
    }

    gotoxy(WIDTH + 2, 10);
    std::cout << "Score : " << player.score;

    gotoxy(WIDTH + 2, 15);
    std::cout << "Damage : " << player.damage;

    gotoxy(WIDTH + 2, 20);
    std::cout << "Time : ";
    gotoxy(WIDTH + 2, 21);
    sw.print_elapsed();


    player.draw();
    enemyPoolA.draw();
    enemyPoolB.draw();
    enemyPoolC.draw();
    // enemyPoolBoss.draw();
    projectilePool.draw();

    Sleep(32);
}

// 보스스테이지 필요한 것들
int BackGround() // 보스스테이지
{
    const int numStars = 40;  // 별의 개수

    float starsX[numStars];
    float starsY[numStars];

    float prevStarsX[numStars];
    float prevStarsY[numStars];
    float speeds[numStars];

    // 별의 초기 위치와 속도 설정
    for (int i = 0; i < numStars; ++i)
    {
        // 각도 랜덤 호도법 굳이? 완벽하게 균일한 별의 방사의 사용
        // float angle = (float)(rand() % 360) * 3.14159f / 180.0f;
        starsX[i] = centerX;
        starsY[i] = centerY;

        prevStarsX[i] = centerX;
        prevStarsY[i] = centerY;
        // 속도 랜덤
        speeds[i] = (float)(rand() % 5 + 1) / 2.0f; // 속도 조정
    }

    // 별의 이동을 계속해서 반복
    while (true)
    {


        clearScreen1();

        /////////////////////////////////////////////////////////////////////////////////////////////
        // 보스스테이지 배경 그리기
        gotoxy(0, 0);
        std::cout << "*";
        for (int i = 0; i < width; i++) std::cout << "-";
        std::cout << "*";
        for (int i = width + 1; i < UI_width; i++) std::cout << "-";
        std::cout << "*";

        for (int i = 1; i <= height; i++)
        {
            gotoxy(0, i);
            std::cout << "|";
            gotoxy(width + 1, i);
            std::cout << "|";
            gotoxy(UI_width + 1, i);
            std::cout << "|";
        }

        gotoxy(0, height + 1);
        std::cout << "*";
        for (int i = 0; i < width; i++) std::cout << "-";
        std::cout << "*";
        for (int i = width + 1; i < UI_width; i++) std::cout << "-";
        std::cout << "*";


        ////////////////////////////////////////////////////////////////////////////////////////////

        for (int i = 0; i < numStars; ++i)
        {
            // 이전 위치 저장
            prevStarsX[i] = starsX[i];
            prevStarsY[i] = starsY[i];

            // 각 별의 위치를 업데이트 (방향 유지)
            // cos(), sin()안에 각도는 라디안이다. 
            starsX[i] += cos(i) * speeds[i];
            starsY[i] += sin(i) * speeds[i];

            // 잔상을 위해 이전 위치에 점을 찍는다
            if (prevStarsX[i] >= 0 && prevStarsX[i] < width && prevStarsY[i] >= 0 && prevStarsY[i] < height)
            {
                gotoxy((int)prevStarsX[i], (int)prevStarsY[i]);
                std::cout << ".";
            }

            // 현재 별의 위치에 별을 그린다
            if (starsX[i] >= 0 && starsX[i] < width && starsY[i] >= 0 && starsY[i] < height)
            {
                gotoxy((int)starsX[i], (int)starsY[i]);
                std::cout << "*";
            }

            else
            {
                // 별이 화면 밖으로 나가면 다시 중앙에서 시작
                starsX[i] = centerX;
                starsY[i] = centerY;
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // 플레이어 기본공격 보스 피격
        for (auto& p : BossStagePlayerProjectpool.getAll())
        {
            for (auto& e : enemyPoolBoss.getAll())
            {
                if (e.active && p.active1)
                {
                    // 보스 피격
                    // 왼쪽 블라스트
                    if (p.x1 * 3 + 1 >= e.x * 3 && p.x1 * 3 + 1 <= e.x * 3 + 20 && p.y1 < e.y + 5) // 버그다 버그 ++해결!
                    {
                        // cout << "!@#!@#@!#!@#!" << endl;
                        e.takeDamage(p.damage);
                        p.active1 = false;
                        player.score += 100;

                        //player.upgrade();
                    }
                    // 오른쪽 블라스트
                    if (p.x2 * 3 + 35 >= e.x * 3 && p.x2 * 3 + 35 <= e.x * 3 + 20 && p.y1 < e.y + 10)
                    {
                        e.takeDamage(p.damage);
                        p.active1 = false;
                        player.score += 100;
                        //player.upgrade();
                    }
                }
            }
        }

        // 플레이어 스킬 보스 피격 
        // 플레이어 스킬 플레이어 에너지소모

        for (auto& p : BSPlayerSkillPool.getAll())
        {
            for (auto& e : enemyPoolBoss.getAll())
            {
                if (e.active && p.active_s && player.health > 1)
                {
                    if (p.xs * 3 + 17 >= e.x * 3 && p.xs * 3 + 17 <= e.x * 3 + 35 && p.ys < e.y + 5)
                    {
                        e.takeDamage(p.damage);
                        p.active_s = false;
                        player.score += 2000;
                    }

                }
            }
        }

        // 보스 총알 발사
        for (auto& e : enemyPoolBoss.getAll())
        {
            if (e.shouldShoot())
            {
                auto ep = AsteroidPool1.get();
                if (ep)
                {
                    ep->b_x = e.x * 3 + 13 + rand() % 10;
                    ep->b_y = e.y + 14;
                    ep->damage = 1;
                    // ep->isEnemy = true;
                    ep->trackPlayer(player.x, player.y); // 플레이어를 추적하도록 설정
                }
                e.resetShootTimer();
            }
        }


        // 보스 총알 발사 업데이트
        AsteroidPool1.draw();
        AsteroidPool1.update();


        // 보스 총알과 플레이어 충돌 처리
        for (auto& p : AsteroidPool1.getAll())
        {
            if (p.active && p.b_x >= player.x * 3.f + 5.f && p.b_x <= player.x * 3.f + 30.f && p.b_y > player.y - 1 && p.b_y < player.y + 3)
            {
                player.takeDamage(p.damage);
                p.active = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // UI
        gotoxy(width + 2, 5);
        std::cout << "Energy : " << player.health;
        for (int i = 0; i < player.health; i++)
        {
            gotoxy(width + 2+(i*2), 6);
            TextColor(10, 10);
            std::cout << "  ";
            TextColor(15, 0);
        }

        gotoxy(width + 2, 10);
        std::cout << "Score : " << player.score;

        gotoxy(width + 2, 15);
        std::cout << "Damage : " << "5";

        /*gotoxy(width + 2, 17);
        std::cout << "player x,y : " << player.x << player.y;*/
        /*gotoxy(width + 2, 18);
        for (auto& e : enemyPoolBoss.getAll())
        {
            std::cout << "보스 x,y : " << h;
        }*/

        gotoxy(width + 2, 20);
        std::cout << "Time : ";
        gotoxy(width + 2, 21);
        sw.print_elapsed();

        gotoxy(width + 2, 22);
        for (auto& e : enemyPoolBoss.getAll())
        {
            std::cout << "Boss : " << e.health;
            if (e.health <= 0)
            {
                sw.stop();
                system("cls");
                gotoxy(0, 15);
                Conpleted();
                Scoring();
                
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                exit(0);
            }
        }
        // 보스체력 그래픽
        gotoxy(width + 2, 23);
        for (auto& e : enemyPoolBoss.getAll())
        {

            for (int i = 0; i < e.health / 300; i++)
            {
                TextColor(4, 4);
                std::cout << "■";
                TextColor(15, 0);
            }
            TextColor(15, 0);
        }

        // 플레이어
        player.BossStagePlayerDraw();
        // 보스
        enemyPoolBoss.draw();

        if (true)
        {
            auto e = enemyPoolBoss.get();
            if (e)
            {
                e->x = 25;
                e->y = 2;
            }
        }

        // 총알 수정차례
        // projectilePool.draw(); 

        /////////////////////////////////////////////
        // 보스스테이지 플레이어 조작
        processInput_BOSS_STAGE();

        // 플레이어 스킬추가
        if (player.health > 1)
        {
            BSPlayerSkillPool.draw();
            BSPlayerSkillPool.update();
        }

        // 보스 움직임
        enemyPoolBoss.update();
        // 플레이어 총알 추가
        BossStagePlayerProjectpool.update();
        BossStagePlayerProjectpool.draw();

        Sleep(16);  // 애니메이션 속도 조절
    }
}

// 점수기록 함수
void Scoring() 
{
    std::string name;
    int Score = player.score;
    StopBgm(); // 노래 종료

    // 콘솔에 이름 입력 요청
    gotoxy(0, 32);
    TextColor(2, 0);
    cout << "                                                                                                                                  ____________________________________________________________________________ " << endl;
    cout << "                                                                                                                                  %=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x% " << endl;
    cout << "                                                                                                                                  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
    cout << "                                                                                                                                                                                                               " << endl;
    cout << "                                                                                                                                                                                T - 65B  Mission Completed     " << endl;
    cout << "                                                                                                                                                                             --------------------------------- " << endl;
    cout << "                                                                                                                                                                                        (Rebel Alliance)       " << endl;
    cout << "                                                                                                                                                                                                               " << endl;
    cout << "                                                                                                                                     Name : ";
    cin >> name;
    cout << "                                                                                                                                                                                                               " << endl;
    cout << "                                                                                                                                     Time :     ";
    sw.print_elapsed();
    cout << endl;
    cout << "                                                                                                                                     Score :    " << player.score << endl;
    cout << "                                                                                                                                                                                                               " << endl;
    
    gotoxy(0, 46);
    cout << "                                                                                                                                  ____________________________________________________________________________ " << endl;
    cout << "                                                                                                                                  %=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x% " << endl;
    cout << "                                                                                                                                  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;

    
    // 디렉토리 생성 (이미 존재해도 에러 발생하지 않음)
    std::filesystem::create_directory("Save");

    // 파일 열기 또는 생성
    std::ofstream ofs("Save/ranking.rnk", std::ios::app);
    if (!ofs) 
    {
        ofs.open("Save/ranking.rnk", std::ios::out);
    }

    // 파일에 이름과 시간을 기록
    ofs << name << " " << Score << std::endl;

    // 파일 닫기
    ofs.close();

    // 저장 완료 메시지
    gotoxy(190, 45);
    std::cout << "Save Completed!" << std::endl;
    TextColor(15, 0);
}