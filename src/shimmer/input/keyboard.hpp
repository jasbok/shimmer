#ifndef SHIMMER_INPUT_KEYBOARD_HPP
#define SHIMMER_INPUT_KEYBOARD_HPP
namespace shimmer
{
class keyboard
{
public:
        enum class shimmer_keys{
                UP, DOWN, LEFT, RIGHT, SELECT, BACK, GRAB_INPUT
        };
        bool capture();
        void key_press(shimmer_keys key);
        void key_release(shimmer_keys key);
protected:
        keyboard();
        virtual ~keyboard();
};
}
#endif
