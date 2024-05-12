#include "pch.h"
#include "Gsnake.h"

Snake::Snake()
{
}

Snake::~Snake()
{
}

void Snake::Init()
{
	currentDirection = Direction::RIGHT;//��ʼ��������
	body.push_back(CPoint(11,10));
	body.push_back(CPoint(10, 10));
	body.push_back(CPoint(9, 10));//�����������
}

void Snake::Move(CPoint food)
{
    // ��ȡ��ͷ��ǰλ��
    int headX = body.front().x;
    int headY = body.front().y;

    // �����ƶ����������ͷλ��
    switch (currentDirection) {
    case Direction::UP:
        headY--;
        break;
    case Direction::DOWN:
        headY++;
        break;
    case Direction::LEFT:
        headX--;
        break;
    case Direction::RIGHT:
        headX++;
        break;
    }

    //// �����ײ
    //if (CheckCollision(headX, headY)) {
    //    // ������ײ�߼���������Ϸ������
    //    return;
    //}

    // ����ͷǰ���һ���µĵ���Ϊ�µ���ͷ
    body.insert(body.begin(), CPoint(headX, headY));

    //�ж��Ƿ�Ե���ʳ��
    //IsateFood(food, body.front());

    //�����û�гԵ�ʳ��Ƴ�β�����Ա����ߵĳ���
    //if (!ateFood) {
    //    body.pop_back();
   // }
}


void Snake::SetDirection(Direction dir)
{
    // ���ݵ�ǰ�ߵķ��򣬱���ֱ�ӷ�������ƶ�
    if ((dir == Direction::UP && currentDirection != Direction::DOWN) ||
        (dir == Direction::DOWN && currentDirection != Direction::UP) ||
        (dir == Direction::LEFT && currentDirection != Direction::RIGHT) ||
        (dir == Direction::RIGHT && currentDirection != Direction::LEFT)) {
        currentDirection = dir;
    }
}//�߲��ᳯ����ͷ������

void Snake::Draw(CDC* pDC)
{

    CBrush brush(RGB(0, 255, 0)); // ʹ����ɫ��ˢ����������
    for (CPoint& point : body) {
        int left = point.x * BodySize; // ÿ������Ĵ�СΪBodySize*BodySize���������λ��
        int top = point.y * BodySize;
        int right = left + BodySize;
        int bottom = top + BodySize;
        pDC->SelectObject(&brush);
        pDC->Rectangle(left, top, right, bottom); // �����������һ����
    }
}

vector<CPoint> Snake::GetBody() const
{
    return body;
}
