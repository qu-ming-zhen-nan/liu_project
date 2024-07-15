#include <stddef.h> /* size_t */
#include<string>
#include "source.h"
class parse {
private:
	typedef struct {
		std::string json;
		int index;
	}context;
	context ss;
	//context s_obj;
public:
	parse(){
		context s;
		s.index = 0;
		ss = s;
	}
	int json_parse(json_value* v, std::string json);
	int json_parse_value(context&s,json_value* v);
	 void json_parse_whitespace(context& s);
	 int  json_parse_null(context& c, json_value* v);
	 int  json_parse_true(context& c, json_value* v);
	 int  json_parse_false(context& c, json_value* v);
	 int json_parse_string(context& c, json_value* v);
	 int json_parse_object(context& c, json_value* v);
	 double json_get_number(json_value* v);
	json_type json_get_type(const json_value* v);
	int json_parse_number(context& c, json_value* v);
	void json_set_string(json_value* v, std::string s);
	void json_parse_unicode(context& c, json_value* v);
	json_value* json_parse_tree;
	size_t json_get_array_size(json_value* v);
	json_value* json_get_array_element(json_value* v, int index);
	 int json_parse_array(context& c, json_value* v);
	 std::string trimLeftSpaces(const std::string& str);
	 std::string trimRightSpaces(const std::string& str);

	
	std:: string get_json_string(json_value*v,int index);

};