#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Пример простого устройства - лампы
class Lamp {
private:
    std::string color;
    bool isOn;

public:
    Lamp() : color("белый"), isOn(false) {}

    void turnOn() {
        isOn = true;
        std::cout << "Лампа включена" << std::endl;
    }

    void turnOff() {
        isOn = false;
        std::cout << "Лампа выключена" << std::endl;
    }

    void setColor(const std::string& newColor) {
        if (isOn) {
            color = newColor;
            std::cout << "Цвет лампы изменен на " << color << std::endl;
        }
        else {
            std::cout << "Невозможно изменить цвет выключенной лампы" << std::endl;
        }
    }

    bool getIsOn() const {
        return isOn;
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

// Конкретная команда для изменения цвета лампы
class ChangeColorCommand : public Command {
private:
    Lamp& lamp;
    std::string color;

public:
    ChangeColorCommand(Lamp& l, const std::string& c) : lamp(l), color(c) {}

    void execute() override {
        lamp.setColor(color);
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

// Перечисление для команд
enum CommandType {
    TURN_ON,
    TURN_OFF,
    CHANGE_COLOR_RED,
    CHANGE_COLOR_GREEN,
    CHANGE_COLOR_BLUE,
    EXIT
};

int main() {
    setlocale(LC_ALL, "Russian");
    Lamp livingRoomLamp;

    // Создаем команды для управления лампой
    std::shared_ptr<Command> turnOnLampCommand = std::make_shared<TurnOnCommand>(livingRoomLamp);
    std::shared_ptr<Command> turnOffLampCommand = std::make_shared<TurnOffCommand>(livingRoomLamp);
    std::shared_ptr<Command> changeColorRedCommand = std::make_shared<ChangeColorCommand>(livingRoomLamp, "красный");
    std::shared_ptr<Command> changeColorGreenCommand = std::make_shared<ChangeColorCommand>(livingRoomLamp, "зеленый");
    std::shared_ptr<Command> changeColorBlueCommand = std::make_shared<ChangeColorCommand>(livingRoomLamp, "синий");

    // Создаем пульт управления и добавляем команды
    RemoteControl remoteControl;
    remoteControl.addCommand(turnOnLampCommand);
    remoteControl.addCommand(turnOffLampCommand);
    remoteControl.addCommand(changeColorRedCommand);
    remoteControl.addCommand(changeColorGreenCommand);
    remoteControl.addCommand(changeColorBlueCommand);

    // Интерактивное меню для выбора команд через консоль
    int choice;
    do {
        std::cout << "Выберите команду:" << std::endl;
        std::cout << "0. Включить лампу" << std::endl;
        std::cout << "1. Выключить лампу" << std::endl;
        std::cout << "2. Изменить цвет лампы на красный" << std::endl;
        std::cout << "3. Изменить цвет лампы на зеленый" << std::endl;
        std::cout << "4. Изменить цвет лампы на синий" << std::endl;
        std::cout << "5. Выйти" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        CommandType command = static_cast<CommandType>(choice);

        switch (command) {
        case TURN_ON:
            remoteControl.pressButton(0); // Включаем лампу
            break;
        case TURN_OFF:
            remoteControl.pressButton(1); // Выключаем лампу
            break;
        case CHANGE_COLOR_RED:
            remoteControl.pressButton(2); // Изменяем цвет лампы на красный
            break;
        case CHANGE_COLOR_GREEN:
            remoteControl.pressButton(3); // Изменяем цвет лампы на зеленый
            break;
        case CHANGE_COLOR_BLUE:
            remoteControl.pressButton(4); // Изменяем цвет лампы на синий
            break;
        case EXIT:
            std::cout << "Выход из программы." << std::endl;
            break;
        default:
            std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
            break;
        }
    } while (choice != EXIT);

    return 0;
}