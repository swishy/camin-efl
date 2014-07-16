#include <Eo.h>
#include <Eina.h>
#include <libxml/SAX2.h>
#include <ctype.h>
#include "common.h"
#include "xml_sax_base_types.h"
#include "xml_sax_base.eo.h"
#include "amin_elt.eo.h"
#include "amin_machine_spec_document.eo.h"

static const char FILTER_TAG[] = "filter";
static const char BUNDLE_TAG[] = "bundle";
static const char GENERATOR_TAG[] = "generator";
static const char HANDLER_TAG[] = "handler";
static const char LOG_TAG[] = "log";
static const char MACHINE_NAME_TAG[] = "name";

static const char ELEMENT_TAG[] = "element";
static const char NAMESPACE_TAG[] = "namespace";
static const char NAME_TAG[] = "name";
static const char POSITION_TAG[] = "position";
static const char DOWNLOAD_TAG[] = "download";
static const char VERSION_TAG[] = "version";
static const char FILTER_PARAMS_TAG[] = "filter_param";

typedef struct
{
    const char *localname;
    char *element;
    Eo *mparent;
    char *log;
    char *filter_param;
    char *download;
    char *module;
    char *version;
    char *generator;
    char *handler_name;
    char *handler_out;
    const char *element_name;
    char *name;
    const char *machine_name;
    const char *position;
    const char *name_space;
    Eina_Hash *filters;

} Document_Data;

static void
_filter_entry_free_cb(void *data)
{
    free(data);
}

static Eina_Bool
_machine_spec_foreach_cb(const Eina_Hash *modules, const void *key,
        void *data, void *fdata)
{
    const char *name = key;
    LOGF("%s\n", name);
    // Return EINA_FALSE to stop this callback from being called
    return EINA_TRUE;
}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_document_start(Eo *obj, Document_Data *pd, void *user_data)
{
    // Setup Eina_Hash to collect filters found during parsing.
    pd->filters = eina_hash_pointer_new(_filter_entry_free_cb);
}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_element_start(Eo *obj, Document_Data *pd, ElementData *elementData)
{
    int i;

    pd->localname = elementData->localname;

    // Get Module Name
    if ( strncmp ( elementData->localname,FILTER_TAG,sizeof ( FILTER_TAG ) ) == 0 || strncmp ( elementData->localname,BUNDLE_TAG,sizeof ( BUNDLE_TAG ) ) == 0 )
    {
        if ( elementData->nb_attributes > 0 )
        {
            int i = 0;
            int attribute_position = 0;
            char *parse_value;

            // Get values from attributes
            while ( i < elementData->nb_attributes )
            {
                if ( elementData->attributes[attribute_position] != NULL )
                {
                    if ( strncmp ( elementData->attributes[attribute_position],"name",sizeof ( elementData->attributes[attribute_position] ) ) == 0 )
                    {
                        int attribute_length = ( strlen ( elementData->attributes[attribute_position + 3] ) - strlen ( elementData->attributes[attribute_position + 4] ) );
                        pd->module = strndup ( elementData->attributes[attribute_position + 3], attribute_length );
                    }
                }
                attribute_position = attribute_position + 5;
                i++;
            }
        }
    }

    if ( strncmp ( elementData->localname,GENERATOR_TAG,sizeof ( GENERATOR_TAG ) ) == 0 )
    {
        if ( elementData->nb_attributes > 0 )
        {
            int i = 0;
            int attribute_position = 0;
            char *parse_value;

            // Get values from attributes
            while ( i < elementData->nb_attributes )
            {
                if ( elementData->attributes[attribute_position] != NULL )
                {
                    if ( strncmp ( elementData->attributes[attribute_position],"generator",sizeof ( elementData->attributes[attribute_position] ) ) == 0 )
                    {
                        int attribute_length = ( strlen ( elementData->attributes[attribute_position + 3] ) - strlen ( elementData->attributes[attribute_position + 4] ) );
                        pd->generator = strndup ( elementData->attributes[attribute_position + 3], attribute_length );
                    }
                }
                attribute_position = attribute_position + 5;
                i++;
            }
        }
    }

    if ( strncmp ( elementData->localname,HANDLER_TAG,sizeof ( HANDLER_TAG ) ) == 0 )
    {
        if ( elementData->nb_attributes > 0 )
        {
            int i = 0;
            int attribute_position = 0;
            char *parse_value;

            // Get values from attributes
            while ( i < elementData->nb_attributes )
            {
                if ( elementData->attributes[attribute_position] != NULL )
                {
                    if ( strncmp ( elementData->attributes[attribute_position],"handler",sizeof ( elementData->attributes[attribute_position] ) ) == 0 )
                    {
                        int attribute_length = ( strlen ( elementData->attributes[attribute_position + 3] ) - strlen ( elementData->attributes[attribute_position + 4] ) );
                        pd->handler_name = strndup ( elementData->attributes[attribute_position + 3], attribute_length );
                    }

                    if ( strncmp ( elementData->attributes[attribute_position],"output",sizeof ( elementData->attributes[attribute_position] ) ) == 0 )
                    {
                        int attribute_length = ( strlen ( elementData->attributes[attribute_position + 3] ) - strlen ( elementData->attributes[attribute_position + 4] ) );
                        pd->handler_out = strndup ( elementData->attributes[attribute_position + 3], attribute_length );
                    }
                }
                attribute_position = attribute_position + 5;
                i++;
            }
        }
    }

    if ( strncmp ( elementData->localname,LOG_TAG,sizeof ( LOG_TAG ) ) == 0 )
    {
        if ( elementData->nb_attributes > 0 )
        {
            int i = 0;
            int attribute_position = 0;
            char *parse_value;

            // Get values from attributes
            while ( i < elementData->nb_attributes )
            {
                if ( elementData->attributes[attribute_position] != NULL )
                {
                    if ( strncmp ( elementData->attributes[attribute_position],"log",sizeof ( elementData->attributes[attribute_position] ) ) == 0 )
                    {
                        int attribute_length = ( strlen ( elementData->attributes[attribute_position + 3] ) - strlen ( elementData->attributes[attribute_position + 4] ) );
                        pd->generator = strndup ( elementData->attributes[attribute_position + 3], attribute_length );
                    }
                }
                attribute_position = attribute_position + 5;
                i++;
            }
        }
    }

}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_element_char(Eo *obj, Document_Data *pd, void *data, const xmlChar *string, int string_len)
{
    // ref important bytes passed in if they arent whitespace.
    if (string_len > 0 && !isspace(*string))
    {
        if ( strncmp ( pd->localname,ELEMENT_TAG,sizeof ( ELEMENT_TAG ) ) == 0 )
        {
            pd->element_name = strndup ( string, string_len );
        }
        if ( strncmp ( pd->localname,NAMESPACE_TAG,sizeof ( NAMESPACE_TAG ) ) == 0 )
        {
            pd->name_space = strndup ( string, string_len );
        }
        if ( strncmp ( pd->localname,NAME_TAG,sizeof ( NAME_TAG ) ) == 0 )
        {
            pd->name = strndup ( string, string_len );
        }
        /**if ( strncmp ( pd->localname,MACHINE_TAG,sizeof ( MACHINE_TAG ) ) == 0 )
        {
        pd->machine_name = strndup ( string, string_len );
        }*/
        if ( strncmp ( pd->localname,POSITION_TAG,sizeof ( POSITION_TAG ) ) == 0 )
        {
            pd->position = strndup ( string, string_len );
        }
        if ( strncmp ( pd->localname,DOWNLOAD_TAG,sizeof ( DOWNLOAD_TAG ) ) == 0 )
        {
            pd->position = strndup ( string, string_len );
        }
        if ( strncmp ( pd->localname,VERSION_TAG,sizeof ( VERSION_TAG ) ) == 0 )
        {
            pd->position = strndup ( string, string_len );
        }
        if ( strncmp ( pd->localname,FILTER_PARAMS_TAG,sizeof ( FILTER_PARAMS_TAG ) ) == 0 )
        {
            pd->position = strndup ( string, string_len );
        }
    }
}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_element_end(Eo *obj, Document_Data *pd, ElementData *data)
{
    const Eo_Class *current_class = eo_class_get ( obj );
    LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );

    if ( strncmp ( data->localname,FILTER_TAG,sizeof ( FILTER_TAG ) ) == 0 )
    {
        Filter_Data *filter = malloc( sizeof(Filter_Data) );

        filter->element = pd->element_name;
        filter->name_space = pd->name_space;
        filter->name = pd->name;
        filter->position = pd->position;
        filter->download = pd->download;
        filter->version = pd->version;
        filter->module = pd->module;
        if(!eina_hash_add(pd->filters, filter->name, filter))
        {
            LOG("Failed to add filter to filters hash!");
        }
    }
}

EOLIAN static void
_amin_machine_spec_document_xml_sax_base_document_end(Eo *obj, Document_Data *pd, void *data)
{
    const Eo_Class *current_class = eo_class_get ( obj );
    LOGF ( "Class is : %s %s", eo_class_name_get ( current_class ), __func__ );

    Eina_Hash *filters = eo_do(obj, amin_machine_spec_document_filters_get());

    if(filters != NULL)
    {
        LOG("Calling foreach in document.c.");
        eina_hash_foreach(filters, _machine_spec_foreach_cb, NULL);
    } else {
        LOG("Filters are null :(");
    }

    Eo *parent = eo_do(obj, eo_parent_get());

    Xml_Base_Data *xd = eo_data_scope_get(parent, XML_SAX_BASE_CLASS);

    if(!xd) eo_error_set(obj);

    xd->result = obj;
}

EOLIAN static Eina_Hash *
_amin_machine_spec_document_filters_get(Eo *obj, Document_Data *pd)
{
    return pd->filters;
}

#include "amin_machine_spec_document.eo.c"



