#include <iostream>
#include <cstring>
#include <cstdlib>
#include <regex>

#define REGULAR_EXPRESSION_NAME "((([a-z]|[A-Z])+)://)?((([a-z]|[A-Z]|[0-9]){1,255})(:(([a-z]|[A-Z]|[0-9]){1,255}))?@)?(([a-z]|[A-Z]|[0-9]){1,255})+((\\.([a-z]|[A-Z]){2,})+)(:([1-9]+))?(/((.)+|[A-Z])*)?"
#define REGULAR_EXPRESSION_IPv4 "((([a-z]|[A-Z])+)://)?((([a-z]|[A-Z]|[0-9]){1,255})(:(([a-z]|[A-Z]|[0-9]){1,255}))?@)?([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})(:([1-9]+))?(/(.)*)?"

using namespace std;

enum {
    REGULAR_NAME = 1,
    REGULAR_IPv4,
    REGULAR_IPv6
};

int main () {

    string url,
           host,
           port,
           protocol,
           user,
           pass,
           path;

    short resp;

    regex expression_url_name (REGULAR_EXPRESSION_NAME);
    regex expression_url_ipv4 (REGULAR_EXPRESSION_IPv4);

    do {
        while(1) {

            url = "";
            host = "";
            port = "";
            protocol = "";
            user = "";
            pass = "";
            path = "";
            resp = 0;

            system("clear");
            cout<< endl << "insert url to : ";

            getline(cin, url);

            if(regex_match(url, expression_url_name)) {
                resp = REGULAR_NAME;

#define NAME_PROTOCOL "$2"
#define NAME_USER "$5"
#define NAME_PASS "$8"
#define NAME_HOST "$10$12"
#define NAME_PORT "$16"
#define NAME_PATH "$17"

                break;

            } else if(regex_match(url, expression_url_ipv4)) {

#define IP_PART_1 "$10"
#define IP_PART_2 "$11"
#define IP_PART_3 "$12"
#define IP_PART_4 "$13"

                cout << endl << " Part 1 " <<  regex_replace(url, expression_url_ipv4, IP_PART_1);
                cout << endl << " Part 2 " <<  regex_replace(url, expression_url_ipv4, IP_PART_2);
                cout << endl << " Part 3 " <<  regex_replace(url, expression_url_ipv4, IP_PART_3);
                cout << endl << " Part 4 " <<  regex_replace(url, expression_url_ipv4, IP_PART_4);

                if(atoi(regex_replace(url, expression_url_ipv4, IP_PART_1).c_str()) > 255 ) {
                    if(atoi(regex_replace(url, expression_url_ipv4, IP_PART_2).c_str()) > 255 ) {
                        if(atoi(regex_replace(url, expression_url_ipv4, IP_PART_3).c_str()) > 255 ) {
                            if(atoi(regex_replace(url, expression_url_ipv4, IP_PART_4).c_str()) > 255 ) {
                                /// IP SUCCESS
                                resp = REGULAR_IPv4;
/*

#define NAME_PROTOCOL "$2"
#define NAME_USER "$5"
#define NAME_PASS "$8"

#define NAME_HOST "$$"
#define NAME_PORT "$"
#define NAME_PATH "$"
 */                               break;
                            }
                        }
                    }
                }
            }

            /// check for each group number ip
            /// if number is > 255

            /// URL is FAIL
            ///  CONTINUE beyond here and print url Fail, and continue to while


        cout<< endl << "URL fail \n";
        cin.get();
        continue;

    }
    /// SAFE
    host = regex_replace(url, expression_url_name, NAME_HOST);
    port = regex_replace(url, expression_url_name, NAME_PORT);
    protocol = regex_replace(url, expression_url_name, NAME_PROTOCOL);
    user = regex_replace(url, expression_url_name, NAME_USER);
    pass = regex_replace(url, expression_url_name, NAME_PASS);
    path = regex_replace(url, expression_url_name, NAME_PATH);

    /// SAFE
    cout<< endl << "URL success : "<< resp ;

    if(resp == REGULAR_NAME) {
        cout<<" : HOST " <<endl <<endl;
    } else if(resp == REGULAR_IPv4) {
        cout<<" : IPv4 " <<endl <<endl;
    } else if(resp == REGULAR_IPv6) {
        cout<<" : IPv6 " <<endl <<endl;
    }

    cout<< "URL : " << url << endl ;
    cout<< "Host : " << host << endl ;
    cout<< "Port : " << port << endl ;
    cout<< "Protocol : " <<protocol << endl ;
    cout<< "User : " <<user << endl ;
    cout<< "Password : " <<pass << endl ;
    cout<< "Path : "<<path <<endl;

    cin.get();

}
while(1);
return 0;
}
