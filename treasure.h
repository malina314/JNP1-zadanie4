template<typename T, bool IsTrapped>
class Treasure {
    // todo: check if T is integer type
    T value;

public:
    bool isTrapped;

    constexpr Treasure(T val) : value(val), isTrapped(IsTrapped) {}

    constexpr T evaluate() { return value; }

    constexpr T getLoot() {
        T buff = value;
        value = 0;
        return buff;
    }
};

template<typename T>
using SafeTreasure = Treasure<T, false>;

template<typename T>
using TrappedTreasure = Treasure<T, true>;