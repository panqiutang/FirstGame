/* Platform independent logic */

struct Button_State {
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_COUNT, // should be the last item, which automatically corresponds to the count value
};

struct Input {
	Button_State buttons[BUTTON_COUNT];
};