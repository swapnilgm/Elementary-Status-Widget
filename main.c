#include <Elementary.h>
#include <Eo.h>
#include "elm_status.eo.h"

static void _status_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	printf("status changed callback\n");
}

static void _mood_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	printf("mood changed callback\n");
}

int main(int argc, char **argv)
{
 	if (!elm_init(argc, argv))
 		return -1;

	/* window object */
	Evas_Object *win;
	/* TODO */
	elm_theme_overlay_add(NULL, "./status.edj");
	//elm_config_item_select_on_focus_disabled_set(1);

	/* on quitting last window, quit the Ecore event loop */
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	/* create window with title "Eo Status Widget" and 'name' prop set to "main" */
	win = elm_win_util_standard_add("main", "Eo Status Widget");

	/* delete the window if user hits the close button */
	elm_win_autodel_set(win, EINA_TRUE);

	/* Set the enabled status for the focus highlight in a window TODO what does this mean? */
	elm_win_focus_highlight_enabled_set(win, EINA_TRUE);

	/* initialize ELM_STATUS_CLASS object with `win` as parent */
	Evas_Object *obj = eo_add(ELM_STATUS_CLASS, win);
	/* Evas_Object *obj = elm_status_add(win); */

	/* elm_status_set(obj, "Hopping for best"); */
	elm_status_mood_set(obj, MOOD_SAD);
	elm_status_visibility_set(obj, VISIBILITY_OFFLINE);
	elm_status_picture_set(obj, "some path");

	/* resize and move */
	evas_object_resize(obj, 400, 300);
	evas_object_move(obj, 0, 50);

	evas_object_smart_callback_add(obj, "changed", _status_changed_cb, NULL);
	evas_object_show(obj);

	/* set window size to (400,400) */
	evas_object_resize(win, 400, 400);

	/* display our window */
	evas_object_show(win);

	elm_object_focus_set(obj, EINA_TRUE);

	/* elm_status_set(obj, "Hopping for worst"); */

	/* start the Ecore main loop */
	elm_run();

	/* shut everything down */
	elm_shutdown();
	return 0;
}
