#include <janet.h>
#include <stdio.h>
#include "../termbox/src/termbox.h"

/**********/
/* TYPES */
/*********/

static const JanetAbstractType tb_event_jt = {
    "event",
    JANET_ATEND_NAME
};

/********************/
/* WRAPER FUNCTIONS */
/********************/

static Janet cfun_init(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void) argv;

  int code = tb_init();
  if (code < 0) {
  	janet_panicf("termbox init failed, code: %d\n", code);
	}	

  return janet_wrap_nil();
}

/* -------------------------------------------------------- */

static Janet cfun_init_f(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  
  const char *f = janet_getcstring(argv, 0);
  int code = tb_init_file(f);
  if (code < 0) {
  	janet_panicf("termbox init failed, code: %d\n", code);
	}	

  return janet_wrap_nil();
}

/* -------------------------------------------------------- */

static Janet cfun_init_fd(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  
  int fd = janet_getinteger(argv, 0);
  int code = tb_init_fd(fd);
  if (code < 0) {
  	janet_panicf("termbox init failed, code: %d\n", code);
	}	

  return janet_wrap_nil();
}

/* -------------------------------------------------------- */

static Janet cfun_shutdown(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void) argv;

  tb_shutdown();    
  return janet_wrap_nil();
}

/* -------------------------------------------------------- */

static Janet cfun_width(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void) argv;

  int width = tb_width();    
  return janet_wrap_integer(width);
}

/* -------------------------------------------------------- */

static Janet cfun_height(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void) argv;

  int height = tb_height();    
  return janet_wrap_integer(height);
}

/* -------------------------------------------------------- */

static Janet cfun_clear(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void) argv;

  tb_clear();    
  return janet_wrap_nil();
}

/* -------------------------------------------------------- */

// TODO:
static Janet cfun_clear_attr(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  uint16_t f = (uint16_t) janet_getinteger(argv, 0);
  uint16_t b = (uint16_t) janet_getinteger(argv, 1);

  tb_set_clear_attributes(f, b);
  return janet_wrap_nil();
}

/* -------------------------------------------------------- */

static Janet cfun_present(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void) argv;

  tb_present();    
  return janet_wrap_nil();
}

/* -------------------------------------------------------- */

static Janet cfun_cursor(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  
  int x = janet_getinteger(argv, 0);
  int y = janet_getinteger(argv, 1);
  tb_set_cursor(x, y);

  return janet_wrap_nil();
}

/* -------------------------------------------------------- */

static Janet cfun_cell(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 5);
  
  int x = janet_getinteger(argv, 0);
  int y = janet_getinteger(argv, 1);
  int h = janet_getinteger(argv, 2);
  int f = janet_getinteger(argv, 3);
  int b = janet_getinteger(argv, 4);
  tb_change_cell(x, y, h, f, b);

  return janet_wrap_nil();
}

/* -------------------------------------------------------- */

static Janet cfun_input_mode(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  
  int m = janet_getinteger(argv, 0);  
  int nm = tb_select_input_mode(m);

  return janet_wrap_integer(nm);
}

/* -------------------------------------------------------- */

static Janet cfun_output_mode(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  
  int m = janet_getinteger(argv, 0);  
  int nm = tb_select_output_mode(m);

  return janet_wrap_integer(nm);
}

/* -------------------------------------------------------- */

static Janet cfun_event(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 0);
  (void) argv;
  
	struct tb_event *event = janet_abstract(&tb_event_jt, sizeof(struct tb_event));
	
	return janet_wrap_abstract(event);
}

/* -------------------------------------------------------- */

static Janet cfun_event_type(int32_t argc, Janet *argv) {
	janet_fixarity(argc, 1);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt)); 
  int type = (int) event->type;
  
  return janet_wrap_integer(type);
}

/* -------------------------------------------------------- */

static Janet cfun_event_mod(int32_t argc, Janet *argv) {
	janet_fixarity(argc, 1);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt)); 
  int mod = (int) event->mod;
  
  return janet_wrap_integer(mod);
}

/* -------------------------------------------------------- */

static Janet cfun_event_key(int32_t argc, Janet *argv) {
	janet_fixarity(argc, 1);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt)); 
  int key = (int) event->key;
  
  return janet_wrap_integer(key);
}

/* -------------------------------------------------------- */

static Janet cfun_event_char(int32_t argc, Janet *argv) {
	janet_fixarity(argc, 1);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt)); 
  int ch = (int) event->ch;
  
  return janet_wrap_integer(ch);
}

/* -------------------------------------------------------- */

static Janet cfun_event_w(int32_t argc, Janet *argv) {
	janet_fixarity(argc, 1);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt)); 
  int w = (int) event->w;
  
  return janet_wrap_integer(w);
}

/* -------------------------------------------------------- */

static Janet cfun_event_h(int32_t argc, Janet *argv) {
	janet_fixarity(argc, 1);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt)); 
  int h = (int) event->h;
  
  return janet_wrap_integer(h);
}

/* -------------------------------------------------------- */

static Janet cfun_event_x(int32_t argc, Janet *argv) {
	janet_fixarity(argc, 1);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt)); 
  int x = (int) event->x;
  
  return janet_wrap_integer(x);
}

/* -------------------------------------------------------- */

static Janet cfun_event_y(int32_t argc, Janet *argv) {
	janet_fixarity(argc, 1);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt)); 
  int y = (int) event->y;
  
  return janet_wrap_integer(y);
}

/* -------------------------------------------------------- */

static Janet cfun_peek_event(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt));
  int timeout = janet_getinteger(argv, 1);

  int res = tb_peek_event(event, timeout);
  if (res == -1) {		
		return janet_wrap_false();
	}

  return janet_wrap_true();
}

/* -------------------------------------------------------- */

static Janet cfun_poll_event(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  
  struct tb_event *event = ((struct tb_event *)janet_getabstract(argv, 0, &tb_event_jt));
  int res = tb_poll_event(event);
  if (res == -1) {		
		return janet_wrap_false();
	}

  return janet_wrap_true();
}

/*************************/
/* C CONSTANTS REGISTERY */
/*************************/

void janet_cdefs(JanetTable *env) {
	// TB_KEYS
	janet_def(env, "key-f1", janet_wrap_integer(TB_KEY_F1), "f1");
	janet_def(env, "key-f2", janet_wrap_integer(TB_KEY_F2), "f2");
	janet_def(env, "key-f3", janet_wrap_integer(TB_KEY_F3), "f3");
	janet_def(env, "key-f4", janet_wrap_integer(TB_KEY_F4), "f4");
	janet_def(env, "key-f5", janet_wrap_integer(TB_KEY_F5), "f5");
	janet_def(env, "key-f6", janet_wrap_integer(TB_KEY_F6), "f6");
	janet_def(env, "key-f7", janet_wrap_integer(TB_KEY_F7), "f7");
	janet_def(env, "key-f8", janet_wrap_integer(TB_KEY_F8), "f8");
	janet_def(env, "key-f9", janet_wrap_integer(TB_KEY_F9), "f9");
	janet_def(env, "key-f10", janet_wrap_integer(TB_KEY_F10), "f10");
	janet_def(env, "key-f11", janet_wrap_integer(TB_KEY_F11), "f11");
	janet_def(env, "key-f12", janet_wrap_integer(TB_KEY_F12), "f12");
	janet_def(env, "key-insert", janet_wrap_integer(TB_KEY_INSERT), "insert");
	janet_def(env, "key-delete", janet_wrap_integer(TB_KEY_DELETE), "delete");
	janet_def(env, "key-home", janet_wrap_integer(TB_KEY_HOME), "home");
	janet_def(env, "key-end", janet_wrap_integer(TB_KEY_END), "end");
	janet_def(env, "key-pgup", janet_wrap_integer(TB_KEY_PGUP), "pgup");
	janet_def(env, "key-pgdn", janet_wrap_integer(TB_KEY_PGDN), "pgdn");
	janet_def(env, "key-arrow-up", janet_wrap_integer(TB_KEY_ARROW_UP), "arrow up");
	janet_def(env, "key-arrow-down", janet_wrap_integer(TB_KEY_ARROW_DOWN), "arrow down");
	janet_def(env, "key-arrow-left", janet_wrap_integer(TB_KEY_ARROW_LEFT), "arrow left");
	janet_def(env, "key-arrow-right", janet_wrap_integer(TB_KEY_ARROW_RIGHT), "arrow right");
	janet_def(env, "key-mouse-left", janet_wrap_integer(TB_KEY_MOUSE_LEFT), "mouse left");
	janet_def(env, "key-mouse-right", janet_wrap_integer(TB_KEY_MOUSE_RIGHT), "mouse right");
	janet_def(env, "key-mouse-middle", janet_wrap_integer(TB_KEY_MOUSE_MIDDLE), "mouse middle");
	janet_def(env, "key-mouse-release", janet_wrap_integer(TB_KEY_MOUSE_RELEASE), "mouse release");
	janet_def(env, "key-mouse-wheel-up", janet_wrap_integer(TB_KEY_MOUSE_WHEEL_UP), "mouse wheel up");
	janet_def(env, "key-mouse-wheel-down", janet_wrap_integer(TB_KEY_MOUSE_WHEEL_DOWN), "mouse wheel down");

	janet_def(env, "key-ctrl-tilde", janet_wrap_integer(TB_KEY_CTRL_TILDE), "ctrl tilde");
	janet_def(env, "key-ctrl-2", janet_wrap_integer(TB_KEY_CTRL_2), "ctrl 2");
	janet_def(env, "key-ctrl-a", janet_wrap_integer(TB_KEY_CTRL_A), "ctrl a");
	janet_def(env, "key-ctrl-b", janet_wrap_integer(TB_KEY_CTRL_B), "ctrl b");
	janet_def(env, "key-ctrl-c", janet_wrap_integer(TB_KEY_CTRL_C), "ctrl c");
	janet_def(env, "key-ctrl-d", janet_wrap_integer(TB_KEY_CTRL_D), "ctrl d");
	janet_def(env, "key-ctrl-e", janet_wrap_integer(TB_KEY_CTRL_E), "ctrl e");
	janet_def(env, "key-ctrl-f", janet_wrap_integer(TB_KEY_CTRL_F), "ctrl f");
	janet_def(env, "key-ctrl-g", janet_wrap_integer(TB_KEY_CTRL_G), "ctrl g");
	janet_def(env, "key-backspace", janet_wrap_integer(TB_KEY_BACKSPACE), "backspace");
	janet_def(env, "key-ctrl-h", janet_wrap_integer(TB_KEY_CTRL_H), "ctrl h");
	janet_def(env, "key-tab", janet_wrap_integer(TB_KEY_TAB), "tab");
	janet_def(env, "key-ctrl-i", janet_wrap_integer(TB_KEY_CTRL_I), "ctrl i");
	janet_def(env, "key-ctrl-j", janet_wrap_integer(TB_KEY_CTRL_J), "ctrl j");
	janet_def(env, "key-ctrl-k", janet_wrap_integer(TB_KEY_CTRL_K), "ctrl k");
	janet_def(env, "key-ctrl-l", janet_wrap_integer(TB_KEY_CTRL_L), "ctrl l");
	janet_def(env, "key-enter", janet_wrap_integer(TB_KEY_ENTER), "enter");
	janet_def(env, "key-ctrl-m", janet_wrap_integer(TB_KEY_CTRL_M), "ctrl m");
	janet_def(env, "key-ctrl-n", janet_wrap_integer(TB_KEY_CTRL_N), "ctrl n");
	janet_def(env, "key-ctrl-o", janet_wrap_integer(TB_KEY_CTRL_O), "ctrl o");
	janet_def(env, "key-ctrl-p", janet_wrap_integer(TB_KEY_CTRL_P), "ctrl p");
	janet_def(env, "key-ctrl-q", janet_wrap_integer(TB_KEY_CTRL_Q), "ctrl q");
	janet_def(env, "key-ctrl-r", janet_wrap_integer(TB_KEY_CTRL_R), "ctrl r");
	janet_def(env, "key-ctrl-s", janet_wrap_integer(TB_KEY_CTRL_S), "ctrl s");
	janet_def(env, "key-ctrl-t", janet_wrap_integer(TB_KEY_CTRL_T), "ctrl t");
	janet_def(env, "key-ctrl-u", janet_wrap_integer(TB_KEY_CTRL_U), "ctrl u");
	janet_def(env, "key-ctrl-v", janet_wrap_integer(TB_KEY_CTRL_V), "ctrl v");
	janet_def(env, "key-ctrl-w", janet_wrap_integer(TB_KEY_CTRL_W), "ctrl w");
	janet_def(env, "key-ctrl-x", janet_wrap_integer(TB_KEY_CTRL_X), "ctrl x");
	janet_def(env, "key-ctrl-y", janet_wrap_integer(TB_KEY_CTRL_Y), "ctrl y");
	janet_def(env, "key-ctrl-z", janet_wrap_integer(TB_KEY_CTRL_Z), "ctrl z");
	janet_def(env, "key-esc", janet_wrap_integer(TB_KEY_ESC), "esc");
	janet_def(env, "key-ctrl-lsq-bracket", janet_wrap_integer(TB_KEY_CTRL_LSQ_BRACKET), "ctrl lsq bracket");
	janet_def(env, "key-ctrl-3", janet_wrap_integer(TB_KEY_CTRL_3), "ctrl 3");
	janet_def(env, "key-ctrl-4", janet_wrap_integer(TB_KEY_CTRL_4), "ctrl 4");
	janet_def(env, "key-ctrl-backslash", janet_wrap_integer(TB_KEY_CTRL_BACKSLASH), "ctrl backslash");
	janet_def(env, "key-ctrl-5", janet_wrap_integer(TB_KEY_CTRL_5), "ctrl 5");
	janet_def(env, "key-ctrl-rsq-bracket", janet_wrap_integer(TB_KEY_CTRL_RSQ_BRACKET), "ctrl rsq bracket");
	janet_def(env, "key-ctrl-6", janet_wrap_integer(TB_KEY_CTRL_6), "ctrl 6");
	janet_def(env, "key-ctrl-7", janet_wrap_integer(TB_KEY_CTRL_7), "ctrl 7");
	janet_def(env, "key-ctrl-slash", janet_wrap_integer(TB_KEY_CTRL_SLASH), "ctrl slash");
	janet_def(env, "key-ctrl-underscore", janet_wrap_integer(TB_KEY_CTRL_UNDERSCORE), "ctrl underscore");
	janet_def(env, "key-space", janet_wrap_integer(TB_KEY_SPACE), "space");
	janet_def(env, "key-backspace2", janet_wrap_integer(TB_KEY_BACKSPACE2), "backspace2");
	janet_def(env, "key-ctrl-8", janet_wrap_integer(TB_KEY_CTRL_8), "ctrl 8");

	// MODIFIERS
	janet_def(env, "mod-alt", janet_wrap_integer(TB_MOD_ALT), "mod alt");
	janet_def(env, "mod-motion", janet_wrap_integer(TB_MOD_MOTION), "mod motion");

	// ATTRIBUTES
	janet_def(env, "bold", janet_wrap_integer(TB_BOLD), "bold");
	janet_def(env, "underline", janet_wrap_integer(TB_UNDERLINE), "underline");
	janet_def(env, "reverse", janet_wrap_integer(TB_REVERSE), "reverse");

	// EVENTS
	janet_def(env, "event-key", janet_wrap_integer(TB_EVENT_KEY), "event key");
	janet_def(env, "event-resize", janet_wrap_integer(TB_EVENT_RESIZE), "event resize");
	janet_def(env, "event-mouse", janet_wrap_integer(TB_EVENT_MOUSE), "event mouse");

	// COLORS
	janet_def(env, "default", janet_wrap_integer(TB_DEFAULT), "default");
	janet_def(env, "black", janet_wrap_integer(TB_BLACK), "black");
	janet_def(env, "red", janet_wrap_integer(TB_RED), "red");
	janet_def(env, "green", janet_wrap_integer(TB_GREEN), "green");
	janet_def(env, "yellow", janet_wrap_integer(TB_YELLOW), "yellow");
	janet_def(env, "blue", janet_wrap_integer(TB_BLUE), "blue");
	janet_def(env, "magenta", janet_wrap_integer(TB_MAGENTA), "magenta");
	janet_def(env, "cyan", janet_wrap_integer(TB_CYAN), "cyan");
	janet_def(env, "white", janet_wrap_integer(TB_WHITE), "white");

	// TB_INPUT_MODE
	janet_def(env, "input-current", janet_wrap_integer(TB_INPUT_CURRENT), "termbox input current");
	janet_def(env, "input-esc", janet_wrap_integer(TB_INPUT_ESC), "termbox input esc");
	janet_def(env, "input-alt", janet_wrap_integer(TB_INPUT_ALT), "termbox input alt");
	janet_def(env, "input-mouse", janet_wrap_integer(TB_INPUT_MOUSE), "termbox input mouse");
	
	// TB_OUTPUT_MODE
	janet_def(env, "output-current", janet_wrap_integer(TB_OUTPUT_CURRENT), "termbox output current");
	janet_def(env, "output-normal", janet_wrap_integer(TB_OUTPUT_NORMAL), "termbox output normal");
	janet_def(env, "output-256", janet_wrap_integer(TB_OUTPUT_256), "termbox output 256");
	janet_def(env, "output-216", janet_wrap_integer(TB_OUTPUT_216), "termbox output 216");
	janet_def(env, "output-grayscale", janet_wrap_integer(TB_OUTPUT_GRAYSCALE), "termbox output grayscale");
}

/************************/
/* C FUNCTION REGISTERY */
/************************/

static JanetReg cfuns[] = {
  {"init", cfun_init, NULL},
  {"initf", cfun_init_f, NULL},
  {"initfd", cfun_init_fd, NULL},
  {"shutdown", cfun_shutdown, NULL},
  {"width", cfun_width, NULL},
  {"height", cfun_height, NULL},
  {"clear", cfun_clear, NULL},
  {"clear-attr", cfun_clear_attr, NULL},
  {"present", cfun_present, NULL},
  {"cursor", cfun_cursor, NULL},
  {"cell", cfun_cell, NULL},
  {"input-mode", cfun_input_mode, NULL},
  {"output-mode", cfun_output_mode, NULL},
  {"event", cfun_event, NULL},
  {"event-type", cfun_event_type, NULL},
	{"event-mod", cfun_event_mod, NULL},
	{"event-key", cfun_event_key, NULL},
	{"event-char", cfun_event_char, NULL},
	{"event-w", cfun_event_w, NULL},
	{"event-h", cfun_event_h, NULL},
	{"event-x", cfun_event_x, NULL},
	{"event-y", cfun_event_y, NULL},	
	{"peek-event", cfun_peek_event, NULL},
	{"poll-event", cfun_poll_event, NULL},

  {NULL, NULL, NULL}
};

/****************/
/* MODULE ENTRY */
/****************/

JANET_MODULE_ENTRY(JanetTable *env) {
	janet_cdefs(env);
  janet_cfuns(env, "jtbox", cfuns);    
}