// Struct to pass around callback data easily.
typedef struct ElementData
{
    void *ctx;
    const xmlChar *localname;
    const xmlChar *prefix;
    const xmlChar *URI;
    int nb_namespaces;
    const xmlChar **namespaces;
    int nb_attributes;
    int nb_defaulted;
    const xmlChar **attributes;
} ElementData ;