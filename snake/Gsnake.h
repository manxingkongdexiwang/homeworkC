#pragma once
#define BodySize 40

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};//���������ƶ���ö����
class Snake
{
public:
    Snake();
    ~Snake();

    void Init();//��ʼ����
    void Move(CPoint food);//�ƶ�����
    bool CheckCollision() const;//�ж�����û�иµ�
    void IsateFood(CPoint food, CPoint head);//�ж��Ƿ�Ե�ʳ��
    void SetDirection(Direction dir);
    //void AutoMoveToFood(CPoint food);
    void Draw(CDC* pDC);//��ͼ����

    vector<CPoint> GetBody() const;

    bool ateFood;

private:
    vector<CPoint> body;
    Direction currentDirection;
};
