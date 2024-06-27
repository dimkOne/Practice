#include <iostream>
#include <string>
#include <memory>
#include <vector>

// ������ �������� ���������� - �����
class Lamp {
private:
    std::string color;
    bool isOn;

public:
    Lamp() : color("�����"), isOn(false) {}

    void turnOn() {
        isOn = true;
        std::cout << "����� ��������" << std::endl;
    }

    void turnOff() {
        isOn = false;
        std::cout << "����� ���������" << std::endl;
    }

    void setColor(const std::string& newColor) {
        if (isOn) {
            color = newColor;
            std::cout << "���� ����� ������� �� " << color << std::endl;
        }
        else {
            std::cout << "���������� �������� ���� ����������� �����" << std::endl;
        }
    }

    bool getIsOn() const {
        return isOn;
    }
};

// ��������� �������
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

// ���������� ������� ��� ��������� �����
class TurnOnCommand : public Command {
private:
    Lamp& lamp;

public:
    TurnOnCommand(Lamp& l) : lamp(l) {}

    void execute() override {
        lamp.turnOn();
    }
};

// ���������� ������� ��� ���������� �����
class TurnOffCommand : public Command {
private:
    Lamp& lamp;

public:
    TurnOffCommand(Lamp& l) : lamp(l) {}

    void execute() override {
        lamp.turnOff();
    }
};

// ���������� ������� ��� ��������� ����� �����
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

// ������ �������, ������� ����� ������������ �������
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

// ������������ ��� ������
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

    // ������� ������� ��� ���������� ������
    std::shared_ptr<Command> turnOnLampCommand = std::make_shared<TurnOnCommand>(livingRoomLamp);
    std::shared_ptr<Command> turnOffLampCommand = std::make_shared<TurnOffCommand>(livingRoomLamp);
    std::shared_ptr<Command> changeColorRedCommand = std::make_shared<ChangeColorCommand>(livingRoomLamp, "�������");
    std::shared_ptr<Command> changeColorGreenCommand = std::make_shared<ChangeColorCommand>(livingRoomLamp, "�������");
    std::shared_ptr<Command> changeColorBlueCommand = std::make_shared<ChangeColorCommand>(livingRoomLamp, "�����");

    // ������� ����� ���������� � ��������� �������
    RemoteControl remoteControl;
    remoteControl.addCommand(turnOnLampCommand);
    remoteControl.addCommand(turnOffLampCommand);
    remoteControl.addCommand(changeColorRedCommand);
    remoteControl.addCommand(changeColorGreenCommand);
    remoteControl.addCommand(changeColorBlueCommand);

    // ������������� ���� ��� ������ ������ ����� �������
    int choice;
    do {
        std::cout << "�������� �������:" << std::endl;
        std::cout << "0. �������� �����" << std::endl;
        std::cout << "1. ��������� �����" << std::endl;
        std::cout << "2. �������� ���� ����� �� �������" << std::endl;
        std::cout << "3. �������� ���� ����� �� �������" << std::endl;
        std::cout << "4. �������� ���� ����� �� �����" << std::endl;
        std::cout << "5. �����" << std::endl;
        std::cout << "��� �����: ";
        std::cin >> choice;

        CommandType command = static_cast<CommandType>(choice);

        switch (command) {
        case TURN_ON:
            remoteControl.pressButton(0); // �������� �����
            break;
        case TURN_OFF:
            remoteControl.pressButton(1); // ��������� �����
            break;
        case CHANGE_COLOR_RED:
            remoteControl.pressButton(2); // �������� ���� ����� �� �������
            break;
        case CHANGE_COLOR_GREEN:
            remoteControl.pressButton(3); // �������� ���� ����� �� �������
            break;
        case CHANGE_COLOR_BLUE:
            remoteControl.pressButton(4); // �������� ���� ����� �� �����
            break;
        case EXIT:
            std::cout << "����� �� ���������." << std::endl;
            break;
        default:
            std::cout << "������������ �����. ���������� �����." << std::endl;
            break;
        }
    } while (choice != EXIT);

    return 0;
}