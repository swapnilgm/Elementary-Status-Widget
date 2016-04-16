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
#include <string.h>

#define MY_CLASS ELM_STATUS_CLASS
#define MY_CLASS_NAME_LEGACY "elm_status"

#define ENUM_TO_STRING(en) #en
#define CRI printf

#define SIGNAL_SIZE 20
#define MAX_STATUS_LEN 140
#define PATH_MAX 4096

typedef struct
{
	char status[MAX_STATUS_LEN];
	MOOD mood;
	VISIBILITY visibility;

	/* path of the image */
	char picture[PATH_MAX];
	/* icon widget object of picture */
	Evas_Object* icon;

	/* associated edje object */
	Edje_Object *edje_obj;

	/*file selector widget*/
	Evas_Object* fs;
	/*file selector window*/
	Evas_Object* fsw;

	/* Evas_Object* entry; */
	/* Eina_Bool editing_mode; */

	/* status widget object */
	Evas_Object *obj;

} Elm_Status_Data;

/* events exposed by status widget */
static const Evas_Smart_Cb_Description _smart_callbacks[] = {
	{SIG_PICTURE_CHANGED, ""},
	{SIG_STATUS_CHANGED, ""},
	{SIG_MOOD_CHANGED, ""},
	{SIG_VISIBILITY_CHANGED, ""},
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

		if(!elm_image_file_set(sd->icon, file, NULL))
		{
			EINA_LOG_WARN("could not set the image." );
		}
		else {
			Status_event_info sei = {
				SIG_PICTURE_CHANGED,
				sd->picture,
				file,
				"elm.picture.image"
			};
			evas_object_smart_callback_call(sd->obj,SIG_PICTURE_CHANGED, "elm.picture.image");
			strncpy(sd->picture, file, PATH_MAX);
		}
	}

	del = sd->fsw;
	sd->fs = NULL;
	sd->fsw = NULL;
	evas_object_del(del);

	return EINA_TRUE;
}

	void
_initialize_image_selector(Elm_Status_Data *pd)
{
	/* add file selector, in list mode */
	pd->fs = elm_fileselector_add(pd->fsw);
	//elm_widget_mirrored_automatic_set(pd->fs, EINA_FALSE);
	 elm_fileselector_expandable_set(pd->fs, EINA_TRUE);
	/* enable the fs file name entry */
	elm_fileselector_is_save_set(pd->fs, EINA_TRUE);
	//elm_fileselector_mime_types_filter_append(pd->fs,"png","image_fileter");
	evas_object_size_hint_weight_set(pd->fs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(pd->fs, EVAS_HINT_FILL, EVAS_HINT_FILL);
	eo_event_callback_add(pd->fs, ELM_FILESELECTOR_EVENT_DONE, _selection_done_cb, pd);

	evas_object_show(pd->fs);
	elm_win_resize_object_add(pd->fsw, pd->fs);
}

	static void
_new_window_add_cb(void *data, Evas_Object *obj, void *ei)
{
	Evas_Object *win, *bg;
	Elm_Status_Data *pd =data;

	win = elm_win_add(obj, "imageselector", ELM_WIN_DIALOG_BASIC);
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
	evas_object_smart_callback_add(pd->icon, "clicked", _new_window_add_cb,pd);

	//TODO
	elm_icon_standard_set(pd->icon, "no_photo");
	strncpy(pd->picture, "no_photo", PATH_MAX);
}


	/* static void */
/* _status_clicked_cb(void *data, Evas_Object *obj, const char * emission, const char* source) */
/* { */
	/* Elm_Status_Data *pd =data; */

	/* Evas_Object *textPart =	edje_object_part_object_get(pd->edje_obj, "elm.status.text.text"); */
	/* EINA_LOG_WARN("Going in editing mode"); */
	/* pd->editing_mode = EINA_TRUE; */
	/* //	elm_entry_entry_set(pd->entry, pd->status); */
	/* //elm_entry_text_set(pd->entry,pd->status); */
	/* //	Evas_Coord *y,*w,*h; */
	/* //	evas_object_geometry_get(textPart,NULL,NULL,w,h ); */
	/* //	evas_object_resize(textPart, 0, 0); */
	/* evas_object_hide(textPart); */
	/* //	evas_object_resize(pd->entry, *w, *h); */
	/* evas_object_show(pd->entry); */

/* } */

	/* static Evas_Object_Event_Cb */
/* _entry_done_cb(void *data, Evas_Object *obj, void* ei) */
/* { */
	/* Elm_Status_Data *pd =data; */

	/* Evas_Object *textPart =	edje_object_part_object_get(pd->edje_obj, "elm.status.text.text"); */
	/* printf("%p", textPart); */
	/* Evas_Event_Key_Down *ev = ei; */
	/* printf("ev->key :: %s",ev->key); */
	/* if(!strcmp(ev->key,"sdfds")) */
	/* { */
	/* 	EINA_LOG_WARN("Going in static mode"); */
	/* 	pd->status = elm_entry_entry_get(pd->entry); */
	/* 	pd->editing_mode = EINA_FALSE; */

	/* 	//		Evas_Coord *w,*h; */
	/* 	//		evas_object_geometry_get(pd->entry,NULL,NULL,w,h ); */
	/* 	///		evas_object_resize(textPart, *w, *h); */
	/* 	//		evas_object_resize(pd->entry, 0, 0); */
	/* 	evas_object_hide(pd->entry); */
	/* 	evas_object_show(textPart); */
	/* } */
/* } */

	/* static void */
/* _initialize_entry(Eo * obj, Elm_Status_Data *pd) */
/* { */
	/* pd->entry = elm_entry_add(obj); */
	/* evas_object_repeat_events_set(pd->entry, EINA_FALSE); */
	/* elm_obj_entry_single_line_set(pd->entry, EINA_TRUE); */
	/* //	elm_obj_entry_editable_set(pd->entry, EINA_TRUE); */
	/* elm_entry_entry_set(pd->entry, pd->status); */
	/* //	evas_object_hide(pd->entry); */
/* } */

static Eina_Bool _set_status(Eo* obj, Elm_Status_Data* pd, const char* txt)
{
	if (txt && elm_obj_layout_text_set(obj,"elm.status.text.text", txt)) {
		strncpy(pd->status, txt, MAX_STATUS_LEN);
		return EINA_TRUE;
	}
	else {
		EINA_LOG_WARN("could not set the text. Maybe part 'text' does not exist?");
		return EINA_FALSE;
	}
}

static Eina_Bool _set_mood(Eo* obj, Elm_Status_Data* pd, MOOD mood)
{
	if (elm_obj_layout_text_set(obj,"elm.mood.message.text", MOOD_TO_STR[mood])) {
		char signal[SIGNAL_SIZE] = "mood_";
		strncat(signal, MOOD_TO_STR[mood], SIGNAL_SIZE-1);
		edje_object_signal_emit(pd->edje_obj, signal, "");
		pd->mood = mood;
		return EINA_TRUE;
	}
	else {
		EINA_LOG_WARN("could not set the text. Maybe part 'elm.mood.message.text' does not exist?");
		return EINA_FALSE;
	}
}

static Eina_Bool _set_visibility(Eo* obj, Elm_Status_Data* pd, VISIBILITY visibility)
{
	if (elm_obj_layout_text_set(obj,"elm.visibility.text", VISIBILITY_TO_STR[visibility])) {
		char signal[SIGNAL_SIZE] = "visibility_";
		strncat(signal, VISIBILITY_TO_STR[visibility], SIGNAL_SIZE-1);
		int pad_len = strlen(signal);

		strcpy(signal+pad_len, "_txt");
		edje_object_signal_emit(pd->edje_obj, signal, "");

		strcpy(signal+pad_len, "_image");
		edje_object_signal_emit(pd->edje_obj, signal, "");

		pd->visibility = visibility;
	}
	else {
		EINA_LOG_WARN("could not set the text. Maybe part 'elm.mood.message.text' does not exist?");
		return EINA_FALSE;
	}
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
	pd->edje_obj = wd->resize_obj;
	pd->obj = obj;
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

	_set_status(obj, pd, "Coding");
	_set_mood(obj, pd, MOOD_SAD);
	_set_visibility(obj, pd, VISIBILITY_OFFLINE);

	_initialize_image(obj, pd);

	edje_object_part_swallow(wd->resize_obj,"elm.picture.image",pd->icon);
	/* TODO: entry input doesn't seem to be working? these calls are causing problems */
	/* if(!pd->editing_mode){ */
	/* 	//edje_object_part_swallow(wd->resize_obj,"elm.picture.selector",pd->fs); */
	/* } */
	/* _initialize_entry(obj, pd); */
	/* edje_object_part_swallow(wd->resize_obj,"elm.status.text.entry",pd->entry); */
	/* elm_layout_signal_callback_add(obj, "mouse,clicked,*", "elm.status.text.text", _status_clicked_cb, pd); */
	/* evas_object_event_callback_add(pd->entry, EVAS_CALLBACK_KEY_DOWN,  _entry_done_cb, pd); */

	evas_object_size_hint_align_set(pd->icon, EVAS_HINT_FILL,
			EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(pd->icon, EVAS_HINT_EXPAND,
			EVAS_HINT_EXPAND);
}

	EOLIAN static void
_elm_status_evas_object_smart_del(Eo *obj, Elm_Status_Data *pd)
{
	evas_obj_smart_del(eo_super(obj, ELM_STATUS_CLASS));
}

	EOLIAN static void
_elm_status_class_constructor(Eo_Class *klass)
{
	evas_smart_legacy_type_register(MY_CLASS_NAME_LEGACY, klass);
}

	EOLIAN static void
_elm_status_status_set(Eo *obj, Elm_Status_Data *pd, const char *txt)
{
	if (_set_status(obj, pd, txt)) {
		Status_event_info sei = {
			SIG_STATUS_CHANGED,
			pd->status,
			txt,
			"elm.status.text.text"
		};
		evas_object_smart_callback_call(obj,SIG_STATUS_CHANGED, &sei);
	}
}

	EOLIAN static const char *
_elm_status_status_get(Eo *obj, Elm_Status_Data *pd)
{
	return pd->status;
}

	EOLIAN static void
_elm_status_mood_set(Eo *obj, Elm_Status_Data *pd, MOOD mood)
{
	if (_set_mood(obj, pd, mood)) {
		Status_event_info sei = {
			SIG_MOOD_CHANGED,
			&pd->mood,
			&mood,
			"elm.mood.message.text"
		};
		evas_object_smart_callback_call(obj,SIG_MOOD_CHANGED, &sei);
	}
}

	EOLIAN static MOOD
_elm_status_mood_get(Eo *obj, Elm_Status_Data *pd)
{
	return pd->mood;
}

	EAPI Evas_Object *
elm_status_add(Evas_Object *parent)
{
	EINA_SAFETY_ON_NULL_RETURN_VAL(parent, NULL);
	Evas_Object *obj = eo_add(MY_CLASS, parent);
	return obj;
}

	EOLIAN static void
_elm_status_visibility_set(Eo *obj, Elm_Status_Data *pd, VISIBILITY visibility)
{
	if (_set_visibility(obj, pd, visibility)) {
		Status_event_info sei = {
			SIG_VISIBILITY_CHANGED,
			&pd->visibility,
			&visibility,
			"elm.visibility.text"
		};
		evas_object_smart_callback_call(obj,SIG_VISIBILITY_CHANGED, "elm.visibility.text");
	}
}

	EOLIAN static VISIBILITY
_elm_status_visibility_get(Eo *obj, Elm_Status_Data *pd)
{
	return pd->visibility;
}

/**
 * Set picture path
 *
 */
	EOLIAN static void
_elm_status_picture_set(Eo *obj, Elm_Status_Data *pd, const char *picture)
{
	if (picture)
	{
		EINA_LOG_DBG("Valid picture url found.");
		if(!elm_image_file_set(pd->icon, picture, NULL))
		{
			EINA_LOG_WARN("could not set the image." );
		}
		else {
			strncpy(pd->picture, picture, PATH_MAX);
			Status_event_info sei = {
				SIG_PICTURE_CHANGED,
				pd->picture,
				picture,
				"elm.picture.image"
			};
			evas_object_smart_callback_call(obj,SIG_PICTURE_CHANGED, "elm.picture.image");
		}
	}
}

	EOLIAN static const char *
_elm_status_picture_get(Eo *obj, Elm_Status_Data *pd)
{
	return pd->picture;
}

#include "elm_status.eo.c"
