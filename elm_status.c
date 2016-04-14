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

	//	char *picture =  "/duel_boot.jpeg";
	elm_icon_standard_set(pd->icon, "no_photo");
	//	if(!elm_image_file_set(pd->icon, picture, NULL))
	//	{
	//		EINA_LOG_WARN("could not set the image." );
	//	}
	//	else
	pd->picture = "no_photo";
	edje_object_part_swallow(wd->resize_obj,"elm.picture.image",pd->icon);

	evas_object_size_hint_align_set(pd->icon, EVAS_HINT_FILL,
			EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(pd->icon, EVAS_HINT_EXPAND,
			EVAS_HINT_EXPAND);


}

	EOLIAN static void
_elm_status_evas_object_smart_del(Eo *obj, Elm_Status_Data *pd)
{
	EINA_LOG_WARN(__func__);
	//evas_obj_smart_add(eo_super(obj, ELM_STATUS_CLASS));
	//	ELM_SAFE_FREE(pd->image, evas_object_del);
	//	eo_do_super(obj, ELM_STATUS_CLASS, evas_object_del);

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
	else{
		Status_event_info *sei = {
			SIG_MOOD_CHANGED,
			pd->mood,
			mood,
			"elm.mood.message.text"
		};
		evas_object_smart_callback_call(obj,SIG_MOOD_CHANGED, sei);
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
