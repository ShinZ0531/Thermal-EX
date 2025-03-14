#include "Arknights.h"
#include "config.h"
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

#define RESET "\033[0m"
#define BLUE_BOLD "\033[1;34m"
#define BOLD "\033[1m"


char* Arknights::getTime() {
    time_t now = time(0);
    return ctime(&now);
}

void Arknights::printLogo() {
    cout << BLUE_BOLD << Arknights_LOGO << RESET << endl;
    cout << BOLD << "Local Time: " << getTime()<< endl;
    cout << BOLD << "Project Name: " << PROJECT_NAME << endl;
    cout << BOLD << "Project Version: " << PROJECT_VERSION << endl;
    cout << BOLD << "Project Description: " << PROJECT_DESCRIPTION << endl;
    cout <<THRMEX_LOGO << endl;
    cout << BLUE_BOLD << "Thermal-EX: " << RESET << "Arknights." << endl;
    cout << BLUE_BOLD << "Thermal-EX: " << RESET << "Welcome back, Doctor! I see that you're also full of light and heat today!" << endl;
}

