#define EFL_BETA_API_SUPPORT
#include <Elementary.h>
#include <Eo.h>
#include "elm_status.eo.h"
#include "elm_widget_status.h"

	static void
_status_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");
}

	static void
_mood_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");
}

	static void
_visibility_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");
}

	static void
_picture_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");
}

	static void
_button_change_mood_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");

	Evas_Object *status = (Evas_Object*)data;
	elm_status_mood_set(status, MOOD_EXCITED);
}

	static void
_button_change_status_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");

	Evas_Object *status = (Evas_Object*)data;
	elm_status_set(status, "hello there");
}

	static void
_button_change_visibility_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");

	Evas_Object *status = (Evas_Object*)data;
	elm_status_visibility_set(status, VISIBILITY_AWAY);
}

	static void
_button_change_picture_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");

	Evas_Object *status = (Evas_Object*)data;
	elm_status_picture_set(status, "../images/monk.png");
}

	static void
_button_print_debug_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");

	Evas_Object *status = (Evas_Object*)data;
	EINA_LOG_WARN("\nStatus widget dump:\n\
		Picture path: %s\
		Status text: %s\
		Mood: %s\
		Visibility: %s",
		elm_status_picture_get(status),
		elm_status_get(status),
		MOOD_TO_STR[elm_status_mood_get(status)],
		VISIBILITY_TO_STR[elm_status_visibility_get(status)]);
}

int main(int argc, char **argv)
{
	if (!elm_init(argc, argv))
		return -1;

	const int WIDGET_WIDTH = 600;
	const int WIDGET_HEIGHT = 250;

	/* window object */
	Evas_Object *win;

	/* add our .edj to default theme */
	elm_theme_overlay_add(NULL, "./status.edj");

	/* quit if our window is closed */
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

	/* add our widget to the window */
	win = elm_win_util_standard_add("Eo Status Widget", "Status Widget Demo");

	/* delete the window if user hits the close button */
	elm_win_autodel_set(win, EINA_TRUE);

	/* Set the enabled status for the focus highlight in a window TODO what does this mean? */
	elm_win_focus_highlight_enabled_set(win, EINA_TRUE);

	/* initialize status widget with `win` as parent */
	Evas_Object *obj = elm_status_add(win);

	/////////////////////////////////////////////////////////////
	/* first object */
	Evas_Object *obj1 = elm_status_add(win);

	evas_object_resize(obj1, WIDGET_WIDTH, WIDGET_HEIGHT);
	evas_object_move(obj1, 100, 100);

	evas_object_smart_callback_add(obj1, SIG_STATUS_CHANGED , _status_changed_cb, NULL);
	evas_object_smart_callback_add(obj1, SIG_PICTURE_CHANGED, _picture_changed_cb, NULL);
	evas_object_smart_callback_add(obj1, SIG_MOOD_CHANGED, _mood_changed_cb, NULL);
	evas_object_smart_callback_add(obj1, SIG_VISIBILITY_CHANGED, _visibility_changed_cb, NULL);

	evas_object_show(obj1);

	/////////////////////////////////////////////////////////////
	/* second object */
	Evas_Object *obj2 = elm_status_add(win);

	/* resize and move */
	evas_object_resize(obj2, WIDGET_WIDTH, WIDGET_HEIGHT);
	evas_object_move(obj2, 100, 400);

	evas_object_smart_callback_add(obj2, SIG_STATUS_CHANGED , _status_changed_cb, NULL);
	evas_object_smart_callback_add(obj2, SIG_PICTURE_CHANGED, _picture_changed_cb, NULL);
	evas_object_smart_callback_add(obj2, SIG_MOOD_CHANGED, _mood_changed_cb, NULL);
	evas_object_smart_callback_add(obj2, SIG_VISIBILITY_CHANGED, _visibility_changed_cb, NULL);

	evas_object_show(obj2);

	/////////////////////////////////////////////////////////////

	Evas_Object *button1 = elm_button_add(win);
	elm_object_text_set(button1, "Change Status");
	evas_object_smart_callback_add(button1,"clicked",_button_change_status_cb,obj1);

	evas_object_resize(button1, 100, 40);
	evas_object_move(button1, 0, 0);
	evas_object_show(button1);

	/////////////////////////////////////////////////////////////

	Evas_Object *button2 = elm_button_add(win);
	elm_object_text_set(button2, "Change Mood");
	evas_object_smart_callback_add(button2,"clicked",_button_change_mood_cb,obj1);

	evas_object_resize(button2, 100, 40);
	evas_object_move(button2, 100, 0);
	evas_object_show(button2);

	/////////////////////////////////////////////////////////////

	Evas_Object *button3 = elm_button_add(win);
	elm_object_text_set(button3, "Change visibility");
	evas_object_smart_callback_add(button3,"clicked",_button_change_visibility_cb,obj1);

	evas_object_resize(button3, 100, 40);
	evas_object_move(button3, 200, 0);
	evas_object_show(button3);

	/////////////////////////////////////////////////////////////

	Evas_Object *button4 = elm_button_add(win);
	elm_object_text_set(button4, "Change picture");
	evas_object_smart_callback_add(button4,"clicked",_button_change_picture_cb,obj1);

	evas_object_resize(button4, 100, 40);
	evas_object_move(button4, 300, 0);
	evas_object_show(button4);

	/////////////////////////////////////////////////////////////

	Evas_Object *button5 = elm_button_add(win);
	elm_object_text_set(button5, "Print debug");
	evas_object_smart_callback_add(button5,"clicked",_button_print_debug_cb,obj1);

	evas_object_resize(button5, 100, 40);
	evas_object_move(button5, 400, 0);
	evas_object_show(button5);

	/////////////////////////////////////////////////////////////

	/* set window size to (400,400) */
	evas_object_resize(win, 1000, 800);

	/* display our window */
	evas_object_show(win);

	/* start the Ecore main loop */
	elm_run();

	/* shut everything down */
	elm_shutdown();

	return 0;
}
