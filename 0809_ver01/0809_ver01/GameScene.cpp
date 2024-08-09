#include "GameScene.h"


int GameScene::GameStart()
{
    //
    //    // 초기 세팅
    //    Player* man = new Player("전사", 1000, 100, 20, 10);
    //
    //    vector<Equip*>Player_EqipSlot;
    //    vector<Equip*> Shop;
    //
    //    Shop.push_back(new Equip(1, "브로드소드", 300, 0, 50, 10));
    //    Shop.push_back(new Equip(2, "클레이모어", 500, 0, 80, 10));
    //    Shop.push_back(new Equip(3, "가죽갑옷", 200, 50, 0, 20));
    //    Shop.push_back(new Equip(4, "사슬갑옷", 400, 100, 0, 40));
    //
    //    while (true)
    //    {
    //
    //        // 처음 분기. 
    //        cout << "1. 상점, 2. 인벤  " << endl;
    //        int j;
    //        cin >> j;
    //        switch (j)
    //        {
    //
    //        case 1:
    //
    //            cout << " ============================= " << endl;
    //            cout << " ============================= " << endl;
    //            cout << "     상점에 들어왔습니다." << endl;
    //            cout << " ============================= " << endl;
    //            cout << " ============================= " << endl << endl << endl;
    //            cout << " 장비 아이템 " << endl;
    //            cout << " 1. " << Shop[0]->I_GetName() << "   가격: " << Shop[0]->I_GetPrice() << "  체력: " << Shop[0]->I_GetHp() << " 공격력 : " << Shop[0]->I_GetAtk() << " 방어력 : " << Shop[0]->I_GetDef() << endl;
    //            cout << " 2. " << Shop[1]->I_GetName() << "   가격: " << Shop[1]->I_GetPrice() << "  체력: " << Shop[1]->I_GetHp() << " 공격력 : " << Shop[1]->I_GetAtk() << " 방어력 : " << Shop[1]->I_GetDef() << endl;
    //            cout << " 3. " << Shop[2]->I_GetName() << "   가격: " << Shop[2]->I_GetPrice() << "  체력: " << Shop[2]->I_GetHp() << " 공격력 : " << Shop[2]->I_GetAtk() << " 방어력 : " << Shop[2]->I_GetDef() << endl;
    //            cout << " 4. " << Shop[3]->I_GetName() << "   가격: " << Shop[3]->I_GetPrice() << "  체력: " << Shop[3]->I_GetHp() << " 공격력 : " << Shop[3]->I_GetAtk() << " 방어력 : " << Shop[3]->I_GetDef() << endl;
    //
    //
    //
    //            
    //            while (true)
    //            {
    //                cout << "구매하실 아이템 번호를 입력하세요 " << endl;
    //                int i = 0;
    //                cin >> i;
    //                switch (i)
    //                {
    //                case 1:
    //                    man->BuyItem(*Shop[i - 1]);
    //                    return 1;
    //                case 2:
    //                    man->BuyItem(*Shop[i - 1]);
    //                    return 1;
    //                case 3:
    //                    man->BuyItem(*Shop[i - 1]);
    //                    return 1;
    //                case 4:
    //                    man->BuyItem(*Shop[i - 1]);
    //                    return 1;
    //                case 5:
    //                    break;
    //                default:
    //                    break;
    //                }
    //            }
    //
    //
    //
    //
    //
    //        case 2:
    //        {
    //
    //            man->printInven();
    //            cout << " ============================= " << endl;
    //            cout << "장착할 아이템 이름을 입력하세요" << endl;
    //            string name1;
    //            cin >> name1;
    //            man->addItem(name1);
    //            // man->addAtk();
    //            cout << " ============================= " << endl;
    //            man->PrintInfo_Unit();
    //
    //           
    //            
    //                name1 = '\0';
    //            break;
    //        }
    //
    //        case 3:
    //           
    //            // 장비 장착후 스텟 반영 스텟 출력
    //            //===================
    //            man->addHp();
    //            man->addAtk();
    //            man->addDef();
    //            man->PrintInfo_Unit();
    //            //===================
    //
    //        }
    //
    //        return 0;
    //    }


        // 상점 아이템 세팅
    std::vector<Equip*> Shop =
    {
           new Equip(1, "브로드소드", 300, 0, 50, 10),
           new Equip(2, "클레이모어", 500, 0, 80, 10),
           new Equip(3, "가죽갑옷", 200, 50, 0, 20),
           new Equip(4, "사슬갑옷", 400, 100, 0, 40)
    };

    Player* man = new Player("전사", 1000, 100, 20, 10);
    // 초기 스텟 출력
    man->PrintInfo_Unit();

    while (true) {
        int j = 0;
        std::cout << "1. 상점, 2. 인벤, 3. 스텟 반영 후 출력, 4 아이템 팔기" << std::endl;
        
        std::cin >> j;

        if (j <= 0 || j > 4 )
        {
            std::cout << "잘못된입력입니다." << std::endl;
            std::cin.clear(); // error 플래그 정상으로 돌리기
            // 입력 버퍼 지우기
            while (true)
            {
                // 마지막 값은 항상 엔터일 것이므로
                 if (cin.get() == '\n')
                {
                    break;
                }
            }
            continue;
        }
        switch (j) {
        case 1: {
            while (true) {
                // 상점에서 아이템 목록 출력
                std::cout << " ============================= " << std::endl;
                std::cout << "     상점에 들어왔습니다." << std::endl;
                std::cout << " ============================= " << std::endl << std::endl;
                std::cout << " 장비 아이템 " << std::endl;
                for (int index = 0; index < Shop.size(); ++index) {
                    std::cout << index + 1 << ". " << Shop[index]->I_GetName()
                        << "   가격: " << Shop[index]->I_GetPrice()
                        << "  체력: " << Shop[index]->I_GetHp()
                        << " 공격력: " << Shop[index]->I_GetAtk()
                        << " 방어력: " << Shop[index]->I_GetDef()
                        << std::endl;
                }
                std::cout << " 번호를 입력하여 아이템을 구매하세요 (종료하려면 0): " << std::endl;
                int i;
                std::cin >> i;

                if (i == 0) {
                    break; // 상점 메뉴를 종료하고 루프의 상위로 돌아가기
                }

                if (i >= 1 && i <= Shop.size())
                {
                    if (man->GetGold() < Shop[i - 1]->I_GetPrice())
                    {
                        std::cout << " ============================= " << std::endl;
                        cout << " 돈이 부족합니다. " << endl;
                        std::cout << " ============================= " << std::endl;
                    }
                    man->BuyItem(*Shop[i - 1]);
                }
                else {
                    std::cout << "유효하지 않은 아이템 번호입니다. 다시 입력해 주세요." << std::endl;
                }
            }
            break;
        }

        case 2:
        {
            man->printInven();
            std::cout << " ============================= " << std::endl;
            std::cout << "장착할 아이템 이름을 입력하세요: " << std::endl;
            std::string name1;
            std::cin >> name1;
            man->addItem(name1);
            std::cout << " ============================= " << std::endl;
            // man->PrintInfo_Unit();
            break;
        }

        case 3:
        {
            // 장비 장착 후 스텟출력
            man->addHp();
            man->addAtk();
            man->addDef();
            man->PrintInfo_Unit();
            break;
        }

        case 4:
        {
            man->printInven();
            std::cout << " ============================= " << std::endl;
            std::cout << "판매할 아이템 이름을 입력하세요: " << std::endl;
            std::string name2;
            std::cin >> name2;
            man->SellItem(name2);
            man->printInven();

            break;
        }

        default:
            std::cout << "유효하지 않은 선택입니다. 다시 입력해 주세요." << std::endl;
            break;
        }
    }

        // 동적 메모리 해제
        for (Item* item : Shop)
        {
            delete item;
        }
        delete man;

        return 0;


    
}













