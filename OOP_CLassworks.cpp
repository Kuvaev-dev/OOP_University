#include <iostream>
#include <Windows.h>
#include <deque>
#include <string>
#include <cfloat>

using namespace std;

struct BusStation {
    string stationName;
    double distance = 0;
};

struct Route {
    string routeName;
    deque<BusStation> busStations;
    int busStationsCount = 0;
};

class TransportManagement {
private:
    deque<Route> routes;
public:
    void AddNewRoute(Route route) {
        this->routes.push_back(route);
    }
    void DeleteRouteByIndex(int index) {
        auto deleteAt = this->routes.begin() + index;
        this->routes.erase(deleteAt);
    }
    void DeleteRouteByName(string name) {
        this->routes.erase(remove_if(this->routes.begin(), this->routes.end(),
            [name](const Route& route) { return route.routeName == name; }), this->routes.end());
    }
    void DeleteBusStationByIndex(int index) {
        if (index < this->routes.size()) {
            Route& selectedRoute = this->routes.at(index);
            cout << "-> Оберіть індекс зупинки, яку треба видалити: ";
            cin >> index;
            if (index < selectedRoute.busStations.size()) {
                selectedRoute.busStations.erase(selectedRoute.busStations.begin() + index);
                cout << "-> Результат видалення:\n";
                ShowAllRoutes();
            }
            else {
                cout << "-> Неправильний індекс зупинки!\n";
            }
        }
        else {
            cout << "-> Неправильний індекс маршруту!\n";
        }
    }
    void DeleteBusStationByName(string name) {
        auto routeIt = find_if(this->routes.begin(), this->routes.end(),
            [name](const Route& route) { return route.routeName == name; });
        if (routeIt != this->routes.end()) {
            Route& selectedRoute = *routeIt;
            string stationName;
            cout << "-> Оберіть назву зупинки, яку треба видалити: ";
            cin >> stationName;
            auto stationIt = find_if(selectedRoute.busStations.begin(), selectedRoute.busStations.end(),
                [stationName](const BusStation& station) { return station.stationName == stationName; });
            if (stationIt != selectedRoute.busStations.end()) {
                selectedRoute.busStations.erase(stationIt);
                cout << "-> Результат видалення:\n";
                ShowAllRoutes();
            }
            else {
                cout << "-> Зупинку з такою назвою не знайдено!\n";
            }
        }
        else {
            cout << "-> Маршрут з такою назвою не знайдено!\n";
        }
    }
    void CalculateRoutesDistance() {
        double minDistance = DBL_MAX;
        Route* minDistanceRoute = nullptr;

        for (auto& route : this->routes) {
            double distance = 0;
            for (auto& station : route.busStations) {
                distance += station.distance;
            }

            if (distance < minDistance) {
                minDistance = distance;
                minDistanceRoute = &route;
            }
        }

        if (minDistanceRoute != nullptr) {
            cout << "-> Маршрут з найменшою дистанцією: " << minDistanceRoute->routeName << "\n";
            cout << "-> Загальна дистанція: " << minDistance << "\n";
        }
    }
    void FindNearestStations(string routeName, string currentStationName) {
        auto routeIt = find_if(this->routes.begin(), this->routes.end(),
            [routeName](const Route& route) { return route.routeName == routeName; });

        if (routeIt == this->routes.end()) {
            cout << "-> Маршрут не найден\n";
            return;
        }

        auto& busStations = routeIt->busStations;

        auto currentIt = find_if(busStations.begin(), busStations.end(),
            [currentStationName](const BusStation& station) { return station.stationName == currentStationName; });

        if (currentIt == busStations.end()) {
            cout << "-> Зупинку не знайдено\n";
            return;
        }

        const int currentIndex = distance(busStations.begin(), currentIt);

        if (currentIndex == 0) {
            cout << "-> Наразі автобус знаходиться на початку маршруту\n";
            cout << "-> Наступні дві зупинки: \n";
            cout << "-> " << busStations.at(currentIndex + 1).stationName << '\n';
            if (busStations.size() == 1) {
                cout << "-> До кінця маршруту залишилась одна зупинка: " << busStations[currentIndex].stationName << '\n';
            }
            else {
                cout << "-> " << busStations.at(currentIndex + 2).stationName << '\n';
            }
        }
        else if (currentIndex == busStations.size() - 1) {
            cout << "-> Наразі автобус знаходиться на кінцевій зупинці\n";
            if (busStations.size() == 1) {
                cout << "-> У маршруті лише одна зупинка: " << busStations.at(currentIndex).stationName << '\n';
            }
            else {
                cout << "-> Попередні дві зупинки: \n";
                cout << "\t-> " << busStations.at(currentIndex - 2).stationName << '\n';
                cout << "\t-> " << busStations.at(currentIndex - 1).stationName << '\n';
            }
        }
        else {
            cout << "-> Наразі автобус знаходиться на зупинці " << currentStationName << '\n';
            cout << "-> Попередні дві зупинки: \n";
            cout << "\t-> " << busStations.at(currentIndex - 1).stationName << '\n';
            cout << "\t-> " << busStations.at(currentIndex - 2).stationName << '\n';
            cout << "-> Наступні дві зупинки: \n";
            cout << "\t-> " << busStations.at(currentIndex + 1).stationName << '\n';
            cout << "\t-> " << busStations.at(currentIndex + 2).stationName << '\n';
        }
    }
    void ShowAllRoutes() {
        for (int r = 0; r < routes.size(); r++)
        {
            cout << "Назва маршруту: " << routes.at(r).routeName << '\n';
            cout << "Зупинки:\n";
            for (int b = 0; b < routes.at(r).busStations.size(); b++)
            {
                cout << "Назва " << b + 1 << " зупинки: " << routes.at(r).busStations.at(b).stationName << '\n';
                cout << "Відстань до наступної зупинки: " << routes.at(r).busStations.at(b).distance << '\n';
            }
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TransportManagement tm;
    Route userRoute;
    BusStation userBusStation;
    int routesCount = 0, sw = 0;
    int userIndex = 0;
    string userRouteName;
    string userBusStationName;

    cout << "-> Введіть кількість маршрутів: ";
    cin >> routesCount;
    cout << "-------------------------------------------------------------------\n";
    for (int rc = 0; rc < routesCount; rc++)
    {
        cout << "-> Введіть назву для " << rc + 1 << " маршруту: ";
        cin >> userRoute.routeName;
        cout << "-> Введіть кількість зупинок для " << rc + 1 << " маршруту: ";
        cin >> userRoute.busStationsCount;
        for (int bsc = 0; bsc < userRoute.busStationsCount; bsc++)
        {
            cout << "\t-> Введіть дані для " << bsc + 1 << " зупинки.\n";
            cout << "\t-> Введіть назву зупинки: ";
            cin >> userBusStation.stationName;
            cout << "\t-> Введіть відстань до наступної зупинки: ";
            cin >> userBusStation.distance;
            userRoute.busStations.push_back(userBusStation);
        }
        tm.AddNewRoute(userRoute);
        userRoute.busStations.clear();
        cout << "-------------------------------------------------------------------\n";
    }
    tm.ShowAllRoutes();
    do {
        cout << "-------------------------------------------------------------------\n";
        cout << "-> Оберіть дію:\n\t-> 1. Видалити маршрут\n\t-> 2. Видалити зупинку з маршруту\n\t-> 3. Знайти найкоротший маршрут\n\t-> 4. Знайти найкоротшу зупинку на маршруті\n-> Ваш вибір: ";
        cin >> sw;
    } while (sw < 1 || sw > 4);
    switch (sw) {
    case 1:
        cout << "-------------------------------------------------------------------\n";
        sw = 0;
        do {
            cout << "-> Видалити маршрут за:\n\t-> 1. Індексом\n\t-> 2. Назвою\n-> Оберіть дію: ";
            cin >> sw;
        } while (sw < 1 || sw > 2);
        switch (sw) {
        case 1:
            cout << "-------------------------------------------------------------------\n";
            cout << "-> Введіть індекс: ";
            cin >> userIndex;
            tm.DeleteRouteByIndex(userIndex);
            cout << "-> Результат видалення:\n";
            tm.ShowAllRoutes();
            cout << "-------------------------------------------------------------------\n";
            break;
        case 2:
            cout << "-------------------------------------------------------------------\n";
            cout << "-> Введіть назву маршруту: ";
            cin >> userRouteName;
            tm.DeleteRouteByName(userRouteName);
            cout << "-> Результат видалення:\n";
            tm.ShowAllRoutes();
            cout << "-------------------------------------------------------------------\n";
            break;
        }
        break;
    case 2:
        cout << "-------------------------------------------------------------------\n";
        sw = 0;
        do {
            cout << "-> Видалити зупинку з маршруту за:\n\t-> 1. Індексом маршруту\n\t-> 2. Назвою маршруту\n-> Оберіть дію: ";
            cin >> sw;
        } while (sw < 1 || sw > 2);
        switch (sw) {
        case 1:
            cout << "-------------------------------------------------------------------\n";
            cout << "-> Введіть індекс маршруту: ";
            cin >> userIndex;
            tm.DeleteBusStationByIndex(userIndex);
            cout << "-------------------------------------------------------------------\n";
            break;
        case 2:
            cout << "-------------------------------------------------------------------\n";
            cout << "-> Введіть назву маршруту: ";
            cin >> userRouteName;
            tm.DeleteBusStationByName(userRouteName);
            cout << "-------------------------------------------------------------------\n";
            break;
        }
        break;
    case 3:
        cout << "-------------------------------------------------------------------\n";
        tm.CalculateRoutesDistance();
        cout << "-------------------------------------------------------------------\n";
        break;
    case 4:
        cout << "-------------------------------------------------------------------\n";
        cout << "-> Введіть ваш маршрут: ";
        cin >> userRouteName;
        cout << "-> Введіть вашу зупинку: ";
        cin >> userBusStationName;
        tm.FindNearestStations(userRouteName, userBusStationName);
        cout << "-------------------------------------------------------------------\n";
        break;
    }

    system("pause");
    return 0;
}
