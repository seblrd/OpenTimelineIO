#include "copentimelineio/timeline.h"
#include <copentimelineio/serializableObjectWithMetadata.h>
#include <opentime/rationalTime.h>
#include <opentime/timeRange.h>
#include <opentimelineio/anyDictionary.h>
#include <opentimelineio/stack.h>
#include <opentimelineio/timeline.h>
#include <opentimelineio/track.h>
#include <vector>

typedef std::vector<OTIO_NS::Track*>           TrackVectorDef;
typedef std::vector<OTIO_NS::Track*>::iterator TrackVectorIteratorDef;

OTIO_API Timeline* Timeline_create(
    const char*    name,
    RationalTime*  global_start_time,
    AnyDictionary* metadata)
{
    std::string name_str = std::string();
    if(name != NULL) 
        name_str = name;

    OTIO_NS::AnyDictionary metadataDictionary = OTIO_NS::AnyDictionary();
    if(metadata != NULL)
        metadataDictionary =
            *reinterpret_cast<OTIO_NS::AnyDictionary*>(metadata);

    nonstd::optional<opentime::RationalTime> rationalTimeOptional =
        nonstd::nullopt;
    if(global_start_time != NULL)
    {
        rationalTimeOptional = nonstd::optional<opentime::RationalTime>(
            *reinterpret_cast<opentime::RationalTime*>(global_start_time));
    }
    return reinterpret_cast<Timeline*>(new OTIO_NS::Timeline(
        name_str, rationalTimeOptional, metadataDictionary));
}

OTIO_API Stack* Timeline_tracks(Timeline* self)
{
    if (!self)
        return NULL;

    return reinterpret_cast<Stack*>(
        reinterpret_cast<OTIO_NS::Timeline*>(self)->tracks());
}
OTIO_API void Timeline_set_tracks(Timeline* self, Stack* stack)
{
    if (!self)
        return;

    reinterpret_cast<OTIO_NS::Timeline*>(self)->set_tracks(
        reinterpret_cast<OTIO_NS::Stack*>(stack));
}
OTIO_API RationalTime* Timeline_global_start_time(Timeline* self)
{
    if (!self)
        return NULL;

    nonstd::optional<opentime::RationalTime> rationalTimeOptional =
        reinterpret_cast<OTIO_NS::Timeline*>(self)->global_start_time();
    if (rationalTimeOptional == nonstd::nullopt) 
        return NULL;

    return reinterpret_cast<RationalTime*>(
        new opentime::RationalTime(rationalTimeOptional.value()));
}
OTIO_API void Timeline_set_global_start_time(
    Timeline* self, RationalTime* global_start_time)
{
    if (!self)
        return;

    nonstd::optional<opentime::RationalTime> rationalTimeOptional = nonstd::nullopt;
    if (global_start_time != NULL)
    {
        rationalTimeOptional = nonstd::optional<opentime::RationalTime>(
            *reinterpret_cast<opentime::RationalTime*>(global_start_time));
    }
    reinterpret_cast<OTIO_NS::Timeline*>(self)->set_global_start_time(
        rationalTimeOptional);
}
OTIO_API RationalTime*
Timeline_duration(Timeline* self, OTIOErrorStatus* error_status)
{
    if (!self)
        return NULL;

    opentime::RationalTime rationalTime =
        reinterpret_cast<OTIO_NS::Timeline*>(self)->duration(
            reinterpret_cast<OTIO_NS::ErrorStatus*>(error_status));
    return reinterpret_cast<RationalTime*>(
        new opentime::RationalTime(rationalTime));
}
OTIO_API TimeRange* Timeline_range_of_child(
    Timeline* self, Composable* child, OTIOErrorStatus* error_status)
{
    if (!self || !child)
        return NULL;

    opentime::TimeRange timeRange =
        reinterpret_cast<OTIO_NS::Timeline*>(self)->range_of_child(
            reinterpret_cast<OTIO_NS::Composable*>(child),
            reinterpret_cast<OTIO_NS::ErrorStatus*>(error_status));
    return reinterpret_cast<TimeRange*>(new opentime::TimeRange(timeRange));
}
OTIO_API TrackVector* Timeline_audio_tracks(Timeline* self)
{
    if (!self)
        return NULL;

    TrackVectorDef trackVector =
        reinterpret_cast<OTIO_NS::Timeline*>(self)->audio_tracks();
    return reinterpret_cast<TrackVector*>(new TrackVectorDef(trackVector));
}
OTIO_API TrackVector* Timeline_video_tracks(Timeline* self)
{
    if (!self)
        return NULL;

    TrackVectorDef trackVector =
        reinterpret_cast<OTIO_NS::Timeline*>(self)->video_tracks();
    return reinterpret_cast<TrackVector*>(new TrackVectorDef(trackVector));
}

OTIO_API const char* Timeline_name(Timeline* self)
{
    if (!self)
        return NULL;

    return SerializableObjectWithMetadata_name(
        (SerializableObjectWithMetadata*) self);
}
OTIO_API void Timeline_set_name(Timeline* self, const char* name)
{
    if (!self)
        return;

    SerializableObjectWithMetadata_set_name(
        (SerializableObjectWithMetadata*) self, name);
}
OTIO_API AnyDictionary* Timeline_metadata(Timeline* self)
{
    if (!self)
        return NULL;

    return SerializableObjectWithMetadata_metadata(
        (SerializableObjectWithMetadata*) self);
}

OTIO_API bool Timeline_to_json_file(
    Timeline*        self,
    const char*      file_name,
    OTIOErrorStatus* error_status,
    int              indent)
{
    if (!self || !file_name)
        return false;

    return SerializableObject_to_json_file(
        reinterpret_cast<OTIOSerializableObject*>(self), file_name, error_status, indent);
}
OTIO_API const char* Timeline_to_json_string(
    Timeline* self, OTIOErrorStatus* error_status, int indent)
{
    if (!self)
        return NULL;

    return SerializableObject_to_json_string(
        reinterpret_cast<OTIOSerializableObject*>(self), error_status, indent);
}
OTIO_API bool Timeline_is_equivalent_to(Timeline* self, OTIOSerializableObject* other)
{
    if (!self || !other)
        return false;

    return SerializableObject_is_equivalent_to(
        reinterpret_cast<OTIOSerializableObject*>(self), other);
}
OTIO_API Timeline* Timeline_clone(Timeline* self, OTIOErrorStatus* error_status)
{
    if (!self)
        return NULL;

    return (Timeline*) SerializableObject_clone(
        reinterpret_cast<OTIOSerializableObject*>(self), error_status);
}
OTIO_API const char* Timeline_schema_name(Timeline* self)
{
    if (!self)
        return NULL;

    return SerializableObject_schema_name(reinterpret_cast<OTIOSerializableObject*>(self));
}
OTIO_API int Timeline_schema_version(Timeline* self)
{
    if (!self)
        return 0;

    return SerializableObject_schema_version(reinterpret_cast<OTIOSerializableObject*>(self));
}
