#ifndef _ELM_STATUS_EO_H_
#define _ELM_STATUS_EO_H_

#ifndef _ELM_STATUS_EO_CLASS_TYPE
#define _ELM_STATUS_EO_CLASS_TYPE

typedef Eo Elm_Status;

#endif

#ifndef _ELM_STATUS_EO_TYPES
#define _ELM_STATUS_EO_TYPES

typedef enum
{
  MOOD_HAPPY = 0, /** docs; also, for C usage, field names get uppercased and
                   * prefixed with MOOD in this case */
  MOOD_SAD
} MOOD;

/** enum docs
 *
 * @ingroup VISIBILITY
 */
typedef enum
{
  VISIBILITY_ONLINE = 0,
  VISIBILITY_OFFLINE
} VISIBILITY;


#endif
#define ELM_STATUS_CLASS elm_status_class_get()

EAPI const Eo_Class *elm_status_class_get(void);

EOAPI void elm_status_set(Eo *obj, const char *txt);

EOAPI const char *elm_status_get(const Eo *obj);

/**
 * @brief Mood of the person. This can be one of the supported moods like
 * 'happy, sad, excited etc.'
 *
 * set the changed mood of person
 *
 * @param[in] mood
 *
 * @ingroup Elm_Status
 */
EOAPI void elm_status_mood_set(Eo *obj, MOOD mood);

/**
 * @brief Mood of the person. This can be one of the supported moods like
 * 'happy, sad, excited etc.'
 *
 * get the current mood of person
 *
 * @ingroup Elm_Status
 */
EOAPI MOOD elm_status_mood_get(const Eo *obj);

/**
 * @brief Display picture of person
 *
 * set the display picture
 *
 * @param[in] picture
 *
 * @ingroup Elm_Status
 */
EOAPI void elm_status_picture_set(Eo *obj, char *picture);

/**
 * @brief Display picture of person
 *
 * get the display pictue
 *
 * @ingroup Elm_Status
 */
EOAPI char *elm_status_picture_get(const Eo *obj);

/**
 * @brief Visibility of person. This can be one of the supported mode like
 * online, offline etc.
 *
 * set the visibility mode
 *
 * @param[in] visibility
 *
 * @ingroup Elm_Status
 */
EOAPI void elm_status_visibility_set(Eo *obj, VISIBILITY visibility);

/**
 * @brief Visibility of person. This can be one of the supported mode like
 * online, offline etc.
 *
 * get the visibility mode
 *
 * @ingroup Elm_Status
 */
EOAPI VISIBILITY elm_status_visibility_get(const Eo *obj);


#endif
