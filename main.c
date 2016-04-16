#define EFL_BETA_API_SUPPORT
#include <Elementary.h>
#include <Eo.h>
#include "elm_status.eo.h"
#include "elm_widget_status.h"

	static void
_status_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");
	Status_event_info *sei = (Status_event_info*)event_info;
	/* printf("even_name :: %s",sei->event_name); */
	/* printf("Priv status ::%s", sei->priv_data); */
	/* printf("New status ::%s", sei->new_data); */
	/* printf("Part::%s", sei->part_name); */
}

	static void
_mood_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");
	/* if (event_info == NULL) { */
	/* 	printf("event_info is NULL\nReturning..\n"); */
	/* 	return; */
	/* } */
	/* printf("event_info is not NULL\n"); */
	/* printf("event_info: %p\n", event_info); */
	/* Status_event_info *sei = (Status_event_info*)event_info; */
	/* printf("even_name :: %s\n",sei->event_name); */
	/* printf("Priv status ::%s", MOOD_TO_STR[*(MOOD*)sei->priv_data]); */
	/* printf("New status ::%s", VISIBILITY_TO_STR[*(VISIBILITY*)sei->new_data]); */
	/* printf("Part::%s", sei->part_name); */
}

	static void
_visibility_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");
	/* Status_event_info *sei = (Status_event_info*)event_info; */
	/* printf("even_name :: %s",sei->event_name); */
	/* printf("Priv status ::%s", sei->priv_data); */
	/* printf("New status ::%s", sei->new_data); */
	/* printf("Part::%s", sei->part_name); */
}

	static void
_picture_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");
	/* Status_event_info *sei = (Status_event_info*)event_info; */
	/* printf("even_name :: %s",sei->event_name); */
	/* printf("Priv status ::%s", sei->priv_data); */
	/* printf("New status ::%s", sei->new_data); */
	/* printf("Part::%s", sei->part_name); */
}

	static void
_edit_dblclick_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("called");
	Evas_Object *status = (Evas_Object*)data;
	elm_status_set(status, "hello there");
	elm_status_mood_set(status, MOOD_EXCITED);
	elm_status_picture_set(status, "../images/Start_IT.png");
	elm_status_visibility_set(status, VISIBILITY_OFFLINE);
}


int main(int argc, char **argv)
{
	if (!elm_init(argc, argv))
		return -1;

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

	evas_object_resize(obj1, 700, 200);
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
	evas_object_resize(obj2, 700, 200);
	evas_object_move(obj2, 100, 400);

	evas_object_smart_callback_add(obj2, SIG_STATUS_CHANGED , _status_changed_cb, NULL);
	evas_object_smart_callback_add(obj2, SIG_PICTURE_CHANGED, _picture_changed_cb, NULL);
	evas_object_smart_callback_add(obj2, SIG_MOOD_CHANGED, _mood_changed_cb, NULL);
	evas_object_smart_callback_add(obj2, SIG_VISIBILITY_CHANGED, _visibility_changed_cb, NULL);

	evas_object_show(obj2);

	/////////////////////////////////////////////////////////////
	/* text entry1 */
	Evas_Object *entry1 = elm_entry_add(win);
	elm_entry_autosave_set(entry1, EINA_FALSE);
	/* elm_entry_file_set(entry1,"/tmp/en.txt",ELM_TEXT_FORMAT_MARKUP_UTF8); */
	elm_object_text_set(entry1, "Change Status");
	evas_object_resize(entry1, 400, 50);
	evas_object_move(entry1, 0, 0);
	evas_object_show(entry1);
	evas_object_smart_callback_add(entry1,"clicked,double",_edit_dblclick_cb,obj1);

	/////////////////////////////////////////////////////////////
	/* text entry2 */
	Evas_Object *entry2 = elm_entry_add(win);
	elm_entry_autosave_set(entry2, EINA_FALSE);
	/* elm_entry_file_set(entry2,"/tmp/en.txt",ELM_TEXT_FORMAT_MARKUP_UTF8); */
	elm_object_text_set(entry2, "Change Status");
	evas_object_resize(entry2, 400, 50);
	evas_object_move(entry2, 500, 0);
	evas_object_show(entry2);
	evas_object_smart_callback_add(entry2,"clicked,double",_edit_dblclick_cb,obj2);

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
