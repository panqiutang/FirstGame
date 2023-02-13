void simulate_game(Input* input) {
    clear_screen(0xda536e);
    if (input->buttons[BUTTON_UP].is_down) {
        draw_rectangle(0, 0, 500, 600, 0xbce2e8);
    }
    
    draw_rectangle(50, -50, 100, 200, 0xf4b3c2);
}