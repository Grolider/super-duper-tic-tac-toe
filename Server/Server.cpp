#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <list>

#pragma warning(disable: 4996)

SOCKET newConnection;
int Counter = 1;

//класс соединения для хранения номера соединения и соответствующего сокета
class Connections {
    int index;
    SOCKET Connection;

public:

    void Connections_info(int _index, SOCKET _Connection) {
        index = _index;
        Connection = _Connection;
    }

    int get_index() {
        return index;
    }

    int Recv(char* msg, int len) {
        return recv(Connection, msg, len, NULL);
    }

    int Send(char* msg, int len) {
        return send(Connection, msg, len, NULL);
    }
};

//список для хранения функционирующих соединений
std::list<Connections> ConnectionsList;

//функция для поиска соединения под конкретным номером
std::list<Connections>::iterator Find_Connection(int index) {
    for (std::list<Connections>::iterator element = ConnectionsList.begin(); element != ConnectionsList.end(); element++) {
        int _index = (*element).get_index();
        if (_index == index) {
            return element;
            break;
        }
    }
}

//класс клиента для хранения id клиента, имени и статуса
class Client {
    char name[13];
    int id;
    int status;
    char msg[50] = "";

public:
    ~Client() {

    }

    void Client_info(char* _name, int index, int stat) {
        strcpy(name, _name);
        id = index;
        status = stat;
    }

    char* GetInfo() {
        memset(msg, '\0', 50);
        std::string _id = std::to_string(id);
        strcpy(msg, _id.c_str());
        strncat(msg, " ", 1);
        strncat(msg, name, 10);
        //strncat(msg, " ", 1);
        //_id = std::to_string(status);
        //strcat(msg, _id.c_str());

        return msg;
    }

    int get_status() {
        return status;
    }

    int get_id() {
        return id;
    }

    char* get_name() {
        return name;
    }
};

//список для хранения подключённых клиентов
std::list < Client > ClientsList;

//функция для поиска клиента с конкретным id
std::list<Client>::iterator Find_Client(int index) {
    for (std::list<Client>::iterator element = ClientsList.begin(); element != ClientsList.end(); element++) {
        int _index = (*element).get_id();
        if (_index == index) {
            return element;
            break;
        }
    }
}

//структура для хранения информации о том, что один игрок пригласил другого игрока и ожидает ответа
struct waiting
{
    int waiter;
    int player;

    waiting(int _waiter_id, int _player_id) {
        waiter = _waiter_id;
        player = _player_id;
    }
};

//список для хранения информации о текущих ожиданиях
std::list<waiting> WaitersList;

//структура для хранения информации о том, какие два игрока играют
struct Game {
    int player1;
    int player2;

    Game(int pl1, int pl2) {
        player1 = pl1;
        player2 = pl2;
    }

};

//список для хранения информации о текущих играх
std::list<Game> GamesList;

//класс для хранения имён игроков в текущей игре и функций логики игры
class XO {

    std::string player1, player2, player;
    int len1, len2;
    char key;

public:

    //отрисовка интерфейса
    int _interface(char* grid) {
        std::cout << "\t     " << char(219) << "\t   " << char(219) << std::endl;
        std::cout << "\t  " << grid[1] << "  " << char(219) << "  " << grid[2] << "  " << char(219) << "  " << grid[3] << std::endl;
        std::cout << "\t" << std::string(5, char(220)) << char(219) << std::string(5, char(220)) << char(219) << std::string(5, char(220)) << std::endl;
        std::cout << "\t     " << char(219) << "\t   " << char(219) << "\t" << std::endl;
        std::cout << "\t  " << grid[4] << "  " << char(219) << "  " << grid[5] << "  " << char(219) << "  " << grid[6] << std::endl;
        std::cout << "\t" << std::string(5, char(220)) << char(219) << std::string(5, char(220)) << char(219) << std::string(5, char(220)) << std::endl;
        std::cout << "\t     " << char(219) << "     " << char(219) << "     " << std::endl;
        std::cout << "\t  " << grid[7] << "  " << char(219) << "  " << grid[8] << "  " << char(219) << "  " << grid[9] << std::endl;
        std::cout << "\t     " << char(219) << "\t   " << char(219) << "\t" << std::endl << std::endl;
        return 0;
    }
    //Ввод имен игроков
    void playersnames(char* name1, char* name2) {
        player1 = name1;
        player2 = name2;
        std::cout <<player1<< "(X)  vs  "<<player2 << "(O)" << std::endl;
    }
    int gameplay(char _key, int inputnumb, char* grid) { //ход игры

        if (inputnumb % 2 == 0) { //первый игрок

            switch (_key) {
            case 'a':
                if (grid[1] != 'O' && grid[1] != 'X')       //проверка на случай если если эта ячейка занята
                    grid[1] = 'X';
                else
                    goto def1;
                break;
            case 'b':
                if (grid[2] != 'O' && grid[2] != 'X')
                    grid[2] = 'X';
                else
                    goto def1;
                break;
            case 'c':
                if (grid[3] != 'O' && grid[3] != 'X')
                    grid[3] = 'X';
                else
                    goto def1;
                break;
            case 'd':
                if (grid[4] != 'O' && grid[4] != 'X')
                    grid[4] = 'X';
                else
                    goto def1;
                break;
            case 'e':
                if (grid[5] != 'O' && grid[5] != 'X')
                    grid[5] = 'X';
                else
                    goto def1;
                break;
            case 'f':
                if (grid[6] != 'O' && grid[6] != 'X')
                    grid[6] = 'X';
                else
                    goto def1;
                break;
            case 'g':
                if (grid[7] != 'O' && grid[7] != 'X')
                    grid[7] = 'X';
                else
                    goto def1;
                break;
            case 'h':
                if (grid[8] != 'O' && grid[8] != 'X')
                    grid[8] = 'X';
                else
                    goto def1;
                break;
            case 'i':
                if (grid[9] != 'O' && grid[9] != 'X')
                    grid[9] = 'X';
                else
                    goto def1;
                break;
            def1: default:
                std::cout << "\t   Wrong Move, try again." << std::endl;
                return 0;
            }
            return 1;
        }
        else if (inputnumb % 2 == 1) { //второй игрок
                return -1;
            }
        }
    //Определение победителя
    int whowon(char* grid) {

        if ((grid[1] == grid[2] && grid[1] == grid[3] && grid[2] == grid[3]) ||    //проверка строки
            (grid[4] == grid[5] && grid[4] == grid[6] && grid[5] == grid[6]) ||
            (grid[7] == grid[8] && grid[7] == grid[9] && grid[8] == grid[9]) ||

            (grid[1] == grid[4] && grid[1] == grid[7] && grid[4] == grid[7]) ||  //проверка столбца
            (grid[2] == grid[5] && grid[2] == grid[8] && grid[5] == grid[8]) ||
            (grid[3] == grid[6] && grid[3] == grid[9] && grid[6] == grid[9]) ||

            (grid[1] == grid[5] && grid[1] == grid[9] && grid[5] == grid[9]) ||   //проверка диагоналей
            (grid[3] == grid[5] && grid[3] == grid[7] && grid[5] == grid[7])) {
            return 1;
        }

        else if (grid[1] != 'a' && grid[2] != 'b' && grid[3] != 'c' && grid[4] != 'd' && grid[5] != 'e' && grid[6] != 'f' && grid[7] != 'g' && grid[8] != 'h' && grid[9] != 'i') //тогда ничья
            return -1;
        else
            return 0;
    }

};

//функция изменения статуса игрока с конкретным id
void change_status(int id, int stat) {
    std::list <Client>::iterator a;
    char name1[10];
    int reason_of_delete=0;
    for (std::list <Client>::iterator element = ClientsList.begin(); element != ClientsList.end(); element++)
    {
        if ((*element).get_id() == id) {
            memset(name1, '\0', 10);
            strcpy(name1, (*element).get_name());
            (*element).~Client();
            a = element;
            reason_of_delete = 1;
        }

    }
    if(reason_of_delete==1){
        ClientsList.erase(a);
        Client new_client1;
        new_client1.Client_info(name1, id, stat);
        ClientsList.push_back(new_client1);
    }
}

//функция записи списка первой сотни свободных игроков на сервере для игрока с конкретным id
char* Delivery(int index) {
    char msg[2500] = { 0 };
    int id=0;
    for (Client element : ClientsList)
    {
        if ((element).get_id() == index) {
            continue;
        }
        if(id<101){
            if((element).get_status()==1){
                strcat(msg, (element).GetInfo());
                strcat(msg, "\n");
                id++;
            }
        }
        else {
            break;
        }
    }

    return msg;

}

//функция составления сообщения для игрока с конкретным id о текущем онлайне
void Build_msg(int index, char* msg) {
    memset(msg, '\0', sizeof(msg));
    strcpy(msg, "02");
    strcat(msg, Delivery(index));
    strcat(msg, "\n");
}

//функция оповещения всех свободных игроков, кроме игрока с конкретным id, об изменении списка игроков
void Updates(int index, int iResult) {
    char msg[2500] = { 0 };
    for (Connections element : ConnectionsList)
    {
        if ((element).get_index() == index) {
            continue;
        }
        if (iResult > 0) {
            for (Client client_element : ClientsList)
            {
                if ((client_element).get_id() == (element).get_index() && (client_element.get_status() == 1)) {
                    Build_msg((element).get_index(), msg);
                    (element).Send(msg, sizeof(msg));
                    break;
                }
            }
        }
    }
}


//функция для обмена сообщений между сервером и конкретным клиентом
int ClientHandler(int index) {
    char grid[10] = { '/0','a','b','c','d','e','f','g','h','i' };//поле игрока на сервере
    int inputnumb = 0;//переменная для проверки очерёдности хода игрока
    XO obj;//элемент игровой логики для игрока на сервере
    char key;//переменная для хранения хода игрока

    char name[10];
    char msg[2500] = { 0 };
    int iResult = 1;//переменная для проверки функционирования соединения клиента с сервером
    char code[3] = "";
    char id[5];
    int opponent = 0;//переменная для проверки функционирования соединения противника с сервером
    int reason_of_wait = 0;//переменная для проверки необходимости удаления элемента из списка ожиданий
    int reason_of_exit = 0;//переменная для проверки необходимости удаления элемента из списка игр
    int not_found = 1;//перемекнная для проверки отсутствия искомого элемента в списке клиентов
    std::string _id;//переменная для перевода числовых значений в строковые
    std::list <waiting>::iterator w;//переменная для поиска элемента в списке ожиданий
    std::list <Connections>::iterator c;//переменная для поиска элемента в списке соединений
    std::list <Game>::iterator g;//переменная для поиска элемента в списке игр
    std::list <Client>::iterator a;//переменная для поиска элемента в списке клиентов

    Client new_client;

    int opponent1 = 0;//переменная для проверки функционирования соединения игрока с сервером во время подключения к игре
    int opponent2 = 0;//переменная для проверки функционирования соединения противника с сервером во время подключения к игре

    while (iResult > 0) {
        iResult = (*Find_Connection(index)).Recv(msg, 25);//получение сообщения клиента
        strncpy(code, msg, 2);//определение кода операции
        switch (atoi(code))
        {
        case 1://код регистрации клиента
            strcpy(name, msg + 2);
            new_client.Client_info(name, index, 1);

            Build_msg(index, msg);
            iResult = (*Find_Connection(index)).Send(msg, 2500);

            ClientsList.push_back(new_client);
            std::cout << new_client.GetInfo() << " is registered" << std::endl;

            Updates(index, iResult);

            break;
        case 2://код запроса списка игроков
            Build_msg(index, msg);
            iResult = (*Find_Connection(index)).Send(msg, sizeof(msg));
            break;
        case 3://код приглашения игрока
            opponent = 0;
            strcpy(id, msg + 2);
            if(id[0]!='\0'){
                for (Client client_element : ClientsList)
                {
                    if ((client_element).get_id() != index) {


                        if ((client_element).get_id() == atoi(id) && client_element.get_status() == 1) {

                            memset(msg, '\0', sizeof(msg));
                            strcpy(msg, "13");
                            _id = std::to_string(index);
                            strcat(msg, _id.c_str());
                            opponent = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                            if (opponent <= 0) {
                                not_found = 1;
                            }
                            waiting wait(index, atoi(id));
                            WaitersList.push_back(wait);

                            break;
                        }
                        if ((client_element).get_id() == atoi(id) && client_element.get_status() == 0) {
                            (*Find_Connection(index)).Send(msg, sizeof(msg));
                            memset(id, '\0', 5);
                            not_found = 0;

                            break;
                        }
                        opponent = 0;
                    }
                }
                if (opponent > 0) {
                    change_status(index, 0);
                    change_status(atoi(id), 0);
                    Updates(index, iResult);
                }

                if (opponent <= 0) {
                    if (not_found == 1) {
                        memset(msg, '\0', sizeof(msg));
                        strcpy(msg, "03");
                        strcat(msg, id);
                        (*Find_Connection(index)).Send(msg, sizeof(msg));
                         memset(id, '\0', 5);
                    }
                    not_found = 1;
                }

                for (Client element : ClientsList)
                {
                    std::cout << element.GetInfo();

                }
            }
            

            break;
        case 23://код принятия приглашения 
            strcpy(id, msg + 2);
            memset(msg, '\0', sizeof(msg));
            strcpy(msg, "23");
            _id = std::to_string(index);
            strcat(msg, _id.c_str());

            for (Client client_element : ClientsList)
            {
                if ((client_element).get_id() == atoi(id)) {
                    opponent = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                }
            }
            if (!(WaitersList.empty())) {
                for (std::list <waiting>::iterator element = WaitersList.begin(); element != WaitersList.end(); element++) {
                    if ((*element).player == index) {
                        w = element;
                        reason_of_wait = 1;
                        break;
                    }
                }
                if (reason_of_wait == 1) {
                    WaitersList.erase(w);
                    reason_of_wait = 0;
                }
            }

            std::cout << id << "accepted" << std::endl;
            if (opponent > 0) {
                memset(msg, '\0', sizeof(msg));
                strcpy(msg, "23");
                strcat(msg, id);
                opponent = (*Find_Connection(index)).Send(msg, sizeof(msg));
                if (opponent <= 0) {
                    memset(msg, '\0', sizeof(msg));
                    strcpy(msg, "03");
                    strcat(msg, _id.c_str());
                    opponent = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                    change_status(atoi(id), 1);
                    Updates(atoi(id), iResult);
                }
                else
                {
                    goto start;
                }
            }
            else {
                memset(msg, '\0', sizeof(msg));
                strcpy(msg, "03");
                strcat(msg, id);
                opponent = (*Find_Connection(index)).Send(msg, sizeof(msg));

                change_status(index, 1);
                Updates(index, iResult);
            }
            break;

        case 33://код отказа на предложение
            opponent = 0;
            strcpy(id, msg + 2);
            memset(msg, '\0', sizeof(msg));
            strcpy(msg, "33");
            _id = std::to_string(index);
            strcat(msg, _id.c_str());
            for (Client client_element : ClientsList)
            {
                if ((client_element).get_id() == atoi(id)) {
                    opponent = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                }
            }
            change_status(index, 1);
            if (opponent > 0) {
                change_status(atoi(id), 1);
                opponent = 0;
            }
            for (Connections element : ConnectionsList)
            {
                if ((element).get_index() == index) {
                    Build_msg((element).get_index(), msg);
                    (element).Send(msg, sizeof(msg));
                    continue;
                }
                if (iResult > 0) {
                    for (Client client_element : ClientsList)
                    {
                        if ((client_element).get_id() == (element).get_index() && (client_element.get_status() == 1)) {
                            Build_msg((element).get_index(), msg);
                            (element).Send(msg, sizeof(msg));
                            break;
                        }
                    }
                }
            }

            break;

        start://подключение игроков к игре
            memset(msg, '\0', sizeof(msg));
            strcpy(msg, "04");

            opponent1 = (*Find_Connection(index)).Send(msg, sizeof(msg));

            memset(msg, '\0', sizeof(msg));
            strcpy(msg, "04");

            for (Client client_element : ClientsList)
            {
                if ((client_element).get_id() == atoi(id)) {
                    opponent2 = (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                }
            }

            if (opponent1 > 0 && opponent2 > 0) {
                Game new_game(index, atoi(id));
                GamesList.push_back(new_game);
                opponent1 = 0;
                opponent2 = 0;
            }
            else {
                if (opponent1 > 0) {
                    memset(msg, '\0', sizeof(msg));
                    strcpy(msg, "03");
                    strcat(msg, id);
                    (*Find_Connection(index)).Send(msg, sizeof(msg));
                    change_status(index, 1);
                    Updates(index, iResult);
                    opponent1 = 0;
                }
                if (opponent2 > 0) {
                    memset(msg, '\0', sizeof(msg));
                    strcpy(msg, "03");
                    _id = std::to_string(index);
                    strcat(msg, _id.c_str());
                    (*Find_Connection(atoi(id))).Send(msg, sizeof(msg));
                    change_status(atoi(id), 1);
                    Updates(atoi(id), iResult);
                    opponent2 = 0;
                }
            }
            break;
        case 4://запрос об очерёдности ходов
            if (!(GamesList.empty())) {
                for (std::list <Game>::iterator game_element = GamesList.begin(); game_element != GamesList.end(); game_element++) {
                    if ((*game_element).player1 == index) {
                        if (inputnumb == 0) {
                            obj.playersnames((*Find_Client(index)).get_name(), (*Find_Client((*game_element).player2)).get_name());
                        }
                        memset(msg, '\0', sizeof(msg));
                        strcpy(msg, "14");
                        iResult = (*Find_Connection(index)).Send(msg, sizeof(msg));
                        break;
                    }
                    if ((*game_element).player2 == index) {
                        if (inputnumb == 0) {
                            obj.playersnames((*Find_Client(index)).get_name(), (*Find_Client((*game_element).player1)).get_name());
                        }
                        inputnumb = 1;
                        memset(msg, '\0', sizeof(msg));
                        strcpy(msg, "24");
                        iResult = (*Find_Connection(index)).Send(msg, sizeof(msg));
                        break;
                    }
                }
            }
            break;
        case 44://ход игрока
            key = msg[2];
            if (key != '\0') {
                if (!(GamesList.empty())) {
                    for (std::list <Game>::iterator game_element = GamesList.begin(); game_element != GamesList.end(); game_element++) {
                        if ((*game_element).player1 == index || (*game_element).player2 == index) {
                            switch (obj.gameplay(key, inputnumb, grid)) {
                            case -1:
                                memset(msg, '\0', sizeof(msg));
                                strcpy(msg, "24");
                                (*Find_Connection(index)).Send(msg, sizeof(msg));
                                break;
                            case 0:
                                memset(msg, '\0', sizeof(msg));
                                strcpy(msg, "34");
                                (*Find_Connection(index)).Send(msg, sizeof(msg));
                                break;
                            case 1:
                                if((*game_element).player1 == index){
                                    (*Find_Connection((*game_element).player2)).Send(msg, sizeof(msg));
                                }
                                if ((*game_element).player2 == index) {
                                    (*Find_Connection((*game_element).player1)).Send(msg, sizeof(msg));
                                }
                                memset(msg, '\0', sizeof(msg));
                                strcpy(msg, "05");
                                _id = key;
                                strcat(msg, _id.c_str());
                                (*Find_Connection(index)).Send(msg, sizeof(msg));
                                inputnumb++;
                                break;
                            };
                            switch (obj.whowon(grid)) {
                            case 1:
                                memset(msg, '\0', sizeof(msg));
                                strcpy(msg, "54");
                                (*Find_Connection(index)).Send(msg, sizeof(msg));
                                memset(msg, '\0', sizeof(msg));
                                strcpy(msg, "64");
                                if ((*game_element).player1 == index) {
                                    (*Find_Connection((*game_element).player2)).Send(msg, sizeof(msg));
                                }
                                if ((*game_element).player2 == index) {
                                    (*Find_Connection((*game_element).player1)).Send(msg, sizeof(msg));
                                }

                                reason_of_exit = 1;
                                g = game_element;

                                break;
                            case -1:
                                memset(msg, '\0', sizeof(msg));
                                strcpy(msg, "94");
                                (*Find_Connection(index)).Send(msg, sizeof(msg));
                                if ((*game_element).player1 == index) {
                                    (*Find_Connection((*game_element).player2)).Send(msg, sizeof(msg));
                                }
                                if ((*game_element).player2 == index) {
                                    (*Find_Connection((*game_element).player1)).Send(msg, sizeof(msg));
                                }

                                reason_of_exit = 1;
                                g = game_element;

                                break;
                            case 0:
                                break;
                            }

                            break;
                        }
                    }

                    if (reason_of_exit == 1) {
                        GamesList.erase(g);
                        reason_of_exit = 0;
                    }
                }
            }
            break;
        case 74://код обновления поля игрока после полученного хода аппонента на сервере
            key = msg[2];
            switch (key) {
            case 'a':
                grid[1] = 'O';
                break;
            case 'b':
                grid[2] = 'O';
                break;
            case 'c':
                grid[3] = 'O';
                break;
            case 'd':
                grid[4] = 'O';
                break;
            case 'e':
                grid[5] = 'O';
                break;
            case 'f':
                grid[6] = 'O';
                break;
            case 'g':
                grid[7] = 'O';
                break;
            case 'h':
                grid[8] = 'O';
                break;
            case 'i':
                grid[9] = 'O';
                break;
            }
            if (inputnumb != 0) {
                inputnumb++;
            }
                break;

            case 84://код сообщения об завершении игры и перехода к списку игроков
                for (int i = 1; i < 10; i++)           //очистка значений для повторной игры
                    grid[i] = char(96 + i);
                inputnumb = 0;
                change_status(index, 1);
                Build_msg(index, msg);
                iResult = (*Find_Connection(index)).Send(msg, 2500);
                Updates(index, iResult);
                break;
            default:
                break;


        }
    }
    
    //удаление клиента с конкретным id
    for (std::list <Client>::iterator element = ClientsList.begin(); element != ClientsList.end(); element++) {
        if ((*element).get_id() == index) {
            a = element;
            break;
        }
    }
    ClientsList.erase(a);

    //удаление соединения с конкретным номером и оповещение об изменении других свободных игроков
    int exception = 0;
    for (std::list <Connections>::iterator element = ConnectionsList.begin(); element != ConnectionsList.end(); element++)
    {
        if ((*element).get_index() == index) {
            c = element;
            if (!(WaitersList.empty())) {
                for (std::list <waiting>::iterator wait_element = WaitersList.begin(); wait_element != WaitersList.end(); wait_element++) {
                    if ((*wait_element).player == index) {

                        change_status((*wait_element).waiter, 1);
                        w = wait_element;
                        reason_of_wait = 1;
                        exception = (*wait_element).waiter;
                        break;
                    }
                    if ((*wait_element).waiter == index) {
                        w = wait_element;
                        reason_of_wait = 1;
                        break;
                    }
                }
                if (reason_of_wait == 1) {
                    WaitersList.erase(w);
                    if (exception != 0) {
                        reason_of_wait = 2;
                    }
                    else
                    {
                        reason_of_wait = 0;
                    }
                }

            }
            if (!(GamesList.empty())) {
                for (std::list <Game>::iterator game_element = GamesList.begin(); game_element != GamesList.end(); game_element++) {
                    if ((*game_element).player1 == index) {

                        change_status((*game_element).player2, 1);
                        g = game_element;
                        reason_of_exit = 1;
                        exception = (*game_element).player2;
                        break;
                    }
                    if ((*game_element).player2 == index) {

                        change_status((*game_element).player1, 1);
                        g = game_element;
                        reason_of_exit = 1;
                        exception = (*game_element).player1;
                        break;
                    }
                }
                if (reason_of_exit == 1) {
                    GamesList.erase(g);
                    reason_of_exit = 2;
                }

            }
            continue;
        }

        for (Client client_element : ClientsList)
        {
            if ((client_element).get_id() == (*element).get_index() && (client_element.get_status() == 1)) {
                if ((client_element).get_id() != exception) {
                    Build_msg((*element).get_index(), msg);
                    (*element).Send(msg, sizeof(msg));
                    break;
                }
            }
        }
    }
    ConnectionsList.erase(c);

    //оповещение игрока, находящегося в игре с конкретным игроком либо ожидающий ответа на приглашение 
    if (reason_of_exit == 2 || reason_of_wait == 2) {
        memset(msg, '\0', sizeof(msg));
        strcpy(msg, "03");
        _id = std::to_string(index);
        strcat(msg, _id.c_str());
        for (Client client_element : ClientsList)
        {
            if ((client_element).get_id() == exception) {
                (*Find_Connection(exception)).Send(msg, sizeof(msg));
            }
        }
    }

    //закрытие потока
    GetExitCodeThread;
    return 0;
}


int main()
{
    //создание сервера
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
    {
        std::cout << "Error" << std::endl;
        exit(1);
    }


    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = PF_INET;

    SOCKET sListen = socket(PF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    //подключение клиентов к серверу
    while (true) {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

        if (newConnection == 0) {
            std::cout << "Error 2" << std::endl;
        }
        else {
            Connections NewConnection;
            NewConnection.Connections_info(Counter, newConnection);
            ConnectionsList.push_back(NewConnection);

            std::cout << "Client " << Counter << " Connected\n";
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(Counter), NULL, NULL);
            Counter++;
        }
    }

    system("pause");
    return 0;


}
