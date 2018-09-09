#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <allegro.h>
#include <alpng.h>
#include "duktape-cpp/DuktapeCpp.h"
#include "duktape.h"
#include "duk_config.h"
#include "duk_console.h"
#include <json/json.h>
using namespace std;
extern void fileio_push_file_buffer(duk_context *ctx,const char *filename);
extern void fileio_push_file_string(duk_context *ctx,const char *filename);
static void my_fatal(void *udata, const char *msg);
static duk_ret_t native_loadscript(duk_context *ctx){
	fileio_push_file_string(
		ctx,
		duk_to_string(ctx,0)
	);
	duk_eval(ctx);
	return 0;
}


//---------------------------
//int install_allegro(int system_id, int *errno_ptr, int (*atexit_ptr)());
//int allegro_init();
static duk_ret_t native_allegro_init(duk_context *ctx){
	allegro_init();
	return 0;
}
//void allegro_exit();
static duk_ret_t native_allegro_exit(duk_context *ctx){
	allegro_exit();
	return 0;
}
//Macro END_OF_MAIN()
//extern char allegro_id[];
//extern char allegro_error[ALLEGRO_ERROR_SIZE];
//#define ALLEGRO_VERSION
//#define ALLEGRO_SUB_VERSION
//#define ALLEGRO_WIP_VERSION
//#define ALLEGRO_VERSION_STR
//#define ALLEGRO_DATE_STR
//#define ALLEGRO_DATE
//Macro AL_ID(a,b,c,d)
//Macro MAKE_VERSION(a, b, c)
//extern int os_type;
//extern int os_version;
//extern int os_revision;
//extern int os_multitasking;
//void allegro_message(const char *text_format, ...);
static duk_ret_t native_allegro_message(duk_context *ctx){
	allegro_message(
		duk_to_string(ctx,0)
	);
	return 0;
}
//void set_window_title(const char *name);
static duk_ret_t native_set_window_title(duk_context *ctx){
	set_window_title(
		duk_to_string(ctx,0)
	);
	return 0;
}
//int set_close_button_callback(void (*proc)(void));
//int desktop_color_depth();
static duk_ret_t native_desktop_color_depth(duk_context *ctx){
	duk_push_int(
		ctx,
		desktop_color_depth(
		)
	);
	return 1;
}
//int get_desktop_resolution(int *width, int *height);
static duk_ret_t native_get_desktop_resolution(duk_context *ctx){//???????????
	//(int*)duk_to_pointer(ctx,0),
	//(int*)duk_to_pointer(ctx,1)
	//duk_save_int(ctx,1,1)
	int width;
	int height;
	duk_push_int(
		ctx,
		get_desktop_resolution(
			&width,
			&height
		)
	);
	return 1;
}

//void check_cpu();
static duk_ret_t native_check_cpu(duk_context *ctx){
	check_cpu(
	);
	return 0;
}
//extern char cpu_vendor[];
//extern int cpu_family;
//extern int cpu_model;
//extern int cpu_capabilities;
//---------------------------
//typedef long fixed
//typedef struct BITMAP
//typedef struct RLE_SPRITE
//typedef struct COMPILED_SPRITE
//typedef struct JOYSTICK_INFO
//typedef struct JOYSTICK_BUTTON_INFO
//typedef struct JOYSTICK_STICK_INFO
//typedef struct JOYSTICK_AXIS_INFO
//typedef struct GFX_MODE_LIST
//typedef struct GFX_MODE
//#define PAL_SIZE
//typedef PALETTE RGB[PAL_SIZE]
//typedef struct RGB
//typedef struct V3D
//typedef struct V3D_f
//typedef struct COLOR_MAP
//typedef struct RGB_MAP
//struct al_ffblk
//typedef struct DATAFILE
//typedef struct MATRIX
//typedef struct MATRIX_f
//typedef struct QUAT
//typedef struct DIALOG
//typedef struct MENU
//typedef struct DIALOG_PLAYER
//typedef struct MENU_PLAYER
//typedef struct FONT
//typedef struct BITMAP ZBUFFER
//typedef struct SAMPLE
//typedef struct MIDI
//typedef struct AUDIOSTREAM
//typedef struct PACKFILE
//typedef struct PACKFILE_VTABLE
//typedef struct LZSS_PACK_DATA
//typedef struct LZSS_UNPACK_DATA
//---------------------------
//void set_uformat(int type);
static duk_ret_t native_set_uformat(duk_context *ctx){
	set_uformat(
		duk_to_int(ctx,0)
	);
	return 0;
}
//int get_uformat(void);
static duk_ret_t native_get_uformat(duk_context *ctx){
	duk_push_int(
		ctx,
		get_uformat(
		)
	);
	return 1;
}
//void register_uformat(int type, int (*u_getc)(const char *s), int (*u_getx)(char **s), int (*u_setc)(char *s, int c), int (*u_width)(const char *s), int (*u_cwidth)(int c), int (*u_isok)(int c));
//void set_ucodepage(const unsigned short *table, const unsigned short *extras);
static duk_ret_t native_set_ucodepage(duk_context *ctx){//???
	set_ucodepage(
		duk_to_pointer(ctx,0),
		duk_to_pointer(ctx,1)
	);
	return 0;
}
//int need_uconvert(const char *s, int type, int newtype);
static duk_ret_t native_need_uconvert(duk_context *ctx){
	duk_push_int(
		ctx,
		need_uconvert(
			duk_to_string(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//int uconvert_size(const char *s, int type, int newtype);
static duk_ret_t native_uconvert_size(duk_context *ctx){
	duk_push_int(
		ctx,
		uconvert_size(
			duk_to_string(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//void do_uconvert(const char *s, int type, char *buf, int newtype, int size);
static duk_ret_t native_do_uconvert(duk_context *ctx){
	do_uconvert(
		duk_to_string(ctx,0),
		duk_to_int(ctx,1),
		duk_to_string(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4)
	);
	return 0;
}
//char *uconvert(const char *s, int type, char *buf, int newtype, int size);
static duk_ret_t native_uconvert(duk_context *ctx){
	duk_push_string(
		ctx,
		uconvert(
			duk_to_string(ctx,0),
			duk_to_int(ctx,1),
			duk_to_string(ctx,2),
			duk_to_int(ctx,3),
			duk_to_int(ctx,4)
		)
	);
	return 1;
}
//char *uconvert_ascii(const char *s, char buf[]);
static duk_ret_t native_uconvert_ascii(duk_context *ctx){
	duk_push_string(
		ctx,
		uconvert_ascii(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1)//???
		)
	);
	return 1;
}
//char *uconvert_toascii(const char *s, char buf[]);
static duk_ret_t native_uconvert_toascii(duk_context *ctx){
	duk_push_string(
		ctx,
		uconvert_toascii(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1)//???
		)
	);
	return 1;
}
//extern char empty_string[];
//int ugetc(const char *s);
static duk_ret_t native_ugetc(duk_context *ctx){
	duk_push_int(
		ctx,
		ugetc(
			duk_to_string(ctx,0)
		)
	);
	return 1;
}
//int ugetx(char **s);
static duk_ret_t native_ugetx(duk_context *ctx){
	duk_push_int(
		ctx,
		ugetx(
			(char**)duk_to_pointer(ctx,0)//???ptr
		)
	);
	return 1;
}
//int ugetxc(const char **s);
static duk_ret_t native_ugetxc(duk_context *ctx){
	duk_push_int(
		ctx,
		ugetxc(
			(char**)duk_to_pointer(ctx,0)//???ptr
		)
	);
	return 1;
}
//int usetc(char *s, int c);
static duk_ret_t native_usetc(duk_context *ctx){
	duk_push_int(
		ctx,
		usetc(
			duk_to_string(ctx,0),//???ptr
			duk_to_int(ctx,1)//???ptr
		)
	);
	return 1;
}
//int uwidth(const char *s);
static duk_ret_t native_uwidth(duk_context *ctx){
	duk_push_int(
		ctx,
		uwidth(
			duk_to_string(ctx,0)
		)
	);
	return 1;
}
//int ucwidth(int c);
static duk_ret_t native_ucwidth(duk_context *ctx){
	duk_push_int(
		ctx,
		ucwidth(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
//int uisok(int c);
static duk_ret_t native_uisok(duk_context *ctx){
	duk_push_int(
		ctx,
		uisok(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
//int uoffset(const char *s, int index);
static duk_ret_t native_uoffset(duk_context *ctx){
	duk_push_int(
		ctx,
		uoffset(
			duk_to_string(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	return 1;
}
//int ugetat(const char *s, int index);
static duk_ret_t native_ugetat(duk_context *ctx){
	duk_push_int(
		ctx,
		ugetat(
			duk_to_string(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	return 1;
}
//int usetat(char *s, int index, int c);
static duk_ret_t native_usetat(duk_context *ctx){
	duk_push_int(
		ctx,
		usetat(
			duk_to_string(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//int uinsert(char *s, int index, int c);
static duk_ret_t native_uinsert(duk_context *ctx){
	duk_push_int(
		ctx,
		uinsert(
			duk_to_string(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//int uremove(char *s, int index);
static duk_ret_t native_uremove(duk_context *ctx){
	duk_push_int(
		ctx,
		uremove(
			duk_to_string(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	return 1;
}
//int ustrsize(const char *s);
static duk_ret_t native_ustrsize(duk_context *ctx){
	duk_push_int(
		ctx,
		ustrsize(
			duk_to_string(ctx,0)
		)
	);
	return 1;
}
//int ustrsizez(const char *s);
static duk_ret_t native_ustrsizez(duk_context *ctx){
	duk_push_int(
		ctx,
		ustrsizez(
			duk_to_string(ctx,0)
		)
	);
	return 1;
}
//int uwidth_max(int type);
static duk_ret_t native_uwidth_max(duk_context *ctx){
	duk_push_int(
		ctx,
		uwidth_max(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
//int utolower(int c);
static duk_ret_t native_utolower(duk_context *ctx){
	duk_push_int(
		ctx,
		utolower(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
//int utoupper(int c);
static duk_ret_t native_utoupper(duk_context *ctx){
	duk_push_int(
		ctx,
		utoupper(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
//int uisspace(int c);
static duk_ret_t native_uisspace(duk_context *ctx){
	duk_push_int(
		ctx,
		uisspace(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
//int uisdigit(int c);
static duk_ret_t native_uisdigit(duk_context *ctx){
	duk_push_int(
		ctx,
		uisdigit(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
//char *ustrdup(const char *src)
static duk_ret_t native_ustrdup(duk_context *ctx){
	duk_push_string(
		ctx,
		uisdigit(
			duk_to_string(ctx,0)
		)
	);
	return 1;
}
//char *_ustrdup(const char *src, void* (*malloc_func)(size_t)) ???????
static duk_ret_t native__ustrdup(duk_context *ctx){
	duk_push_string(
		ctx,
		_ustrdup(
			duk_to_string(ctx,0),
			duk_to_pointer(ctx,1)
		)
	);
	return 1;
}
//char *ustrcpy(char *dest, const char *src); ????
static duk_ret_t native_ustrcpy(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrcpy(
			duk_to_string(ctx,0),//pointers???
			duk_to_string(ctx,1)//pointers???
		)
	);
	return 1;
}
//char *ustrzcpy(char *dest, int size, const char *src); ????
static duk_ret_t native_ustrzcpy(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrzcpy(
			duk_to_string(ctx,0),//pointers???
			duk_to_int(ctx,1),
			duk_to_string(ctx,2)//pointers???
		)
	);
	return 1;
}
//char *ustrcat(char *dest, const char *src);
static duk_ret_t native_ustrcat(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrcat(
			duk_to_string(ctx,0),//pointers???
			duk_to_string(ctx,1)//pointers???
		)
	);
	return 1;
}
//char *ustrzcat(char *dest, int size, const char *src);
static duk_ret_t native_ustrzcat(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrzcat(
			duk_to_string(ctx,0),//pointers???
			duk_to_int(ctx,1),
			duk_to_string(ctx,2)//pointers???
		)
	);
	return 1;
}
//int ustrlen(const char *s);
static duk_ret_t native_ustrlen(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrlen(
			duk_to_string(ctx,0)
		)
	);
	return 1;
}
//int ustrcmp(const char *s1, const char *s2);
static duk_ret_t native_ustrcmp(duk_context *ctx){
	duk_push_int(
		ctx,
		ustrcmp(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1)
		)
	);
	return 1;
}
//char *ustrncpy(char *dest, const char *src, int n); ???
static duk_ret_t native_ustrncpy(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrncpy(
			duk_to_string(ctx,0),//pointers
			duk_to_string(ctx,1),//pointers
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//char *ustrzncpy(char *dest, int size, const char *src, int n); ???
static duk_ret_t native_ustrzncpy(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrzncpy(
			duk_to_string(ctx,0),//pointers ???
			duk_to_int(ctx,1),
			duk_to_string(ctx,2),//pointers ???
			duk_to_int(ctx,3)
		)
	);
	return 1;
}
//char *ustrncat(char *dest, const char *src, int n);
static duk_ret_t native_ustrncat(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrncat(
			duk_to_string(ctx,0),//pointers ???
			duk_to_string(ctx,1),//pointers ???
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//char *ustrzncat(char *dest, int size, const char *src, int n);
static duk_ret_t native_ustrzncat(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrzncat(
			duk_to_string(ctx,0),//pointers ???
			duk_to_int(ctx,1),
			duk_to_string(ctx,2),//pointers ???
			duk_to_int(ctx,3)
		)
	);
	return 1;
}
//int ustrncmp(const char *s1, const char *s2, int n);
static duk_ret_t native_ustrncmp(duk_context *ctx){
	duk_push_int(
		ctx,
		ustrncmp(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//int ustricmp(const char *s1, const char *s2);
static duk_ret_t native_ustricmp(duk_context *ctx){
	duk_push_int(
		ctx,
		ustricmp(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1)
		)
	);
	return 1;
}
//int ustrnicmp(const char *s1, const char *s2, int n);
static duk_ret_t native_ustrnicmp(duk_context *ctx){
	duk_push_int(
		ctx,
		ustrnicmp(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//char *ustrlwr(char *s); ???
static duk_ret_t native_ustrlwr(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrlwr(
			duk_to_string(ctx,0)//pointer???
		)
	);
	return 1;
}
//char *ustrupr(char *s);
static duk_ret_t native_ustrupr(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrupr(
			duk_to_string(ctx,0)//pointer???
		)
	);
	return 1;
}
//char *ustrchr(const char *s, int c);
static duk_ret_t native_ustrchr(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrchr(
			duk_to_string(ctx,0),//pointer???
			duk_to_int(ctx,1)//pointer???
		)
	);
	return 1;
}
//char *ustrrchr(const char *s, int c);
static duk_ret_t native_ustrrchr(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrrchr(
			duk_to_string(ctx,0),//pointer???
			duk_to_int(ctx,1)//pointer???
		)
	);
	return 1;
}
//char *ustrstr(const char *s1, const char *s2);
static duk_ret_t native_ustrstr(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrstr(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1)
		)
	);
	return 1;
}
//char *ustrpbrk(const char *s, const char *set);
static duk_ret_t native_ustrpbrk(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrpbrk(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1)
		)
	);
	return 1;
}
//char *ustrtok(char *s, const char *set); ???
static duk_ret_t native_ustrtok(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrtok(
			duk_to_string(ctx,0),//pointer???
			duk_to_string(ctx,1)
		)
	);
	return 1;
}
//char *ustrtok_r(char *s, const char *set, char **last);
static duk_ret_t native_ustrtok_r(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrtok_r(
			duk_to_string(ctx,0),//pointer???
			duk_to_string(ctx,1),
			duk_to_pointer(ctx,2)//pointer???
		)
	);
	return 1;
}
//double uatof(const char *s);
static duk_ret_t native_uatof(duk_context *ctx){
	duk_push_number(
		ctx,
		uatof(
			duk_to_string(ctx,0)
		)
	);
	return 1;
}
//long ustrtol(const char *s, char **endp, int base); ???
static duk_ret_t native_ustrtol(duk_context *ctx){
	duk_push_number(
		ctx,
		ustrtol(
			duk_to_string(ctx,0),
			duk_to_pointer(ctx,1),//pointer???
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//double ustrtod(const char *s, char **endp); ???
static duk_ret_t native_ustrtod(duk_context *ctx){
	duk_push_number(
		ctx,
		ustrtod(
			duk_to_string(ctx,0),
			duk_to_pointer(ctx,1)//pointer???
		)
	);
	return 1;
}
//const char *ustrerror(int err);
static duk_ret_t native_ustrerror(duk_context *ctx){
	duk_push_string(
		ctx,
		ustrerror(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
//int usprintf(char *buf, const char *format, ...); ???
static duk_ret_t native_usprintf(duk_context *ctx){
	duk_push_int(
		ctx,
		usprintf(
			duk_to_string(ctx,0),//pointer ???
			duk_to_string(ctx,1)
		)
	);
	return 1;
}
//int uszprintf(char *buf, int size, const char *format, ...); ???
static duk_ret_t native_uszprintf(duk_context *ctx){
	duk_push_int(
		ctx,
		uszprintf(
			duk_to_string(ctx,0),//pointer ???
			duk_to_int(ctx,1),
			duk_to_string(ctx,2)
		)
	);
	return 1;
}
//int uvsprintf(char *buf, const char *format, va_list args);
static duk_ret_t native_uvsprintf(duk_context *ctx){
	duk_push_int(
		ctx,
		uvsprintf(
			duk_to_string(ctx,0),//pointer ???
			duk_to_string(ctx,2),
			duk_to_string(ctx,3)//pointer ???
		)
	);
	return 1;
}
//int uvszprintf(char *buf, int size, const char *format, va_list args);
static duk_ret_t native_uvszprintf(duk_context *ctx){
	duk_push_int(
		ctx,
		uvszprintf(
			duk_to_string(ctx,0),//pointer ???
			duk_to_int(ctx,2),
			duk_to_string(ctx,3),
			duk_to_string(ctx,4)//pointer ???
		)
	);
	return 1;
}
//---------------------------
//void set_config_file(const char *filename);
static duk_ret_t native_set_config_file(duk_context *ctx){
	set_config_file(
		duk_to_string(ctx,0)
	);
	return 0;
}
//void set_config_data(const char *data, int length);
static duk_ret_t native_set_config_data(duk_context *ctx){
	set_config_data(
		duk_to_pointer(ctx,0),
		duk_to_int(ctx,1)
	);
	return 0;
}
//void override_config_file(const char *filename);
static duk_ret_t native_override_config_file(duk_context *ctx){
	override_config_file(
		duk_to_string(ctx,0)
	);
	return 0;
}
//void override_config_data(const char *data, int length);
static duk_ret_t native_override_config_data(duk_context *ctx){
	override_config_data(
		duk_to_pointer(ctx,0),
		duk_to_int(ctx,1)
	);
	return 0;
}
//void push_config_state();
static duk_ret_t native_push_config_state(duk_context *ctx){
	push_config_state(
	);
	return 0;
}
//void pop_config_state();
static duk_ret_t native_pop_config_state(duk_context *ctx){
	pop_config_state(
	);
	return 0;
}
//void flush_config_file();
static duk_ret_t native_flush_config_file(duk_context *ctx){
	flush_config_file(
	);
	return 0;
}
//void reload_config_texts(const char *new_language);
static duk_ret_t native_reload_config_texts(duk_context *ctx){
	reload_config_texts(
		duk_to_string(ctx,0)
	);
	return 0;
}
//void hook_config_section(
//	const char *section,
//	int (*intgetter)(
//		const char *name,
//		int def
//	),
//	const char *(*stringgetter)(
//		const char *name,
//		const char *def
//	),
//	void (*stringsetter)(
//		const char *name,
//		const char *value
//	)
//); ???
static duk_ret_t native_hook_config_section(duk_context *ctx){
	hook_config_section(
		duk_to_string(ctx,0),
		NULL,//duk_to_string(ctx,1),//pointer ???
		NULL,//duk_to_string(ctx,2),//pointer ???
		NULL//duk_to_string(ctx,3)//pointer ???
	);
	return 0;
}
//int config_is_hooked(const char *section);
static duk_ret_t native_config_is_hooked(duk_context *ctx){
	duk_push_int(
		ctx,
		config_is_hooked(
			duk_to_string(ctx,0)//pointer ???
		)
	);
	return 1;
}
//const char *get_config_string(const char *section, const char *name, const char *def);
static duk_ret_t native_get_config_string(duk_context *ctx){
	duk_push_string(
		ctx,
		get_config_string(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1),
			duk_to_string(ctx,2)
		)
	);
	return 1;
}
//int get_config_int(const char *section, const char *name, int def);
static duk_ret_t native_get_config_int(duk_context *ctx){
	duk_push_int(
		ctx,
		get_config_int(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1),
			duk_to_string(ctx,2)
		)
	);
	return 1;
}
//int get_config_hex(const char *section, const char *name, int def);
static duk_ret_t native_get_config_hex(duk_context *ctx){
	duk_push_int(
		ctx,
		get_config_hex(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1),
			duk_to_string(ctx,2)
		)
	);
	return 1;
}
//float get_config_float(const char *section, const char *name, float def);
static duk_ret_t native_get_config_float(duk_context *ctx){
	duk_push_number(
		ctx,
		get_config_float(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1),
			duk_to_number(ctx,2)
		)
	);
	return 1;
}
//int get_config_id(const char *section, const char *name, int def);
static duk_ret_t native_get_config_id(duk_context *ctx){
	duk_push_int(
		ctx,
		get_config_id(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
//char **get_config_argv(const char *section, const char *name, int *argc); ???
static duk_ret_t native_get_config_argv(duk_context *ctx){
	duk_push_pointer(
		ctx,
		get_config_argv(
			duk_to_string(ctx,0),
			duk_to_string(ctx,1),
			duk_to_pointer(ctx,2)//pointer???
		)
	);
	return 1;
}
//const char *get_config_text(const char *msg);
static duk_ret_t native_get_config_text(duk_context *ctx){
	duk_push_string(
		ctx,
		get_config_text(
			duk_to_string(ctx,0)
		)
	);
	return 1;
}
//void set_config_string(const char *section, const char *name, const char *val);
static duk_ret_t native_set_config_string(duk_context *ctx){
	set_config_string(
		duk_to_string(ctx,0),
		duk_to_string(ctx,1),
		duk_to_string(ctx,2)
	);
	return 0;
}
//void set_config_int(const char *section, const char *name, int val);
static duk_ret_t native_set_config_int(duk_context *ctx){
	set_config_int(
		duk_to_string(ctx,0),
		duk_to_string(ctx,1),
		duk_to_int(ctx,2)
	);
	return 0;
}
//void set_config_hex(const char *section, const char *name, int val);
static duk_ret_t native_set_config_hex(duk_context *ctx){
	set_config_hex(
		duk_to_string(ctx,0),
		duk_to_string(ctx,1),
		duk_to_int(ctx,2)
	);
	return 0;
}
//void set_config_float(const char *section, const char *name, float val);
static duk_ret_t native_set_config_float(duk_context *ctx){
	set_config_float(
		duk_to_string(ctx,0),
		duk_to_string(ctx,1),
		duk_to_number(ctx,2)
	);
	return 0;
}
//void set_config_id(const char *section, const char *name, int val);
static duk_ret_t native_set_config_id(duk_context *ctx){
	set_config_id(
		duk_to_string(ctx,0),
		duk_to_string(ctx,1),
		duk_to_number(ctx,2)
	);
	return 0;
}
//int list_config_entries(const char *section, const char ***names); ???
static duk_ret_t native_list_config_entries(duk_context *ctx){
	duk_push_int(
		ctx,
		list_config_entries(
			duk_to_string(ctx,0),
			duk_to_pointer(ctx,1)//pointer pointer ???
		)
	);
	return 1;
}
//int list_config_sections(const char ***names); ???
static duk_ret_t native_list_config_sections(duk_context *ctx){
	duk_push_int(
		ctx,
		list_config_sections(
			duk_to_pointer(ctx,0)//pointer pointer ???
		)
	);
	return 1;
}
//int free_config_entries(const char ***names); ???
static duk_ret_t native_free_config_entries(duk_context *ctx){
	/*
	duk_push_int(
		ctx,
		free_config_entries( 
			duk_to_pointer(ctx,0)//pointer pointer ???
		) ??? retval ???
	);
	return 1;
	*/
	free_config_entries( 
		duk_to_pointer(ctx,0)//pointer pointer ???
	);
	return 0;
}
//---------------------------
//int install_mouse();
static duk_ret_t native_install_mouse(duk_context *ctx){
	duk_push_int(
		ctx,
		install_mouse( 
		)
	);
	return 1;
}
//void remove_mouse();
static duk_ret_t native_remove_mouse(duk_context *ctx){
	remove_mouse( 
	);
	return 0;
}
//int poll_mouse();
static duk_ret_t native_poll_mouse(duk_context *ctx){
	duk_push_int(
		ctx,
		poll_mouse( 
		)
	);
	//hack to update the stuff js side ???
	duk_push_int(ctx,mouse_x);
	duk_put_global_string(ctx,"mouse_x");
	duk_push_int(ctx,mouse_y);
	duk_put_global_string(ctx,"mouse_y");
	duk_push_int(ctx,mouse_z);
	duk_put_global_string(ctx,"mouse_z");
	duk_push_int(ctx,mouse_w);
	duk_put_global_string(ctx,"mouse_w");
	duk_push_int(ctx,mouse_b);
	duk_put_global_string(ctx,"mouse_b");
	duk_push_int(ctx,mouse_pos);
	duk_put_global_string(ctx,"mouse_pos");
	duk_push_pointer(ctx,mouse_sprite);
	duk_put_global_string(ctx,"mouse_sprite");
	duk_push_int(ctx,mouse_x_focus);
	duk_put_global_string(ctx,"mouse_x_focus");
	duk_push_int(ctx,mouse_y_focus);
	duk_put_global_string(ctx,"mouse_y_focus");
	return 1;
}
//int mouse_needs_poll();
static duk_ret_t native_mouse_needs_poll(duk_context *ctx){
	duk_push_int(
		ctx,
		mouse_needs_poll( 
		)
	);
	return 1;
}
//void enable_hardware_cursor(void);
static duk_ret_t native_enable_hardware_cursor(duk_context *ctx){
	enable_hardware_cursor( 
	);
	return 0;
}
//void disable_hardware_cursor(void);
static duk_ret_t native_disable_hardware_cursor(duk_context *ctx){
	disable_hardware_cursor( 
	);
	return 0;
}
//void select_mouse_cursor(int cursor);
static duk_ret_t native_select_mouse_cursor(duk_context *ctx){
	select_mouse_cursor( 
		duk_to_int(ctx,0)
	);
	return 0;
}
//void set_mouse_cursor_bitmap(int cursor, BITMAP *bmp);
static duk_ret_t native_set_mouse_cursor_bitmap(duk_context *ctx){
	set_mouse_cursor_bitmap( 
		duk_to_int(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1)
	);
	return 0;
}
//extern volatile int mouse_x;
//extern volatile int mouse_y;
//extern volatile int mouse_z;
//extern volatile int mouse_w;
//extern volatile int mouse_b;
//extern volatile int mouse_pos;
//extern BITMAP *mouse_sprite;
//extern int mouse_x_focus;
//extern int mouse_y_focus;
//void show_mouse(BITMAP *bmp);
static duk_ret_t native_show_mouse(duk_context *ctx){
	show_mouse( 
		duk_to_pointer(ctx,0)
	);
	return 0;
}
//void scare_mouse();
static duk_ret_t native_scare_mouse(duk_context *ctx){
	scare_mouse( 
	);
	return 0;
}
//void scare_mouse_area(int x, int y, int w, int h);
static duk_ret_t native_scare_mouse_area(duk_context *ctx){
	scare_mouse_area( 
		duk_to_int(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
//void unscare_mouse();
static duk_ret_t native_unscare_mouse(duk_context *ctx){
	unscare_mouse( 
	);
	return 0;
}
//int show_os_cursor(int cursor);
static duk_ret_t native_show_os_cursor(duk_context *ctx){
	duk_push_int(
		ctx,
		show_os_cursor( 
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
//extern volatile int freeze_mouse_flag;
//void position_mouse(int x, int y);
static duk_ret_t native_position_mouse(duk_context *ctx){
	position_mouse( 
		duk_to_int(ctx,0),
		duk_to_int(ctx,1)
	);
	return 0;
}
//void position_mouse_z(int z);
static duk_ret_t native_position_mouse_z(duk_context *ctx){
	position_mouse_z( 
		duk_to_int(ctx,0)
	);
	return 0;
}
//void position_mouse_w(int w);
static duk_ret_t native_position_mouse_w(duk_context *ctx){
	position_mouse_w( 
		duk_to_int(ctx,0)
	);
	return 0;
}
//void set_mouse_range(int x1, int y1, int x2, int y2);
static duk_ret_t native_set_mouse_range(duk_context *ctx){
	set_mouse_range( 
		duk_to_int(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
//void set_mouse_speed(int xspeed, int yspeed);
static duk_ret_t native_set_mouse_speed(duk_context *ctx){
	set_mouse_speed( 
		duk_to_int(ctx,0),
		duk_to_int(ctx,1)
	);
	return 0;
}
//void set_mouse_sprite(BITMAP *sprite);
static duk_ret_t native_set_mouse_sprite(duk_context *ctx){
	set_mouse_sprite(
		(BITMAP*)duk_to_pointer(ctx,0)
	);
	return 0;
}
//void set_mouse_sprite_focus(int x, int y);
static duk_ret_t native_set_mouse_sprite_focus(duk_context *ctx){
	set_mouse_sprite_focus(
		duk_to_int(ctx,0),
		duk_to_int(ctx,1)
	);
	return 0;
}
//void get_mouse_mickeys(int *mickeyx, int *mickeyy); ???
static duk_ret_t native_get_mouse_mickeys(duk_context *ctx){
	get_mouse_mickeys(
		(int*)duk_to_pointer(ctx,0),//pointer ???
		(int*)duk_to_pointer(ctx,1)//pointer ???
	);
	return 0;
}
//extern void (*mouse_callback)(int flags);
/* this function does not exist ????
//int mouse_on_screen();
static duk_ret_t native_mouse_on_screen(duk_context *ctx){
	duk_push_int(
		ctx,
		mouse_on_screen( 
		)
	);
	return 1;
}
*/

//zzzzzzzzz
//---------------------------
//int install_timer();
//void remove_timer();
//int install_int(void (*proc)(), int speed);
//int install_int_ex(void (*proc)(), int speed);
//Macro LOCK_VARIABLE(variable_name);
//Macro LOCK_FUNCTION(function_name);
//Macro END_OF_FUNCTION(function_name);
//void remove_int(void (*proc)());
//int install_param_int(void (*proc)(void *), void *param, int speed);
//int install_param_int_ex(void (*proc)(void *), void *param, int speed);
//void remove_param_int(void (*proc)(void *), void *param);
//extern volatile int retrace_count;
//---------------------------
//int install_keyboard();
//void remove_keyboard();
//void install_keyboard_hooks(int (*keypressed)(), int (*readkey)());
//int poll_keyboard();
//int keyboard_needs_poll();
//extern volatile char key[KEY_MAX];
//extern volatile int key_shifts;
//int keypressed();
//int readkey();
//int ureadkey(int *scancode);
//int scancode_to_ascii(int scancode);
//const char *scancode_to_name(int scancode);
//void simulate_keypress(int key);
//void simulate_ukeypress(int key, int scancode);
//extern int (*keyboard_callback)(int key);
//extern int (*keyboard_ucallback)(int key, int *scancode);
//extern void (*keyboard_lowlevel_callback)(int scancode);
//void set_leds(int leds);
//void set_keyboard_rate(int delay, int repeat);
//void clear_keybuf();
//extern int three_finger_flag;
//extern int key_led_flag;
//---------------------------
//int install_joystick(int type);
//void remove_joystick();
//int poll_joystick();
//extern int num_joysticks;
//extern JOYSTICK_INFO joy[n];
//const char *calibrate_joystick_name(int n);
//int calibrate_joystick(int n);
//int save_joystick_data(const char *filename);
//int load_joystick_data(const char *filename);
//int initialise_joystick();
//---------------------------
//void set_color_depth(int depth);
//int get_color_depth(void);
//void request_refresh_rate(int rate);
//int get_refresh_rate(void);
//GFX_MODE_LIST *get_gfx_mode_list(int card);
//void destroy_gfx_mode_list(GFX_MODE_LIST *mode_list);
//int set_gfx_mode(int card, int w, int h, int v_w, int v_h);
//int set_display_switch_mode(int mode);
//int set_display_switch_callback(int dir, void (*cb)());
//void remove_display_switch_callback(void (*cb)());
//int get_display_switch_mode();
//int is_windowed_mode(void);
//int get_gfx_mode_type(int graphics_card);
//int get_gfx_mode();
//extern int gfx_capabilities;
//int enable_triple_buffer();
//int scroll_screen(int x, int y);
//int request_scroll(int x, int y);
//int poll_scroll();
//int show_video_bitmap(BITMAP *bitmap);
//int request_video_bitmap(BITMAP *bitmap);
//void vsync();
static duk_ret_t native_vsync(duk_context *ctx){
	vsync(
	);
	return 0;
}

//---------------------------
//extern BITMAP *screen;
//#define SCREEN_W;
//#define SCREEN_H;
//#define VIRTUAL_W;
//#define VIRTUAL_H;
//BITMAP *create_bitmap(int width, int height);
//BITMAP *create_bitmap_ex(int color_depth, int width, int height);
//BITMAP *create_sub_bitmap(BITMAP *parent, int x, y, width, height);
//BITMAP *create_video_bitmap(int width, int height);
//BITMAP *create_system_bitmap(int width, int height);
//void destroy_bitmap(BITMAP *bitmap);
//void lock_bitmap(BITMAP *bitmap);
//int bitmap_color_depth(BITMAP *bmp);
//int bitmap_mask_color(BITMAP *bmp);
//int is_same_bitmap(BITMAP *bmp1, BITMAP *bmp2);
//int is_planar_bitmap(BITMAP *bmp);
//int is_linear_bitmap(BITMAP *bmp);
//int is_memory_bitmap(BITMAP *bmp);
//int is_screen_bitmap(BITMAP *bmp);
//int is_video_bitmap(BITMAP *bmp);
//int is_system_bitmap(BITMAP *bmp);
//int is_sub_bitmap(BITMAP *bmp);
//void acquire_bitmap(BITMAP *bmp);
//void release_bitmap(BITMAP *bmp);
//void acquire_screen();
static duk_ret_t native_acquire_screen(duk_context *ctx){
	acquire_screen(
	);
	return 0;
}

//void release_screen();
//void set_clip_rect(BITMAP *bitmap, int x1, int y1, int x2, int y2);
//void get_clip_rect(BITMAP *bitmap, int *x1, int *y1, int *x2, int *y2);
//void add_clip_rect(BITMAP *bitmap, int x1, int y1, int x2, int y2);
//void set_clip_state(BITMAP *bitmap, int state)
//int get_clip_state(BITMAP *bitmap)
//int is_inside_bitmap(BITMAP *bmp, int x, int y, int clip);
//---------------------------
//BITMAP *load_bitmap(const char *filename, RGB *pal);
//BITMAP *load_bmp(const char *filename, RGB *pal);
//BITMAP *load_bmp_pf(PACKFILE *f, RGB *pal);
//BITMAP *load_lbm(const char *filename, RGB *pal);
//BITMAP *load_pcx(const char *filename, RGB *pal);
//BITMAP *load_pcx_pf(PACKFILE *f, RGB *pal);
//BITMAP *load_tga(const char *filename, RGB *pal);
//BITMAP *load_tga_pf(PACKFILE *f, RGB *pal);
//int save_bitmap(const char *filename, BITMAP *bmp, const RGB *pal);
//int save_bmp(const char *filename, BITMAP *bmp, const RGB *pal);
//int save_bmp_pf(PACKFILE *f, BITMAP *bmp, RGB *pal);
//int save_pcx(const char *filename, BITMAP *bmp, const RGB *pal);
//int save_pcx_pf(PACKFILE *f, BITMAP *bmp, RGB *pal);
//int save_tga(const char *filename, BITMAP *bmp, const RGB *pal);
//int save_tga_pf(PACKFILE *f, BITMAP *bmp, RGB *pal);
//void register_bitmap_file_type(const char *ext, BITMAP *(*load)(const char *filename, RGB *pal), int (*save)(const char *filename, BITMAP *bmp, const RGB *pal));
//void set_color_conversion(int mode);
//int get_color_conversion();
//---------------------------
//void set_color(int index, const RGB *p);
//void _set_color(int index, const RGB *p);
//void set_palette(const PALETTE p);
//void set_palette_range(const PALETTE p, int from, int to, int vsync);
//void get_color(int index, RGB *p);
//void get_palette(PALETTE p);
//void get_palette_range(PALETTE p, int from, int to);
//void fade_interpolate(const PALETTE source, const PALETTE dest, PALETTE output, int pos, int from, int to);
//void fade_from_range(const PALETTE source, const PALETTE dest, int speed, int from, int to);
//void fade_in_range(const PALETTE p, int speed, int from, int to);
//void fade_out_range(int speed, int from, int to);
//void fade_from(const PALETTE source, const PALETTE dest, int speed);
//void fade_in(const PALETTE p, int speed);
//void fade_out(int speed);
//void select_palette(const PALETTE p);
//void unselect_palette();
//void generate_332_palette(PALETTE pal);
//int generate_optimized_palette(BITMAP *bmp, PALETTE pal, const char rsvd[PAL_SIZE]);
//extern PALETTE default_palette;
//extern PALETTE black_palette;
//extern PALETTE desktop_palette;
//---------------------------
//int makecol8(int r, int g, int b);
//int makecol15(int r, int g, int b);
//int makecol16(int r, int g, int b);
//int makecol24(int r, int g, int b);
//int makecol32(int r, int g, int b);
//int makeacol32(int r, int g, int b, int a);
//int makecol(int r, int g, int b);
//int makecol_depth(int color_depth, int r, int g, int b);
//int makeacol(int r, int g, int b, int a);
//int makeacol_depth(int color_depth, int r, int g, int b, int a);
//int makecol15_dither(int r, int g, int b, int x, int y);
//int makecol16_dither(int r, int g, int b, int x, int y);
//int getr8(int c);
//int getg8(int c);
//int getb8(int c);
//int getr15(int c);
//int getg15(int c);
//int getb15(int c);
//int getr16(int c);
//int getg16(int c);
//int getb16(int c);
//int getr24(int c);
//int getg24(int c);
//int getb24(int c);
//int getr32(int c);
//int getg32(int c);
//int getb32(int c);
//int geta32(int c);
//int getr(int c);
//int getg(int c);
//int getb(int c);
//int geta(int c);
//int getr_depth(int color_depth, int c);
//int getg_depth(int color_depth, int c);
//int getb_depth(int color_depth, int c);
//int geta_depth(int color_depth, int c);
//extern int palette_color[256];
//#define MASK_COLOR_8 0
//#define MASK_COLOR_15 (5.5.5 pink)
//#define MASK_COLOR_16 (5.6.5 pink)
//#define MASK_COLOR_24 (8.8.8 pink)
//#define MASK_COLOR_32 (8.8.8 pink)
//---------------------------
//void clear_bitmap(BITMAP *bitmap);
//void clear_to_color(BITMAP *bitmap, int color);
//void putpixel(BITMAP *bmp, int x, int y, int color);
//void _putpixel(BITMAP *bmp, int x, int y, int color);
//void _putpixel15(BITMAP *bmp, int x, int y, int color);
//void _putpixel16(BITMAP *bmp, int x, int y, int color);
//void _putpixel24(BITMAP *bmp, int x, int y, int color);
//void _putpixel32(BITMAP *bmp, int x, int y, int color);
//int getpixel(BITMAP *bmp, int x, int y);
//int _getpixel(BITMAP *bmp, int x, int y);
//int _getpixel15(BITMAP *bmp, int x, int y);
//int _getpixel16(BITMAP *bmp, int x, int y);
//int _getpixel24(BITMAP *bmp, int x, int y);
//int _getpixel32(BITMAP *bmp, int x, int y);
//void vline(BITMAP *bmp, int x, int y1, int y2, int color);
//void hline(BITMAP *bmp, int x1, int y, int x2, int color);
//void do_line(BITMAP *bmp, int x1, y1, x2, y2, int d, void (*proc)(BITMAP *bmp, int x, int y, int d));
//void line(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
//void fastline(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
//void triangle(BITMAP *bmp, int x1, y1, x2, y2, x3, y3, int color);
//void polygon(BITMAP *bmp, int vertices, const int *points, int color);
//void rect(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
//void rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
//void do_circle(BITMAP *bmp, int x, int y, int radius, int d, void (*proc)(BITMAP *bmp, int x, int y, int d));
//void circle(BITMAP *bmp, int x, int y, int radius, int color);
//void circlefill(BITMAP *bmp, int x, int y, int radius, int color);
//void circlefill(BITMAP *bmp, int x, int y, int radius, int color);
//void do_ellipse(BITMAP *bmp, int x, int y, int rx, ry, int d, void (*proc)(BITMAP *bmp, int x, int y, int d));
//void ellipse(BITMAP *bmp, int x, int y, int rx, int ry, int color);
//void ellipsefill(BITMAP *bmp, int x, int y, int rx, int ry, int color);
//void do_arc(BITMAP *bmp, int x, int y, fixed a1, fixed a2, int r, int d, void (*proc)(BITMAP *bmp, int x, int y, int d));
//void arc(BITMAP *bmp, int x, y, fixed ang1, ang2, int r, int color);
//void calc_spline(const int points[8], int npts, int *x, int *y);
//void spline(BITMAP *bmp, const int points[8], int color);
//void floodfill(BITMAP *bmp, int x, int y, int color);
//---------------------------
//void blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
//void stretch_blit(BITMAP *source, BITMAP *dest, int source_x, source_y, source_width, source_height, int dest_x, dest_y, dest_width, dest_height);
//void masked_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
//void masked_stretch_blit(BITMAP *source, BITMAP *dest, int source_x, source_y, source_w, source_h, int dest_x, dest_y, dest_w, dest_h);
//void draw_sprite_ex(BITMAP *bmp, BITMAP *sprite, int x, int y, int mode, int flip);
//void draw_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y);
//void stretch_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int w, int h);
//void draw_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y);
//void draw_sprite_h_flip(BITMAP *bmp, BITMAP *sprite, int x, int y);
//void draw_sprite_vh_flip(BITMAP *bmp, BITMAP *sprite, int x, int y);
//void draw_trans_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y);
//void draw_lit_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int color);
//void draw_gouraud_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int c1, int c2, int c3, int c4);
//void draw_character_ex(BITMAP *bmp, BITMAP *sprite, int x, int y, color, bg);
//void rotate_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle);
//void rotate_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle);
//void rotate_scaled_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle, fixed scale);
//void rotate_scaled_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle, fixed scale);
//void pivot_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle);
//void pivot_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle);
//void pivot_scaled_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale);
//void pivot_scaled_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale);
//void rotate_sprite_trans(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle);
//void rotate_sprite_v_flip_trans(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle);
//void rotate_scaled_sprite_trans(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle, fixed scale);
//void rotate_scaled_sprite_v_flip_trans(BITMAP *bmp, BITMAP *sprite, int x, int y,  fixed angle, fixed scale);
//void pivot_sprite_trans(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle);
//void pivot_sprite_v_flip_trans(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle);
//void pivot_scaled_sprite_trans(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale);
//void pivot_scaled_sprite_v_flip_trans(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale);
//void rotate_sprite_lit(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle);
//void rotate_sprite_v_flip_lit(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle);
//void rotate_scaled_sprite_lit(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle, fixed scale);
//void rotate_scaled_sprite_v_flip_lit(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle, fixed scale);
//void pivot_sprite_lit(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle);
//void pivot_sprite_v_flip_lit(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle);
//void pivot_scaled_sprite_lit(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale);
//void pivot_scaled_sprite_v_flip_lit(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale);
//---------------------------
//RLE_SPRITE *get_rle_sprite(BITMAP *bitmap);
//void destroy_rle_sprite(RLE_SPRITE *sprite);
//void draw_rle_sprite(BITMAP *bmp, const RLE_SPRITE *sprite, int x, int y);
//void draw_trans_rle_sprite(BITMAP *bmp, const RLE_SPRITE *sprite, int x, int y);
//void draw_lit_rle_sprite(BITMAP *bmp, const RLE_SPRITE *sprite, int x, y, color);
//---------------------------
//COMPILED_SPRITE *get_compiled_sprite(BITMAP *bitmap, int planar);
//void destroy_compiled_sprite(COMPILED_SPRITE *sprite);
//void draw_compiled_sprite(BITMAP *bmp, const COMPILED_SPRITE *sprite, int x, int y);
//---------------------------
//void register_font_file_type(const char *ext, FONT *(*load)(const char *filename, RGB *pal, void *param));
//FONT *load_font(const char *filename, RGB *pal, void *param);
//void destroy_font(FONT *f);
//void make_trans_font(FONT *f);
//int is_trans_font(FONT *f)
//int is_color_font(FONT *f)
//int is_mono_font(FONT *f)
//int font_has_alpha(FONT *f)
//int *is_compatible_font(FONT *f1, FONT *f2)
//int get_font_ranges(FONT *f)
//int get_font_range_begin(FONT *f, int range)
//int get_font_range_end(FONT *f, int range)
//FONT *extract_font_range(FONT *f, int begin, int end)
//int transpose_font(FONT *f, int drange)
//FONT *merge_fonts(FONT *f1, FONT *f2)
//FONT *load_dat_font(const char *filename, RGB *pal, void *param)
//FONT *load_bios_font(const char *filename, RGB *pal, void *param)
//FONT *load_grx_font(const char *filename, RGB *pal, void *param)
//FONT *load_grx_or_bios_font(const char *filename, RGB *pal, void *param)
//FONT *load_bitmap_font(const char *filename, RGB *pal, void *param)
//FONT *grab_font_from_bitmap(BITMAP *bmp)
//FONT *load_txt_font(const char *filename, RGB *pal, void *param)
//---------------------------
//extern FONT *font;
//extern int allegro_404_char;
//int text_length(const FONT *f, const char *str);
//int text_height(const FONT *f)
//void textout_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg);
//void textout_centre_ex(BITMAP *bmp, const FONT *f, const char *s, int x, y, int color, int bg);
//void textout_right_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg);
//void textout_justify_ex(BITMAP *bmp, const FONT *f, const char *s, int x1, int x2, int y, int diff, int color, int bg);
//void textprintf_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *fmt, ...);
//void textprintf_centre_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *fmt, ...);
//void textprintf_right_ex(BITMAP *bmp, const FONT *f, int x, y, color, bg, const char *fmt, ...);
//void textprintf_justify_ex(BITMAP *bmp, const FONT *f, int x1, x2, y, diff, color, bg, const char *fmt, ...);
//--------------------------
//#define POLYTYPE_FLAT
//#define POLYTYPE_GCOL
//#define POLYTYPE_GRGB
//#define POLYTYPE_ATEX
//#define POLYTYPE_PTEX
//#define POLYTYPE_ATEX_MASK
//#define POLYTYPE_PTEX_MASK
//#define POLYTYPE_ATEX_LIT
//#define POLYTYPE_PTEX_LIT
//#define POLYTYPE_ATEX_MASK_LIT
//#define POLYTYPE_PTEX_MASK_LIT
//#define POLYTYPE_ATEX_TRANS
//#define POLYTYPE_PTEX_TRANS
//#define POLYTYPE_ATEX_MASK_TRANS
//#define POLYTYPE_PTEX_MASK_TRANS
//void polygon3d(BITMAP *bmp, int type, BITMAP *texture, int vc, V3D *vtx[]);
//void polygon3d_f(BITMAP *bmp, int type, BITMAP *texture, int vc, V3D_f *vtx[]);
//void triangle3d(BITMAP *bmp, int type, BITMAP *tex, V3D *v1, *v2, *v3);
//void triangle3d_f(BITMAP *bmp, int type, BITMAP *tex, V3D_f *v1, *v2, *v3);
//void quad3d(BITMAP *bmp, int type, BITMAP *tex, V3D *v1, *v2, *v3, *v4);
//void quad3d_f(BITMAP *bmp, int type, BITMAP *tex, V3D_f *v1, *v2, *v3, *v4);
//int clip3d_f(int type, float min_z, float max_z, int vc, const V3D_f *vtx[], V3D_f *vout[], V3D_f *vtmp[], int out[]);
//int clip3d(int type, fixed min_z, fixed max_z, int vc, const V3D *vtx[], V3D *vout[], V3D *vtmp[], int out[]);
//ZBUFFER *create_zbuffer(BITMAP *bmp);
//ZBUFFER *create_sub_zbuffer(ZBUFFER *parent, int x, int y, int width, int height);
//void set_zbuffer(ZBUFFER *zbuf);
//void clear_zbuffer(ZBUFFER *zbuf, float z);
//void destroy_zbuffer(ZBUFFER *zbuf);
//int create_scene(int nedge, int npoly);
//void clear_scene(BITMAP *bmp);
//void destroy_scene();
//int scene_polygon3d(int type, BITMAP *texture, int vc, V3D *vtx[]);
//int scene_polygon3d_f(int type, BITMAP *texture, int vc, V3D_f *vtx[]);
//void render_scene();
//extern float scene_gap;
//---------------------------
//void xor_mode(int on);
//void solid_mode();
//extern COLOR_MAP *color_map;
//void create_trans_table(COLOR_MAP *table, const PALETTE pal, int r, g, b, void (*callback)(int pos));
//void create_light_table(COLOR_MAP *table, const PALETTE pal, int r, g, b, void (*callback)(int pos));
//void create_color_table(COLOR_MAP *table, const PALETTE pal, void (*blend)(PALETTE pal, int x, int y, RGB *rgb), void (*callback)(int pos));
//void create_blender_table(COLOR_MAP *table, const PALETTE pal, void (*callback)(int pos));
//void set_trans_blender(int r, int g, int b, int a);
//void set_alpha_blender();
//void set_write_alpha_blender();
//void set_add_blender(int r, int g, int b, int a);
//void set_burn_blender(int r, int g, int b, int a);
//void set_color_blender(int r, int g, int b, int a);
//void set_difference_blender(int r, int g, int b, int a);
//void set_dissolve_blender(int r, int g, int b, int a);
//void set_dodge_blender(int r, int g, int b, int a);
//void set_hue_blender(int r, int g, int b, int a);
//void set_invert_blender(int r, int g, int b, int a);
//void set_luminance_blender(int r, int g, int b, int a);
//void set_multiply_blender(int r, int g, int b, int a);
//void set_saturation_blender(int r, int g, int b, int a);
//void set_screen_blender(int r, int g, int b, int a);
//void set_blender_mode(BLENDER_FUNC b15, b16, b24, int r, g, b, a);
//void set_blender_mode_ex(BLENDER_FUNC b15, b16, b24, b32, b15x, b16x, b24x, int r, g, b, a);
//---------------------------
//int bestfit_color(const PALETTE pal, int r, int g, int b);
//extern RGB_MAP *rgb_map;
//void create_rgb_table(RGB_MAP *table, const PALETTE pal, void (*callback)(int pos));
//void hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b);
//void rgb_to_hsv(int r, int g, int b, float *h, float *s, float *v);
//---------------------------
//unsigned long bmp_write_line(BITMAP *bmp, int line);
//unsigned long bmp_read_line(BITMAP *bmp, int line);
//void bmp_unwrite_line(BITMAP *bmp);
//---------------------------
//int play_fli(const char *filename, BITMAP *bmp, int loop, int (*callback)());
//int play_memory_fli(const void *fli_data, BITMAP *bmp, int loop, int (*callback)());
//int open_fli(const char *filename);
//int open_memory_fli(const void *fli_data);
//void close_fli();
//int next_fli_frame(int loop);
//extern BITMAP *fli_bitmap;
//extern PALETTE fli_palette;
//extern int fli_bmp_dirty_from;
//extern int fli_bmp_dirty_to;
//extern int fli_pal_dirty_from;
//extern int fli_pal_dirty_to;
//void reset_fli_variables();
//extern int fli_frame;
//extern volatile int fli_timer;
//---------------------------
//int detect_digi_driver(int driver_id);
//int detect_midi_driver(int driver_id);
//void reserve_voices(int digi_voices, int midi_voices);
//void set_volume_per_voice(int scale);
//int install_sound(int digi, int midi, const char *cfg_path);
//void remove_sound();
//void set_volume(int digi_volume, int midi_volume);
//void set_hardware_volume(int digi_volume, int midi_volume);
//void get_volume(int *digi_volume, int *midi_volume);
//void get_hardware_volume(int *digi_volume, int *midi_volume);
//--------------------------
//void set_mixer_quality(int quality);
//int get_mixer_quality(void);
//int get_mixer_frequency(void);
//int get_mixer_bits(void);
//int get_mixer_channels(void);
//int get_mixer_voices(void);
//int get_mixer_buffer_length(void);
//--------------------------
//SAMPLE *load_sample(const char *filename);
//SAMPLE *load_wav(const char *filename);
//SAMPLE *load_wav_pf(PACKFILE *f);
//SAMPLE *load_voc(const char *filename);
//SAMPLE *load_voc_pf(PACKFILE *f);
//int save_sample(const char *filename, SAMPLE *spl);
//SAMPLE *create_sample(int bits, int stereo, int freq, int len);
//void destroy_sample(SAMPLE *spl);
//void lock_sample(SAMPLE *spl);
//void register_sample_file_type(const char *ext, SAMPLE *(*load)(const char *filename), int (*save)(const char *filename, SAMPLE *spl));
//int play_sample(const SAMPLE *spl, int vol, int pan, int freq, int loop);
//void adjust_sample(const SAMPLE *spl, int vol, int pan, int freq, int loop);
//void stop_sample(const SAMPLE *spl);
//int allocate_voice(const SAMPLE *spl);
//void deallocate_voice(int voice);
//void reallocate_voice(int voice, const SAMPLE *spl);
//void release_voice(int voice);
//void voice_start(int voice);
//void voice_stop(int voice);
//void voice_set_priority(int voice, int priority);
//SAMPLE *voice_check(int voice);
//int voice_get_position(int voice);
//void voice_set_position(int voice, int position);
//void voice_set_playmode(int voice, int playmode);
//int voice_get_volume(int voice);
//void voice_set_volume(int voice, int volume);
//void voice_ramp_volume(int voice, int time, int endvol);
//void voice_stop_volumeramp(int voice);
//int voice_get_frequency(int voice);
//void voice_set_frequency(int voice, int frequency);
//void voice_sweep_frequency(int voice, int time, int endfreq);
//void voice_stop_frequency_sweep(int voice);
//int voice_get_pan(int voice);
//void voice_set_pan(int voice, int pan);
//void voice_sweep_pan(int voice, int time, int endpan);
//void voice_stop_pan_sweep(int voice);
//void voice_set_echo(int voice, int strength, int delay);
//void voice_set_tremolo(int voice, int rate, int depth);
//void voice_set_vibrato(int voice, int rate, int depth);
//--------------------------
//AUDIOSTREAM *play_audio_stream(int len, int bits, int stereo, int freq, int vol, int pan);
//void stop_audio_stream(AUDIOSTREAM *stream);
//void *get_audio_stream_buffer(AUDIOSTREAM *stream);
//void free_audio_stream_buffer(AUDIOSTREAM *stream);
//--------------------------
//int install_sound_input(int digi, int midi);
//void remove_sound_input();
//int get_sound_input_cap_bits();
//int get_sound_input_cap_stereo();
//int get_sound_input_cap_rate(int bits, int stereo);
//int get_sound_input_cap_parm(int rate, int bits, int stereo);
//int set_sound_input_source(int source);
//int start_sound_input(int rate, int bits, int stereo);
//void stop_sound_input();
//int read_sound_input(void *buffer);
//extern void (*digi_recorder)();
//extern void (*midi_recorder)(unsigned char data);
//--------------------------
//void get_executable_name(char *buf, int size);
//char *fix_filename_case(char *path);
//char *fix_filename_slashes(char *path);
//char *canonicalize_filename(char *dest, const char *filename, int size);
//char *make_absolute_filename(char *dest, const char *path, const char *filename, int size);
//char *make_relative_filename(char *dest, const char *path, const char *filename, int size);
//int is_relative_filename(const char *filename);
//char *replace_filename(char *dest, const char *path, const char *filename, int size);
//char *replace_extension(char *dest, const char *filename, const char *ext, int size);
//char *append_filename(char *dest, const char *path, const char *filename, int size);
//char *get_filename(const char *path);
//char *get_extension(const char *filename);
//void put_backslash(char *filename);
//void set_filename_encoding(int encoding)
//int get_filename_encoding(void)
//int file_exists(const char *filename, int attrib, int *aret);
//int exists(const char *filename);
//uint64_t file_size_ex(const char *filename);
//time_t file_time(const char *filename);
//int delete_file(const char *filename);
//int for_each_file_ex(const char *name, int in_attrib, int out_attrib, int (*callback)(const char *filename, int attrib, void *param), void *param);
//int al_findfirst(const char *pattern, struct al_ffblk *info, int attrib);
//int al_findnext(struct al_ffblk *info);
//void al_findclose(struct al_ffblk *info);
//uint64_t al_ffblk_get_size(struct al_ffblk *info);
//int find_allegro_resource(char *dest, const char *resource, const char *ext, const char *datafile, const char *objectname, const char *envvar, const char *subdir, int size);
//int set_allegro_resource_path(int priority, const char *path);
//void packfile_password(const char *password);
//PACKFILE *pack_fopen(const char *filename, const char *mode);
//PACKFILE *pack_fopen_vtable(const PACKFILE_VTABLE *vtable, void *userdata);
//int pack_fclose(PACKFILE *f);
//int pack_fseek(PACKFILE *f, int offset);
//int pack_feof(PACKFILE *f);
//int pack_ferror(PACKFILE *f);
//int pack_getc(PACKFILE *f);
//int pack_ungetc(int c, PACKFILE *f);
//int pack_putc(int c, PACKFILE *f);
//int pack_igetw(PACKFILE *f);
//int pack_iputw(int c, PACKFILE *f);
//long pack_igetl(PACKFILE *f);
//long pack_iputl(long c, PACKFILE *f);
//int pack_mgetw(PACKFILE *f);
//int pack_mputw(int c, PACKFILE *f);
//long pack_mgetl(PACKFILE *f);
//long pack_mputl(long c, PACKFILE *f);
//long pack_fread(void *p, long n, PACKFILE *f);
//long pack_fwrite(const void *p, long n, PACKFILE *f);
//char *pack_fgets(char *p, int max, PACKFILE *f);
//int pack_fputs(const char *p, PACKFILE *f);
//PACKFILE *pack_fopen_chunk(PACKFILE *f, int pack);
//PACKFILE *pack_fclose_chunk(PACKFILE *f);
//LZSS_PACK_DATA *create_lzss_pack_data(void);
//void free_lzss_pack_data(LZSS_PACK_DATA *dat);
//int lzss_write(PACKFILE *file, LZSS_PACK_DATA *dat, int size, unsigned char *buf, int last);
//LZSS_UNPACK_DATA *create_lzss_unpack_data(void);
//void free_lzss_unpack_data(LZSS_UNPACK_DATA *dat);
//int lzss_read(PACKFILE *file, LZSS_UNPACK_DATA *dat, int s, unsigned char *buf);
//--------------------------
//DATAFILE *load_datafile(const char *filename);
//DATAFILE *load_datafile_callback(const char *filename, void (*callback)(DATAFILE *d));
//void unload_datafile(DATAFILE *dat);
//DATAFILE *load_datafile_object(const char *filename, const char *objectname);
//void unload_datafile_object(DATAFILE *dat);
//DATAFILE *find_datafile_object(const DATAFILE *dat, const char *objectname);
//DATAFILE_INDEX *create_datafile_index(const char *filename);
//DATAFILE *load_datafile_object_indexed(const DATAFILE_INDEX *index, int item)
//void destroy_datafile_index(DATAFILE_INDEX *index)
//const char *get_datafile_property(const DATAFILE *dat, int type);
//void register_datafile_object(int id, void *(*load)(PACKFILE *f, long size), void (*destroy)(void *data));
//void fixup_datafile(DATAFILE *data);
//Macro DAT_ID(a, b, c, d);
//--------------------------
//fixed itofix(int x);
//int fixtoi(fixed x);
//int fixfloor(fixed x);
//int fixceil(fixed x);
//fixed ftofix(double x);
//double fixtof(fixed x);
//fixed fixmul(fixed x, fixed y);
//fixed fixdiv(fixed x, fixed y);
//fixed fixadd(fixed x, fixed y);
//fixed fixsub(fixed x, fixed y);
//extern const fixed fixtorad_r;
//extern const fixed radtofix_r;
//fixed fixsin(fixed x);
//fixed fixcos(fixed x);
//fixed fixtan(fixed x);
//fixed fixasin(fixed x);
//fixed fixacos(fixed x);
//fixed fixatan(fixed x);
//fixed fixatan2(fixed y, fixed x);
//fixed fixsqrt(fixed x);
//fixed fixhypot(fixed x, fixed y);
//--------------------------
//extern MATRIX identity_matrix;
//extern MATRIX_f identity_matrix_f;
//void get_translation_matrix(MATRIX *m, fixed x, fixed y, fixed z);
//void get_translation_matrix_f(MATRIX_f *m, float x, float y, float z);
//void get_scaling_matrix(MATRIX *m, fixed x, fixed y, fixed z);
//void get_scaling_matrix_f(MATRIX_f *m, float x, float y, float z);
//void get_x_rotate_matrix(MATRIX *m, fixed r);
//void get_x_rotate_matrix_f(MATRIX_f *m, float r);
//void get_y_rotate_matrix(MATRIX *m, fixed r);
//void get_y_rotate_matrix_f(MATRIX_f *m, float r);
//void get_z_rotate_matrix(MATRIX *m, fixed r);
//void get_z_rotate_matrix_f(MATRIX_f *m, float r);
//void get_rotation_matrix(MATRIX *m, fixed x, fixed y, fixed z);
//void get_rotation_matrix_f(MATRIX_f *m, float x, float y, float z);
//void get_align_matrix(MATRIX *m, fixed xfront, yfront, zfront, fixed xup, fixed yup, fixed zup);
//void get_align_matrix_f(MATRIX *m, float xfront, yfront, zfront, float xup, yup, zup);
//void get_vector_rotation_matrix(MATRIX *m, fixed x, y, z, fixed a);
//void get_vector_rotation_matrix_f(MATRIX_f *m, float x, y, z, float a);
//void get_transformation_matrix(MATRIX *m, fixed scale, fixed xrot, yrot, zrot, x, y, z);
//void get_transformation_matrix_f(MATRIX_f *m, float scale, float xrot, yrot, zrot, x, y, z);
//void get_camera_matrix(MATRIX *m, fixed x, y, z, xfront, yfront, zfront, fixed xup, yup, zup, fov, aspect);
//void get_camera_matrix_f(MATRIX_f *m, float x, y, z, xfront, yfront, zfront, float xup, yup, zup, fov, aspect);
//void qtranslate_matrix(MATRIX *m, fixed x, fixed y, fixed z);
//void qtranslate_matrix_f(MATRIX_f *m, float x, float y, float z);
//void qscale_matrix(MATRIX *m, fixed scale);
//void qscale_matrix_f(MATRIX_f *m, float scale);
//void matrix_mul(const MATRIX *m1, const MATRIX *m2, MATRIX *out);
//void matrix_mul_f(const MATRIX_f *m1, const MATRIX_f *m2, MATRIX_f *out);
//fixed vector_length(fixed x, fixed y, fixed z);
//float vector_length_f(float x, float y, float z);
//void normalize_vector(fixed *x, fixed *y, fixed *z);
//void normalize_vector_f(float *x, float *y, float *z);
//fixed dot_product(fixed x1, y1, z1, x2, y2, z2);
//float dot_product_f(float x1, y1, z1, x2, y2, z2);
//void cross_product(fixed x1, y1, z1, x2, y2, z2, *xout, *yout, *zout);
//void cross_product_f(float x1, y1, z1, x2, y2, z2, *xout, *yout, *zout);
//fixed polygon_z_normal(const V3D *v1, const V3D *v2, const V3D *v3);
//float polygon_z_normal_f(const V3D_f *v1, const V3D_f *v2, const V3D_f *v3);
//void apply_matrix(const MATRIX *m, fixed x, y, z, *xout, *yout, *zout);
//void apply_matrix_f(const MATRIX_f *m, float x, y, z, *xout, *yout, *zout);
//void set_projection_viewport(int x, int y, int w, int h);
//void persp_project(fixed x, fixed y, fixed z, fixed *xout, fixed *yout);
//void persp_project_f(float x, float y, float z, float *xout, float *yout);
//--------------------------
//extern QUAT identity_quat;
//void get_x_rotate_quat(QUAT *q, float r);
//void get_y_rotate_quat(QUAT *q, float r);
//void get_z_rotate_quat(QUAT *q, float r);
//void get_rotation_quat(QUAT *q, float x, float y, float z);
//void get_vector_rotation_quat(QUAT *q, float x, y, z, float a);
//void quat_to_matrix(const QUAT *q, MATRIX_f *m);
//void matrix_to_quat(const MATRIX_f *m, QUAT *q);
//void quat_mul(const QUAT *p, const QUAT *q, QUAT *out);
//void apply_quat(const QUAT *q, float x, y, z, *xout, *yout, *zout);
//void quat_interpolate(const QUAT *from, const QUAT *to, float t, QUAT *out);
//void quat_slerp(const QUAT *from, const QUAT *to, float t, QUAT *out, int how);
//--------------------------
//int d_clear_proc(int msg, DIALOG *d, int c);
//int d_box_proc(int msg, DIALOG *d, int c);
//int d_shadow_box_proc(int msg, DIALOG *d, int c);
//int d_bitmap_proc(int msg, DIALOG *d, int c);
//int d_text_proc(int msg, DIALOG *d, int c);
//int d_ctext_proc(int msg, DIALOG *d, int c);
//int d_rtext_proc(int msg, DIALOG *d, int c);
//int d_button_proc(int msg, DIALOG *d, int c);
//int d_check_proc(int msg, DIALOG *d, int c);
//int d_radio_proc(int msg, DIALOG *d, int c);
//int d_icon_proc(int msg, DIALOG *d, int c);
//int d_keyboard_proc(int msg, DIALOG *d, int c);
//int d_edit_proc(int msg, DIALOG *d, int c);
//int d_list_proc(int msg, DIALOG *d, int c);
//int d_text_list_proc(int msg, DIALOG *d, int c);
//int d_textbox_proc(int msg, DIALOG *d, int c);
//int d_slider_proc(int msg, DIALOG *d, int c);
//int d_menu_proc(int msg, DIALOG *d, int c);
//int d_yield_proc(int msg, DIALOG *d, int c);
//extern int gui_mouse_focus;
//extern int gui_fg_color;
//extern int gui_bg_color;
//extern int gui_mg_color;
//extern int gui_font_baseline;
//extern int (*gui_mouse_x)();
//extern int (*gui_mouse_y)();
//extern int (*gui_mouse_z)();
//extern int (*gui_mouse_b)();
//int gui_textout_ex(BITMAP *bmp, const char *s, int x, y, color, bg, centre);
//int gui_strlen(const char *s);
//void gui_set_screen(BITMAP *bmp);
//BITMAP *gui_get_screen(void);
//void position_dialog(DIALOG *dialog, int x, int y);
//void centre_dialog(DIALOG *dialog);
//void set_dialog_color(DIALOG *dialog, int fg, int bg);
//int find_dialog_focus(DIALOG *dialog);
//int offer_focus(DIALOG *dialog, int obj, int *focus_obj, int force);
//int object_message(DIALOG *dialog, int msg, int c);
//int dialog_message(DIALOG *dialog, int msg, int c, int *obj);
//int broadcast_dialog_message(int msg, int c);
//int do_dialog(DIALOG *dialog, int focus_obj);
//int popup_dialog(DIALOG *dialog, int focus_obj);
//DIALOG_PLAYER *init_dialog(DIALOG *dialog, int focus_obj);
//int update_dialog(DIALOG_PLAYER *player);
//int shutdown_dialog(DIALOG_PLAYER *player);
//extern DIALOG *active_dialog;
//int do_menu(MENU *menu, int x, int y);
//MENU_PLAYER *init_menu(MENU *menu, int x, int y);
//int update_menu(MENU_PLAYER *player);
//int shutdown_menu(MENU_PLAYER *player);
//extern MENU *active_menu;
//extern void (*gui_menu_draw_menu)(int x, int y, int w, int h);
//extern void (*gui_menu_draw_menu_item)(MENU *m, int x, int y, int w, int h, int bar, int sel);
//int alert(const char *s1, *s2, *s3, const char *b1, *b2, int c1, c2);
//int alert3(const char *s1, *s2, *s3, const char *b1, *b2, *b3, int c1, c2, c3);
//int file_select_ex(const char *message, char *path, const char *ext, int size, int w, int h);
//int gfx_mode_select(int *card, int *w, int *h);
//int gfx_mode_select_ex(int *card, int *w, int *h, int *color_depth);
//int gfx_mode_select_filter(int *card, int *w, int *h, int *color_depth, int (*filter)(int, int, int, int));
//extern int (*gui_shadow_box_proc)(int msg, struct DIALOG *d, int c);
//extern int (*gui_shadow_box_proc)(int msg, struct DIALOG *d, int c);
//extern int (*gui_ctext_proc)(int msg, struct DIALOG *d, int c);
//extern int (*gui_button_proc)(int msg, struct DIALOG *d, int c);
//extern int (*gui_edit_proc)(int msg, struct DIALOG *d, int c);
//extern int (*gui_list_proc)(int msg, struct DIALOG *d, int c);
//extern int (*gui_text_list_proc)(int msg, struct DIALOG *d, int c);
//--------------------------
//extern int i_love_bill;
//--------------------------
//HWND win_get_window(void);
//void win_set_window(HWND wnd);
//void win_set_wnd_create_proc(HWND (*proc)(WNDPROC));
//HDC win_get_dc(BITMAP *bmp);
//void win_release_dc(BITMAP *bmp, HDC dc);
//void win_set_msg_pre_proc(int (*proc)(HWND, UINT, WPARAM, LPARAM, int *retval));
//void set_gdi_color_format(void);
//void set_palette_to_hdc(HDC dc, PALETTE pal);
//HPALETTE convert_palette_to_hpalette(PALETTE pal);
//void convert_hpalette_to_palette(HPALETTE hpal, PALETTE pal);
//HBITMAP convert_bitmap_to_hbitmap(BITMAP *bitmap);
//BITMAP *convert_hbitmap_to_bitmap(HBITMAP bitmap);
//void draw_to_hdc(HDC dc, BITMAP *bitmap, int x, int y);
//void blit_to_hdc(BITMAP *bitmap, HDC dc, int sx, sy, dx, dy, w, h);
//void stretch_blit_to_hdc(BITMAP *bitmap, HDC dc, int sx, sy, sw, sh, int dx, dy, dw, dh);
//void blit_from_hdc(HDC hdc, BITMAP *bitmap, int sx, sy, dx, dy, w, h);
//void stretch_blit_from_hdc(HDC hcd, BITMAP *bitmap, int sx, sy, sw, sh, int dx, dy, dw, dh);
//--------------------------
//void xwin_set_window_name(const char *name, const char *group);
//extern void *allegro_icon;
//--------------------------
//PtWidget_t qnx_get_window(void);
//--------------------------
//void ASSERT(condition);
//void TRACE(char *msg, ...);
//void register_assert_handler(int (*handler)(const char *msg));
//void register_trace_handler(int (*handler)(const char *msg));
//void al_assert(const char *file, int line);
//void al_trace(const char *msg, ...);
//--------------------------
//--------------------------
static duk_ret_t native_pivot_scaled_sprite_v_flip(duk_context *ctx){
	pivot_scaled_sprite_v_flip(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),//float???
		duk_to_int(ctx,5),//float???
		duk_to_int(ctx,6),//float???
		duk_to_int(ctx,7)//float???
	);
	return 0;
}
static duk_ret_t native_pivot_scaled_sprite(duk_context *ctx){
	pivot_scaled_sprite(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),//float???
		duk_to_int(ctx,5),//float???
		duk_to_int(ctx,6),//float???
		duk_to_int(ctx,7)//float???
	);
	return 0;
}
static duk_ret_t native_pivot_sprite_v_flip(duk_context *ctx){
	pivot_sprite_v_flip(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),//float???
		duk_to_int(ctx,5),//float???
		duk_to_int(ctx,6)//float???
	);
	return 0;
}
static duk_ret_t native_pivot_sprite(duk_context *ctx){
	pivot_sprite(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),//float???
		duk_to_int(ctx,5),//float???
		duk_to_int(ctx,6)//float???
	);
	return 0;
}
static duk_ret_t native_rotate_scaled_sprite_v_flip(duk_context *ctx){
	rotate_scaled_sprite_v_flip(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),//float???
		duk_to_int(ctx,5)//float???
	);
	return 0;
}
static duk_ret_t native_rotate_scaled_sprite(duk_context *ctx){
	rotate_scaled_sprite(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),//float???
		duk_to_int(ctx,5)//float???
	);
	return 0;
}
static duk_ret_t native_rotate_sprite(duk_context *ctx){
	rotate_sprite(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4)//float???
	);
	return 0;
}
static duk_ret_t native_rotate_sprite_v_flip(duk_context *ctx){
	rotate_sprite_v_flip(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4)//float???
	);
	return 0;
}
static duk_ret_t native_draw_character_ex(duk_context *ctx){
	draw_character_ex(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5)
	);
	return 0;
}
static duk_ret_t native_draw_lit_sprite(duk_context *ctx){
	draw_lit_sprite(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4)
	);
	return 0;
}
static duk_ret_t native_draw_gouraud_sprite(duk_context *ctx){
	draw_gouraud_sprite(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5),
		duk_to_int(ctx,6),
		duk_to_int(ctx,7)
	);
	return 0;
}
static duk_ret_t native_draw_trans_sprite(duk_context *ctx){
	draw_trans_sprite(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native_draw_sprite_v_flip(duk_context *ctx){
	draw_sprite_h_flip(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native_draw_sprite_h_flip(duk_context *ctx){
	draw_sprite_h_flip(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native_draw_sprite_vh_flip(duk_context *ctx){
	draw_sprite_vh_flip(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native_draw_sprite(duk_context *ctx){
	draw_sprite(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native_stretch_sprite(duk_context *ctx){
	stretch_sprite(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5)
	);
	return 0;
}
static duk_ret_t native_load_bitmap(duk_context *ctx){
	BITMAP *buffer = NULL;
	buffer = load_bitmap(
		duk_to_string(ctx,0),
		(RGB*)duk_to_pointer(ctx,1)
	);
	duk_push_pointer(ctx, buffer);
	return 1;
}
static duk_ret_t native_load_png(duk_context *ctx){
	BITMAP *buffer = NULL;
	buffer = load_png(
		duk_to_string(ctx,0),
		(RGB*)duk_to_pointer(ctx,1)
	);
	duk_push_pointer(ctx, buffer);
	return 1;
}
static duk_ret_t native_create_bitmap(duk_context *ctx){
	BITMAP *buffer = NULL;
	buffer = create_bitmap(
		duk_to_int(ctx,0),
		duk_to_int(ctx,1)
	);
	duk_push_pointer(ctx, buffer);
	return 1;
}
static duk_ret_t native_destroy_bitmap(duk_context *ctx){
	destroy_bitmap((BITMAP*)duk_to_pointer(ctx,0));
	return 0;
}
static duk_ret_t native_clear_bitmap(duk_context *ctx){
	clear_bitmap(
		(BITMAP*)duk_to_pointer(ctx,0)
	);
	return 0;
}

static duk_ret_t native_clear(duk_context *ctx){
	clear(
		(BITMAP*)duk_to_pointer(ctx,0)
	);
	return 0;
}
static duk_ret_t native_clear_to_color(duk_context *ctx){
	clear_to_color(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1)
	);
	return 0;
}

static duk_ret_t native_stretch_blit(duk_context *ctx){
	stretch_blit(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5),
		duk_to_int(ctx,6),
		duk_to_int(ctx,7),
		duk_to_int(ctx,8),
		duk_to_int(ctx,9)
	);
	return 0;
}
static duk_ret_t native_blit(duk_context *ctx){
	blit(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5),
		duk_to_int(ctx,6),
		duk_to_int(ctx,7)
	);
	return 0;
}
static duk_ret_t native_masked_stretch_blit(duk_context *ctx){
	masked_stretch_blit(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5),
		duk_to_int(ctx,6),
		duk_to_int(ctx,7),
		duk_to_int(ctx,8),
		duk_to_int(ctx,9)
	);
	return 0;
}
static duk_ret_t native_masked_blit(duk_context *ctx){
	masked_blit(
		(BITMAP*)duk_to_pointer(ctx,0),
		(BITMAP*)duk_to_pointer(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5),
		duk_to_int(ctx,6),
		duk_to_int(ctx,7)
	);
	return 0;
}
static duk_ret_t native_test(duk_context *ctx){
	duk_push_number(ctx,duk_to_int(ctx,0));
	return 1;
}
static duk_ret_t native_abort(duk_context *ctx){
	abort();
	return 0;
}
static duk_ret_t native_exit(duk_context *ctx){
	exit(
		duk_to_int(ctx,0)
	);
	return 0;
}
static duk_ret_t native_set_leds(duk_context *ctx){
	set_leds(
		duk_to_int(ctx,0)
	);
	return 0;
}

static duk_ret_t native_install_keyboard(duk_context *ctx){
	install_keyboard();
	return 0;
}
static duk_ret_t native_install_timer(duk_context *ctx){
	install_timer();
	return 0;
}
static duk_ret_t native_remove_keyboard(duk_context *ctx){
	remove_keyboard();
	return 0;
}
/* function pointers???
static duk_ret_t native_remove_keyboard(duk_context *ctx){
	//void install_keyboard_hooks(int (*keypressed)(), int (*readkey)());
	install_keyboard_hooks(
		duk_to_int(ctx,0)
	);
	return 0;
}
*/
static duk_ret_t native_poll_keyboard(duk_context *ctx){
	duk_push_int(ctx,poll_keyboard());
	return 1;
}
static duk_ret_t native_keyboard_needs_poll(duk_context *ctx){
	duk_push_int(ctx,keyboard_needs_poll());
	return 1;
}
static duk_ret_t native_set_color_depth(duk_context *ctx){
	set_color_depth(duk_to_int(ctx,0));
	return 0;
}
static duk_ret_t native_set_gfx_mode(duk_context *ctx){
	set_gfx_mode(
		duk_to_int(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4)
	);
	duk_push_pointer(ctx, screen);
	duk_put_global_string(ctx,"screen");
	duk_push_pointer(ctx, font);
	duk_put_global_string(ctx,"font");
	return 0;
}
static duk_ret_t native_install_sound(duk_context *ctx){
	duk_push_int(
		ctx,
		install_sound(
			duk_to_int(ctx,0),
			duk_to_int(ctx,1),
			NULL//???
		)
	);
	return 1;
}
static duk_ret_t native_load_midi(duk_context *ctx){
	duk_push_pointer(
		ctx,
		load_midi(
			duk_to_string(ctx,0)
		)
	);
	return 1;
}
//----------------------------------------------------------
//from here...
static duk_ret_t native_lock_midi(duk_context *ctx){
	//void lock_midi(MIDI *midi);
	lock_midi(
		(MIDI*)duk_to_pointer(ctx,0)
	);
	return 0;
}
static duk_ret_t native_play_midi(duk_context *ctx){
	//int play_midi(MIDI *midi, int loop);
	duk_push_int(
		ctx,
		play_midi(
			(MIDI*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	return 1;
}
static duk_ret_t native_play_looped_midi(duk_context *ctx){
	//int play_looped_midi(MIDI *midi, int loop_start, int loop_end);
	duk_push_int(
		ctx,
		play_looped_midi(
			(MIDI*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
static duk_ret_t native_stop_midi(duk_context *ctx){
	//void stop_midi();
	stop_midi(
	);
	return 0;
}
static duk_ret_t native_midi_pause(duk_context *ctx){
	//void midi_pause();
	midi_pause(
	);
	return 0;
}
static duk_ret_t native_midi_resume(duk_context *ctx){
	//void midi_resume();
	midi_resume(
	);
	return 0;
}
static duk_ret_t native_midi_seek(duk_context *ctx){
	//int midi_seek(int target);
	duk_push_int(
		ctx,
		midi_seek(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
static duk_ret_t native_get_midi_length(duk_context *ctx){
	//int get_midi_length(MIDI *midi);
	duk_push_int(
		ctx,
		get_midi_length(
			(MIDI*)duk_to_pointer(ctx,0)
		)
	);
	return 1;
}
static duk_ret_t native_midi_out(duk_context *ctx){
	//void midi_out(unsigned char *data, int length);
	midi_out(
		(unsigned char*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1)
	);
	return 0;
}
static duk_ret_t native_load_midi_patches(duk_context *ctx){
	//int load_midi_patches();
	duk_push_int(
		ctx,
		load_midi_patches(
		)
	);
	return 1;
}
//extern volatile long midi_pos; ???
//extern volatile long midi_time; ???
//extern long midi_loop_start; ???
//extern long midi_loop_end; ???
//extern void (*midi_msg_callback)(int msg, int byte1, int byte2); ???
//extern void (*midi_meta_callback)(int type, const unsigned char *data, int length); ???
//extern void (*midi_sysex_callback)(const unsigned char *data, int length); ???
static duk_ret_t native_load_ibk(duk_context *ctx){
	//int load_ibk(char *filename, int drums);
	duk_push_int(
		ctx,
		load_ibk(
			duk_to_string(ctx,0),
			duk_to_int(ctx,1)
		)
	);
	return 1;
}
//...to here
//----------------------------------------------------------
static duk_ret_t native_destroy_midi(duk_context *ctx){
   	destroy_midi(
		duk_to_pointer(ctx,0)
	);
	return 0;
}
static duk_ret_t native_keypressed(duk_context *ctx){
	duk_push_number(ctx,keypressed());
	return 1;
}
static duk_ret_t native_getkey(duk_context *ctx) {
	duk_push_number(ctx,getkey());
	return 1;
}
static duk_ret_t native_readkey(duk_context *ctx) {
	duk_push_number(ctx,readkey());
	return 1;
}
static duk_ret_t native_ureadkey(duk_context *ctx) {
	duk_push_number(
		ctx,
		ureadkey(
			(int*)duk_to_pointer(ctx,0)
		)
	);
	return 1;
}
static duk_ret_t native_scancode_to_ascii(duk_context *ctx) {
	duk_push_number(
		ctx,
		scancode_to_ascii(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
static duk_ret_t native_scancode_to_name(duk_context *ctx) {
	duk_push_pointer(
		ctx,
		scancode_to_name(
			duk_to_int(ctx,0)
		)
	);
	return 1;
}
static duk_ret_t native_simulate_keypress(duk_context *ctx) {
	simulate_keypress(
		duk_to_int(ctx,0)
	);
	return 0;
}
static duk_ret_t native_simulate_ukeypress(duk_context *ctx) {
	simulate_ukeypress(
		duk_to_int(ctx,0),
		duk_to_int(ctx,1)
	);
	return 0;
}
static duk_ret_t native_set_keyboard_rate(duk_context *ctx) {
	set_keyboard_rate(
		duk_to_int(ctx,0),
		duk_to_int(ctx,1)
	);
	return 0;
}
static duk_ret_t native_clear_keybuf(duk_context *ctx) {
	clear_keybuf();
	return 0;
}
//
//extern volatile char key[KEY_MAX];??? how to expose???
//extern volatile int key_shifts;
//
static duk_ret_t native_textout(duk_context *ctx) {
	text_mode(-1);
	textout(
		(BITMAP*)duk_to_pointer(ctx,0),
		(FONT*)duk_to_pointer(ctx,1),
		duk_to_string(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5)
	);
	return 0;
}

static duk_ret_t native_triangle(duk_context *ctx) {
	triangle(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5),
		duk_to_int(ctx,6),
		duk_to_int(ctx,7)
	);
	return 0;
}

static duk_ret_t native_polygon(duk_context *ctx) {
	//void polygon(BITMAP *bmp, int vertices, const int *points, int color);
	polygon(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_pointer(ctx,2),//??? send in array???///
		duk_to_int(ctx,3)
	);
	return 0;
}
/* ???
static duk_ret_t native_do_line(duk_context *ctx) {
	//void do_line(BITMAP *bmp, int x1, y1, x2, y2, int d, void (*proc)(BITMAP *bmp, int x, int y, int d));
	do_line(
		(BITMAP*)duk_to_pointer(ctx,0),
	);
	return 0;
}
*/
static duk_ret_t native_fastline(duk_context *ctx) {
	fastline(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5)
	);
	return 0;
}
static duk_ret_t native_vline(duk_context *ctx) {
	vline(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4)
	);
	return 0;
}
static duk_ret_t native_hline(duk_context *ctx) {
	hline(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4)
	);
	return 0;
}

static duk_ret_t native_line(duk_context *ctx) {
	line(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5)
	);
	return 0;
}
static duk_ret_t native_getpixel(duk_context *ctx) {
	duk_push_number(
		ctx,
		getpixel(
			(BITMAP*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
static duk_ret_t native__getpixel(duk_context *ctx) {
	duk_push_number(
		ctx,
		_getpixel(
			(BITMAP*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
static duk_ret_t native__getpixel15(duk_context *ctx) {
	duk_push_number(
		ctx,
		_getpixel15(
			(BITMAP*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
static duk_ret_t native__getpixel16(duk_context *ctx) {
	duk_push_number(
		ctx,
		_getpixel16(
			(BITMAP*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
static duk_ret_t native__getpixel24(duk_context *ctx) {
	duk_push_number(
		ctx,
		_getpixel24(
			(BITMAP*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
static duk_ret_t native__getpixel32(duk_context *ctx) {
	duk_push_number(
		ctx,
		_getpixel32(
			(BITMAP*)duk_to_pointer(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}

static duk_ret_t native_putpixel(duk_context *ctx) {
	putpixel(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}

static duk_ret_t native__putpixel(duk_context *ctx) {
	_putpixel(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native__putpixel15(duk_context *ctx) {
	putpixel(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native__putpixel16(duk_context *ctx) {
	putpixel(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native__putpixel24(duk_context *ctx) {
	putpixel(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native__putpixel32(duk_context *ctx) {
	putpixel(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
static duk_ret_t native_rect(duk_context *ctx) {
	rect(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5)
	);
	return 0;
}
static duk_ret_t native_rectfill(duk_context *ctx) {
	rectfill(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5)
	);
	return 0;
}
static duk_ret_t native_circle(duk_context *ctx) {
	circle(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4)
	);
	return 0;
}
static duk_ret_t native_circlefill(duk_context *ctx) {
	circlefill(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4)
	);
	return 0;
}
/* function pointer ???
static duk_ret_t native_do_circle(duk_context *ctx) {
	//void do_circle(BITMAP *bmp, int x, int y, int radius, int d, void (*proc)(BITMAP *bmp, int x, int y, int d));
	circlefill(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		makecol(
			duk_to_int(ctx,4),
			duk_to_int(ctx,5),
			duk_to_int(ctx,6)
		)
	);
	return 0;
}
*/
static duk_ret_t native_ellipse(duk_context *ctx) {
	ellipse(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5)
	);
	return 0;
}
static duk_ret_t native_ellipsefill(duk_context *ctx) {
	ellipsefill(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),
		duk_to_int(ctx,4),
		duk_to_int(ctx,5)
	);
	return 0;
}
static duk_ret_t native_makecol(duk_context *ctx) {
	duk_push_int(
		ctx,
		makecol(
			duk_to_int(ctx,0),
			duk_to_int(ctx,1),
			duk_to_int(ctx,2)
		)
	);
	return 1;
}
/* function pointer ???
static duk_ret_t native_ellipsefill(duk_context *ctx) {
	////void do_ellipse(BITMAP *bmp, int x, int y, int rx, ry, int d, void (*proc)(BITMAP *bmp, int x, int y, int d));
	ellipsefill(
		(BITMAP*)duk_to_pointer(ctx,0),
	);
	return 0;
}
*/
/* function pointer ???
static duk_ret_t native_do_arc(duk_context *ctx) {
	//void do_arc(BITMAP *bmp, int x, int y, fixed a1, fixed a2, int r, int d, void (*proc)(BITMAP *bmp, int x, int y, int d));
	do_arc(
		(BITMAP*)duk_to_pointer(ctx,0),
	);
	return 0;
}
*/
static duk_ret_t native_do_arc(duk_context *ctx) {
	arc(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3),//float???
		duk_to_int(ctx,4),//float???
		duk_to_int(ctx,5),
		duk_to_int(ctx,6)
	);
	return 0;
}
/* send array???
static duk_ret_t native_calc_spline(duk_context *ctx) {
	//void calc_spline(const int points[8], int npts, int *x, int *y);
	calc_spline(
		(BITMAP*)duk_to_pointer(ctx,0),
	);
	return 0;
}
*/
/* send array???
static duk_ret_t native_spline(duk_context *ctx) {
	//void spline(BITMAP *bmp, const int points[8], int color);
	spline(
		(BITMAP*)duk_to_pointer(ctx,0),
	);
	return 0;
}
*/
static duk_ret_t native_floodfill(duk_context *ctx) {
	floodfill(
		(BITMAP*)duk_to_pointer(ctx,0),
		duk_to_int(ctx,1),
		duk_to_int(ctx,2),
		duk_to_int(ctx,3)
	);
	return 0;
}
int main(int argc,char* argv[]){
	//duk::Context ctx;
	duk_context *ctx;
	ctx = duk_create_heap(NULL, NULL, NULL,NULL, my_fatal);
	duk_console_init(ctx,DUK_CONSOLE_PROXY_WRAPPER|DUK_CONSOLE_FLUSH);
	int a=0;
	duk_push_pointer(ctx, &a);
	duk_put_global_string(ctx,"a");
	duk_push_int(ctx, ALLEGRO_VERSION);
	duk_put_global_string(ctx,"ALLEGRO_VERSION");
	duk_push_int(ctx, ALLEGRO_SUB_VERSION);
	duk_put_global_string(ctx,"ALLEGRO_SUB_VERSION");
	duk_push_int(ctx, ALLEGRO_WIP_VERSION);
	duk_put_global_string(ctx,"ALLEGRO_WIP_VERSION");
	duk_push_string(ctx, ALLEGRO_DATE_STR);
	duk_put_global_string(ctx,"ALLEGRO_DATE_STR");
	duk_push_int(ctx, ALLEGRO_DATE);
	duk_put_global_string(ctx,"ALLEGRO_DATE");
	duk_push_string(ctx, allegro_id);
	duk_put_global_string(ctx,"allegro_id");
	duk_push_int(ctx, ALLEGRO_ERROR_SIZE);
	duk_put_global_string(ctx,"ALLEGRO_ERROR_SIZE");
	duk_push_string(ctx, allegro_error);
	duk_put_global_string(ctx,"allegro_error");
	duk_push_int(ctx, OSTYPE_UNKNOWN);
	duk_put_global_string(ctx,"OSTYPE_UNKNOWN");
	duk_push_int(ctx, OSTYPE_WIN3);
	duk_put_global_string(ctx,"OSTYPE_WIN3");
	duk_push_int(ctx, OSTYPE_WIN95);
	duk_put_global_string(ctx,"OSTYPE_WIN95");
	duk_push_int(ctx, OSTYPE_WIN98);
	duk_put_global_string(ctx,"OSTYPE_WIN98");
	duk_push_int(ctx, OSTYPE_WINME);
	duk_put_global_string(ctx,"OSTYPE_WINME");
	duk_push_int(ctx, OSTYPE_WINNT);
	duk_put_global_string(ctx,"OSTYPE_WINNT");
	duk_push_int(ctx, OSTYPE_WIN2000);
	duk_put_global_string(ctx,"OSTYPE_WIN2000");
	duk_push_int(ctx, OSTYPE_WINXP);
	duk_put_global_string(ctx,"OSTYPE_WINXP");
	duk_push_int(ctx, OSTYPE_WIN2003);
	duk_put_global_string(ctx,"OSTYPE_WIN2003");
	duk_push_int(ctx, OSTYPE_WINVISTA);
	duk_put_global_string(ctx,"OSTYPE_WINVISTA");
	duk_push_int(ctx, OSTYPE_OS2);
	duk_put_global_string(ctx,"OSTYPE_OS2");
	duk_push_int(ctx, OSTYPE_WARP);
	duk_put_global_string(ctx,"");
	duk_push_int(ctx, OSTYPE_DOSEMU);
	duk_put_global_string(ctx,"");
	duk_push_int(ctx, OSTYPE_OPENDOS);
	duk_put_global_string(ctx,"OSTYPE_OPENDOS");
	duk_push_int(ctx, OSTYPE_LINUX);
	duk_put_global_string(ctx,"");
	duk_push_int(ctx, OSTYPE_SUNOS);
	duk_put_global_string(ctx,"OSTYPE_SUNOS");
	duk_push_int(ctx, OSTYPE_FREEBSD);
	duk_put_global_string(ctx,"OSTYPE_FREEBSD");
	duk_push_int(ctx, OSTYPE_NETBSD);
	duk_put_global_string(ctx,"OSTYPE_NETBSD");
	duk_push_int(ctx, OSTYPE_IRIX);
	duk_put_global_string(ctx,"OSTYPE_IRIX");
	duk_push_int(ctx, OSTYPE_DARWIN);
	duk_put_global_string(ctx,"OSTYPE_DARWIN");
	duk_push_int(ctx, OSTYPE_QNX);
	duk_put_global_string(ctx,"OSTYPE_QNX");
	duk_push_int(ctx, OSTYPE_UNIX);
	duk_put_global_string(ctx,"OSTYPE_UNIX");
	duk_push_int(ctx, OSTYPE_BEOS);
	duk_put_global_string(ctx,"");
	duk_push_int(ctx, OSTYPE_MACOS);
	duk_put_global_string(ctx,"");
	duk_push_int(ctx, OSTYPE_MACOSX);
	duk_put_global_string(ctx,"OSTYPE_MACOSX");
	duk_push_int(ctx, os_type);
	duk_put_global_string(ctx,"os_type");
	duk_push_int(ctx, os_version);
	duk_put_global_string(ctx,"os_version");
	duk_push_int(ctx, os_revision);
	duk_put_global_string(ctx,"os_revision");
	duk_push_int(ctx, os_multitasking);
	duk_put_global_string(ctx,"os_multitasking");


	duk_push_string(ctx,cpu_vendor);
	duk_put_global_string(ctx,"cpu_vendor");
	duk_push_int(ctx,cpu_family);
	duk_put_global_string(ctx,"cpu_family");
	duk_push_int(ctx,cpu_model);
	duk_put_global_string(ctx,"cpu_model");
	duk_push_int(ctx,cpu_capabilities);
	duk_put_global_string(ctx,"cpu_capabilities");
		//see include/allegro/system.h for more for the below families
	duk_push_int(ctx,CPU_FAMILY_UNKNOWN);
	duk_put_global_string(ctx,"CPU_FAMILY_UNKNOWN");
	duk_push_int(ctx,CPU_FAMILY_I386);
	duk_put_global_string(ctx,"CPU_FAMILY_I386");
	duk_push_int(ctx,CPU_FAMILY_I486);
	duk_put_global_string(ctx,"CPU_FAMILY_I486");
	duk_push_int(ctx,CPU_FAMILY_I586);
	duk_put_global_string(ctx,"CPU_FAMILY_I586");
	duk_push_int(ctx,CPU_FAMILY_I686);
	duk_put_global_string(ctx,"CPU_FAMILY_I686");
	duk_push_int(ctx,CPU_FAMILY_ITANIUM);
	duk_put_global_string(ctx,"CPU_FAMILY_ITANIUM");
	duk_push_int(ctx,CPU_FAMILY_POWERPC);
	duk_put_global_string(ctx,"CPU_FAMILY_POWERPC");
	duk_push_int(ctx,CPU_FAMILY_EXTENDED);
	duk_put_global_string(ctx,"CPU_FAMILY_EXTENDED");

	duk_push_c_function(ctx, native_allegro_init, 0);
	duk_put_global_string(ctx,"allegro_init");
	duk_push_c_function(ctx, native_allegro_exit, 0);
	duk_put_global_string(ctx,"allegro_exit");

	duk_push_c_function(ctx, native_allegro_message, 1);
	duk_put_global_string(ctx,"allegro_message");
	duk_push_c_function(ctx, native_set_window_title, 1);
	duk_put_global_string(ctx,"set_window_title");
	duk_push_c_function(ctx, native_desktop_color_depth, 0);
	duk_put_global_string(ctx,"desktop_color_depth");
	duk_push_c_function(ctx, native_get_desktop_resolution,2);
	duk_put_global_string(ctx,"get_desktop_resolution");
	duk_push_c_function(ctx, native_check_cpu,0);
	duk_put_global_string(ctx,"check_cpu");
	duk_push_c_function(ctx, native_set_uformat,1);
	duk_put_global_string(ctx,"set_uformat");
	duk_push_c_function(ctx, native_set_ucodepage,2);
	duk_put_global_string(ctx,"set_ucodepage");
	duk_push_c_function(ctx, native_need_uconvert,3);
	duk_put_global_string(ctx,"need_uconvert");
	duk_push_c_function(ctx, native_uconvert_size,5);
	duk_put_global_string(ctx,"uconvert_size");
	duk_push_c_function(ctx, native_do_uconvert,5);
	duk_put_global_string(ctx,"do_uconvert");
	duk_push_c_function(ctx, native_uconvert,5);
	duk_put_global_string(ctx,"uconvert");
	duk_push_c_function(ctx, native_uconvert_ascii,2);
	duk_put_global_string(ctx,"uconvert_ascii");
	duk_push_c_function(ctx, native_uconvert_toascii,2);
	duk_put_global_string(ctx,"uconvert_toascii");
	duk_push_string(ctx, empty_string);
	duk_put_global_string(ctx,"empty_string");
	duk_push_c_function(ctx, native_ugetc,1);
	duk_put_global_string(ctx,"ugetc");
	duk_push_c_function(ctx, native_ugetx,1);
	duk_put_global_string(ctx,"ugetx");
	duk_push_c_function(ctx, native_ugetxc,1);
	duk_put_global_string(ctx,"ugetxc");
	duk_push_c_function(ctx, native_usetc,2);
	duk_put_global_string(ctx,"usetc");
	duk_push_c_function(ctx, native_uwidth,1);
	duk_put_global_string(ctx,"uwidth");
	duk_push_c_function(ctx, native_ucwidth,1);
	duk_put_global_string(ctx,"ucwidth");
	duk_push_c_function(ctx, native_uisok,1);
	duk_put_global_string(ctx,"uisok");
	duk_push_c_function(ctx, native_uoffset,2);
	duk_put_global_string(ctx,"uoffset");
	duk_push_c_function(ctx, native_ugetat,2);
	duk_put_global_string(ctx,"ugetat");
	duk_push_c_function(ctx, native_usetat,3);
	duk_put_global_string(ctx,"usetat");
	duk_push_c_function(ctx, native_uinsert,3);
	duk_put_global_string(ctx,"uinsert");
	duk_push_c_function(ctx, native_uremove,2);
	duk_put_global_string(ctx,"uremove");
	duk_push_c_function(ctx, native_ustrsize,1);
	duk_put_global_string(ctx,"ustrsize");
	duk_push_c_function(ctx, native_ustrsizez,1);
	duk_put_global_string(ctx,"ustrsizez");
	duk_push_c_function(ctx, native_uwidth_max,1);
	duk_put_global_string(ctx,"uwidth_max");
	duk_push_c_function(ctx, native_utolower,1);
	duk_put_global_string(ctx,"utolower");
	duk_push_c_function(ctx, native_utoupper,1);
	duk_put_global_string(ctx,"utoupper");
	duk_push_c_function(ctx, native_uisspace,1);
	duk_put_global_string(ctx,"uisspace");
	duk_push_c_function(ctx, native_uisdigit,1);
	duk_put_global_string(ctx,"uisdigit");
	duk_push_c_function(ctx, native_ustrdup,1);
	duk_put_global_string(ctx,"ustrdup");
	duk_push_c_function(ctx, native__ustrdup,2);
	duk_put_global_string(ctx,"_ustrdup");
	duk_push_c_function(ctx, native_ustrcpy,2);
	duk_put_global_string(ctx,"ustrcpy");
	duk_push_c_function(ctx, native_ustrzcpy,3);
	duk_put_global_string(ctx,"ustrzcpy");
	duk_push_c_function(ctx, native_ustrcat,2);
	duk_put_global_string(ctx,"ustrcat");
	duk_push_c_function(ctx, native_ustrzcat,3);
	duk_put_global_string(ctx,"ustrzcat");
	duk_push_c_function(ctx, native_ustrlen,1);
	duk_put_global_string(ctx,"ustrlen");
	duk_push_c_function(ctx, native_ustrcmp,2);
	duk_put_global_string(ctx,"ustrcmp");
	duk_push_c_function(ctx, native_ustrncpy,3);
	duk_put_global_string(ctx,"ustrncpy");
	duk_push_c_function(ctx, native_ustrzncpy,4);
	duk_put_global_string(ctx,"ustrzncpy");
	duk_push_c_function(ctx, native_ustrncat,2);
	duk_put_global_string(ctx,"ustrzncpy");
	duk_push_c_function(ctx, native_ustrzncat,4);
	duk_put_global_string(ctx,"ustrncat");
	duk_push_c_function(ctx, native_ustrncmp,3);
	duk_put_global_string(ctx,"ustrncmp");
	duk_push_c_function(ctx, native_ustricmp,2);
	duk_put_global_string(ctx,"ustrncmp");
	duk_push_c_function(ctx, native_ustrnicmp,3);
	duk_put_global_string(ctx,"ustricmp");
	duk_push_c_function(ctx, native_ustrlwr,1);
	duk_put_global_string(ctx,"ustrnicmp");
	duk_push_c_function(ctx, native_ustrupr,1);
	duk_put_global_string(ctx,"ustrupr");
	duk_push_c_function(ctx, native_ustrchr,2);
	duk_put_global_string(ctx,"ustrchr");
	duk_push_c_function(ctx, native_ustrrchr,2);
	duk_put_global_string(ctx,"ustrrchr");
	duk_push_c_function(ctx, native_ustrstr,2);
	duk_put_global_string(ctx,"ustrstr");
	duk_push_c_function(ctx, native_ustrpbrk,2);
	duk_put_global_string(ctx,"ustrpbrk");
	duk_push_c_function(ctx, native_ustrtok,2);
	duk_put_global_string(ctx,"ustrtok");
	duk_push_c_function(ctx, native_ustrtok_r,3);
	duk_put_global_string(ctx,"ustrtok_r");
	duk_push_c_function(ctx, native_ustrtok_r,1);
	duk_put_global_string(ctx,"uatof");
	duk_push_c_function(ctx, native_ustrtol,3);
	duk_put_global_string(ctx,"ustrtok_r");
	duk_push_c_function(ctx, native_ustrtod,3);
	duk_put_global_string(ctx,"ustrtod");
	duk_push_c_function(ctx, native_ustrerror,1);
	duk_put_global_string(ctx,"ustrerror");
	duk_push_c_function(ctx, native_usprintf,2);
	duk_put_global_string(ctx,"usprintf");
	duk_push_c_function(ctx, native_uszprintf,3);
	duk_put_global_string(ctx,"uszprintf");
	duk_push_c_function(ctx, native_uvsprintf,3);
	duk_put_global_string(ctx,"uvsprintf");
	duk_push_c_function(ctx, native_uvszprintf,3);
	duk_put_global_string(ctx,"uvszprintf");
	duk_push_c_function(ctx, native_set_config_file,1);
	duk_put_global_string(ctx,"set_config_file");
	duk_push_c_function(ctx, native_set_config_data,2);
	duk_put_global_string(ctx,"set_config_data");
	duk_push_c_function(ctx, native_override_config_file,1);
	duk_put_global_string(ctx,"override_config_file");
	duk_push_c_function(ctx, native_override_config_data,2);
	duk_put_global_string(ctx,"override_config_data");
	duk_push_c_function(ctx, native_push_config_state,0);
	duk_put_global_string(ctx,"push_config_state");
	duk_push_c_function(ctx, native_pop_config_state,0);
	duk_put_global_string(ctx,"pop_config_state");
	duk_push_c_function(ctx, native_flush_config_file,0);
	duk_put_global_string(ctx,"flush_config_file");
	duk_push_c_function(ctx, native_reload_config_texts,1);
	duk_put_global_string(ctx,"reload_config_texts");
	duk_push_c_function(ctx, native_hook_config_section,4);
	duk_put_global_string(ctx,"hook_config_section");
	duk_push_c_function(ctx, native_config_is_hooked,1);
	duk_put_global_string(ctx,"native_config_is_hooked");
	duk_push_c_function(ctx, native_get_config_string,3);
	duk_put_global_string(ctx,"get_config_string");
	duk_push_c_function(ctx, native_get_config_int,3);
	duk_put_global_string(ctx,"get_config_int");
	duk_push_c_function(ctx, native_get_config_hex,3);
	duk_put_global_string(ctx,"get_config_hex");
	duk_push_c_function(ctx, native_get_config_float,3);
	duk_put_global_string(ctx,"get_config_float");
	duk_push_c_function(ctx, native_get_config_id,3);
	duk_put_global_string(ctx,"get_config_id");
	duk_push_c_function(ctx, native_get_config_argv,3);
	duk_put_global_string(ctx,"get_config_argv");
	duk_push_c_function(ctx, native_get_config_text,1);
	duk_put_global_string(ctx,"get_config_text");
	duk_push_c_function(ctx, native_set_config_string,3);
	duk_put_global_string(ctx,"set_config_string");
	duk_push_c_function(ctx, native_set_config_int,3);
	duk_put_global_string(ctx,"set_config_int");
	duk_push_c_function(ctx, native_set_config_hex,3);
	duk_put_global_string(ctx,"set_config_hex");
	duk_push_c_function(ctx, native_set_config_float,3);
	duk_put_global_string(ctx,"set_config_float");
	duk_push_c_function(ctx, native_set_config_id,3);
	duk_put_global_string(ctx,"set_config_id");
	duk_push_c_function(ctx, native_list_config_entries,2);
	duk_put_global_string(ctx,"list_config_entries");
	duk_push_c_function(ctx, native_list_config_sections,1);
	duk_put_global_string(ctx,"list_config_sections");
	duk_push_c_function(ctx, native_free_config_entries,1);
	duk_put_global_string(ctx,"free_config_entries");
	duk_push_c_function(ctx, native_install_mouse,0);
	duk_put_global_string(ctx,"install_mouse");
	duk_push_c_function(ctx, native_remove_mouse,0);
	duk_put_global_string(ctx,"remove_mouse");
	duk_push_c_function(ctx, native_poll_mouse,0);
	duk_put_global_string(ctx,"poll_mouse");
	duk_push_c_function(ctx, native_mouse_needs_poll,0);
	duk_put_global_string(ctx,"mouse_needs_poll");
	duk_push_c_function(ctx, native_enable_hardware_cursor,0);
	duk_put_global_string(ctx,"enable_hardware_cursor");
	duk_push_c_function(ctx, native_disable_hardware_cursor,0);
	duk_put_global_string(ctx,"disable_hardware_cursor");
	duk_push_c_function(ctx, native_select_mouse_cursor,1);
	duk_put_global_string(ctx,"select_mouse_cursor");
	duk_push_c_function(ctx, native_set_mouse_cursor_bitmap,2);
	duk_put_global_string(ctx,"set_mouse_cursor_bitmap");
	duk_push_int(ctx,mouse_x);
	duk_put_global_string(ctx,"mouse_x");
	duk_push_int(ctx,mouse_y);
	duk_put_global_string(ctx,"mouse_y");
	duk_push_int(ctx,mouse_z);
	duk_put_global_string(ctx,"mouse_z");
	duk_push_int(ctx,mouse_w);
	duk_put_global_string(ctx,"mouse_w");
	duk_push_int(ctx,mouse_b);
	duk_put_global_string(ctx,"mouse_b");
	duk_push_int(ctx,mouse_pos);
	duk_put_global_string(ctx,"mouse_pos");
	duk_push_pointer(ctx,mouse_sprite);
	duk_put_global_string(ctx,"mouse_sprite");
	duk_push_int(ctx,mouse_x_focus);
	duk_put_global_string(ctx,"mouse_x_focus");
	duk_push_int(ctx,mouse_y_focus);
	duk_put_global_string(ctx,"mouse_y_focus");
	duk_push_c_function(ctx, native_show_mouse,1);
	duk_put_global_string(ctx,"show_mouse");
	duk_push_c_function(ctx, native_scare_mouse,0);
	duk_put_global_string(ctx,"scare_mouse");
	duk_push_c_function(ctx, native_scare_mouse_area,4);
	duk_put_global_string(ctx,"scare_mouse_area");
	duk_push_c_function(ctx, native_unscare_mouse,0);
	duk_put_global_string(ctx,"unscare_mouse");
	duk_push_c_function(ctx, native_show_os_cursor,1);
	duk_put_global_string(ctx,"show_os_cursor");
	duk_push_int(ctx,freeze_mouse_flag);
	duk_put_global_string(ctx,"freeze_mouse_flag");
	duk_push_c_function(ctx, native_position_mouse,2);
	duk_put_global_string(ctx,"position_mouse");
	duk_push_c_function(ctx, native_position_mouse_z,1);
	duk_put_global_string(ctx,"position_mouse_z");
	duk_push_c_function(ctx, native_position_mouse_w,1);
	duk_put_global_string(ctx,"position_mouse_w");
	duk_push_c_function(ctx, native_set_mouse_range,4);
	duk_put_global_string(ctx,"set_mouse_range");
	duk_push_c_function(ctx, native_set_mouse_speed,2);
	duk_put_global_string(ctx,"set_mouse_speed");
	duk_push_c_function(ctx, native_set_mouse_sprite,1);
	duk_put_global_string(ctx,"set_mouse_sprite");
	duk_push_c_function(ctx, native_set_mouse_sprite_focus,2);
	duk_put_global_string(ctx,"set_mouse_sprite_focus");
	duk_push_c_function(ctx, native_get_mouse_mickeys,2);
	duk_put_global_string(ctx,"get_mouse_mickeys");

	//invalid callback, as this is not defined yet	
	//extern void (*mouse_callback)(int flags);
	//duk_push_c_function(ctx, mouse_callback,1);
	//duk_put_global_string(ctx,"mouse_callback");
	
		//this function does not exist???
	//duk_push_c_function(ctx, native_mouse_on_screen,0);
	//duk_put_global_string(ctx,"mouse_on_screen");
	duk_push_c_function(ctx, native_acquire_screen,0);
	duk_put_global_string(ctx,"acquire_screen");
	duk_push_c_function(ctx, native_vsync,0);
	duk_put_global_string(ctx,"vsync");


	//-----------------------zzzzzzzz
	duk_push_c_function(ctx, native_loadscript, 1);
	duk_put_global_string(ctx,"loadscript");
	duk_push_c_function(ctx, native_floodfill, 4);
	duk_put_global_string(ctx,"floodfill");
	duk_push_c_function(ctx, native_makecol, 3);
	duk_put_global_string(ctx,"makecol");
	duk_push_c_function(ctx, native_do_arc, 7);
	duk_put_global_string(ctx,"do_arc");
	duk_push_c_function(ctx, native_pivot_scaled_sprite_v_flip, 8);
	duk_put_global_string(ctx,"pivot_scaled_sprite_v_flip");
	duk_push_c_function(ctx, native_pivot_scaled_sprite, 8);
	duk_put_global_string(ctx,"pivot_scaled_sprite");
	duk_push_c_function(ctx, native_pivot_sprite_v_flip, 7);
	duk_put_global_string(ctx,"pivot_sprite_v_flip");
	duk_push_c_function(ctx, native_pivot_sprite, 7);
	duk_put_global_string(ctx,"pivot_sprite");
	duk_push_c_function(ctx, native_rotate_scaled_sprite_v_flip, 6);
	duk_put_global_string(ctx,"rotate_scaled_sprite_v_flip");
	duk_push_c_function(ctx, native_rotate_scaled_sprite, 6);
	duk_put_global_string(ctx,"rotate_scaled_sprite");
	duk_push_c_function(ctx, native_rotate_sprite_v_flip, 5);
	duk_put_global_string(ctx,"rotate_sprite_v_flip");
	duk_push_c_function(ctx, native_rotate_sprite, 5);
	duk_put_global_string(ctx,"rotate_sprite");
	duk_push_c_function(ctx, native_draw_sprite, 4);
	duk_put_global_string(ctx,"draw_sprite");
	duk_push_c_function(ctx, native_draw_trans_sprite, 4);
	duk_put_global_string(ctx,"draw_trans_sprite");
	duk_push_c_function(ctx, native_draw_sprite_v_flip, 4);
	duk_put_global_string(ctx,"draw_sprite_v_flip");
	duk_push_c_function(ctx, native_draw_lit_sprite, 5);
	duk_put_global_string(ctx,"draw_lit_sprite");
	duk_push_c_function(ctx, native_draw_sprite_h_flip, 4);
	duk_put_global_string(ctx,"draw_sprite_h_flip");
	duk_push_c_function(ctx, native_draw_gouraud_sprite, 8);
	duk_put_global_string(ctx,"draw_gouraud_sprite");
	duk_push_c_function(ctx, native_draw_sprite_vh_flip, 4);
	duk_put_global_string(ctx,"draw_sprite_vh_flip");
	duk_push_c_function(ctx, native_stretch_sprite, 6);
	duk_put_global_string(ctx,"stretch_sprite");
	duk_push_c_function(ctx, native_create_bitmap, 2);
	duk_put_global_string(ctx,"create_bitmap");
	duk_push_c_function(ctx, native_load_png, 2);
	duk_put_global_string(ctx,"load_png");
	duk_push_c_function(ctx, native_load_bitmap, 2);
	duk_put_global_string(ctx,"load_bitmap");
	duk_push_c_function(ctx, native_clear, 1);
	duk_put_global_string(ctx,"clear");
	duk_push_c_function(ctx, native_clear_bitmap, 1);
	duk_put_global_string(ctx,"clear_bitmap");
	duk_push_c_function(ctx, native_clear_to_color, 2);
	duk_put_global_string(ctx,"clear_to_color");
	duk_push_c_function(ctx, native_destroy_bitmap, 1);
	duk_put_global_string(ctx,"destroy_bitmap");
	duk_push_c_function(ctx, native_stretch_blit, 10);
	duk_put_global_string(ctx,"stretch_blit");
	duk_push_c_function(ctx, native_masked_stretch_blit, 10);
	duk_put_global_string(ctx,"masked_stretch_blit");
	duk_push_c_function(ctx, native_blit, 8);
	duk_put_global_string(ctx,"blit");
	duk_push_c_function(ctx, native_masked_blit, 8);
	duk_put_global_string(ctx,"masked_blit");
	duk_push_c_function(ctx, native_test, 1);
	duk_put_global_string(ctx,"test");
	duk_push_c_function(ctx, native_exit, 1);
	duk_put_global_string(ctx,"exit");
	duk_push_c_function(ctx, native_abort, 0);
	duk_put_global_string(ctx,"abort");
	duk_push_c_function(ctx, native_set_leds, 1);
	duk_put_global_string(ctx,"set_leds");
	duk_push_c_function(ctx, native_install_keyboard, 0);
	duk_put_global_string(ctx,"install_keyboard");
	duk_push_c_function(ctx, native_install_timer, 0);
	duk_put_global_string(ctx,"install_timer");
	duk_push_c_function(ctx, native_install_sound, 3);
	duk_put_global_string(ctx,"install_sound");

	duk_push_c_function(ctx, native_load_midi, 1);
	duk_put_global_string(ctx,"load_midi");
	duk_push_c_function(ctx, native_destroy_midi, 1);
	duk_put_global_string(ctx,"destroy_midi");
	duk_push_c_function(ctx, native_stop_midi, 0);
	duk_put_global_string(ctx,"midi_stop");
	duk_push_c_function(ctx, native_lock_midi , 1);
	duk_put_global_string(ctx,"lock_midi");
	duk_push_c_function(ctx, native_play_midi , 2);
	duk_put_global_string(ctx,"play_midi");
	duk_push_c_function(ctx, native_play_looped_midi , 3);
	duk_put_global_string(ctx,"play_looped_midi");
	duk_push_c_function(ctx, native_stop_midi , 0);
	duk_put_global_string(ctx,"stop_midi");
	duk_push_c_function(ctx, native_midi_pause , 0);
	duk_put_global_string(ctx,"midi_pause");
	duk_push_c_function(ctx, native_midi_resume , 0);
	duk_put_global_string(ctx,"midi_resume");
	duk_push_c_function(ctx, native_midi_seek , 1);
	duk_put_global_string(ctx,"midi_seek");
	duk_push_c_function(ctx, native_get_midi_length , 1);
	duk_put_global_string(ctx,"get_midi_length");
	duk_push_c_function(ctx, native_midi_out , 2);
	duk_put_global_string(ctx,"midi_out");
	duk_push_c_function(ctx, native_load_midi_patches , 0);
	duk_put_global_string(ctx,"load_midi_patches");
	duk_push_c_function(ctx, native_load_ibk , 2);
	duk_put_global_string(ctx,"load_ibk");



	duk_push_c_function(ctx, native_remove_keyboard, 0);
	duk_put_global_string(ctx,"remove_keyboard");
	duk_push_c_function(ctx, native_poll_keyboard, 0);
	duk_put_global_string(ctx,"poll_keyboard");
	duk_push_c_function(ctx, native_keyboard_needs_poll, 0);
	duk_put_global_string(ctx,"keyboard_needs_poll");
	duk_push_c_function(ctx, native_set_color_depth, 1);
	duk_put_global_string(ctx,"set_color_depth");
	duk_push_c_function(ctx, native_set_gfx_mode, 5);
	duk_put_global_string(ctx,"set_gfx_mode");
	duk_push_c_function(ctx, native_keypressed, 0);
	duk_put_global_string(ctx,"keypressed");
	duk_push_c_function(ctx,native_getkey,0);
	duk_put_global_string(ctx,"getkey");
	duk_push_c_function(ctx,native_readkey,0);
	duk_put_global_string(ctx,"readkey");
	duk_push_c_function(ctx,native_scancode_to_ascii,1);
	duk_put_global_string(ctx,"scancode_to_ascii");
	duk_push_c_function(ctx,native_scancode_to_name,1);
	duk_put_global_string(ctx,"scancode_to_name");
	duk_push_c_function(ctx,native_simulate_keypress,1);
	duk_put_global_string(ctx,"simulate_keypress");
	duk_push_c_function(ctx,native_simulate_ukeypress,2);
	duk_put_global_string(ctx,"simulate_ukeypress");
	duk_push_c_function(ctx,native_set_keyboard_rate,2);
	duk_put_global_string(ctx,"set_keyboard_rate");
	duk_push_c_function(ctx,native_clear_keybuf,0);
	duk_put_global_string(ctx,"clear_keybuf");
	duk_push_c_function(ctx,native_ureadkey,1);
	duk_put_global_string(ctx,"ureadkey");
	duk_push_c_function(ctx,native_textout,8);
	duk_put_global_string(ctx,"textout");
	duk_push_c_function(ctx,native_putpixel,6);
	duk_put_global_string(ctx,"putpixel");
	duk_push_c_function(ctx,native_getpixel,0);
	duk_put_global_string(ctx,"getpixel");
	duk_push_c_function(ctx,native__getpixel,0);
	duk_put_global_string(ctx,"_getpixel");
	duk_push_c_function(ctx,native__getpixel15,0);
	duk_put_global_string(ctx,"_getpixel15");
	duk_push_c_function(ctx,native__getpixel16,0);
	duk_put_global_string(ctx,"_getpixel16");
	duk_push_c_function(ctx,native__getpixel24,0);
	duk_put_global_string(ctx,"_getpixel24");
	duk_push_c_function(ctx,native__getpixel32,0);
	duk_put_global_string(ctx,"_getpixel32");
	duk_push_c_function(ctx,native__putpixel,6);
	duk_put_global_string(ctx,"_putpixel");
	duk_push_c_function(ctx,native__putpixel15,6);
	duk_put_global_string(ctx,"_putpixel15");
	duk_push_c_function(ctx,native__putpixel16,6);
	duk_put_global_string(ctx,"_putpixel16");
	duk_push_c_function(ctx,native__putpixel24,6);
	duk_put_global_string(ctx,"_putpixel24");
	duk_push_c_function(ctx,native__putpixel32,6);
	duk_put_global_string(ctx,"_putpixel32");
	duk_push_c_function(ctx,native_fastline,6);
	duk_put_global_string(ctx,"fastline");
	duk_push_c_function(ctx,native_line,8);
	duk_put_global_string(ctx,"line");
	duk_push_c_function(ctx,native_vline,5);
	duk_put_global_string(ctx,"vline");
	duk_push_c_function(ctx,native_hline,5);
	duk_put_global_string(ctx,"hline");
	duk_push_c_function(ctx,native_rect,8);
	duk_put_global_string(ctx,"rect");
	duk_push_c_function(ctx,native_rectfill,8);
	duk_put_global_string(ctx,"rectfill");
	duk_push_c_function(ctx,native_circle,7);
	duk_put_global_string(ctx,"circle");
	duk_push_c_function(ctx,native_circlefill,7);
	duk_put_global_string(ctx,"circlefill");
	duk_push_c_function(ctx,native_ellipse,8);
	duk_put_global_string(ctx,"ellipse");
	duk_push_c_function(ctx,native_ellipsefill,8);
	duk_put_global_string(ctx,"ellipsefill");
	duk_push_c_function(ctx,native_triangle,10);
	duk_put_global_string(ctx,"triangle");
	duk_push_c_function(ctx,native_polygon,4);
	duk_put_global_string(ctx,"polygon");
	if(argc>1){
		for(int i=1;i<argc;i++){
			fileio_push_file_string(
				ctx,
				argv[i]
			);
			duk_eval(ctx);
		}
	}else{
		cerr<<"Usage: "<<argv[0]<<" [JSFILES]"<<endl;
		return -1;
	}
	return 0;
}
END_OF_MAIN()
static void my_fatal(void *udata, const char *msg) {
	(void) udata;
	fprintf(stderr, "*** FATAL ERROR: %s\n", (msg ? msg : "no message"));
	fflush(stderr);
	exit(-1);//abort();//exit used to use stdout to print error to text file with file redirection from console
}
