#define EFL_BETA_API_SUPPORT
#include <Elementary.h>
#include <Eo.h>
#include "elm_status.eo.h"

int main(int argc, char **argv)
{
   elm_init(argc, argv);

   Evas_Object *win;
   elm_theme_overlay_add(NULL, "./status.edj");
   //elm_config_item_select_on_focus_disabled_set(1);

   win = elm_win_util_standard_add("Eo Smart Object",
                                   "Eo Smart Object");
//   elm_win_focus_highlight_enabled_set(win, 1);
 //  elm_win_autodel_set(win, 1);

   Evas_Object *obj = eo_add(ELM_STATUS_CLASS,
                              win);
   elm_status_mood_set(obj, "Sample Mood Text");
   evas_object_resize(obj, 100, 30);
   evas_object_move(obj, 100, 100);
   evas_object_show(obj);

   evas_object_resize(win, 400, 400);
   evas_object_show(win);

   elm_object_focus_set(obj, 1);

   elm_run();
   elm_shutdown();

   return 0;
}
