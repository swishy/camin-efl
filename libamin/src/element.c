#include <Eo.h>
#include "element.eo.h"

typedef struct
{
    void *ctx;
    const char *localname;
    const char *prefix;
    const char *uri;
    const char *namespaces;
    const char *attributes;
    int nb_namespaces;
    int nb_attributes;
    int nb_defaulted;
} Element_Data;

EOLIAN static void
_element_context_set(Eo *obj, Element_Data *pd, void *context)
{
    pd->ctx = context;
}

EOLIAN static void *
_element_context_get(const Eo *obj, Element_Data *pd)
{
    return pd->ctx;
}

EOLIAN static void
_element_localname_set(Eo *obj, Element_Data *pd, const char *localname)
{
    pd->localname = localname;
}

EOLIAN static const char *
_element_localname_get(const Eo *obj, Element_Data *pd)
{
    return pd->localname;
}

EOLIAN static void
_element_prefix_set(Eo *obj, Element_Data *pd, const char *prefix)
{
    pd->prefix = prefix;
}

EOLIAN static const char *
_element_prefix_get(const Eo *obj, Element_Data *pd)
{
    return pd->prefix;
}

EOLIAN static void
_element_uri_set(Eo *obj, Element_Data *pd, const char *uri)
{
    pd->uri = uri;
}

EOLIAN static const char *
_element_uri_get(const Eo *obj, Element_Data *pd)
{
    return pd->uri;
}

EOLIAN static void
_element_namespaces_set(Eo *obj, Element_Data *pd, const char *namespaces)
{
    pd->namespaces = namespaces;
}

EOLIAN static const char *
_element_namespaces_get(const Eo *obj, Element_Data *pd)
{
    return pd->namespaces;
}

EOLIAN static void
_element_attributes_set(Eo *obj, Element_Data *pd, const char *attributes)
{
    pd->attributes = attributes;
}

EOLIAN static const char *
_element_attributes_get(const Eo *obj, Element_Data *pd)
{
    return pd->attributes;
}

EOLIAN static void
_element_nb_namespaces_set(Eo *obj, Element_Data *pd, int nb_namespaces)
{
    pd->nb_namespaces = nb_namespaces;
}

EOLIAN static int
_element_nb_namespaces_get(const Eo *obj, Element_Data *pd)
{
    return pd->nb_namespaces;
}

EOLIAN static void
_element_nb_attributes_set(Eo *obj, Element_Data *pd, int nb_attributes)
{
    pd->nb_attributes = nb_attributes;
}

EOLIAN static int
_element_nb_attributes_get(const Eo *obj, Element_Data *pd)
{
    return pd->nb_attributes;
}

EOLIAN static void
_element_nb_defaulted_set(Eo *obj, Element_Data *pd, int nb_defaulted)
{
    pd->nb_defaulted = nb_defaulted;
}

EOLIAN static int
_element_nb_defaulted_get(const Eo *obj, Element_Data *pd)
{
    return pd->nb_defaulted;
}

#include "element.eo.c"
