/* pixel type */
typedef unsigned int u32;

#define global_variable static

/* Clamp an integer between a minimum and maximum */
inline int clamp(int min, int value, int max) {
    if (value < min) {
        return min;
    }
    else if (value > max) {
        return max;
    }
    else {
        return value;
    }
}