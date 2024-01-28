#ifndef A45_915_MINDRILA_MIHAIL_IDGENERATOR_H
#define A45_915_MINDRILA_MIHAIL_IDGENERATOR_H


class IdGenerator
{
private:
    int next_id;
public:
    IdGenerator() : next_id(1) {}

    int getNextId()
    {
        return next_id++;
    }
};


#endif //A45_915_MINDRILA_MIHAIL_IDGENERATOR_H
