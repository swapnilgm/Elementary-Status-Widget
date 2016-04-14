#define EFL_BETA_API_SUPPORT
#include <Elementary.h>
#include <Eo.h>
#include "elm_status.eo.h"
#include "elm_widget_status.h"

	static void
_status_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	printf("status changed callback\n");
	//	Status_event_info *sei = (Status_event_info*)event_info;
	/*	printf("even_name :: %s",sei->event_name);
		printf("Priv status ::%s", sei->priv_data);
		printf("New status ::%s", sei->new_data);
		printf("Part::%s", sei->part_name);
		*/
}

	static void
_mood_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	printf("mood changed callback\n");
	//	Status_event_info *sei = (Status_event_info*)event_info;
	/*	printf("even_name :: %s",sei->event_name);
		printf("Priv status ::%s", sei->priv_data);
		printf("New status ::%s", sei->new_data);
		printf("Part::%s", sei->part_name);
		*/
}

	static void
_visibility_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	printf("visibility changed callback\n");
	//	Status_event_info *sei = (Status_event_info*)event_info;
	/*	printf("even_name :: %s",sei->event_name);
		printf("Priv status ::%s", sei->priv_data);
		printf("New status ::%s", sei->new_data);
		printf("Part::%s", sei->part_name);
		*/
}

	static void
_picture_changed_cb(void *data, Evas_Object *obj,void *event_info)
{
	printf("picture changed callback\n");
	//	Status_event_info *sei = (Status_event_info*)event_info;
	/*	printf("even_name :: %s",sei->event_name);
		printf("Priv status ::%s", sei->priv_data);
		printf("New status ::%s", sei->new_data);
		printf("Part::%s", sei->part_name);
		*/
}


	static void
_edit_dblclick_cb(void *data, Evas_Object *obj,void *event_info)
{
	EINA_LOG_WARN("edit dblclick callback\n");
	Evas_Object *status = (Evas_Object*)data;
	elm_status_set(status, "helloi");
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
	/* TODO */
	elm_theme_overlay_add(NULL, "./status.edj");
	//elm_config_item_select_on_focus_disabled_set(1);
	elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
	win = elm_win_util_standard_add("Eo Smart Object",
			"Eo Status Widget");
	elm_win_focus_highlight_enabled_set(win, 1);


	/* delete the window if user hits the close button */
	elm_win_autodel_set(win, EINA_TRUE);

	/* Set the enabled status for the focus highlight in a window TODO what does this mean? */
	elm_win_focus_highlight_enabled_set(win, EINA_TRUE);

	/* initialize ELM_STATUS_CLASS object with `win` as parent */
//	Evas_Object *obj = eo_add(ELM_STATUS_CLASS, win);
	Evas_Object *obj = elm_status_add(win);

	/* elm_status_set(obj, "Hopping for best"); */
	elm_status_mood_set(obj, MOOD_SAD);
	elm_status_visibility_set(obj, VISIBILITY_OFFLINE);
	//elm_status_picture_set(obj, "../monk.png");

	/* resize and move */
	evas_object_resize(obj, 500, 200);
	evas_object_move(obj, 50, 50);

	evas_object_smart_callback_add(obj, SIG_STATUS_CHANGED , _status_changed_cb, NULL);
	evas_object_smart_callback_add(obj, SIG_PICTURE_CHANGED, _picture_changed_cb, NULL);
	evas_object_smart_callback_add(obj, SIG_MOOD_CHANGED, _mood_changed_cb, NULL);
	evas_object_smart_callback_add(obj, SIG_VISIBILITY_CHANGED, _visibility_changed_cb, NULL);
	evas_object_show(obj);

	/* set window size to (400,400) */
	evas_object_resize(win, 600, 300);

	/* display our window */
	evas_object_show(win);

	Evas_Object *entry = elm_entry_add(win);
	elm_entry_autosave_set(entry, EINA_FALSE);
	elm_entry_file_set(entry,"/tmp/en.txt",ELM_TEXT_FORMAT_MARKUP_UTF8);
	elm_object_text_set(entry, "Change Status");
	evas_object_resize(entry, 400, 50);
	evas_object_move(entry, 0, 0);
	evas_object_show(entry);
	elm_object_focus_set(obj, EINA_TRUE);
	evas_object_smart_callback_add(entry,"clicked,double",_edit_dblclick_cb,obj);

	evas_object_move(obj, 0, 50);

	/* start the Ecore main loop */
	elm_run();

	/* shut everything down */
	elm_shutdown();

	return 0;
}
