#include <iostream>
#include <string>
#include "c_tokenizer.h"

__thread int mysql_thread___query_digests_max_query_length;

__thread bool mysql_thread___query_digests_lowercase;
__thread bool mysql_thread___query_digests_replace_null;
__thread bool mysql_thread___query_digests_no_digits;

//char * mysql_query_digest_and_first_comment(char *s , int len , char **first_comment, char *buf);

int main() {
	mysql_thread___query_digests_lowercase = false;
	mysql_thread___query_digests_replace_null = true;
	mysql_thread___query_digests_no_digits = false;
	unsigned int count = 0;
    for (std::string line; std::getline(std::cin, line);) {
		size_t ql = line.length();
		for (unsigned int i=0; i<100000; i++) {
		char *digest = NULL;
		char *first_comment = NULL;
		char buf[4096];
		//digest = mysql_query_digest_and_first_comment((char *)line.c_str(), ql, &first_comment, (ql > 4000 ? NULL : buf));
		digest = mysql_query_digest_and_first_comment_test2((char *)line.c_str(), ql, &first_comment, (ql > 4000 ? NULL : buf));
		if (digest) {
			count++;
		}
		if (ql > 4000) {
			free(digest);
		}
		if (first_comment) free(first_comment);
		}
        //std::cout << line << std::endl;
    }
	std::cout << count << std::endl;
    return 0;
}
