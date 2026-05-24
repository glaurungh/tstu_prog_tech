#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>


using namespace std;

/*
Сведения о каждом автобусе содержат:
- номер автобуса;
- фамилию и инициалы водителя;
- номер маршрута.
*/

const char NO_LETTERS[] = {'A', 'B', 'C', 'E', 'T', 'O', 'P', 'H', 'K', 'M'};


class Bus {
private:
    char busNo[12];
    char driverName[255];
    unsigned routeNo;
public:
    Bus();
    Bus(const char * no, const char * driver, unsigned route);
    char * GetBusNo()
    {
        return busNo;
    }
    void SetBusNo(const char * no) {
        strncpy(busNo, no, 11);
        busNo[11] = '\0';
    }
    char * GetDriverName()
    {
        return driverName;
    }
    void SetDriverName(const char * driver) {
        strncpy(driverName, driver, 254);
        driverName[254] = '\0';
    }
    unsigned GetRouteNo()
    {
        return routeNo;
    }
    void SetRouteNo(unsigned routeNo) {
        this->routeNo = routeNo;
    }
    void FillRandomData();
    void Show();
    void Input();
    void SaveToFile(ofstream &fout);
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
    this->FillRandomData();
}

Bus::Bus(const char * no, const char * driver, unsigned route)
{
    strncpy(busNo, no, 11);
    busNo[11] = '\0';

    strncpy(driverName, driver, 254);
    driverName[254] = '\0';

    routeNo = route;
}

void Bus::Show()
{
    cout << "Информация об автобусе:" << endl;
    cout << "Номер: " << busNo << endl;
    cout << "Водитель: " << driverName << endl;
    cout << "Маршрут: " << routeNo << endl;
}

void Bus::Input()
{
    cin >> busNo;
    cin.ignore();

    cin.getline(driverName, 255);

    cin >> routeNo;
}

void Bus::SaveToFile(ofstream &fout)
{
    fout << busNo << ";"
         << driverName << ";"
         << routeNo << endl;
}

class BusPark
{
private:
    Bus *buses;
    unsigned count;
    unsigned maxCount;

public:
    BusPark(unsigned size = 100);

    ~BusPark();

    void FillRandom(unsigned n);

    void Show();

    void AddBus(Bus b);

    void SaveToFile(const char *filename);

    void LoadFromFile(const char *filename);

    void SortByDriver();

    int SearchByRoute(unsigned route);
};


BusPark::BusPark(unsigned size)
{
    maxCount = size;
    count = 0;

    buses = new Bus[maxCount];
}

void BusPark::FillRandom(unsigned n)
{
    if (n > maxCount)
        n = maxCount;

    for (unsigned i = 0; i < n; i++)
    {
        buses[i].FillRandomData();
    }

    count = n;
}


BusPark::~BusPark()
{
    delete[] buses;
}

void BusPark::Show()
{
    for (unsigned i = 0; i < count; i++)
    {
        cout << "Автобус #" << i + 1 << endl;
        buses[i].Show();
    }
}

void BusPark::AddBus(Bus b)
{
    if (count >= maxCount)
        return;

    buses[count] = b;
    count++;
}

void BusPark::SaveToFile(const char *filename)
{
    ofstream fout(filename);

    for (unsigned i = 0; i < count; i++)
    {
        buses[i].SaveToFile(fout);
    }

    fout.close();
}

void BusPark::LoadFromFile(const char *filename)
{
    ifstream fin(filename);

    if (!fin)
        return;

    char no[12];
    char driver[255];
    unsigned route;

    count = 0;

    while (
        fin.getline(no, 12, ';') &&
        fin.getline(driver, 255, ';') &&
        fin >> route
    )
    {
        fin.ignore();
        buses[count] = Bus(no, driver, route);
        count++;
        if (count >= maxCount)
            break;
    }

    fin.close();
}

void BusPark::SortByDriver()
{
    for (unsigned i = 0; i < count - 1; i++)
    {
        unsigned min = i;
        for (unsigned j = i + 1; j < count; j++)
        {
            if (
                strcmp(
                    buses[j].GetDriverName(),
                    buses[min].GetDriverName()
                ) < 0
            )
            {
                min = j;
            }
        }

        if (min != i)
        {
            Bus temp = buses[i];
            buses[i] = buses[min];
            buses[min] = temp;
        }
    }
}

int BusPark::SearchByRoute(unsigned route)
{
    for (unsigned i = 0; i < count; i++)
    {
        if (buses[i].GetRouteNo() == route)
        {
            return i;
        }
    }

    return -1;
}

int main() {
    srand(time(NULL));

    // Создание и изменение автобуса

    Bus my_bus = Bus("AB341E68", "Иванов Б.В.", 50);

    my_bus.Show();

    my_bus.SetBusNo("PP666P66");
    my_bus.SetDriverName("Петров П.В.");
    my_bus.SetRouteNo(13);

    my_bus.Show();

    // Генерация автобусов

    cout << "==========================================" << endl;

    for (int i = 0; i < 5; i++) {
        Bus b = Bus();
        b.Show();
    }

    // Парк

    cout << "==========================================" << endl;

    BusPark park(20);

    park.FillRandom(5);

    cout << endl << "Исходный массив:" << endl;
    park.Show();

    park.SortByDriver();

    cout << endl << "После сортировки:" << endl;
    park.Show();

    park.AddBus(my_bus);

    park.SaveToFile("buses.txt");

    int index = park.SearchByRoute(13);

    if (index != -1)
    {
        cout << "Маршрут найден" << endl;
    }
    else
    {
        cout << "Маршрут не найден" << endl;
    }

    return 0;

}
