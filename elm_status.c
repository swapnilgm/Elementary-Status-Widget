#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include "elm_status.eo.h"
#define ELM_INTERNAL_API_ARGESFSDFEFC
#define EFL_EO_API_SUPPORT
#include <Elementary.h>
#include <Evas.h>
#include <canvas/evas_object_smart.eo.h>
#include <elm_widget.h>
#include <elm_layout.h>
#include <elm_widget_layout.h>
#include "elm_widget_status.h"

#define MY_CLASS ELM_STATUS_CLASS
#define MY_CLASS_NAME_LEGACY "elm_status"

#define ENUM_TO_STRING(en) #en
#define CRI printf

typedef struct
{
	int temp;
	char *status;
	MOOD mood;
	VISIBILITY visibility;
	char * picture;
	Evas_Object* icon;

	/*file selector*/
	Evas_Object* fs;
	const char *fs_title;
	/*file selector window*/
	Evas_Object* fsw;
	Evas_Object* entry;
	Eina_Bool editing_mode;
}Elm_Status_Data;

/* smart callbacks coming from elm button objects (besides the ones
 * coming from elm layout): */
static const Evas_Smart_Cb_Description _smart_callbacks[] = {
	{SIG_CLICKED, ""},
	{SIG_PICTURE_CHANGED, ""},
	{SIG_STATUS_CHANGED, ""},
	{SIG_MOOD_CHANGED, ""},
	{SIG_VISIBILITY_CHANGED, ""},
	//      {SIG_LAYOUT_FOCUSED, ""}, /**< handled by elm_layout */
	//      {SIG_LAYOUT_UNFOCUSED, ""}, /**< handled by elm_layout */
	{NULL, NULL}
};

EOLIAN static Eo_Base *
_elm_status_eo_base_constructor(Eo *obj, Elm_Status_Data *pd){
	/* call super class ctr */
	obj = eo_constructor(eo_super(obj, ELM_STATUS_CLASS));
	/* set type of our obj */
	evas_obj_type_set(obj, MY_CLASS_NAME_LEGACY);
	/* add our callbacks */
	evas_obj_smart_callbacks_descriptions_set(obj, _smart_callbacks);
	return obj;
}

	EOLIAN static void
_elm_status_eo_base_destructor(Eo *obj, Elm_Status_Data *pd)
{
	/* call super class dtr */
	eo_destructor(eo_super(obj, ELM_STATUS_CLASS));

}

	static Eina_Bool
_selection_done_cb(void *data, const Eo_Event *event)
{
	Elm_Status_Data *sd = data;
	const char *file = event->event_info;
	Evas_Object *del;

	if (file){
		elm_image_file_set(sd->icon, file, NULL);
		//TODO add event callback
		sd->picture= file;

	}

	del = sd->fsw;
	sd->fs = NULL;
	sd->fsw = NULL;
	evas_object_del(del);
//	eo_event_callback_call
//		(sd->obj, ELM_FILESELECTOR_EVENT_FILE_CHOSEN, (void *)file);

	return EINA_TRUE;
}


	static void
_new_window_add(Elm_Status_Data *pd)
{
	Evas_Object *win, *bg;

	win = elm_win_add(NULL, "imageselector", ELM_WIN_DIALOG_BASIC);
	elm_win_title_set(win, "Change image");
	elm_win_autodel_set(win, EINA_TRUE);
	eo_event_callback_add(win, ELM_WIN_EVENT_DELETE_REQUEST, _selection_done_cb, pd);
	bg = elm_bg_add(win);
	evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(win, bg);
	pd->fsw = win;
	evas_object_show(bg);
	_initialize_image_selector(pd);
	evas_object_show(win);
}



	void
_initialize_image_selector(Elm_Status_Data *pd)
{

	EINA_LOG_WARN("Adding new iwndow ");
	printf("%x", pd->fsw);
	/* add file selector, in list mode */
	pd->fs = elm_fileselector_add(pd->fsw);
	//elm_widget_mirrored_automatic_set(pd->fs, EINA_FALSE);
	// elm_fileselector_expandable_set(pd->fs, EINA_TRUE);
	/* enable the fs file name entry */
	//elm_fileselector_is_save_set(pd->fs, EINA_TRUE);
	evas_object_size_hint_weight_set(pd->fs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(pd->fs, EVAS_HINT_FILL, EVAS_HINT_FILL);
	eo_event_callback_add(pd->fs, ELM_FILESELECTOR_EVENT_DONE, _selection_done_cb, pd);

	evas_object_show(pd->fs);
	elm_win_resize_object_add(pd->fsw, pd->fs);

	//	evas_object_hide(pd->fs;

}


/**
 * Private function Just to manage initial image loading parameters
 *
 */
	static void
_initialize_image(Eo *obj, Elm_Status_Data *pd)
{
	//use icon widget to load image
	pd->icon = elm_icon_add(obj);
	evas_object_repeat_events_set(pd->icon, EINA_TRUE);
	//although the icon widget provides basic image functionality
	//the apis over icon are deprecated
	//so we use image api to manage the image attributes
	elm_image_resizable_set(pd->icon, EINA_TRUE, EINA_TRUE);
	elm_image_smooth_set(pd->icon, EINA_TRUE);
	elm_image_fill_outside_set(pd->icon, EINA_TRUE);
	elm_image_prescale_set(pd->icon, 0);
	elm_object_scale_set(pd->icon, elm_widget_scale_get(obj));
	//evas_object_smart_callback_add(pd->icon, "clicked", _new_window_add,NULL);

	//TODO
	elm_icon_standard_set(pd->icon, "no_photo");
	pd->picture = "no_photo";
	//_initialize_image_selector(obj, pd);

}


static void
_status_clicked_cb(void *data, Evas_Object *obj, const char * emission, const char* source)
{
	Elm_Status_Data *pd =data;
	printf("*****************");

	Evas_Object *txtObj = evas_object_name_find(obj,"elm.status.text.text");
	printf("%x", txtObj);
	if(!pd->editing_mode)
	{
		pd->editing_mode = EINA_TRUE;
		evas_object_show(pd->entry);
	evas_object_hide(txtObj);
	} else {

		pd->editing_mode = EINA_FALSE;
	evas_object_show(txtObj);
		evas_object_hide(pd->entry);
	}
}

	static void
	_initialize_entry(Eo * obj, Elm_Status_Data *pd)
{
pd->entry = elm_entry_add(obj);
evas_object_hide(pd->entry);
	}

	EOLIAN static void
_elm_status_evas_object_smart_add(Eo *obj, Elm_Status_Data *pd)
{
	//add smart object in widget hierarchy
	evas_obj_smart_add(eo_super(obj, ELM_STATUS_CLASS));
	// This function adds obj as a sub object of parent.
	// This must be added to have widget hierarchy (parent)
	elm_widget_sub_object_parent_add(obj);
	ELM_WIDGET_DATA_GET_OR_RETURN(obj, wd, );
	//Since we are deriving from Elm.widget,
	// our resize object is actually null. we actually don;t use it.
	// But now we are deriving from Elm.layout
	// add object as a resize object for the window (controls window minimum
	// size as well as gets resized if window is resized)
	EINA_LOG_DBG("wd->resize_obj %p\n", wd->resize_obj);
	//set the layout to "base" grouping from "statdus.edj"
	if(!elm_layout_theme_set(obj, "status", "base",	elm_widget_style_get(obj)))
		printf("Failed to set layout!\n");
	else
		EINA_LOG_DBG("Layout theme set to base.");

	_initialize_image(obj,pd);

	Evas_Object *txtObj = evas_object_name_find(wd->resize_obj,"elm.status.text.text");
	printf("asfgfggfdsdfsd%x", txtObj);
	if(!pd->editing_mode)
	//edje_object_part_swallow(wd->resize_obj,"elm.picture.selector",pd->fs);
	edje_object_part_swallow(wd->resize_obj,"elm.picture.image",pd->icon);

	_initialize_entry(obj, pd);
	edje_object_part_swallow(wd->resize_obj,"elm.status.text.entry",pd->entry);
	edje_object_signal_callback_add(wd->resize_obj, "elm,action,click", "*",_status_clicked_cb, pd);
	evas_object_size_hint_align_set(pd->icon, EVAS_HINT_FILL,
			EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(pd->icon, EVAS_HINT_EXPAND,
			EVAS_HINT_EXPAND);


}

	EOLIAN static void
_elm_status_evas_object_smart_del(Eo *obj, Elm_Status_Data *pd)
{
	EINA_LOG_WARN(__func__);
	evas_obj_smart_del(eo_super(obj, ELM_STATUS_CLASS));
}

	EOLIAN static Eina_Bool
_elm_status_elm_widget_event(Eo *obj, Elm_Status_Data *pd, Evas_Object *source, Evas_Callback_Type type, void *event_info)
{

	EINA_LOG_WARN(__func__);
}

	EOLIAN static Eina_Bool
_elm_status_elm_widget_theme_apply(Eo *obj, Elm_Status_Data *pd)
{

	EINA_LOG_WARN(__func__);
}

	EOLIAN static void
_elm_status_class_constructor(Eo_Class *klass)
{
	EINA_LOG_WARN(__func__);
	evas_smart_legacy_type_register(MY_CLASS_NAME_LEGACY, klass);
}

	EOLIAN static void
_elm_status_status_set(Eo *obj, Elm_Status_Data *pd, const char *txt)
{
	EINA_LOG_WARN(txt);
	if (txt)
	{
		if (!elm_obj_layout_text_set(obj,"elm.status.text.text", txt))
		{
			EINA_LOG_WARN("could not set the text. "
					"Maybe part 'text' does not exist?");
		}
		else {
			Status_event_info *sei = {
				SIG_STATUS_CHANGED,
				pd->status,
				txt,
				"elm.status.text.text"
			};
			pd->status = txt;
			evas_object_smart_callback_call(obj,SIG_STATUS_CHANGED, sei);
		}
	}
}

	EOLIAN static const char *
_elm_status_status_get(Eo *obj, Elm_Status_Data *pd)
{
	EINA_LOG_WARN(__func__);
	return pd->status;
}

	EOLIAN static void
_elm_status_mood_set(Eo *obj, Elm_Status_Data *pd, MOOD mood)
{

	if (!elm_obj_layout_text_set(obj,"elm.mood.message.text", "mood"+mood))
	{
		EINA_LOG_WARN("could not set the text. "
				"Maybe part 'elm.mood.message.text' does not exist?");
	}
	else {
		Status_event_info sei = {
			SIG_MOOD_CHANGED,
			&pd->mood,
			&mood,
			"elm.mood.message.text"
		};
		evas_object_smart_callback_call(obj,SIG_MOOD_CHANGED, &sei);
		pd->mood = mood;
	}
}

	EOLIAN static MOOD
_elm_status_mood_get(Eo *obj, Elm_Status_Data *pd)
{
	EINA_LOG_WARN(__func__);
	return pd->mood;
}

	EAPI Evas_Object *
elm_status_add(Evas_Object *parent)
{
	EINA_LOG_WARN(__func__);
	EINA_SAFETY_ON_NULL_RETURN_VAL(parent, NULL);
	Evas_Object *obj = eo_add(MY_CLASS, parent);
	return obj;
}

	EOLIAN static void
_elm_status_visibility_set(Eo *obj, Elm_Status_Data *pd, VISIBILITY visibility)
{
	EINA_LOG_WARN(__func__);
	if (!elm_obj_layout_text_set(obj,"elm.visibility.text", "visibid"+visibility))
	{
		EINA_LOG_WARN("could not set the text. "
				"Maybe part 'elm.visibility.text' does not exist?");
	}
	else {
		Status_event_info *sei = {
			SIG_VISIBILITY_CHANGED,
			pd->visibility,
			visibility,
			"elm.visibility.text"
		};
		evas_object_smart_callback_call(obj,SIG_VISIBILITY_CHANGED, "elm.visibility.text");
		pd->visibility = visibility;
	}
}

	EOLIAN static VISIBILITY
_elm_status_visibility_get(Eo *obj, Elm_Status_Data *pd)
{
	EINA_LOG_WARN(__func__);
	return pd->visibility;
}

	EOLIAN static void
_elm_status_picture_set(Eo *obj, Elm_Status_Data *pd, char *picture)
{
	EINA_LOG_WARN(__func__);
	if (picture)
	{
		EINA_LOG_DBG("Valid picture url found.");
		if(!elm_image_file_set(pd->icon, picture, NULL))
		{
			EINA_LOG_WARN("could not set the image." );
		}
		else {
			Status_event_info *sei = {
				SIG_PICTURE_CHANGED,
				pd->picture,
				picture,
				"elm.picture.image"
			};
			evas_object_smart_callback_call(obj,SIG_PICTURE_CHANGED, "elm.picture.image");
			pd->picture = picture;
		}
	}
}

	EOLIAN static char *
_elm_status_picture_get(Eo *obj, Elm_Status_Data *pd)
{
	EINA_LOG_WARN(__func__);
	return pd->picture;
}

#include "elm_status.eo.c"
