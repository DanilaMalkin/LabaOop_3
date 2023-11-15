//Малкин Д.А. Вариант 4 

#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

class Command{
public:
    Command(){
        time = 0;
        speedUp = 0;
        angle = 0;
    }

    Command(double valueTime, double valueSpeedUp, double valueAngle){
        time = valueTime;
        speedUp = valueSpeedUp;
        angle = valueAngle;
    }

    Command(const Command &other){
        time = other.time;
        speedUp = other.speedUp;
        angle = other.angle;
    }

    ~Command(){

    }

    double getSpeed() const{
        return speed;
    }
    double getSpeedUp() const{
        return speedUp;
    }
    double getAngle() const{
        return angle;
    }
    double getTime() const{
        return time;
    }
    


private:
    double time;
    double speed;
    double speedUp;
    double angle;


};

class CommandQueue {
private:
    vector<Command> commands;

public:
    CommandQueue() {
        commands = vector<Command>();
    }
    
    ~CommandQueue() {
    }
    
    void addCommand(const Command& command) {
        if (!commands.empty()) {
            const Command& lastAddTime = commands.back();
            if (lastAddTime.getTime() < command.getTime()) {
                commands.push_back(command);
            } else {
                cout << "Неверный ввод времени" << endl;
        }
        } 
        else {
            commands.push_back(command);
        }

        
        
    }

    const vector<Command>& getCommands() const {
        return commands;
    }
};

class Car{
public:
    Car(){
        x = 0.0;
        y = 0.0;
        speed = 0.0;
        speedUp = 0.0;
        angle = 0.0;
    }
    Car(double valueX, double valueY){
        x = valueX;
        y = valueY;
        speed = 0;
        speedUp = 0;
        angle = 0;
    }
    Car(const Car &other){
        x = other.x;
        y = other.y;
        speed = other.speed;
        speedUp = other.speedUp;
        angle = other.angle;
    }
    double getX() const{
        return x;
    }
    double getY() const{
        return y;
    }
    double getSpeed() const{
        return speed;
    }
    double getSpeedUp() const{
        return speedUp;
    }
    double getAngle() const{
        return angle;
    }
    void setX(double valueX){
        x = valueX;
    }
    void setY(double valueY){
        y = valueY;
    }
    void setSpeed(double valueSpeed){
        speed = valueSpeed;
    }
    void setSpeedUp(double valueSpeedUp){
        speedUp = valueSpeedUp;
    }
    void setAngle(double valueAngle){
        angle = valueAngle;
    }
    ~Car() {
    }
    virtual void printCar() const{
        cout << "X = "<< x << endl;
        cout << "Y = " << y << "\nСкорость: " << speed << "\nУскорение: "
             << speedUp << "\nУгол: " << angle << "\n" << endl;
    }
    virtual string identification() const{
        string nameClass;
        nameClass = "Car";
        return nameClass;
    }



protected:
    double x;
    double y;
    double speed;
    double speedUp;
    double angle;
    double lastSpeedUp;
    double lastAngle;

};


class RadioControlCar: public Car{
public:
    ~RadioControlCar(){

    }

    RadioControlCar() : Car(){
        lastTime = 0.0;
    }
    RadioControlCar(double valueX, double valueY) : Car(valueX, valueY){
        lastTime = 0.0;
    }
    RadioControlCar(const RadioControlCar &other) : Car(other){
        lastTime = 0.0;
    }

    double getLastTime(){
        return lastTime;
    }
    void setSpeedUp(double valueSpeedUp,double currentTime) {
        upDateInfo(currentTime,valueSpeedUp,angle);
    

    }
    void setAngle(double valueAngle,double currentTime){
        upDateInfo(currentTime,speedUp,valueAngle); 
        
    }

    virtual string identification() const override{
        string nameClass;
        nameClass = "RadioControlCar";
        return nameClass;
    }
    virtual void printCar() const override{
        cout << "прошло секунд с начала работы: "<< lastTime << "\n"
             << "X = "<< x << endl;
        cout << "Y = " << y << "\nСкорость: " << speed << "\nУскорение: "
             << speedUp << "\nУгол: " << angle << "\n" << endl;
    }
    void loadCommandQueue(const CommandQueue& queue) {
        commandQueue = queue;
    }

    void executeCommands() {
        const vector<Command>& commands = commandQueue.getCommands();
        for (const Command& command : commands) {
            upDateInfo(command.getTime(), command.getSpeedUp(), command.getAngle());
        }
    }




private:
    double lastTime;
    CommandQueue commandQueue;
    void upDateInfo(double currentTime, double newSpeedUp, double newAngle ){
        assert(currentTime >= lastTime && "Ошибка в передаче времени");
        if (currentTime > lastTime){
            double runTime = currentTime - lastTime;
            double runDistance = speed * runTime + 0.5 * speedUp * runTime * runTime;
            x += runDistance * cos(angle * M_PI / 180);
            y += runDistance * sin(angle * M_PI / 180);
            speed += speedUp * runTime;
            lastTime = currentTime;
            angle = newAngle;
            
            

        }
        speedUp = newSpeedUp;
    }

};





int main() {
    string name;

    Car a1;
    assert(a1.getX()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в X)");
    assert(a1.getY()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в Y)");
    assert(a1.getSpeed()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в Speed)");
    assert(a1.getSpeedUp()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в SpeedUp)");
    assert(a1.getAngle()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в Angle)");


    Car c1(a1);
    assert(c1.getX()==0 && "конструктор копирования  сработал не коректно (ошибка в X)");
    assert(c1.getY()==0 && "конструктор копирования  сработал не коректно (ошибка в Y)");
    assert(c1.getSpeed()==0 && "конструктор копирования  сработал не коректно (ошибка в Speed)");
    assert(c1.getSpeedUp()==0 && "конструктор копирования  сработал не коректно (ошибка в SpeedUp)");
    assert(c1.getAngle()==0 && "конструктор копирования  сработал не коректно (ошибка в Angle)");

    RadioControlCar f1(1,2);
    assert(f1.getX()==1 && "конструктор копирования в наследнике сработал не коректно (ошибка в X)");
    assert(f1.getY()==2 && "конструктор копирования в наследнике сработал не коректно (ошибка в Y)");
    assert(f1.getSpeed()==0 && "конструктор копирования в наследнике сработал не коректно (ошибка в Speed)");
    assert(f1.getSpeedUp()==0 && "конструктор копирования в наследнике сработал не коректно (ошибка в SpeedUp)");
    assert(f1.getAngle()==0 && "конструктор копирования в наследнике сработал не коректно (ошибка в Angle)");


    RadioControlCar a;
    assert(a.getX()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в X)");
    assert(a.getY()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в Y)");
    assert(a.getSpeed()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в Speed)");
    assert(a.getSpeedUp()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в SpeedUp)");
    assert(a.getAngle()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в Angle)");
    assert(a.getLastTime()==0 && "конструктор по умолчанию в наследнике сработал не коректно (ошибка в Last Time)");

    RadioControlCar c(a);
    assert(c.getX()==0 && "конструктор копирования в наследнике сработал не коректно (ошибка в X)");
    assert(c.getY()==0 && "конструктор копирования в наследнике сработал не коректно (ошибка в Y)");
    assert(c.getSpeed()==0 && "конструктор копирования в наследнике сработал не коректно (ошибка в Speed)");
    assert(c.getSpeedUp()==0 && "конструктор копирования в наследнике сработал не коректно (ошибка в SpeedUp)");
    assert(c.getAngle()==0 && "конструктор копирования в наследнике сработал не коректно (ошибка в Angle)");
    assert(c.getLastTime()==0 && "конструктор копирования в наследнике сработал не коректно (ошибка в Last Time)");

    a.setSpeedUp(4,0.0);
    a.setAngle(0,4);
    a.printCar();
    assert(a.getY()==0.0&&"проблема в проблема в координатах начальное движение в сторону ->,c 0 по Y");
    a.setAngle(70,8);
    assert(a.getAngle()==70&&"передалось не верный угол");
    a.printCar();
    a.setSpeedUp(8,13);
    a.printCar();
    Car b(4,3);
    assert(b.getX()==4&&"конструктор инициализации сработал не верно");
    Car t(b);

    assert(t.identification()=="Car"&&"инициализатор Car сработал не верно");
    assert(a.identification()=="RadioControlCar"&&"инициализатор Car сработал не верно");
    assert(t.getX()==4&&"конструктор копирования сработал не верно");


    RadioControlCar r;
    Car nr;
    nr.setSpeedUp(23);
    nr.setSpeedUp(43);
    assert(nr.getSpeed()==0&&"неверная перегрузка функции SpeedUp");
    r.setSpeedUp(23,3);
    r.setSpeedUp(43,6);
    assert(r.getSpeed()!=0&&"неверная перегрузка функции SpeedUp");

    name = r.identification();
    cout << name << endl;
    name = nr.identification();
    cout << name << endl;
    

   
    Command command1(0, 20, 0);
    assert(typeid(command1) == typeid(Command) && "не верный тип данных");
    Command command2(10, 0, 90);
    assert(typeid(command2) == typeid(Command) && "не верный тип данных"); 
    Command command3(20, 0, 90);
    assert(typeid(command3) == typeid(Command) && "не верный тип данных");
    
    CommandQueue commandQueue;
    assert(typeid(commandQueue) == typeid(CommandQueue) && "commandQueue не соответствует ожидаймому типу");
    commandQueue.addCommand(command1);
    commandQueue.addCommand(command2);
    assert(command1.getTime()<command2.getTime() && "не верная очерёдность ввода команд по времени");
    commandQueue.addCommand(command3);
    
    RadioControlCar testCommand(0, 0);
    testCommand.loadCommandQueue(commandQueue);
    testCommand.executeCommands();
    assert(testCommand.getAngle()==90&&"команды не верно передались"); 
    testCommand.printCar();


    cout << "тестирование прошло успешно!" << endl;
    return 0;
}
