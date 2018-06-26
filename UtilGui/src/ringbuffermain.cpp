#include <QCoreApplication>
#include <iostream>
#include "qringbuffer.h"
#include "ringbuffert.h"
using namespace std;

#define USE_QRINGBUFFER 0

/*
 * QRingBuffer不支持各种类型的数据，只能支持char型数据
 * ringbuffer支持各种类型的数据，放的是模板，理论上来说ringbuffer更好用
 *
 */

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#if USE_QRINGBUFFER
    QRingBuffer buffer;

    cout<<"buffer size:"<<buffer.size()<<endl;

    char data1[48] = {0x55};
    char data2[8] = {0};
    cout<<"buffer can read:"<<buffer.canRead()<<endl;
    cout<<"buffer can write:"<<buffer.canWrite()<<endl;
    cout<<"buffer writing..."<<endl;
    buffer.write(data1,sizeof(data1));
    cout<<"buffer can read:"<<buffer.canRead()<<endl;
    cout<<"buffer can write:"<<buffer.canWrite()<<endl;
    cout<<"buffer reading..."<<endl;
    buffer.read(data2,8);
    cout<<"buffer can read:"<<buffer.canRead()<<endl;
    cout<<"buffer can write:"<<buffer.canWrite()<<endl;

    cout<<"HelloWorld!"<<endl;
#else
    RingBuffer<int> q(5);
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    for (int i = 0; i < 4 ; i++)
        cout << q.pop() << endl;
    q.push(5);
    q.push(5);
    q.push(5);
    while(!q.isEmpty())//不判空就pop会崩
    {
        cout << q.pop() << endl;
    }
#endif

    return a.exec();
}
