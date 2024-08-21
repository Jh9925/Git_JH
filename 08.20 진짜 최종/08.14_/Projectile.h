#pragma once
#include <iostream>
#include <windows.h>
#include "Player.h"

void TextColor(int font, int backGround)
{
    int Color = font + backGround * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);

}


extern const int HEIGHT;

Player player(WIDTH / 2 - 3, HEIGHT - 5, 10); // 플레이어 초기화 (체력 10)

class Projectile 
{
public:
    int x, y;          // 총알의 좌표
    int damage;        // 총알의 피해량
    bool isEnemy;      // 적의 총알인지 여부
    bool active;       // 총알의 활성화 여부

    void update() 
    {
        if (active) 
        {
            y += (isEnemy ? 1 : -1);  // 적의 총알은 아래로, 플레이어의 총알은 위로 이동
            if (y < 0 || y >= HEIGHT) 
            {
                active = false;  // 화면 밖으로 나가면 비활성화
            }
        }
    }

    void draw() 
    {
        if (active)
        {
            gotoxy(x, y);
            if (isEnemy)
            {
                TextColor(3, 0);
                std::cout << "*";
                TextColor(15, 0);
            }
            else
            {
                TextColor(4, 0);
                std::cout << player.GetBulShape();
                TextColor(15, 0);
            }
           
        }
    }


};

class BossStagePlayerProjectile
{
public:
    int x1, y1;          // 왼쪽 총알의 좌표
    int x2, y2;          // 오른쪽 총알의 좌표
    int damage;        // 총알의 피해량
    // bool isEnemy;      // 적의 총알인지 여부
    bool active1 = true;       // 총알의 활성화 여부



    void update()
    {
        if (active1)
        {
            damage = 5;
            y1 -= 4;  // 플레이어의 총알은 위로 이동, y가 3줄을때마다 화면 중심기준 좌측은 +1 우픅은 -1
            y2 -= 4;
             // 총알이 휘는거
            int c = 0;
            c++;
            if (c % 5 == 1)
            {
                if (x1*3 < 55) x1+=2;
                if (x2 * 3 < 55) x2++;
                if (x1 * 3 > 55) x1-=1;
                if (x2 * 3 > 55) x2 -= 2;
            }
            
            
            if (y1 < 1)
            {
                active1 = false;  // 화면 밖으로 나가면 비활성화
            }
            if (y2 < 1)
            {
                active1 = false;  // 화면 밖으로 나가면 비활성화
            }
        }
    }

    void draw()
    {
        if (active1)
        {
            gotoxy(x1*3+1, y1);
            TextColor(4, 0);
            std::cout << "↑";  // 총알의 시각적 표현
            gotoxy(x1 * 3 + 1, y1+1);
            std::cout << "||";
            TextColor(15, 0);

            gotoxy(x2*3+35, y2);
            TextColor(4, 0);
            std::cout << "↑";
            gotoxy(x2 * 3 + 35, y2+1);
            std::cout << "||";
            TextColor(15, 0);
        }  
    }


};


class BossStagePlayerSkill
{
public:
    int xs, ys;          // 왼쪽 총알의 좌표
   
    int damage;        // 총알의 피해량
    // bool isEnemy;      // 적의 총알인지 여부
    bool active_s = true;       // 총알의 활성화 여부



    void update()
    {
        if (active_s)
        {
            damage = 50;
            ys -= 4;  // 플레이어의 총알은 위로 이동
        }

        if (ys < 0)
        {
            active_s = false;  // 화면 밖으로 나가면 비활성화
        }
    }

    void draw()
    {
        if (active_s)
        {
            int beamLength = 40;  // 빔의 길이 설정
            TextColor(0, 10);

            for (int i = 0; i < beamLength; ++i)
            {
                int beamY = ys - i;  // 빔이 위로 향하게
                if (beamY >= 0)  // 화면을 벗어나지 않도록
                {
                    gotoxy(xs * 3 + 17, beamY);
                    std::cout << "  ";
                }
            }

            TextColor(15, 0);  // 원래 색상으로 복원
        }
    }
};

//  보스총알로 변경
class Asteroid
{
public:
    float b_x, b_y;          // 총알의 좌표
    int damage;        // 총알의 피해량
    float dx, dy;    // 이동할 방향 벡터
    bool active;       // 총알의 활성화 여부


    void trackPlayer(int playerX, int playerY)
    {
        // 플레이어와의 거리 계산
        float deltaX = (playerX*3+18)  - b_x;
        float deltaY = playerY - b_y;
        float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

        // 방향 벡터 계산 및 정규화
        dx = deltaX / distance;
        dy = deltaY / distance;
    }


    void update()
    {
        if (active)
        {
            b_x += dx;
            b_y += dy;

            // b_y += 1;  // 적의 총알은 아래로, 플레이어의 총알은 위로 이동
            if (b_y < 10 || b_y >= HEIGHT || b_x < 1 || b_x >= 170)
            {
                active = false;  // 화면 밖으로 나가면 비활성화
            }
        }
    }

    void draw()
    {
        if (active)
        {
            if (b_y < 25)
            {
                gotoxy(b_x, b_y);
                cout << "↓" << endl;
               
            }

            if (b_y >= 25 && b_y < 50)
            {
               TextColor(13, 0);
               gotoxy(b_x, b_y);
               cout << "∨"<< endl;
               
               gotoxy(b_x, b_y+1);
               cout << "││" << endl;
               gotoxy(b_x, b_y+2);
               cout << "∀" << endl;
               TextColor(15, 0);
              
            }

        }
    }

};