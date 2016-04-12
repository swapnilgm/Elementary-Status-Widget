#define EFL_BETA_API_SUPPORT
#include <Elementary.h>
#include <Eo.h>
#include "elm_status.eo.h"


	static void
_status_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	printf("status changed callback\n");
}
	
	static void
_mood_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	printf("mood changed callback\n");
}



int main(int argc, char **argv)
{
	elm_init(argc, argv);

	Evas_Object *win;
	elm_theme_overlay_add(NULL, "./status.edj");
	//elm_config_item_select_on_focus_disabled_set(1);
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	win = elm_win_util_standard_add("Eo Smart Object",
			"Eo Status Widget");
	elm_win_focus_highlight_enabled_set(win, 1);
	elm_win_autodel_set(win, 1);

	Evas_Object *obj = eo_add(ELM_STATUS_CLASS,win);
	//  Evas_Object *obj = elm_status_add(win);
	elm_status_set(obj, "Hopping for best");
	elm_status_mood_set(obj, MOOD_SAD);
	elm_status_visibility_set(obj, VISIBILITY_OFFLINE);
	elm_status_picture_set(obj, "some path");
	evas_object_resize(obj, 400, 300);
	evas_object_move(obj, 0, 50);

	evas_object_smart_callback_add(obj, "changed", _status_changed_cb, NULL);
	evas_object_show(obj);



	evas_object_resize(win, 400, 400);
	evas_object_show(win);

	elm_object_focus_set(obj, 1);

	elm_status_set(obj, "Hopping for worst");

	elm_run();


	elm_shutdown();

	return 0;
}
