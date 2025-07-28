#ifndef PHP_LITEHTMLTOPNG_H
#define PHP_LITEHTMLTOPNG_H

extern zend_module_entry litehtmltopng_module_entry;
#define phpext_litehtmltopng_ptr &litehtmltopng_module_entry

int litehtmltopng_render_file(const char* html_file, const char* output_file);

#endif
