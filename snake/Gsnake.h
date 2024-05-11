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

    void Init();//初始化
    void Move(CPoint food);
   // bool CheckCollision() const;
    //void IsateFood(CPoint food, CPoint head);
    void SetDirection(Direction dir);
    //void AutoMoveToFood(CPoint food);
    void Draw(CDC* pDC);

    vector<CPoint> GetBody() const;

    bool ateFood;

private:
    vector<CPoint> body;
    Direction currentDirection;
};
