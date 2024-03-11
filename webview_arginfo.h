/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: a322bb44f53cbd70139e4f90258718206586c5e6 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_test1, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Webview___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, debug, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Webview_hello, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, salutation, IS_STRING, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(test1);
ZEND_METHOD(Webview, __construct);
ZEND_METHOD(Webview, hello);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(test1, arginfo_test1)
	ZEND_FE_END
};


static const zend_function_entry class_Webview_methods[] = {
	ZEND_ME(Webview, __construct, arginfo_class_Webview___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Webview, hello, arginfo_class_Webview_hello, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Webview(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "Webview", class_Webview_methods);
	class_entry = zend_register_internal_class_ex(&ce, NULL);

	zval property_debug_default_value;
	ZVAL_LONG(&property_debug_default_value, 0);
	zend_string *property_debug_name = zend_string_init("debug", sizeof("debug") - 1, 1);
	zend_declare_typed_property(class_entry, property_debug_name, &property_debug_default_value, ZEND_ACC_PRIVATE, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_debug_name);

	return class_entry;
}
