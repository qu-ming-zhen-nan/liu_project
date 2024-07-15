#include "json_prase.h"
#include <iostream>
#include <assert.h> 
#include <regex>  
#include <sstream>  
#include<stack>
#include <iomanip>
#define EXPECT(c, ch) do {  \
assert(c.index < c.json.size()); \
	assert(c.json[c.index++] == (ch)); \
}while (0);

bool isValidJsonNumber(const std::string & str) {
	// 正则表达式匹配可能的JSON数字格式  
	std::regex jsonNumberRegex(
		R"(-?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][-+]?\d+)?)"
	);

	return std::regex_match(str, jsonNumberRegex);
}
std::string removeLastClosingParenthesis(const std::string& str) {
	std::string result = str; // 复制原始字符串，避免修改原字符串  
	size_t pos = result.rfind('}'); // 从后往前查找最后一个右括号  
	if (pos != std::string::npos) { // 如果找到了  
		result.resize(pos); // 调整字符串大小，去除最后一个右括号  
	}
	return result;
}

using namespace std;
 void parse::json_parse_whitespace(context& c) {
	
	 int n = c.json.size();
	 int i = c.index;
	 while (i < n) {
		 
		 if (c.json[i]!= ' ')break;
		 
		 i++;
	 }
	// std::string copied = c.json.substr(i);
	 //c.json = copied;
	 c.index = i;
}
 int parse::json_parse_null(context& c, json_value* v) {
	 EXPECT(c, 'n');
	 if (c.json[c.index] != 'u' || c.json[c.index+1] != 'l' || c.json[c.index+2] != 'l')
		 return PARSE_INVALID_VALUE;
	 c.index += 3;
	 v->type = json_NULL;

	 json_parse_whitespace(c);
	 if (c.index != c.json.size()) {
		 v->type = json_FAITH;
		 return PARSE_MULTIPLE_WORD;
	 }
	 return PARSE_OK;
	 
 }

 int parse::json_parse_true(context& c, json_value* v) {
	 EXPECT(c, 't');
	 if (c.json[c.index] != 'r' || c.json[c.index + 1] != 'u' || c.json[c.index + 2] != 'e')
		 return PARSE_INVALID_VALUE;
	 c.index += 3;
	 v->type = json_TRUE;
	 json_parse_whitespace(c);
	 if (c.index != c.json.size()) {
		 v->type = json_FAITH;
		 return PARSE_MULTIPLE_WORD;
	 }
	 return PARSE_OK;

 }
 int parse::json_parse_false(context& c, json_value* v) {
	 EXPECT(c, 'f');
	 if (c.json[c.index] != 'a' || c.json[c.index + 1] != 'l' || c.json[c.index + 2] != 's'||c.json[c.index+3]!='e')
		 return PARSE_INVALID_VALUE;
	 c.index += 4;
	 v->type = json_FALSE;
	
	 json_parse_whitespace(c);
	 if (c.index != c.json.size()) {
		 v->type = json_FAITH;
		 return PARSE_MULTIPLE_WORD;
	 }

	 return PARSE_OK;

 }

int parse::json_parse(json_value* v, std::string json) {
	assert(v != NULL);
	ss.json = json;
	
	ss.index = 0;
	v->type = json_FAITH;
	json_parse_whitespace(ss);


	return json_parse_value(ss, v);
}
int parse::json_parse_value(context&c, json_value* v) {
	
	switch (c.json[c.index]) {
	case 'n':  return json_parse_null(c, v);
	case '"': return json_parse_string(c, v);
	case 'f':return json_parse_false(c, v);
	case 't': return json_parse_true(c, v);
	case '[':  return json_parse_array(c,v);
	case '{': return json_parse_object(c, v);
	case '\0': return PARSE_IS_BLANK;
	
	case '-':case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9': return json_parse_number(c,v);
	
	default:  return PARSE_INVALID_VALUE;
	}
}
int parse::json_parse_number(context& c, json_value* v) {
	double num = 0;
		
	c.json = trimRightSpaces(c.json); 
	c.json = trimLeftSpaces(c.json);
	
	try {

		bool a = isValidJsonNumber(c.json);
		if (!a) {
			v->type = json_FAITH;
			return PARSE_INVALID_VALUE;
		}
		 num = std::stod(c.json);
	
		//std::cout << "转换后的double值为: " << num << std::endl;
	}
	catch (const std::invalid_argument& e) {
		//std::cerr << "无效的参数: " << e.what() << std::endl;
		v->type = json_FAITH;
		v->value = 0;
		return PARSE_INVALID_VALUE;
	}
	catch (const std::out_of_range& e) {
	//	std::cerr << "数值范围错误: " << e.what() << std::endl;
		v->value = 0;
		v->type = json_FAITH;
		return PARSE_NUMBER_TOO_BIG;
	}
	
	v->type = json_NUMBER;
	v->value = num;

	//无需去空，正则表达式已经判断
	return PARSE_OK;
}
void parse::json_parse_unicode(context&c,json_value*v) {

}
bool isblank(std::string a) {
	for (auto s : a) {
		if (s != ' ')return false;
	}
	
	return true;
}
std::string parse::trimLeftSpaces(const std::string& str) {
	size_t start = str.find_first_not_of(' '); // 查找第一个非空格字符的位置  
	if (start == std::string::npos) {
		// 如果没有找到非空格字符，则返回空字符串  
		return "";
	}
	return str.substr(start); // 返回从第一个非空格字符开始到字符串末尾的子串  
}
std::string parse:: trimRightSpaces(const std::string& str) {
	size_t end = str.find_last_not_of(' ');
	if (end == std::string::npos) return "";
	return str.substr(0, end + 1); // 但由于 end 是索引，所以实际上是到 end（不包括 end+1 的位置）  
	// 或者更准确地，因为 +1 是多余的：  
	return str.substr(0, end);
}

int parse:: json_parse_string(context& c, json_value* v) {
	
	assert(v != NULL);

	c.index++;	
	
	//std::istringstream iss(v->s);
	v->s = "";
	std::string sss = "";
	while (c.index<c.json.size()) {
		sss += c.json[c.index];
		c.index++;
	
	}
	//std::cout << sss << std::endl;
	/*if (c.index == c.json.size()) {
		v->s = "";
		
		return PARSE_STRING_ERROR;
	}*/
	//处理转义字符
	int i = 0,n=sss.size();
	while (i < n) {
		switch (sss[i]) {
		case '\\': {
			i++;
			if (i == n)return PARSE_ESPACE_ERROR;
			switch (sss[i]) {


			case '\"':v->s += "\""; i++; break;
			case '\\': v->s += "\\"; i++; break;
			case '/':  v->s += "\/"; i++; break;
			case 'b':  v->s += "\b"; i++; break;
			case 'f':  v->s += "\f"; i++; break;
			case 'n':  v->s += "\n"; i++; break;
			case 'r':   v->s += "\r"; i++; break;
			case 't':  v->s += "\t"; i++; break;
			case 'u': {
				if (c.index + 4 >= c.json.size()) {
					v->s = "";
					std::cout << "Incomplete \\u escape sequence\n";
					v->type = json_FAITH;
					return PARSE_ESPACE_ERROR;
				}

				std::string unicode_hex(c.json.substr(c.index + 1, 4));
				char32_t unicode_char = std::stoull(unicode_hex, nullptr, 16);
				c.index += 4; 
				// 跳过 \u 和随后的四个十六进制数字  

				// 将 Unicode 字符转换为 UTF-8 编码的字符串  
				// 注意：这里简化处理，仅处理 BMP 内的字符（基本多文种平面）  
				if (unicode_char <= 0x7F) {
					v->s += static_cast<char>(unicode_char);
				}
				else if (unicode_char <= 0x7FF) {
					v->s += static_cast<char>((unicode_char >> 6) | 0xC0);
					v->s += static_cast<char>((unicode_char & 0x3F) | 0x80);
				}
				else if (unicode_char <= 0xFFFF) {
					v->s += static_cast<char>((unicode_char >> 12) | 0xE0);
					v->s += static_cast<char>(((unicode_char >> 6) & 0x3F) | 0x80);
					v->s += static_cast<char>((unicode_char & 0x3F) | 0x80);
				}
				else {
					// 处理超出基本多文种平面的字符（需要 UTF-16 代理对或直接使用 UTF-32）  
					// 这里简单返回错误 
					v->type = json_FAITH;
					return PARSE_UNICODE_ERRPR;
				}
			}
			default:
				v->type = json_FAITH;
				return PARSE_ESPACE_ERROR;


		}
			}
		default: {
			
			v->s += sss[i];
			i++;
		}



		}


	}
	          //去除尾空格
	v->s=trimRightSpaces(v->s);
	 if (!v->s.empty()&&v->s[v->s.size()-1]=='\"') {
			v->s.erase(v->s.size() - 1);
		}
		
	
	else {
		 v->type = json_FAITH;
		return PARSE_STRING_ERROR;
	}
	v->type = json_STRING;
	return PARSE_OK;
}
void parse:: json_set_string(json_value* v, std::string s) {
	assert(v != NULL );
	v->s = s;
	
	v->type = json_STRING;
}
size_t parse::json_get_array_size(json_value* v) {
	assert(v != NULL );
	return v->child.size();
}
json_value* parse:: json_get_array_element( json_value* v, int index) {
	assert(v != NULL );
	assert(index < v->child.size());
	return v->child[index];
}









int  parse::json_parse_array(context& c, json_value* v) {
	
	int lev = 0;//递归层数
	c.index++;
	std::vector<std::string>nums;//用以存储数组中的资源
	json_parse_whitespace(c);
	string copy = "";
	for (int i = c.index; i < c.json.size(); i++) {
		copy += c.json[i];
	}
	std::istringstream istoken(copy);
	std::string ss;
	std::stack<json_value*>st;   //用栈来存储结点
	st.push(v);
	while (std::getline(istoken, ss, '[')) {   //以[为分隔符分割string并逐一处理

		nums.push_back(ss);
	}
	
	for (auto s : nums) {
	
		
			json_value* now_json = st.top();
			lev++;
			if (lev > 1) {  //递归层数加一
				json_value* new_json = new json_value();
				new_json->type = json_NULL;
				now_json->child.push_back(new_json);
				st.push(new_json);
			}


			if (s.size() > 0) {
				int n = s.size();
				bool have_comma = false;//检查是否有逗号
				int i = n - 1;
				for (; i >= 0; i--) {
					if (s[i] != ' ') {
						if (s[i] == ',') {
							have_comma = true;
						}
						else {
							break;
						}
					}
				}
				if (!have_comma && s != nums.back()&&!isblank(s)) {


					while (!st.empty()) {
						json_value* l = st.top();
						st.pop();
						
					}
					v->type = json_FAITH;
					return PARSE_ARRAY_COMMA;
				}
				
				std::vector<std::string>nums2;//用以存储用逗号分割的string

				std::string res;
				res.resize(s.size());
				std::memcpy(&res[0], s.data(), i+1);
				std::istringstream resstring(res);
				std::string s1;
				while (std::getline(resstring, s1, ',')) {   //以','为分隔符分割string并逐一处理
					s1 += " ";//可以检测'[',不可省略
					nums2.push_back(s1);
					
				}
				for (auto s2 : nums2) {
					std::istringstream resstring2(s2);                   //以']'为分隔符分割string并逐一处理
					std::vector<std::string>nums3;
					std::string s3;
					while (std::getline(resstring2, s3, ']')) {   //以','为分隔符分割string并逐一处理
				
						nums3.push_back(s3);
						
					}
					int index = 0;
					for (auto s_final : nums3) {
						s_final = trimLeftSpaces(s_final);//去除前导空格
						
						index++;

						if (index > 1) {
							if (!st.empty())
								st.pop();
						}
						if (index == 1&&!isblank(s_final)) {
							//std::cout << s_final.size();
						//	std::cout << s_final << "  " << 52 << std::endl;
							json_value* pp = new json_value();
							json_parse(pp, s_final);
							if (st.empty())return PARSE_ARRAY_BRACKET;
							auto new_json = st.top();
							new_json->child.push_back(pp);
							
						}
						
					}
				

				}

			}

		
	}


	if (!st.empty()) {
		v->type = json_FAITH;
		return PARSE_ARRAY_BRACKET;
	
	}
	v->type = json_ARRAY;

		return PARSE_OK;
	
}

double parse::json_get_number(json_value* v) {
	assert(v != NULL && v->type == json_NUMBER);
	return v->value;
}




json_type parse::json_get_type(const json_value* v) {
	return v->type;
}

/*思路：分割对象使之成为一个一个同一级的项
  不断分解
*/
int parse::json_parse_object(context& c, json_value* v ) {
	c.index++;
	json_parse_whitespace(c);
	int lev = 1; //对象层数
	int n = c.json.size();
	string s="";
	int i = c.index;
	vector<string>obj1;//用以存储每一项
	

	for (; i < n; i++) {
		if (c.json[i] == '{'||c.json[i] == '[') {
			lev++;
		}
		if (c.json[i] == '}'||c.json[i]==']')lev--;
		if (c.json[i] == ',' && lev == 1) {    //当前层的项
			obj1.push_back(s);
			
			s = "";
			continue;
		}
		
		s += c.json[i];
		if (lev < 0) {
			v->type = json_FAITH;
			return PARSE_OBJECT_BRACES; }
	}

	//处理最后一个右括号
	s = removeLastClosingParenthesis(s);
	obj1.push_back(s);


		
	if (lev != 0) {      //括号不匹配
		v->type = json_FAITH;
		return PARSE_OBJECT_BRACES;
	}
	//处理每一个项
	int col = obj1.size();
	for (int j = 0; j < col; j++) {
		
		string ss = obj1[j];
		//cout << ss << endl;
		ss=trimLeftSpaces(ss);
		ss=trimRightSpaces(ss);
		string ss_key = "";
		string ss_value = "";
		bool fenge = false;       //分割key以及value
		for (auto a : ss) {
			if (a == ':'&&fenge==false) { 
				fenge = true;
				continue; }
			if (fenge) {
				ss_value += a;
			}
			else {
				ss_key += a;
			}
		}
		json_value* new_json = new json_value();
		new_json->type = json_COL;
		v->child.push_back(new_json);
		new_json->s = ss_key;
		json_value* now_value = new json_value();
		json_parse( now_value, ss_value);
		//cout << ss_value;
		new_json->child.push_back(now_value);
	
		

		//cout << ss_key << "  " << ss_value << endl;
	}

	v->type = json_OBJECT;

	

	return PARSE_OK;
}


string parse::get_json_string(json_value* v,int index){
	string s="";
	
	
	switch (v->type) {
	case json_NULL: {
		if (index > 1) {
			s += ",";
		}
		s += "NULL";
		break;
	}
	case json_FALSE: {
		if (index > 1) {
			s += ",";
		}
		s += "FALSE";
		break;
	}
	case json_TRUE: {
		if (index > 1) {
			s += ",";
		}
		s += "TRUE";
		break;
	}
	case json_STRING: {
		if (index > 1) {
			s += ",";
		}
		
		s += "\"" + v->s + "\"";    
		break;
	}
	case json_NUMBER:{
		if (index > 1) {
			s += ",";
		}
		std::ostringstream oss;
		oss << std::fixed  <<v->value; 
		std::string str = oss.str();
		
		s += str; break;
	}
	case json_ARRAY: {
		if (index > 1) {
			s += ",";
		}
		
		s += "[";
		for (int j = 0; j < v->child.size(); j++) {
			if (j > 0) {
				s += ",";
			}
			s += get_json_string(v->child[j], j);
		}
		s += "]";
		break;
	}
	case json_OBJECT: {
		if (index > 1) {
			s += ",";
		}
		
		s += "{";
		
		for (int j = 0; j < v->child.size(); j++) {
			
			
			s += get_json_string(v->child[j], j);
		}
		s += "}";
		break;
	}
	case json_COL: {  
		if (index > 1) {
			s += ",";
		}
		
		s +=  v->s ;
		s += ":";
		s += get_json_string(v->child[0], 0);
		break;
	}
	default:
		return "";
	}
	return s;
}
	

