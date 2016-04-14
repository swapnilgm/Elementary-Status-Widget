#ifndef ELM_WIDGET_STATUS_H
#define ELM_WIDGET_STATUS_H

#include<Elementary.h>
#include<Eo.h>
#include<Evas.h>
/*Event Info to pass to smart callbacks
 *
 * Move this to some header files
 * */
typedef struct {
	//event name i.e signal
const char *event_name;
//previous data specific to event object just before happening of event
char *priv_data;
//new modifed data after execution of event
char *new_data;
//theme part name 
const char *part_name;

}Status_event_info;

static const char SIG_CLICKED[] = "clicked";
static const char SIG_PICTURE_CHANGED[] = "picture,changed";
static const char SIG_STATUS_CHANGED[] = "status,changed";
static const char SIG_MOOD_CHANGED[] = "mood,changed";
static const char SIG_VISIBILITY_CHANGED[] = "visibility,changed";

/*
 * API to add status widget
 */
EAPI Evas_Object * elm_status_add(Evas_Object *parent);

#endif
