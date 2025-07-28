#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_litehtmltopng.h"
#include <stdlib.h>

int litehtmltopng_render_file(const char* html_file, const char* output_file);

ZEND_BEGIN_ARG_INFO(arginfo_litehtmltopng_version, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_litehtmltopng_render, 0, 0, 2)
    ZEND_ARG_TYPE_INFO(0, html_file, IS_STRING, 0)
    ZEND_ARG_TYPE_INFO(0, output_file, IS_STRING, 0)
ZEND_END_ARG_INFO()

static PHP_FUNCTION(litehtmltopng_version)
{
    RETURN_STRING("0.1");
}

static PHP_FUNCTION(litehtmltopng_render)
{
    char *html_file = NULL, *output_file = NULL;
    size_t html_len = 0, out_len = 0;

    ZEND_PARSE_PARAMETERS_START(2,2)
        Z_PARAM_STRING(html_file, html_len)
        Z_PARAM_STRING(output_file, out_len)
    ZEND_PARSE_PARAMETERS_END();

    int ret = litehtmltopng_render_file(html_file, output_file);
    RETURN_LONG(ret);
}

static const zend_function_entry litehtmltopng_functions[] = {
    PHP_FE(litehtmltopng_version, arginfo_litehtmltopng_version)
    PHP_FE(litehtmltopng_render, arginfo_litehtmltopng_render)
    PHP_FE_END
};

zend_module_entry litehtmltopng_module_entry = {
    STANDARD_MODULE_HEADER,
    "litehtmltopng",
    litehtmltopng_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "0.1",
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_LITEHTMLTOPNG
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(litehtmltopng)
#endif
