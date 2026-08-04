/* Test fixture with custom sections and data */

__attribute__((section(".custom_data"))) int custom_section_var = 55;
__attribute__((section(".custom_text"))) void custom_text_fn(void) {}

int regular_func_1(void) { return 1; }
int regular_func_2(void) { return 2; }
int regular_func_3(void) { return 3; }
