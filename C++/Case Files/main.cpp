#include <iostream>
#include <sstream>
#include "Repository.h"
#include "FilesRepository.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"
#include "GUI.h"
#include "FileLocation.h"
#include "FileConfiguraton.h"
#include "MemoryRepository.h"
#include "Service.h"
#include <string>
#include <fstream>
#include <memory>
#include "Service.h"
#include <algorithm>
#include <vector>
#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
//#include "Pie.h"


using namespace std;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    ifstream fileConfiguration("settings.properties");
    string line, repositoryType;
    getline(fileConfiguration, line);
    repositoryType = line.substr(line.find("=") + 1);

    if (repositoryType == "file")
    {
        string mylistFile, repositoryFile;
        getline(fileConfiguration, line);
        repositoryFile = line.substr(line.find("=") + 1);
        getline(fileConfiguration, line);
        mylistFile = line.substr(line.find("=") + 1);

        FileRepository repository{ repositoryFile };
        if (mylistFile.find(".csv") != std::string::npos)
        {
            CSVRepository savedEvidences{ mylistFile };
            Service service{ repository, savedEvidences };
            GUI gui{ service };
            gui.show();

            /* std::vector < std::shared_ptr<Users>> userWindows;

             std::vector<User> all_users = service.get_users();


             for (int i = 0; i < all_users.size(); i++)
             {
                 std::shared_ptr<Users> w = std::make_shared<Users>(service, all_users[i]);
                 userWindows.push_back(w);
                 service.addObserver(w.get());
             }
             for (auto& item : userWindows)
                 item->show();*/
            return a.exec();
        }
        else
        {
            HTMLRepository savedEvidences{ mylistFile };
            Service service{ repository, savedEvidences };
            GUI gui{ service };
            gui.show();
            /*std::vector < std::shared_ptr<Users>> userWindows;

            std::vector<User> all_users = service.get_users();


            for (int i = 0; i < all_users.size(); i++)
            {
                std::shared_ptr<Users> w = std::make_shared<Users>(service, all_users[i]);
                userWindows.push_back(w);
                service.addObserver(w.get());
            }
            for (auto& item : userWindows)
                item->show();*/
            return a.exec();
        }
    }
    else
    {
        MemoryRepository repository;
        Evidence evidence1("e1", "5X5X5", 3, 10, "DSC1323");
        Evidence evidence2("e2", "6X6X6", 2, 30, "DSC3345");
        Evidence evidence3("e3", "6X6X6", 1, 60, "DSC5654");
        Evidence evidence4("e4", "7X7X7", 2, 70, "DSC54645");
        Evidence evidence5("e5", "9X9X9", 8, 20, "DSC16543");

        string mylistFile, repositoryFile;
        getline(fileConfiguration, line);
        repositoryFile = line.substr(line.find("=") + 1);
        getline(fileConfiguration, line);
        mylistFile = line.substr(line.find("=") + 1);
        if (mylistFile.find(".csv") != std::string::npos)
        {
            CSVRepository savedEvidences{ mylistFile };
            Service service{ repository, savedEvidences };
            GUI gui{ service };
            gui.show();
            /*std::vector < std::shared_ptr<Users>> userWindows;

            std::vector<User> all_users = service.get_users();


            for (int i = 0; i < all_users.size(); i++)
            {
                std::shared_ptr<Users> w = std::make_shared<Users>(service, all_users[i]);
                userWindows.push_back(w);
                service.addObserver(w.get());
            }
            for (auto& item : userWindows)
                item->show();*/
            return a.exec();
        }
        else
        {
            HTMLRepository savedEvidences{ mylistFile };
            Service service{ repository, savedEvidences };
            GUI gui{ service };
            /* std::vector < std::shared_ptr<Users>> userWindows;

             std::vector<User> all_users = service.get_users();


             for (int i = 0; i < all_users.size(); i++)
             {
                 std::shared_ptr<Users> w = std::make_shared<Users>(service, all_users[i]);
                 userWindows.push_back(w);
                 service.addObserver(w.get());
             }
             for (auto& item : userWindows)
                 item->show();*/
            gui.show();
            return a.exec();
        }
    }
};
