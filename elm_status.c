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

#define MY_CLASS_NAME_LEGACY "elm_status"

typedef struct
{
   int temp;
} Elm_Status_Data;

EOLIAN static Eo_Base *
_elm_status_eo_base_constructor(Eo *obj, Elm_Status_Data *pd)
{
   obj = eo_constructor(eo_super(obj, ELM_STATUS_CLASS));
   evas_obj_type_set(obj, MY_CLASS_NAME_LEGACY);
   return obj;
}

EOLIAN static void
_elm_status_eo_base_destructor(Eo *obj, Elm_Status_Data *pd)
{
   eo_destructor(eo_super(obj, ELM_STATUS_CLASS));

}

EOLIAN static void
_elm_status_evas_object_smart_add(Eo *obj, Elm_Status_Data *pd)
{
   evas_obj_smart_add(eo_super(obj, ELM_STATUS_CLASS));

   elm_widget_sub_object_parent_add(obj);
//   ELM_WIDGET_DATA_GET_OR_RETURN(obj, wd, );

   if(!elm_layout_theme_set(obj, "status", "base",
                            elm_widget_style_get(obj)))
     printf("Failed to set layout!\n");

/*   evas_object_size_hint_align_set(pd->btn, EVAS_HINT_FILL,
                                   EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(pd->btn, EVAS_HINT_EXPAND,
                                    EVAS_HINT_EXPAND);
*/

}

EOLIAN static void
_elm_status_evas_object_smart_del(Eo *obj, Elm_Status_Data *pd)
{

}

EOLIAN static Eina_Bool
_elm_status_elm_widget_event(Eo *obj, Elm_Status_Data *pd, Evas_Object *source, Evas_Callback_Type type, void *event_info)
{

}

EOLIAN static Eina_Bool
_elm_status_elm_widget_theme_apply(Eo *obj, Elm_Status_Data *pd)
{

}

EOLIAN static void
_elm_status_mood_set(Eo *obj, Elm_Status_Data *pd, const char* txt)
{
   elm_object_text_set(obj, txt);
}

EOLIAN static const char*
_elm_status_mood_get(Eo *obj, Elm_Status_Data *pd)
{

}

EOLIAN static void
_elm_status_class_constructor(Eo_Class *klass)
{
   evas_smart_legacy_type_register(MY_CLASS_NAME_LEGACY, klass);
}

EOLIAN static void
_elm_status_value_set(Eo *obj, Elm_Status_Data *pd, int sz)
{

}

EOLIAN static int
_elm_status_value_get(Eo *obj, Elm_Status_Data *pd)
{

}

#include "elm_status.eo.c"
