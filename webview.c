/* webview extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "webview.h"
#include "ext/standard/info.h"
#include "php_webview.h"
#include "webview_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE()  \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

zend_result php_json_decode_ex(zval *return_value, const char *str, size_t str_len, zend_long options, zend_long depth);

static zend_object_handlers webview_object_handlers;

typedef struct php_webview_t
{
	webview_t native;
	zend_object std;
} php_webview_t;

typedef struct bind_arg_t
{
	webview_t native;
	zend_fcall_info *fci;
	zend_fcall_info_cache *fcc;
} bind_arg_t;

#define Z_WEBVIEW_P(zv) \
	((php_webview_t *)((char *)(Z_OBJ_P(zv)) - XtOffsetOf(php_webview_t, std)))

zend_object *webview_new(zend_class_entry *ce)
{
	php_webview_t *wv = zend_object_alloc(sizeof(php_webview_t), ce);

	zend_object_std_init(&wv->std, ce);
	wv->std.handlers = &webview_object_handlers;
	return &wv->std;
}

PHP_METHOD(Webview, __construct)
{
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);
	zend_long debug = 0;

	ZEND_PARSE_PARAMETERS_START(0, 1)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(debug)
	ZEND_PARSE_PARAMETERS_END();

	if (ZEND_NUM_ARGS() > 0)
	{
		zend_update_property_long(Z_OBJCE_P(ZEND_THIS), Z_OBJ_P(ZEND_THIS),
								  "debug", sizeof("debug") - 1, debug);
	}

	container->native = webview_create((int) debug, NULL);
}

PHP_METHOD(Webview, __destruct)
{
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);
	webview_destroy(container->native);
}

PHP_METHOD(Webview, set_title)
{
	zval *title;
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ZVAL(title)
	ZEND_PARSE_PARAMETERS_END();

	webview_set_title(container->native, Z_STRVAL(*title));
}

PHP_METHOD(Webview, set_html)
{
	zval *html;
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ZVAL(html)
	ZEND_PARSE_PARAMETERS_END();

	webview_set_html(container->native, Z_STRVAL(*html));
}

PHP_METHOD(Webview, set_size)
{
	zend_long width, height, hint = 0;
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

	ZEND_PARSE_PARAMETERS_START(2, 3)
	Z_PARAM_LONG(width);
	Z_PARAM_LONG(height);
	Z_PARAM_OPTIONAL
	if (ZEND_NUM_ARGS() > 2)
	{
		Z_PARAM_LONG(hint);
	}
	ZEND_PARSE_PARAMETERS_END();

	webview_set_size(container->native, (int) width, (int) height, hint);
}

PHP_METHOD(Webview, navigate)
{
	zval *url;
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ZVAL(url)
	ZEND_PARSE_PARAMETERS_END();

	webview_navigate(container->native, Z_STRVAL(*url));
}

PHP_METHOD(Webview, init)
{
	zval *js;
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ZVAL(js)
	ZEND_PARSE_PARAMETERS_END();

	webview_init(container->native, Z_STRVAL(*js));
}

PHP_METHOD(Webview, eval)
{
	zval *js;
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ZVAL(js)
	ZEND_PARSE_PARAMETERS_END();

	webview_eval(container->native, Z_STRVAL(*js));
}

PHP_METHOD(Webview, run)
{
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

	webview_run(container->native);
}

void bind_callback_handler(const char *seq, const char *req, void *arg)
{
	bind_arg_t *context = (bind_arg_t *)arg;

	zval args;
	zval *result = emalloc(sizeof(zval));
	context->fci->retval = result;
	context->fci->param_count = 0;

	if (strlen(req) > 0) {
		php_json_decode_ex(&args, req, strlen(req), 1, 512);
		context->fci->param_count = zend_array_count(Z_ARRVAL(args));
		zend_fcall_info_args(context->fci, &args);
	}

	if(zend_call_function(context->fci, context->fcc) == SUCCESS){
		if (ZVAL_IS_NULL(result)) {
			ZVAL_STRING(result, "[]");
		}
		webview_return(context->native, seq, 0, Z_STRVAL_P(result));
	} else {
		webview_return(context->native, seq, 1, "[]");
	}
	zval_ptr_dtor(result);
	zval_ptr_dtor(&args);
}

PHP_METHOD(Webview, bind)
{
	zval *name;
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

    bind_arg_t *context = emalloc(sizeof(bind_arg_t));
    context->native = container->native;
    context->fci = emalloc(sizeof(zend_fcall_info));
    context->fcc = emalloc(sizeof(zend_fcall_info_cache));

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_ZVAL(name)
	Z_PARAM_FUNC(*context->fci, *context->fcc)
	ZEND_PARSE_PARAMETERS_END();

    Z_TRY_ADDREF(context->fci->function_name);
    if (context->fci->object != NULL){
        ++context->fci->object->gc.refcount; // @todo: really needed?
    }

	webview_bind(container->native, Z_STRVAL(*name), bind_callback_handler, context);
}

PHP_METHOD(Webview, unbind)
{
	zval *name;
	php_webview_t *container = Z_WEBVIEW_P(ZEND_THIS);

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ZVAL(name)
	ZEND_PARSE_PARAMETERS_END();

	webview_unbind(container->native, Z_STRVAL(*name));
}

PHP_MINIT_FUNCTION(webview)
{
	zend_class_entry *ce = register_class_Webview();

	ce->create_object = webview_new;

	memcpy(&webview_object_handlers, &std_object_handlers,
		   sizeof(zend_object_handlers));
	webview_object_handlers.offset = XtOffsetOf(php_webview_t, std);

	REGISTER_LONG_CONSTANT("WEBVIEW_HINT_NONE", 0, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("WEBVIEW_HINT_MIN", 1, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("WEBVIEW_HINT_MAX", 2, CONST_CS | CONST_PERSISTENT);
	REGISTER_LONG_CONSTANT("WEBVIEW_HINT_FIXED", 3, CONST_CS | CONST_PERSISTENT);

	return SUCCESS;
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(webview)
{
#if defined(ZTS) && defined(COMPILE_DL_WEBVIEW)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(webview)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "webview support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ webview_module_entry */
zend_module_entry webview_module_entry = {
	STANDARD_MODULE_HEADER,
	"webview",			 /* Extension name */
	NULL,		 /* zend_function_entry */
	PHP_MINIT(webview),	 /* PHP_MINIT - Module initialization */
	NULL,				 /* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(webview),	 /* PHP_RINIT - Request initialization */
	NULL,				 /* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(webview),	 /* PHP_MINFO - Module info */
	PHP_WEBVIEW_VERSION, /* Version */
	STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_WEBVIEW
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(webview)
#endif
