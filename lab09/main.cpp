#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

const char NO_LETTERS[] = "ABCETOPHKM";

class Bus
{
private:
    char busNo[12];
    char driverName[255];
    unsigned routeNo;

public:
    Bus();

    Bus(const char *no, const char *driver, unsigned route);

    const char *GetBusNo() const
    {
        return busNo;
    }

    const char *GetDriverName() const
    {
        return driverName;
    }

    unsigned GetRouteNo() const
    {
        return routeNo;
    }

    void SetBusNo(const char *no)
    {
        strncpy(busNo, no, sizeof(busNo) - 1);
        busNo[sizeof(busNo) - 1] = '\0';
    }

    void SetDriverName(const char *driver)
    {
        strncpy(driverName, driver, sizeof(driverName) - 1);
        driverName[sizeof(driverName) - 1] = '\0';
    }

    void SetRouteNo(unsigned routeNo)
    {
        this->routeNo = routeNo;
    }

    void FillRandomData();

    void Show() const;

    void Input();

    void SaveToFile(ofstream &fout) const;
};

void Bus::FillRandomData()
{
    snprintf(
        busNo,
        sizeof(busNo),
        "%c%d%c%c%d",
        NO_LETTERS[rand() % 10],
        rand() % 900 + 100,
        NO_LETTERS[rand() % 10],
        NO_LETTERS[rand() % 10],
        rand() % 99 + 1
    );

    snprintf(
        driverName,
        sizeof(driverName),
        "ВодительФИО_%d",
        rand() % 1000
    );

    routeNo = rand() % 100 + 1;
}

Bus::Bus()
{
    FillRandomData();
}

Bus::Bus(const char *no, const char *driver, unsigned route)
{
    SetBusNo(no);
    SetDriverName(driver);
    SetRouteNo(route);
}

void Bus::Show() const
{
    cout << "Номер автобуса: " << busNo << endl;
    cout << "Водитель: " << driverName << endl;
    cout << "Маршрут: " << routeNo << endl;
}

void Bus::Input()
{
    cout << "Введите номер автобуса: ";
    cin >> busNo;

    cin.ignore();

    cout << "Введите ФИО водителя: ";
    cin.getline(driverName, 255);

    cout << "Введите номер маршрута: ";
    cin >> routeNo;
}

void Bus::SaveToFile(ofstream &fout) const
{
    fout << busNo << ";"
         << driverName << ";"
         << routeNo << endl;
}

/*
Узел списка
*/

class BusNode
{
public:
    Bus data;
    BusNode *next;

    BusNode(Bus bus)
    {
        data = bus;
        next = NULL;
    }
};

/*
Связный список автобусов
*/

class BusList
{
private:
    BusNode *head;

public:
    BusList();

    ~BusList();

    void Add(Bus bus);

    void Show() const;

    int RemoveByBusNo(const char *busNo, Bus &removedBus);

    Bus *Find(const char *busNo);

    void FillRandom(unsigned count);

    void SaveToFile(const char *filename) const;

    void LoadFromFile(const char *filename);

    void SortByDriver();
};

BusList::BusList()
{
    head = NULL;
}

BusList::~BusList()
{
    BusNode *current = head;

    while (current != NULL) {
        BusNode *temp = current;
        current = current->next;
        delete temp;
    }
}

void BusList::Add(Bus bus)
{
    BusNode *newNode = new BusNode(bus);

    if (head == NULL) {
        head = newNode;
        return;
    }

    BusNode *current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

void BusList::Show() const
{
    if (head == NULL) {
        cout << "Список пуст" << endl;
        return;
    }

    BusNode *current = head;
    int index = 1;

    while (current != NULL) {
        cout << "Автобус #" << index << endl;
        current->data.Show();
        cout << endl;

        current = current->next;
        index++;
    }
}

int BusList::RemoveByBusNo(const char *busNo, Bus &removedBus)
{
    if (head == NULL) {
        return 0;
    }

    if (strcmp(head->data.GetBusNo(), busNo) == 0) {
        BusNode *temp = head;

        removedBus = head->data;

        head = head->next;

        delete temp;

        return 1;
    }

    BusNode *current = head;

    while (current->next != NULL) {
        if (strcmp(current->next->data.GetBusNo(), busNo) == 0) {
            BusNode *temp = current->next;

            removedBus = temp->data;

            current->next = temp->next;

            delete temp;

            return 1;
        }

        current = current->next;
    }

    return 0;
}

Bus *BusList::Find(const char *busNo)
{
    BusNode *current = head;

    while (current != NULL) {
        if (strcmp(current->data.GetBusNo(), busNo) == 0) {
            return &current->data;
        }

        current = current->next;
    }

    return NULL;
}

void BusList::FillRandom(unsigned count)
{
    for (unsigned i = 0; i < count; i++) {
        Bus bus;
        Add(bus);
    }
}

void BusList::SaveToFile(const char *filename) const
{
    ofstream fout(filename);

    if (!fout) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    BusNode *current = head;

    while (current != NULL) {
        current->data.SaveToFile(fout);
        current = current->next;
    }

    fout.close();
}

void BusList::LoadFromFile(const char *filename)
{
    ifstream fin(filename);

    if (!fin) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    char no[12];
    char driver[255];
    unsigned route;

    while (
        fin.getline(no, 12, ';') &&
        fin.getline(driver, 255, ';') &&
        fin >> route
    ) {
        fin.ignore();

        Bus bus(no, driver, route);

        Add(bus);
    }

    fin.close();
}

void BusList::SortByDriver()
{
    if (head == NULL) {
        return;
    }

    for (BusNode *i = head; i != NULL; i = i->next)
    {
        BusNode *min = i;

        for (BusNode *j = i->next; j != NULL; j = j->next) {
            if (strcmp(j->data.GetDriverName(), min->data.GetDriverName()) < 0) {
                min = j;
            }
        }

        if (min != i) {
            Bus temp = i->data;
            i->data = min->data;
            min->data = temp;
        }
    }
}

/*
Автобусный парк
*/

class BusPark
{
private:
    BusList parkBuses;
    BusList routeBuses;

public:
    void FillRandom(unsigned count);

    void ShowParkBuses() const;

    void ShowRouteBuses() const;

    void BusGoToRoute(const char *busNo);

    void BusComeToPark(const char *busNo);

    void SaveAll();
};

void BusPark::FillRandom(unsigned count)
{
    parkBuses.FillRandom(count);
}

void BusPark::ShowParkBuses() const
{
    cout << endl;
    cout << "Автобусы в парке:" << endl;
    cout << "========================" << endl;

    parkBuses.Show();
}

void BusPark::ShowRouteBuses() const
{
    cout << endl;
    cout << "Автобусы на маршруте:" << endl;
    cout << "========================" << endl;

    routeBuses.Show();
}

void BusPark::BusGoToRoute(const char *busNo)
{
    Bus movedBus;

    if (parkBuses.RemoveByBusNo(busNo, movedBus))
    {
        routeBuses.Add(movedBus);

        cout << "Автобус " << busNo << " выехал на маршрут" << endl;
    }
    else
    {
        cout << "Автобус не найден в парке" << endl;
    }
}

void BusPark::BusComeToPark(const char *busNo)
{
    Bus movedBus;

    if (routeBuses.RemoveByBusNo(busNo, movedBus))
    {
        parkBuses.Add(movedBus);

        cout << "Автобус " << busNo << " вернулся в парк" << endl;
    }
    else
    {
        cout << "Автобус не найден на маршруте" << endl;
    }
}

void BusPark::SaveAll()
{
    parkBuses.SaveToFile("park_buses.txt");
    routeBuses.SaveToFile("route_buses.txt");
}

int main()
{
    srand(time(NULL));

    BusPark park;

    park.FillRandom(5);

    park.ShowParkBuses();

    char busNo[12];

    cout << endl;
    cout << "Введите номер автобуса для выезда на маршрут: ";
    cin >> busNo;

    park.BusGoToRoute(busNo);

    park.ShowParkBuses();
    park.ShowRouteBuses();

    cout << endl;
    cout << "Введите номер автобуса для возврата в парк: ";
    cin >> busNo;

    park.BusComeToPark(busNo);

    park.ShowParkBuses();
    park.ShowRouteBuses();

    park.SaveAll();

    return 0;
}
