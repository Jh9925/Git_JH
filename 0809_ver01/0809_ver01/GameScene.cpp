#include "GameScene.h"


int GameScene::GameStart()
{
    //
    //    // �ʱ� ����
    //    Player* man = new Player("����", 1000, 100, 20, 10);
    //
    //    vector<Equip*>Player_EqipSlot;
    //    vector<Equip*> Shop;
    //
    //    Shop.push_back(new Equip(1, "��ε�ҵ�", 300, 0, 50, 10));
    //    Shop.push_back(new Equip(2, "Ŭ���̸��", 500, 0, 80, 10));
    //    Shop.push_back(new Equip(3, "���װ���", 200, 50, 0, 20));
    //    Shop.push_back(new Equip(4, "�罽����", 400, 100, 0, 40));
    //
    //    while (true)
    //    {
    //
    //        // ó�� �б�. 
    //        cout << "1. ����, 2. �κ�  " << endl;
    //        int j;
    //        cin >> j;
    //        switch (j)
    //        {
    //
    //        case 1:
    //
    //            cout << " ============================= " << endl;
    //            cout << " ============================= " << endl;
    //            cout << "     ������ ���Խ��ϴ�." << endl;
    //            cout << " ============================= " << endl;
    //            cout << " ============================= " << endl << endl << endl;
    //            cout << " ��� ������ " << endl;
    //            cout << " 1. " << Shop[0]->I_GetName() << "   ����: " << Shop[0]->I_GetPrice() << "  ü��: " << Shop[0]->I_GetHp() << " ���ݷ� : " << Shop[0]->I_GetAtk() << " ���� : " << Shop[0]->I_GetDef() << endl;
    //            cout << " 2. " << Shop[1]->I_GetName() << "   ����: " << Shop[1]->I_GetPrice() << "  ü��: " << Shop[1]->I_GetHp() << " ���ݷ� : " << Shop[1]->I_GetAtk() << " ���� : " << Shop[1]->I_GetDef() << endl;
    //            cout << " 3. " << Shop[2]->I_GetName() << "   ����: " << Shop[2]->I_GetPrice() << "  ü��: " << Shop[2]->I_GetHp() << " ���ݷ� : " << Shop[2]->I_GetAtk() << " ���� : " << Shop[2]->I_GetDef() << endl;
    //            cout << " 4. " << Shop[3]->I_GetName() << "   ����: " << Shop[3]->I_GetPrice() << "  ü��: " << Shop[3]->I_GetHp() << " ���ݷ� : " << Shop[3]->I_GetAtk() << " ���� : " << Shop[3]->I_GetDef() << endl;
    //
    //
    //
    //            
    //            while (true)
    //            {
    //                cout << "�����Ͻ� ������ ��ȣ�� �Է��ϼ��� " << endl;
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
    //            cout << "������ ������ �̸��� �Է��ϼ���" << endl;
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
    //            // ��� ������ ���� �ݿ� ���� ���
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


        // ���� ������ ����
    std::vector<Equip*> Shop =
    {
           new Equip(1, "��ε�ҵ�", 300, 0, 50, 10),
           new Equip(2, "Ŭ���̸��", 500, 0, 80, 10),
           new Equip(3, "���װ���", 200, 50, 0, 20),
           new Equip(4, "�罽����", 400, 100, 0, 40)
    };

    Player* man = new Player("����", 1000, 100, 20, 10);
    // �ʱ� ���� ���
    man->PrintInfo_Unit();

    while (true) {
        int j = 0;
        std::cout << "1. ����, 2. �κ�, 3. ���� �ݿ� �� ���, 4 ������ �ȱ�" << std::endl;
        
        std::cin >> j;

        if (j <= 0 || j > 4 )
        {
            std::cout << "�߸����Է��Դϴ�." << std::endl;
            std::cin.clear(); // error �÷��� �������� ������
            // �Է� ���� �����
            while (true)
            {
                // ������ ���� �׻� ������ ���̹Ƿ�
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
                // �������� ������ ��� ���
                std::cout << " ============================= " << std::endl;
                std::cout << "     ������ ���Խ��ϴ�." << std::endl;
                std::cout << " ============================= " << std::endl << std::endl;
                std::cout << " ��� ������ " << std::endl;
                for (int index = 0; index < Shop.size(); ++index) {
                    std::cout << index + 1 << ". " << Shop[index]->I_GetName()
                        << "   ����: " << Shop[index]->I_GetPrice()
                        << "  ü��: " << Shop[index]->I_GetHp()
                        << " ���ݷ�: " << Shop[index]->I_GetAtk()
                        << " ����: " << Shop[index]->I_GetDef()
                        << std::endl;
                }
                std::cout << " ��ȣ�� �Է��Ͽ� �������� �����ϼ��� (�����Ϸ��� 0): " << std::endl;
                int i;
                std::cin >> i;

                if (i == 0) {
                    break; // ���� �޴��� �����ϰ� ������ ������ ���ư���
                }

                if (i >= 1 && i <= Shop.size())
                {
                    if (man->GetGold() < Shop[i - 1]->I_GetPrice())
                    {
                        std::cout << " ============================= " << std::endl;
                        cout << " ���� �����մϴ�. " << endl;
                        std::cout << " ============================= " << std::endl;
                    }
                    man->BuyItem(*Shop[i - 1]);
                }
                else {
                    std::cout << "��ȿ���� ���� ������ ��ȣ�Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
                }
            }
            break;
        }

        case 2:
        {
            man->printInven();
            std::cout << " ============================= " << std::endl;
            std::cout << "������ ������ �̸��� �Է��ϼ���: " << std::endl;
            std::string name1;
            std::cin >> name1;
            man->addItem(name1);
            std::cout << " ============================= " << std::endl;
            // man->PrintInfo_Unit();
            break;
        }

        case 3:
        {
            // ��� ���� �� �������
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
            std::cout << "�Ǹ��� ������ �̸��� �Է��ϼ���: " << std::endl;
            std::string name2;
            std::cin >> name2;
            man->SellItem(name2);
            man->printInven();

            break;
        }

        default:
            std::cout << "��ȿ���� ���� �����Դϴ�. �ٽ� �Է��� �ּ���." << std::endl;
            break;
        }
    }

        // ���� �޸� ����
        for (Item* item : Shop)
        {
            delete item;
        }
        delete man;

        return 0;


    
}













