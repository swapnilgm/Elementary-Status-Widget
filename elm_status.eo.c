
void _elm_status_status_set(Eo *obj, Elm_Status_Data *pd, const char *txt);

EOAPI EO_VOID_FUNC_BODYV(elm_status_set, EO_FUNC_CALL(txt), const char *txt);

const char * _elm_status_status_get(Eo *obj, Elm_Status_Data *pd);

EOAPI EO_FUNC_BODY_CONST(elm_status_get, const char *, 0);

void _elm_status_mood_set(Eo *obj, Elm_Status_Data *pd, MOOD mood);

EOAPI EO_VOID_FUNC_BODYV(elm_status_mood_set, EO_FUNC_CALL(mood), MOOD mood);

MOOD _elm_status_mood_get(Eo *obj, Elm_Status_Data *pd);

EOAPI EO_FUNC_BODY_CONST(elm_status_mood_get, MOOD, 0);

void _elm_status_picture_set(Eo *obj, Elm_Status_Data *pd, char *picture);

EOAPI EO_VOID_FUNC_BODYV(elm_status_picture_set, EO_FUNC_CALL(picture), char *picture);

char * _elm_status_picture_get(Eo *obj, Elm_Status_Data *pd);

EOAPI EO_FUNC_BODY_CONST(elm_status_picture_get, char *, 0);

void _elm_status_visibility_set(Eo *obj, Elm_Status_Data *pd, VISIBILITY visibility);

EOAPI EO_VOID_FUNC_BODYV(elm_status_visibility_set, EO_FUNC_CALL(visibility), VISIBILITY visibility);

VISIBILITY _elm_status_visibility_get(Eo *obj, Elm_Status_Data *pd);

EOAPI EO_FUNC_BODY_CONST(elm_status_visibility_get, VISIBILITY, 0);

Eo_Base * _elm_status_eo_base_constructor(Eo *obj, Elm_Status_Data *pd);


void _elm_status_eo_base_destructor(Eo *obj, Elm_Status_Data *pd);


void _elm_status_evas_object_smart_add(Eo *obj, Elm_Status_Data *pd);


void _elm_status_evas_object_smart_del(Eo *obj, Elm_Status_Data *pd);


Eina_Bool _elm_status_elm_widget_event(Eo *obj, Elm_Status_Data *pd, Evas_Object *source, Evas_Callback_Type type, void *event_info);


Eina_Bool _elm_status_elm_widget_theme_apply(Eo *obj, Elm_Status_Data *pd);


static const Eo_Op_Description _elm_status_op_desc[] = {
     EO_OP_FUNC_OVERRIDE(eo_constructor, _elm_status_eo_base_constructor),
     EO_OP_FUNC_OVERRIDE(eo_destructor, _elm_status_eo_base_destructor),
     EO_OP_FUNC_OVERRIDE(evas_obj_smart_add, _elm_status_evas_object_smart_add),
     EO_OP_FUNC_OVERRIDE(evas_obj_smart_del, _elm_status_evas_object_smart_del),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_event, _elm_status_elm_widget_event),
     EO_OP_FUNC_OVERRIDE(elm_obj_widget_theme_apply, _elm_status_elm_widget_theme_apply),
     EO_OP_FUNC(elm_status_set, _elm_status_status_set),
     EO_OP_FUNC(elm_status_get, _elm_status_status_get),
     EO_OP_FUNC(elm_status_mood_set, _elm_status_mood_set),
     EO_OP_FUNC(elm_status_mood_get, _elm_status_mood_get),
     EO_OP_FUNC(elm_status_picture_set, _elm_status_picture_set),
     EO_OP_FUNC(elm_status_picture_get, _elm_status_picture_get),
     EO_OP_FUNC(elm_status_visibility_set, _elm_status_visibility_set),
     EO_OP_FUNC(elm_status_visibility_get, _elm_status_visibility_get),
};

static const Eo_Class_Description _elm_status_class_desc = {
     EO_VERSION,
     "Elm_Status",
     EO_CLASS_TYPE_REGULAR,
     EO_CLASS_DESCRIPTION_OPS(_elm_status_op_desc),
     NULL,
     sizeof(Elm_Status_Data),
     _elm_status_class_constructor,
     NULL
};

EO_DEFINE_CLASS(elm_status_class_get, &_elm_status_class_desc, ELM_LAYOUT_CLASS, NULL);