#include<vector>
typedef enum { json_NULL, json_FALSE, json_TRUE, json_NUMBER, json_STRING, json_ARRAY, json_OBJECT,json_COL,json_FAITH } json_type;//最后一个为项代表对象中的一个
typedef enum {
    PARSE_OK = 0,
  PARSE_IS_BLANK,
  PARSE_MULTIPLE_WORD,
    PARSE_INVALID_VALUE,
    PARSE_NUMBER_TOO_BIG,
    PARSE_STRING_ERROR,
    PARSE_ESPACE_ERROR,
    PARSE_UNICODE_ERRPR,
    PARSE_ARRAY_COMMA,
    PARSE_ARRAY_BRACKET,
    PARSE_OBJECT_BRACES


}error_mes;//解析结果
typedef struct json_value json_value;

struct json_value {
    std::string s;
    double value;
    std::vector<json_value*> child;//可用以存储嵌套类型，如array以及object
   
    json_type type;
    void free() {
        type = json_FALSE;
        value = 0;
        child.erase(child.begin(), child.end());
        s = "";
    }
};//json解析树形结果结点

