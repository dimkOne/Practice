#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Пример простого устройства - лампы
class Lamp {
public:
    void turnOn() {
        std::cout << "Лампа включена" << std::endl;
    }

    void turnOff() {
        std::cout << "Лампа выключена" << std::endl;
    }
};

// Интерфейс команды
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

// Конкретная команда для включения лампы
class TurnOnCommand : public Command {
private:
    Lamp& lamp;

public:
    TurnOnCommand(Lamp& l) : lamp(l) {}

    void execute() override {
        lamp.turnOn();
    }
};

// Конкретная команда для выключения лампы
class TurnOffCommand : public Command {
private:
    Lamp& lamp;

public:
    TurnOffCommand(Lamp& l) : lamp(l) {}

    void execute() override {
        lamp.turnOff();
    }
};

// Пример клиента, который будет использовать команды
class RemoteControl {
private:
    std::vector<std::shared_ptr<Command>> commands;

public:
    void addCommand(std::shared_ptr<Command> command) {
        commands.push_back(command);
    }

    void pressButton(int index) {
        if (index >= 0 && index < commands.size()) {
            commands[index]->execute();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Lamp livingRoomLamp;

    // Создаем команды для управления лампой
    std::shared_ptr<Command> turnOnLampCommand = std::make_shared<TurnOnCommand>(livingRoomLamp);
    std::shared_ptr<Command> turnOffLampCommand = std::make_shared<TurnOffCommand>(livingRoomLamp);

    // Создаем пульт управления и добавляем команды
    RemoteControl remoteControl;
    remoteControl.addCommand(turnOnLampCommand);
    remoteControl.addCommand(turnOffLampCommand);

    // Интерактивное меню для выбора команд через консоль
    int choice;
    do {
        std::cout << "Выберите команду:" << std::endl;
        std::cout << "1. Включить лампу" << std::endl;
        std::cout << "2. Выключить лампу" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            remoteControl.pressButton(0); // Включаем лампу
            break;
        case 2:
            remoteControl.pressButton(1); // Выключаем лампу
            break;
        case 0:
            std::cout << "Выход из программы." << std::endl;
            break;
        default:
            std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
            break;
        }
    } while (choice != 0);

    return 0;
}