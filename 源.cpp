#include <iostream>
#include "json_prase.h"
using namespace std;
static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)
#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")


#define EXPECT_EQ_DOUBLE(expect,actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%lf")

#define EXPECT_EQ_STRING(expect, actual) \
 do {\
      test_count++;            \
        if (expect != actual) {\
             fprintf(stderr, "%s:%d: expect: actual: \n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
}else{ \
test_pass++;}\
} while (0)


static void test_parse_null();
static void test_parse_false();
static void test_parse_true();
static void test_parse_is_blank();
static void test_parse_invalid_value();
static void test_parse_multiple_words();
static void test_parse_number_too_big();
static void test_parse_number();
static void test_parse_string();
static void test_parse_string_error();
static void test_parse_array();
static void test_parse_obj();
static void test_parse() {
   /* test_parse_null();
    test_parse_false();
    test_parse_true();
    test_parse_is_blank();
    test_parse_invalid_value();
    test_parse_multiple_words();
    test_parse_number();
    test_parse_number_too_big();
    test_parse_string();
    test_parse_string_error();
    test_parse_array();*/
    test_parse_obj();
}

int main() {

    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;


}






static void test_number2(double number, string s) {
    json_value v;
    parse test;
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_OK, test.json_parse(&v, s));
    EXPECT_EQ_INT(json_NUMBER, test.json_get_type(&v));
    EXPECT_EQ_DOUBLE(number, test.json_get_number(&v));

}
static void test_parse_number() {
    test_number2(0.0, "0");
    test_number2(0.0, "-0");
    test_number2(0.0, "-0.0");
    test_number2(1.0, "1");
    test_number2(-1.0, "-1");
    test_number2(1.5, "1.5");
    test_number2(-1.5, "-1.5");
    test_number2(3.1416, "3.1416");
    test_number2(1E10, "1E10");
    test_number2(1e10, "1e10");
    test_number2(1E+10, "1E+10");
    test_number2(1E-10, "1E-10");
    test_number2(-1E10, "-1E10");
    test_number2(-1e10, "-1e10");
    test_number2(-1E+10, "-1E+10");
    test_number2(-1E-10, "-1E-10");
    test_number2(1.234E+10, "1.234E+10");
    test_number2(1.234E-10, "1.234E-10");





}
static void test_parse_null() {
    json_value v;
    parse* test = new parse();
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_OK, test->json_parse(&v, "null"));
    EXPECT_EQ_INT(json_NULL, test->json_get_type(&v));
}
static void test_parse_false() {
    json_value v;
    parse* test = new parse();
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_OK, test->json_parse(&v, "false"));
    EXPECT_EQ_INT(json_FALSE, test->json_get_type(&v));

}
static void test_parse_true() {
    json_value v;
    parse test;
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_OK, test.json_parse(&v, "true"));
    EXPECT_EQ_INT(json_TRUE, test.json_get_type(&v));
}
static void test_parse_is_blank() {
    json_value v;

    parse test;
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_IS_BLANK, test.json_parse(&v, ""));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));

    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_IS_BLANK, test.json_parse(&v, " "));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
}
static void test_parse_multiple_words() {
    json_value v;

    parse test;
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_MULTIPLE_WORD, test.json_parse(&v, "null ad"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));

    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_MULTIPLE_WORD, test.json_parse(&v, "false true"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_MULTIPLE_WORD, test.json_parse(&v, "true true"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
}
static void test_parse_number_too_big() {
    json_value v;

    parse test;
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_NUMBER_TOO_BIG, test.json_parse(&v, "1e562"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));


}
static void test_parse_invalid_value() {
    json_value v;

    parse test;
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_INVALID_VALUE, test.json_parse(&v, "nul"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));

    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_INVALID_VALUE, test.json_parse(&v, "+0"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_INVALID_VALUE, test.json_parse(&v, "+1"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_INVALID_VALUE, test.json_parse(&v, ".265"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_INVALID_VALUE, test.json_parse(&v, "INF"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_INVALID_VALUE, test.json_parse(&v, "inf"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_INVALID_VALUE, test.json_parse(&v, "0..1"));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
}
static void test_string(string a, string b) {
    json_value v;

    parse test;
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_OK, test.json_parse(&v, b));
    EXPECT_EQ_INT(json_STRING, test.json_get_type(&v));
    EXPECT_EQ_STRING(a, v.s);
  
  
}
 
static void test_parse_string() {
    test_string("", "\"\"");
   test_string("Hello", "\"Hello\"");
    test_string("Hello\nWorld", "\"Hello\\nWorld\"");
    test_string("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
    
   // test_string("", "\"\\u0000\"");
}
static void test_parse_string_error2(int error,string b) {
    json_value v;

    parse test;
    v.type = json_FALSE;
    EXPECT_EQ_INT(error, test.json_parse(&v, b));
    EXPECT_EQ_INT(json_FAITH, test.json_get_type(&v));
    

}
static void test_parse_string_error() {
   
   
   test_parse_string_error2(PARSE_STRING_ERROR, "\"");
   test_parse_string_error2(PARSE_ESPACE_ERROR, "\"\\v\"");
   test_parse_string_error2(PARSE_ESPACE_ERROR, "\"\\'\"");
   test_parse_string_error2(PARSE_ESPACE_ERROR, "\"\\0\"");
   test_parse_string_error2(PARSE_ESPACE_ERROR, "\"\\x12\"");


}

static void test_parse_array() {
    json_value v;

    parse test;
    v.type = json_FALSE;

   EXPECT_EQ_INT(PARSE_OK, test.json_parse(&v, "[ ]"));
   
   EXPECT_EQ_INT(json_ARRAY, test.json_get_type(&v));
    EXPECT_EQ_INT(0, test.json_get_array_size(&v));

    v.type = json_FALSE;

    EXPECT_EQ_INT(PARSE_OK, test.json_parse(&v, "[ ]"));

    EXPECT_EQ_INT(json_ARRAY, test.json_get_type(&v));
    EXPECT_EQ_INT(0, test.json_get_array_size(&v));


    v.type = json_FALSE;

    EXPECT_EQ_INT(PARSE_OK, test.json_parse(&v, "[ null , false , true , 123 , \"abc\" ]"));

    EXPECT_EQ_INT(json_ARRAY, test.json_get_type(&v));
    EXPECT_EQ_INT(5, test.json_get_array_size(&v));

   EXPECT_EQ_INT(json_NULL, test.json_get_type(test.json_get_array_element(&v,0)));
    EXPECT_EQ_INT(json_FALSE, test.json_get_type(test.json_get_array_element(&v, 1)));
   EXPECT_EQ_INT(json_TRUE, test.json_get_type(test.json_get_array_element(&v, 2)));
    EXPECT_EQ_INT(json_NUMBER, test.json_get_type(test.json_get_array_element(&v, 3)));
    EXPECT_EQ_INT(json_STRING, test.json_get_type(test.json_get_array_element(&v, 4)));
   EXPECT_EQ_DOUBLE(123.0, test.json_get_number(test.json_get_array_element(&v, 3)));

    v.free();

    EXPECT_EQ_INT(PARSE_OK, test.json_parse(&v, "[ [[], [0] ,  [  0 , 1 ] , [ [ 0 , 1 , 2 ]] ]]"));
    
    EXPECT_EQ_INT(json_ARRAY, test.json_get_type(&v));
  EXPECT_EQ_INT(1, test.json_get_array_size(&v));
 
}


static void test_parse_obj() {
    json_value v;

    parse test;
    v.type = json_FALSE;
    EXPECT_EQ_INT(PARSE_OBJECT_BRACES, test.json_parse(&v, "{ \"cd\": 0 "));


    v.free();
    EXPECT_EQ_INT(PARSE_OK, test.json_parse(&v, "{ \"cd\": 0 }"));

    EXPECT_EQ_INT(json_OBJECT, test.json_get_type(&v));
    EXPECT_EQ_INT(1, test.json_get_array_size(&v));
   

    v.free();
    EXPECT_EQ_INT(PARSE_OK, test.json_parse(&v,
        " { "
        "\"n\" : null , "
        "\"f\" : false , "
        "\"t\" : true , "
        "\"i\" : 123 , "
        "\"s\" : \"abc\", "
        "\"a\" : [ 1, 2, 3 ],"
        "\"o\" : { \"1\" : 1, \"2\" : 2, \"3\" : 3 }"
        " } "
    ));

    EXPECT_EQ_INT(json_OBJECT, test.json_get_type(&v));
    EXPECT_EQ_INT(7, test.json_get_array_size(&v));
    string s = test.get_json_string(&v, 0);
    cout << s << endl;

}