#ifndef ASSIST_H
#define ASSIST_H


class Assist
{
public:
    Assist();
    Assist(int cid,int tid);
    int getCid();
    int getTid();
private:
    int class_id;
    int tutor_id;
};

#endif // ASSIST_H
