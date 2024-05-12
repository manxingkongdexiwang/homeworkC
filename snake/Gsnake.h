#pragma once
#define BodySize 40

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};//上下左右移动的枚举类
class Snake
{
public:
    Snake();
    ~Snake();

    void Init();//初始化蛇
    void Move(CPoint food);//移动函数
    bool CheckCollision() const;//判断蛇有没有嘎掉
    void IsateFood(CPoint food, CPoint head);//判断是否吃到食物
    void SetDirection(Direction dir);
    //void AutoMoveToFood(CPoint food);
    void Draw(CDC* pDC);//绘图函数

    vector<CPoint> GetBody() const;

    bool ateFood;

private:
    vector<CPoint> body;
    Direction currentDirection;
};
