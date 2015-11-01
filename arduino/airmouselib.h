#define averageLength 4

struct smoothValue {
    int values[averageLength] = {0};
    int lastValue = 0;
};

typedef struct smoothValue smoothValue;
